#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include "../glut/glut.h"
#include <iostream>
#include<vector>
#include<ctime>
#include<random>

using namespace std;

struct pointx3 {
	int x, y, z;
};

struct pointx2 {
	int i, j;
};

vector<vector<pointx3>> matrix_centre(3, vector<pointx3>(4));
vector<pointx2> spheres(7);
pointx2 current_hedgehog;
int turn;//0 -right, 1 - left, 2 - up, 3 -down

GLuint texture_grass;
GLuint texture_h;
GLuint texture_apple;

struct texture {
	int w, h;
	unsigned char* image;
} get_texture;

int Load_Texture(char *filename, GLuint& texture_id) {
	FILE* f;
	f = fopen(filename, "rb");
	fseek(f, 18, SEEK_SET);
	fread(&(get_texture.w), 2, 1, f);
	fseek(f, 2, SEEK_CUR);
	fread(&(get_texture.h), 2, 1, f);
	get_texture.image = (unsigned char*)malloc(sizeof(unsigned char) * 3 * get_texture.w* get_texture.h);
	fseek(f, 30, SEEK_CUR);
	fread(get_texture.image, 3, get_texture.w*get_texture.h, f);

	glGenTextures(1, &texture_id);
	glBindTexture(GL_TEXTURE_2D, texture_id);
	//glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, get_texture.w, get_texture.h, GL_RGB, GL_UNSIGNED_BYTE, get_texture.image);
	free(get_texture.image);
	fclose(f);
	return 1;
}


void resize(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-5, 5, -5, 5, 2, 12);
	gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);
	glMatrixMode(GL_MODELVIEW);
}

void hedgehog_pos() {
	current_hedgehog.i = 0;
	current_hedgehog.j = 0;
}

void fill_matrix_centre(){//making matrix of centres of rectangles
	pointx3 centre;
	centre.x = -1;
	centre.y = -2;
	centre.z = 1;
	for (int i = 0; i < 3; i++) {
		if (i != 0)
			centre.x += 2;
		centre.z = 1;
		for (int j = 0; j < 4; j++) {
			if (j != 0)
				centre.z -= 2;
			matrix_centre[i][j] = centre;
		}
	}
}

void random_fill_apples() {//making massive with random position of apples
	mt19937 gen(time(0));
	uniform_int_distribution<> urdi(0, 2);
	uniform_int_distribution<> urdj(0, 3);
	pointx2 temp;
	for (int k = 0; k < spheres.size(); k++) {
		temp.i = urdi(gen);
		temp.j = urdj(gen);
		if (temp.i != current_hedgehog.i && temp.j != current_hedgehog.j) {
			spheres[k] = temp;
		}
		else k--;
	}
	
}

void draw_apples() {
	for (int i = 0; i < spheres.size(); i++) {
		glColor3d(0.863, 0.078, 0.235);
		glPushMatrix();
		GLUquadricObj *quadObj;
		quadObj = gluNewQuadric();
		gluQuadricTexture(quadObj, GL_TRUE);
		gluQuadricDrawStyle(quadObj, GLU_FILL);
		glTranslated(matrix_centre[spheres[i].i][spheres[i].j].x, matrix_centre[spheres[i].i][spheres[i].j].y + 0.3, matrix_centre[spheres[i].i][spheres[i].j].z + 0.3);//ok sphere!!!
		gluSphere(quadObj, 0.3, 15, 15);
		gluQuadricTexture(quadObj, GL_FALSE);
		
		glLineWidth(5);
		glBegin(GL_LINES);
		glColor3d(0.545, 0.271, 0.075);
		glVertex3d(0.05, 0.28, 0);
		glVertex3d(0, 0.45, 0);
		glEnd();
		glPopMatrix();
		gluDeleteQuadric(quadObj);
	}
	glDisable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture_h);
}

