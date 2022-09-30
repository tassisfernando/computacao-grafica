
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>

GLfloat xf, yf, win;
GLsizei largura, altura;

// Fun��o callback de redesenho da janela de visualiza��o
void Desenha(void)
{
	// Muda para o sistema de coordenadas do modelo
	glMatrixMode(GL_MODELVIEW);
	// Inicializa a matriz de transforma��o corrente
	glLoadIdentity();

	//o comando que limpa a janela de visualiza��o foi desativado nesse ponto
	//glClear(GL_COLOR_BUFFER_BIT);

    //desenha o ponto
    glPointSize(7.0f);
    glBegin(GL_POINTS);
       glVertex2i(xf, yf);
    glEnd();

	glFlush();
}

// Fun��o callback chamada quando o tamanho da janela � alterado
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
    // Especifica as dimensões da Viewport
    glViewport(0, 0, w, h);
    largura = w;
    altura = h;

    // Inicializa o sistema de coordenadas
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D (-win, win, -win, win);
}

// Função callback chamada para gerenciar eventos do mouse
void GerenciaMouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON){
        if (state == GLUT_DOWN) {
          // Troca o tamanho do retângulo, que vai do centro da
          // janela até a posição onde o usuário clicou com o mouse
          xf = ( (2 * win * x) / largura) - win;
          yf = ( ( (2 * win) * (y-altura) ) / -altura) - win;
        }
    }
    glutPostRedisplay();
}

// Fun��o callback chamada para gerenciar eventos de teclas
void GerenciaTeclado(unsigned char key, int x, int y)
{
    if (key == 27)
		exit(0);

    switch (key) {
        case 'R':
        case 'r':// muda a cor corrente para vermelho
             glColor3f(1.0f, 0.0f, 0.0f);
             break;
        case 'G':
        case 'g':// muda a cor corrente para verde
             glColor3f(0.0f, 1.0f, 0.0f);
             break;
        case 'B':
        case 'b':// muda a cor corrente para azul
             glColor3f(0.0f, 0.0f, 1.0f);
             break;
    }
}

// Fun��o respons�vel por inicializar par�metros e vari�veis
void Inicializa (void)
{
	// Define a cor de fundo da janela de visualiza��o como branca
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	//limpa a tela
    glClear(GL_COLOR_BUFFER_BIT);

    //define a cor preta como inicial
    glColor3f(0.0f, 0.0f, 0.0f);

	// Inicializa��o das vari�veis globais
    xf=0.0f;
    yf=0.0f;
	win = 250.0f;

}


// Programa Principal
int main(int argc, char *argv[])
{
    // Utilizada para inicializar a biblioteca GLUT
    glutInit(&argc, argv);

	// Define do modo de opera��o da GLUT
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	// Especifica a posi��o inicial da janela GLUT
	glutInitWindowPosition(5,5);

	// Especifica o tamanho inicial em pixels da janela GLUT
	glutInitWindowSize(500,500);

	// Cria a janela passando como argumento o t�tulo da mesma
	glutCreateWindow("Criacao de pontos com o mouse");

	// Registra a fun��o callback de redesenho da janela de visualiza��o
	glutDisplayFunc(Desenha);

	// Registra a fun��o callback de redimensionamento da janela de visualiza��o
	glutReshapeFunc(AlteraTamanhoJanela);

	// Registra a função callback para tratamento das teclas ASCII
	glutKeyboardFunc (GerenciaTeclado);

	// Registra a função callback para tratamento de mouse
	glutMouseFunc(GerenciaMouse);

	// Chama a fun��o respons�vel por fazer as inicializa��es
	Inicializa();

	// Inicia o processamento e aguarda intera��es do usu�rio
	glutMainLoop();

	return 0;
}
