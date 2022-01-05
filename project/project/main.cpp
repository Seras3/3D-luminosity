// Iluminare: aplicarea mecanismului la nivel de varf / de fragment
#include <windows.h>  // biblioteci care urmeaza sa fie incluse
#include <stdlib.h> // necesare pentru citirea shader-elor
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <GL/glew.h> // glew apare inainte de freeglut
#include <GL/freeglut.h> // nu trebuie uitat freeglut.h
#include "loadShaders.h"
#include "glm/glm/glm.hpp"  
#include "glm/glm/gtc/matrix_transform.hpp"
#include "glm/glm/gtx/transform.hpp"
#include "glm/glm/gtc/type_ptr.hpp"

using namespace std;

// identificatori 
GLuint
VaoId,
VboId,
ColorBufferId,
ProgramIdv,
ProgramIdf,
viewLocation,
projLocation,
codColLocation,
depthLocation,
rendermode,
codCol;
GLint objectColorLoc, lightColorLoc, lightPosLoc, viewPosLoc, myMatrixLoc;

// variabile pentru matricea de vizualizare
float Obsx = 0.0, Obsy = -600.0, Obsz = 0.f;
float Refx = 0.0f, Refy = 1000.0f, Refz = 0.0f;
float Vx = 0.0, Vy = 0.0, Vz = 1.0;

// variabile pentru matricea de proiectie
float width = 800, height = 600, znear = 0.1, fov = 45;
float PI = 3.141592;

// matrice utilizate
glm::mat4 view, projection, myMatrix, rotationMat, translationMat, scaleMat;

void processNormalKeys(unsigned char key, int x, int y)
{
	switch (key) {
	case 'l':
		Vx -= 0.1;
		break;
	case 'r':
		Vx += 0.1;
		break;
	case '+':
		Obsy += 10;
		break;
	case '-':
		Obsy -= 10;
		break;
	}
	if (key == 27)
		exit(0);
}
void processSpecialKeys(int key, int xx, int yy)
{
	switch (key) {
	case GLUT_KEY_LEFT:
		Obsx -= 20;
		break;
	case GLUT_KEY_RIGHT:
		Obsx += 20;
		break;
	case GLUT_KEY_UP:
		Obsz += 20;
		break;
	case GLUT_KEY_DOWN:
		Obsz -= 20;
		break;
	}
}
void CreateVBO(void)
{
	// varfurile 
	GLfloat Vertices[] =
	{
		  // inspre Oz'
			-10.f, -10.f, -10.f,  -1.0f,  -1.0f, -1.0f,
			 10.f, -10.f, -10.f,  1.0f,  -1.0f, -1.0f,
			 10.f,  10.f, -10.f,  1.0f,  1.0f, -1.0f,
			 10.f,  10.f, -10.f,  1.0f,  1.0f, -1.0f,
			-10.f,  10.f, -10.f,  -1.0f,  1.0f, -1.0f,
			-10.f, -10.f, -10.f,  -1.0f,  -1.0f, -1.0f,

			// inspre Oz
			-10.f, -10.f,  10.f,  -1.0f,  -1.0f,  1.0f,
			 10.f, -10.f,  10.f,  1.0f,  -1.0f,  1.0f,
			 10.f,  10.f,  10.f,  1.0f,  1.0f,  1.0f,
			 10.f,  10.f,  10.f,  1.0f,  1.0f,  1.0f,
			-10.f,  10.f,  10.f,  -1.0f,  1.0f,  1.0f,
			-10.f, -10.f,  10.f,  -1.0f,  -1.0f,  1.0f,

			// inspre Ox'
			-10.f,  10.f,  10.f, -1.0f,  1.0f,  1.0f,
			-10.f,  10.f, -10.f, -1.0f,  1.0f,  -1.0f,
			-10.f, -10.f, -10.f, -1.0f,  -1.0f,  -1.0f,
			-10.f, -10.f, -10.f, -1.0f,  -1.0f,  -1.0f,
			-10.f, -10.f,  10.f, -1.0f,  -1.0f,  1.0f,
			-10.f,  10.f,  10.f, -1.0f,  1.0f,  1.0f,

			// inspre Ox
			 10.f,  10.f,  10.f,  1.0f,  1.0f,  1.0f,
			 10.f,  10.f, -10.f,  1.0f,  1.0f,  -1.0f,
			 10.f, -10.f, -10.f,  1.0f,  -1.0f,  -1.0f,
			 10.f, -10.f, -10.f,  1.0f,  -1.0f,  -1.0f,
			 10.f, -10.f,  10.f,  1.0f,  -1.0f,  1.0f,
			 10.f,  10.f,  10.f,  1.0f,  1.0f,  1.0f,

			 // inspre Oy'
			-10.f, -10.f, -10.f,  -1.0f, -1.0f,  -1.0f,
			 10.f, -10.f, -10.f,  1.0f, -1.0f,  -1.0f,
			 10.f, -10.f,  10.f,  1.0f, -1.0f,  1.0f,
			 10.f, -10.f,  10.f,  1.0f, -1.0f,  1.0f,
			-10.f, -10.f,  10.f,  -1.0f, -1.0f,  1.0f,
			-10.f, -10.f, -10.f,  -1.0f, -1.0f,  -1.0f,

			// inspre Oy
			-10.f,  10.f, -10.f,  -1.0f,  1.0f,  -1.0f,
			 10.f,  10.f, -10.f,  1.0f,  1.0f,  -1.0f,
			 10.f,  10.f,  10.f,  1.0f,  1.0f,  1.0f,
			 10.f,  10.f,  10.f,  1.0f,  1.0f,  1.0f,
			-10.f,  10.f,  10.f,  -1.0f,  1.0f,  1.0f,
			-10.f,  10.f, -10.f,  -1.0f,  1.0f,  -1.0f
	};

	glGenVertexArrays(1, &VaoId);
	glGenBuffers(1, &VboId);
	glBindVertexArray(VaoId);
	glBindBuffer(GL_ARRAY_BUFFER, VboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0); // atributul 0 = pozitie
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(1); // atributul 1 = normale
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
}
void DestroyVBO(void)
{
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &VboId);
	glBindVertexArray(0);
	glDeleteVertexArrays(1, &VaoId);
}
void CreateShadersVertex(void)
{
	ProgramIdv = LoadShaders("10_02v_Shader.vert", "10_02v_Shader.frag");
	glUseProgram(ProgramIdv);
}
void DestroyShaders(void)
{
	glDeleteProgram(ProgramIdv);
}
void Initialize(void)
{
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f); 
	CreateVBO();
	CreateShadersVertex();
	objectColorLoc = glGetUniformLocation(ProgramIdv, "objectColor");
	lightColorLoc = glGetUniformLocation(ProgramIdv, "lightColor");
	lightPosLoc = glGetUniformLocation(ProgramIdv, "lightPos");
	viewPosLoc = glGetUniformLocation(ProgramIdv, "viewPos");
	viewLocation = glGetUniformLocation(ProgramIdv, "view");
	projLocation = glGetUniformLocation(ProgramIdv, "projection");
	myMatrixLoc = glGetUniformLocation(ProgramIdv, "myMatrix");
}

