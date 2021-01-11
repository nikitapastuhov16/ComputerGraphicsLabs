#include "viewer.hpp"
#include <QOpenGLWidget>
#include "mainwindow.h"

Viewer::Viewer(QWidget *parent) : QOpenGLWidget(parent)
{
    this->lastDrawingMode = SINGLE_POINTS_MODE;
    mouseClicked = false;
}
void Viewer::setDrawingColor(const QColor &color)
{
    float r, g, b;
    QColorToRGB(color, r, g, b);
    glColor3f(r, g, b);
    this->lastDrawingColor = color;
}

void Viewer::setPixelSize(int size)
{
    glPointSize(size);
}

void Viewer::setDrawingType(GLenum mode, bool save)
{
    glBegin(mode);
    if(save) this->lastDrawingMode = mode;
}
void Viewer::QColorToRGB(const QColor &c, float &r, float &g, float &b)
{
   r = normalize(c.red(), 1.0f, 255.0f);
   g = normalize(c.green(), 1.0f, 255.0f);
   b = normalize(c.blue(), 1.0f, 255.0f);
}

void Viewer::mousePressEvent(QMouseEvent *args)
{
    emit PointSelected(args->pos());
}

void Viewer::drawPoint(QPoint a)
{
    glPointSize(1);
    setDrawingType(SINGLE_POINTS_MODE, true);
    setDrawingColor(Qt::yellow);
    glVertex2i(a.x(), a.y());
}
void Viewer::refreshScene(const QColor &color)
{
    float r, g, b;
    glEnd();
    QColorToRGB(color, r, g, b);
    glClearColor(r, g, b, 1.0f);
    glBegin(lastDrawingMode);
    this->update();
}
float Viewer::normalize(float val, float min, float max)
{
    return (val-min)/(max-min);
}
void Viewer::initializeGL()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, this->width(), this->height(), 0, 0, 1);
}
void Viewer::resizeGL(int w, int h)
{
    glViewport(0,0, w, h);
}
void Viewer::paintGL()
{
    refreshScene(Qt::magenta);
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(1);
    setDrawingType(SINGLE_POINTS_MODE, true);
    setDrawingColor(Qt::yellow);
    for(int i = 0; i < vertices.size(); ++i) glVertex2i(vertices[i].x(), vertices[i].y());
    glEnd();
}

bool Viewer::containsPoint(int x, int y)
{
    bool a = vertices.contains(QPoint(x, y));
    return a;
}

void Viewer::addPoint(QPoint point)
{
    vertices.push_back(point);
}
QPoint Viewer::getPoint(int index)
{
    return vertices[index];
}
