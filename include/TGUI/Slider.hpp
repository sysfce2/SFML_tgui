/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus's Graphical User Interface
// Copyright (C) 2012 Bruno Van de Velde (VDV_B@hotmail.com)
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


#ifndef _TGUI_SLIDER_INCLUDED_
#define _TGUI_SLIDER_INCLUDED_

/// \todo  The thumb should have the same scaling as the rest of the slider.
///        This is already done in the experimental brach, but this cannot be merged before scrollbar is fixed too.

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    struct TGUI_API Slider : public OBJECT
    {
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Default constructor
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Slider();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Copy constructor
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Slider(const Slider& copy);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Destructor
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual ~Slider();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Overload of assignment operator
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Slider& operator= (const Slider& right);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual Slider* clone();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Loads the slider images.
        ///
        /// The \a verticalScroll member might be changed in this function. If you want to change it then do it afterwards.
        ///
        /// \param pathname  The path to the folder that contains the images.
        ///                  The folder must also contain an info.txt file, which will give more information about the slider.
        ///
        /// \return
        ///        - true on success
        ///        - false when the pathname is empty
        ///        - false when the info.txt file was not found
        ///        - false when the images couldn't be loaded
        ///
        /// \remarks You must call setSize after this function or the slider will not be drawn on the screen.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual bool load(const std::string pathname);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Changes the size of the slider.
        ///
        /// \param width   The new width of the slider
        /// \param height  The new height of the slider
        ///
        /// \remarks If this function is not called then the slider will not be drawn on the screen.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setSize(float width, float height);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns the size of the slider, unaffected by scaling.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual Vector2u getSize() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns the size of the slider, after the scaling transformation.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual Vector2f getScaledSize() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns the pathname that was used to load the slider.
        ///
        /// When the slider has not been loaded yet then this function will return an empty string.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual std::string getLoadedPathname() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Sets a minimum value.
        ///
        /// When the value is too small then it will be changed to this minimum.
        /// The default minimum value is 0.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setMinimum(const unsigned int minimum);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Sets a maximum value.
        ///
        /// When the value is too big then it will be changed to this maximum.
        /// The default maximum value is 100.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setMaximum(const unsigned int maximum);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Changes the current value.
        ///
        /// It can't be smaller than the minimum or bigger than the maximum.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setValue(const unsigned int value);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns the minimum value.
        ///
        /// The default minimum value 0.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual unsigned int getMinimum() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns the maximum value.
        ///
        /// The default maximum value 0.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual unsigned int getMaximum() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns the current value.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual unsigned int getValue() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // These functions are used to receive callback from the EventManager.
        // You normally don't need them, but you can use them to simulate an event.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual bool mouseOnObject(float x, float y);
        virtual void leftMousePressed(float x, float y);
        virtual void leftMouseReleased(float x, float y);
        virtual void mouseMoved(float x, float y);
        virtual void keyPressed(sf::Keyboard::Key key);
        virtual void objectFocused();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    protected:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Because this struct is derived from sf::Drawable, you can just call the draw function from your sf::RenderTarget.
        // This function will be called and it will draw the slider on the render target.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    public:

        /// Is the slider draw vertically?
        /// Set this boolean to false when the slider should lie horizontal.
        bool verticalScroll;

    protected:

        // When the mouse went down, did it go down on top of the thumb? If so, where?
        bool m_MouseDownOnThumb;
        Vector2f m_MouseDownOnThumbPos;

        unsigned int m_Minimum;
        unsigned int m_Maximum;
        unsigned int m_Value;

        // Is the image vertically?
        bool m_VerticalImage;

        // If this is true then the L, M and R images will be used.
        // If it is false then the slider is just one big image that will be stored in the M image.
        bool m_SplitImage;

        // Is there a separate hover image, or is it a semi-transparent image that is drawn on top of the others?
        bool m_SeparateHoverImage;

        // The size of the slider and its thumb
        Vector2f m_Size;
        Vector2f m_ThumbSize;

        sf::Texture* m_TextureTrackNormal_L;
        sf::Texture* m_TextureTrackHover_L;
        sf::Texture* m_TextureTrackNormal_M;
        sf::Texture* m_TextureTrackHover_M;
        sf::Texture* m_TextureTrackNormal_R;
        sf::Texture* m_TextureTrackHover_R;
        sf::Texture* m_TextureThumbNormal;
        sf::Texture* m_TextureThumbHover;

        sf::Sprite   m_SpriteTrackNormal_L;
        sf::Sprite   m_SpriteTrackHover_L;
        sf::Sprite   m_SpriteTrackNormal_M;
        sf::Sprite   m_SpriteTrackHover_M;
        sf::Sprite   m_SpriteTrackNormal_R;
        sf::Sprite   m_SpriteTrackHover_R;
        sf::Sprite   m_SpriteThumbNormal;
        sf::Sprite   m_SpriteThumbHover;

        // The pathname used to load the slider
        std::string m_LoadedPathname;
    };

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif //_TGUI_SLIDER_INCLUDED_
