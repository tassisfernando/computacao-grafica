#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


#include <math.h>

void DesenhaEixos(void){
     glBegin(GL_LINES);
       glColor3f(1.0f, 1.0f, 0.0f); //amarelo em RGB
       glVertex2i(0, 20); // linha do eixo Y
       glVertex2i(0, -20);
       glVertex2i(-20, 0);// linha do eixo X
       glVertex2i(20, 0);
     glEnd();
}


void DesenhaTriangulo(){
     glBegin(GL_LINE_LOOP);
       glVertex2f(8.0, 11.0);
       glVertex2f(4.0, 3.0);
       glVertex2f(12.0, 6.0);
     glEnd();
}

void Desenha(void)
{
     //Muda para o sistema de coordenadas do modelo
	 glMatrixMode(GL_MODELVIEW);
	 //Inicializa a matriz de transforma��o corrente
	 glLoadIdentity();

     glClear(GL_COLOR_BUFFER_BIT);

     glLineWidth(2.0f);
     DesenhaEixos();

     glColor3f(1.0, 0.0, 0.0); //vermelho em RGB
     DesenhaTriangulo();

     //Reflexão com relação ao eixo X
     //glScalef(1.0f, -1.0f, 0.0f);

     //Reflexão com relação ao eixo Y
     //glScalef(-1.0f, 1.0f, 0.0f);

     //Reflexão com relação à origem
     glScalef(-1.0f, -1.0f, 0.0f);

     glColor3f(0.0f, 1.0f, 0.0f); //verde em RGB
     DesenhaTriangulo();

     glFlush();
}


// Inicializa par�metros de rendering
void Inicializa (void)
{
    // Define a cor de fundo da janela de visualiza��o como branco
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

// Fun��o callback chamada para gerenciar eventos de teclas
void Teclado (unsigned char key, int x, int y)
{
	if (key == 27)
		exit(0);
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

    glViewport(0, 0, largura, altura);

    // Inicializa o sistema de coordenadas
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Estabelece a janela de sele��o (esquerda, direita, inferior,
    // superior) mantendo a propor��o com a janela de visualiza��o
    if (largura <= altura)
        gluOrtho2D (-20.0f, 20.0f, -20.0f*altura/largura, 20.0f*altura/largura);
    else
        gluOrtho2D (-20.0f*largura/altura, 20.0f*largura/altura, -20.0f, 20.0f);

}
// Programa Principal
int main(int argc, char *argv[])
{
    // Utilizada para inicializar a biblioteca GLUT
    glutInit(&argc, argv);
    // Define do modo de opera��o da GLUT
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    // Especifica o tamanho e localiza��o inicial em pixels da janela GLUT
	glutInitWindowSize(400,400);
	// Cria a janela passando como argumento o t�tulo da mesma
	glutCreateWindow("Projeto 02");
	// Registra a fun��o callback de redesenho da janela de visualiza��o
	glutDisplayFunc(Desenha);
	// Registra a fun��o callback de redimensionamento da janela de visualiza��o
	glutReshapeFunc(AlteraTamanhoJanela);
	// Registra a fun��o callback para tratamento das teclas ASCII
	glutKeyboardFunc (Teclado);
	// Chama a fun��o respons�vel por fazer as inicializa��es
	Inicializa();
	// Inicia o processamento e aguarda intera��es do usu�rio
	glutMainLoop();
}


