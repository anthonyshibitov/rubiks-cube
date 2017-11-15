//test
#ifdef _WIN32
#include <windows.h>
#endif

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/glui.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#ifndef _WIN32
#include <unistd.h>
#else
void usleep(unsigned int nanosec)
{
	Sleep(nanosec / 1000);
}
#endif


// *************** GLOBAL VARIABLES *************************


const float PI = 3.14159;

// --------------- USER INTERFACE VARIABLES -----------------

// Window settings
int windowID;               // Glut window ID (for display)
GLUI *glui;                 // Glui window (for controls)
int Win[2];                 // window (x,y) size


							// ---------------- ANIMATION VARIABLES ---------------------

							// Animation settings
int animate_mode = 0;       // 0 = no anim, 1 = animate
int animation_frame = 0;      // Specify current frame of animation

							  // Joint parameters
const float JOINT_MIN_X = -180.0f;
const float JOINT_MAX_X = 180.0f;
const float JOINT_MIN_Y = -180.0f;
const float JOINT_MAX_Y = 180.0f;
const float JOINT_MIN_Z = -180.0f;
const float JOINT_MAX_Z = 180.0f;
float joint_rot_x = 0.0f;
float joint_rot_y = 0.0f;
float joint_rot_z = 0.0f;

float rotate_clockwise = 0.0f;
float rotate_counterclockwise = 0.0f;


//////////////////////////////////////////////////////
// TODO: Add additional joint parameters here
//////////////////////////////////////////////////////


struct Color
{
	float r, g, b;
};

Color red = { 1.0 , 0.0, 0.0 };
Color yellow = { 1.0 , 1.0, 0.0 };
Color orange = { 1.0 , 0.5, 0.0 };
Color blue = { 0.0 , 0.0, 1.0 };
Color green = { 0.0 , 0.5, 0.0 };
Color white = { 1.0 , 1.0, 1.0 };
Color black = { 0,0,0 };

// ***********  FUNCTION HEADER DECLARATIONS ****************


// Initialization functions
void initGlut(char* winName);
void initGlui();
void initGl();

void drawSubCube(Color c1, Color c2, Color c3, Color c4, Color c5, Color c6);


// Callbacks for handling events in glut
void myReshape(int w, int h);
void animate();
void display(void);

// Callback for handling events in glui
void GLUI_Control(int id);



#include <vector>

struct Vertex
{
	float x, y, z, w;
	float r, g, b, a;
};
std::vector< Vertex > verts;

void myReshape(int w, int h)
{
	// Setup projection matrix for new window
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-w / 2, w / 2, -h / 2, h / 2);

	// Update OpenGL viewport and internal variables
	glViewport(0, 0, w, h);
	Win[0] = w;
	Win[1] = h;
}

// Initialize glut and create a window with the specified caption 
void initGlut(char* winName)
{
	// Set video mode: double-buffered, color, depth-buffered
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	gluOrtho2D(-100, 100, -100, 100);
	// Create window
	glutInitWindowPosition(0, 0);

	glutInitWindowSize(Win[0], Win[1]);
	windowID = glutCreateWindow(winName);

	// Setup callback functions to handle events
	glutReshapeFunc(myReshape); // Call myReshape whenever window resized
	glutDisplayFunc(display);   // Call display whenever new frame needed 
}


// Quit button handler.  Called when the "quit" button is pressed.
void quitButton(int)
{
	exit(0);
}

// Animate button handler.  Called when the "animate" checkbox is pressed.
void animateButton(int)
{
	// synchronize variables that GLUT uses
	glui->sync_live();

	animation_frame = 0;
	if (animate_mode == 1) {
		// start animation
		GLUI_Master.set_glutIdleFunc(animate);
	}
	else {
		// stop animation
		GLUI_Master.set_glutIdleFunc(NULL);
	}
}

