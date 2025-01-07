/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus' Graphical User Interface
// Copyright (C) 2012-2025 Bruno Van de Velde (vdv_b@tgui.eu)
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

#ifndef TGUI_MENU_BAR_HPP
#define TGUI_MENU_BAR_HPP

#include <TGUI/Widgets/MenuWidgetBase.hpp>
#include <TGUI/Renderers/MenuBarRenderer.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TGUI_MODULE_EXPORT namespace tgui
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Menu bar widget
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class TGUI_API MenuBar : public MenuWidgetBase
    {
    public:

        using Ptr = std::shared_ptr<MenuBar>; //!< Shared widget pointer
        using ConstPtr = std::shared_ptr<const MenuBar>; //!< Shared constant widget pointer

        static constexpr const char StaticWidgetType[] = "MenuBar"; //!< Type name of the widget

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /// @brief Constructor
        /// @param typeName     Type of the widget
        /// @param initRenderer Should the renderer be initialized? Should be true unless a derived class initializes it.
        /// @see create
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        MenuBar(const char* typeName = StaticWidgetType, bool initRenderer = true);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Creates a new menu bar widget
        ///
        /// @return The new menu bar
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD static MenuBar::Ptr create();

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Makes a copy of another menu bar
        ///
        /// @param menuBar  The other menu bar
        ///
        /// @return The new menu bar
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD static MenuBar::Ptr copy(const MenuBar::ConstPtr& menuBar);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the renderer, which gives access to functions that determine how the widget is displayed
        /// @return Temporary pointer to the renderer that may be shared with other widgets using the same renderer
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD MenuBarRenderer* getSharedRenderer() override;
        TGUI_NODISCARD const MenuBarRenderer* getSharedRenderer() const override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the renderer, which gives access to functions that determine how the widget is displayed
        /// @return Temporary pointer to the renderer
        /// @warning After calling this function, the widget has its own copy of the renderer and it will no longer be shared.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD MenuBarRenderer* getRenderer() override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Connects a signal handler to the "MenuItemClicked" callback that will only be called when a specific
        ///        menu item was clicked.
        ///
        /// @param menu     Menu containing the menu item
        /// @param menuItem Menu item which should trigger the signal
        /// @param handler  Callback function to call
        /// @param args     Optional extra arguments to pass to the signal handler when the signal is emitted
        ///
        /// @return Unique id of the connection
        ///
        /// The hierarchy does not need to exist yet and the signal will still exist when removing and readding the menu items.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        template <typename Func, typename... Args>
        unsigned int connectMenuItem(const String& menu, const String& menuItem, Func&& handler, const Args&... args)
        {
            return connectMenuItem({menu, menuItem}, std::forward<Func>(handler), args...);
        }

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Connects a signal handler to the "MenuItemClicked" callback that will only be called when a specific
        ///        menu item was clicked.
        ///
        /// @param hierarchy Hierarchy of the menu items, starting with the menu and ending with menu item that should trigger
        ///                  the signal when pressed
        /// @param handler   Callback function to call
        /// @param args      Optional extra arguments to pass to the signal handler when the signal is emitted
        ///
        /// @return Unique id of the connection
        ///
        /// The hierarchy does not need to exist yet and the signal will still exist when removing and readding the menu items.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        template <typename Func, typename... Args>
        unsigned int connectMenuItem(const std::vector<String>& hierarchy, Func&& handler, const Args&... args)
        {
#if defined(__cpp_lib_invoke) && (__cpp_lib_invoke >= 201411L)
            return onMenuItemClick.connect(
                [=](const std::vector<String>& clickedMenuItem)
                {
                    if (clickedMenuItem == hierarchy)
                        std::invoke(handler, args...);
                }
            );
#else
            return onMenuItemClick.connect(
                [f=std::function<void(const Args&...)>(handler),args...,hierarchy](const std::vector<String>& clickedMenuItem)
                {
                    if (clickedMenuItem == hierarchy)
                        f(args...);
                }
            );
#endif
        }

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the size of the menu bar
        ///
        /// @param size  The new size of the menu bar
        ///
        /// By default, the menu bar has the same width as the window and the height is 20 pixels.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setSize(const Layout2d& size) override;
        using Widget::setSize;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Enables or disables the widget
        /// @param enabled  Is the widget enabled?
        ///
        /// The disabled widget will no longer receive events and thus no longer send callbacks.
        /// All widgets are enabled by default.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setEnabled(bool enabled) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Adds a new menu
        ///
        /// @param text  The text written on the menu
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void addMenu(const String& text);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Adds a new menu item to the last added menu
        ///
        /// @param text  The text written on this menu item
        ///
        /// @return True when the item was added, false when the menu bar doesn't contain any menus yet
        ///
        /// @code
        /// menuBar->addMenu("File");
        /// menuBar->addMenuItem("Load");
        /// menuBar->addMenuItem("Save");
        /// menuBar->addMenu("Edit");
        /// menuBar->addMenuItem("Undo");
        /// @endcode
        ///
        /// If the "-" string is given as menu item then a separator will appear instead of an item.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool addMenuItem(const String& text);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Adds a new menu item to an existing menu
        ///
        /// @param menu  The name of the menu to which the menu item will be added
        /// @param text  The text written on this menu item
        ///
        /// @return True when the item was added, false when menu was not found
        ///
        /// @code
        /// menuBar->addMenu("File");
        /// menuBar->addMenu("Edit");
        /// menuBar->addMenuItem("File", "Load");
        /// menuBar->addMenuItem("File", "Save");
        /// menuBar->addMenuItem("Edit", "Undo");
        /// @endcode
        ///
        /// If the "-" string is given as menu item then a separator will appear instead of an item.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool addMenuItem(const String& menu, const String& text);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Adds a new menu item (or sub menu item)
        ///
        /// @param hierarchy     Hierarchy of the menu items, starting with the menu and ending with menu item to be added
        /// @param createParents Should the hierarchy be created if it did not exist yet?
        ///
        /// @return True when the item was added, false when createParents was false and the parents hierarchy does not exist
        ///         or if hierarchy does not contain at least 2 elements.
        ///
        /// @code
        /// menuBar->addMenuItem({"File", "Save"});
        /// menuBar->addMenuItem({"View", "Messages", "Tags", "Important"});
        /// @endcode
        ///
        /// If the "-" string is given as menu item then a separator will appear instead of an item.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool addMenuItem(const std::vector<String>& hierarchy, bool createParents = true);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the text of an existing menu item
        ///
        /// @param hierarchy Hierarchy of the menu items, starting with the menu and ending with menu item that is to be renamed
        /// @param text      The new text written on this menu item
        ///
        /// @return True when the menu item was renamed, false when the menu item was not found
        ///
        /// @code
        /// menuBar->addMenu("File");
        /// menuBar->addMenuItem("Load");
        /// menuBar->changeMenuItem({"File", "Load"}, "Load file");
        /// @endcode
        ///
        /// This function can also be used to rename menus, by passing a hierarchy with only one element.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool changeMenuItem(const std::vector<String>& hierarchy, const String& text);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Removes all menus
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void removeAllMenus();

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Removes a menu
        ///
        /// Any menu items that belong to this menu will be removed as well.
        ///
        /// @param menu  The name of the menu to remove
        ///
        /// @return True when the menu was removed, false when menu was not found
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool removeMenu(const String& menu);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Removes a menu item
        ///
        /// @param menu      The name of the menu in which the menu item is located
        /// @param menuItem  The name of the menu item to remove
        ///
        /// @return True when the item was removed, false when menu or menuItem was not found
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool removeMenuItem(const String& menu, const String& menuItem);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Removes a menu item (or sub menu item)
        ///
        /// @param hierarchy  Hierarchy of the menu item, starting with the menu and ending with menu item to be deleted
        /// @param removeParentsWhenEmpty  Also delete the parent of the deleted menu item if it has no other children
        ///
        /// @return True when the menu item existed and was removed, false when hierarchy was incorrect
        ///
        /// @code
        /// menuBar->removeMenuItem({"File", "Save"});
        /// menuBar->removeMenuItem({"View", "Messages", "Tags", "Important"});
        /// @endcode
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool removeMenuItem(const std::vector<String>& hierarchy, bool removeParentsWhenEmpty = true);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Removes all menu items from a menu
        ///
        /// @param menu      The name of the menu for which all menu items should be removed
        ///
        /// @return True when the menu existed and its children were removed, false when menu was not found
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool removeMenuItems(const String& menu);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Removes a all menu items below a (sub) menu
        ///
        /// @param hierarchy Hierarchy of the menu item, starting with the menu and ending with the sub menu containing the items
        ///
        /// @return True when the menu item existed and its children were removed, false when hierarchy was incorrect
        ///
        /// @code
        /// menuBar->removeSubMenuItems({"File", "Recent files"});
        /// @endcode
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool removeSubMenuItems(const std::vector<String>& hierarchy);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Enable or disable an entire menu
        /// @param menu     The name of the menu to enable or disable
        /// @param enabled  Should the menu be enabled or disabled?
        /// @return True when the menu exists, false when menu was not found
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool setMenuEnabled(const String& menu, bool enabled);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Check if an entire menu is enabled or disabled
        /// @param menu  The name of the menu to check
        /// @return True if the menu is enabled, false if it was disabled or when the menu did not exist
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD bool getMenuEnabled(const String& menu) const;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Enable or disable a menu item
        /// @param menu      The name of the menu in which the menu item is located
        /// @param menuItem  The name of the menu item to enable or disable
        /// @param enabled   Should the menu item be enabled or disabled?
        /// @return True when the menu item exists, false when menu or menuItem was not found
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool setMenuItemEnabled(const String& menu, const String& menuItem, bool enabled);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Enable or disable a menu item
        /// @param hierarchy  Hierarchy of menu items, starting with the menu and ending with the menu item to enable/disable
        /// @param enabled    Should the menu item be enabled or disabled?
        /// @return True when the menu item exists, false when hierarchy was incorrect
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool setMenuItemEnabled(const std::vector<String>& hierarchy, bool enabled);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Check if a menu item is enabled or disabled
        /// @param menu      The name of the menu in which the menu item is located
        /// @param menuItem  The name of the menu item to check
        /// @return True if the menu item is enabled, false if it was disabled or when the menu or menuItem did not exist
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD bool getMenuItemEnabled(const String& menu, const String& menuItem) const;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Check if a menu item is enabled or disabled
        /// @param hierarchy  Hierarchy of menu items, starting with the menu and ending with the menu item to check
        /// @return True if the menu item is enabled, false if it was disabled or when the hierarchy was incorrect
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD bool getMenuItemEnabled(const std::vector<String>& hierarchy) const;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the minimum width of the submenus
        ///
        /// When a submenu is displayed, the width will be either this or the width of the longest text in the submenu.
        ///
        /// @param minimumWidth  minimum width of the submenus
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setMinimumSubMenuWidth(float minimumWidth);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the minimum width of the submenus
        ///
        /// @return minimum width of the submenus
        ///
        /// @see setMinimumSubMenuWidth
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD float getMinimumSubMenuWidth() const;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes whether the menus open above or below the menu bar
        ///
        /// @param invertDirection  Should the menus open above the bar instead of below like it does by default?
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setInvertedMenuDirection(bool invertDirection);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns whether the menus open above or below the menu bar
        ///
        /// @return Do menus open above the bar instead of below like it does by default?
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD bool getInvertedMenuDirection() const;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the menus and their menu items, including submenus
        /// @return List of menus
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD std::vector<GetMenusElement> getMenus() const;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Closes the open menu when one of the menus is open
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void closeMenu() override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns whether the mouse position (which is relative to the parent widget) lies on top of the widget
        ///
        /// @return Is the mouse on top of the widget?
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD bool isMouseOnWidget(Vector2f pos) const override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool leftMousePressed(Vector2f pos) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void leftMouseReleased(Vector2f pos) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void mouseMoved(Vector2f pos) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Draw the widget to a render target
        ///
        /// @param target Render target to draw to
        /// @param states Current render states
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void draw(BackendRenderTarget& target, RenderStates states) const override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    protected:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Function called when one of the properties of the renderer is changed
        ///
        /// @param property  Name of the property that was changed
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void rendererChanged(const String& property) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Saves the widget as a tree node in order to save it to a file
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD std::unique_ptr<DataIO::Node> save(SavingRenderersMap& renderers) const override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Loads the widget from a tree of nodes
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void load(const std::unique_ptr<DataIO::Node>& node, const LoadingRenderersMap& renderers) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Called when the text size is changed (either by setTextSize or via the renderer)
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void updateTextSize() override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Makes a copy of the widget
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD Widget::Ptr clone() const override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Opens a menu
        /// @param menuIndex  Index of the menu to open
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void openMenu(std::size_t menuIndex);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /// @brief Draw the backgrounds and text of the menu names on top of the bar itself
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void drawMenusOnBar(BackendRenderTarget& target, RenderStates states) const;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /// @brief Calculates the offset of an open menu relative to the menu bar
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD Vector2f calculateMenuOffset(std::size_t visibleMenuIdx) const;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /// @brief Triggers the onMenuItemClick callback
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void emitMenuItemClick(const std::vector<String>& hierarchy) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /// @brief Deselects the selected item of the deepest open submenu
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void deselectDeepestItem() override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /// @brief Is the mouse located on one of the opened menus?
        /// @param pos  Mouse position
        /// @return True if mouse on menu, false otherwise.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD bool isMouseOnOpenMenu(Vector2f pos) const override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /// @brief Returns the height of a normal menu item (i.e. not a separator). For a menu bar this is the height of the bar.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD float getDefaultMenuItemHeight() const override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /// @brief Left mouse button was released while a menu might be open
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void leftMouseReleasedOnMenu() override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /// @brief Mouse moved on top of a menu
        /// @param pos  Mouse position
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void mouseMovedOnMenu(Vector2f pos) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /// @brief Called from OpenMenuPlaceholder to draw the menu that is currently open
        /// @param target Render target to draw to
        /// @param states Current render states
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void drawOpenMenu(BackendRenderTarget& target, RenderStates states) const override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    protected:

        std::vector<Menu> m_menus;
        int m_visibleMenu = -1;
        Sprite m_spriteBackground;
    };

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // TGUI_MENU_BAR_HPP