void DrawPlank(float rotationAngle, glm::vec3 rotationAxis, glm::vec3 translation) {
	translationMat = glm::translate(glm::mat4(1.0f), translation);
	scaleMat = glm::scale(glm::mat4(1.0f), glm::vec3(10.0f, 0.5f, 2.0f));
	if (rotationAngle != 0) {

		rotationMat = glm::rotate(glm::mat4(1.0f), rotationAngle, rotationAxis);
		myMatrix = translationMat * rotationMat * scaleMat;
	}
	else {
		myMatrix = translationMat * scaleMat;
	}

	glUniformMatrix4fv(myMatrixLoc, 1, GL_FALSE, &myMatrix[0][0]);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}



void DrawBench() {
	// de jos
	DrawPlank(0.f, glm::vec3(0.f ,0.f, 0.f), glm::vec3(0, -50, -50));
	DrawPlank(0.f, glm::vec3(0.f, 0.f, 0.f), glm::vec3(0, -50,   0));
}

void RenderFunction(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glm::vec3 Obs = glm::vec3(Obsx, Obsy, Obsz);
	glm::vec3 PctRef = glm::vec3(Refx, Refy, Refz);
	glm::vec3 Vert = glm::vec3(Vx, Vy, Vz);
	view = glm::lookAt(Obs, PctRef, Vert);
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);
	projection = glm::infinitePerspective(fov, GLfloat(width) / GLfloat(height), znear);
	glUniformMatrix4fv(projLocation, 1, GL_FALSE, &projection[0][0]);

	// Variabile uniforme pentru iluminare
	glUniform3f(objectColorLoc, 1.0f, 0.5f, 0.4f);
	glUniform3f(lightColorLoc, 1.0f, 1.0f, 1.0f);
	glUniform3f(lightPosLoc, 400.f, -400.f, 400.f);
	glUniform3f(viewPosLoc, Obsx, Obsy, Obsz);

	DrawBench();

	glutSwapBuffers();
	glFlush();
}
void Cleanup(void)
{
	DestroyShaders();
	DestroyVBO();
}
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(1200, 900);
	glutCreateWindow("3D Luminosity");
	glewInit();
	Initialize();
	glutIdleFunc(RenderFunction);
	glutDisplayFunc(RenderFunction);
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(processSpecialKeys);
	glutCloseFunc(Cleanup);
	glutMainLoop();

}