// Initialize GLUI and the user interface
void initGlui()
{
	GLUI_Master.set_glutIdleFunc(NULL);

	// Create GLUI window
	glui = GLUI_Master.create_glui("Glui Window", 0, Win[0] + 10, 0);

	// Create a control to specify the rotation of the joint
	//X
	GLUI_Spinner *joint_spinner_x
		= glui->add_spinner("X: ", GLUI_SPINNER_FLOAT, &joint_rot_x);
	joint_spinner_x->set_speed(0.1);
	joint_spinner_x->set_float_limits(JOINT_MIN_X, JOINT_MAX_X, GLUI_LIMIT_CLAMP);

	//Y
	GLUI_Spinner *joint_spinner_y
		= glui->add_spinner("Y: ", GLUI_SPINNER_FLOAT, &joint_rot_y);
	joint_spinner_y->set_speed(0.1);
	joint_spinner_y->set_float_limits(JOINT_MIN_Y, JOINT_MAX_Y, GLUI_LIMIT_CLAMP);
	//Z
	GLUI_Spinner *joint_spinner_z
		= glui->add_spinner("Z:" , GLUI_SPINNER_FLOAT, &joint_rot_z);
	joint_spinner_z->set_speed(0.1);
	joint_spinner_z->set_float_limits(JOINT_MIN_Z, JOINT_MAX_Z, GLUI_LIMIT_CLAMP);


/*

	GLUI_Spinner *base_y
		= glui->add_spinner("Y Direction:", GLUI_SPINNER_FLOAT, &base_trans);
	base_y->set_speed(0.1);
	base_y->set_float_limits(BASE_MIN, BASE_MAX, GLUI_LIMIT_CLAMP);

	GLUI_Spinner *base_x
		= glui->add_spinner("X Direction:", GLUI_SPINNER_FLOAT, &base_trans_x);
	base_x->set_speed(0.1);
	base_x->set_float_limits(BASE_MIN_X, BASE_MAX_X, GLUI_LIMIT_CLAMP);*/

	///////////////////////////////////////////////////////////
	// TODO: 
	//   Add controls for additional joints here
	///////////////////////////////////////////////////////////

	// Add button to specify animation mode 
	glui->add_separator();
	glui->add_checkbox("Animate", &animate_mode, 0, animateButton);

	// Add "Quit" button
	glui->add_separator();
	glui->add_button("Quit", 0, quitButton);

	// Set the main window to be the "active" window
	glui->set_main_gfx_window(windowID);
}


// Performs most of the OpenGL intialization
void initGl(void)
{
	// glClearColor (red, green, blue, alpha)
	// Ignore the meaning of the 'alpha' value for now
	glClearColor(0.7f, 0.7f, 0.9f, 1.0f);
}




// Callback idle function for animating the scene
void animate()
{
	// JOIN F
	const double joint_rot_speed_x = 0.1;
	double joint_rot_t_x = (sin(animation_frame*joint_rot_speed_x) + 1.0) / 2.0;
	joint_rot_t_x = joint_rot_t_x * JOINT_MIN_X + (1 - joint_rot_t_x) * JOINT_MAX_X;

	// JOIN R
	const double joint_rot_speed_y = 0.1;
	double joint_rot_t_y = (sin(animation_frame*joint_rot_speed_y) + 1.0) / 2.0;
	joint_rot_t_y = joint_rot_t_y * JOINT_MIN_Y + (1 - joint_rot_t_y) * JOINT_MAX_Y;

	// JOIN E
	const double joint_rot_speed_z = 0.1;
	double joint_rot_t_z = (sin(animation_frame*joint_rot_speed_z) + 1.0) / 2.0;
	joint_rot_t_z = joint_rot_t_z * JOINT_MIN_Z + (1 - joint_rot_t_z) * JOINT_MAX_Z;
	

	//// Update geometry - BASE 
	//const double base_speed = 0.1;
	//double base_trans_t = (sin(animation_frame*base_speed) + 1.0) / 2.0;
	//base_trans = base_trans_t * BASE_MIN + (1 - base_trans_t) * BASE_MAX;

	//// Update geometry - BASE 
	//const double base_x_speed = 0.1;
	//double base_trans_1 = (cos(animation_frame*base_x_speed) + 1.0) / 2.0;
	//base_trans_x = base_trans_1 * BASE_MIN_X + (1 - base_trans_1) * BASE_MAX_X;




	///////////////////////////////////////////////////////////
	// TODO:
	//   Modify this function animate the character's joints
	//   Note: Nothing should be drawn in this function!  OpenGL drawing
	//   should only happen in the display() callback.
	///////////////////////////////////////////////////////////

	// Update user interface
	glui->sync_live();

	// Tell glut window to update itself.  This will cause the display()
	// callback to be called, which renders the object (once you've written
	// the callback).


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glutSetWindow(windowID);
	glutPostRedisplay();

	// increment the frame number.
	animation_frame++;

	// Wait 50 ms between frames (20 frames per second)
	usleep(50000);
}


