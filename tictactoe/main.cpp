#include "tictactoe.h"

Button save_Button = Button(Vertex(10,750), 100, 15, "Save");
Button load_Button = Button(Vertex(10, 780), 100, 15, "Load");
double g_screen_x, g_screen_y;
double g_red, g_blue, g_green;
Game g_game(650,800);
int main(int argc, char **argv)
{
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	glutInit(&argc, argv);
	g_screen_x = 650;
	g_screen_y = 800;
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(g_screen_x, g_screen_y);
	glutInitWindowPosition(50, 50);

	int fullscreen = 0;
	if (fullscreen)
	{
		glutGameModeString("800x600:32");
		glutEnterGameMode();
	}
	else
	{
		glutCreateWindow("THE ULTIMATE SHOWDOWN OF ULTIMATE DESTINY");
	}

	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutPassiveMotionFunc(moveMouse);

	glColor3d(0, 0, 0); // forground color
	glClearColor(1, 1, 1, 0); // background color

	glutMainLoop();
	//_CrtDumpMemoryLeaks();
	return 0;
}
void keyboard(unsigned char c, int x, int y)
{
	switch (c)
	{
	case 'q':
	case 27: // escape character means to quit the program
		exit(0);
		break;
	case 'b':
		// do something when 'b' character is hit.
		break;
	default:
		return; // if we don't care, return without glutPostRedisplay()
	}

	glutPostRedisplay();
}
void reshape(int w, int h)
{
	// Reset our global variables to the new width and height.
	g_screen_x = w;
	g_screen_y = h;

	// Set the pixel resolution of the final picture (Screen coordinates).
	glViewport(0, 0, w, h);

	// Set the projection mode to 2D orthographic, and set the world coordinates:
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, w, 0, h);
	glMatrixMode(GL_MODELVIEW);

}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	save_Button.draw();
	load_Button.draw();
	g_game.draw();
	glutSwapBuffers();
}

void mouse(int mouse_button, int state, int x, int y)
{
	// translate pixel coordinates to display coordinates
	int xdisplay = x;
	int ydisplay = g_screen_y - y;
	if (mouse_button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		Vertex v = Vertex(xdisplay, ydisplay);


		if (load_Button.isInside(v))
		{
			load_Button.setColors(0, 0, 0);
			save_Button.setColors(.4, .4, .4);
			std::ifstream fin("tictacsaved.txt");
			std::cout << "Load Button!" << std::endl;
			g_game.load(fin);
			fin.close();
			return;
		}
		else if (save_Button.isInside(v))
		{
			save_Button.setColors(0, 0, 0);
			load_Button.setColors(.4, .4, .4);
			std::ofstream fout("tictacsaved.txt");
			std::cout << "Save Button!" << std::endl;
			g_game.save(fout);
			fout.close();
			return;
		}
		else {
			save_Button.setColors(.4, .4, .4);
			load_Button.setColors(.4, .4, .4);
		}
		g_game.clicked(v);

	}
	if (mouse_button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
	}
	if (mouse_button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
	{
	}
	if (mouse_button == GLUT_MIDDLE_BUTTON && state == GLUT_UP)
	{
	}
	if (mouse_button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
	}
	glutPostRedisplay();
}

void moveMouse(int x, int y)
{

}
