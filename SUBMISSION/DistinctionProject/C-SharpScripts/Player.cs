using System.Collections.Generic;
using System.Linq;
using UnityEngine;

/// <summary>
/// Class Player.
/// 
/// Records the Players state and manages all of the player's components.
/// </summary>
public class Player : MonoBehaviour
{
    /// <summary>
    /// Enum representing the state of the player
    /// </summary>
    public enum PlayerState
    {
        Idle,
        Active,
        Crashed,
        Respawning
    }

    [SerializeField]
    private int _id = 1;                        // The player ID
    private int _controllerId = 1;              // The controller ID assigned to this player.
    [SerializeField]
    private Character.Type _type;               // The player's type
    [SerializeField]
    private GameObject _solidChair;             // The player's solid chair.
    private BreakableChair _breakableChair;     // The player's breakable chair.
    [SerializeField]
    private bool _debug = false;                // If the debugging information is displayed.

    public PlayerState State { get; private set; }          // The state of the player
    public float RespawnDelay = 1;                          // The delay before the player respawns.
    public float CameraRespawnDelay = 3;                    // How long the player needs to out of the screen before respawning.

    public ControllerMap Controller { get; private set; }   // The player controller

    private PlayerMovement _movement;                       // The player's movement script.
    public PlayerPickups Pickups { get; private set; }      // The player's pickup script.
    public PlayerBash Bash { get; private set; }            // The player's bash script.
    public Character Character { get; private set; }        // The player's character.
    public Health Health { get; private set; }              // The player's health

    public List<ChairWheel> Wheels { get; private set; }

    public PlayerStats Stats { get; private set; }          // The player's statistics.
    public PlayerAudio Audio { get; private set; }          // The player's audio manager script.
    public AnimationManager Animation { get; private set; } // The player's animation manager script.

    private int _physicsLayer;                              // The current players physics layer.
    public LayerMask LayerMask { get; private set; }        // The player mask
    private readonly float _collisionTestDist = 2.5f;       // The distance from the origin to test for collisions.

    private bool _insideCamera;                             // If the player is inside the camera or not. 

    public IntEvent PlayerCrashEvent { get; private set; }  // The player crash event

    /// <summary>
    /// Sets up the player.
    /// </summary>
    void Awake()
    {
        State = PlayerState.Idle;
        _insideCamera = true;
        PlayerCrashEvent = new IntEvent();

        if (PlayerDetailsManager.Instance != null && PlayerDetailsManager.Instance.HasPlayerDetails(_id))
        {
            PlayerDetails details = PlayerDetailsManager.Instance.GetPlayerDetails(_id);
            _controllerId = details.Controller;
            _type = details.Type;
        }
        else
        {
            _controllerId = _id;
        }

        ControllerManager.Controllers.AddController(_controllerId);
        Controller = ControllerManager.Controllers.GetController(_controllerId);

        _movement = GetComponent<PlayerMovement>();
        if (!_movement) Debug.LogError("Attach a PlayerMovement script to " + gameObject.name);
        Pickups = GetComponent<PlayerPickups>();
        if (!Pickups) Debug.LogError("Attach a PlayerPickups script to " + gameObject.name);
        Bash = GetComponent<PlayerBash>();
        if (!Bash) Debug.LogError("Attach a PlayerBash script to " + gameObject.name);
        Health = GetComponent<Health>();
        if (!Health) Debug.LogError("Attach a Health script to " + gameObject.name);
        Audio = GetComponent<PlayerAudio>();
        if (!Audio) Debug.LogError("Attach a PlayerAudio script to " + gameObject.name);
        Stats = GetComponent<PlayerStats>();
        if (!Stats) Debug.LogError("Attach a PlayerStats script to " + gameObject.name);

        Wheels = GetComponentsInChildren<ChairWheel>().ToList();

        if (!_solidChair) Debug.LogError("Attach a chair game object to the Player script on " + gameObject.name);
        _breakableChair = GetComponentInChildren<BreakableChair>();
        if (!_breakableChair) Debug.LogError("Attach a BreakableChair script to a child of " + gameObject.name);
        _breakableChair.gameObject.SetActive(false);

        // Disable the not used character
        foreach (Character character in GetComponentsInChildren<Character>())
        {
            if (character.CharacterType == _type)
            {
                Character = character;
                Animation = character.GetComponent<AnimationManager>();
            }
            else
            {
                character.gameObject.SetActive(false);
            }
        }

        if (!Character) Debug.LogError("Attach a Character script to a child of " + gameObject.name);
        if (!Animation) Debug.LogError("Attach an AnimationManager script to a child of " + gameObject.name);

        // Add the player to the correct physics layer.
        switch (Id)
        {
            case 1: SetPhysicsLayer(PhysicsLayer.Player1); break;
            case 2: SetPhysicsLayer(PhysicsLayer.Player2); break;
            case 3: SetPhysicsLayer(PhysicsLayer.Player3); break;
            case 4: SetPhysicsLayer(PhysicsLayer.Player4); break;
        }

        LayerMask = 1 << PhysicsLayer.Obstacles;
        if (Id != 1) LayerMask |= 1 << PhysicsLayer.Player1;
        if (Id != 2) LayerMask |= 1 << PhysicsLayer.Player2;
        if (Id != 3) LayerMask |= 1 << PhysicsLayer.Player3;
        if (Id != 4) LayerMask |= 1 << PhysicsLayer.Player4;

        // The parent layer should always be default so that it always detects collisions between all layers
        gameObject.layer = PhysicsLayer.Default;

        SetupCollisionTestRays(_collisionTestDist);
    }

