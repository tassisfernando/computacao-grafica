#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

//vari�veis para o controle da transla��o
GLfloat posicaoX=0, posicaoY=0;

//vari�vel para o controle da escala nos eixos X e Y
GLfloat escala=1;

//vari�vel para o controle do angulo de rota��o no eixo Z
GLfloat  angulo=0;

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

    // Aplica uma transla��o sobre a casinha que ser� desenhada
    glTranslatef(posicaoX, posicaoY, 0.0f);

    // Aplica uma rota��o sobre a casinha que ser� desenhada
    glRotatef(angulo, 0.0f, 0.0f, 1.0f);

    // Aplica uma escala sobre a casinha que ser� desenhada
    glScalef(escala, escala, 1.0f);


    // Desenha uma casinha composta de um quadrado e um tri�ngulo

    // Altera a cor do desenho para azul
    glColor3f(0.0f, 0.0f, 1.0f);
    // Desenha a casa
    glBegin(GL_QUADS);
    glVertex2f(-15.0f,-15.0f);
    glVertex2f(-15.0f,  5.0f);
    glVertex2f( 15.0f,  5.0f);
    glVertex2f( 15.0f,-15.0f);
    glEnd();

    // Altera a cor do desenho para branco
    glColor3f(1.0f, 1.0f, 1.0f);
    // Desenha a porta e a janela
    glBegin(GL_QUADS);
    glVertex2f(-4.0f,-14.5f);
    glVertex2f(-4.0f,  0.0f);
    glVertex2f( 4.0f,  0.0f);
    glVertex2f( 4.0f,-14.5f);
    glVertex2f( 7.0f,-5.0f);
    glVertex2f( 7.0f,-1.0f);
    glVertex2f(13.0f,-1.0f);
    glVertex2f(13.0f,-5.0f);
    glEnd();

    // Altera a cor do desenho para azul
    glColor3f(0.0f, 0.0f, 1.0f);
    // Desenha as "linhas" da janela
    glBegin(GL_LINES);
    glVertex2f( 7.0f,-3.0f);
    glVertex2f(13.0f,-3.0f);
    glVertex2f(10.0f,-1.0f);
    glVertex2f(10.0f,-5.0f);
    glEnd();

    // Altera a cor do desenho para vermelho
    glColor3f(1.0f, 0.0f, 0.0f);
    // Desenha o telhado
    glBegin(GL_TRIANGLES);
    glVertex2f(-15.0f, 5.0f);
    glVertex2f(  0.0f,17.0f);
    glVertex2f( 15.0f, 5.0f);
    glEnd();

    // Executa os comandos OpenGL
    glFlush();
}

// Fun��o callback chamada quando o tamanho da janela � alterado
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
    GLsizei largura, altura;

    // Evita a divisao por zero
    if(h == 0) h = 1;

    // Atualiza as vari�veis
    largura = w;
    altura = h;

    // Especifica as dimens�es da Viewport
    glViewport(0, 0, largura, altura);

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
