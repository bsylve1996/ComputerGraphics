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
const double PI  = 3.141592653589793238463;
//int radius = 150;

struct Point {
	GLint x;
	GLint y;
};

Point pC = {256, 256};
GLint radius = 150;

// radius of the needles from  the center
GLint hRadius = 120;
GLint mRadius = 130;
GLint sRadius = 140;

// angles of the three needles
double hDegree = 0;
double mDegree = 0;
double sDegree = 0;

void reshape(int w, int h) {
    
    glViewport(0, 0, w, h);       /* Establish viewing area to cover entire window. */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, w, 0, h, -1, 1);
    glScalef(1, -1, 1);
    glTranslatef(0, -h, 0);
}

void drawFilledCircle(GLfloat x, GLfloat y){
	int i;
	int triangleAmount = 360; //# of triangles used to draw circle
	
	//GLfloat radius = 0.8f; //radius
	GLfloat twicePi = 2.0f * PI;
	
	glBegin(GL_TRIANGLE_FAN);
		glVertex2f(x, y); // center of circle
		for(i = 0; i <= triangleAmount;i++) { 
			glVertex2f(
		        x + (radius * cos(i *  twicePi / triangleAmount)), 
			    y + (radius * sin(i * twicePi / triangleAmount))
			);
		}
	glEnd();
}
/*
void tickMarks(GLfloat x, GLfloat y){
    glPushMatrix();
    glTranslatef(10.0, 10.0, 0.0);
    glColor3f(0.2,0.2,0.2);
    glLineWidth(2);
    for(int angle=0; angle <= 360; angle +=30) {
        glBegin(GL_LINES);
        printf("Angle: %d\n", angle);

        if(angle == 0.0 || angle==90.0 || angle == 180.0 || angle == 270.0 || angle == 360.0 ) {
            glColor3f(1.0,0.2,0.1);
            glVertex2f(cos(angle * PI/180.0f)* (radius-1.2), sin(angle * PI/180.0f) * (radius-1.2));
            glVertex2f(cos(angle * PI/180.0f)* radius, sin(angle * PI/180.0f) * radius);
        }
        else {
            glColor3f(0.2,0.2,0.2);
            glVertex2f(cos(angle * PI/180.0f)* (radius-0.5), sin(angle * PI/180.0f) * (radius-0.5));
            glVertex2f(cos(angle * PI/180.0f)* radius, sin(angle * PI/180.0f) * radius);
        }
        glEnd();
    }
    glPopMatrix();
}
*/

void draw_dda(Point p1, Point p2) {
	GLfloat dx = p2.x - p1.x;
	GLfloat dy = p2.y - p1.y;

	GLfloat x1 = p1.x;
	GLfloat y1 = p1.y;

	GLfloat step = 0;

	if(abs(dx) > abs(dy)) {
		step = abs(dx);
	} else {
		step = abs(dy);
	}

	GLfloat xInc = dx/step;
	GLfloat yInc = dy/step;

	for(float i = 1; i <= step; i++) {
		glVertex2i(x1, y1);
		x1 += xInc;
		y1 += yInc;
	}
}
void init() {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(0.0f, 0.0f, 0.0f);
	glPointSize(1.0f);
	gluOrtho2D(0.0f, 640.0f, 0.0f, 480.0f);
}
void display(void) {
    
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Insert your own code here
    	// Terminal Points for Needle
	Point pHour, pMinute, pSecond;

	pHour.y = pC.y + (hRadius * sin(hDegree));
	pHour.x = pC.x + (hRadius * cos(hDegree));

	pMinute.y = pC.y + (mRadius * sin(mDegree));
	pMinute.x = pC.x + (mRadius * cos(mDegree));

	pSecond.y = pC.y + (sRadius * sin(sDegree));
	pSecond.x = pC.x + (sRadius * cos(sDegree));

	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);
	glColor3f(1.0, 0.0, 1.0);
    drawFilledCircle(win_H/2,win_W/2);
	glColor3f(1.0, 0.0, 0.0);
	draw_dda(pC, pHour);

	glColor3f(0.0, 1.0, 0.0);
	draw_dda(pC, pMinute);

	glColor3f(0.0, 0.0, 1.0);
	draw_dda(pC, pSecond);
	glEnd();
	glFlush();

	mDegree -= 0.001333333;
	sDegree -= 0.08;
	hDegree -= 0.0002733333;
    //tickMarks(win_H/2,win_W/2);

    // Your code ends here
    
    glutSwapBuffers(); // swap the back buffer to front
    
    
}

void TimeEvent(int time_val) {
    time(&timer); // get the current date and time from system
    //localtime_s(&curr_time, &timer); // windows
    localtime_r(&timer, &curr_time);  //  linux
    glutPostRedisplay();
    glutTimerFunc(30, TimeEvent, 1);// By using a timed event, your application should run at the same speed on any machine.
}

int main(int argc, char **argv) {
    GLenum type;
    
    glutInit(&argc, argv);
    
    type = GLUT_DEPTH;
    type |= GLUT_RGB;
    type |= GLUT_DOUBLE;
    glutInitDisplayMode(type);
    
    time(&timer); // get current date and time
    //localtime_s(&curr_time, &timer); // windows
    localtime_r(&timer, &curr_time);  //  linux
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