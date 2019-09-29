// assignment1.cpp : Defines the entry point for the console application.
// Brandon Sylve
// Clock assignment 

#include <iostream>
#include <GL/glut.h>  
#include <math.h>
#include <time.h>

int win_W = 512;
int win_H = 512;
time_t timer;
struct tm curr_time;
GLint radius = 150;
const double PI = 3.141592653589793;
int colorAngle = 50;
float one, two, three;

void reshape(int w, int h) {
	glViewport(0, 0, w, h);       // Establish viewing area to cover entire window. 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, w, 0, h, -1, 1);
	glScalef(1, -1, 1);
	glTranslatef(0, -h, 0);
}

void drawFilledCircle(GLfloat x, GLfloat y) {
	int i;
	int triangleAmount = 360; //# of triangles used to draw circle

	//GLfloat radius = 0.8f; //radius
	GLfloat twicePi = 2.0f * PI;

	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x, y); // center of circle
	for (i = 0; i <= triangleAmount; i++) {
		glVertex2f(
			x + (radius * cos(i * twicePi / triangleAmount)),
			y + (radius * sin(i * twicePi / triangleAmount))
		);
	}
	glEnd();
}


void drawHourHand() {
	double hourDegrees = curr_time.tm_hour * 30.0 + curr_time.tm_min / 2.0 + curr_time.tm_sec / 120.0;
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(256, 256, 0);
	glRotatef(hourDegrees, 0.0f, 0.0f, 1.0f);
	glTranslatef(-256, -256, 0);
	glBegin(GL_LINES);
		glLineWidth(100);
		glVertex2f(256, 256);
		glVertex2f(256, 190);
	glEnd();
	glPopMatrix();
}

void drawMinuteHand() {
	double minuteDegrees = curr_time.tm_min * 6.0 + curr_time.tm_sec / 10.0;
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(256, 256, 0);
	glRotatef(minuteDegrees, 0.0f, 0.0f, 1.0f);
	glTranslatef(-256, -256, 0);
	glBegin(GL_LINES);
		glLineWidth(100);
		glVertex2f(256, 256);
		glVertex2f(256, 130);
	glEnd();
	glPopMatrix();
}

void drawSecondHand() {
	double secDegrees = curr_time.tm_sec * 6.0;
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(256, 256, 0);
	glRotatef(secDegrees, 0.0f, 0.0f, 1.0f);
	glTranslatef(-256, -256, 0);
	glBegin(GL_LINES);
		glLineWidth(100);
		glVertex2f(256,256);
		glVertex2f(256, 120);
	glEnd();
	glPopMatrix();
}

void display(void) {/*
	glClear(GL_COLOR_BUFFER_BIT);
	if (colorAngle % 50 == 0) {
		one = (float)sin(colorAngle) * 0.5f + 0.5f;
		two = (float)cos(colorAngle) * 0.5f + 0.5f;
		three = (one + two) / 2;
		glColor3f(one, two, three);
	}
	else*/
		//glColor3f(one, two, three);
	glColor3f(1.0, 1.0, 1.0);
	colorAngle++;
	drawFilledCircle(win_H / 2, win_W / 2);
	
	
	glColor3f(0.0, 0.0, 1.0);
	drawSecondHand();
	glColor3f(0.0, 0.5, 1.0);
	drawMinuteHand();
	glColor3f(1.0, 0.0, 1.0);
	drawHourHand();
	
	glutSwapBuffers(); // swap the back buffer to front
}

void TimeEvent(int time_val) {
	time(&timer); // get the current date and time from system
	localtime_s(&curr_time, &timer); // windows
	//localtime_r(&timer, &curr_time);  //  linux
	glutPostRedisplay();
	glutTimerFunc(30, TimeEvent, 1);// By using a timed event, your application should run at the same speed on any machine.
}

int main(int argc, char** argv) {
	GLenum type;

	glutInit(&argc, argv);

	type = GLUT_DEPTH;
	type |= GLUT_RGB;
	type |= GLUT_DOUBLE;
	glutInitDisplayMode(type);

	time(&timer); // get current date and time
	localtime_s(&curr_time, &timer); // windows
	//localtime_r(&timer, &curr_time);  //  linux

	// set window size and create a window for rendering
	glutInitWindowSize(win_H, win_W);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("My clock");

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutTimerFunc(30, TimeEvent, 1);
	glutMainLoop();
	return 0;
}
