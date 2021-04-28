#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

#include <External/glm/glm.hpp>
#include "Core/ENGINEDEFINITIONS.hpp"
#include "Core/Game.hpp"
#include "Graphics/MenuComponent.hpp"
#include "Graphics/Button.hpp"

namespace Sonar
{
    class ButtonGroup : public MenuComponent
    {
    public:
        /**
        * \brief The orientation of the buttons in the button group
        */
        enum ORIENTATION
        {
            VERTICAL = 0,
            HORIZONTAL
        };

        /**
        * \brief Class constructor
        *
        * \param data Game data object
        */
        ButtonGroup( GameDataRef data );

        /**
        * \brief Class destructor
        */
        ~ButtonGroup( );
        
        /**
        * \brief Draw the classes objects
        */
        void Draw( );

        /**
        * \brief Update the classes objects
        *
        * \param dt Delta time (difference between frames)
        */
        void Update( const float &dt );

        /**
        * \brief Poll the input from the Joystick, Keyboard and Mouse
        *
        * \param dt Delta time (difference between frames)
        * \param event Event to poll
        */
        void PollInput( const float &dt, const Event &event );

        /**
        * \brief Add a button (orientation and gap must be set before adding any buttons or default values will be used)
        *
		* \param button button to add
		* \param overrideStyle Should the button's style be overriden using the group's style
		* \param resetWidthForAllButtons Should the buttons have the same width
        */
        void AddButton( Button *button, const bool &overrideStyle = true, const bool &resetWidthForAllButtons = true, const bool &autoOrient = true );

        /**
        * \brief Remove button
        *
        * \param button Button to remove
        */
        void RemoveButton( Button *button );

        /**
        * \brief Remove button at a specific index
        *
        * \param index Index of button to remove
        */
        void RemoveButton( const int &index );

        /**
        * \brief Remove the first button
        */
        void RemoveFirstButton( );

        /**
        * \brief Remove the last button from the menu
        */
        void RemoveLastButton( );

        /**
        * \brief Get the number of buttons
        *
        * \return Output returns the size of the button vector
        */
        unsigned int GetSize( ) const;

        /**
        * \brief Set the components theme
        *
        * \param theme Theme to set
        */
        void SetTheme( const MenuComponent::Theme &theme );

        /**
        * \brief Move up 1 in the menu
        *
		* \param cycleDown If at the top, go to the bottom item
		* \param moveDown Move amount for the button selection
        */
		void MoveUp( const bool &cycleDown = true, const unsigned int &moveAmount = 1 );

        /**
        * \brief Move down 1 in the menu
        *
        * \param cycleUp If at the bottom, go to the top item
        * \param moveUp Move amount for the button selection
        */
        void MoveDown( const bool &cycleUp = true, const unsigned int &moveAmount = 1 );

        /**
        * \brief Jump to a particular button
        *
        * \param index Button index to jump to (starts at 0)
        */
        void JumpToIndex( const unsigned int &index );

        /**
        * \brief Get the index of the current selected button
        *
        * \return Output returns the current selected index
        */
        unsigned int GetCurrentIndex( ) const;

        /**
        * \brief Enable/disable the keyboard state for the button group
        *
        * \param variableName Variable description
        */
        void SetKeyboadEnabled( const bool &isEnabled );

        /**
        * \brief Enable the keyboard state for the button group
        */
        void EnableKeyboard( );

        /**
        * \brief Disable the keyboard state for the button group
        */
        void DisableKeyboard( );

        /**
        * \brief Toggle the keyboard state for the button group
        */
        void ToggleKeyboard( );

        /**
        * \brief Is the keyboard enabled for the button group
        *
        * \return Output returns the keyboard enabled state
        */
        const bool &IsKeyboardEnabled( ) const;

        /**
        * \brief Set the button groups minimum width
        *
        * \param width Variable description
        */
        void SetMinimumWidth( const float &width );

        /**
        * \brief Get the button groups minimum width
        *
        * \return Output returns the minimum width of the button group
        */
        const float &GetMinimumWidth( ) const;

        /**
        * \brief Set the orientation of the buttons in the button group (NEEDS TO BE SET BEFORE ADDING ANY BUTTONS)
        *
        * \param orientation Orientation of the buttons
        */
        void SetOrientation( const ORIENTATION &orientation );

        /**
        * \brief Get the orientation of the buttons
        *
        * \return Output returns the orientation
        */
        const ORIENTATION &GetOrientation( ) const;

        /**
        * \brief Set the gap between the buttons in the button group (NEEDS TO BE SET BEFORE ADDING ANY BUTTONS)
        *
        * \param gap Gap between the buttons
        */
        void SetGap( const float &gap );

        /**
        * \brief Get the gap between the buttons
        *
        * \return Output returns the gap between the buttons
        */
        const float &GetGap( ) const;

        /**
        * \brief Set x and y position
        *
        * \param position X and Y position
        */
        void SetPosition( const glm::vec2 &position );

        /**
        * \brief Set x and y position
        *
        * \param x X position
        * \param y Y position
        */
        void SetPosition( const float &x, const float &y );

        /**
        * \brief Set x position
        *
        * \param x X position
        */
        void SetPositionX( const float &x );

        /**
        * \brief Set y position
        *
        * \param y Y position
        */
        void SetPositionY( const float &y );

        /**
        * \brief Get the x position
        *
        * \return Output returns the x position
        */
        float GetPositionX( ) const;

        /**
        * \brief Get the y position
        *
        * \return Output returns the y position
        */
        float GetPositionY( ) const;

        /**
        * \brief Get the position vector
        *
        * \return Output returns the position vector
        */
        glm::vec2 GetPosition( ) const;

    private:
        /**
        * \brief Update the buttons to show which one is selected
        */
        void UpdateButtons( );

        /**
        * \brief Game data object
        */
        GameDataRef _data;

        /**
        * \brief Vector of buttons
        */
        std::vector<Button *> _buttons;

        /**
        * \brief Style of the menu
        */
        MenuComponent::Theme _theme;

        /**
        * \brief Current selected button
        */
        int _currentIndex;

        /**
        * \brief Is the keyboard enabled
        */
        bool _isKeyboardEnabled;

        /**
        * \brief Is the current button clicked
        */
        bool _isCurrentButtonClicked;

        /**
        * \brief Has the button group's been updated/loaded initially
        */
        bool _hasButtonGroupLoaded;

        /**
        * \brief Current mouse state
        */
        Button::MOUSE_STATE _currentMouseState;

        /**
        * \brief Minimum button width
        */
        float _minimumWidth;

        /**
        * \brief Orientation of the buttons inside the button group
        */
        ORIENTATION _orientation;

        /**
        * \brief Gap between the buttons when using auto position
        */
        float _gap;

        /**
        * \brief Position of the button group (aka the position of the first button)
        */
        glm::vec2 _position;

    };
}
