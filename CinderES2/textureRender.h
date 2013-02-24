//
//  textureRender.h
//  CinderES2
//
//  Created by Kris Meeusen on 15/02/13.
//  Copyright (c) 2013 Kris Meeusen. All rights reserved.
//

#ifndef __CinderES2__textureRender__
#define __CinderES2__textureRender__

#include <iostream>


#include "cinder/app/AppBasic.h"
#include "cinder/Timeline.h"
#include "cinder/TimelineItem.h"

#include "cinder/Camera.h"
#include "cinder/TriMesh.h"
#include "cinder/gl/Texture.h"


#include "constants.h"

class textureRender{
	
private:
	GLuint program;
	GLint uWorldMatrix;
	
	GLuint interfaceTextureId;
	
	bool isSetup;
	static textureRender* instance;
	
	
public:
	void drawLine(const ci::Vec3f &start, const ci::Vec3f &end );
	void drawMesh(const ci::TriMesh mesh);
	void drawMesh(const ci::TriMesh mesh,GLint shape);
	void drawTexture(const ci::gl::Texture& texture);
	
	
	void setCameraMatrix(ci::Matrix44f worldMatrix);
	void bindTexture(const ci::gl::Texture& texture);
	void unbindTexture(const ci::gl::Texture& texture);

	void setLineWidth(const float width);
	
	
	textureRender();
	
	static textureRender* Instance();
	
	void setup();
	
	
};

#endif /* defined(__CinderES2__textureRender__) */
