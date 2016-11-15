using UnityEngine;

/// <summary>
/// Class PlayerStats.
/// 
/// Records the player's statistics throughtout the level.
/// </summary>
[RequireComponent(typeof(Player))]
public class PlayerStats : MonoBehaviour
{
    public int Wins { get; private set; }           // The amount of wins   
    public int Deaths { get; private set; }         // The amount of deaths    
    public int Takedowns { get; private set; }      // The amount of takedowns
    public int CoffeeCupsCollected { get; private set; }    // The amount of coffee cups collected 
    public int ObstaclesDestroyed { get; private set; }     // The amount of obstacles destroyed
    public int PickupsUsed { get; private set; }    // The amount of pickups used
    public int DamageTaken { get; private set; }    // The amount of damage taken
    public int DamageDone { get; private set; }     // The amount of damage the player has inflicted
    public int CarDeaths { get; private set; }      // The amount of times a player was killed by a car

    public float TimeAlive { get; private set; }    // The total time the player has been alive
    public float DistanceTravelled { get; private set; }    // The total distance travelled by the player

    private Player _player;             // The player script
    private bool _initialized;          // Whether the values for time and distance have been initialized
    private float _previousTime;        // The previous time that was recorded
    private Vector3 _previousPosition;  // The previous position that was recorded

    /// <summary>
    /// Initializes the PlayerStats.
    /// </summary>
    void Awake()
    {
        _player = GetComponent<Player>();
        _initialized = false;
    }

    /// <summary>
    /// Initializes the time and position values if they haven't already and updates the total player's time alive and distance travelled.
    /// </summary>
    void Update()
    {
        if (LevelManager.GameOver) return;

        if (_player.Crashed || _player.State == Player.PlayerState.Idle) return;

        if (!_initialized && _player.State == Player.PlayerState.Active)
        {
            _previousTime = Time.time;
            _previousPosition = transform.position;
            _initialized = true;
            return;
        }

        TimeAlive += Time.time - _previousTime;
        DistanceTravelled += Vector3.Distance(transform.position, _previousPosition);
        _previousTime = Time.time;
        _previousPosition = transform.position;
    }

    /// <summary>
    /// Adds a win to the players win count.
    /// </summary>
    public void AddWin()
    {
        if (LevelManager.GameOver) return;
        ++Wins;
    }

    /// <summary>
    /// Adds a death to the players death count.
    /// </summary>
    public void AddDeath()
    {
        if (LevelManager.GameOver) return;
        ++Deaths;
    }

    /// <summary>
    /// Adds to the amount of crashes of opponents that the player has caused.
    /// </summary>
    public void AddTakedown()
    {
        if (LevelManager.GameOver) return;
        ++Takedowns;
    }

    /// <summary>
    /// Adds to the amount of pickups the player has used.
    /// </summary>
    public void CollectedPickup()
    {
        if (LevelManager.GameOver) return;
        ++PickupsUsed;
    }

    /// <summary>
    /// Adds to the amount of coffee the player has collected.
    /// </summary>
    public void CollectedCoffee()
    {
        if (LevelManager.GameOver) return;
        ++CoffeeCupsCollected;
    }

    /// <summary>
    /// Adds to the amount of obstacles the player has destroyed.
    /// </summary>
    public void DestroyedObstacle()
    {
        if (LevelManager.GameOver) return;
        ++ObstaclesDestroyed;
    }

    /// <summary>
    /// Adds an amount of damage that the player has taken.
    /// </summary>
    /// <param name="amount">The amount of damage that the player has taken.</param>
    public void TakenDamage(int amount)
    {
        if (LevelManager.GameOver) return;
        DamageTaken += amount;
    }

    /// <summary>
    /// Adds an amount of damage that the player has inflicted.
    /// </summary>
    /// <param name="amount">The amount of damage the player has inflicted.</param>
    public void InflictedDamage(int amount)
    {
        if (LevelManager.GameOver) return;
        DamageDone += amount;
    }

    /// <summary>
    /// Adds to the amount of times the player has been killed by a car.
    /// </summary>
    public void KilledByCar()
    {
        if (LevelManager.GameOver) return;
        ++CarDeaths;
    }
}
