//
//  main.cpp
//  CinderES2
//
//  Created by Kris Meeusen on 13/02/13.
//  Copyright (c) 2013 Kris Meeusen. All rights reserved.
//

#include "mainController.h"
#include "cinder/app/AppBasic.h"
#include  "QuartzCore/QuartzCore.h"
#include "cinder/ImageIo.h"
#include "cinder/app/AppBasic.h"


using namespace ci;
using namespace app;
using namespace gl2;


void mainController::setActiveTouches(std::vector<ci::Vec2f> touches){
	activeTouches.clear();
	activeTouches = touches;

}

void mainController::touchesBegan(std::vector<ci::Vec2f> touches){
}

void mainController::touchesMoved(std::vector<ci::Vec2f> touches){

}

void mainController::setup(){
	
    mesh.appendVertex(Vec3f(100,300,-0.1));
    mesh.appendVertex(Vec3f(10,10,-0.1));
    mesh.appendVertex(Vec3f(310,10,-0.1));
    
	// not implemented
//    mesh.appendColorRGB(Color(1,1,0));
//    mesh.appendColorRGB(Color(1,0,1));
//    mesh.appendColorRGB(Color(1,0,1));
	
	mesh.appendTexCoord(Vec2f(1,1));
	mesh.appendTexCoord(Vec2f(0,0));
	mesh.appendTexCoord(Vec2f(1,0));

	setLineWidth(8);
    
    
    texture = ci::loadImage(ci::app::loadResource("1.png"));
	std::cout << "texture loaded " << texture.getWidth() << std::endl;


}


void mainController::setSize(ci::Vec2f size){
	camera.setOrtho(0, size.x, 0, size.y, -1, 1);
	gl2::setCamera(camera.getProjectionMatrix());
	
	std::cout << "set size " << size <<  std::endl;
}


void mainController::update(){
	
}



void mainController::draw(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.15f, 0.3, 0.15f, 1.0f);
	
    bindTexture(texture);
	drawMesh(mesh);
    unbindTexture(texture);
    
    
    drawTexture(texture);
	
	setColor(ColorA(0,1,1,1));
	
	if(activeTouches.size() > 1){
		for(int i=0;i < activeTouches.size();++i){
			for(int j=0;j < activeTouches.size();++j){
				drawLine(Vec3f(activeTouches[i].x,activeTouches[i].y,0), Vec3f(activeTouches[j].x,activeTouches[j].y,0));
			}
		}
	}


	
     
}
