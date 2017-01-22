// COPYRIGHT(C) ANDREY TKACHOV (DK_31)
#include <math.h>
#include <conio.h>
#include <locale.h>
#include <stdio.h>
#include <string.h>
//#include <stdafx.h>
#include <windows.h>
#include "../glut/glut.h"
#include <iostream>

/* GRAPHICS ПЕРЕМЕННЫЕ*/
double long fx;
int z;
float x;
/* END GRAPHICS*/



/* GRAPHICS FUNCTIONS*/

void RenderWhiteString(float x, float y, void *font, const char* string)
{
	char *c;

	glColor3f(1.0, 1.0, 1.0);
	glRasterPos2i(x, y);

	//glutBitmapCharacter(font, string);
}


void Initialize()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear (GL_COLOR_BUFFER_BIT);
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	glColor3f(1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 400, 0, 400); // ORTHO
								//glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
}

void Draw()
{
	char text[10];
	int i;
	int GradY = 35, GradX = 35;
	float Gx = 0, Gy = 0;
	float Gr[2];
	// CHARACTERS 
	text[1] = '1';
	text[2] = '2';
	text[3] = '3';
	text[4] = '4';
	text[5] = '5';
	text[6] = '6';
	text[7] = '7';
	text[8] = '8';
	text[9] = '9';
	text[0] = '0';


	// 0;0 НИЖНИЙ ЛЕВЫЙ УГОЛ
	glBegin(GL_LINE_STRIP);
	glColor3f(1.0, 1.0, 1.0);
	glVertex2i(20, 370);
	glVertex2i(20, 20);
	glVertex2i(370, 20);
	glEnd();
	// END OSI
	// STRELO4KI 
	glBegin(GL_LINE_STRIP);
	glColor3f(1.0, 1.0, 1.0);
	glVertex2i(15, 350);
	glVertex2i(20, 370);
	glVertex2i(25, 350);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glColor3f(1.0, 1.0, 1.0);
	glVertex2i(350, 15);
	glVertex2i(370, 20);
	glVertex2i(350, 25);
	glEnd();
	// NADPISI X,Y
	glRasterPos2i(380, 20);

	glutBitmapCharacter(GLUT_BITMAP_8_BY_13, 'X');
	glRasterPos2i(20, 380);

	glutBitmapCharacter(GLUT_BITMAP_8_BY_13, 'Y');
	// END STRELO4KI 	
	//text[0] = "0";
	//RenderString(15, 15, GLUT_BITMAP_TIMES_ROMAN_24, "0");
	glRasterPos2i(10, 10);

	glutBitmapCharacter(GLUT_BITMAP_8_BY_13, text[0]);
	// OTMETKI


	for (i = 1; i<10; i++) {
		glBegin(GL_LINES);
		//glColor3f(1.0, 1.0, 1.0);
		glVertex2i(20 + GradX*i, 15);
		glVertex2i(20 + GradX*i, 25);
		glEnd();
		glRasterPos2i(20 + GradX*i, 8);
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, text[i]);
		//glFlush(); 
	}
	for (i = 1; i<10; i++) {
		glBegin(GL_LINES);
		//glColor3f(1.0, 1.0, 1.0);
		glVertex2i(15, 20 + GradY*i);
		glVertex2i(25, 20 + GradY*i);
		glEnd();
		glRasterPos2i(9, 20 + GradY*i);
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, text[i]);
		//glFlush(); 
	}
	// END OTMETKI
	Gr[0] = 0.0;
	Gr[1] = 1.0;
	while (Gx <= 9 && Gy <= 10) {
		Gy = cosh(Gx);
		glBegin(GL_LINES);
		//glColor3f(1.0, 1.0, 1.0);
		glVertex2i(20 + Gr[0] * GradX, 20 + Gr[1] * GradY);
		glVertex2i(20 + Gx*GradX, 20 + Gy*GradY);
		glEnd();
		Gx = Gx + 0.01;
		Gr[0] = Gx;
		Gr[1] = Gy;
	}

	glBegin(GL_LINES);
	glColor3f(1.0, 0.0, 1.0);
	glVertex2i(20 + x*GradX + 5, 20 + fx*GradY + 5);
	glVertex2i(20 + x*GradX - 5, 20 + fx*GradY - 5);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(1.0, 0.0, 1.0);
	glVertex2i(20 + x*GradX + 5, 20 + fx*GradY - 5);
	glVertex2i(20 + x*GradX - 5, 20 + fx*GradY + 5);
	glEnd();


	glFlush();

}


int PointCount(char *mas) {
	int pointC;

	return 0;
}
/* END GRAPHICS FUNCTIONS*/

