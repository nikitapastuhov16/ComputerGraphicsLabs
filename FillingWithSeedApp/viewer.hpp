#ifndef VIEWER_HPP
#define VIEWER_HPP

#include <QWidget>
#include <QOpenGLWidget>
#include <vector>
#include <QMouseEvent>
#include <QLabel>
#define WITHOUT_COLOR                       nullptr
//DRAWING - MODE - DEFINEITIONS
#define SINGLE_POINTS_MODE                  0x0000
#define NOT_INTERSECT_LINES_MODE            0x0001
#define LOOP_LINE_MODE                      0x0002
#define STRIP_LINE_MODE                     0x0003
#define TRIANGLES_MODE                      0x0004
#define TRIANGLE_WITH_SHARED_SIDE_MODE      0x0005
#define TRIANGLE_FAN_MODE                   0x0006
#define QQUADS_WITH_SHARED_SIDE_MODE        0x0008
#define POLYGON_MODE                        0x0009
//END - OF - DEFINITIONS
class Viewer : public QOpenGLWidget
{
    Q_OBJECT
public:
    explicit Viewer(QWidget *parent = nullptr);
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    bool containsPoint(int x, int y);
    void addPoint(QPoint point);
    QPoint getPoint(int index);
    void refreshScene(const QColor &color);
    void setDrawingColor(const QColor &color);
    void setPixelSize(int size);
    void setDrawingType(GLenum mode, bool Save);
    void mousePressEvent(QMouseEvent *args);
    QColor lastDrawingColor;
    int lastSize;
    QVector<QPoint> vertices;
    bool mouseClicked;
    void drawPoint(QPoint a);
private:
    float normalize(float val, float min, float max);
    void QColorToRGB(const QColor &c, float &r, float &g, float &b);
    GLenum lastDrawingMode;
signals:
    void PointSelected(QPoint point);
};

#endif // VIEWER_HPP
