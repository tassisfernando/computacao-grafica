//*****************************************************
//
// PrimeiroPrograma.cpp
// Um programa OpenGL simples que abre uma janela GLUT
// e desenha um triângulo no centro
//
// Isabel H. Manssour e Marcelo Cohen
// Este código acompanha o livro
// "OpenGL - Uma Abordagem Prática e Objetiva"
//
//*****************************************************

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


// Função callback de redesenho da janela de visualização
void Desenha(void)
{
	// Limpa a janela de visualização com a cor preta
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);

	// Desenha um triângulo no centro da janela
	glLineWidth(3); // Determina a espessura da linha que será desenhada
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

// Função callback chamada para gerenciar eventos de teclas
void Teclado (unsigned char key, int x, int y)
{
	if (key == 27)
		exit(0);
}

// Função responsável por inicializar parâmetros e variáveis
void Inicializa(void)
{
	// Define a janela de visualização 2D
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-1.0,1.0,-1.0,1.0);
	glMatrixMode(GL_MODELVIEW);
}

// Programa Principal
int main(int argc, char *argv[])
{
    // Utilizada para inicializar a biblioteca GLUT
    glutInit(&argc, argv);

	// Define do modo de operação da GLUT
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	// Especifica o tamanho inicial em pixels da janela GLUT
	glutInitWindowSize(400,400);

	// Cria a janela passando como argumento o título da mesma
	glutCreateWindow("Figura 02 - Janela do exercício");

	// Registra a função callback de redesenho da janela de visualização
	glutDisplayFunc(Desenha);

	// Registra a função callback para tratamento das teclas ASCII
	glutKeyboardFunc (Teclado);

	// Chama a função responsável por fazer as inicializações
	Inicializa();

	// Inicia o processamento e aguarda interações do usuário
	glutMainLoop();

	return 0;
}
