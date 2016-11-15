using System;
using UnityEngine;
using System.Collections.Generic;

/// <summary>
/// Class MenuList.
/// 
/// Has a list of MenuItems and provides a way to scroll through them using a controller.
/// </summary>
public class MenuList : MonoBehaviour
{
    [SerializeField]
    private List<MenuItemWrapper> _items;           // The items in the list
    [SerializeField]
    private ControllerMap.Button _confirmButton;    // The confirm button to react to
    [SerializeField]
    private float _selectionDelay = 0.8f;           // The selection delay time
    [SerializeField]
    private AudioSource _source;                    // The audio source to play when the confirm button is pressed.

    private int _selectedItem;                      // The selected item in the list
    private Timer _delayTimer;                      // The delay between selections
    public int ControllerId { get; set; }           // The ID of the controller to use

    /// <summary>
    /// Initialises the MenuList.
    /// </summary>
    void Awake()
    {
        _selectedItem = 0;
        _delayTimer = new Timer(_selectionDelay, false);

        if (_items.Count == 0) Debug.LogError("A MenuList needs at least 1 item in the list.");

        _items[_selectedItem].Item.Select();
    }

    /// <summary>
    /// Waits for controller input and either scrolls thought the items or opens the next screen associated with the item.
    /// </summary>
    void Update()
    {
        // If the controller ID is zero, then use all controllers for the menu list.
        if (ControllerId == 0)
        {
            if (ControllerManager.Controllers.HasPressed(_confirmButton) != -1) ConfirmButtonPressed();

            if (!_delayTimer.TimerFinished) return;

            if (ControllerManager.Controllers.AnyYAxis(-0.95f)) SelectPreviousItem();
            if (ControllerManager.Controllers.AnyYAxis(0.95f)) SelectNextItem();
        }
        // Otherwise use the controller at the controller ID.
        else
        {
            if (ControllerManager.Controllers.GetController(ControllerId).GetButtonDown(_confirmButton)) ConfirmButtonPressed();

            if (!_delayTimer.TimerFinished) return;

            if (ControllerManager.Controllers.GetController(ControllerId).YAxis < -0.95f) SelectPreviousItem();
            if (ControllerManager.Controllers.GetController(ControllerId).YAxis > 0.95f) SelectNextItem();
        }
    }

    /// <summary>
    /// Selects the next item in the list.
    /// </summary>
    private void SelectNextItem()
    {
        // Deselect the current item
        _items[_selectedItem].Item.Deselect();

        // Select the next item
        ++_selectedItem;
        if (_selectedItem == _items.Count) _selectedItem = 0;

        _items[_selectedItem].Item.Select();

        // Restart the delay timer
        _delayTimer.Reset();
    }

    /// <summary>
    /// Selects the previous item in the list.
    /// </summary>
    private void SelectPreviousItem()
    {
        // Deselect the current item
        _items[_selectedItem].Item.Deselect();

        // Select the next item
        --_selectedItem;
        if (_selectedItem == -1) _selectedItem = _items.Count - 1;

        _items[_selectedItem].Item.Select();

        // Restart the delay timer
        _delayTimer.Reset();
    }

    /// <summary>
    ///  Opens the next window associated with the currently selected menu item.
    /// </summary>
    private void ConfirmButtonPressed()
    {
        if (_items[_selectedItem].NextScreen) _items[_selectedItem].NextScreen.SetActive(true);
        gameObject.SetActive(false);

        if (_source && !_source.isPlaying) _source.Play();
    }
}

/// <summary>
/// Class MenuItemWrapper.
/// 
/// Binds a MenuItem to a GameObject that will be activated when the MenuItem is selected.
/// </summary>
[Serializable]
public class MenuItemWrapper
{
    public MenuItem Item;
    public GameObject NextScreen;
}
