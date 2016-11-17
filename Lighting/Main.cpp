#include <stdlib.h>
#include <math.h>
#include <Windows.h>
#include <GL/GL.h>
#include <GL/GLU.h>
#include <GL/glut.h>

using namespace std;

// global variables for positioning camera based on mouse movement
GLfloat eyex, eyey, eyez;
GLfloat vAngle, hAngle;

// init callback
void myInit(void) {
	glShadeModel(GL_SMOOTH);
	glEnable(GL_NORMALIZE);

	glClearColor(0.0, 0.0, 0.0, 0.0);	// background color: black
	glColor3f(1.0f, 1.0f, 0.0f);		// drawing color: white
	glLineWidth(10.0);					// a line is 5 pixels wide

	glMatrixMode(GL_PROJECTION);		// set matrix mode
	glLoadIdentity();					// load identity matrix

	glOrtho(-50.0, 50.0, -50.0, 50.0, -50.0, 50.0);	// orthographic mapping

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

	GLfloat mat_shininess = { .5 };
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);

	for (x = -1; x < 1; x = x + 0.1) {
		for (y = -1; y < 1; y = y + 0.1) {
			glBegin(GL_POLYGON);
				glVertex3f(x, y, 1);
				glVertex3f(x + 0.1, y, 1);
				glVertex3f(x + 0.1, y + 0.1, 1);
				glVertex3f(x, y + 0.1, 1);
			glEnd();
		}
	}

}

// calculates where camera should be positioned
void eyeAt(GLfloat r) {
	eyez = r * sin(vAngle) * cos(hAngle);
	eyex = r * sin(vAngle) * sin(hAngle);
	eyey = r * cos(vAngle);
}

// display callback
void display() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear screen to bg color

	eyeAt(1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eyex, eyey, eyez, 0, 0, 0, 0, 1, 0);

	GLfloat light_ambient[] = { .5, .5, .5, 1 };
	GLfloat light_diffuse[] = { .5, .5, .5, 1 };
	GLfloat light_specular[] = { .5, .5, .5, 1 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

	GLfloat light_position[] = { 0, 0, 0, 1 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.0);

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);

	
	glPushMatrix();
	glNormal3f(0, 0, -1);
	glTranslatef(1.0, 1.0, 25.0);
	glScalef(25.0, 25.0, 1);
	plane();
	glPopMatrix();

	
	glPushMatrix();
	glNormal3f(1, 0, 0);
	glTranslatef(1.0, 1.0, 25.0);
	glRotatef(90.0, 0, 1, 0);
	glTranslatef(1.0, 1.0, 25.0);
	glScalef(25.0, 25.0, 1);
	plane();
	glPopMatrix();

	glPushMatrix();
	glNormal3f(-1, 0, 0);
	glTranslatef(1.0, 1.0, 25.0);
	glRotatef(-90.0, 0, 1, 0);
	glTranslatef(1.0, 1.0, 25.0);
	glScalef(25.0, 25.0, 1);
	plane();
	glPopMatrix();

	glPushMatrix();
	glNormal3f(0, -1, 0);
	glTranslatef(1.0, 1.0, 25.0);
	glRotatef(90.0, 1, 0, 0);
	glTranslatef(1.0, 1.0, 25.0);
	glScalef(25.0, 25.0, 1);
	plane();
	glPopMatrix();

	glPushMatrix();
	glNormal3f(0, 1, 0);
	glTranslatef(1.0, 1.0, 25.0);
	glRotatef(-90.0, 1, 0, 0);
	glTranslatef(1.0, 1.0, 25.0);
	glScalef(25.0, 25.0, 1);
	plane();
	glPopMatrix();

	glutSwapBuffers();	// draw to screen
}

// reshape callback
void reshape(int w, int h) {

	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (w <= h) {
		glOrtho(-50.0, 50.0, -50.0 * (GLfloat)h / (GLfloat)w, 50.0 * (GLfloat)h / (GLfloat)w, -50.0, 50.0);
	}
	else {
		glOrtho(-50.0 * (GLfloat)w / (GLfloat)h, 50.0 * (GLfloat)w / (GLfloat)h, -50.0, 50.0, -50.0, 50.0);
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}

// mouse movement callback
void mouse(int x, int y) {

	hAngle = (360.0 / glutGet(GLUT_WINDOW_WIDTH) * (x + 1)); // 360 degrees
	vAngle = (180.0 / glutGet(GLUT_WINDOW_HEIGHT) * (y + 1)); // 180 degrees
	hAngle = hAngle * 0.017453;
	vAngle = vAngle * 0.017453;

	glutPostRedisplay();
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
	glutMotionFunc(mouse);

	glMatrixMode(GL_PROJECTION);

	glutMainLoop();


}