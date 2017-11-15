//
//#ifdef _WIN32
//#include <windows.h>
//#endif
//
//#include <GL/gl.h>
//#include <GL/glu.h>
//#include <GL/glut.h>
//#include <GL/glui.h>
//
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <math.h>
//
//#ifndef _WIN32
//#include <unistd.h>
//#else
//void usleep(unsigned int nanosec)
//{
//	Sleep(nanosec / 1000);
//}
//#endif
//
//
//// *************** GLOBAL VARIABLES *************************
//
//
//const float PI = 3.14159;
//
//// --------------- USER INTERFACE VARIABLES -----------------
//
//// Window settings
//int windowID;               // Glut window ID (for display)
//GLUI *glui;                 // Glui window (for controls)
//int Win[2];                 // window (x,y) size
//
//
//							// ---------------- ANIMATION VARIABLES ---------------------
//
//							// Animation settings
//int animate_mode_f = 0;       // 0 = no anim, 1 = animate
//int animate_mode_r = 0;       // 0 = no anim, 1 = animate
//int animate_mode_e = 0;       // 0 = no anim, 1 = animate
//int animate_mode_d = 0;       // 0 = no anim, 1 = animate
//int animate_mode = 0;
//
//int animation_frame = 0;      // Specify current frame of animation
//
//							  // Joint parameters
//const float JOINT_MIN = -45.0f;
//const float JOINT_MAX = 45.0f;
//const float DEG2RAD = 3.14159 / 180;
//
////float joint_rot = 0.0f;
//float joint_rot_f = 0.0f;
//float joint_rot_r = 0.0f;
//float joint_rot_e = 0.0f;
//float joint_rot_d = 0.0f;
//float joint_rot = 0.0f;
//
////////////////////////////////////////////////////////
//// TODO: Add additional joint parameters here
////////////////////////////////////////////////////////
//
//
//
//// ***********  FUNCTION HEADER DECLARATIONS ****************
//
//
//// Initialization functions
//void initGlut(char* winName);
//void initGlui();
//void initGl();
//
//
//// Callbacks for handling events in glut
//void myReshape(int w, int h);
//void animate();
//void display(void);
//void display2(void);
//
//// Callback for handling events in glui
//void GLUI_Control(int id);
//
//void drawSquare(float size);
//void drawFilledCircle(GLfloat x, GLfloat y, GLfloat radius);
////void drawCircle(float cx, float cy, float r, int num_segments);
//void drawF();
//void drawR();
//void drawE();
//void drawD();
//
//void rotateF();
//void rotateR();
//void rotateE();
//void rotateD();
//
//#include <vector>
//
//struct rot_state {
//		bool rotating;    // animation/movement happening
//		float x, y, z;      // current rotation values
//		int current_axis; // 0 for x, 1 for y, 2 for z
//	} app_state;
//
//void init(void) {
//		// Setting up initial app state
//		app_state.rotating = false;
//		app_state.x = app_state.y = app_state.z = 0.0f;
//		app_state.current_axis = 0;
//	
//		glClearColor(0.0, 0.0, 0.0, 0.0);
//		glShadeModel(GL_SMOOTH);
//	}
//
//struct Vertex
//{
//	float x, y, z, w;
//	float r, g, b, a;
//};
//std::vector< Vertex > verts;
//
//void fillVerts()
//{
//	double h = 0.01;
//	double a = 10.0;
//	double b = 28.0;
//	double c = 8.0 / 3.0;
//
//	Vertex cur;
//	cur.a = 0.09f;
//
//	double x0 = 0.1;
//	double y0 = 0;
//	double z0 = 0;
//	for (unsigned int i = 0; i < 100000; i++)
//	{
//		if (i == 20000)
//		{
//			cur.r = 1.0f;
//			cur.g = 0.0f;
//			cur.b = 0.0f;
//		}
//		if (i == 40000)
//		{
//			cur.r = 1.0f;
//			cur.g = 0.0f;
//			cur.b = 1.0f;
//		}
//		if (i == 60000)
//		{
//			cur.r = 0.0f;
//			cur.g = 0.0f;
//			cur.b = 1.0f;
//		}
//		if (i == 80000)
//		{
//			cur.r = 0.0f;
//			cur.g = 1.0f;
//			cur.b = 1.0f;
//		}
//
//		const double x1 = x0 + h * a * (y0 - x0);
//		const double y1 = y0 + h * (x0 * (b - z0) - y0);
//		const double z1 = z0 + h * (x0 * y0 - c * z0);
//		x0 = x1;
//		y0 = y1;
//		z0 = z1;
//
//		if (i > 100)
//		{
//			cur.x = x0;
//			cur.y = y0;
//			cur.z = z0;
//			verts.push_back(cur);
//		}
//	}
//}
//
//float angle = 0;
//void timer(int extra)
//{
//	// spin
//	angle += 0.5;
//
//	glutPostRedisplay();
//	glutTimerFunc(16, timer, 0);
//}
////
//void display(void)
//{
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	const double w = glutGet(GLUT_WINDOW_WIDTH);
//	const double h = glutGet(GLUT_WINDOW_HEIGHT);
//	gluPerspective(60.0, w / h, 1.0, 10000.0);
//
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//	gluLookAt(70, 70, 70, 0, 0, 0, 0, 0, 1);
//
//	glRotatef(angle, 0, 0, 1);
//
//
//	display2();
//
//	//// draw curve
//	//glEnableClientState(GL_VERTEX_ARRAY);
//	//glEnableClientState(GL_COLOR_ARRAY);
//	//glVertexPointer(3, GL_FLOAT, sizeof(Vertex), &verts[0].x);
//	//glColorPointer(4, GL_FLOAT, sizeof(Vertex), &verts[0].r);
//	//glDrawArrays(GL_LINE_STRIP, 0, verts.size());
//	//glDisableClientState(GL_VERTEX_ARRAY);
//	//glDisableClientState(GL_COLOR_ARRAY);
//
//	glutSwapBuffers();
//}
//
//void display2(void) {
//
//	glClear(GL_COLOR_BUFFER_BIT);
//	glPushMatrix();
//
//	// Apply the rotations
//	glRotatef(app_state.x, 1, 0, 0);
//	glRotatef(app_state.y, 0, 1, 0);
//	glRotatef(app_state.z, 0, 0, 1);
//
//	//glutWireCube(4);
//
//	//starts here
//	const float BODY_WIDTH = 30.0f;
//	const float BODY_LENGTH = 50.0f;
//	const float ARM_LENGTH = 50.0f;
//	const float ARM_WIDTH = 10.0f;
//
//
//	// Push the current transformation matrix on the stack
//	glPushMatrix();
//
//	// Draw the 'body'
//	glPushMatrix();
//	// Scale square to size of body
//	glTranslatef(50, 0, 0);
//
//	glScalef(BODY_WIDTH * 8, BODY_LENGTH, 1.0);
//
//	// Set the colour to green
//	glColor3f(0.184, 0.310, 0.310);
//
//	// Draw the square for the body
//	glutWireCube(1.0);
//	glPopMatrix();
//
//	// Draw the 'arm'
//
//	//F and joint
//	glPushMatrix();
//	// Move the arm to the joint hinge
//	glTranslatef(0.0, -BODY_LENGTH / 2 + ARM_WIDTH, 0.0);
//	glColor3f(0.199, 0.088, 0.350);
//	//drawFilledCircle(0, 0, 10);
//
//
//	rotateF();
//	glPopMatrix();
//
//	// R and joint
//	glPushMatrix();
//	// Move the arm to the joint hinge
//	glTranslatef(40.0, -BODY_LENGTH / 2 + ARM_WIDTH - 2, 0.0);
//	//drawFilledCircle(0, 0, 10);
//
//
//	rotateR();
//	glPopMatrix();
//
//	// E and joint
//	glPushMatrix();
//	// Move the arm to the joint hinge
//	glTranslatef(80.0, -BODY_LENGTH / 2 + ARM_WIDTH, 0.0);
//	//drawFilledCircle(0, 0, 10);
//
//	rotateE();
//
//	glPopMatrix();
//
//	// D and joint
//	glPushMatrix();
//	// Move the arm to the joint hinge
//	glTranslatef(120.0, -BODY_LENGTH / 2 + ARM_WIDTH - 2, 0.0);
//	//drawFilledCircle(0, 0, 10);
//
//	rotateD();
//	//ends here
//
//	glPopMatrix();
//	glutSwapBuffers();
//	glFlush();
//}
//
//int main(int argc, char **argv)
//{
//	glutInit(&argc, argv);
//	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
//	glutInitWindowSize(800, 600);
//	glutCreateWindow("Attractor");
//
//	glutDisplayFunc(display);
//	glutTimerFunc(0, timer, 0);
//
//	fillVerts();
//
//	glEnable(GL_BLEND);
//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//
//	glEnable(GL_POINT_SMOOTH);
//	glPointSize(1.0f);
//
//	glutMainLoop();
//	return 0;
//}
//
//void initGlut(char* winName)
//{
//	// Set video mode: double-buffered, color, depth-buffered
//	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
//
//	// Create window
//	glutInitWindowPosition(0, 0);
//	glutInitWindowSize(Win[10], Win[11]);
//	windowID = glutCreateWindow(winName);
//
//	// Setup callback functions to handle events
//	glutReshapeFunc(myReshape); // Call myReshape whenever window resized
//	glutDisplayFunc(display);   // Call display whenever new frame needed 
//}
//
//void quitButton(int)
//{
//	exit(0);
//}
//
////void animateButtonF(int)
////{
////	// synchronize variables that GLUT uses
////	glui->sync_live();
////
////	animation_frame = 0;
////	if (animate_mode_f == 1) {
////		// start animation
////		GLUI_Master.set_glutIdleFunc(animateF);
////	}
////	else {
////		// stop animation
////		GLUI_Master.set_glutIdleFunc(NULL);
////	}
////}
////void animateButtonR(int)
////{
////	// synchronize variables that GLUT uses
////	glui->sync_live();
////
////	animation_frame = 0;
////	if (animate_mode_r == 1) {
////		// start animation
////		GLUI_Master.set_glutIdleFunc(animateR);
////	}
////	else {
////		// stop animation
////		GLUI_Master.set_glutIdleFunc(NULL);
////	}
////}
////void animateButtonE(int)
////{
////	// synchronize variables that GLUT uses
////	glui->sync_live();
////
////	animation_frame = 0;
////	if (animate_mode_e == 1) {
////		// start animation
////		GLUI_Master.set_glutIdleFunc(animateE);
////	}
////	else {
////		// stop animation
////		GLUI_Master.set_glutIdleFunc(NULL);
////	}
////}
//
//
//void animateButton(int)
//{
//	// synchronize variables that GLUT uses
//	glui->sync_live();
//
//	animation_frame = 0;
//	if (animate_mode == 1) {
//		// start animation
//		GLUI_Master.set_glutIdleFunc(animate);
//	}
//	else {
//		// stop animation
//		GLUI_Master.set_glutIdleFunc(NULL);
//	}
//}
//
//void initGlui()
//{
//	GLUI_Master.set_glutIdleFunc(NULL);
//
//	// Create GLUI window
//	glui = GLUI_Master.create_glui("Glui Window", 0, Win[0] + 10, 0);
//
//	// Create a control to specify the rotation of the joint
//	GLUI_Spinner *joint_spinner_f
//		= glui->add_spinner("Joint", GLUI_SPINNER_FLOAT, &joint_rot_f);
//	joint_spinner_f->set_speed(0.1);
//	joint_spinner_f->set_float_limits(JOINT_MIN, JOINT_MAX, GLUI_LIMIT_CLAMP);
//	GLUI_Spinner *joint_spinner_r
//		= glui->add_spinner("Joint", GLUI_SPINNER_FLOAT, &joint_rot_r);
//	joint_spinner_r->set_speed(0.1);
//	joint_spinner_r->set_float_limits(JOINT_MIN, JOINT_MAX, GLUI_LIMIT_CLAMP);
//	GLUI_Spinner *joint_spinner_e
//		= glui->add_spinner("Joint", GLUI_SPINNER_FLOAT, &joint_rot_e);
//	joint_spinner_e->set_speed(0.1);
//	joint_spinner_e->set_float_limits(JOINT_MIN, JOINT_MAX, GLUI_LIMIT_CLAMP);
//	GLUI_Spinner *joint_spinner_d
//		= glui->add_spinner("Joint", GLUI_SPINNER_FLOAT, &joint_rot_d);
//	joint_spinner_d->set_speed(0.1);
//	joint_spinner_d->set_float_limits(JOINT_MIN, JOINT_MAX, GLUI_LIMIT_CLAMP);
//
//	///////////////////////////////////////////////////////////
//	// TODO: 
//	//   Add controls for additional joints here
//	///////////////////////////////////////////////////////////
//
//	// Add button to specify animation mode 
//	glui->add_separator();
//	glui->add_checkbox("Animate", &animate_mode, 0, animateButton);
//
//
//	// Add "Quit" button
//	glui->add_separator();
//	glui->add_button("Quit", 0, quitButton);
//
//	// Set the main window to be the "active" window
//	glui->set_main_gfx_window(windowID);
//}
//void initGl(void)
//{
//	// glClearColor (red, green, blue, alpha)
//	// Ignore the meaning of the 'alpha' value for now
//	glClearColor(0.7f, 0.7f, 0.9f, 1.0f);
//}
//
//void animateF()
//{
//	// Update geometry
//	const double joint_rot_speed = 0.1;
//	double joint_rot_t = (sin(animation_frame*joint_rot_speed) + 1.0) / 2.0;
//	joint_rot_f = joint_rot_t * JOINT_MIN + (1 - joint_rot_t) * JOINT_MAX;
//
//	// Update user interface
//	glui->sync_live();
//
//	// Tell glut window to update itself.  This will cause the display()
//	// callback to be called, which renders the object (once you've written
//	// the callback).
//	glutSetWindow(windowID);
//	glutPostRedisplay();
//
//	// increment the frame number.
//	animation_frame++;
//
//	// Wait 50 ms between frames (20 frames per second)
//	usleep(50000);
//}
//void animateR()
//{
//	// Update geometry
//	const double joint_rot_speed = 0.1;
//	double joint_rot_t = (sin(animation_frame*joint_rot_speed) + 1.0) / 2.0;
//	joint_rot_r = joint_rot_t * JOINT_MIN + (1 - joint_rot_t) * JOINT_MAX;
//
//	// Update user interface
//	glui->sync_live();
//
//	// Tell glut window to update itself.  This will cause the display()
//	// callback to be called, which renders the object (once you've written
//	// the callback).
//	glutSetWindow(windowID);
//	glutPostRedisplay();
//
//	// increment the frame number.
//	animation_frame++;
//
//	// Wait 50 ms between frames (20 frames per second)
//	usleep(50000);
//}
//void animateE()
//{
//	// Update geometry
//	const double joint_rot_speed = 0.1;
//	double joint_rot_t = (sin(animation_frame*joint_rot_speed) + 1.0) / 2.0;
//	joint_rot_e = joint_rot_t * JOINT_MIN + (1 - joint_rot_t) * JOINT_MAX;
//
//	// Update user interface
//	glui->sync_live();
//
//	// Tell glut window to update itself.  This will cause the display()
//	// callback to be called, which renders the object (once you've written
//	// the callback).
//	glutSetWindow(windowID);
//	glutPostRedisplay();
//
//	// increment the frame number.
//	animation_frame++;
//
//	// Wait 50 ms between frames (20 frames per second)
//	usleep(50000);
//}
//void animate()
//{
//	// Update geometry
//	const double joint_rot_speed = 0.1;
//	double joint_rot_t = (sin(animation_frame*joint_rot_speed) + 1.0) / 2.0;
//	joint_rot_f = joint_rot_t * JOINT_MIN + (1 - joint_rot_t) * JOINT_MAX;
//	joint_rot_r = joint_rot_t * JOINT_MIN + (1 - joint_rot_t) * JOINT_MAX;
//	joint_rot_e = joint_rot_t * JOINT_MIN + (1 - joint_rot_t) * JOINT_MAX;
//	joint_rot_d = joint_rot_t * JOINT_MIN + (1 - joint_rot_t) * JOINT_MAX;
//	// Update user interface
//	glui->sync_live();
//
//	// Tell glut window to update itself.  This will cause the display()
//	// callback to be called, which renders the object (once you've written
//	// the callback).
//	glutSetWindow(windowID);
//	glutPostRedisplay();
//
//	// increment the frame number.
//	animation_frame++;
//
//	// Wait 50 ms between frames (20 frames per second)
//	usleep(50000);
//}
//
//
//// Handles the window being resized by updating the viewport
//// and projection matrices
//void myReshape(int w, int h)
//{
//	// Setup projection matrix for new window
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	gluOrtho2D(-w / 2, w / 2, -h / 2, h / 2);
//
//	// Update OpenGL viewport and internal variables
//	glViewport(0, 0, w, h);
//	Win[0] = w;
//	Win[1] = h;
//}
//
//
//
////display callback
//
////This gets called by the event handler to draw
////the scene, so this is where you need to build
////your scene -- make your changes and additions here.
////All rendering happens in this function.  For this Assignment,
////updates to geometry should happen in the "animate" function.
//
//
//
//
//// Draw a square of the specified size, centered at the current location
//void drawSquare(float width)
//{
//	// Draw the square
//	glBegin(GL_POLYGON);
//	glVertex2d(-width / 2, -width / 2);
//	glVertex2d(width / 2, -width / 2);
//	glVertex2d(width / 2, width / 2);
//	glVertex2d(-width / 2, width / 2);
//	glEnd();
//}
//void drawFilledCircle(GLfloat x, GLfloat y, GLfloat radius) {
//	int i;
//	int triangleAmount = 20; //# of triangles used to draw circle
//
//							 //GLfloat radius = 0.8f; //radius
//	GLfloat twicePi = 2.0f * PI;
//
//	glBegin(GL_TRIANGLE_FAN);
//	glVertex2f(x, y); // center of circle
//	for (i = 0; i <= triangleAmount; i++) {
//		glVertex2f(
//			x + (radius * cos(i *  twicePi / triangleAmount)),
//			y + (radius * sin(i * twicePi / triangleAmount))
//		);
//	}
//	glEnd();
//}
//
//
//void drawF() {
//	//draw F
//	glBegin(GL_LINES);
//	glVertex2d(1.0, 1.0);
//	glVertex2d(1.0, 5.0);
//
//	glVertex2d(1.0, 5.0);
//	glVertex2d(4.0, 5.0);
//
//	glVertex2d(4.0, 5.0);
//	glVertex2d(4.0, 4.0);
//
//	glVertex2d(4.0, 4.0);
//	glVertex2d(2.0, 4.0);
//
//	glVertex2d(2.0, 4.0);
//	glVertex2d(2.0, 3.30);
//
//	glVertex2d(2.0, 3.30);
//	glVertex2d(3.5, 3.30);
//
//	glVertex2d(3.5, 3.30);
//	glVertex2d(3.45, 2.5);
//
//	glVertex2d(3.45, 2.5);
//	glVertex2d(2.0, 2.5);
//
//	glVertex2d(2.0, 2.5);
//	glVertex2d(2.0, 1.0);
//
//	glVertex2d(2.0, 1.0);
//	glVertex2d(1.0, 1.0);
//
//	glEnd();
//
//}
//void drawR() {
//	glBegin(GL_LINES);
//	// draw R
//	glVertex2f(5.0, 1.0);
//	glVertex2f(5.0, 5.0);
//
//	glVertex2f(5.0, 5.0);
//	glVertex2f(8.0, 5.0);
//
//	glVertex2f(8.0, 5.0);
//	glVertex2f(8.0, 3.50);
//
//	glVertex2f(8.0, 3.50);
//	glVertex2f(6.0, 3.0);
//
//	glVertex2f(6.0, 3.0);
//	glVertex2f(8.0, 2.0);
//
//	glVertex2f(8.0, 2.0);
//	glVertex2f(8.0, 1.0);
//
//	glVertex2f(8.0, 1.0);
//	glVertex2f(7.50, 1.0);
//
//	glVertex2f(7.50, 1.0);
//	glVertex2f(6.0, 2.0);
//
//	glVertex2f(6.0, 2.0);
//	glVertex2f(6.0, 1.0);
//
//	glVertex2f(6.0, 1.0);
//	glVertex2f(5.0, 1.0);
//
//	glEnd();
//}
//void drawE() {
//	glBegin(GL_LINES);
//
//	//draw E
//
//	glVertex2f(9.0, 1.0);
//	glVertex2f(9.0, 5.0);
//
//	glVertex2f(9.0, 5.0);
//	glVertex2f(12.0, 5.0);
//
//	glVertex2f(12.0, 5.0);
//	glVertex2f(12.0, 4.0);
//
//	glVertex2f(12.0, 4.0);
//	glVertex2f(10.0, 4.0);
//
//	glVertex2f(10.0, 4.0);
//	glVertex2f(10.0, 3.30);
//
//	glVertex2f(10.0, 3.30);
//	glVertex2f(11.5, 3.30);
//
//	glVertex2f(11.5, 3.30);
//	glVertex2f(11.45, 2.5);
//
//	glVertex2f(11.45, 2.5);
//	glVertex2f(10.0, 2.5);
//
//	glVertex2f(10.0, 2.5);
//	glVertex2f(10.0, 2.0);
//
//	glVertex2f(10.0, 2.0);
//	glVertex2f(12.0, 2.0);
//
//	glVertex2f(12.0, 2.0);
//	glVertex2f(12.0, 1.0);
//
//
//	glVertex2f(12.0, 1.0);
//	glVertex2f(9.0, 1.0);
//
//	glEnd();
//}
//void drawD() {
//
//	glBegin(GL_LINES);
//
//	glVertex2f(13.0, 1.0);
//	glVertex2f(13.0, 5.0);
//
//	glVertex2f(13.0, 5.0);
//	glVertex2f(16.5, 5.0);
//
//	glVertex2f(16.5, 5.0);
//	glVertex2f(17, 4.0);
//
//	glVertex2f(17, 4.0);
//	glVertex2f(17, 2.0);
//
//	glVertex2f(17, 2.0);
//	glVertex2f(16.5, 1.0);
//
//	glVertex2f(16.5, 1.0);
//	glVertex2f(13.0, 1.0);
//	//inside of D
//	glVertex2f(14.0, 2.0);
//	glVertex2f(14.0, 4.0);
//
//	glVertex2f(14.0, 4.0);
//	glVertex2f(15.5, 4.0);
//
//	glVertex2f(15.5, 4.0);
//	glVertex2f(16, 3.5);
//
//	glVertex2f(16, 3.5);
//	glVertex2f(16, 3.5);
//
//	glVertex2f(16, 3.5);
//	glVertex2f(15.5, 2.0);
//
//	glVertex2f(15.5, 2.0);
//	glVertex2f(14.0, 2.0);
//
//	glEnd();
//}
//
//void rotateF() {
//	const float ARM_LENGTH = 50.0f;
//	const float ARM_WIDTH = 10.0f;
//	// Rotate along the hinge
//	glRotatef(joint_rot_f, 0.0, 0.0, 1.0);
//	// Scale the size of the arm
//	glScalef(ARM_WIDTH, ARM_LENGTH, 1.0);
//	// Move to center location of arm, under previous rotation
//	//glTranslatef(0.0, -0.5, 0.0);
//	// Draw the square for the arm
//	glColor3f(0.098, 0.098, 0.439);
//	drawSquare(1.0);
//	glPushMatrix();
//	glTranslatef(-3, -5.5, 0);
//	drawF();
//	glPopMatrix();
//}
//void rotateR() {
//	const float ARM_LENGTH = 50.0f;
//	const float ARM_WIDTH = 10.0f;
//	// Rotate along the hinge
//	glRotatef(joint_rot_r, 0.0, 0.0, 1.0);
//	// Scale the size of the arm
//	glScalef(ARM_WIDTH, ARM_LENGTH, 1.0);
//	// Move to center location of arm, under previous rotation
//	//glTranslatef(-5, -1, 0.0);
//	// Draw the square for the arm
//	glColor3f(0.000, 0.000, 0.804);
//	drawSquare(1.0);
//	glPushMatrix();
//	glTranslatef(-7, -5.5, 0);
//	drawR();
//	glPopMatrix();
//
//}
//void rotateE() {
//	const float ARM_LENGTH = 50.0f;
//	const float ARM_WIDTH = 10.0f;
//	// Rotate along the hinge
//	glRotatef(joint_rot_e, 0.0, 0.0, 1.0);
//	// Scale the size of the arm
//	glScalef(ARM_WIDTH, ARM_LENGTH, 1.0);
//	// Move to center location of arm, under previous rotation
//	//glTranslatef(-5, -1, 0.0);
//	// Draw the square for the arm
//	glColor3f(0.118, 0.565, 1.00);
//	drawSquare(1.0);
//	glPushMatrix();
//	glTranslatef(-10.5, -5.5, 0);
//	drawE();
//	glPopMatrix();
//}
//void rotateD() {
//	const float ARM_LENGTH = 50.0f;
//	const float ARM_WIDTH = 10.0f;
//	// Rotate along the hinge
//	glRotatef(joint_rot_d, 0.0, 0.0, 1.0);
//	// Scale the size of the arm
//	glScalef(ARM_WIDTH, ARM_LENGTH, 1.0);
//	// Move to center location of arm, under previous rotation
//	//glTranslatef(-5, -1, 0.0);
//	// Draw the square for the arm
//	glColor3f(0.000, 0.749, 1.00);
//	drawSquare(1.0);
//	glPushMatrix();
//	glTranslatef(-15, -5.5, 0);
//	drawD();
//	//drawFilledCircle(2, 2, 2);
//	//drawCircle(2, 2, 2, 100);
//
//	glPopMatrix();
//}