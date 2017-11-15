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
//int animate_mode = 0;       // 0 = no anim, 1 = animate
//int animation_frame = 0;      // Specify current frame of animation
//
//							  // Joint parameters
//const float JOINT_MIN = -45.0f;
//const float JOINT_MAX = 45.0f;
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
//
//// Callback for handling events in glui
//void GLUI_Control(int id);
//
//
//
//#include <vector>
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
//
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
//	// draw curve
//	glEnableClientState(GL_VERTEX_ARRAY);
//	glEnableClientState(GL_COLOR_ARRAY);
//	glVertexPointer(3, GL_FLOAT, sizeof(Vertex), &verts[0].x);
//	glColorPointer(4, GL_FLOAT, sizeof(Vertex), &verts[0].r);
//	glDrawArrays(GL_LINE_STRIP, 0, verts.size());
//	glDisableClientState(GL_VERTEX_ARRAY);
//	glDisableClientState(GL_COLOR_ARRAY);
//
//	glutSwapBuffers();
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