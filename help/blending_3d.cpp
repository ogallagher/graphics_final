/*  

Adapted from the given blending example, as a reference for defining
material properties.

*/


#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#include <cstdlib>


GLfloat xangle=0;
GLfloat yangle=0;
GLfloat zangle=0;


GLfloat mat_ambient[] =  { 0.0 , 0.0 , 0.0 , 1.0 };
GLfloat mat_diffuse[] =  { 0.0 , 0.0 , 0.0 , 1.0 };
GLfloat mat_specular[] = { 0.5 , 0.5 , 0.5 , 1.0 };
GLfloat mat_shininess[] = { 32 };


void myInit()
{
    // Enable drawing features that we need
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glShadeModel(GL_SMOOTH);

	GLfloat light_position[] = {1,1,1,1};
	GLfloat light_diffuse[] = {1.0,1.0,1.0,1.0};
	GLfloat light_ambient[] = {0.2,0.2,0.2,1.0};
	GLfloat light_specular[] = {1.0,1.0,1.0,1.0};

	// assign the above properties to light source 0
	glLightfv(GL_LIGHT0 , GL_POSITION , light_position);
	glLightfv(GL_LIGHT0 , GL_DIFFUSE , light_diffuse);
	glLightfv(GL_LIGHT0 , GL_AMBIENT , light_ambient);
	glLightfv(GL_LIGHT0 , GL_SPECULAR , light_specular);


}

void reshape (GLint w, GLint h) 
{
	glViewport(0,0,w,h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30, (double) w/h , 0.1 , 10);
	
	glMatrixMode(GL_MODELVIEW);
}


void keyboard(unsigned char key, GLint x, GLint y)
{
	switch (key)
	{
        case 'x':
                xangle+=5;
                break;
        case 'y':
                yangle+=5;
                break;
        case 'z':
                zangle+=5;
                break;
		case 'q':
				exit(0);
				break;
		case 'Q':
				exit(0);
				break;
	}

        
	glutPostRedisplay();

	return;
}


void display()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(0,0,5,0,0,0,0,1,0);

	glRotatef(xangle, 1, 0, 0);
	glRotatef(yangle, 0, 1, 0);
	glRotatef(zangle, 0, 0, 1);

	// Clear the window to black 
    glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// ice cube
	mat_ambient[0]=0.0 ; mat_ambient[1]=0.0 ; mat_ambient[2]=0.0; mat_ambient[3]=0.5;
	mat_diffuse[0]=0.01 ; mat_diffuse[1]=0.01 ; mat_diffuse[2]=0.01; mat_diffuse[3]=0.5;
	mat_specular[0]=0.5; mat_specular[1]=0.5; mat_specular[2]=0.5; mat_specular[3]=0.5;
	mat_shininess[0]=32;

	// assign the material properties
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

	// render the cube (which will be inside the teapot)
    glutSolidCube(0.5);

	// turn on blending
	glEnable( GL_BLEND );

	// make depth buffer read-only, so translucent objects are blended with opaque objects, if they are closer to the viewer
	glDepthMask( GL_FALSE );

	// choose the blending
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	//material properties for the translucent teapot
	mat_ambient[0]=0.329412 ; mat_ambient[1]=0.223529 ; mat_ambient[2]=0.027451; mat_ambient[3]=0.6;
	mat_diffuse[0]=0.0 ; mat_diffuse[1]=0.8 ; mat_diffuse[2]=0.8; mat_diffuse[3]=0.6;
	mat_specular[0]=0.992157; mat_specular[1]=0.941176; mat_specular[2]=0.907843; mat_specular[3]=0.15;
	mat_shininess[0]=100;

	// apply material properties
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    // render the teapot
    glutSolidTeapot(1.0);

	// toggle depth buffer back to read-write
	glDepthMask( GL_TRUE );

	// turn off blending
    glDisable( GL_BLEND );


	glutSwapBuffers();
}

int main (int argc , char **argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400,400);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Blending");
	myInit();
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(reshape);
	glutMainLoop();

	return 0;
}