using UnityEngine;
using System.Collections.Generic;
using System.Linq;

/// <summary>
/// Class PlayerMovement.
/// 
/// Controls the movement of the player.
/// </summary>
[RequireComponent(typeof(Player))]
public class PlayerMovement : Movement
{
    private Player _player;                 // The player script.

    [SerializeField]
    private float _accelerationForce = 1;   // The acceleration force.
    [SerializeField]
    private float _decelerationForce = 1;   // The player's break force.
    [SerializeField]
    private float _turningForce = 1;        // The forced used to turn the player. 
    [SerializeField]
    private float _inAirDownwardsForce = 10;  // The downwards force applied on the player while they are in the air.
    [SerializeField]
    private float _rubberBandAcceleration = 1;  // The acceleration force applied for rubber banding.   

    [SerializeField]
    private float _crashMagnitude = 20;     // The minimum magnitude of a collision to cause a player to crash.
    [SerializeField]
    private float _respawnAcceleration = 10f;     // The acceleration when respawning.

    private Vector3 _startingRotation;      // The starting rotation.
    private Vector3 _startingCenterOfMass;  // The starting center of mass.
    private Vector3 _centerOfMass;          // The center of mass.

    private float _positionOffset;          // How close the player needs to get to the position when accelerating

    private float _maxUprightRotation;      // The rotation to restrict the player to when it is being forced upright

    private const float _controllerSensitivity = 0.2f;  // The controller sensitivity threshold
    private const float _minBreakingSpeed = 10;     // Used to calculate the players minimum breaking speed (camera velocity - breaking speed)
    private const float _maxAcceleratingSpeed = 10; // Used to calculate the players maximum accelerating speed (camera velocity + accelerating speed)  

    /// <summary>
    /// Gets all of the variables to initalise.
    /// </summary>
    void Awake()
    {
        Initialise();
    }

    /// <summary>
    /// Initalises all of the PlayerMovement and Movement variables.
    /// This method is used instead of Awake() because calling Awake() override the base Awake() method in Movement.
    /// </summary>
    protected override void Initialise()
    {
        base.Initialise();

        _player = GetComponent<Player>();

        // Save start values that are used when the player is reset.
        _startingCenterOfMass = Rigidbody.centerOfMass;
        _startingRotation = Rigidbody.rotation.eulerAngles;

        // Set the center of mass to be lower down on the chair.
        _centerOfMass = new Vector3(0, 0, 0);
        Rigidbody.centerOfMass = _centerOfMass;

        _maxUprightRotation = 13;
        _positionOffset = 0.5f;
    }

    /// <summary>
    /// Takes the controller's X-axis input to rotate and turn the player.
    /// </summary>
    void Update()
    {
        if (_player.State == Player.PlayerState.Idle || LevelManager.Paused) return;

        // If the player is below the track, force crash the player
        if (!_player.AboveTrack)
        {
            _player.FatalCrash();
            return;
        }

        // Don't control the player's movement if it has crashed
        if (_player.Crashed) return;

        // Add a extra downwards force on the player when they are in the air
        if (!Grounded()) Rigidbody.AddRelativeForce(Vector3.down * _inAirDownwardsForce, ForceMode.Acceleration);

        // Accelerating
        if (_player.Controller.YAxis < -_controllerSensitivity)
        {
            Accelerate();
        }
        // Breaking
        else if (_player.Controller.YAxis > _controllerSensitivity)
        {
            Decelerate();
        }
        // If the player isn't accelerating or decelerating, get them to accelerate/decelerate to the camera velocity
        else
        {
            if (Rigidbody.velocity.z < 0.1 && Rigidbody.velocity.z > 0.1)
            {
                float difference = CameraMovement.CameraVelocity / Rigidbody.velocity.z;
                Vector3 targetVelocity = Rigidbody.velocity * difference;
                Rigidbody.velocity = Vector3.Lerp(Rigidbody.velocity, targetVelocity, Time.deltaTime * 5);
            }
        }

        // Turning
        if (_player.Controller.XAxis > _controllerSensitivity || _player.Controller.XAxis < -_controllerSensitivity)
        {
            Turn();
        }
        else
        {
            // If a player isn't turning, return their x-axis velocity to 0
            AccelerateToVelocity(new Vector3(0, Rigidbody.velocity.y, Rigidbody.velocity.z));
        }

        // Update the player animations
        _player.Animation.SetXAxis(_player.Controller.XAxis);
        _player.Animation.SetYAxis(_player.Controller.YAxis);

        // Add the rubber band forces
        Vector3 centerPosition = GeometryUtils.GetAveragePlayerPosition(LevelManager.Players);
        if (centerPosition != Vector3.zero && (transform.position - centerPosition).magnitude > RubberBand.RubberBandSize)
        {
            MoveTo(centerPosition, _rubberBandAcceleration, RubberBand.RubberBandSize);
        }

        // Rotate the character back to the origin in the y-axis
        var rotateTo = transform.rotation;
        rotateTo.y = Quaternion.Euler(0, 0, 0).y;
        transform.rotation = Quaternion.Lerp(transform.rotation, rotateTo, Time.deltaTime * 5);
    }

