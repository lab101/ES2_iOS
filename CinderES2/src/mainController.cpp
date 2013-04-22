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
#include "TouchDispatcher.h"



using namespace ci;
using namespace app;
using namespace gl2;



void mainController::setup(){
	
	
	
    mesh1.appendVertex(Vec3f(10,200,0));
    mesh1.appendVertex(Vec3f(10,10,0));
    mesh1.appendVertex(Vec3f(200,10,0));

	// not implemented
//    mesh.appendColorRGB(Color(1,1,0));
//    mesh.appendColorRGB(Color(1,0,1));
//    mesh.appendColorRGB(Color(1,0,1));
	
	mesh1.appendTexCoord(Vec2f(0,1));
	mesh1.appendTexCoord(Vec2f(0,0));
	mesh1.appendTexCoord(Vec2f(1,0));

	
	//mesh2
	mesh2.appendVertex(Vec3f(-100,100,0));
    mesh2.appendVertex(Vec3f(-100,-100,0));
    mesh2.appendVertex(Vec3f(100,-100,0));
	
	mesh2.appendTexCoord(Vec2f(0,1));
	mesh2.appendTexCoord(Vec2f(0,0));
	mesh2.appendTexCoord(Vec2f(1,0));

	
	
	glUseProgram(ColorRender::Instance()->program);
	vboMesh = new VboMesh(mesh2);
	gl2::CheckForErrors();

	glUseProgram(0);
	

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
    
    //glDisable(GL_DEPTH_TEST);
    
    
    isRotating = false;
    
    perspectiveRender.setup();
    //perspectiveRender.setColor(ColorA(1.0,0.0,1.0,1.0));
    
    TouchDispatcher::Instance()->onTouchesBegan.Connect(this,&mainController::touchesBegan);
    TouchDispatcher::Instance()->onTouchesMoved.Connect(this,&mainController::touchesMoved);
    TouchDispatcher::Instance()->onTouchesEnded.Connect(this,&mainController::touchesEnded);
	
	//trackball.set(0.01, 0, 1, 0);
	frameCounter = 0;
	lastTouchPoint.set(-1 ,-1);
}


void mainController::touchesBegan(std::vector<ci::Vec2f> touches){
	if(touches.size() > 1) return;
	
	std::cout << "started" << lastTouchPoint << std::endl;

	lastTouchPoint = touches[0];
	std::cout << lastTouchPoint << std::endl;

}

void mainController::touchesEnded(std::vector<ci::Vec2f> touches){
	if(touches.size() > 1) return;

	std::cout << "ended" << lastTouchPoint << std::endl;

	lastTouchPoint.set(-1 ,-1);
}

void mainController::touchesMoved(std::vector<ci::Vec2f> touches){
	if(touches.size() > 1) return;

   // perspectiveCamera.lookAt( mesh.getVertices()[2] + Vec3f(touches[0].x /100 ,touches[0].y/100 ,-1),mesh.getVertices()[2], Vec3f::yAxis() );
	
	std::cout << lastTouchPoint << std::endl;
	
	// check if first touchpoint
	if (lastTouchPoint.x == -1 && lastTouchPoint.y == -1) {
		return;
	}
	

	Vec2f div = lastTouchPoint - touches[0];
	
	//float newYaw = trackball.getYaw() + div.x/100.0;
	//trackball.set(0,newYaw,0);
	localMatrix.rotate(Vec3f(0,1,0), -div.x / 100.0);
	localMatrix.rotate(Vec3f(1,0,0), div.y / 100.0);
	lastTouchPoint = touches[0];

	
	/*
	float lookatX = 150.0 + 320- (touches[0].x *2);
	float lookatY = 150.0 + 568- (touches[0].y *2);
	
	perspectiveCamera.lookAt(Vec3f(lookatX,lookatY,+500.0),Vec3f(150.0,150.0,0.0),Vec3f::yAxis());
    perspectiveRender.setCameraMatrix(perspectiveCamera.getProjectionMatrix() * perspectiveCamera.getModelViewMatrix());
	 */

}


void mainController::clicked(uiSpriteButton* button){
	std::cout << button->argument;
    button->setAlpha(1);
    button->setCenterPosition(Vec2f(-button->getBoundingBox().getWidth(),button->getCenterPosition().y));
	//"clicked";
}

void mainController::setSize(ci::Vec2f size){
    
    
    // Set default renders to orthocamera
    orthoCamera.setOrtho(0, size.x, 0,size.y, -1, 1);
	gl2::setCamera(orthoCamera.getProjectionMatrix());

    
    
    // Create perspective camera for perspective render
    perspectiveCamera.setPerspective( 60.0f, size.x / size.y, 1.0f, 1000.0f );
	perspectiveCamera.lookAt(Vec3f(0,0.0,+500.0),Vec3f(0.0,0.0,0.0),Vec3f::yAxis());

    
    perspectiveRender.setCameraMatrix(perspectiveCamera.getProjectionMatrix() * perspectiveCamera.getModelViewMatrix());

    
    
	std::cout << "set size " << size <<  std::endl;
}


void mainController::update(){
	
	++frameCounter;
	//trackball.set(0, 0, sin(frameCounter/200.0));
	perspectiveRender.setCameraMatrix(perspectiveCamera.getProjectionMatrix() * perspectiveCamera.getModelViewMatrix() * localMatrix);

    star.setRotation(star.getRotation() + 1.0);
    
	button.update();
    star.update();
	
	
	localMatrix.lowerTriangular()
//	float newYaw = trackball.getYaw()+ 0.1;
//	trackball.set(0,newYaw,0);

}



void mainController::draw(){

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.7f, 0.7, 0.75f, 1.0f);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
	setColor(ColorA(1,0.4,0,1));

	glEnable(GL_BLEND);

	bindTexture(texture);
    perspectiveRender.drawMesh(*vboMesh);
    unbindTexture(texture);
    
	
	bindTexture(texture);
	drawMesh(mesh1);
    unbindTexture(texture);

	
	
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
