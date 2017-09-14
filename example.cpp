

#include <GL/freeglut.h>

void drawAnotherLine() {
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINES);
    glVertex3f(-0.5, 0.5, 0.5);
    glVertex3f(0, 0.5, -0.5);
    glEnd();

}

void display() {

}

float angle = 0.0;

void renderScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    glRotatef(angle, 0.0, 1.0, 0.0);
    glBegin(GL_TRIANGLES);
    glVertex3f(-0.5, -.05, 0.0);
    glVertex3f(0.5, 0.0, 0.0);
    glVertex3f(0.0, 0.5, 0.0);
    glEnd();
    glPopMatrix();
    glutSwapBuffers();
//    glFlush();
    angle++;
}


// 程序入口
int main(int argc, char **argv) {
    //窗口初始化
    glutInit(&argc, argv);
    //创建一个名为Demo的窗口
    glutInitWindowSize(1024, 768);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutCreateWindow("Demo");
    //绘图函数
    glutDisplayFunc(display);
        glutIdleFunc(renderScene);

    glutMainLoop();

    drawAnotherLine();
}