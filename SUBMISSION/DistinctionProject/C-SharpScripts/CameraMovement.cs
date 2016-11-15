using UnityEngine;

/// <summary>
/// Class CameraMovement
/// 
/// Moves the camera at a constant velocity in the Z direction.
/// </summary>
public class CameraMovement : MonoBehaviour
{
    [SerializeField]
    private float _velocity = 20f;          // The velocity in the z direction the camera travels in.
    [SerializeField]
    private float _gameOverVelocity = 5f;   // The cameras velocity when the game is over
    [SerializeField]
    private float _positionAboveTrack = 7;  // The position of the camera above the track.
    [SerializeField]
    private float _xRotation = 30;          // The x-rotation of the camera.
    [SerializeField]
    private Track _startTrackObject;        // The Track object at the start of the level.

    [SerializeField]
    private float _bottomZBounds = 0.2f;    // The bottom of the z bounds.
    [SerializeField]
    private float _topZBounds = 0.55f;      // The top of the z bounds.

    [SerializeField]
    private float _yRotationOffset = 0.05f; // The amount to rotate the camera in the Y axis while moving left/right
    [SerializeField]
    private float _zRotationOffset = 0.4f;  // The amount to rotate the camera in the Z axis while moving left/right
    [SerializeField]
    private float _rotationSpeed = 4f;      // The speed at which the camera rotates when moving left/right

    [SerializeField]
    private float _xPositionRange = 27f;    // The range that the camera can move to either side (ie. 27 units left and 27 units right)

    private Quaternion _rightRotation;      // The rotation to lerp to when moving right
    private Quaternion _leftRotation;       // The rotation to lerp to when moving left
    private Quaternion _origRotation;       // The original rotation

    private static float _topBounds;        // A static variable for the top bounds.
    private static float _bottomBounds;     // A static variable for the bottom bounds.
    private float _xPosition;               // The x-position of the camera.
    private bool _movementActive;           // If the cameras movement is active.

    public static float CameraVelocity { get; private set; }    // A static variable for the camera velocity

    /// <summary>
    /// Sets the cameras rotation.
    /// </summary>
    void Start()
    {
        _movementActive = false;

        transform.rotation = Quaternion.Euler(_xRotation, 0, 0);

        CameraVelocity = _velocity;
        _topBounds = _topZBounds;
        _bottomBounds = _bottomZBounds;

        // Position the camera in the x-axis.
        _xPosition = _startTrackObject ? _startTrackObject.StartPosition.x : transform.position.x;

        // Set the camera's initial position
        Vector3 newPosition = GeometryUtils.PositionAboveTrack(transform.position, _positionAboveTrack);
        newPosition.x = _xPosition;
        transform.position = newPosition;

        Vector3 startRotation = transform.rotation.eulerAngles;
        _rightRotation = Quaternion.Euler(startRotation.x, startRotation.y - _yRotationOffset, startRotation.z - _zRotationOffset);
        _leftRotation = Quaternion.Euler(startRotation.x, startRotation.y + _yRotationOffset, startRotation.z + _zRotationOffset);
        _origRotation = transform.rotation;

        if (!_startTrackObject) Debug.Log("No Track object is given to the CameraMovement script. The Track object is used to position the camera in the x-axis.");
    }

    /// <summary>
    /// Updates the player's on screen status.
    /// </summary>
    void Update()
    {
        if (!_movementActive || LevelManager.GameOver) return;

        foreach (Player player in LevelManager.Players) player.InsideCamera = IsPlayerOnScreen(player);
    }

    /// <summary>
    /// Updates the cameras position.
    /// </summary>
    void FixedUpdate()
    {
        if (!_movementActive) return;

        // Slow the camera's velocity if the game is over
        if (LevelManager.GameOver && _velocity > _gameOverVelocity)
        {
            _velocity = Mathf.Lerp(_velocity, 0, Time.deltaTime * 0.1f);
        }

        // Downhill and left to right movement
        Vector3 newPosition = GeometryUtils.PositionAboveTrack(transform.position, _positionAboveTrack);
        float newXPosition = GeometryUtils.GetAveragePlayerPosition(LevelManager.Players).x;
        if (newXPosition > _xPositionRange) newPosition.x = _xPositionRange;
        if (newXPosition < -_xPositionRange) newPosition.x = -_xPositionRange;
        newPosition.x = Mathf.Lerp(newPosition.x, newXPosition, Time.deltaTime * 5f);
        newPosition.z = _velocity * Time.deltaTime + newPosition.z;

        // Rotation for left to right movement
        Quaternion newRotation = transform.rotation;
        if (newPosition.x > transform.position.x + 0.04f)
        {
            newRotation = Quaternion.Lerp(newRotation, _rightRotation, Time.deltaTime * _rotationSpeed);
        }
        else if (newPosition.x < transform.position.x - 0.04f)
        {
            newRotation = Quaternion.Lerp(newRotation, _leftRotation, Time.deltaTime * _rotationSpeed);
        }
        else
        {
            newRotation = Quaternion.Lerp(newRotation, _origRotation, Time.deltaTime * _rotationSpeed);
        }
        transform.rotation = newRotation;
        transform.position = newPosition;
    }

