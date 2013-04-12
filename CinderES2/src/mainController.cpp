//
//  main.cpp
//  CinderES2
//
//  Created by Kris Meeusen on 13/02/13.
//  Copyright (c) 2013 Kris Meeusen. All rights reserved.
//

#include "mainController.h"
#include "cinder/app/AppBasic.h"
#include "QuartzCore/QuartzCore.h"
#include "cinder/ImageIo.h"
#include "TouchDispatcher.h"
#include "checkError.h"


using namespace ci;
using namespace app;
using namespace gl2;




void mainController::touchesBegan(std::vector<ci::Vec2f> touches){
}

void mainController::touchesMoved(std::vector<ci::Vec2f> touches){

}

void mainController::setup(){
	
	
	
    mesh.appendVertex(Vec3f(10,300,-0.1));
    mesh.appendVertex(Vec3f(10,10,-0.1));
    mesh.appendVertex(Vec3f(300,10,-0.1));
    
	// not implemented
//    mesh.appendColorRGB(Color(1,1,0));
//    mesh.appendColorRGB(Color(1,0,1));
//    mesh.appendColorRGB(Color(1,0,1));
	
	mesh.appendTexCoord(Vec2f(0,1));
	mesh.appendTexCoord(Vec2f(0,0));
	mesh.appendTexCoord(Vec2f(1,0));

//	glUseProgram(ColorRender::Instance()->program);
	int test = (ColorRender::Instance()->program);
	vboMesh = new VboMesh(mesh);
	gl2::CheckForErrors();

//	glUseProgram(0);
	

	setLineWidth(8);
    
    
    texture = ci::loadImage(ci::app::loadResource("1.png"));
	std::cout << "texture loaded " << texture.getWidth() << std::endl;
	
    // double scale for retina images
    button.setTexureScale(2);
	button.setupByResource("btnStart.png", 320/2, 568/2, ALIGN_CENTER);
	button.onClicked.Connect(this,&mainController::clicked);
	button.argument = "arg test";
	button.enable();
	button.resetData();
	button.update();
    
    star.setTexureScale(2);
    star.setupByResource("star.png", 120, 60, ALIGN_CENTER);
    
    glDisable(GL_DEPTH_TEST);
    
    
    isRotating = false;

}

void mainController::clicked(uiSpriteButton* button){
	std::cout << button->argument;
    button->setAlpha(1);
    button->setCenterPosition(Vec2f(-button->getBoundingBox().getWidth(),button->getCenterPosition().y));
	//"clicked";
}

void mainController::setSize(ci::Vec2f size){
    
    camera.setOrtho(0, size.x, 0,size.y, -1, 1);
	gl2::setCamera(camera.getProjectionMatrix());
	
	std::cout << "set size " << size <<  std::endl;
}


void mainController::update(){
    star.setRotation(star.getRotation() + 1.0);
	button.update();
    star.update();
}



void mainController::draw(){

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.7f, 0.7, 0.75f, 1.0f);
	
	setColor(ColorA(1,1,0,1));

	
	
	ColorRender::Instance()->drawMesh(*vboMesh);
    
	
	bindTexture(texture);
	drawMesh(mesh);
    unbindTexture(texture);

//	return;
	
   // drawTexture(texture);
	
	
    int nrOfTouches = TouchDispatcher::Instance()->getActiveTouches().size();
	if(nrOfTouches > 1){
		for(int i=0;i < nrOfTouches;++i){
			for(int j=0;j < nrOfTouches;++j){
				drawLine(Vec3f(TouchDispatcher::Instance()->getActiveTouches()[i].x,TouchDispatcher::Instance()->getActiveTouches()[i].y,0), Vec3f(TouchDispatcher::Instance()->getActiveTouches()[j].x,TouchDispatcher::Instance()->getActiveTouches()[j].y,0));
			}
		}
	}
	
	glEnable(GL_BLEND);
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

	TextureRender::Instance()->drawSprite(star);
    TextureRender::Instance()->drawSprite(button);

	glDisable(GL_BLEND);


	
     
}
