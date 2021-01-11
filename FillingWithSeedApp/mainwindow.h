#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void    simleFillingAlgo(QPoint beginPoint);
    void linewiseFillingAlgo(QPoint beginPoint);
    QPixmap getSceneMap();
    bool swapper(int &x, int &y);
    void brezDrawLine(QPoint a, QPoint b);
    int sign(int x);
public slots:
    void PointChecked(QPoint point);
private slots:
    void on_commandLinkButton_clicked();
private:
    Ui::MainWindow *ui;
    QColor boardColor;
    QPoint point;
    int min(int size, int params[]);
    bool intoRectangle(QPoint point);
};

#endif // MAINWINDOW_H
