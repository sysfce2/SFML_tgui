/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus' Graphical User Interface
// Copyright (C) 2012-2020 Bruno Van de Velde (vdv_b@tgui.eu)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef TGUI_BACKEND_GUI_SFML_HPP
#define TGUI_BACKEND_GUI_SFML_HPP


#include <TGUI/GuiBase.hpp>

#if TGUI_BUILD_WITH_SFML
    #include <SFML/Window/Event.hpp>
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    class BackendRenderTargetSFML;

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Gui class for the SFML backend
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class TGUI_API GuiSFML : public GuiBase
    {
    public:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Default constructor
        ///
        /// @warning If you use this constructor then you will still have to call setTarget before using the gui.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        GuiSFML();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Constructs the gui and set the target on which the gui should be drawn
        ///
        /// @param target  The render target (typically sf::RenderWindow) that will be used by the gui
        ///
        /// If you use this constructor then you will no longer have to call setTarget yourself.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        GuiSFML(sf::RenderTarget& target);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Sets the target on which the gui should be drawn
        ///
        /// @param target  The render target (typically sf::RenderWindow) that will be used by the gui
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setTarget(sf::RenderTarget& target);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the render target on which the gui is being drawn
        ///
        /// @return The sfml render target that is used by the gui
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        sf::RenderTarget* getTarget() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Passes the event to the widgets
        ///
        /// @param event  The event that was polled from the window
        ///
        /// @return Has the event been consumed?
        ///         When this function returns false, then the event was ignored by all widgets.
        ///
        /// You should call this function in your event loop.
        /// @code
        /// sf::Event event;
        /// while (window.pollEvent(event) {
        ///     gui.handleEvent(event);
        /// }
        /// @endcode
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool handleEvent(sf::Event event);
        using GuiBase::handleEvent;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Draws all the widgets that were added to the gui
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void draw() override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Give the gui control over the main loop
        ///
        /// This function is only intended in cases where your program only needs to respond to gui events.
        /// For multimedia applications, games, or other programs where you want a high framerate or do a lot of processing
        /// in the main loop, you should use your own main loop.
        ///
        /// You can consider this function to execute something similar (but not identical) to the following code:
        /// @code
        /// while (window.isOpen())
        /// {
        ///     while (window.waitEvent(event))
        ///     {
        ///         gui.handleEvent(event);
        ///         if (event.type == sf::Event::Closed)
        ///             window.close();
        ///     }
        ///
        ///     window.clear({240, 240, 240});
        ///     gui.draw();
        ///     window.display();
        /// }
        /// @endcode
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void mainLoop();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    protected:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Function that is called when constructing the Gui
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void init() override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Updates the view and changes the size of the root container when needed
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void updateContainerSize() override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    protected:

        std::shared_ptr<BackendRenderTargetSFML> m_renderTarget = nullptr;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    };
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // TGUI_BACKEND_GUI_SFML_HPP