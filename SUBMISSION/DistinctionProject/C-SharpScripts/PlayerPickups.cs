using UnityEngine;

/// <summary>
/// Class PlayerPickups.
/// 
/// Handles the player pickups. A player can only hold one item at a time.
/// When a player collides with a pickup they automatically pick it up. If the player is already holding a pickup it ignores it.
/// </summary>
[RequireComponent(typeof(Player))]
public class PlayerPickups : MonoBehaviour
{
    [SerializeField]
    private ParticleSystem _spinAttackParticle; // The spin attack particle

    private Player _player;                     // The player script
    private Pickup _currentPickup;              // The currently held pickup.

    private Timer _attackTimer;                 // The timer for attacks
    private bool _pickupUsed;                   // If the current pickup has been used

    /// <summary>
    /// Initializes the variables.
    /// </summary>
    void Awake()
    {
        _player = GetComponent<Player>();
        _currentPickup = null;

        _attackTimer = new Timer(3f, false);
        _pickupUsed = false;

        if (_spinAttackParticle) _spinAttackParticle.Stop();
    }

    /// <summary>
    /// Moves the pickup into position if there is one.
    /// </summary>
    void Update()
    {
        if (_player.State == Player.PlayerState.Idle || LevelManager.Paused) return;

        if (!HasPickup) return;

        if (_attackTimer.TimerFinished) _currentPickup.Armed = false;

        // If the pickup has been used then force the player to drop it.
        if (_pickupUsed && _attackTimer.TimerFinished)
        {
            DropItem();
            return;
        }

        // Check for controller inputs
        if (_player.Controller.GetButtonDown(ControllerMap.Button.GamepadBottom)) UsePickup();
        if (_player.Controller.GetButton(ControllerMap.Button.GamepadTop)) DropItem();
    }

    /// <summary>
    /// Handles the pickup and returns whether the pickup caused damage.
    /// </summary>
    /// <param name="item">The pickup to handle.</param>
    /// <returns>True if the pickup caused damage, false if not.</returns>
    public bool HandlePickup(Pickup item)
    {
        if (!item) Debug.LogError("An item with the the 'Pickup' tag needs to have the Pickup script attached");

        if (_player.Crashed) return false;

        if (item.Armed)
        {
            TakeDamage(item);
            return true;
        }

        if (item.CanPickUp && !_currentPickup)
        {
            PickupItem(item);
        }

        return false;
    }

    /// <summary>
    /// Uses the pickup the player is holding
    /// </summary>
    public void UsePickup()
    {
        if (!_currentPickup || !_attackTimer.TimerFinished) return;

        // If the player is currently hurt, then they can't use the item
        if (_player.Health.IsHurt) return;

        MoveItemToHand(Hand.Side.Right);
        _player.Animation.SetSpinAttack(true);

        _attackTimer.Reset();
        _currentPickup.Use();
        _pickupUsed = true;
        Invoke("TurnOffAnimations", 0.7f);
        Invoke("ArmPickup", 1.3f);

        _player.Character.Audio.PlayAudioClip(_player.Character.Audio.UsePickup);
    }

    /// <summary>
    /// Moves the pickup to the given hand side.
    /// </summary>
    /// <param name="side">The hand to give the pickup to.</param>
    public void MoveItemToHand(Hand.Side side)
    {
        if (!_currentPickup) return;

        foreach (Hand hand in _player.Character.Hands)
        {
            if (hand.HandSide == side) hand.HoldItem(_currentPickup);
            else hand.DropItem();
        }
    }

    /// <summary>
    /// Picks up the item.
    /// </summary>
    /// <param name="item">The item to pickup</param>
    private void PickupItem(Pickup item)
    {
        _currentPickup = item;
        _currentPickup.PickUp(_player);
        _player.Stats.CollectedPickup();

        if (_player.Character.Hands.Count > 0) _player.Character.Hands[0].HoldItem(item);
    }

    /// <summary>
    /// Gets the player to take damage from the item.
    /// </summary>
    /// <param name="item">The item to take damage from.</param>
    private void TakeDamage(Pickup item)
    {
        if (item.Armed && item.IsImmune(_player)) return;

        _player.Audio.PlayAudioClip(_player.Audio.PickupHit);
        _player.Health.PickupCollision(item.Holder, item.Damage);

        Vector3 direction = transform.position - item.Holder.transform.position;
        direction.y = 0;
        _player.Rigidbody.AddForce(direction.normalized * item.HitForce, ForceMode.VelocityChange);
        _player.Crash();

        item.HitPlayer();
    }

    /// <summary>
    /// Drops the pickup if the player is holding one.
    /// </summary>
    public void DropItem()
    {
        if (!_currentPickup || UsingItem) return;

        _currentPickup.Drop();
        _currentPickup = null;
        _pickupUsed = false;

        foreach (Hand hand in _player.Character.Hands) hand.DropItem();
    }

    /// <summary>
    /// Arms the pickup.
    /// </summary>
    private void ArmPickup()
    {
        _currentPickup.Armed = true;
        if (_spinAttackParticle) _spinAttackParticle.Play();
    }

    /// <summary>
    /// Sets the large attack animation flags to false so they don't keep playing.
    /// </summary>
    private void TurnOffAnimations()
    {
        _player.Animation.SetSpinAttack(false);
    }

    /// <summary>
    /// Returns whether the player is holding a pickup.
    /// </summary>
    public bool HasPickup
    {
        get { return _currentPickup; }
    }

    /// <summary>
    /// Returns whether the player is currently using an item.
    /// </summary>
    public bool UsingItem
    {
        get { return !_attackTimer.TimerFinished; }
    }
}