    /// <summary>
    /// Controls the speed of office chair and the wheel colliders
    /// </summary>
    void FixedUpdate()
    {
        if (_player.State == Player.PlayerState.Idle || LevelManager.Paused) return;

        // Don't control the player's movement if it has crashed.
        if (_player.Crashed)
        {
            // Always cap the player speed so that the ragdolls don't freak out when the players go to fast
            CapSpeed(CameraMovement.CameraVelocity);
            return;
        }

        // Force the player to stay upright
        ForcePlayerUpright();

        // If the player has passed the front of the camera bounds, decelerate until they are inside the bounds
        if (transform.position.z > CameraMovement.TopCameraBounds)
        {
            Break(0.1f);
            CapSpeed(CameraMovement.CameraVelocity);
        }
        // If the player has fallen behind the camera bounds, accelerate until they are inside the bounds
        else if (transform.position.z < CameraMovement.BottomCameraBounds)
        {
            AccelerateToPosition(CameraMovement.TopCameraBoundsPosition);
        }
        else
        {
            // If the player is accelerating
            if (_player.Controller.YAxis < -_controllerSensitivity)
            {
                CapSpeed(CameraMovement.CameraVelocity + _maxAcceleratingSpeed);
            }
            // If the player is decelerating
            else if (_player.Controller.XAxis > _controllerSensitivity)
            { }
            else
            {
                CapSpeed(CameraMovement.CameraVelocity + _maxAcceleratingSpeed);
            }
        }
    }

    /// <summary>
    /// Gets the player to accelerate.
    /// </summary>
    private void Accelerate()
    {
        // If the player is above the top of the bounds then don't accelerate
        if (transform.position.z > CameraMovement.TopCameraBounds) return;

        Vector3 acceleratingVelocity = Rigidbody.velocity + new Vector3(0, _player.Controller.YAxis * (_accelerationForce / 2), _player.Controller.YAxis * -_accelerationForce);
        AccelerateToVelocity(acceleratingVelocity);
    }

    /// <summary>
    /// Gets the player to decelerate.
    /// </summary>
    private void Decelerate()
    {
        // Only break if the players velocity is below the minimum
        // or if they are above the bottom of the camera bounds
        if (Rigidbody.velocity.z > CameraMovement.CameraVelocity - _minBreakingSpeed &&
            transform.position.z > CameraMovement.BottomCameraBounds)
        {
            Break(_decelerationForce * _player.Controller.YAxis);
        }
    }

    /// <summary>
    /// Turns the player in the direction of the controller's XAxis.
    /// </summary>
    private void Turn()
    {
        Vector3 turningVelocity = Rigidbody.velocity;
        turningVelocity.x = _player.Controller.XAxis * _turningForce;
        AccelerateToVelocity(turningVelocity);
    }

    /// <summary>
    /// Gets the player to accelerate to a velocity
    /// </summary>
    /// <param name="newVelocity">The velocity to accelerate to.</param>
    private void AccelerateToVelocity(Vector3 newVelocity)
    {
        Rigidbody.velocity = Vector3.Lerp(Rigidbody.velocity, newVelocity, Time.deltaTime * 5);
    }

    /// <summary>
    /// Forces the player to stay in an upright position when they are not crashed.
    /// </summary>
    private void ForcePlayerUpright()
    {
        Vector3 rotation = transform.rotation.eulerAngles;

        rotation.x = CalculationUtils.RestrictAngle(rotation.x, _maxUprightRotation);
        rotation.z = CalculationUtils.RestrictAngle(rotation.z, _maxUprightRotation);

        transform.rotation = Quaternion.Euler(rotation);
    }

