#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <drawingparams.hpp>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void brezDrawCircle(QPoint center, int radius, const QColor &color, DrawingParams parts);
public slots:
    void PointChecked(QPoint point);

private slots:
    void on_pushButton_3_clicked();
    void on_pushButton_clicked();
private:
    Ui::MainWindow *ui;
    QColor boardColor;
    int min(int size, int params[]);
};

#endif // MAINWINDOW_H
