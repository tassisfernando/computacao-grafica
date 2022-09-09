#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


GLsizei auxLargura, auxAltura;

void desenhaQuadrado(void){
     glBegin(GL_QUADS);
       glVertex2i(-40, 40);
       glVertex2i(-40, -40);
       glVertex2i(40, -40);
       glVertex2i(40, 40);
     glEnd();
}

// Função callback de redesenho da janela de visualização
void Desenha(void)
{
	// Limpa a janela de visualização com a cor de fundo definida previamente
	glClear(GL_COLOR_BUFFER_BIT);

    glViewport(0, 0, auxLargura/2, auxAltura/2);
    glColor3f(1.0f, 0.0f, 0.0f); // vermelho em RGB
    desenhaQuadrado();

    glViewport(auxLargura/2, 0, auxLargura/2, auxAltura/2);
    glColor3f(0.0f, 1.0f, 0.0f); // verde em RGB
    desenhaQuadrado();

    glViewport(auxLargura/2, auxAltura/2, auxLargura/2, auxAltura/2);
    glColor3f(0.0f, 0.0f, 1.0f); // azul em RGB
    desenhaQuadrado();

    glViewport(0, auxAltura/2, auxLargura/2, auxAltura/2);
    glColor3f(1.0f, 1.0f, 0.0f); // amarelo em RGB
    desenhaQuadrado();

	// Executa os comandos OpenGL
	glFlush();
}

// Função callback chamada quando o tamanho da janela é alterado
void AlteraTamanhoJanela(GLsizei largura, GLsizei altura)
{
	// Evita a divisão por zero
	if(altura == 0){
      altura = 1;
	}
    //Variáveis globais
	auxLargura = largura;
	auxAltura = altura;

	// Inicializa o sistema de coordenadas
    glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

    // Estabelece a janela de seleção
    // mantendo a proporção com a janela de visualização
	if (largura <= altura){
		gluOrtho2D (-40.0f, 40.0f, -40.0f*altura/largura, 40.0f*altura/largura);
    }
	else{
        gluOrtho2D (-40.0f*largura/altura, 40.0f*largura/altura, -40.0f, 40.0f);
	}

}

// Função callback chamada para gerenciar eventos de teclas
void Teclado (unsigned char key, int x, int y)
{
	if (key == 27)
		exit(0);
}

// FunFunçãoo responsável por inicializar parâmetros e variáveis
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

	// Define do modo de opera��o da GLUT
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    // Especifica a posi��o inicial da janela GLUT
	glutInitWindowPosition(100, 100);

	// Especifica o tamanho inicial em pixels da janela GLUT
	glutInitWindowSize(400, 400);

	// Cria a janela passando como argumento o t�tulo da mesma
	glutCreateWindow("Exemplo 03");

	// Registra a função  callback de redesenho da janela de visualização
	glutDisplayFunc(Desenha);

	// Registra a função callback de redimensionamento da janela de visualização
	glutReshapeFunc(AlteraTamanhoJanela);

	// Registra a função  callback para tratamento das teclas ASCII
	glutKeyboardFunc (Teclado);

	// Chama a função  responsável por fazer as inicializações
	Inicializa();

	// Inicia o processamento e aguarda interações do usuário
	glutMainLoop();

	return 0;
}