    /// <summary>
    /// Accelerates the player to a position on the camera. 
    /// </summary>
    /// <param name="position">The camera position to accelerate to.</param>
    /// <param name="sameXPosition">If the position should be at the same x position the player is currently in.</param>
    private void AccelerateToCameraPosition(Vector3 position, bool sameXPosition = true)
    {
        // If the target position is not on the track then don't accelerate
        bool onTrack;
        Vector3 targetPosition = GeometryUtils.CalculatePositionOnCamera(position, out onTrack);
        if (!onTrack) return;

        AccelerateToPosition(targetPosition, sameXPosition);
    }

    /// <summary>
    /// Accelerates the player to a position.
    /// </summary>
    /// <param name="position">The camera position to accelerate to.</param>
    /// <param name="sameXPosition">If the position should be at the same x position the player is currently in.</param>
    private void AccelerateToPosition(Vector3 position, bool sameXPosition = true)
    {
        // Modify the position to be in the same x position as the player is currently in
        if (sameXPosition) position.x = transform.position.x;

        // Change the rate the player is accelerating depending on how close they are to the target
        float acceleration = _respawnAcceleration * Vector3.Distance(position, transform.position);

        // If the player has reached the target position then stop accelerating
        MoveTo(position, acceleration, _positionOffset);
    }

    /// <summary>
    /// Checks if all the player's wheels are on the ground.
    /// </summary>
    /// <returns>True is all the wheels are on the ground, false if not.</returns>
    private bool Grounded()
    {
        bool isGrounded = true;

        foreach (var wheel in _player.Wheels.Where(wheel => !IsGrounded(wheel.transform.position)))
        {
            isGrounded = false;
        }

        return isGrounded;
    }

    /// <summary>
    /// Handles the player collisions
    /// <param name="collision">The object that the player collided with.</param>
    /// </summary>
    void OnCollisionEnter(Collision collision)
    {
        if (collision.gameObject.tag != "Track" && !collision.transform.IsChildOf(transform))
        {
            _player.Controller.SetVibration(0.1f, 0.3f);

            if (_player.IsOpposingPlayerLayer(collision.gameObject.layer))
            {
                Vector3 direction = transform.position - collision.transform.position;
                Rigidbody.AddForce(direction.normalized * 5, ForceMode.VelocityChange);
            }
            else if (collision.impulse.magnitude > _crashMagnitude)
            {
                _player.HandleCollision(collision.gameObject);
            }
        }
    }

    /// <summary>
    /// Crashes the player.
    /// </summary>
    public void Crash()
    {
        Rigidbody.centerOfMass = _startingCenterOfMass;
    }

    /// <summary>
    /// Sets the player's center of mass and sets its rotation to (0, 0, 0).
    /// </summary>
    public void Reset()
    {
        transform.rotation = Quaternion.Euler(_startingRotation);
        Rigidbody.centerOfMass = _centerOfMass;
        Rigidbody.angularVelocity = Vector3.zero;
    }

    /// <summary>
    /// Checks if the player is above the track.
    /// </summary>
    public bool AboveTrack()
    {
        var origin = transform.position + new Vector3(0, 3, 0);
        return Physics.Raycast(origin, Vector3.down, 100, 1 << PhysicsLayer.Track);
    }

    /// <summary>
    /// Draw's gizmos.
    /// </summary>
    void OnDrawGizmosSelected()
    {
        // Draw a circle in front of the player
        Gizmos.color = Color.cyan;
        Gizmos.DrawSphere(transform.position + new Vector3(0, 1, 2), 0.3f);
        Gizmos.DrawSphere(transform.position + new Vector3(0, 1.4f, 0), 0.1f);

        // Draw character position
        if (_player)
        {
            Gizmos.color = Color.green;
            Gizmos.DrawSphere(_player.CharacterPosition, 0.5f);
        }

        // Draw the center of mass
        if (Rigidbody)
        {
            Gizmos.color = Color.yellow;
            Gizmos.DrawSphere(transform.position + Rigidbody.centerOfMass, 0.3f);
        }

        // Draw the grounded checking values
        foreach (var collider in GetComponentsInChildren<WheelCollider>())
        {
            Vector3 destination = collider.transform.position + (Vector3.down * 0.3f);
            Gizmos.DrawLine(collider.transform.position, destination);
        }

        // Draw the direction the player is heading
        Vector3 origin = transform.position;
        origin.y = origin.y + 2;
        Gizmos.color = Color.green;
        if (Rigidbody) Gizmos.DrawLine(origin, origin + (Rigidbody.velocity.normalized * 3));

        // Draw the direction the player is facing
        Gizmos.color = Color.red;
        Vector3 facing = GeometryUtils.GetPlayerFacingDirection(transform);
        Gizmos.DrawLine(origin, origin + (facing.normalized * 3));
    }
}
