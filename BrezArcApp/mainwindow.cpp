#include "mainwindow.h"
#include <QPainter>
#include "ui_mainwindow.h"
#include <ctime>
#include <cmath>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->drawingScene, &Viewer::PointSelected, this, &MainWindow::PointChecked);
}

MainWindow::~MainWindow()
{
    delete ui;
}
int MainWindow::min(int size, int params[])
{
    int min = params[0];
    for(int i = 0; i < size; ++i) if(params[i] < min) min = params[i];
    return min;
}

void MainWindow::brezDrawArc(QPoint center, int radius, const QColor &color, int beginAngle, int endAngle)
{
    ui->drawingScene->refreshScene(Qt::blue);
    ui->drawingScene->setDrawingColor(color);

    //selecting minimum circle radius
    int radiuses[]{ radius, abs(center.x() - ui->drawingScene->width()), abs(center.y() - ui->drawingScene->height()) };
    //selecting minimum circle radius
    int r = radius;
    for(int i = 0; i < 3; ++i) if(r > radiuses[i]) r = radiuses[i];

    int x = r*cos(beginAngle*(3.14/180.0)), y = r*sin(beginAngle*(3.14/180.0));
    int delta = pow(x+1,2) + pow(y-1,2) -r*r;
    int error = 0;
    while(y > r*sin(endAngle*(3.14/180.0)))
    {
        ui->drawingScene->addPoint(QPoint(center.x() + x, center.y()+ y));

        error = 2 * (delta + y) - 1;
        if(delta < 0 && error <= 0)
        {
            ++x;
            delta += (2 * x) + 1;
            continue;
        }
        if(delta > 0 && error > 0)
        {
            --y;
            delta -= (2 * y) + 1;
            continue;
        }
        ++x;
        delta += 2 * (x - y);
        --y;
    }
    ui->drawingScene->paintGL();
}

void MainWindow::PointChecked(QPoint point)
{
    ui->Coord_Label->setText("( " + QString::number(point.x()) + " ; " + QString::number(point.y()) + " )");
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->drawingScene->selectingPoint = true;
}
template<typename T>
void MainWindow::swap(T &x1, T &x2)
{
    T x = x1;
    x1 = x2;
    x2 = x;
}
void MainWindow::on_pushButton_clicked()
{
    if(ui->drawingScene->pointSelected && ui->begin_angle_input->text() != "" && ui->end_angle_edit->text() != "")
    {
        int startAngle = ui->begin_angle_input->text().toInt(), endAngle =  ui->end_angle_edit->text().toInt();
        int radius = ui->lineEdit_3->text().toInt();
        if(startAngle < endAngle) swap(startAngle, endAngle);

        brezDrawArc(ui->drawingScene->lastCenterPoint, radius, Qt::blue, startAngle, endAngle);

        ui->drawingScene->pointSelected = false;
    }
}