    /// <summary>
    /// Constrain the player's movement while they are in the idle state
    /// </summary>
    void Start()
    {
        _movement.Rigidbody.constraints = RigidbodyConstraints.FreezePositionX | RigidbodyConstraints.FreezePositionZ;
    }

    /// <summary>
    /// Checks if the player has paused/resumed the game.
    /// </summary>
    void Update()
    {
        if (State == PlayerState.Idle) return;

        if (Controller.GetButtonDown(ControllerMap.Button.Start)) UIManager.Instance.ChangePauseState(_id, _controllerId);
    }

    /// <summary>
    /// Removes all rigidbody constraints and sets the player's state to be active.
    /// </summary>
    public void ActivatePlayer()
    {
        _movement.Rigidbody.constraints = RigidbodyConstraints.None;
        Controller.SetVibration(0.8f, 0.4f);
        State = PlayerState.Active;

        // Set an instantaneous velocity to the player so they are travelling at the same speed as the camera
        _movement.Rigidbody.velocity = new Vector3(0, 0, CameraMovement.CameraVelocity);
    }

    /// <summary>
    /// Forces the player to crash regardless of their health.
    /// </summary>
    public void FatalCrash()
    {
        Health.Kill();
        Crash();
    }

    /// <summary>
    /// Crashes the player.
    /// Sets the player's state to crashed and causes all of the other player components to crash.
    /// </summary>
    public void Crash(int amount = 0)
    {
        if (Crashed) return;
        if (Health.CurrentHealth > 0)
        {
            Health.TakeDamage(amount);
            return;
        }

        State = PlayerState.Crashed;

        Physics.IgnoreLayerCollision(_physicsLayer, _physicsLayer, false);

        Character.Crash(_movement.Rigidbody.velocity);
        _movement.Crash();
        Pickups.DropItem();

        _solidChair.gameObject.SetActive(false);
        Character.SetChairVisibility(false);
        _breakableChair.gameObject.SetActive(true);
        _movement.Rigidbody.constraints = RigidbodyConstraints.FreezeAll;

        Audio.ForcePlayAudioClip(Audio.Crash);
        PlayerCrashEvent.Invoke(Id);
        Controller.SetVibration(1, 2);
        Stats.AddDeath();

        if (_debug) Debug.Log(gameObject.name + " has crashed.");
    }

