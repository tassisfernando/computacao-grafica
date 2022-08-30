//*****************************************************
//
// PrimeiroPrograma.cpp
// Um programa OpenGL simples que abre uma janela GLUT
// e desenha um tri�ngulo no centro
//
// Isabel H. Manssour e Marcelo Cohen
// Este c�digo acompanha o livro
// "OpenGL - Uma Abordagem Pr�tica e Objetiva"
//
//*****************************************************

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


// Fun��o callback de redesenho da janela de visualiza��o
void Desenha(void)
{
	// Limpa a janela de visualiza��o com a cor preta
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);

	// Desenha um tri�ngulo no centro da janela
	glLineWidth(3); // Determina a espessura da linha que ser� desenhada
    glBegin(GL_TRIANGLES);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex2f(-0.2,0.1);
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex2f(0.0,0.22);
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex2f(0.2,0.1);
    glEnd();

    // Define a cor de desenho: azul
	glColor3f(0, 0, 1);

    glBegin(GL_LINE_LOOP);
        glVertex3f(-0.2, 0, 0);
        glVertex3f(-0.2, 0.1, 0);
        glVertex3f(0.2, 0.1, 0);
        glVertex3f(0.2, 0, 0);
    glEnd();

    glColor3f(1, 1, 1);

	glBegin(GL_LINES);
        glVertex3f(-1, 0, 0);
        glVertex3f(1, 0, 0);
        glVertex3f(0, -1, 0);
        glVertex3f(0, 1, 0);
	glEnd();



	//Executa os comandos OpenGL
	glFlush();
}

// Fun��o callback chamada para gerenciar eventos de teclas
void Teclado (unsigned char key, int x, int y)
{
	if (key == 27)
		exit(0);
}

// Fun��o respons�vel por inicializar par�metros e vari�veis
void Inicializa(void)
{
	// Define a janela de visualiza��o 2D
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-1.0,1.0,-1.0,1.0);
	glMatrixMode(GL_MODELVIEW);
}

// Programa Principal
int main(int argc, char *argv[])
{
    // Utilizada para inicializar a biblioteca GLUT
    glutInit(&argc, argv);

	// Define do modo de opera��o da GLUT
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	// Especifica o tamanho inicial em pixels da janela GLUT
	glutInitWindowSize(400,400);

	// Cria a janela passando como argumento o t�tulo da mesma
	glutCreateWindow("Figura 02 - Janela do exerc�cio");

	// Registra a fun��o callback de redesenho da janela de visualiza��o
	glutDisplayFunc(Desenha);

	// Registra a fun��o callback para tratamento das teclas ASCII
	glutKeyboardFunc (Teclado);

	// Chama a fun��o respons�vel por fazer as inicializa��es
	Inicializa();

	// Inicia o processamento e aguarda intera��es do usu�rio
	glutMainLoop();

	return 0;
}
