#include "Mountain.h"
#include "TextureLoader.h"


using namespace std;
using namespace glm;


#pragma region Geometry data to setup VBOs for rendering - use triangles not quads here

static float positions[] = {

	-0.5f, 0.0f,
	0.0f, 1.0f,
	0.5f, 0.0f,
	0.5f, 0.5f,
	1.0f, 0.0f
	
};

static float texCoords[] = {

	0.0f, 0.0f,
	0.33f, 1.0f,
	0.66f, 0.0f,
	0.66f, 0.5f,
	1.0f, 0.0f

};

// Indices for 2 triangles
static GLuint indices[] = { 0, 1, 2, 0, 3, 4 };

#pragma endregion

MountainousScene::MountainousScene(){}

// Initialisation, update (called per-frame) and render functions...

// Initialise planet system with given properties for size and orbit distance / speed.
void MountainousScene::initialise(float mountainScale) {

	// Load textures
	// Textures from Master of Orion II: Battle at Antares (https://www.spriters-resource.com/pc_computer/masteroforioniibattleatantares/sheet/206151/)
	mountainTexture = loadTexture(string("Assets\\Textures\\planet01.png"), FIF_PNG);


	// Setup VBOs for geometry
	glGenBuffers(1, &posVBO);
	glBindBuffer(GL_ARRAY_BUFFER, posVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

	glGenBuffers(1, &texCoordVBO);
	glBindBuffer(GL_ARRAY_BUFFER, texCoordVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(texCoords), texCoords, GL_STATIC_DRAW);

	glGenBuffers(1, &indicesVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesVBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Unbind buffers once done
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	this->mountainScale = mountainScale;
}
	
	void MountainousScene::render(mat4 currentTransform) {

		// Enable Texturing
		glEnable(GL_TEXTURE_2D);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// Setup VBOs ready for rendering
		glBindBuffer(GL_ARRAY_BUFFER, posVBO);
		glVertexPointer(2, GL_FLOAT, 0, (GLvoid*)0);

		glBindBuffer(GL_ARRAY_BUFFER, texCoordVBO);
		glTexCoordPointer(2, GL_FLOAT, 0, (GLvoid*)0);

		// Bind (and leave bound) the index array for drawing
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesVBO);

		// Declare which arrays are needed for the semi-circle object
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);

		glBindTexture(GL_TEXTURE_2D, mountainTexture);
		
		glLoadMatrixf((GLfloat*)&currentTransform);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (GLvoid*)0);


		// Unbind buffers once done
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}