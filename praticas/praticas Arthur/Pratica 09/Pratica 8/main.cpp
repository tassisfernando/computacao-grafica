
//*****************************************************
//
// Exemplo3DComZoomEPan.cpp
// Um programa OpenGL simples que abre uma janela GLUT,
// desenha um "torus" e permite fazer: zoom in e
// zoom out quando os botões do mouse são pressionados
// (utiliza a projeção perspectiva); e pan quando as
// teclas page up, page down, seta para cima, seta para
// baixo, seta para esquerda e seta para direita são
// pressionadas.
//
// Marcelo Cohen e Isabel H. Manssour
// Este código acompanha o livro
// "OpenGL - Uma Abordagem Prática e Objet

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <math.h>


GLfloat angle, fAspect;
GLfloat deslocamentoX, deslocamentoY, deslocamentoZ;
GLfloat angleRotate = 0;
GLfloat angleOrbita = 0;
GLint raio = 150;
GLfloat angulo = 0;
GLfloat incremento;
bool cameraorbital = false;

static int slices = 20;
static int stacks = 20;

// Funcao para desenhar linhas
void desenhaTerreno()
{
	float L = 500.0;
	float incr = 10.0;
	float y = 0.2;
	glColor3f(0.0f, 0.0f, 0.0f);

	for (float i = -L; i <= L; i += incr)
	{
	    glBegin(GL_LINES);
            // Verticais
            glVertex3f(i,y,-L);
            glVertex3f(i,y,L);

            // Horizontais
            glVertex3f(-L,y,i);
            glVertex3f(L,y,i);
		glEnd();
	}

}

// Desenhar cubo
void desenhaCubo(GLfloat tamanho){
    //anterior - vermelho
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex3f(-tamanho, tamanho, tamanho);
    glVertex3f(-tamanho, -tamanho, tamanho);
    glVertex3f( tamanho, -tamanho, tamanho);
    glVertex3f( tamanho, tamanho, tamanho);
    glEnd();
    //lateral esquerda - azul
    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex3f( tamanho, tamanho, tamanho);
    glVertex3f( tamanho, -tamanho, tamanho);
    glVertex3f( tamanho, -tamanho, -tamanho);
    glVertex3f( tamanho, tamanho, -tamanho);
    glEnd();
    //posterior - amarelo
    glColor3f(1.0f, 1.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex3f( tamanho, tamanho, -tamanho);
    glVertex3f(-tamanho, tamanho, -tamanho);
    glVertex3f(-tamanho, -tamanho, -tamanho);
    glVertex3f( tamanho, -tamanho, -tamanho);
    glEnd();
    //lateral direita - verde
    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex3f(-tamanho, tamanho, tamanho);
    glVertex3f(-tamanho, tamanho, -tamanho);
    glVertex3f(-tamanho, -tamanho, -tamanho);
    glVertex3f(-tamanho, -tamanho, tamanho);
    glEnd();
    //superior - laranja
    glColor3f(1.0f, 0.5f, 0.2f);
    glBegin(GL_QUADS);
    glVertex3f(-tamanho, tamanho, tamanho);
    glVertex3f( tamanho, tamanho, tamanho);
    glVertex3f( tamanho, tamanho, -tamanho);
    glVertex3f(-tamanho, tamanho, -tamanho);
    glEnd();
    //inferior - roxo
    glColor3f(0.5f, 0.2f, 0.8f);
    glBegin(GL_QUADS);
    glVertex3f(-tamanho, -tamanho, tamanho);
    glVertex3f(-tamanho, -tamanho, -tamanho);
    glVertex3f( tamanho, -tamanho, -tamanho);
    glVertex3f( tamanho, -tamanho, tamanho);
    glEnd();
}

// Função callback de redesenho da janela de visualização
void Desenha(void)
{
	// Limpa a janela de visualização com a cor
	// de fundo definida previamente
	glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);


    desenhaTerreno();

	 glPushMatrix();
        glTranslated(0,40,0);
        desenhaCubo(10);
    glPopMatrix();

    glColor3f(0.0f, 0.0f, 1.0f);

    glPushMatrix();
        glRotated(angleRotate, 0, 1, 0);
        glTranslated(50,40,0);
        glutSolidSphere(5,slices,stacks);
    glPopMatrix();


	// Executa os comandos OpenGL
	glutSwapBuffers();
}



// Função usada para especificar o volume de visualização
void EspecificaParametrosVisualizacao(void)
{
	// Especifica sistema de coordenadas de projeção
	glMatrixMode(GL_PROJECTION);
	// Inicializa sistema de coordenadas de projeção
	glLoadIdentity();

	// Especifica a projeção perspectiva(angulo,aspecto,zMin,zMax)
	gluPerspective(angle,fAspect,0.5,500);

	// Especifica sistema de coordenadas do modelo
	glMatrixMode(GL_MODELVIEW);
	// Inicializa sistema de coordenadas do modelo
	glLoadIdentity();

	// Especifica posição do observador, do alvo e do vetor up
	gluLookAt(deslocamentoX,deslocamentoY,deslocamentoZ,
		0,0,0,
		0,1,0);
}

