using UnityEngine;

/// <summary>
/// Class CameraMovementEffects
/// 
/// Manages the movement performed on the camera to add effects to the game. 
/// Eg. Shaking or bouncing the camera when a player is bashed by another player.
/// Zooming and Rotation also handled here.
/// </summary>
[RequireComponent(typeof(Camera))]
public class CameraMovementEffects : MonoBehaviour
{
    [SerializeField]
    private bool _useFOVZoom = true;            // Determines whether FOV zooming is enabled or not
    [SerializeField]
    private bool _useRotation = true;           // Determines whether rotation on left/right movement is enabled or not
    [SerializeField]
    private float _bounceStrength = 0.9f;       // The amount to multiply the bounce direction by
    [SerializeField]
    private float _bounceSpeed = 18f;           // Initial speed of the bounce
    [SerializeField]
    private float _zoomDampTime = 0.9f;         // Time to shift camera
    [SerializeField]
    private float _minScreenFOV = 40f;          // The smallest size the camera can be (FOV)
    [SerializeField]
    private float _maxScreenFOV = 70f;          // The largest size the camera can be (FOV)
    [SerializeField]
    private float _fovMultiplier = 5.5f;        // The amount to multiply the new FOV size by, as the distances between the players is fairly small
    [SerializeField]
    private float _slopeRotationSpeed = 0.75f;  // The speed of the up and down rotation (x-axis) when going from flat track to slope and vice versa

    private float _bounceSpeedConst;            // The constant original bounce speed
    private float _zoomSpeed;                   // The zoom speed
    private static float _shakeTime;            // The time to shake the camera
    private static float _shakeStrength;        // The force of the shake
    private static int _bounceState;            // The state for the bounce. 0- not bouncing, 1- bouncing in, 2- bouncing out
    private float _decreaseTime = 1.0f;         // The time to reduce the shakeTime by each update
    private Vector3 _originalPosition;          // The original position to move back to after the bounce
    private Vector3 _moveToPosition;            // The current position to move to for the bounce to occur
    private Vector3 _moveToPositionConst;       // The fixed position to move to for the current bounce
    private Vector3 _offsetPosition;            // The amount of offset for the position movement
    private Camera _camera;                     // The camera object within the scene

    private Quaternion _flatRotation;           // The rotation on flat surfaces
    private Quaternion _slopeRotation;           // The rotation on sloped surfaces

    /// <summary>
    /// Sets original position and fov
    /// </summary>
    void Start()
    {
        _originalPosition = transform.localPosition;
        _offsetPosition = Vector3.zero;
        _camera = Camera.main;
        _bounceSpeedConst = _bounceSpeed;
        _flatRotation = Quaternion.Euler(340f, 0f, 0f);
        _slopeRotation = Quaternion.Euler(2.5f, 0f, 0f);
    }

    /// <summary>
    /// Disables bouncing and shaking on script disable
    /// </summary>
    void OnDisable()
    {
        _bounceState = 0;
        _shakeTime = 0;
    }

    /// <summary>
    /// Updates the cameras position/rotation/FOV to create the effects desired
    /// </summary>
    void FixedUpdate()
    {
        // Camera zoom and rotation
        if (_useFOVZoom) Zoom();
        if (_useRotation) Rotate();

        // Camera Bounce Effect
        if (_bounceState > 0)
        {
            Bounce();
        }
        else
        {
            _moveToPosition = Vector3.zero;
        }

        // Camera Shake Effect
        if (_shakeTime > 0)
        {
            transform.localPosition = transform.localPosition + Random.insideUnitSphere * _shakeStrength;
            _shakeTime -= Time.deltaTime * _decreaseTime;
        }
    }

    /// <summary>
    /// Zoom the camera in and out as required, to see all players.
    /// </summary>
    private void Zoom()
    {
        // TODO: The zoom effect is currently randomly killing players. This bug isn't acceptable so the zoom functionality 
        // will be disbaled until the bug is fixed.
        return;

        float requiredSize = FindRequiredSize();
        _camera.fieldOfView = Mathf.SmoothDamp(_camera.fieldOfView, requiredSize, ref _zoomSpeed, _zoomDampTime);
    }