    /// <summary>
    /// Respawns the player.
    /// Causes all of the player's components to reset and sets the player's state to respawning.
    /// </summary>
    public void Respawn()
    {
        // If the player is inside the camera and is not currently crashed, they shouldn't respawn
        if (InsideCamera && !Crashed) return;

        bool validPosition;
        var newPosition = GeometryUtils.GetRandomBottomScreenPosition(out validPosition);

        // If the new position isn't valid or if they are crashed inside the camera, try to respawn again in half a second
        if (!validPosition || (InsideCamera && Crashed))
        {
            Invoke("Respawn", 0.5f);
            return;
        }

        gameObject.SetActive(true);
        SetIgnoreLayerCollisions(true);
        State = PlayerState.Respawning;

        Physics.IgnoreLayerCollision(_physicsLayer, _physicsLayer, true);
        Character.Reset();
        _movement.Reset();
        Bash.Reset();
        Health.Reset();

        _solidChair.gameObject.SetActive(true);
        Character.SetChairVisibility(true);
        _breakableChair.gameObject.SetActive(false);
        foreach (ChairWheel wheel in Wheels.Where(wheel => wheel.SparkParticle)) wheel.SparkParticle.Stop();

        _movement.Rigidbody.constraints = RigidbodyConstraints.None;

        // Sets the players new position
        transform.position = newPosition + new Vector3(0, 0.1f, 0);

        Invoke("EnableCollisions", 2);
        Controller.SetVibration(0.5f, 1);

        if (_debug) Debug.Log(gameObject.name + " has has repawned.");
    }

    /// <summary>
    /// Enables the player's collisions.
    /// </summary>
    private void EnableCollisions()
    {
        if (!Respawning) return;

        // If the player is not currently inside an obstacle, enable its collisions
        if (!InCollision())
        {
            SetIgnoreLayerCollisions(false);
            State = PlayerState.Active;
            if (_debug) Debug.Log(gameObject.name + " has had their collisions enabled.");
        }
        else
        {
            // Check every half second if collisions can be enabled again.
            Invoke("EnableCollisions", 0.5f);
        }
    }

    /// <summary>
    /// If the player is inside the camera or not.
    /// </summary>
    public bool InsideCamera
    {
        get { return _insideCamera; }
        set
        {
            // If the player is outside the camera and not disabled
            if (!value && gameObject.activeSelf)
            {
                // If the player has just fallen outside the camera, then play the out of camera audio
                if (_insideCamera)
                {
                    // TODO: Do we still need this audio?
                    VoiceAudio.PlayAudioClip(VoiceAudio.OutOfCamera);
                    if (_debug) Debug.Log(gameObject.name + " is outside the camera.");
                }

                // Crash and deactivate the player if they fall behind the camera
                if (transform.position.z < Camera.main.transform.parent.position.z - 19.8 && CharacterPosition.z < Camera.main.transform.parent.position.z - 19.8)
                {
                    FatalCrash();
                    gameObject.SetActive(false);
                }
            }
            _insideCamera = value;
        }
    }

    /// <summary>
    /// Sets the physics player for the player and all of it's children.
    /// </summary>
    /// <param name="layer">The layer to change it to.</param>
    private void SetPhysicsLayer(int layer)
    {
        _physicsLayer = layer;
        SetLayer(transform, layer);
    }

    /// <summary>
    /// Set the physics layer for the player and all it's children
    /// </summary>
    /// <param name="toChange">The transforms who's layer to change.</param>
    /// <param name="layer">The layer to change it to.</param>
    private void SetLayer(Transform toChange, int layer)
    {
        toChange.gameObject.layer = layer;

        foreach (Transform child in toChange)
        {
            if (transform.childCount > 0)
            {
                SetLayer(child, layer);
            }
            else
            {
                child.gameObject.layer = layer;
            }
        }
    }

