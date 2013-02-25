//
//  uiSpriteButton.h
//  TouchGallery
//
//  Created by Kris Meeusen on 19/01/13.
//
//

#ifndef __TouchGallery__uiSpriteButton__
#define __TouchGallery__uiSpriteButton__
#define BOOST_INTEL_STDCXX0X

#include <boost/signals.hpp>

#include <iostream>
#include "uiSprite.h"
#include "cinder/app/AppBasic.h"

#define BOOST_INTEL_STDCXX0X


class uiSpriteButton : public uiSprite{
	
public:
	//uiSpriteButton();
	void setup();
	
	//boost::signals2::signal<void(uiSpriteButton* button)> onClicked;
	//boost::signals::signal<void(uiSpriteButton* button)> onClicked;
//     boost::signals::connection mCallbacks;
    boost::signal<void ()> onClicked;

	std::string argument;
	
private:
	bool mouseDown(ci::app::MouseEvent event);
	
};

#endif /* defined(__TouchGallery__uiSpriteButton__) */
