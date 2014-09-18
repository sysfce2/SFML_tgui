/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus's Graphical User Interface
// Copyright (C) 2012-2014 Bruno Van de Velde (vdv_b@tgui.eu)
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


#ifndef TGUI_TAB_HPP
#define TGUI_TAB_HPP


#include <TGUI/Label.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    class TabRenderer;

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Tab widget
    ///
    /// Signals:
    ///     - TabChanged (Another tab has been selected)
    ///         * Optional parameter sf::String: New name of the newly selected tab
    ///         * Uses Callback member 'text'
    ///
    ///     - Inherited signals from Widget
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class TGUI_API Tab : public Widget
    {
    public:

        typedef std::shared_ptr<Tab> Ptr; ///< Shared widget pointer
        typedef std::shared_ptr<const Tab> ConstPtr; ///< Shared constant widget pointer


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Default constructor
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Tab();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Virtual destructor
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual ~Tab() {}


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Create the tab
        ///
        /// @param themeFileFilename  Filename of the theme file.
        /// @param section            The section in the theme file to read.
        ///
        /// @throw Exception when the theme file could not be opened.
        /// @throw Exception when the theme file did not contain the requested section with the needed information.
        /// @throw Exception when one of the images, described in the theme file, could not be loaded.
        ///
        /// When an empty string is passed as filename, the built-in white theme will be used.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        static Tab::Ptr create(const std::string& themeFileFilename = "", const std::string& section = "Tab");


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Makes a copy of another tab
        ///
        /// @param tab  The other tab
        ///
        /// @return The new tab
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        static Tab::Ptr copy(Tab::ConstPtr tab);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the renderer, which gives access to functions that determine how the widget is displayed
        ///
        /// @return Reference to the renderer
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        std::shared_ptr<TabRenderer> getRenderer() const
        {
            return std::static_pointer_cast<TabRenderer>(m_renderer);
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Set the position of the widget
        ///
        /// This function completely overwrites the previous position.
        /// See the move function to apply an offset based on the previous position instead.
        /// The default position of a transformable widget is (0, 0).
        ///
        /// @param position  New position
        ///
        /// @see move, getPosition
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setPosition(const Layout& position) override;
        using Transformable::setPosition;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief This function currently does nothing.
        ///
        /// @param size  Currently ignored
        ///
        /// It is not yet possible to change the size directly.
        ///
        /// @see setTabHeight
        /// @see setDistanceToSide
        /// @see setMaximumTabWidth
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setSize(const Layout& size) override;
        using Transformable::setSize;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the size of the tabs.
        ///
        /// @return Size of the tabs
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual sf::Vector2f getSize() const override
        {
            return {m_width, m_tabHeight};
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Adds a new tab.
        ///
        /// @param name    The name of the tab (this is the text that will be drawn on top of the tab).
        /// @param select  Do you want the new tab to be selected immediately?
        ///
        /// @return  The index of the tab in the list.
        ///
        /// @warning The index returned by this function may no longer be correct when a tab is removed.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        unsigned int add(const sf::String& name, bool select = true);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Selects the tab with a given name.
        ///
        /// @param name  The name of the tab to select.
        ///
        /// When the name doen't match any tab then nothing will be changed.
        /// If there are multiple tabs with the same name then the first one will be selected.
        ///
        /// @see select(int)
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void select(const sf::String& name);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Selects the tab with a given index.
        ///
        /// @param index  The index of the tab to select.
        ///
        /// When the index is too high then nothing will happen.
        ///
        /// @see select(sf::String)
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void select(unsigned int index);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Deselects the selected tab.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void deselect();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Removes a tab with a given name.
        ///
        /// @param name  The name of the tab to remove.
        ///
        /// When multiple tabs have the same name, only the first will be removed.
        ///
        /// @see remove(unsigned int)
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void remove(const sf::String& name);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Removes a tab with a given index.
        ///
        /// @param index  The index of the tab to remove.
        ///
        /// When the index is too high then nothing will happen.
        ///
        /// @see remove(sf::String)
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void remove(unsigned int index);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Removes all tabs.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void removeAll();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Get the name of the currently selected tab.
        ///
        /// @return The name of the tab.
        ///         When no tab is selected then this function returns an empty string.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        sf::String getSelected() const
        {
            return (m_selectedTab >= 0) ? m_tabNames[m_selectedTab].getText() : "";
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Get the index of the currently selected tab.
        ///
        /// @return The index of the tab.
        ///         When no tab is selected then this function returns -1.
        ///
        /// @warning The index returned by this function may no longer be correct when a tab is removed.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        int getSelectedIndex() const
        {
            return m_selectedTab;
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the character size of the text.
        ///
        /// @param size  The new size of the text.
        ///              If the size is 0 (default) then the text will be scaled to fit in the tab.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setTextSize(unsigned int size);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the character size of the text.
        ///
        /// @return The text size.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        unsigned int getTextSize() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the height of the tabs.
        ///
        /// @param height  Height of the tabs
        ///
        /// By default, it is the height of the tab image that is loaded with the load function.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setTabHeight(float height);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the height of the tabs.
        ///
        /// @return Tab height
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        float getTabHeight() const
        {
            return m_tabHeight;
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the maximum tab width of the tabs.
        ///
        /// @param maximumWidth  Maximum width of a single tab
        ///
        /// If the text on the tab is longer than this width then it will be cropped to fit inside the tab.
        /// By default, the maximum width is 0 which means that there is no limitation.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setMaximumTabWidth(float maximumWidth);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the maximum tab width of the tabs.
        ///
        /// @return Maximum tab width
        ///
        /// If the text on the tab is longer than this width then it will be cropped to fit inside the tab.
        /// By default, the maximum width is 0 which means that there is no limitation.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        float getMaximumTabWidth() const
        {
            return m_maximumTabWidth;
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the transparency of the widget.
        ///
        /// @param transparency  The transparency of the widget.
        ///                      0 is completely transparent, while 255 (default) means fully opaque.
        ///
        /// Note that this will only change the transparency of the images. The parts of the widgets that use a color will not
        /// be changed. You must change them yourself by setting the alpha channel of the color.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setTransparency(unsigned char transparency) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual bool mouseOnWidget(float x, float y) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void leftMousePressed(float x, float y) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    protected:


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Recalculates the size of each tab image.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void recalculateTabsWidth();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // This function is called when the widget is added to a container.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void initialize(Container *const container) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Makes a copy of the widget
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual Widget::Ptr clone() override
        {
            return std::make_shared<Tab>(*this);
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Draws the widget on the render target.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    protected:

        // The distance between the side of the tab and the text that is drawn on top of the tab.
        unsigned int       m_distanceToSide = 5;

        unsigned int       m_textSize = 0;
        float              m_maximumTabWidth = 0;
        int                m_selectedTab = -1;

        float              m_width = 0;
        float              m_tabHeight = 0;
        std::vector<float> m_tabWidth;

        std::vector<Label> m_tabNames;

        friend class TabRenderer;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    };


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    class TabRenderer : public WidgetRenderer, public WidgetBorders
    {
    public:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Constructor
        ///
        /// @param tab  The tab that is connected to the renderer
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TabRenderer(Tab* tab) : m_tab{tab} {}


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Dynamically change a property of the renderer, without even knowing the type of the widget.
        ///
        /// This function should only be used when you don't know the type of the widget.
        /// Otherwise you can make a direct function call to make the wanted change.
        ///
        /// @param property  The property that you would like to change
        /// @param value     The new value that you like to assign to the property
        /// @param rootPath  Path that should be placed in front of any resource filename
        ///
        /// @throw Exception when the property doesn't exist for this widget.
        /// @throw Exception when the value is invalid for this property.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setProperty(std::string property, const std::string& value, const std::string& rootPath = getResourcePath()) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the font of the tabs.
        ///
        /// When you don't call this function then the global font will be use.
        /// This global font can be changed with the setGlobalFont function from the parent.
        ///
        /// @param font  The new font.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setTextFont(std::shared_ptr<sf::Font> font);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Set the text color that will be used inside the tabs.
        ///
        /// @param color  The new text color.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setTextColor(const sf::Color& color)
        {
            m_textColor = color;
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Set the text color that will be used for the selected tab.
        ///
        /// @param color  The new text color.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setSelectedTextColor(const sf::Color& color)
        {
            m_selectedTextColor = color;
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the distance between the text and the side of the tab.
        ///
        /// @param distanceToSide  distance between the text and the side of the tab
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setDistanceToSide(unsigned int distanceToSide);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Change the image that is displayed when the tab is not selected
        ///
        /// When this image and the selected image are set, the background color properties will be ignored.
        ///
        /// Pass an empty string to unset the image, in this case the background color properties will be used again.
        ///
        /// @param filename   Filename of the image to load.
        /// @param partRect   Load only part of the image. Don't pass this parameter if you want to load the full image.
        /// @param middlePart Choose the middle part of the image for 9-slice scaling (relative to the part defined by partRect)
        /// @param repeated   Should the image be repeated or stretched when the size is bigger than the image?
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setNormalImage(const std::string& filename,
                            const sf::IntRect& partRect = sf::IntRect(0, 0, 0, 0),
                            const sf::IntRect& middlePart = sf::IntRect(0, 0, 0, 0),
                            bool repeated = false);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Change the image that is displayed when the tab is selected
        ///
        /// When this image and the normal image are set, the background color properties will be ignored.
        ///
        /// Pass an empty string to unset the image, in this case the background color properties will be used again.
        ///
        /// @param filename   Filename of the image to load.
        /// @param partRect   Load only part of the image. Don't pass this parameter if you want to load the full image.
        /// @param middlePart Choose the middle part of the image for 9-slice scaling (relative to the part defined by partRect)
        /// @param repeated   Should the image be repeated or stretched when the size is bigger than the image?
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setSelectedImage(const std::string& filename,
                              const sf::IntRect& partRect = sf::IntRect(0, 0, 0, 0),
                              const sf::IntRect& middlePart = sf::IntRect(0, 0, 0, 0),
                              bool repeated = false);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Set the background color of the tabs
        ///
        /// @param color  The new background color.
        ///
        /// Note that this color is ignored when a normal and selected image were set.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setBackgroundColor(const sf::Color& color)
        {
            m_backgroundColor = color;
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Set the background color of the selected tab.
        ///
        /// @param color  The new background color.
        ///
        /// Note that this color is ignored when a normal and selected image were set.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setSelectedBackgroundColor(const sf::Color& color)
        {
            m_selectedBackgroundColor = color;
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Set the color of the borders
        ///
        /// @param color  The new border color.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setBorderColor(const sf::Color& color)
        {
            m_borderColor = color;
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Draws the widget on the render target.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    private:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Makes a copy of the renderer
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual std::shared_ptr<WidgetRenderer> clone(Widget* widget) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        TabRenderer(const TabRenderer&) = default;
        TabRenderer& operator=(const TabRenderer&) = delete;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    protected:

        Tab* m_tab;

        Texture            m_textureNormal;
        Texture            m_textureSelected;
        std::list<Texture> m_texturesNormal;
        std::list<Texture> m_texturesSelected;

        sf::Color m_textColor         = {  0,   0,   0};
        sf::Color m_selectedTextColor = {255, 255, 255};

        sf::Color m_backgroundColor         = {255, 255, 255};
        sf::Color m_selectedBackgroundColor = {  0, 110, 255};

        sf::Color m_borderColor = {0, 0, 0};

        friend class Tab;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    };

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // TGUI_TAB_HPP
