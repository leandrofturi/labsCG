#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>
#define TAMANHO_JANELA 500

float gX[4] = {0.0, 0.0, 0.5, 0.5};
float gY[4] = {0.0, 0.5, 0.5, 0.0};

float gX0[4] = {0.25, 0.25, 0.25, 0.25};
float gY0[4] = {0.25, 0.25, 0.25, 0.25};

int keyStatus[256];

void mouseMotion(int x, int y) {
   y = TAMANHO_JANELA-y;

   //printf("%d\t%d\n", x, y);
   float x_ = ((float) x/(float) TAMANHO_JANELA);
   float y_ = ((float) y/(float) TAMANHO_JANELA);

   gX[0] = x_ - gX0[0];
   gY[0] = y_ - gY0[0];
   
   gX[1] = x_ - gX0[1];
   gY[1] = y_ + gY0[1];
   
   gX[2] = x_ + gX0[2];
   gY[2] = y_ + gY0[2];
   
   gX[3] = x_ + gX0[3];
   gY[3] = y_ - gY0[3];
   
   glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {
   // printf("%d\t%d\n", x, TAMANHO_JANELA-y);
   y = TAMANHO_JANELA-y;
   float x_ = ((float) x/(float) TAMANHO_JANELA);
   float y_ = ((float) y/(float) TAMANHO_JANELA);
   
   if((x_ >= gX[0]) && (x_ >= gX[1]) && (x_ <= gX[2]) && (x_ <= gX[3]) &&
      (y_ >= gY[0]) && (y_ <= gY[1]) && (y_ <= gY[2]) && (y_ >= gY[3])) {
       gX0[0] = x_ - gX[0];
       gY0[0] = y_ - gY[0];
   
       gX0[1] = x_ - gX[1];
       gY0[1] = gY[1] - y_;
   
       gX0[2] = gX[2] - x_;
       gY0[2] = gY[2] - y_;
   
       gX0[3] = gX[3] - x_;
       gY0[3] = y_ - gY[3];  
   }
   else {
       gX[0] = x_-0.25;
       gY[0] = y_-0.25;
   
       gX[1] = x_-0.25;
       gY[1] = y_+0.25;
   
       gX[2] = x_+0.25;
       gY[2] = y_+0.25;
   
       gX[3] = x_+0.25;
       gY[3] = y_-0.25;
   
       glutPostRedisplay();
   }
}

void idle(void) {
   if(keyStatus[(int) 'w']) {
      gY[0] += 0.001;
      gY[1] += 0.001;
      gY[2] += 0.001;
      gY[3] += 0.001;
      glutPostRedisplay();
   }
   else if(keyStatus[(int) 's']) {
      gY[0] -= 0.001;
      gY[1] -= 0.001;
      gY[2] -= 0.001;
      gY[3] -= 0.001;
      glutPostRedisplay();
   }
   else if(keyStatus[(int) 'a']) {
      gX[0] -= 0.001;
      gX[1] -= 0.001;
      gX[2] -= 0.001;
      gX[3] -= 0.001;
      glutPostRedisplay();
   }
   else if(keyStatus[(int) 'd']) {
      gX[0] += 0.001;
      gX[1] += 0.001;
      gX[2] += 0.001;
      gX[3] += 0.001;
      glutPostRedisplay();
   }
}

void keyUp(unsigned char key, int x, int y) {
   keyStatus[(int) key] = 0;
   glutPostRedisplay();
}

void keyPress(unsigned char key, int x, int y) {
   keyStatus[(int) key] = 1;
/*
   if(key == 'w') {
      gY[0] += 0.01;
      gY[1] += 0.01;
      gY[2] += 0.01;
      gY[3] += 0.01;
      glutPostRedisplay();
   }
   else if(key == 's') {
      gY[0] -= 0.01;
      gY[1] -= 0.01;
      gY[2] -= 0.01;
      gY[3] -= 0.01;
      glutPostRedisplay();
   }
   else if(key == 'a') {
      gX[0] -= 0.01;
      gX[1] -= 0.01;
      gX[2] -= 0.01;
      gX[3] -= 0.01;
      glutPostRedisplay();
   }
   else if(key == 'd') {
      gX[0] += 0.01;
      gX[1] += 0.01;
      gX[2] += 0.01;
      gX[3] += 0.01;
      glutPostRedisplay();
   }
*/
}

void display(void)
{
   /* Limpar todos os pixels  */
   glClear (GL_COLOR_BUFFER_BIT);

   /* Define cor dos vértices com os valores R, G e B variando de 0.0 a 1.0 */
   glColor3f (1.0, 1.0, 1.0);
   /* Desenhar um polígono branco (retângulo) */
   glBegin(GL_POLYGON);
      glVertex3f (gX[0], gY[0], 0.0);
      glVertex3f (gX[1], gY[1], 0.0);
      glVertex3f (gX[2], gY[2], 0.0);
      glVertex3f (gX[3], gY[3], 0.0);
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

int main(int argc, char** argv)
{
    for(int i = 0; i < 256; i++) {
        keyStatus[i] = 0;
    }

    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize (TAMANHO_JANELA, TAMANHO_JANELA); 
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("hello world");
    init ();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyPress);
    glutKeyboardUpFunc(keyUp);
    glutIdleFunc(idle);
    glutMouseFunc(mouse);
    glutMotionFunc(mouseMotion);

    glutMainLoop();

    return 0;
}
