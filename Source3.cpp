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
//GLUI *glui;                 // Glui window (for controls)
//int windowID;               // Glut window ID (for display)
//int Win[2];                 // window (x,y) size
//
//
//// Animation settings
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
//float joint_rot_f = 0.0f;
//float joint_rot_r = 0.0f;
//float joint_rot_e = 0.0f;
//float joint_rot_d = 0.0f;
//float joint_rot = 0.0f;
//
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
//void animate();
//
//
//struct rot_state {
//	bool rotating;    // animation/movement happening
//	float x, y, z;      // current rotation values
//	int current_axis; // 0 for x, 1 for y, 2 for z
//} app_state;
//
//void init(void) {
//	// Setting up initial app state
//	app_state.rotating = false;
//	app_state.x = app_state.y = app_state.z = 0.0f;
//	app_state.current_axis = 0;
//
//	glClearColor(0.0, 0.0, 0.0, 0.0);
//	glShadeModel(GL_SMOOTH);
//}
//
//void action(void)
//{
//	// Animate the rotation
//	float increment = 0.10f;
//	switch (app_state.current_axis)
//	{
//	case 0:
//		app_state.x += increment;
//		break;
//	case 1:
//		app_state.y += increment;
//		break;
//	case 2:
//		app_state.z += increment;
//		break;
//	default:
//		break;
//	}
//
//	glutPostRedisplay();
//}
//
//
//void display(void)
//{
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
//void reshape(int w, int h)
//{
//	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	glFrustum(-1.0, 1.0, -1.0, 1.0, 0.5, 115.0);
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//	gluLookAt(13.5, 13.5, 50.5, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
//
//}
//
////keyboard event handler
//void keyboard(unsigned char key, int x, int y)
//{
//	switch (key)
//	{
//	case 27: // Escape key
//		exit(0);
//		break;
//	case 'x':
//		app_state.current_axis = 0;
//		break;
//	case 'y':
//		app_state.current_axis = 1;
//		break;
//	case 'z':
//		app_state.current_axis = 2;
//		break;
//	case 'r':
//		app_state.rotating ^= 1;
//		glutIdleFunc(app_state.rotating ? action : NULL);
//		break;
//	}
//	glutPostRedisplay();
//}
//
//
//int main(int argc, char** argv)
//{
//	glutInit(&argc, argv);
//	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
//	glutInitWindowSize(500, 500);
//	glutInitWindowPosition(100, 100);
//	glutCreateWindow(argv[0]);
//	init();
//	glutReshapeFunc(reshape);
//	glutDisplayFunc(display);
//	glutKeyboardFunc(keyboard);
//	glutIdleFunc(action);
//	glutMainLoop();
//	return 0;
//}
//
//void drawF() {
//
//	glBegin(GL_LINE_LOOP);
//	//draw F
//	glColor3f(1.00, 0.00, 0.00);
//
//	glVertex3f(1.00, 1.00, 0.00);
//	glVertex3f(1.00, 1.00, 1.00);
//	glVertex3f(1.00, 5.00, 0.00);
//	glVertex3f(1.00, 5.00, 1.00);
//
//
//	glVertex3f(1.00, 5.00, 0.00);
//	glVertex3f(1.00, 5.00, 1.00);
//	glVertex3f(4.00, 5.00, 0.00);
//
//	glVertex3f(4.00, 5.00, 0.00);
//	glVertex3f(4.00, 5.00, 1.00);
//	glVertex3f(4.00, 4.00, 0.00);
//
//	glVertex3f(4.00, 4.00, 0.00);
//	glVertex3f(4.00, 4.00, 1.00);
//	glVertex3f(2.00, 4.00, 0.00);
//
//	glVertex3f(2.00, 4.00, 0.00);
//	glVertex3f(2.00, 4.00, 1.00);
//	glVertex3f(2.00, 3.30, 0.00);
//
//	glVertex3f(2.00, 3.30, 0.00);
//	glVertex3f(2.00, 3.30, 1.00);
//	glVertex3f(3.50, 3.30, 0.00);
//
//	glVertex3f(3.50, 3.30, 0.00);
//	glVertex3f(3.50, 3.30, 1.00);
//	glVertex3f(3.45, 2.50, 0.00);
//
//	glVertex3f(3.45, 2.50, 0.00);
//	glVertex3f(3.45, 2.50, 1.00);
//	glVertex3f(2.0, 2.50, 0.00);
//
//	glVertex3f(2.0, 2.50, 0.00);
//	glVertex3f(2.0, 2.50, 1.00);
//	glVertex3f(2.0, 1.00, 0.00);
//
//	glVertex3f(2.0, 1.00, 0.00);
//	glVertex3f(2.0, 1.00, 1.00);
//	glVertex3f(1.0, 1.00, 0.00);
//
//	// draw R
//	glVertex3f(5.0, 1.0, 0);
//	glVertex3f(5.0, 5.0, 0);
//
//	glVertex3f(5.0, 5.0, 0);
//	glVertex3f(8.0, 5.0, 0);
//
//	glVertex3f(8.0, 5.0, 0);
//	glVertex3f(8.0, 3.50, 0);
//
//	glVertex3f(8.0, 3.50, 0);
//	glVertex3f(6.0, 3.0, 0);
//
//	glVertex3f(6.0, 3.0, 0);
//	glVertex3f(8.0, 2.0, 0);
//
//	glVertex3f(8.0, 2.0, 0);
//	glVertex3f(8.0, 1.0, 0);
//
//	glVertex3f(8.0, 1.0, 0);
//	glVertex3f(7.50, 1.0, 0);
//
//	glVertex3f(7.50, 1.0, 0);
//	glVertex3f(6.0, 2.0, 0);
//
//	glVertex3f(6.0, 2.0, 0);
//	glVertex3f(6.0, 1.0, 0);
//
//	glVertex3f(6.0, 1.0, 0);
//	glVertex3f(5.0, 1.0, 0);
//
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
//	//draw D
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
//	glutWireCube(1.0);
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
//	glutWireCube(1.0);
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
//	glutWireCube(1.0);
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
//	glutWireCube(1.0);
//	glPushMatrix();
//	glTranslatef(-15, -5.5, 0);
//	drawD();
//	//drawFilledCircle(2, 2, 2);
//	//drawCircle(2, 2, 2, 100);
//
//	glPopMatrix();
//}