    /// <summary>
    /// Updates the visibility of the models showing the players current place.
    /// </summary>
    public void UpdateVisalPlaceModels()
    {
        Character.SetCrownVisibility(LevelManager.GameResults.GetAmountOfPlayersAtPlace(1) <= 2
            && LevelManager.GameResults.GetPlayersPlace(Id) == 1);

        int lowestPlacement = LevelManager.GameResults.GetAmountOfPlayersAtPlace(4) > 0
            ? 4 : LevelManager.GameResults.GetAmountOfPlayersAtPlace(3) > 0
                ? 3 : LevelManager.GameResults.GetAmountOfPlayersAtPlace(2) > 0
                    ? 2 : 1;

        Character.SetLPlateVisibility(LevelManager.GameResults.GetAmountOfPlayersAtPlace(lowestPlacement) <= 2
            && LevelManager.GameResults.GetPlayersPlace(Id) == lowestPlacement);
    }

    /// <summary>
    /// Keeps track of when a player is collided with an obstacle and handles any special items the player collides with.
    /// </summary>
    /// <param name="collider">The collider it collided with.</param>
    void OnTriggerEnter(Collider collider)
    {
        HandleCollision(collider.gameObject, collider.isTrigger);
    }

    /// <summary>
    /// Handles the players collision with another game object.
    /// </summary>
    /// <param name="collidedObject">The object the player collided with.</param>
    /// <param name="isTriggerCollider">If the collider is a trigger.</param>
    public void HandleCollision(GameObject collidedObject, bool isTriggerCollider = false)
    {
        if (Crashed) return;
        switch (collidedObject.tag)
        {
            case "Pickup":
                // If the player is crashed or immune to the pickup then do nothing
                Pickup pickup = collidedObject.GetComponent<Pickup>();
                if (pickup && pickup.IsImmune(this)) return;

                if (Pickups.HandlePickup(pickup))
                {
                    Character.Audio.PlayAudioClip(Character.Audio.HitByPickup);
                    Crash();

                    // If the pickup has caused a crash, then add a takedown to the opposing player's stats
                    if (Crashed && pickup.Holder) pickup.Holder.Stats.AddTakedown();
                }
                break;
            case "Stamina":
                Health.AddHealth(collidedObject.GetComponent<Stamina>().Collect());
                Stats.CollectedCoffee();
                break;
            case "Moving Obstacle":
                if (isTriggerCollider || Respawning) return;
                FatalCrash();
                Audio.PlayAudioClip(Audio.CarHit);
                Stats.KilledByCar();
                break;
            case "Obstacle":
                Health.ObstacleCollision();
                Audio.PlayAudioClip(Audio.Collision);
                Crash();
                break;
        }
    }

    /// <summary>
    /// Sets the ignore collision layers.
    /// While a player is respawning, it should ignore collisions between other players and obstacles.
    /// The collisions should be re-enabled when the player has finished re-spawning.
    /// </summary>
    /// <param name="isEnabled"></param>
    private void SetIgnoreLayerCollisions(bool isEnabled)
    {
        Physics.IgnoreLayerCollision(_physicsLayer, PhysicsLayer.Obstacles, isEnabled);
        if (_physicsLayer != PhysicsLayer.Player1)
        {
            Physics.IgnoreLayerCollision(_physicsLayer, PhysicsLayer.Player1, isEnabled);
        }
        if (_physicsLayer != PhysicsLayer.Player2)
        {
            Physics.IgnoreLayerCollision(_physicsLayer, PhysicsLayer.Player2, isEnabled);
        }
        if (_physicsLayer != PhysicsLayer.Player3)
        {
            Physics.IgnoreLayerCollision(_physicsLayer, PhysicsLayer.Player3, isEnabled);
        }
        if (_physicsLayer != PhysicsLayer.Player4)
        {
            Physics.IgnoreLayerCollision(_physicsLayer, PhysicsLayer.Player4, isEnabled);
        }
    }

    /// <summary>
    /// Checks if the passed physics layer belongs to an opposing player.
    /// </summary>
    /// <param name="layerToCheck">The layer to check.</param>
    /// <returns>True if it is an opposing player physics layer, false if not.</returns>
    public bool IsOpposingPlayerLayer(int layerToCheck)
    {
        // If the layer to check is the player's physics layer then return false
        if (layerToCheck == _physicsLayer) return false;

        switch (layerToCheck)
        {
            case PhysicsLayer.Player1: return true;
            case PhysicsLayer.Player2: return true;
            case PhysicsLayer.Player3: return true;
            case PhysicsLayer.Player4: return true;
            default: return false;
        }
    }

