//
//  colorRender.h
//  CinderES2
//
//  Created by Kris Meeusen on 15/02/13.
//  Copyright (c) 2013 Kris Meeusen. All rights reserved.
//

#ifndef __CinderES2__colorRender__
#define __CinderES2__colorRender__

#include <iostream>


#include "cinder/app/AppBasic.h"
#include "cinder/Timeline.h"
#include "cinder/TimelineItem.h"

#include "cinder/Camera.h"
#include "cinder/TriMesh.h"

#include "constants.h"

class colorRender{

private:
	GLuint program;
	GLint uWorldMatrix;
	GLint uColor;
	
	bool isSetup;
	static colorRender* instance;
	
public:
	void drawLine(const ci::Vec3f &start, const ci::Vec3f &end );
	void drawMesh(const ci::TriMesh mesh);
	void drawMesh(const ci::TriMesh mesh,GLint shape);
	
	

	void setCameraMatrix(ci::Matrix44f worldMatrix);
	void setColor(const ci::ColorA color);
	void setLineWidth(const float width);

	
	colorRender();
	
	static colorRender* Instance();
	
	void setup();
	
};

#endif /* defined(__CinderES2__colorRender__) */
