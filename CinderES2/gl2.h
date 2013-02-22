//
//  gl2.h
//  CinderES2
//
//  Created by Kris Meeusen on 22/02/13.
//  Copyright (c) 2013 Kris Meeusen. All rights reserved.
//
#pragma once

#include <iostream>
#include "colorRender.h"
#include "textureRender.h"

#include "cinder/TriMesh.h"

namespace gl2 {

	inline void drawLine(const ci::Vec3f &start, const ci::Vec3f &end ){
		colorRender::Instance()->drawLine(start, end);
	}
	
	inline void setColor(const ci::ColorA color){
		colorRender::Instance()->setColor(color);
	}

	inline void setLineWidth(const float lineWidth){
		colorRender::Instance()->setLineWidth(lineWidth);
	}
	
	inline void drawMesh(const ci::TriMesh mesh){
		if(mesh.hasTexCoords()){
			textureRender::Instance()->drawMesh(mesh);
		}else{
			colorRender::Instance()->drawMesh(mesh);
		}
	}

	inline void setCamera(const ci::Matrix44f worldMatrix){
		colorRender::Instance()->setCameraMatrix(worldMatrix);
		textureRender::Instance()->setCameraMatrix(worldMatrix);
	}
	


}

