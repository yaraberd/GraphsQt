#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QPainter>
#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void paintEvent(QPaintEvent *event);
    QPushButton *button;
    QLineEdit * le;
    QLabel * ar;
    QLabel * br;
    QLineEdit * al;
    QLineEdit * bl;
private slots:
    void button_clicked();
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
