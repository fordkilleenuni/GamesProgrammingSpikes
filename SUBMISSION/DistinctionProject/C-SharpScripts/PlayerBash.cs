using UnityEngine;
using System.Collections.Generic;
using System.Linq;

/// <summary>
/// Class PlayerBash.
/// 
/// Handles the player punches and kicks.
/// </summary>
public class PlayerBash : MonoBehaviour
{
    [SerializeField]
    private float _punchForce = 3;      // The force of the punch on the opposing player
    [SerializeField]
    private float _punchTime = 0.3f;    // The time delay that the punch damage is inflicted

    [SerializeField]
    private float _kickForce = 7;       // The force of the kick on the opposing player
    [SerializeField]
    private float _kickTime = 0.5f;     // The time delay that the kick damage is inflicted

    [SerializeField]
    private ParticleSystem _punchParticle;  // The particle played when the punch is successful
    [SerializeField]
    private ParticleSystem _kickParticle;   // The particle played when the kick is successful

    private Player _player;             // The player script

    private Timer _cooldownTimer;       // The cooldown timer between attacks   

    /// <summary>
    /// Initializes the PlayerBash.
    /// </summary>
    void Awake()
    {
        _player = GetComponent<Player>();

        _cooldownTimer = new Timer(0.1f, false);

        if (_punchParticle) _punchParticle.Stop();
        if (_kickParticle) _kickParticle.Stop();
    }

    /// <summary>
    /// Checks if a controller button has been pressed to trigger a new bash and executes 
    /// any previously triggered bashes.
    /// </summary>
    void Update()
    {
        if (_player.State == Player.PlayerState.Idle || LevelManager.Paused || _player.Crashed) return;

        // Check for left punch
        if (_player.Controller.GetButtonDown(ControllerMap.Button.LeftBumper))
        {
            TriggerPunch(true);
        }
        else
        {
            _player.Animation.SetLeftPunch(false);
        }

        // Check for right punch
        if (_player.Controller.GetButtonDown(ControllerMap.Button.RightBumper))
        {
            TriggerPunch(false);
        }
        else
        {
            _player.Animation.SetRightPunch(false);
        }

        // Check for left kick
        if (_player.Controller.GetButtonDown(ControllerMap.Button.LeftTrigger))
        {
            TriggerKick(true);
        }
        else
        {
            _player.Animation.SetLeftKick(false);
        }

        // Check for right kick
        if (_player.Controller.GetButtonDown(ControllerMap.Button.RightTrigger))
        {
            TriggerKick(false);
        }
        else
        {
            _player.Animation.SetRightKick(false);
        }
    }

    /// <summary>
    /// Resets the player bash.
    /// </summary>
    public void Reset()
    {
        _cooldownTimer.Stop();

        // Disable all of the animation parameters
        _player.Animation.SetLeftPunch(false);
        _player.Animation.SetRightPunch(false);
        _player.Animation.SetLeftKick(false);
        _player.Animation.SetRightKick(false);

        DisableLimbs();
    }

    /// <summary>
    /// Triggers a punch.
    /// </summary>
    /// <param name="leftPunch">If the punch is to the left.</param>
    private void TriggerPunch(bool leftPunch)
    {
        // If the player is currently hurt or using an item, then they can't punch
        if (_player.Health.IsHurt || _player.Pickups.UsingItem) return;

        _cooldownTimer.Reset(_punchTime);

        Invoke("DisableLimbs", 1);

        _player.Animation.SetLeftPunch(leftPunch);
        _player.Animation.SetRightPunch(!leftPunch);

        Hand.Side side = leftPunch ? Hand.Side.Left : Hand.Side.Right;
        _player.Pickups.MoveItemToHand(side);

        foreach (Hand hand in _player.Character.Hands.Where(hand => hand.HandSide == side))
        {
            hand.Attacking = true;
        }

        _player.VoiceAudio.PlayAudioClip(_player.VoiceAudio.Punch);
        _player.Audio.PlayAudioClip(_player.Audio.Punch);
    }

    /// <summary>
    /// Triggers a kick.
    /// </summary>
    /// <param name="leftKick">If the kick is to the left.</param>
    private void TriggerKick(bool leftKick)
    {
        if (!_cooldownTimer.TimerFinished) return;

        // If the player is currently hurt or using an item, then they can't kick
        if (_player.Health.IsHurt || _player.Pickups.UsingItem) return;

        _cooldownTimer.Reset(_kickTime);

        Invoke("DisableLimbs", 1);

        Hand.Side footSide;
        if (leftKick)
        {
            _player.Animation.SetLeftKick(true);
            footSide = Hand.Side.Left;
        }
        else
        {
            _player.Animation.SetRightKick(true);
            footSide = Hand.Side.Right;
        }

        foreach (Foot foot in _player.Character.Feet)
        {
            if (foot.FootSide == footSide) foot.Attacking = true;
        }

        _player.VoiceAudio.PlayAudioClip(_player.VoiceAudio.Kick);
        _player.Audio.PlayAudioClip(_player.Audio.Kick);
    }

    /// <summary>
    /// Disabled the players hands and feet from attacking.
    /// </summary>
    private void DisableLimbs()
    {
        foreach (Hand hand in _player.Character.Hands) hand.Attacking = false;
        foreach (Foot foot in _player.Character.Feet) foot.Attacking = false;
    }

    /// <summary>
    /// Executes a punch attack.
    /// </summary>
    /// <param name="victim">The victim of the punch.</param>
    /// <param name="hitPosition">The position of the hit.</param>
    public void Punch(GameObject victim, Vector3 hitPosition)
    {
        Player player = victim.GetComponentInParent<Player>();
        if (!player) victim.GetComponent<Player>();

        if (player)
        {
            _player.Controller.SetLeftVibration(0.2f, 0.2f);

            // Inflict the damage on the victim
            player.Health.PunchDamage(_player);
            Bash(player, hitPosition, _punchForce, _punchParticle);

            // Disable the attacking hand
            foreach (Hand hand in _player.Character.Hands) hand.Attacking = false;
        }
    }

    /// <summary>
    /// Executes a kick attack.
    /// </summary>
    /// <param name="victim">The victim of the kick.</param>
    /// <param name="hitPosition">The position of the hit.</param>
    public void Kick(GameObject victim, Vector3 hitPosition)
    {
        Player player = victim.GetComponentInParent<Player>();
        if (!player) victim.GetComponent<Player>();

        if (player)
        {
            _player.Controller.SetLeftVibration(0.2f, 0.5f);

            // Inflict the damage on the victim
            player.Health.KickDamage(_player);
            Bash(player, hitPosition, _kickForce, _kickParticle);

            // Disable the attacking foot
            foreach (Foot foot in _player.Character.Feet) foot.Attacking = false;
        }
    }

    /// <summary>
    /// Executes a bash.
    /// </summary>
    /// <param name="player">The player that was hit by the bash.</param>
    /// <param name="hitPosition">The position of the bash hit.</param>
    /// <param name="force">The force applied to the victim of the bash.</param>
    /// <param name="hitParticles">The hit particles played.</param>
    private void Bash(Player player, Vector3 hitPosition, float force, ParticleSystem hitParticles)
    {
        Vector3 direction = player.transform.position - transform.position;
        direction.y = 0;
        player.Rigidbody.AddForce(direction.normalized * force, ForceMode.VelocityChange);

        // Play the hit hitParticle at the position of impact
        if (hitParticles)
        {
            hitParticles.transform.position = hitPosition;
            if (!hitParticles.isPlaying) hitParticles.Play();
        }
    }
}