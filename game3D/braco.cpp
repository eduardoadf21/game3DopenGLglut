/*
 * Computacao Grafica
 * Codigo: Game 3D usando GLUT/OpenGL
 * Autor: Luis Eduardo Alencar
 */

// Bibliotecas utilizadas pelo OpenGL
#ifdef __APPLE__
    #define GL_SILENCE_DEPRECATION
    #include <GLUT/glut.h>
    #include <OpenGL/gl.h>
    #include <OpenGL/glu.h>
#else
    #include <GL/glut.h>
    #include <GL/gl.h>
    #include <GL/glu.h>
#endif

#include <stdio.h>
#include <stdlib.h>

#define ESC 27

/*
 * Declaracao de constantes e variaveis
 */
static int ombro = 0, cotovelo = 0, cotovelo2 = 0, polegar = 0, anelar = 0, indicador = 0, ombroY = 0;

/*
 * Declaracoes antecipadas (forward) das funcoes (assinaturas)
 */
void init(void);
void keyboard (unsigned char key, int x, int y);
void display(void);
void reshape (int w, int h);

//Fucao principal
int main(int argc, char** argv){
    // inicia o GLUT
    glutInit(&argc,argv);

    // inicia o display usando RGB, double-buffering e z-buffering
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(800,600);
    glutInitWindowPosition(100,100);
    glutCreateWindow("Computacao Grafica: Braco Robotico");

    // Funcao com alguns comandos para a inicializacao do OpenGL
    init ();

    // define as funcoes de callback
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();

  return EXIT_SUCCESS;
}

// Funcao com alguns comandos para a inicializacao do OpenGL
void init(void){
    glClearColor (1.0, 1.0, 1.0, 1.0); //Limpa a tela com a cor branca;
    glEnable(GL_DEPTH_TEST); // Habilita o algoritmo Z-Buffer
}

float camW= 0;

//Funcal callback para o reshape da janela
void reshape (int w, int h){
    // muda para o modo GL_PROJECTION e reinicia a matriz de projecao
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();

    // define o tamanho da area de desenho da janela
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);

    // Define a forma do volume de visualizacao para termos
    // uma projecao perspectiva (3D).
    gluPerspective(60, (float)w/(float)h , 1.0, 9.0); //(angulo, aspecto, ponto_proximo, ponto distante)
    gluLookAt(6.0,0.0,7.0,  // posicao da camera (olho)
              0.0,1.0,0.0,  // direcao da camera (geralmente para centro da cena)
              0.0,1.0,0.0); // sentido ou orientacao da camera (de cabeca para cima)
    // muda para o modo GL_MODELVIEW para desenhar na tela
    glMatrixMode (GL_MODELVIEW);

}


// Fucao callback para controle das teclas comuns
void keyboard (unsigned char key, int x, int y){
	switch (key) {
		case 'o': ombro = (ombro - 5) % 360; break; // sentido horario
		case 'O': ombro = (ombro + 5) % 360; break; // sentido anti-horario
		case 'c': cotovelo = (cotovelo - 5) % 360; break; // sentido horario
		case 'C': cotovelo = (cotovelo + 5) % 360; break; // sentido anti-horario
		case 'm': cotovelo2 = (cotovelo2 - 5) % 360; break; // sentido horario
		case 'M': cotovelo2 = (cotovelo2 + 5) % 360; break; // sentido anti-horario
		case 'p': polegar = (polegar - 5) % 360; break; // sentido horario
		case 'P': polegar = (polegar + 5) % 360; break; // sentido anti-horario
		case 'a': anelar = (anelar - 5) % 360; break; // sentido horario
		case 'A': anelar = (anelar + 5) % 360; break; // sentido anti-horario
		case 'i': indicador = (indicador - 5) % 360; break; // sentido horario
		case 'I': indicador = (indicador + 5) % 360; break; // sentido anti-horario
		case 'y': ombroY = (ombroY - 5) % 360; break; // sentido horario
		case 'Y': ombroY = (ombroY + 5) % 360; break; // sentido anti-horario
        case 'w': camW += 5; break;
                                          //
                                                         
		case ESC: exit(EXIT_SUCCESS); break; // sai do programa
	}
    glutPostRedisplay();
}

