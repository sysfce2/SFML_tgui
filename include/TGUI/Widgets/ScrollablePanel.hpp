/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus' Graphical User Interface
// Copyright (C) 2012-2017 Bruno Van de Velde (vdv_b@tgui.eu)
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


#ifndef TGUI_SCROLLABLE_PANEL_HPP
#define TGUI_SCROLLABLE_PANEL_HPP

#include <TGUI/Widgets/Panel.hpp>
#include <TGUI/Widgets/Scrollbar.hpp>
#include <TGUI/Renderers/ScrollablePanelRenderer.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Group of widgets that has a background color and optional borders.
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class TGUI_API ScrollablePanel : public Panel
    {
    public:

        typedef std::shared_ptr<ScrollablePanel> Ptr; ///< Shared widget pointer
        typedef std::shared_ptr<const ScrollablePanel> ConstPtr; ///< Shared constant widget pointer


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Default constructor
        ///
        /// @param size        Size of the panel
        /// @param contentSize Size of the content area for which the scrollbars will appear if larger than the size
        ///
        /// When contentSize is set to (0,0), the content size is determined by the child widgets of the panel.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        ScrollablePanel(const Layout2d& size = {"100%", "100%"}, sf::Vector2f contentSize = {0, 0});


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Creates a new scrollable panel widget
        ///
        /// @param size  Size of the panel
        /// @param contentSize Size of the content area for which the scrollbars will appear if larger than the size
        ///
        /// When contentSize is set to (0,0), the content size is determined by the child widgets of the panel.
        ///
        /// @return The new scrollable panel
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        static ScrollablePanel::Ptr create(Layout2d size = {"100%", "100%"}, sf::Vector2f contentSize = {0, 0});


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Makes a copy of another scrollbable panel
        ///
        /// @param panel  The other scrollbable panel
        ///
        /// @return The new scrollbable panel
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        static ScrollablePanel::Ptr copy(ScrollablePanel::ConstPtr panel);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the renderer, which gives access to functions that determine how the widget is displayed
        ///
        /// @return Temporary pointer to the renderer
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        ScrollablePanelRenderer* getRenderer() const
        {
            return aurora::downcast<ScrollablePanelRenderer*>(m_renderer.get());
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the size of the panel
        ///
        /// @param size  The new size of the panel
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setSize(const Layout2d& size) override;
        using Widget::setSize;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Adds a widget at the end of the layout
        ///
        /// @param widget      Pointer to the widget you would like to add
        /// @param widgetName  An identifier to access to the widget later
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void add(const tgui::Widget::Ptr& widget, const sf::String& widgetName = "") override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Removes a single widget that was added to the container
        ///
        /// @param widget  Pointer to the widget to remove
        ///
        /// @return True when widget is removed, false when widget was not found
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool remove(const Widget::Ptr& widget) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Removes all widgets that were added to the container
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void removeAllWidgets() override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Channges the size available for child widgets
        ///
        /// @param size  Inner size of the container
        ///
        /// If the content size is larger than the size of the panel then scrollbars will be displayed.
        ///
        /// When the content size is (0,0), which is the default, then the content size is determined by the child widgets.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setContentSize(sf::Vector2f size);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the size available for child widgets
        ///
        /// @return Inner size of the container
        ///
        /// If the content size is larger than the size of the panel then scrollbars will be displayed
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        sf::Vector2f getContentSize() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the amount of pixels the child widgets have been shifted to be displayed by the scrollable panel
        ///
        /// @return Value of the scrollbars
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        sf::Vector2f getContentOffset() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void leftMousePressed(sf::Vector2f pos) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void leftMouseReleased(sf::Vector2f pos) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void mouseMoved(sf::Vector2f pos) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void mouseWheelScrolled(float delta, sf::Vector2f pos) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void mouseNoLongerOnWidget() override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void mouseNoLongerDown() override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Draw the widget to a render target
        ///
        /// @param target Render target to draw to
        /// @param states Current render states
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    protected:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Function called when one of the properties of the renderer is changed
        ///
        /// @param property  Lowercase name of the property that was changed
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void rendererChanged(const std::string& property) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Makes a copy of the widget
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Widget::Ptr clone() const override
        {
            return std::make_shared<ScrollablePanel>(*this);
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    private:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Update the position, size and value of the scrollbars
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void updateScrollbars();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Find out where the
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void recalculateMostBottomRightPosition();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    private:

        sf::Vector2f         m_contentSize;
        sf::Vector2f         m_mostBottomRightPosition;
        ScrollbarChildWidget m_verticalScrollbar;
        ScrollbarChildWidget m_horizontalScrollbar;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    };

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // TGUI_SCROLLABLE_PANEL_HPP