    /// <summary>
    /// Gets the player's Rigidbody.
    /// </summary>
    public Rigidbody Rigidbody
    {
        get { return _movement.Rigidbody; }
    }

    /// <summary>
    /// The position of the character in the player object.
    /// </summary>
    public Vector3 CharacterPosition
    {
        get { return Character.Position; }
    }

    /// <summary>
    /// Gets the position of the rubber band.
    /// </summary>
    public Vector3 RubberBandPosition
    {
        get { return transform.position + Vector3.up * 0.7f; }
    }

    /// <summary>
    /// Gets the character's voice audio.
    /// </summary>
    public CharacterVoiceAudio VoiceAudio
    {
        get { return Character.Audio; }
    }

    /// <summary>
    /// Checks whether the player is above the track or not.
    /// Both the character and the chair needs to be above the track for it to be true.
    /// </summary>
    public bool AboveTrack
    {
        get { return Character.AboveTrack() && _movement.AboveTrack(); }
    }

    /// <summary>
    /// Checks if the player is currently in a collision with another player or an obstacle.
    /// </summary>
    /// <returns></returns>
    private bool InCollision()
    {
        return _collisionRays.Any(ray => Physics.Raycast(transform.TransformPoint(ray.origin), ray.direction, 4.5f, LayerMask));
    }

    private List<Ray> _collisionRays = new List<Ray>();

    /// <summary>
    /// Creates a list of eight rays in a circle around a point.
    /// </summary>
    /// <param name="distance">The distance of the ray from the origin.</param>
    private void SetupCollisionTestRays(float distance)
    {
        _collisionRays = new List<Ray>();
        float diagonalDist = distance * Mathf.Cos(Mathf.Deg2Rad * 45);
        Vector3 direction = transform.TransformPoint(Vector3.up) - transform.TransformPoint(Vector3.zero);

        _collisionRays.Add(new Ray(new Vector3(distance, 0, 0), direction));
        _collisionRays.Add(new Ray(new Vector3(-distance, 0, 0), direction));
        _collisionRays.Add(new Ray(new Vector3(0, 0, distance), direction));
        _collisionRays.Add(new Ray(new Vector3(0, 0, -distance), direction));

        _collisionRays.Add(new Ray(new Vector3(diagonalDist, 0, diagonalDist), direction));
        _collisionRays.Add(new Ray(new Vector3(diagonalDist, 0, -diagonalDist), direction));
        _collisionRays.Add(new Ray(new Vector3(-diagonalDist, 0, diagonalDist), direction));
        _collisionRays.Add(new Ray(new Vector3(-diagonalDist, 0, -diagonalDist), direction));
    }

    /// <summary>
    /// If the player is crashed.
    /// </summary>
    public bool Crashed
    {
        get { return State == PlayerState.Crashed; }
    }

    /// <summary>
    /// If the player is respawning
    /// </summary>
    public bool Respawning
    {
        get { return State == PlayerState.Respawning; }
    }

    /// <summary>
    /// Gets/Sets the Player ID as well as sets the material
    /// </summary>
    public int Id
    {
        get { return _id; }
    }

    /// <summary>
    /// Draws the collision test gizmos.
    /// </summary>
    void OnDrawGizmos()
    {
        if (_collisionRays != null)
        {
            // Draw Raycating positions
            Gizmos.color = Color.cyan;
            foreach (Ray ray in _collisionRays) Gizmos.DrawLine(transform.TransformPoint(ray.origin), transform.TransformPoint(ray.origin) + ray.direction * 4.5f);
        }

        Gizmos.color = new Color(1, 0.5f, 0);
        Gizmos.DrawSphere(RubberBandPosition, 0.2f);
    }
}