// Funcao callback para desenhar na janela
void display(void){
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Limpa o Buffer de Cores
    glLoadIdentity();
    
    //Base
    glPushMatrix();
        glTranslatef(0.0, -2.0, 0.0);
        glRotatef(-90, 1, 0, 0);
        glColor3f(0.2, 0.2, 0.2);
        glutSolidCone(1.0, 1.2, 30, 30); // base, altura, fatias, pilhas
    glPopMatrix();
    
    //Ombro
    glPushMatrix();
        glTranslatef(0.0, -1.0, 0.0);
        glColor3f(0.7, 0.7, 0.7);
        glutSolidSphere(0.5, 30, 30); // raio, fatias, pilhas
    glPopMatrix();

    //Movimento do braco
    glPushMatrix();
        // origem posicionada no ombro
        glTranslatef (0.0, -1.0, 0.0);
        glRotatef ((GLfloat) ombro, 0.0, 0.0, 1.0);
        glRotatef ((GLfloat) ombroY, 0.0, 1.0, 0.0);
        // origem posicionada no centro do braco
        glTranslatef (0.0, 1.0, 0.0);
        // Braco
        glPushMatrix();
            glRotatef(90, 0, 0, 1);
            glScalef (2.0, 0.5, 0.5);
            glColor3f(0.8,0.8,0.0);
            glutSolidCube (1.0); // Tamanho
        glPopMatrix();

        //Cotovelo
        glPushMatrix();
            glTranslatef(0.0, 1.0, 0.0);
            glColor3f(0.7, 0.7, 0.7);
            glutSolidSphere(0.4, 30, 30); // raio, fatias, pilhas
        glPopMatrix();

        //Movimento do antebraco
        glPushMatrix();
            //origem posicionada no cotovelo
            glTranslatef (0.0, 1.0, 0.0);
            glRotatef ((GLfloat) cotovelo, 0.0, 0.0, 1.0);
            glTranslatef (0.0, 1.0, 0.0);
            // Antebraco
            glPushMatrix();
                glRotatef(90, 0, 0, 1);
                glScalef (2.0, 0.5, 0.5);
                glColor3f(0.8,0.8,0.0);
                glutSolidCube (1.0); // Tamanho
            glPopMatrix();

        		//Cotovelo2
        		glPushMatrix();
           		 glTranslatef(0.0, 1.0, 0.0);
            	 glColor3f(0.6, 0.6, 0.6);
            	 glutSolidSphere(0.4, 30, 30); // raio, fatias, pilhas
        	  glPopMatrix();
						//Movimento do antebraco2
						glPushMatrix();
								// origem posicionada no cotovelo2
								glTranslatef (0.0, 1.0, 0.0);
								glRotatef ((GLfloat) cotovelo2, 0.0, 0.0, 1.0);
								// origem posicionada no centro do braco
								glTranslatef (0.0, 1.0, 0.0);
								// anteBraco2
								glPushMatrix();
										glRotatef(90, 0, 0, 1);
										glScalef (2.0, 0.5, 0.5);
										glColor3f(0.8,0.8,0.0);
										glutSolidCube (1.0); // Tamanho
								glPopMatrix();
								//punho
								glPushMatrix();
										glTranslatef(0.0, 1.0, 0.0);
										glColor3f(0.6, 0.6, 0.6);
										glutSolidSphere(0.4, 30, 30); // raio, fatias, pilhas
								glPopMatrix();
								//Movimento do polegar
									glPushMatrix();
										// origem posicionada no punho
										glTranslatef (0.0, 1.0, 0.0);
										glRotatef ((GLfloat) polegar, 0.0, 0.0, 1.0);
											// origem posicionada no centro do braco
										glTranslatef (0.0, 1.0, 0.0);
											// polegar
										glPushMatrix();
												glRotatef(90, 0, 0, 1);
												glScalef (2.0, 0.1, 0.1);
												glColor3f(0.1,0.1,0.1);
												glTranslatef (0.0, -1.0, 0.0);
												glutSolidCube (1.0); // Tamanho
										glPopMatrix();
								//Movimento do anelar
									glPushMatrix();
										// origem posicionada no punho
										glTranslatef (0.0, 1.0, 0.0);
										glRotatef ((GLfloat) anelar, -1.0, 0.0, -1.0);
											// origem posicionada no centro do braco
										glTranslatef (0.0, 1.0, 0.0);
											// anelar
										glPushMatrix();
												glRotatef(90, 0, 0, 1);
												glScalef (2.0, 0.1, 0.1);
												glColor3f(0.1,0.1,0.1);
												glTranslatef (0.0, 1.0, 1.0);
												glutSolidCube (1.0); // Tamanho
										glPopMatrix();
								//Movimento do indicador
									glPushMatrix();
										// origem posicionada no punho
										glTranslatef (0.0, 1.0, 0.0);
										glRotatef ((GLfloat) indicador, 1.0, 0.0, -1.0);
											// origem posicionada no centro do braco
										glTranslatef (0.0, 1.0, 0.0);
											// indicador
										glPushMatrix();
												glRotatef(90, 0, 0, 1);
												glScalef (2.0, 0.1, 0.1);
												glColor3f(0.1,0.1,0.1);
												glTranslatef (0.0, 1.0, -1.0);
												glutSolidCube (1.0); // Tamanho
										glPopMatrix();
						glPopMatrix();


				
        glPopMatrix();

    // origem volta para o sistema de coordenadas original
    glPopMatrix();


    // Troca os buffers, mostrando o que acabou de ser desenhado
    glutSwapBuffers();
}

