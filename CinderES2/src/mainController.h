//
//  main.h
//  CinderES2
//
//  Created by Kris Meeusen on 13/02/13.
//  Copyright (c) 2013 Kris Meeusen. All rights reserved.
//

#ifndef __CinderES2__main__
#define __CinderES2__main__

#include <iostream>
#include "cinder/app/AppBasic.h"
#include "cinder/Timeline.h"
#include "cinder/TimelineItem.h"

#include "cinder/Camera.h"
#include "cinder/TriMesh.h"
#include "gl2.h"

//#include "colorRender.h"

class mainController{

private:
	
public:
	
	//mainController();
	void update();
	void setup();
	void setSize(ci::Vec2f size);
	
    GLuint LoadShader(const char *shaderSrc, GLenum type);

	void draw();




    ci::CameraPersp cameraPersp;

    GLuint _vertexArray;
    GLuint _vertexBuffer;
    

    GLuint program;
    GLint uWorldMatrix;
    
    ci::TriMesh mesh;
	ci::CameraOrtho camera;
    
	//colorRender mColorRender;
	
	std::vector<ci::Vec2f> activeTouches;
	
	void setActiveTouches(std::vector<ci::Vec2f> touches);
	void touchesBegan(std::vector<ci::Vec2f> touches);
	void touchesMoved(std::vector<ci::Vec2f> touches);



};
#endif /* defined(__CinderES2__main__) */
