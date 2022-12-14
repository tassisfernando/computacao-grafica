
/*
 * GLUT Shapes Demo
 *
 * Written by Nigel Stewart November 2003
 *
 * This program is test harness for the sphere, cone
 * and torus shapes in GLUT.
 *
 * Spinning wireframe and smooth shaded shapes are
 * displayed until the ESC or q key is pressed.  The
 * number of geometry stacks and slices can be adjusted
 * using the + and - keys.
 */

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
using namespace std;

// Vari�veis que guardam a transla��o que ser� aplicada
// sobre a casinha
GLfloat Tx;
GLfloat Ty;

// Vari�veis que guardam os valores m�nimos de x e y da
// casinha
GLfloat minX, maxX;
GLfloat minY, maxY;

// Vari�veis que guardam o tamanho do incremento nas
// dire��es x e y (n�mero de pixels para se mover a
// cada intervalo de tempo)
GLfloat xStep;
GLfloat yStep;

// Vari�veis que guardam a largura e altura da janela
GLfloat windowXmin, windowXmax;
GLfloat windowYmin, windowYmax;

GLfloat ang1 = 0;

GLsizei largura, altura;


void DesenhaObjeto() {
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(5, 5);
    glVertex2f(11, 5);
    glVertex2f(8, 11);
    glEnd();
}

// Fun��o callback de redesenho da janela de visualiza��o
void Desenha(void)
{
	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT);
    DesenhaObjeto(); // 1
    glPushMatrix();
    glScaled(1 , -1, 1);
    DesenhaObjeto(); // 2
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-16, 0, 0);
    DesenhaObjeto(); // 3
    glPushMatrix();
    glScaled(1 , -1, 1);
    DesenhaObjeto(); // 4
    glPopMatrix();
    glPopMatrix();
    glFlush();
}

// Fun��o respons�vel por inicializar par�metros e vari�veis
void Inicializa (void)
{
	// Define a cor de fundo da janela de visualiza��o como branca
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	// Inicializa��o das vari�veis globais
	xStep = yStep = 0.1f;
	Tx = Ty = 0.0f;
	minX = -5.1f;
	maxX =  5.1f;
	minY = -5.1f;
	maxY =  5.1f;
	windowXmin = windowYmin = -40.0f;
	windowXmax = windowYmax = 40.0f;
}


// Programa Principal
int main(int argc, char *argv[])
{
    // Utilizada para inicializar a biblioteca GLUT
    glutInit(&argc, argv);

	// Define do modo de opera��o da GLUT
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

	// Especifica a posi��o inicial da janela GLUT
	glutInitWindowPosition(5,5);

	// Especifica o tamanho inicial em pixels da janela GLUT
	glutInitWindowSize(450,450);

	// Cria a janela passando como argumento o t�tulo da mesma
	glutCreateWindow("Exercicio 08");

	// Registra a fun��o callback de redesenho da janela de visualiza��o
	glutDisplayFunc(Desenha);

	// Chama a fun��o respons�vel por fazer as inicializa��es
	Inicializa();

	// Inicia o processamento e aguarda intera��es do usu�rio
	glutMainLoop();

	return 0;
}
