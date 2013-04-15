//
//  main.h
//  CinderES2
//
//  Created by Kris Meeusen on 13/02/13.
//  Copyright (c) 2013 Kris Meeusen. All rights reserved.
//

#ifndef __CinderES2__main__
#define __CinderES2__main__

//#include <iostream>
#include "cinder/app/AppBasic.h"
#include "cinder/Timeline.h"
#include "cinder/TimelineItem.h"

#include "cinder/Camera.h"
#include "cinder/TriMesh.h"

#include "cinder/gl/Texture.h"

#include "gl2.h"
#include "uiSpriteButton.h"
#include "uiSprite.h"
#include "VboMesh.h"

//#include "colorRender.h"

class mainController{

private:
	
    ci::gl::Texture texture;
    
    GLuint _vertexArray;
    GLuint _vertexBuffer;
    
    
    GLuint program;
    GLint uWorldMatrix;
    
	// classic mesh
    ci::TriMesh mesh;
	VboMesh* vboMesh;
	ci::CameraOrtho orthoCamera;
    ci::CameraPersp perspectiveCamera;

	ColorRender perspectiveRender;
	

    
    
	uiSpriteButton button;
    uiSprite star;
    
    bool isRotating;
	int countScreenshot;
	
	//test
	GLuint _storeFramebuffer,_storeRenderbuffer;

public:
	
	//mainController();
	void update();
	void setup();
	void setSize(ci::Vec2f size);

	
    GLuint LoadShader(const char *shaderSrc, GLenum type);

	void draw();


	void clicked(uiSpriteButton* button);


	
	void touchesBegan(std::vector<ci::Vec2f> touches);
    void touchesMoved(std::vector<ci::Vec2f> touches);

//	void touchesMoved(std::vector<ci::Vec2f> touches);



};
#endif /* defined(__CinderES2__main__) */