int check(char *mas);
float step(float y, int n);
double long factorial(int n);
void main(int argc, char **argv)
{
	int n, i;
	double long fc;
	char num[100];
	float e;
	double long st, f4;
	setlocale(LC_ALL, "Russian");
	//printf("Вводите только положительные и отрицательные числа\n");
	std::cout << "Функция cosh(x) = Гиберболический косинус\n";
	std::cout << "Вводите только положительные числа\nОтрицательные будут взяты по модулю,дробные разрешены\nПрограма считает корректно числа от 0 до 10\n";
	// ДЛЯ ЧИСЕЛ БОЛЬШЕ 11 НЕЛЬЗЯ
metka:

	do
	{
		//printf("Введите число Х\n");
		std::cout << "Введите число Х\n";
		//scanf("%s",&num);
		std::cin >> num;
		if (!check(num))
		{
			//printf("Некорректное число.Повторите ввод\n");
			std::cout << "Некорректное число. Повторите ввод\n";
		}
		x = atof(num);
		if (x>11) {
			std::cout << "Число не из диапазона. Повторите ввод\n";
			goto metka;
		}
	} while (!check(num));


	do
	{
		//printf ("Введите точность e\n");
		std::cout << "Введите точность е\n";
		//scanf("%s",&num);
		std::cin >> num;
		if (!check(num))
		{
			//printf("Некорректное число.Повторите ввод\n");
			std::cout << "Некорректное число. Повторите ввод\n";
		}
		e = atof(num);
	} while (!check(num));
	//printf("Точка функции %f\n",x);
	//printf("Точность %f\n",e);
	std::cout << "Точка функции : " << x << "\n";
	std::cout << "Точность е : " << e << "\n";
	fx = 0;
	f4 = 1;
	fx = fx + f4;
	i = 1;
	while (f4 >= e) {
		st = step(x, 2 * i);
		fc = factorial(2 * i);
		f4 = st / fc;
		fx = fx + f4;
		i++;
		//printf("Степень Икса - %f \n Факториал - %d \n Член - %f \n Общее значение - %f \n Показатель степени - %d \n",st,fc,f4,fx,i);
	}
	//printf("\nВаш результат функции - %f\a",fx);
	std::cout << "\nВаш результат функции : " << fx << "\a";
	//printf("\nРезультат функции вычисленого компютером - %f\a",cosh(x));
	std::cout << "\nРезультат функции вычисленого компютером : " << cosh(x) << "\a";
	std::cout << "\nАбсолютная погрешность : " << fabs(fx - cosh(x)) << "\a";
	std::cout << "\nОтносительная погрешность : " << (fabs(fx - cosh(x)) * 100) / cosh(x) << "%\a";
	//printf("\nДля завершения программы нажмите любую кнопку\a");
	std::cout << "\nДля отображения графика нажмите пробел\nДля завершения программы нажмите любую кнопку кроме пробела\a";
	if (_getch() == 32) {
		//GRAPHIC INTERFACE
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
		glutInitWindowSize(400, 400);
		glutInitWindowPosition(0, 0);
		glutCreateWindow("График Функции y=cosh(x)");
		Initialize();
		glutDisplayFunc(Draw);
		glutMainLoop();
	}
	//_getch();
}

// ФУНКЦИЯ ПРОВЕРКИ ЧИСЛА
int check(char *mas)
{
	int i, j;
	int to4ka, minus;
	to4ka = 0;
	z = 1;
	minus = 0;
	if (strlen(mas)>10) {
		z = 0;
	}
	for (i = 0; i<strlen(mas); i++)

	{
		if (mas[i] != '0' && mas[i] != '1' && mas[i] != '2' && mas[i] != '3' && mas[i] != '4' && mas[i] != '5' && mas[i] != '6' && mas[i] != '7' && mas[i] != '8' && mas[i] != '9' && mas[i] != ',' && mas[i] != '-' && mas[i] != '+')
		{
			z = 0;
		}
		else if (mas[i] == ',' && to4ka == 0) {
			to4ka = 1;
		}
		else if (mas[i] == ' ') {
			z = 0;
		}
		else if (mas[i] == ',' && to4ka == 1) {
			z = 0;
		}
		else if (mas[i] == '-' && i == 0 && minus != 2) {
			minus = 1;
			mas[0] = '0';
		}
		else if (mas[i] == '-' && i != 1 && minus == 2) {
			z = 0;
		}
		else if (mas[i] == '-' && i != 0) {
			z = 0;
		}
		else if (mas[i] == '+' && i == 0) {
			minus = 0;
			/*for (j=0; j<strlen(mas)-1; j++){
			mas[j]=mas[j+1];

			}
			*/
			mas[0] = '0';
			minus = 2;
		}
		else if (mas[i] == '+' && i != 0) {
			z = 0;
		}

	}

	return z;
}

// СТЕПЕНЬ
float step(float y, int n) {
	float rez = y;
	for (int i = 1; i<n; i++) {
		rez = rez*y;
	}
	return rez;
}

// ФАКТОРИАЛ
double long factorial(int n) {
	double long fact = 1;
	for (int i = 1; i <= n; i++) {
		fact = fact * i;
	}
	return fact;
}
