
//  Created by Kris Meeusen on 05/10/12.
//
//

#include "uiFontSprite.h"
#include "cinder/app/AppBasic.h"

using namespace ci;

uiFontSprite::uiFontSprite(){
    mColor = Color( 1, 1, 1.1f );
    mAlligment = ALIGN_BOTTOMLEFT;

}

void uiFontSprite::setup(){

    setup("AVGITCBT.TTF", 120,0,0 );
}

void uiFontSprite::setup(std::string fontName,int size,float x,float y,int align){
    mAlligment = align;
    mOriginalPoint.set(x, y);
    mFont = ci::Font(ci::app::loadResource(fontName),size);
    isTextureReady=false;
}



void uiFontSprite::setText(std::string text){
    mText = text;
    generateTexture();
    setDirty();
}

void uiFontSprite::setAlign(int align){
    mAlligment = align;
    setDirty();
}

void uiFontSprite::setColor(ci::Color color){
    mColor  = color;
    setDirty();
}

bool  uiFontSprite::update(bool parentIsDirty =false){
//    if (isDirty) {
//       // std::cout << "new texture" << std::endl;
//        generateTexture();
//    }
    return true;//npBitmapSprite::update(parentIsDirty);
}


void uiFontSprite::generateTexture(){
    TextLayout simple;
	simple.setFont(mFont);
	simple.setColor(mColor);
	simple.addLine(mText);
	mTexture = gl::Texture( simple.render( true, true ) );
    
    
    setupByTexture(mTexture, mOriginalPoint,mAlligment);
    //uiSprite::setSize(mTexture.getWidth(),mTexture.getHeight(),mAlligment);
    
    
    isTextureReady=true;


}

