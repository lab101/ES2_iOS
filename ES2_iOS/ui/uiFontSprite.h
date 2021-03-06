
//  Created by Kris Meeusen on 05/10/12.
//
//

#ifndef __eristoffGameConsole__uiFontSprite__
#define __eristoffGameConsole__uiFontSprite__

#include <iostream>

#include "cinder/Font.h"
#include "cinder/Text.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"

#include "uiSprite.h"

class uiFontSprite : public uiSprite{
    ci::Font	mFont;
    ci::gl::Texture	mTexture;
    ci::Color mColor;
    
    void generateTexture();
    
    std::string mText;
    

public:
    
    bool isTextureReady;
    uiFontSprite();
    
    void setup();
    void setup(std::string fontName,int size,float x,float y,int align = ALIGN_CENTER);
    
    virtual bool update(bool parentIsDirty );


    void bind();
    void setText(std::string text);
    void setAlign(int align);
    void setColor(ci::Color color);

    
};




#endif /* defined(__eristoffGameConsole__npFontObject__) */
