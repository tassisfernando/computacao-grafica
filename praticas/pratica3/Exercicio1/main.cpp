#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <math.h>

GLsizei largura, altura;

// Função callback chamada para fazer o desenho
void DesenhaPontos(int nVertices)
{
     float angulo, incremento;

     // Especifica que a cor corrente é vermelha RGB
     glColor3f(1.0f, 0.0f, 0.0f);

	 // Especifica o tamanho do ponto
	 glPointSize(4.0f);

     incremento = (2 * M_PI) / nVertices; // 7 é o número de vértices

     // Desenha um círculo de pontos
     glBegin(GL_POINTS);
     for(angulo=0; angulo<2*M_PI; angulo+=incremento){
        glVertex2f(20*cos(angulo),20*sin(angulo));
     }
     glEnd();
}

// Função callback chamada para fazer o desenho
void DesenhaCirculos(int nVertices)
{
     float angulo, incremento;

     // Especifica que a cor corrente é vermelha RGB
     glColor3f(1.0f, 0.0f, 0.0f);

	 // Especifica o tamanho do ponto
	 glPointSize(4.0f);

     incremento = (2 * M_PI) / nVertices; // 7 é o número de vértices

     // Desenha um círculo de pontos
     glBegin(GL_LINE_LOOP);
     for(angulo=0; angulo<2*M_PI; angulo+=incremento){
        glVertex2f(20*cos(angulo),20*sin(angulo));
     }
     glEnd();
}

void Desenha()
{
    // Limpa a janela de visualiza��o com a cor
	// de fundo definida previamente
	glClear(GL_COLOR_BUFFER_BIT);

    glViewport(largura/2, altura/2, largura/2, altura/2);
    DesenhaCirculos(10);

    // left bottom
    glViewport(0, altura/2, largura/2, altura/2);
    DesenhaCirculos(30);

    // top right
    glViewport(largura/2, 0, largura/2, altura/2);
    DesenhaCirculos(7);

    // top left
    glViewport(0, 0, largura/2, altura/2);
    DesenhaPontos(7);

    // Executa os comandos OpenGL
	glFlush();
}

// Função callback chamada quando o tamanho da janela é alterado
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
	// Evita a divisao por zero
	if(h == 0) h = 1;

	// Atualiza as vari�veis
	largura= w;
	altura = h;

	// Inicializa o sistema de coordenadas
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Estabelece a janela de sele��o (esquerda, direita, inferior,
	// superior) mantendo a propor��o com a janela de visualiza��o
	if (largura <= altura)
		gluOrtho2D (-40.0f, 40.0f, -40.0f*altura/largura, 40.0f*altura/largura);
	else
		gluOrtho2D (-40.0f*largura/altura, 40.0f*largura/altura, -40.0f, 40.0f);
}

// Função callback chamada para gerenciar eventos de teclas
void Teclado (unsigned char key, int x, int y)
{
	if (key == 27)
		exit(0);
}

// Inicializa parâmetros de rendering
void Inicializa (void)
{
    // Define a cor de fundo da janela de visualização como preta
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

// Programa Principal
int main(int argc, char *argv[])
{
    // Utilizada para inicializar a biblioteca GLUT
    glutInit(&argc, argv);
    // Define do modo de operação da GLUT
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    // Especifica a posi��o inicial da janela GLUT
	glutInitWindowPosition(5,5);
	// Especifica o tamanho inicial em pixels da janela GLUT
	glutInitWindowSize(450,450);
	// Cria a janela passando como argumento o título da mesma
	glutCreateWindow("Exercício 01");
	// Registra a função callback de redesenho da janela de visualização
	glutDisplayFunc(Desenha);
	// Registra a função callback de redimensionamento da janela de visualização
	glutReshapeFunc(AlteraTamanhoJanela);
	// Registra a função callback para tratamento das teclas ASCII
	glutKeyboardFunc (Teclado);
	// Chama a função responsável por fazer as inicializações
	Inicializa();
	// Inicia o processamento e aguarda interações do usuário
	glutMainLoop();
}


