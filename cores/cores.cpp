#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>
#define TAMANHO_JANELA 500

//Pontos do triangulo
float pRx = 0.1;
float pRy = 0.1;
float pGx = 0.9;
float pGy = 0.1;
float pBx = 0.5;
float pBy = 0.9;

//Controle dos arrastes
int draggingPointR = 0, draggingPointG = 0, draggingPointB = 0, choosingColor = 0;

//Cor
float gR = 0., gG = 0., gB = 0.;

//Ponto do clique da cor
float pCliqueX = 0, pCliqueY = 0;
//Pronto do clique projetado
float pProjX = 0, pProjY = 0;

int barycentric2D(float *bar, float x, float y, float x1, float y1, float x2, float y2, float x3, float y3) {

    float y2y3 = y2 - y3,
          x3x2 = x3 - x2,
          x1x3 = x1 - x3,
          y1y3 = y1 - y3,
          y3y1 = y3 - y1,
          xx3  = x  - x3,
          yy3  = y  - y3;

    float d = y2y3 * x1x3 + x3x2 * y1y3,
          lambda1 = (y2y3 * xx3 + x3x2 * yy3) / d,
          lambda2 = (y3y1 * xx3 + x1x3 * yy3) / d;

    bar[0] = lambda1;
    bar[1] = lambda2;
    bar[2] = 1 - lambda1 - lambda2;

    return 0;
}

void display(void)
{
    //Define a cor do fundo
    glClearColor (gR, gG, gB, 0.0);

    /* Limpar todos os pixels  */
    glClear (GL_COLOR_BUFFER_BIT);

    /* Define cor dos vértices com os valores R, G e B variando de 0.0 a 1.0 */
    /* Desenhar um polígono branco (retângulo) */
    glBegin(GL_POLYGON);
        glColor3f (1.0, 0.0, 0.0);
        glVertex3f (pRx, pRy, 0.0);
        glColor3f (0.0, 1.0, 0.0);
        glVertex3f (pGx, pGy, 0.0);
        glColor3f (0.0, 0.0, 1.0);
        glVertex3f (pBx, pBy, 0.0);
    glEnd();

    /* Desenha o ponto de clique. */
    glPointSize(5.0);
    glColor3f(1.0, 1.0, 0.0);
    glBegin(GL_POINTS);
        glVertex3f(pCliqueX, pCliqueY, 0.0);
    glEnd();

    /* Desenha o ponto projetado. */
    glPointSize(5.0);
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POINTS);
        glVertex3f(pProjX, pProjY, 0.0);
    glEnd();

    /* Desenhar no frame buffer! */
    glutSwapBuffers(); //Funcao apropriada para janela double buffer
}

void init (void) 
{
    /* selecionar cor de fundo (preto) */
    glClearColor (0.0, 0.0, 0.0, 0.0);

    /* inicializar sistema de visualizacao */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
}

void motion(int x, int y){
    //Corrige a posicao do mouse para a posicao da janela de visualizacao
    y = TAMANHO_JANELA - y;
    GLfloat fX = (GLfloat)x/TAMANHO_JANELA;
    GLfloat fY = (GLfloat)y/TAMANHO_JANELA;
    float bar[3];
    
    if (choosingColor){
        //Atualiza posicao do clique
        pCliqueX = fX;
        pCliqueY = fY;

	    barycentric2D(bar, pCliqueX, pCliqueY, pRx, pRy, pGx, pGy, pBx, pBy);
        gR = bar[0];
        gG = bar[1];
        gB = bar[2];


    } else if (draggingPointR){
        pRx = (GLfloat)x/TAMANHO_JANELA;
        pRy = (GLfloat)y/TAMANHO_JANELA;
    } else if (draggingPointG){
        pGx = (GLfloat)x/TAMANHO_JANELA;
        pGy = (GLfloat)y/TAMANHO_JANELA;
    } else if (draggingPointB){
        pBx = (GLfloat)x/TAMANHO_JANELA;
        pBy = (GLfloat)y/TAMANHO_JANELA;
    }
    
    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y){
    //Corrige a posicao do mouse para a posicao da janela de visualizacao
    GLfloat fX = (GLfloat)x/TAMANHO_JANELA;
    GLfloat fY = (GLfloat)(TAMANHO_JANELA - y)/TAMANHO_JANELA;

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        choosingColor = 1;
    } else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN){
        if (    (pRx-fX)*(pRx-fX) +
                (pRy-fY)*(pRy-fY) < 
                    (30.0/TAMANHO_JANELA)*(30.0/TAMANHO_JANELA) ){
            draggingPointR = 1;
        } else if (     (pGx-fX)*(pGx-fX) +
                        (pGy-fY)*(pGy-fY) < 
                            (30.0/TAMANHO_JANELA)*(30.0/TAMANHO_JANELA) ){
            draggingPointG = 1;
        } else if (     (pBx-fX)*(pBx-fX) +
                        (pBy-fY)*(pBy-fY) < 
                            (30.0/TAMANHO_JANELA)*(30.0/TAMANHO_JANELA) ){
            draggingPointB = 1;
        }

    } else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP){
        choosingColor = 0;
    }else if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP){
        draggingPointR = draggingPointG = draggingPointB = 0;
    }
    
    motion(x, y);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize (TAMANHO_JANELA, TAMANHO_JANELA); 
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("Cores");
    init ();
    glutDisplayFunc(display); 
    glutMotionFunc(motion);
    glutMouseFunc(mouse);

    glutMainLoop();

    return 0;
}

