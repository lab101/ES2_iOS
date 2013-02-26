//
//  TouchDispatcher.h
//  CinderES2
//
//  Created by Kris Meeusen on 26/02/13.
//  Copyright (c) 2013 Kris Meeusen. All rights reserved.
//

#ifndef __CinderES2__TouchDispatcher__
#define __CinderES2__TouchDispatcher__

#include <iostream>
#include <vector>
#include "cinder/Vector.h"

#include "Signal.h"
#include "Delegate.h"


class TouchDispatcher{
    
private:
    static TouchDispatcher* instance;
    std::vector<ci::Vec2f> mActiveTouches;

public:
    static TouchDispatcher* Instance();

    
    std::vector<ci::Vec2f> getActiveTouches();
	void setActiveTouches(std::vector<ci::Vec2f> touches);
	void beginTouches(std::vector<ci::Vec2f> touches);
	void endTouches(std::vector<ci::Vec2f> touches);
    
    TouchDispatcher();
    
    Gallant::Signal1< std::vector<ci::Vec2f> > onTouchesEnded;

    

};

#endif /* defined(__CinderES2__TouchDispatcher__) */
