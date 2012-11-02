#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <GL/glut.h>
#include "Utils.h"


#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 640
#define LENGTH 100

/* - Menu State Identifier - */
int g_iMenuId;

/* - Mouse State Variables - */
int g_vMousePos[2] = {0, 0};
int g_iLeftMouseButton = 0;    /* 1 if pressed, 0 if not */
int g_iMiddleMouseButton = 0;
int g_iRightMouseButton = 0;

/* - SplineList Variable for the Aplication - */
//SplineList g_Splines;

Vector points[LENGTH*1000];  //store the precalculated points of the list of splines
Vector splineList[LENGTH];

int spIndex = -1;
int pIndex = 0;

/*
	myinit - Initialize circle points
*/
void myinit()
{
	/* setup gl view here */
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);  //Z buffer
}

/*
     Calculate point spline list
	 store all this data in global arrays
*/
void calcPoints()
{
	Vector P[4];
	Vector spPoint;
	float t2 = 0;
	float t3 = 0;
	int index = 0;
	float t=0;
	int pointsleft;
	//Loop all the splines
	int numberSplines = (spIndex+1)/4;
	pIndex = 0;

	P[0].x = splineList[0].x;
	P[0].y = splineList[0].y;

	P[1].x = splineList[1].x;
	P[1].y = splineList[1].y;

	P[2].x = splineList[2].x;
	P[2].y = splineList[2].y;

	P[3].x = splineList[3].x;
	P[3].y = splineList[3].y;

	//for each spline calculate the points
	for (int sp = 0; sp < numberSplines; sp++)
	{
		t = 0;
		t2 = t*t;
		t3 = t*t*t;

		//Each element calculated represents a ring in the artery
		for(float t = 0; t <= 1; t+=0.001)
		{
			t2 = t*t;
			t3 = t*t*t;

			//Calculate spline point at moment t
			spPoint.x = ((1-3*t + 3*t2 - t3) * P[0].x) + ((3*t - 6*t2 + 3*t3)*P[1].x) + ((3*t2 - 3*t3)*P[2].x) + (t3*P[3].x);
			spPoint.y = ((1-3*t + 3*t2 - t3) * P[0].y) + ((3*t - 6*t2 + 3*t3)*P[1].y) + ((3*t2 - 3*t3)*P[2].y) + (t3*P[3].y);

			//Save the points in the array structure
			points[pIndex] = spPoint;
			pIndex++;
		}

		//Move to next spline point
		//Take the first point of the next spline 
		//the last one of the previous spline.
		if(sp+1 < numberSplines){
			P[0].x = P[3].x;
			P[0].y = P[3].y;

			P[1].x = splineList[((sp+1)*4)].x;
			P[1].y = splineList[((sp+1)*4)].y;

			P[2].x = splineList[((sp+1)*4)+1].x;
			P[2].y = splineList[((sp+1)*4)+1].y;

			P[3].x = splineList[((sp+1)*4)+2].x;
			P[3].y = splineList[((sp+1)*4)+2].y;
		}
	}
}


/*
	display - Function to modify with your heightfield rendering code (Currently displays a simple cube)
*/

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	//Si tenemos suficientes puntos para dibujar
	if(spIndex >= 3)
	{
		//Calculamos la spline y dibujamos
		calcPoints();
		glBegin(GL_POINTS);
		glColor3f(1,1,1);
		for(int i=0; i<pIndex; i++)
		{
			glVertex3f(points[i].x, points[i].y, -1);
		}
		glEnd();
	}
	//draw the control points
	glBegin(GL_POINTS);
	glColor3f(0,1,0);
	for(int i=0; i<=spIndex; i++)
		glVertex3f(splineList[i].x, splineList[i].y, 0);
	glEnd();
	glutSwapBuffers ();

}

/*
	menufunc - Menu Event-handler
*/
void menufunc(int value)
{
	switch (value)
	{
	case 0: //on exit liberate resources
		exit(0);
		break;
	}
}

/*
	doIdle - The idle-function used to update the screen
*/
void doIdle()
{
	glutPostRedisplay();
}


/*
	mousebutton - Sets the global mouse states according to the actions
*/
void mousebutton(int button, int state, int x, int y)
{
	switch (button)
	{
	case GLUT_LEFT_BUTTON:
		if (state==GLUT_UP)
		{
			spIndex++;
			splineList[spIndex].x = x;
			splineList[spIndex].y = WINDOW_HEIGHT-y;
		}
		break;
	}

	g_vMousePos[0] = x;
	g_vMousePos[1] = y;
}


//Reshape function
void reshape(int width, int height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//Se utiliza GLOrtho2D ya que es una proyeccion 2d 
	//Asi podemos hacer que las coordenadas de mundo coincidan con las de pantalla
	gluOrtho2D (0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


/*
	main - The Main Function
*/
int main (int argc, char ** argv)
{	
	glutInit(&argc,argv);

	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

	glutCreateWindow("Practica 4 - José Zerpa");

	/* tells glut to use a particular display function to redraw */
	glutDisplayFunc(display);

	/* allow the user to quit using the right mouse button menu */
	g_iMenuId = glutCreateMenu(menufunc);
	glutSetMenu(g_iMenuId);
	glutAddMenuEntry("Quit",0);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutIdleFunc(doIdle);

	/* callback for mouse button changes */
	glutMouseFunc(mousebutton);

	glutReshapeFunc(reshape);

    calcPoints();

	myinit();

	glutMainLoop();
	return 0;
}
