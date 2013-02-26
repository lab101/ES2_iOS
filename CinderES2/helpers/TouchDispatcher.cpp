//
//  TouchDispatcher.cpp
//  CinderES2
//
//  Created by Kris Meeusen on 26/02/13.
//  Copyright (c) 2013 Kris Meeusen. All rights reserved.
//

#include "TouchDispatcher.h"

TouchDispatcher* TouchDispatcher::instance;

TouchDispatcher* TouchDispatcher::Instance(){
    if(instance == NULL)
	{
        instance = new TouchDispatcher();
        //instance->setup();
	}
    return instance;
}


TouchDispatcher::TouchDispatcher(){
}


std::vector<ci::Vec2f> TouchDispatcher::getActiveTouches(){
    return mActiveTouches;
}


void TouchDispatcher::setActiveTouches(std::vector<ci::Vec2f> touches){
	mActiveTouches.clear();
	mActiveTouches = touches;
}

void TouchDispatcher::beginTouches(std::vector<ci::Vec2f> touches){
    
}

void TouchDispatcher::endTouches(std::vector<ci::Vec2f> touches){
    onTouchesEnded(touches);
    
}


