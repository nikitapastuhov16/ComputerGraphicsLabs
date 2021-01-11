#include "mainwindow.h"
#include <QPainter>
#include "ui_mainwindow.h"
#include <ctime>
#include <QMessageBox>
#include <QImage>
#include <QStack>
//-*-*-D*E*F*I*N*I*T*I*O*N*S-*-*-
#define RECTANGLE_WIDTH  ui->lineEdit->text().toInt()
#define RECTANGLE_HEIGHT ui->lineEdit_2->text().toInt()
#define RECTANGLE_X0     this->point.x()
#define RECTANGLE_Y0     this->point.y()
//-*-*-D*E*F*I*N*I*T*I*O*N*S-*-*-
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
void MainWindow::linewiseFillingAlgo(QPoint beginPoint)
{
    QImage paintMap = grab(QRect(ui->drawingScene->pos().x(), ui->drawingScene->pos().y(), ui->drawingScene->width(), ui->drawingScene->height())).toImage();
    QStack<QPoint> fstack;
    QVector<QPoint> points;
    fstack.push(beginPoint);
    while(fstack.count() > 0)
    {

        QPoint top = fstack.pop();
        ui->drawingScene->addPoint(top);
        int x = top.x() + 1;
        points.push_back(top);
        for(x;intoRectangle(QPoint(x, top.y())); x++)
        {
            QPoint a = QPoint(x, top.y());
            ui->drawingScene->addPoint(a);
            points.push_back(a);
        }
        int xR = x-1; x--;
        for(x;intoRectangle(QPoint(x, top.y())); x--)
        {
            QPoint a = QPoint(x, top.y());
            ui->drawingScene->addPoint(a);
            points.push_back(a);
        }
        int xL = x+1;
        int y = top.y();
        for(x = xL; x <= xR; x++)
        {
            if(!points.contains(QPoint(x, y-1)))
            {
                QPoint a(x, y-1);
                fstack.push(a);
                break;
            }
        }

        for(x = xL; x <= xR; x++)
        {
            if(!points.contains(QPoint(x, y+1)))
            {
                QPoint a(x, y+1);
                fstack.push(a);
                break;
            }
        }
    }
    ui->drawingScene->paintGL();
}
void MainWindow::simleFillingAlgo(QPoint beginPoint)
{
    QImage paintMap = grab(QRect(ui->drawingScene->pos().x(), ui->drawingScene->pos().y(), ui->drawingScene->width(), ui->drawingScene->height())).toImage();
    QStack<QPoint> fstack;
    QVector<QPoint> points;
    fstack.push(beginPoint);
    while(fstack.count() > 0)
    {
        QPoint top = fstack.pop();
        if(intoRectangle(top) && !points.contains(top)) { points.push_back(top); ui->drawingScene->addPoint(top); }
        QPoint a = QPoint(top.x() + 1, top.y());
        if(intoRectangle(a) && !points.contains(a)) fstack.push(a);
        a = QPoint(top.x(), top.y() + 1);
        if(intoRectangle(a) && !points.contains(a)) fstack.push(a);
        a = QPoint(top.x() - 1, top.y());
        if(intoRectangle(a) && !points.contains(a)) fstack.push(a);
        a = QPoint(top.x(), top.y() - 1);
        if(intoRectangle(a) && !points.contains(a)) fstack.push(a);
    }
    ui->drawingScene->paintGL();
}

bool MainWindow::swapper(int &x, int &y)
{
    if(y > x)
    {
        int temp = x;
        x = y;
        y = temp;
        return true;
    }
    else return false;
}

void MainWindow::brezDrawLine(QPoint a, QPoint b)
{
    int x = a.x(), y = a.y(), dx = abs(b.x()-a.x()), dy = abs(b.y()-a.y()), s1 =sign((b.x() - a.x())), s2 = sign((b.y() - a.y()));
    int e, swap;
    e = 2*dy - dx;
    swap = swapper(dx, dy) ? 1 : 0;
    for(int i = 0; i <= dx; i++)
    {
        ui->drawingScene->addPoint(QPoint(x,y));
        while(e > 0)
        {
            if(swap == 1) x+=s1; else y += s2;
            e -= 2*dx;
        }
        if(swap == 1) y += s2; else x += s1;
        e += 2* dy;
    }
}

int MainWindow::sign(int x)
{
    if (x > 0) return 1;
    if (x < 0) return -1;
    return 0;
}
int MainWindow::min(int size, int params[])
{
    int min = params[0];
    for(int i = 0; i < size; ++i) if(params[i] < min) min = params[i];
    return min;
}

bool MainWindow::intoRectangle(QPoint point)
{
    int x = point.x(), y = point.y();
    return (x - RECTANGLE_X0 > 0) && (x - RECTANGLE_X0 < RECTANGLE_WIDTH) && (y - RECTANGLE_Y0 > 0) && (y - RECTANGLE_Y0 < RECTANGLE_HEIGHT);
}
void MainWindow::PointChecked(QPoint point)
{
    if(point.x() != 0 && point.y() != 0)
    {
        ui->Coord_Label->setText("( " + QString::number(point.x()) + " ; " + QString::number(point.y()) + " )");
        this->point = point;
        ui->commandLinkButton->setEnabled(true);
    }
}

void MainWindow::on_commandLinkButton_clicked()
{
    brezDrawLine(this->point, QPoint(point.x() + ui->lineEdit->text().toInt(), point.y()));
    brezDrawLine(this->point, QPoint(point.x(), point.y() + ui->lineEdit_2->text().toInt()));
    brezDrawLine(QPoint(point.x(), point.y() + ui->lineEdit_2->text().toInt()), QPoint(point.x() + ui->lineEdit->text().toInt(), point.y() + ui->lineEdit_2->text().toInt()));
    brezDrawLine(QPoint(point.x() + ui->lineEdit->text().toInt(), point.y()), QPoint(point.x() + ui->lineEdit->text().toInt(), point.y() + ui->lineEdit_2->text().toInt()));
    ui->drawingScene->paintGL();
    QPoint a = QPoint(this->point.x() + 1, this->point.y() + 1);
    if(ui->radioButton->isChecked())        simleFillingAlgo   (a);
    else if(ui->radioButton_2->isChecked()) linewiseFillingAlgo(a);
}