void fillVerts()
{
	double h = 0.01;
	double a = 10.0;
	double b = 28.0;
	double c = 8.0 / 3.0;

	Vertex cur;
	cur.a = 0.09f;

	double x0 = 0.1;
	double y0 = 0;
	double z0 = 0;
	for (unsigned int i = 0; i < 100000; i++)
	{
		if (i == 20000)
		{
			cur.r = 1.0f;
			cur.g = 0.0f;
			cur.b = 0.0f;
		}
		if (i == 40000)
		{
			cur.r = 1.0f;
			cur.g = 0.0f;
			cur.b = 1.0f;
		}
		if (i == 60000)
		{
			cur.r = 0.0f;
			cur.g = 0.0f;
			cur.b = 1.0f;
		}
		if (i == 80000)
		{
			cur.r = 0.0f;
			cur.g = 1.0f;
			cur.b = 1.0f;
		}

		const double x1 = x0 + h * a * (y0 - x0);
		const double y1 = y0 + h * (x0 * (b - z0) - y0);
		const double z1 = z0 + h * (x0 * y0 - c * z0);
		x0 = x1;
		y0 = y1;
		z0 = z1;

		if (i > 100)
		{
			cur.x = x0;
			cur.y = y0;
			cur.z = z0;
			verts.push_back(cur);
		}
	}
}

