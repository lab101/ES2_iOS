//
//  textureRender.cpp
//  CinderES2
//
//  Created by Kris Meeusen on 15/02/13.
//  Copyright (c) 2013 Kris Meeusen. All rights reserved.
//

#include "TextureRender.h"
#include "shaderLoader.h"
#include "checkError.h"


using namespace ci;

TextureRender* TextureRender::instance;


TextureRender* TextureRender::Instance(){
    if(instance == NULL)
	{
		instance = new TextureRender();
		instance->setup();
	}
    return instance;
}


TextureRender::TextureRender(){
	isSetup = false;
}


void TextureRender::setup(){
	const char vShaderStr[] =
    "attribute vec4 position;   \n"
	"attribute vec3 uv;			\n"

	"uniform mat4 modelViewProjectionMatrix;"
	"uniform mat3 normalMatrix;"
	"varying vec3 uvVarying;			\n"

    "void main()                 \n"
    "{                           \n"
    "   gl_Position = modelViewProjectionMatrix * position; \n"
	"	uvVarying.x = uv.x; \n"
	"	uvVarying.y = 1.0-uv.y; \n"
	"	uvVarying.z = uv.z; \n"

    "}                           \n";
    
    const char fShaderStr[] =
    "precision mediump float;						\n"
	"uniform sampler2D texture;						\n"
	"varying vec3 uvVarying;						\n"
	
    "void main()									\n"
    "{												\n"
    "  gl_FragColor = texture2D(texture, uvVarying.xy);		\n"
    " // gl_FragColor.a   *= uvVarying.z;						\n"
    "  gl_FragColor.xyz /= gl_FragColor.a;					\n"
    "}														\n";
	
	
    GLuint vertexShader;
    GLuint fragmentShader;
    GLint linked;
    
	
	gl2::CheckForErrors();
	
    // Load the vertex/fragment shaders
    vertexShader = loadShader( vShaderStr,GL_VERTEX_SHADER);
    fragmentShader = loadShader(fShaderStr, GL_FRAGMENT_SHADER);
	
	gl2::CheckForErrors();
	
    // Create the program object
    program = glCreateProgram();
	gl2::CheckForErrors();
	
    if(program == 0)
        return;
	
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    
    gl2::CheckForErrors();
	
    glBindAttribLocation(program, ATTRIB_VERTEX, "position");
    glBindAttribLocation(program, ATTRIB_UV, "uv");
    
	glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &linked);
    
    gl2::CheckForErrors();
	
    if(!linked)
    {
        GLint infoLen = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLen);
        
        if(infoLen > 1)
        {
            char* infoLog = (GLchar *) malloc(sizeof(char) * infoLen);
            glGetProgramInfoLog(program, infoLen, NULL, infoLog);
            std::cout << " !! " <<  infoLog << std::endl;
            gl2::CheckForErrors();
			
            free(infoLog);
        }
        return;
    }else{
		glUseProgram(program);
		
		uWorldMatrix= glGetUniformLocation(program, "modelViewProjectionMatrix");
		//utexture = glGetUniformLocation(program, "vtexture");
		
	}
	
	
	isSetup = true;
	gl2::CheckForErrors();
    
	
}



void TextureRender::setCameraMatrix(ci::Matrix44f worldMatrix){
	glUseProgram(program);
	glUniformMatrix4fv(uWorldMatrix, 1, 0,worldMatrix.m);
	glUseProgram(0);
	
}


void TextureRender::bindTexture(const ci::gl::Texture &texture)
{
    texture.bind();
	gl2::CheckForErrors();
}

void TextureRender::unbindTexture(const ci::gl::Texture &texture)
{
    texture.unbind();
	gl2::CheckForErrors();
}



void TextureRender::setLineWidth(const float width){
	glLineWidth(width);
	
}


void TextureRender::drawMesh(const ci::TriMesh mesh){
	drawMesh(mesh,GL_TRIANGLES);
}


void TextureRender::drawLine(const ci::Vec3f &start,const ci::Vec3f &end){
	glUseProgram(program);
	
	ci::TriMesh mesh;
	mesh.appendVertex(start);
	mesh.appendVertex(end);
	
	drawMesh(mesh, GL_LINE_LOOP);
	glUseProgram(0);
	
}

void TextureRender::drawTexture(const ci::gl::Texture& texture){

//    ci::TriMesh mesh;
//
//    mesh.appendVertex(Vec3f(100,500,-0.1));
//    mesh.appendVertex(Vec3f(10,0,-0.1));
//    mesh.appendVertex(Vec3f(310,0,-0.1));
//    
//	// not implemented
//    //    mesh.appendColorRGB(Color(1,1,0));
//    //    mesh.appendColorRGB(Color(1,0,1));
//    //    mesh.appendColorRGB(Color(1,0,1));
//	
//	mesh.appendTexCoord(Vec2f(1,1));
//	mesh.appendTexCoord(Vec2f(0,0));
//	mesh.appendTexCoord(Vec2f(1,0));

    
}


void TextureRender::drawMesh(const ci::TriMesh mesh,GLint shape){


	glUseProgram(program);
	glVertexAttribPointer(ATTRIB_VERTEX, 3, GL_FLOAT, GL_FALSE, 0, &(mesh.getVertices()[0]));
    glEnableVertexAttribArray(ATTRIB_VERTEX);
	
	
	gl2::CheckForErrors();

	
	glVertexAttribPointer(ATTRIB_UV, 2, GL_FLOAT, GL_FALSE, 0, &mesh.getTexCoords()[0]);
	glEnableVertexAttribArray(ATTRIB_UV);

	gl2::CheckForErrors();

    glDrawArrays(shape, 0, mesh.getNumVertices());
	gl2::CheckForErrors();

	glDisableVertexAttribArray(ATTRIB_VERTEX);
	glDisableVertexAttribArray(ATTRIB_UV);


	glUseProgram(0);
	//glDisable  (GL_BLEND);

	
	gl2::CheckForErrors();

}


void TextureRender::drawSprite(uiSprite& sprite){
	if(!sprite.isTextureLoaded) return;
	glUseProgram(program);

	
	bindTexture(sprite.getTexture());
	//sprite.getTexture().bind();
	//  std::cout << "id from sprite obj " << sprite.getTexture().getId() << "\n-----\n"  << std::endl;
	
    
    //std::cout << sprite.getTexture().getId();
	GLfloat *pointer = sprite.data;
    glVertexAttribPointer(ATTRIB_VERTEX, 3, GL_FLOAT, 0, 6 * sizeof(GLfloat), pointer);
	glEnableVertexAttribArray(ATTRIB_VERTEX);

    pointer +=3;
    glVertexAttribPointer(ATTRIB_UV, 3, GL_FLOAT, 0, 6 * sizeof(GLfloat), pointer);
	glEnableVertexAttribArray(ATTRIB_UV);

    
    glDrawArrays(GL_TRIANGLES, 0, 6);
	sprite.getTexture().unbind();
	
	glDisableVertexAttribArray(ATTRIB_VERTEX);
	glDisableVertexAttribArray(ATTRIB_UV);

	glUseProgram(0);
	//glDisable  (GL_BLEND);
	
	
	gl2::CheckForErrors();


}


