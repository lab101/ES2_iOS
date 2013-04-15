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


#include <CoreVideo/CoreVideo.h>
#include <CoreVideo/CVPixelBuffer.h>
#include <QuartzCore/QuartzCore.h>

using namespace ci;
using namespace app;
using namespace gl2;



void mainController::setup(){
	
	
	
    mesh.appendVertex(Vec3f(10,300,0));
    mesh.appendVertex(Vec3f(10,10,0));
    mesh.appendVertex(Vec3f(300,10,0));

	// not implemented
//    mesh.appendColorRGB(Color(1,1,0));
//    mesh.appendColorRGB(Color(1,0,1));
//    mesh.appendColorRGB(Color(1,0,1));
	
	mesh.appendTexCoord(Vec2f(0,1));
	mesh.appendTexCoord(Vec2f(0,0));
	mesh.appendTexCoord(Vec2f(1,0));

	glUseProgram(ColorRender::Instance()->program);
	vboMesh = new VboMesh(mesh);
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
    perspectiveRender.setColor(ColorA(1.0,0.0,1.0,1.0));
    
    TouchDispatcher::Instance()->onTouchesMoved.Connect(this,&mainController::touchesMoved);
	
	// test buffer
	glGenFramebuffersOES(1, &_storeFramebuffer);
	glGenRenderbuffersOES(1, &_storeRenderbuffer);
	glBindFramebufferOES(GL_FRAMEBUFFER_OES, _storeFramebuffer);
	glBindRenderbufferOES(GL_RENDERBUFFER_OES, _storeRenderbuffer);
	glFramebufferRenderbufferOES(GL_FRAMEBUFFER_OES, GL_COLOR_ATTACHMENT0_OES,   GL_RENDERBUFFER_OES, _storeRenderbuffer);
	glRenderbufferStorageOES(GL_RENDERBUFFER_OES, GL_RGBA8_OES, 320, 568);
	
	countScreenshot = 0;
}



void mainController::touchesMoved(std::vector<ci::Vec2f> touches){
    perspectiveCamera.lookAt( mesh.getVertices()[2] + Vec3f(touches[0].x /100 ,touches[0].y/100 ,-1),mesh.getVertices()[2], Vec3f::yAxis() );

    perspectiveRender.setCameraMatrix(perspectiveCamera.getProjectionMatrix() * perspectiveCamera.getModelViewMatrix());
	if(++countScreenshot > 100){
		countScreenshot = 0;
		
		glBindFramebufferOES(GL_FRAMEBUFFER_OES, _storeFramebuffer);
		glBindRenderbufferOES(GL_RENDERBUFFER_OES, _storeRenderbuffer);
		GLuint* buffer = (GLuint*) malloc(320*568 * 4);

		glReadPixels(0, 0, 320, 568, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
	}
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
    perspectiveCamera.setPerspective( 60.0f, 1.5f, 1.0f, 1000.0f );
    perspectiveCamera.lookAt( mesh.getVertices()[2] + Vec3f(1,1,-1),mesh.getVertices()[2], Vec3f::yAxis() );

    
    perspectiveRender.setCameraMatrix(perspectiveCamera.getProjectionMatrix() * perspectiveCamera.getModelViewMatrix());

    
    
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
	
	setColor(ColorA(1,0.4,0,1));

	
   // ColorRender::Instance()->drawMesh(mesh);
    perspectiveRender.drawMesh(*vboMesh);
  //  return;
    
	
	bindTexture(texture);
	drawMesh(mesh);
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
