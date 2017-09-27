#include <gl/glut.h>
#include <gl/gl.h>
#include <math.h>


#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

int size = 4;
int brush = 0;
int angle = 0;
bool solid = true;

void display(void)
{
	glFlush();
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
		case '1': glColor4f(1, 0, 0, .1); break;
		case '2': glColor4f(0, 1, 0, .1); break;
		case '3': glColor4f(1, 1, 0, .1); break;
		case '4': glColor4f(0, 0, 1, .1); break;
		case '5': glColor4f(1, 0, 1, .1); break;
		case '6': glColor4f(0, 1, 1, .1); break;
		case '7': glColor4f(1, 1, 1, .1); break;

		case 'c': case 'C': glClear(GL_COLOR_BUFFER_BIT); break;
		case 'r': case 'R': angle += 10; break;
		case 'a': case 'A': solid=!solid; break;

		case '+':
			if (size < 128) {
				size *= 2;
			}
			break;

		case '-':
			if (size > 1) {
				size /= 2;
			}
			break;

		case 'b': case 'B':
			brush++;
			if (brush == 4) {
				brush = 0;
			}
			break;
	}
	glutPostRedisplay();
}

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, WINDOW_WIDTH - 1, WINDOW_HEIGHT - 1, 0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
}

void drawQuads(int x, int y)
{
	glBegin(GL_QUADS);
	glVertex2f(x - size, y + size);
	glVertex2f(x - size, y - size);
	glVertex2f(x + size, y - size);
	glVertex2f(x + size, y + size);
	glEnd();
}

void drawTriangles(int x, int y)
{
	glBegin(GL_TRIANGLES);
	glVertex2f(x - size, y + size);
	glVertex2f(x + size, y + size);
	glVertex2f(x, y - size);
	glEnd();
}

void drawLines(int x, int y)
{
	glBegin(GL_LINES);
	glVertex2f(x, y - size);
	glVertex2f(x, y + size);
	glEnd();
}

void drawCircles(int x, int y)
{
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++)
	{
		glVertex2f(x + size*cos(i*3.14159265358979323846 / 180), y + size*sin(i*3.14159265358979323846 / 180));
	}
	glEnd();
}

void drawBlendedCircles(int x, int y)
{
	glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_COLOR , GL_ONE); this is cool but not what we need
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++)
	{
		glVertex2f(x + size*cos(i*3.14159265358979323846 / 180), y + size*sin(i*3.14159265358979323846 / 180));
	}
	glEnd();
	glDisable(GL_BLEND);
}
void mouseClick(int x, int y)
{
	glTranslated(x, y, 0);
	glRotatef(angle, 0, 0, 1.0);
	glTranslated(-x, -y, 0);


	if (brush == 0) {
		drawQuads(x, y);
	}
	else if (brush == 1) {
		drawTriangles(x, y);
	}
	else if (brush == 2) {
		drawLines(x, y);
	}
	else if (brush == 3) {
		solid ? drawCircles(x, y):drawBlendedCircles(x,y);
	}
	glTranslated(x, y, 0);
	glRotatef(-angle, 0, 0, 1.0);
	glTranslated(-x, -y, 0);
	glutPostRedisplay();
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Your Name - Assignment 1");
	init();
	glutMotionFunc(mouseClick);
	glutKeyboardFunc(keyboard);
	glutDisplayFunc(display);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor4f(1, 0, 0, .1);
	glutMainLoop();
	return 0;
}	