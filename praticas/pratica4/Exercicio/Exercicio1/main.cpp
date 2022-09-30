#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <math.h>

GLsizei largura, altura;

//vari�veis para o controle da transla��o
GLfloat posicaoX=0, posicaoY=0;

//vari�vel para o controle da escala nos eixos X e Y
GLfloat escala=1;

//vari�vel para o controle do angulo de rota��o no eixo Z
GLfloat  angulo=0;

// Função callback chamada para fazer o desenho
void DesenhaCirculo(int nVertices, GLfloat red, GLfloat green, GLfloat blue)
{
    float angulo, incremento;

    // Especifica que a cor corrente é vermelha RGB
    glColor3f(red, green, blue);

    // Especifica o tamanho do ponto
    glPointSize(4.0f);

    incremento = (2 * M_PI) / nVertices; // 7 é o número de vértices

    // Desenha um círculo de pontos
    glBegin(GL_TRIANGLE_FAN);
    for(angulo=0; angulo<2*M_PI; angulo+=incremento)
    {
        glVertex2f(20*cos(angulo),20*sin(angulo));
    }
    glEnd();
}

void DesenhaQuadrado(GLfloat red, GLfloat green, GLfloat blue)
{
    // Altera a cor do desenho para azul
    glColor3f(red, green, blue);

    // Desenha a casa
    glBegin(GL_QUADS);
    glVertex2f(-15.0f,-15.0f);
    glVertex2f(-15.0f, 15.0f);
    glVertex2f( 15.0f, 15.0f);
    glVertex2f( 15.0f,-15.0f);
    glEnd();
}

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

    glViewport(0, 0, largura, altura);

    glRotatef(angulo, 0.0f, 0.0f, 1.0f);

    // Aplica uma transla��o sobre a casinha que ser� desenhada
    glTranslatef(posicaoX, posicaoY, 0.0f);

    // Aplica uma rota��o sobre a casinha que ser� desenhada
    glScalef(escala/2, escala/2, 1.0f);

    DesenhaCirculo(10, 1.0f, 0.0f, 1.0f);

    //Desenha os quadrados
    glPushMatrix();
    glTranslatef(-largura/8, -altura/8, 0.0f);
    DesenhaQuadrado(0.0f, 1.0f, 1.0f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-largura/8, altura/8, 0.0f);
    DesenhaQuadrado(0.0f, 1.0f, 0.0f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(largura/8, -altura/8, 0.0f);
    DesenhaQuadrado(0.0f, 0.0f, 1.0f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(largura/8, altura/8, 0.0f);
    DesenhaQuadrado(1.0f, 0.0f, 0.0f);
    glPopMatrix();

    // Executa os comandos OpenGL
    glFlush();
}

// Fun��o callback chamada quando o tamanho da janela � alterado

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

// Fun��o callback chamada para gerenciar eventos de teclas
void Teclado (unsigned char key, int x, int y)
{
    if (key == 27)
        exit(0);
}

void TeclasEspeciais (int key, int x, int y)
{

    switch (key)
    {
    case GLUT_KEY_LEFT:
        posicaoX--;
        break;
    case GLUT_KEY_RIGHT:
        posicaoX++;
        break;
    case GLUT_KEY_UP:
        posicaoY++;
        break;
    case GLUT_KEY_DOWN:
        posicaoY--;
        break;
    case GLUT_KEY_PAGE_UP:
        angulo++;
        break;
    case GLUT_KEY_PAGE_DOWN:
        angulo--;
        break;
    case GLUT_KEY_HOME:
        escala++;
        break;
    case GLUT_KEY_END:
        escala--;
        break;
    }

    Desenha();
}

// Fun��o respons�vel por inicializar par�metros e vari�veis
void Inicializa (void)
{
    // Define a cor de fundo da janela de visualiza��o como branca
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
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
    glutInitWindowSize(450,450);

    // Cria a janela passando como argumento o t�tulo da mesma
    glutCreateWindow("Desenho de uma casa com translacao, rotacao e escala");

    // Registra a fun��o callback de redesenho da janela de visualiza��o
    glutDisplayFunc(Desenha);

    // Registra a fun��o callback de redimensionamento da janela de visualiza��o
    glutReshapeFunc(AlteraTamanhoJanela);

    // Registra a fun��o callback para tratamento das teclas ASCII
    glutKeyboardFunc (Teclado);

    // Registra a fun��o callback para tratamento das teclas Especiais
    glutSpecialFunc(TeclasEspeciais);

    // Chama a fun��o respons�vel por fazer as inicializa��es
    Inicializa();

    // Inicia o processamento e aguarda intera��es do usu�rio
    glutMainLoop();

    return 0;
}