float angle = 0;
void timer(int extra)
{
	// spin
	angle += 0.5;

	glutPostRedisplay();
	glutTimerFunc(16, timer, 0);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	const double w = glutGet(GLUT_WINDOW_WIDTH);
	const double h = glutGet(GLUT_WINDOW_HEIGHT);
	gluPerspective(60.0, w / h, 1.0, 10000.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//glEnable(GL_DEPTH_TEST);
	gluLookAt(joint_rot_x, joint_rot_y, joint_rot_z - 40, 10.5, 10.5, 10.5, 0, 1, 0);


	// draw curve

	//glColor3f(1.0, 0, 0);
	//glutSolidCube(10);
	Color c1 = { 0.0 , 0.0, 1.0 };
	Color c2 = { 0.0 , 1.0, 0.0 };
	Color c3 = { 1.0 , 0.0, 0.0 };


	glRotatef(angle, 0, 0, 1);

	//bottom layer
	// front, top, back, bottom, left, right
	drawSubCube(black, black, blue, yellow, black, red);
	glTranslatef(10.5, 0, 0);
	drawSubCube(black, black, blue, yellow, black, black);
	glTranslatef(10.5, 0, 0);
	drawSubCube(black, black, blue, yellow, orange, black);

	glTranslatef(0, 10.5, 0);
	drawSubCube(black, black, blue, black, orange, black);
	glTranslatef(-10.5, 0, 0);
	drawSubCube(black, black, blue, black, black, black);
	glTranslatef(-10.5, 0, 0);
	drawSubCube(black, black, blue, black, black, red);


	glTranslatef(0, 10.5, 0);
	drawSubCube(black, white, blue, black, black, red);
	glTranslatef(10.5, 0, 0);
	drawSubCube(black, white, blue, black, black, black);
	glTranslatef(10.5, 0, 0);
	drawSubCube(black, white, blue, black, orange, black);

	//middle layer
	glTranslatef(-21, -21, 10.5);
	drawSubCube(black, black, black, yellow, black, red);
	glTranslatef(10.5, 0, 0);
	drawSubCube(black, black, black, yellow, black, black);
	glTranslatef(10.5, 0, 0);
	drawSubCube(black, black, black, yellow, orange, black);

	glTranslatef(0, 10.5, 0);
	drawSubCube(black, black, black, black, orange, black);
	glTranslatef(-10.5, 0, 0);
	drawSubCube(black, black, black, black, black, black);
	glTranslatef(-10.5, 0, 0);
	drawSubCube(black, black, black, black, black, red);


	glTranslatef(0, 10.5, 0);
	drawSubCube(black, white, black, black, black, red);
	glTranslatef(10.5, 0, 0);
	drawSubCube(black, white, black, black, black, black);
	glTranslatef(10.5, 0, 0);
	drawSubCube(black, white, black, black, orange, black);

	//top layer
	glTranslatef(-21, -21, 10.5);
	drawSubCube(green, black, black, yellow, black, red);
	glTranslatef(10.5, 0, 0);
	drawSubCube(green, black, black, yellow, black, black);
	glTranslatef(10.5, 0, 0);
	drawSubCube(green, black, black, yellow, orange, black);

	glTranslatef(0, 10.5, 0);
	drawSubCube(green, black, black, black, orange, black);
	glTranslatef(-10.5, 0, 0);
	drawSubCube(green, black, black, black, black, black);
	glTranslatef(-10.5, 0, 0);
	drawSubCube(green, black, black, black, black, red);


	glTranslatef(0, 10.5, 0);
	drawSubCube(green, white, black, black, black, red);
	glTranslatef(10.5, 0, 0);
	drawSubCube(green, white, black, black, black, black);
	glTranslatef(10.5, 0, 0);
	drawSubCube(green, white, black, black, orange, black);


	//test
	glTranslatef(50, 50, 0);

	/*glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glVertexPointer(3, GL_FLOAT, sizeof(Vertex), &verts[0].x);
	glColorPointer(4, GL_FLOAT, sizeof(Vertex), &verts[0].r);
	glDrawArrays(GL_LINE_STRIP, 0, verts.size());
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);*/



	glutSwapBuffers();
}

void drawSubCube(Color c1, Color c2, Color c3, Color c4, Color c5, Color c6) {
	glBegin(GL_POLYGON);
	glColor3f(c1.r, c1.g, c1.b);
	glVertex3f(-5.00000, -5.00000, 5.00000);
	glVertex3f(5.00000, -5.00000, 5.00000);
	glVertex3f(5.00000, 5.00000, 5.00000);
	glVertex3f(-5.00000, 5.00000, 5.00000);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(c2.r, c2.g, c2.b);
	glVertex3f(-5.00000, 5.00000, 5.00000);
	glVertex3f(5.00000, 5.00000, 5.00000);
	glVertex3f(5.00000, 5.00000, -5.00000);
	glVertex3f(-5.00000, 5.00000, -5.00000);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(c3.r, c3.g, c3.b);
	glVertex3f(-5.00000, 5.00000, -5.00000);
	glVertex3f(5.00000, 5.00000, -5.00000);
	glVertex3f(5.00000, -5.00000, -5.00000);
	glVertex3f(-5.00000, -5.00000, -5.00000);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(c4.r, c4.g, c4.b);
	glVertex3f(-5.00000, -5.00000, -5.00000);
	glVertex3f(5.00000, -5.00000, -5.00000);
	glVertex3f(5.00000, -5.00000, 5.00000);
	glVertex3f(-5.00000, -5.00000, 5.00000);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(c5.r, c5.g, c5.b);

	glVertex3f(5.00000, -5.00000, 5.00000);
	glVertex3f(5.00000, -5.00000, -5.00000);
	glVertex3f(5.00000, 5.00000, -5.00000);
	glVertex3f(5.00000, 5.00000, 5.00000);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(c6.r, c6.g, c6.b);
	glVertex3f(-5.00000, -5.00000, -5.00000);
	glVertex3f(-5.00000, -5.00000, 5.00000);
	glVertex3f(-5.00000, 5.00000, 5.00000);
	glVertex3f(-5.00000, 5.00000, -5.00000);
	glEnd();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	//glutInitWindowSize(800, 600);
	//glutCreateWindow("Attractor");

	initGlut(argv[0]);
	initGlui();
	initGl();


	glutDisplayFunc(display);



	//glutTimerFunc(0, timer, 0);

	//fillVerts();

	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//glEnable(GL_POINT_SMOOTH);
	//glPointSize(1.0f);

	glutMainLoop();
	return 0;
}