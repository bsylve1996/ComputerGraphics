// assignment1.cpp : Defines the entry point for the console application.
// Brandon Sylve
// Clock assignment

#include <iostream>
#include <GL/glut.h>  
#include <math.h>
#include <time.h>

int win_H, win_W;
time_t timer;
struct tm curr_time;


void reshape(int w, int h) {
    
    glViewport(0, 0, w, h);       /* Establish viewing area to cover entire window. */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, w, 0, h, -1, 1);
    glScalef(1, -1, 1);
    glTranslatef(0, -h, 0);
}

void display(void) {
    
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Insert your own code here
    
    
    
    
    // Your code ends here
    
    glutSwapBuffers(); // swap the back buffer to front
    
    
}

void TimeEvent(int time_val) {
    time(&timer); // get the current date and time from system
    localtime_s(&curr_time, &timer); 
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
    localtime_s(&curr_time, &timer); 
    
    // set window size and create a window for rendering
    win_W = 512;
    win_H = 512;
    glutInitWindowSize(win_H, win_W);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("My clock");
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    
    glutTimerFunc(30, TimeEvent, 1);
    glutMainLoop();
    return 0;
}