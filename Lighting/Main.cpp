#include <stdlib.h>
#include <math.h>
#include <Windows.h>
#include <GL/GL.h>
#include <GL/GLU.h>
#include <GL/glut.h>

using namespace std;

// init callback
void myInit(void) {
	glClearColor(0.0, 0.0, 0.0, 0.0);	// background color: black
	glColor3f(1.0f, 1.0f, 0.0f);		// drawing color: white
	glLineWidth(2.0);					// a line is 5 pixels wide

	glMatrixMode(GL_PROJECTION);		// set matrix mode
	glLoadIdentity();					// load identity matrix
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);	// orthographic mapping

												// set up ability to track object depths
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

}

void plane() {

	GLfloat x, y;

	GLfloat mat_ambient[] = { 0, 0, 0, 1 };
	GLfloat mat_diffuse[] = { 0, 0, 0, 1 };
	GLfloat mat_specular[] = { 1, 1, 0, 1 };

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);

	GLfloat mat_shininess = { 10.0 };
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);

	for (x = -1; x < 1; x = x + 0.1) {
		for (y = -1; y < 1; y = y + 0.1) {
			glBegin(GL_POLYGON);
			glNormal3f(0, 0, 1);
			//glNormal3f(-x, -y, 1);
			glVertex3f(x, y, 0);
			glVertex3f(x + 0.1, y, 0);
			glVertex3f(x + 0.1, y + 0.1, 0);
			glVertex3f(x, y + 0.1, 0);
			glEnd();
		}
	}

}

// display callback
void display() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear screen to bg color

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	GLfloat light_ambient[] = { 0.5, 0.5, 0.5, 1 };
	GLfloat light_diffuse[] = { 0.5, 0.5, 0.5, 1 };
	GLfloat light_specular[] = { .8, .8, .8, 1 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

	GLfloat light_position[] = { 0, 0, 2, 1 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.0);

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);

	plane();

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