//
//  uiSpriteButton.cpp
//  TouchGallery
//
//  Created by Kris Meeusen on 19/01/13.
//
//

#include "uiSpriteButton.h"
#include "cinder/app/AppBasic.h"
#include "cinder/Timeline.h"



using namespace ci;
using namespace app;


// uiSpriteButton::uiSpriteButton(){
// }

void uiSpriteButton::setup(){
	//AppBasic::get()->registerMouseDown(this,&uiSpriteButton::mouseDown);
	
//	uiSpriteButton test;
	onClicked(this);
}

bool uiSpriteButton::mouseDown(ci::app::MouseEvent event){
	
	if(getBoundingBox().contains(event.getPos()))
	{
//		onClicked(this);
     //   		onClicked();
		timeline().apply( &mScale, 0.9f, 0.1f, EaseInCubic()).updateFn(std::bind( &uiSprite::setDirty, this ));
		timeline().appendTo( &mScale, 1.0f, 0.1f, EaseInCubic()).updateFn(std::bind( &uiSprite::setDirty, this ));
		return true;
	}

	return false;
}