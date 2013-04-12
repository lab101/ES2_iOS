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
	
	
	// An array of 3 vectors which represents 3 vertices
//	g_vertex_buffer_data = new GLfloat[9];
//	
//	g_vertex_buffer_data[0]= -100.0f;
//	g_vertex_buffer_data[1]= -100.0f;
//	g_vertex_buffer_data[2]= 0;
//	g_vertex_buffer_data[3]= 100.0f;
//	g_vertex_buffer_data[4]= -100.0;
//	g_vertex_buffer_data[5]= 0;
//	g_vertex_buffer_data[6]= 0;
//	g_vertex_buffer_data[7]= 100.0f;
//	g_vertex_buffer_data[8]= 0;
	
	
	GLfloat g_vertex_buffer_data[] = {
		0.0f, -0.0f, 0.0f,
		200.0f, -0.0f, 0.0f,
		0.0f,  200.0f, 0.0f,
	};
//	{
//		-1.0f, -1.0f, 0.0f,
//		1.0f, -1.0f, 0.0f,
//		0.0f,  1.0f, 0.0f,
//	};
	// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);


}
