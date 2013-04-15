//
//  VboMesh.cpp
//  CinderES2
//
//  Created by Kris Meeusen on 12/04/13.
//  Copyright (c) 2013 Kris Meeusen. All rights reserved.
//

#include "VboMesh.h"

using namespace ci;



VboMesh::VboMesh(ci::TriMesh mesh){
	
	GLuint VertexArrayID;
	glGenVertexArraysOES(1, &VertexArrayID);
	glBindVertexArrayOES(VertexArrayID);
	// Generate 1 buffer, put the resulting identifier in vertexbuffer
	glGenBuffers(1, &vertexbuffer);
	
	// The following commands will talk about our 'vertexbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	
	
	
	GLfloat g_vertex_buffer_data[mesh.getNumVertices()*3];//
    
    int i = 0;
    for (std::vector<Vec3f>::const_iterator it = mesh.getVertices().begin(); it != mesh.getVertices().end(); ++it) {
        g_vertex_buffer_data[i] = it->x;
        g_vertex_buffer_data[i +1] = it->y;
        g_vertex_buffer_data[i +2] = it->z;
        i+=3;
    }
    
//	{
//		-1.0f, -1.0f, 0.0f,
//		1.0f, -1.0f, 0.0f,
//		0.0f,  1.0f, 0.0f,
//	};
	// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);


}