    /// <summary>
    /// Starts the camera's movement.
    /// </summary>
    public void StartCamera()
    {
        _movementActive = true;
    }

    /// <summary>
    /// Checks if a player is on screen.
    /// </summary>
    /// <param name="player">The player to check.</param>
    /// <returns>True if the player is on the screen, false if not.</returns>
    public static bool IsPlayerOnScreen(Player player)
    {
        if (!player.gameObject.activeSelf) return false;
        Vector3 playerScreenPosition = Camera.main.WorldToScreenPoint(player.CharacterPosition);
        float xRatio = playerScreenPosition.x / Camera.main.pixelWidth;
        float yRatio = playerScreenPosition.y / Camera.main.pixelHeight;
        float zRatio = playerScreenPosition.z / Camera.main.pixelWidth;

        return yRatio > 0 && yRatio < 1 && xRatio > 0 && xRatio < 1 && zRatio > 0;
    }

    /// <summary>
    /// Gets the top-middle of the camera bounds as a Vector3.
    /// </summary>
    public static Vector3 TopCameraBoundsPosition
    {
        get { return GetBoundsPosition(_topBounds); }
    }

    /// <summary>
    /// Getd the middle of the camera bounds as a Vector3.
    /// </summary>
    public static Vector3 MiddleCameraBoundsPosition
    {
        get { return GetBoundsPosition(_topBounds - _bottomBounds); }
    }

    /// <summary>
    /// Getd the bottom-middle of the camera bounds as a Vector3.
    /// </summary>
    public static Vector3 BottomCameraBoundsPosition
    {
        get { return GetBoundsPosition(_bottomBounds); }
    }

    /// <summary>
    /// Gets the z value for the top of the camera bounds.
    /// </summary>
    public static float TopCameraBounds
    {
        get { return TopCameraBoundsPosition.z; }
    }

    /// <summary>
    /// Gets the z value for the bottom of the camera bounds.
    /// </summary>
    public static float BottomCameraBounds
    {
        get { return BottomCameraBoundsPosition.z; }
    }

    /// <summary>
    /// Gets a camera bounds poisiton from a y-position on the screen.
    /// </summary>
    /// <param name="yPositionOnCamera">The y screen position.</param>
    /// <returns>The camera bounds position.</returns>
    private static Vector3 GetBoundsPosition(float yPositionOnCamera)
    {
        bool result;
        return GeometryUtils.CalculatePositionOnCamera(new Vector3(Camera.main.pixelWidth / 2, Camera.main.pixelHeight * yPositionOnCamera, 10), out result);
    }

    /// <summary>
    /// Draws gizmos for the bounds of the camera.
    /// </summary>
    void OnDrawGizmos()
    {
        bool result;
        var bottomYPos = Camera.main.pixelHeight * _bottomZBounds;
        var topYPos = Camera.main.pixelHeight * _topZBounds;

        var bottomLeft = GeometryUtils.CalculatePositionOnCamera(new Vector3(0, bottomYPos, 10), out result);
        var bottomRight = GeometryUtils.CalculatePositionOnCamera(new Vector3(Camera.main.pixelWidth, bottomYPos, 10), out result);
        var topMiddle = GeometryUtils.CalculatePositionOnCamera(new Vector3(Camera.main.pixelWidth / 2, topYPos, 10), out result);
        var topLeft = new Vector3(bottomLeft.x, topMiddle.y, topMiddle.z);
        var topRight = new Vector3(bottomRight.x, topMiddle.y, topMiddle.z);

        // Draw the bounds
        Gizmos.color = Color.green;
        Gizmos.DrawLine(topRight, topLeft);
        Gizmos.DrawLine(topLeft, bottomLeft);
        Gizmos.DrawLine(bottomLeft, bottomRight);
        Gizmos.DrawLine(bottomRight, topRight);
        //Draw the left and right most positions the camera can have. This is only valid while the camera is centred as during runtime these dots move with the camera.
        Gizmos.DrawSphere(transform.position + Vector3.left * _xPositionRange, 0.5f);
        Gizmos.DrawSphere(transform.position + Vector3.right * _xPositionRange, 0.5f);
    }
}
