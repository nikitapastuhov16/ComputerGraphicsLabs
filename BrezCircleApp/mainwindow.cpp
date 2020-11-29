#include "mainwindow.h"
#include <QPainter>
#include "ui_mainwindow.h"
#include <ctime>
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

void MainWindow::brezDrawCircle(QPoint center, int radius, const QColor &color, DrawingParams parts)
{
    ui->drawingScene->refreshScene(Qt::blue);
    ui->drawingScene->setDrawingColor(color);
    //selecting minimum circle radius
    int radiuses[]{ radius, abs(center.x() - ui->drawingScene->width()), abs(center.y() - ui->drawingScene->height()) };
    //selecting minimum circle radius
    int r = radiuses[0];
    for(int i = 0; i < 3; ++i) if(r > radiuses[i]) r = radiuses[i];
    int x = 0, y = r;
    int delta = 2 * (1-r);
    int error = 0;
    while(y >= 0)
    {
        if(parts.contains(Full_circle) || parts.contains(First_half)  || parts.contains(First_quarter))
        {
            ui->drawingScene->addPoint(QPoint(center.x() + x, center.y() + y));
        }
        if(parts.contains(Full_circle) || parts.contains(First_half)  || parts.contains(Second_quarter))
        {
            ui->drawingScene->addPoint(QPoint(center.x() + x, center.y() - y));
        }
        if(parts.contains(Full_circle) || parts.contains(Second_half) || parts.contains(Third_quarter))
        {
            ui->drawingScene->addPoint(QPoint(center.x() - x, center.y() - y));
        }
        if(parts.contains(Full_circle) || parts.contains(Second_half) || parts.contains(Fourth_quarter))
        {
            ui->drawingScene->addPoint(QPoint(center.x() - x, center.y() + y));
        }
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

void MainWindow::on_pushButton_clicked()
{
    if(ui->drawingScene->pointSelected)
    {
        DrawingParams params;
        QStringList list = ui->lineEdit->text().split(',');
        foreach(QString line, list)
        {
            if     (line.toLower() == "first_quarter" ) params.addParams(First_quarter);
            else if(line.toLower() == "second_quarter") params.addParams(Second_quarter);
            else if(line.toLower() == "third_quarter" ) params.addParams(Third_quarter);
            else if(line.toLower() == "fourth_quarter") params.addParams(Fourth_quarter);
            else if(line.toLower() == "first_half"    ) params.addParams(First_half);
            else if(line.toLower() == "second_half"   ) params.addParams(Second_half);
            else if(line.toLower() == "full_circle"   ) params.addParams(Full_circle);
        }
        brezDrawCircle(ui->drawingScene->lastCenterPoint, ui->lineEdit_3->text().toFloat(), Qt::blue, params);
        ui->drawingScene->pointSelected = false;
    }
}
