#pragma once

#include "core.h"




class MountainousScene {

	GLuint		mountainTexture;
	

	GLuint		posVBO;
	GLuint		texCoordVBO;
	GLuint		indicesVBO;

	float		mountainScale;
public:

	// Constructor
	MountainousScene();

	// Initialisation, update (called per-frame) and render functions
	void initialise(float mountainScale);
	void update();
	void render(glm::mat4 currentTransform);
};