    /// <summary>
    /// Checks the current tracks angle and rotates the camera as required
    /// The normal returned on slopes is (0.0, 1.0, 0.2) and flats is (0.0, 1.0, 0.0)
    /// Start position is 28 units ahead of actual camera as that is when it visually seems to go over the 'edge'
    /// </summary>
    private void Rotate()
    {
        // TODO: The rotate functionality is sling shotting the players forward (and sometimes killing them) when the camera moves from 
        // chunks on different rotations. This bug is game breaking so the functionality will be disabled until it can be fixed.
        return;

        RaycastHit hit;
        Vector3 startPosition = transform.position;
        startPosition.z = startPosition.z + 28f;
        if (Physics.Raycast(startPosition, -Vector3.up, out hit, Mathf.Infinity, 1 << PhysicsLayer.Track))
        {
            transform.localRotation = Quaternion.Lerp(transform.localRotation, hit.normal.z > 0.1f ? _slopeRotation : _flatRotation, Time.deltaTime * _slopeRotationSpeed);
        }
    }

    /// <summary>
    /// Handles the bouncing of the camera, bouncing in and out after a collision
    /// </summary>
    private void Bounce()
    {
        // Set new random position and FOV
        if (_moveToPosition == Vector3.zero)
        {
            float x = Random.Range(-1f, 1f);
            _offsetPosition = new Vector3(x, Random.Range(-Mathf.Abs(x) * 0.15f, Mathf.Abs(x) * 0.15f), 0);
            _moveToPositionConst = _originalPosition + _offsetPosition.normalized * _bounceStrength;
            _moveToPositionConst.z = _originalPosition.z;
            _moveToPosition = _moveToPositionConst;
            _bounceSpeed = _bounceSpeedConst;
        }

        // Move the camera to the new position
        transform.localPosition = Vector3.Lerp(transform.localPosition, _moveToPosition, Time.deltaTime * _bounceSpeed);

        // If the camera is at the move to position, set state and position to move back to original values
        if (Vector3.Distance(transform.localPosition, _moveToPosition) < 0.2f)
        {
            _bounceState -= 1;
            switch (_bounceState)
            {
                case 6:
                    _moveToPosition = _moveToPositionConst * -0.9f;
                    _bounceSpeed -= 0.5f;
                    break;
                case 5:
                    _moveToPosition = _moveToPositionConst * 0.8f;
                    _bounceSpeed -= 0.25f;
                    break;
                case 4:
                    _moveToPosition = _moveToPositionConst * -0.65f;
                    _bounceSpeed -= 0.10f;
                    break;
                case 3:
                    _moveToPosition = _moveToPositionConst * 0.3f;
                    break;
                case 2:
                    _moveToPosition = _moveToPositionConst * -0.2f;
                    break;
                case 1:
                    _moveToPosition = _originalPosition;
                    break;
                case 0:
                    transform.localPosition = _originalPosition;
                    break;
            }
            _moveToPosition.z = _originalPosition.z;
        }
    }

    /// <summary>
    /// Find the required Field of View size for the zoom, as it must contain all players
    /// </summary>
    /// <returns>The new Field of View size as a float</returns>
    private float FindRequiredSize()
    {
        Vector3 desiredPosition = transform.InverseTransformPoint(GeometryUtils.GetAveragePlayerPosition(LevelManager.Players));
        float fovSize = 0f;

        foreach (Player player in LevelManager.Players)
        {
            if (player.Crashed) continue;
            Vector3 targetPosition = transform.InverseTransformPoint(player.CharacterPosition);
            Vector3 desiredPositionToTarget = targetPosition - desiredPosition;
            fovSize = Mathf.Max(fovSize, Mathf.Abs(desiredPositionToTarget.y));
            fovSize = Mathf.Max(fovSize, Mathf.Abs(desiredPositionToTarget.x) / _camera.aspect);
        }
        fovSize = fovSize * _fovMultiplier;
        float dist = Vector3.Distance(transform.localPosition, transform.InverseTransformPoint(GeometryUtils.GetAveragePlayerPosition(LevelManager.Players))) * 0.4f;
        if (dist < 60) dist = 0;
        fovSize -= dist;
        fovSize = Mathf.Max(fovSize, _minScreenFOV);
        fovSize = Mathf.Min(fovSize, _maxScreenFOV);
        return fovSize;
    }

    /// <summary>
    /// Starts the camera bounce 
    /// </summary>
    public static void StartCameraBounce()
    {
        if (_bounceState == 0) _bounceState = 7;
    }

    /// <summary>
    /// Starts the camera shaking
    /// </summary>
    public static void StartCameraShake()
    {
        _shakeTime = 0.4f;
        _shakeStrength = 0.6f;
    }
}