void draw_hedgehog() {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture_h);
	GLdouble equation[4] = { 0,0.5,0,1};
	glEnable(GL_CLIP_PLANE0); 
	glPushMatrix();
	glClipPlane(GL_CLIP_PLANE0, equation);
	
	glTranslated(matrix_centre[current_hedgehog.i][current_hedgehog.j].x, matrix_centre[current_hedgehog.i][current_hedgehog.j].y - 0.2, matrix_centre[current_hedgehog.i][current_hedgehog.j].z);
	GLUquadricObj *quadObj;
	quadObj = gluNewQuadric();
	glColor3d(0.512, 0.512, 0.512);
	gluQuadricTexture(quadObj, GL_TRUE);
	gluQuadricDrawStyle(quadObj, GLU_FILL);
	gluSphere(quadObj, 0.85, 15, 15);
	gluDeleteQuadric(quadObj);
	gluQuadricTexture(quadObj, GL_FALSE);
	glDisable(GL_CLIP_PLANE0);
	if (turn != 1) {
		glTranslated(0.83, 0.25, 0);
		glPushMatrix();
		glRotated(90, 0, 1, 0);
		glutSolidCone(0.15, 0.15, 15, 15);
		glPopMatrix();
		glColor3d(0.96, 0.88, 0.52);
		glTranslated(0.14, 0, 0);
		glutSolidSphere(0.02, 15, 15);
	}
	else {
			glTranslated(-0.75, 0.25, 0.2);
			glPushMatrix();
			glRotated(-85, 0, 1, 0);
			glutSolidCone(0.15, 0.15, 15, 15);
			glPopMatrix();
			glColor3d(0.96, 0.88, 0.52);
			glTranslated(-0.14, 0, 0);
			glutSolidSphere(0.02, 15, 15);
	}
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture_apple);
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	if (spheres.size() == 0) {
		spheres.resize(7);
		random_fill_apples();
	}
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	
	glTranslated(-2.4, -0.5, 0);
	glRotated(34, 5, -2, 0.5);
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_QUADS);
	glBindTexture(GL_TEXTURE_2D, texture_h);
	glTexCoord2d(0,0); glVertex3f(-2, -2, -6);
	glTexCoord2d(0,3) ;glVertex3f(4, -2, -6);
	glTexCoord2d(2,3); glVertex3f(4, -2, 2);
	glTexCoord2d(2, 0); glVertex3f(-2, -2, 2);
	
	glVertex3f(-2, 2, 2);
	glVertex3f(-2, -2, 2);
	glVertex3f(-2, -2, -6);
	glVertex3f(-2, 2, -6);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glLineWidth(5);
	glBegin(GL_LINES);
	glColor3d(0, 0, 0);
	glVertex3d(0, -2, 2);
	glVertex3d(0, -2, -6);
	glVertex3d(2, -2, 2); 
	glVertex3d(2, -2, -6);
	glVertex3d(-2, -2, 0);
	glVertex3d(4, -2, 0);
	glVertex3d(-2, -2, -2);
	glVertex3d(4, -2, -2);
	glVertex3d(-2, -2, -4);
	glVertex3d(4, -2, -4);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, texture_apple);
	draw_hedgehog();
	draw_apples();
	glPopMatrix();
	glFlush();
	glutSwapBuffers();
}


void del_apple(pointx2 point) {
	for (int i = 0; i < spheres.size(); i++) {
		if (spheres[i].i == point.i && spheres[i].j == point.j) {
			spheres.erase(spheres.begin() + i);
			i--;
		}
	}
}

void processNormalKeys(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_UP: //up
		if (current_hedgehog.j < 3) {
			current_hedgehog.j++;
			del_apple(current_hedgehog);
			turn = 2;
		}
		break;
	case GLUT_KEY_DOWN: //down
		if (current_hedgehog.j > 0) {
			current_hedgehog.j--;
			del_apple(current_hedgehog);
			turn = 3;
		}
		break;
	case GLUT_KEY_LEFT: //left
		if (current_hedgehog.i > 0) {
			current_hedgehog.i--;
			del_apple(current_hedgehog);
			turn = 1;
		}
		break;
	case GLUT_KEY_RIGHT: //right
		if (current_hedgehog.i < 2) {
			current_hedgehog.i++;
			del_apple(current_hedgehog);
			turn = 0;
		}
		break;
	}
}

void main()
{
	fill_matrix_centre();
	static bool is_filled = 0;
	if (!is_filled) {
		random_fill_apples();
		hedgehog_pos();
		is_filled = 1;
	}
	float pos[4] = { -5,5,5,5 };
	float dir[3] = { 4.5,2.5, 0 };
	glutInitWindowPosition(50, 10);
	glutInitWindowSize(1000, 1000);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	glutCreateWindow("Sweet hedgehog");
	glutSpecialFunc(processNormalKeys);
	glutDisplayFunc(display);
	
	glutIdleFunc(display);
	glutReshapeFunc(resize);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glLightfv(GL_LIGHT0, GL_POSITION, pos);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, dir);
	float ambient[4] = { 0.7, 0.5, 0.5, 1 };
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);

		Load_Texture((char*)"grass.bmp", texture_grass);
		Load_Texture((char*)"h.bmp", texture_h);
		Load_Texture((char*)"app1.bmp", texture_apple);

	glutMainLoop();
}