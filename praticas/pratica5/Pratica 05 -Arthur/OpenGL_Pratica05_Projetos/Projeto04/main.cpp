
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

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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

int win = 250;

bool stopAnimate = true;

// Fun��o callback de redesenho da janela de visualiza��o
void Desenha(void)
{
	// Muda para o sistema de coordenadas do modelo
	glMatrixMode(GL_MODELVIEW);
	// Inicializa a matriz de transforma��o corrente
	glLoadIdentity();

	// Limpa a janela de visualiza��o com a cor
	// de fundo definida previamente
	glClear(GL_COLOR_BUFFER_BIT);

	// Aplica uma transla��o sobre a casinha
	glTranslatef(Tx, Ty, 0.0f);

	// Desenha uma casinha composta de um quadrado e um tri�ngulo

	// Altera a cor do desenho para azul
	glColor3f(0.0f, 0.0f, 1.0f);
	// Desenha o quadrado
	glBegin(GL_QUADS);
		glVertex2f(-5.0f,-5.0f);
		glVertex2f(-5.0f,  5.0f);
		glVertex2f( 5.0f,  5.0f);
		glVertex2f( 5.0f,-5.0f);
	glEnd();

	//Altera a cor para verde
	glColor3f(0.0f, 1.0f, 0.0f);
	// Desenha circulo
	int vertices = 7;
	int raio = 4;
	float angulo, incremento;

	incremento = (2 * M_PI) / vertices;

	glRotatef(ang1,0.0f,0.0f,1.0f);

	glBegin(GL_POLYGON);
     for(angulo=0; angulo<2*M_PI; angulo+=incremento){
        glVertex2f(raio*cos(angulo),raio*sin(angulo));
        glVertex2d(raio*cos(angulo+incremento), raio*sin(angulo+incremento));
     }
    glEnd();

	// Executa os comandos OpenGL
	glutSwapBuffers();
}

// Fun��o callback chamada quando o tamanho da janela � alterado
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{

	// Evita a divisao por zero
	if(h == 0) h = 1;

	// Atualiza as vari�veis
	largura = w;
	altura = h;

	// Especifica as dimens�es da Viewport
	glViewport(0, 0, largura, altura);

	// Inicializa o sistema de coordenadas de proje��o
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Estabelece a janela de sele��o (esquerda, direita, inferior,
	// superior) mantendo a propor��o com a janela de visualiza��o
	if (largura <= altura)
	{
		gluOrtho2D (-40.0f, 40.0f, -40.0f*altura/largura, 40.0f*altura/largura);
		windowXmin = -40.0f;
		windowXmax =  40.0f;
		windowYmin = -40.0f*altura/largura;
		windowYmax = 40.0f*altura/largura;
	}
	else
	{
		gluOrtho2D (-40.0f*largura/altura, 40.0f*largura/altura, -40.0f, 40.0f);
		windowXmin = -40.0f*largura/altura;
		windowXmax =  40.0f*largura/altura;
		windowYmin = -40.0f;
		windowYmax =  40.0f;
	}
}

// Fun��o callback chamada pela GLUT a cada intervalo de tempo
void Anima(int value)
{
	// Muda a dire��o quando chega na borda esquerda ou direita
	if( (Tx+maxX) > windowXmax || (Tx+minX) < windowXmin )
		xStep = -xStep;

	// Muda a dire��o quando chega na borda superior ou inferior
	if( (Ty+maxY) > windowYmax || (Ty+minY) < windowYmin )
		yStep = -yStep;

	// Move a casinha
	Tx += xStep;
	Ty += yStep;

    ang1 += 0.5;

	// Redesenha a casinha em outra posi��o
	glutPostRedisplay();
	if(stopAnimate)
        glutTimerFunc(10,Anima, 1);
}

// Fun��o callback chamada para gerenciar eventos de teclas
void Teclado (unsigned char key, int x, int y)
{
	if (key == 27)
		exit(0);

    if (key == 80 || key == 112){
        stopAnimate = !stopAnimate;
        if(stopAnimate){
            glutTimerFunc(10, Anima, 1);
        }
    }
}

// Função callback chamada para gerenciar eventos do mouse
void GerenciaMouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON){
        if (state == GLUT_DOWN) {
          // Troca o tamanho do retângulo, que vai do centro da
          // janela até a posição onde o usuário clicou com o mouse
          Tx = ( (2 * windowXmax * x) / largura) - windowXmax;
          Ty = ( ( (2 * windowYmax) * (y-altura) ) / -altura) - windowYmax;
          printf("largura: %d altura: %d\n", largura, altura);
          printf("windowXmax: %d windowYmax: %d\n", windowXmax, windowYmax);
          printf("x: %d  y: %d\n", x, y);
          printf("Tx: %d  Ty: %d", Tx, Ty);
        }
    }
    glutPostRedisplay();
}

// Fun��o respons�vel por inicializar par�metros e vari�veis
void Inicializa (void)
{
	// Define a cor de fundo da janela de visualiza��o como branca
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

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
	glutCreateWindow("Animacao de uma casa");

	// Registra a fun��o callback de redesenho da janela de visualiza��o
	glutDisplayFunc(Desenha);

	// Registra a fun��o callback de redimensionamento da janela de visualiza��o
	glutReshapeFunc(AlteraTamanhoJanela);

	// Registra a fun��o callback para tratamento das teclas ASCII
	glutKeyboardFunc (Teclado);

	// Registra a função callback para tratamento de mouse
	glutMouseFunc(GerenciaMouse);

	// Registra a fun��o callback que ser� chamada a cada intervalo de tempo
	glutTimerFunc(10, Anima, 1);

	// Chama a fun��o respons�vel por fazer as inicializa��es
	Inicializa();

	// Inicia o processamento e aguarda intera��es do usu�rio
	glutMainLoop();

	return 0;
}
