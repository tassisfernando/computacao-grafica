#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


#include <math.h>

// Função callback chamada para fazer o desenho
void Desenha(void)
{
     float angulo, incremento;

     // Limpa a janela de visualização com a cor de fundo especificada
     glClear(GL_COLOR_BUFFER_BIT);

    // Desenha os eixos
     glColor3f(1, 1, 0);
     glLineWidth(3);
     glBegin(GL_LINES);
        glVertex3f(-100, 0, 0);
        glVertex3f(100, 0, 0);
        glVertex3f(0, -100, 0);
        glVertex3f(0, 100, 0);
    glEnd();

    // Especifica que a cor corrente é vermelha RGB - função 1
     glColor3f(0.0f, 0.0f, 1.0f);
     glLineWidth(2);
     // Desenha um círculo de pontos
     glBegin(GL_LINE_STRIP);
        glVertex2f(-3, 15);
        glVertex2f(-2, 8);
        glVertex2f(-1, 3);
        glVertex2f(0, 0);
        glVertex2f(1, -1);
        glVertex2f(2, 0);
        glVertex2f(3, 3);
        glVertex2f(4, 8);
     glEnd();

     // Especifica que a cor corrente é vermelha RGB - função 2
     glColor3f(1.0f, 0.0f, 0.0f);
     glLineWidth(2);
     // Desenha um círculo de pontos
     glBegin(GL_LINE_STRIP);
        glVertex2f(-3, -18);
        glVertex2f(-2, -10);
        glVertex2f(-1, -4);
        glVertex2f(0, 0);
        glVertex2f(1, 2);
        glVertex2f(2, 2);
        glVertex2f(3, 0);
        glVertex2f(4, -4);
        glVertex2f(5, -10);
        glVertex2f(6, -18);
     glEnd();

     // Executa os comandos OpenGL
     glFlush();
}


// Inicializa parâmetros de rendering
void Inicializa (void)
{
    // Define a cor de fundo da janela de visualização como preta
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

// Função callback chamada para gerenciar eventos de teclas
void Teclado (unsigned char key, int x, int y)
{
	if (key == 27)
		exit(0);
}

// Função callback chamada quando o tamanho da janela é alterado
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{

    GLsizei largura, altura;

    // Evita a divisao por zero
    if(h == 0) h = 1;

    // Atualiza as variáveis
    largura = w;
    altura = h;

    glViewport(0, 0, largura, altura);

    // Inicializa o sistema de coordenadas
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Estabelece a janela de seleção (esquerda, direita, inferior,
    // superior) mantendo a proporção com a janela de visualização
    if (largura <= altura)
        gluOrtho2D (-40.0f, 40.0f, -40.0f*altura/largura, 40.0f*altura/largura);
    else
        gluOrtho2D (-40.0f*largura/altura, 40.0f*largura/altura, -40.0f, 40.0f);

}
// Programa Principal
int main(int argc, char *argv[])
{
    // Utilizada para inicializar a biblioteca GLUT
    glutInit(&argc, argv);
    // Define do modo de operação da GLUT
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    // Especifica o tamanho e localização inicial em pixels da janela GLUT
	glutInitWindowSize(400,400);
	// Cria a janela passando como argumento o título da mesma
	glutCreateWindow("Exercício 02");
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


