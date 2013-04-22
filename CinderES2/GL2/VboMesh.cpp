//
//  VboMesh.cpp
//  CinderES2
//
//  Created by Kris Meeusen on 12/04/13.
//  Copyright (c) 2013 Kris Meeusen. All rights reserved.
//

#include "VboMesh.h"

using namespace ci;


bool VboMesh::hasTexCoords(){
	return mHasTexCoords;
}

int VboMesh::getStride(){
	return mStride;
}



VboMesh::VboMesh(ci::TriMesh mesh){
	
	mHasTexCoords = false;
	
	
	GLuint VertexArrayID;
	glGenVertexArraysOES(1, &VertexArrayID);
	glBindVertexArrayOES(VertexArrayID);
	// Generate 1 buffer, put the resulting identifier in vertexbuffer
	glGenBuffers(1, &vertexbuffer);
	
	// The following commands will talk about our 'vertexbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	
	
	
	mStride  = 3;
	if(mesh.hasTexCoords()){ mStride += 3; mHasTexCoords = true;}
	if(mesh.hasColorsRGBA()) mStride += 4;
	if(mesh.hasNormals()) mStride += 2;
	
	GLfloat g_vertex_buffer_data[mesh.getNumVertices()*mStride];

    
    int i = 0;
    for (std::vector<Vec3f>::const_iterator it = mesh.getVertices().begin(); it != mesh.getVertices().end(); ++it) {
//		std::cout << i  << ":" <<  it->x << std::endl;
//		std::cout << i +1<< ":" <<  it->y << std::endl;
//		std::cout << i +2 << ":" <<  it->z << std::endl;

        
		g_vertex_buffer_data[i] = it->x;
        g_vertex_buffer_data[i +1] = it->y;
        g_vertex_buffer_data[i +2] = it->z;
        i+=mStride;
    }
	
	
	i = 3;
    for (std::vector<Vec2f>::const_iterator it = mesh.getTexCoords().begin(); it != mesh.getTexCoords().end(); ++it) {
//		std::cout << i  << ":" <<  it->x << std::endl;
//		std::cout << i +1 << ":" <<  it->y << std::endl;
		
        
		g_vertex_buffer_data[i] = it->x;
        g_vertex_buffer_data[i +1] = it->y;
        g_vertex_buffer_data[i +2] = 1;
        i+=mStride;
		
    }

    
//	{
//		-1.0f, -1.0f, 0.0f,
//		1.0f, -1.0f, 0.0f,
//		0.0f,  1.0f, 0.0f,
//	};
	// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);


}
