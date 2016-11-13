#include <stdlib.h>
#include <math.h>
#include <Windows.h>
#include <GL/GL.h>
#include <GL/GLU.h>
#include <GL/glut.h>

using namespace std;

// init callback
void myInit(void) {
	glClearColor(1.0, 1.0, 1.0, 1.0);	// background color: black
	glColor3f(0.0f, 0.0f, 0.0f);		// drawing color: white
	glLineWidth(2.0);					// a line is 5 pixels wide

	glMatrixMode(GL_PROJECTION);		// set matrix mode
	glLoadIdentity();					// load identity matrix
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);	// orthographic mapping

												// set up ability to track object depths
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

}

// display callback
void display() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear screen to bg color

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glutSwapBuffers();	// draw to screen
}

// reshape callback
void reshape(int w, int h) {

	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (w <= h) {
		glOrtho(-3.5, 3.5, -3.0 * (GLfloat)h / (GLfloat)w, 4.0 * (GLfloat)h / (GLfloat)w, -10.0, 10.0);
	}
	else {
		glOrtho(-3.5 * (GLfloat)w / (GLfloat)h, 3.5* (GLfloat)w / (GLfloat)h, -3.0, 4.0, -10.0, 10.0);
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}

// main method
int main(int argc, char**argv)
{
	// Basic glut setup
	glutInit(&argc, argv);										// initialize toolkit
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);	// set display mode
	glutInitWindowSize(500, 500);								// set window size
	glutInitWindowPosition(100, 100);							// set window position on screen
	glutCreateWindow("HW5");									// open screen window

	myInit();	// additional inits

				// register callback functions
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	glMatrixMode(GL_PROJECTION);

	glutMainLoop();


}