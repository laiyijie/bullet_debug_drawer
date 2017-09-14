//
// Created by laiyijie on 9/13/17.
//

#ifndef BULLET_COLLISION_MYDEBUGDRAWER_H
#define BULLET_COLLISION_MYDEBUGDRAWER_H


#include <LinearMath/btVector3.h>
#include <LinearMath/btIDebugDraw.h>
#include <LinearMath/btAlignedObjectArray.h>
#include <vector>
#include <GL/gl.h>
#include <LinearMath/btVector3.h>
#include <GL/freeglut.h>

class MyDebugDrawer : public btIDebugDraw {

    int m_debugMode;

public:
    struct DebugLine {
        btVector3 from;
        btVector3 to;
        btVector3 color;
    };
private:
    static std::vector<DebugLine> debugLines;

    DefaultColors m_ourColors;

    static void init_scene() {
        btVector3 eye_point = {10,15,20};
        float axis_length = 100;
        float w = 1024, h = 768;
        auto ratio = 1.0f * w / h;
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glViewport(0, 0, 1024, 768);
        gluPerspective(45, ratio, 0.1, 1000);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(eye_point.getX(), eye_point.getY(), eye_point.getZ(), 0, 0, 0, 0.0, 1.0, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        draw_axis(axis_length);
        glLineWidth(1);
        for (auto &line : debugLines) {
            glColor3f(line.color.getX(), line.color.getY(), line.color.getZ());
            glBegin(GL_LINES);
            glVertex3d(line.from.getX(), line.from.getY(), line.from.getZ());
            glVertex3d(line.to.getX(), line.to.getY(), line.to.getZ());
            glEnd();
        }
        glutSwapBuffers();
    }


    static void draw_axis(float length){
        glLineWidth(1);
        //x
        glColor3f(200,0,200);
        glBegin(GL_LINES);
        glVertex3d(0,0,0);
        glVertex3d(length,0,0);
        glEnd();
        //y
        glColor3f(0,200,200);
        glBegin(GL_LINES);
        glVertex3d(0,0,0);
        glVertex3d(0,length,0);
        glEnd();
        //z
        glColor3f(0,0,200);
        glBegin(GL_LINES);
        glVertex3d(0,0,0);
        glVertex3d(0,0,length);
        glEnd();
    }


//    void static display() {
//
//        glMatrixMode(GL_MODELVIEW);
//        glLoadIdentity();
//        gluLookAt(10,10,-10,0,0,0,0.0,1.0,0);
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//        glLineWidth(2);
//        for (auto &line : debugLines) {
//            glColor3f(line.color.getX(), line.color.getY(), line.color.getZ());
//            glBegin(GL_LINES);
//            glVertex3d(line.from.getX(), line.from.getY(), line.from.getZ());
//            glVertex3d(line.to.getX(), line.to.getY(), line.to.getZ());
//            glEnd();
//        }
//        glutSwapBuffers();
//    }

public:
    MyDebugDrawer() {
//        m_debugMode = DBG_DrawWireframe | DBG_DrawContactPoints | DBG_DrawAabb | DBG_DrawNormals;
        m_debugMode = DBG_DrawWireframe | DBG_DrawContactPoints | DBG_DrawNormals;
        //创建一个名为Demo的窗口


    }


    virtual ~MyDebugDrawer() {
    }

    DefaultColors getDefaultColors() const override {
        return m_ourColors;
    }

///the default implementation for setDefaultColors has no effect. A derived class can implement it and store the colors.
    void setDefaultColors(const DefaultColors &colors) override {
        m_ourColors = colors;
    }


    virtual void drawLine(const btVector3 &from1, const btVector3 &to1, const btVector3 &color1) {
        DebugLine debugLine;
        debugLine.from = from1;
        debugLine.to = to1;
        debugLine.color = color1;

        debugLines.push_back(debugLine);

    }

    void
    drawContactPoint(const btVector3 &PointOnB, const btVector3 &normalOnB, btScalar distance, int lifeTime,
                     const btVector3 &color) override {
        drawLine(PointOnB, PointOnB + normalOnB * distance, color);
        btVector3 ncolor(0, 0, 0);
        drawLine(PointOnB, PointOnB + normalOnB * 0.01, ncolor);

    }


    void reportErrorWarning(const char *warningString) override {
    }

    void draw3dText(const btVector3 &location, const char *textString) override {
    }

    void setDebugMode(int debugMode) override {
        m_debugMode = debugMode;
    }

    int getDebugMode() const override {
        return m_debugMode;
    }

    void flushLines() override {
        glutInitWindowSize(1024, 768);
        glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
        glutCreateWindow("Demo");
//        glutIdleFunc(display);
        glutDisplayFunc(init_scene);
        glutMainLoop();
    }

};

std::vector<MyDebugDrawer::DebugLine>MyDebugDrawer::debugLines;
#endif //BULLET_COLLISION_MYDEBUGDRAWER_H