// Função callback chamada quando o tamanho da janela é alterado
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
	// Para previnir uma divisão por zero
	if ( h == 0 ) h = 1;

	// Especifica as dimensões da viewport
	glViewport(0, 0, w, h);

	// Calcula a correção de aspecto
	fAspect = (GLfloat)w/(GLfloat)h;

	EspecificaParametrosVisualizacao();
}

// Função callback chamada para gerenciar eventos de teclas especiais(F1,PgDn,...)
void TeclasEspeciais(int key, int x, int y)
{
	switch(key)
	{
		case GLUT_KEY_UP:		// desloca o volume de visualização para cima
								deslocamentoY -= 2;
								break;
		case GLUT_KEY_DOWN:		// desloca o volume de visualização para baixo
								deslocamentoY += 2;
								break;
		case GLUT_KEY_LEFT:		// desloca o volume de visualização para o lado esquerdo
								deslocamentoX += 2;
								break;
		case GLUT_KEY_RIGHT:	// desloca o volume de visualização para o lado direito
								deslocamentoX -= 2;
								break;
		case GLUT_KEY_PAGE_UP:	// desloca o volume de visualização para frente
								deslocamentoZ -= 2;
								break;
		case GLUT_KEY_PAGE_DOWN:// desloca o volume de visualização para trás
								deslocamentoZ += 2;
		break;
	}
	EspecificaParametrosVisualizacao();
	glutPostRedisplay();
}

// Função callback chamada quando são notificados os eventos do mouse
void GerenciaMouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
		if (state == GLUT_DOWN) {  // zoom in
			if (angle >= 10) angle -= 5;
		}
	if (button == GLUT_RIGHT_BUTTON)
		if (state == GLUT_DOWN) {  // zoom out
			if (angle <= 130) angle += 5;
		}
	EspecificaParametrosVisualizacao();
	glutPostRedisplay();
}

void AnimaOrbita(int value){

	incremento = (2 * M_PI) / 100;

	if(cameraorbital){
        deslocamentoX = raio*cos(angulo);
        deslocamentoZ = raio*sin(angulo);
	}
        glutPostRedisplay();
        glutTimerFunc(10,AnimaOrbita, 1);

}

// Função callback chamada para gerenciar eventos de teclas
void Teclado (unsigned char key, int x, int y)
{
	if (key == 27)
		exit(0);

	switch(key){
        case(48):
            if(cameraorbital){
                cameraorbital = false;
            }else{
                cameraorbital = true;
            }
            glutTimerFunc(10,AnimaOrbita, 1);
        break;
        case(49):
            deslocamentoX = 0;
            deslocamentoY = 80;
            deslocamentoZ = 150;
            EspecificaParametrosVisualizacao();
            glutPostRedisplay();
        break;
        case(50):
            deslocamentoX = 150;
            deslocamentoY = 80;
            deslocamentoZ = 0;
            EspecificaParametrosVisualizacao();
            glutPostRedisplay();
        break;
        case(51):
            deslocamentoX = 0;
            deslocamentoY = 80;
            deslocamentoZ = -150;
            EspecificaParametrosVisualizacao();
            glutPostRedisplay();
        break;
        case(52):
            deslocamentoX = -150;
            deslocamentoY = 80;
            deslocamentoZ = 0;
            EspecificaParametrosVisualizacao();
            glutPostRedisplay();
        break;
        case(53):
            deslocamentoX = 0.1;
            deslocamentoY = 200;
            deslocamentoZ = 0;
            EspecificaParametrosVisualizacao();
            glutPostRedisplay();
        break;
        case(54):
            deslocamentoX = 0.1;
            deslocamentoY = -200;
            deslocamentoZ = 0;
            EspecificaParametrosVisualizacao();
            glutPostRedisplay();
        break;
	}
}

void Anima(int value){
    angleRotate += 1;
    glutPostRedisplay();
    glutTimerFunc(10,Anima, 1);
}


// Função responsável por inicializar parâmetros e variáveis
void Inicializa (void)
{
	// Define a cor de fundo da janela de visualização como branca
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);

	// Inicializa a variável que especifica o ângulo da projeção
	// perspectiva
	angle=60;

	// Inicializa as variáveis utilizadas para implementação
	// da operação de pan
	deslocamentoX = 0.0f;
	deslocamentoY = 80.0f;
	deslocamentoZ = 150.0f;
}

// Programa Principal
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);

	// Define do modo de operação da GLUT
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

	// Especifica a posição inicial da janela GLUT
	glutInitWindowPosition(5,5);

	// Especifica o tamanho inicial em pixels da janela GLUT
	glutInitWindowSize(500,500);

	// Cria a janela passando como argumento o título da mesma
	glutCreateWindow("Sistema solar 3d");

	// Registra a função callback de redesenho da janela de visualização
	glutDisplayFunc(Desenha);

	// Registra a função callback de redimensionamento da janela de visualização
	glutReshapeFunc(AlteraTamanhoJanela);

	// Registra a função callback para tratamento das teclas especiais
	glutSpecialFunc(TeclasEspeciais);

	// Registra a função callback que gerencia os eventos do mouse
	glutMouseFunc(GerenciaMouse);

	// Registra a função callback para tratamento das teclas ASCII
	glutKeyboardFunc (Teclado);

	glutTimerFunc(100, Anima, 1);

	// Chama a função responsável por fazer as inicializações
	Inicializa();

	// Inicia o processamento e aguarda interações do usuário
	glutMainLoop();

	return 0;
}
