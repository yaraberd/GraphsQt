#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QPixmap>
#include <QtMath>
#include "pol.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    resize(800, 600);
    le = new QLineEdit(this);

    ar = new QLabel(this);
    br = new QLabel(this);
    ar->setGeometry(width() / 15 * 13, 50, 40, 80);
    ar->setText("a:");
    br->setGeometry(width() / 15 * 13, 80, 40, 110);
    br->setText("b:");

    al = new QLineEdit(this);
    bl = new QLineEdit(this);
    al->setGeometry(width() / 15 * 13.5, 75, 74, 30);
    bl->setGeometry(width() / 15 * 13.5, 120, 74, 30);

    le->setGeometry(width() / 15 * 0.2, 10, 560, 30);


    QPushButton * button = new QPushButton(this);
    button->setGeometry(width() / 15 * 13, 10, 100, 30);
    button->setText("рисовать");
    connect(button, SIGNAL(clicked()), this, SLOT(button_clicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event) {
    QPainter painter;
    painter.begin(this);
    QPen pen;
    pen.setColor(0xff0000);
    pen.setCapStyle(Qt::RoundCap);
    painter.setPen(pen);
    painter.end();
}

void MainWindow::button_clicked() {
    double rez = 0;

    QPainter painter;

    ui->label->setGeometry(10, 60, width() * 0.7, height() * 0.8);
    QPixmap pm(ui->label->width(), ui->label-> height());
    painter.begin(&pm);
    pm.fill(Qt::gray);

    QString ax = al->text();
    QString bx = bl->text();

    double xmin = 0, xmax = 2*M_PI;
    if (ax == "" or bx == "") {
        double xmin = 0, xmax = 2*M_PI;
    }
    else {
        double ax1 = ax.toFloat();
        double bx1 = bx.toFloat();
        xmin = ax1, xmax = bx1;
    }

    double ymin = -1.335, ymax = 1;

    int xgmin = 0, xgmax = pm.width();
    int ygmin = 0, ygmax = pm.height();

    double y = 0;

    double kx = (xgmax - xgmin) / (xmax - xmin);
    double ky = (xgmin - xgmax) / (ymax - ymin);

    double x0 = xgmin - kx * xmin;
    double y0 = ygmin - ky * ymax;
    double x = xmin;
    double stepx = (xmax - xmin) / (xgmax - xgmin);

    int xg = x0 + kx * x;
    int yg = y0 + ky * y;

    QPainterPath path;

    QString fun = le->text();

    QString xs;
    xs = QString::number(x);
    fun.replace(QRegularExpression("x"), "(" + xs +")");
    int pr = calc(fun.toStdString(),rez);
    y = rez;
    yg = y0 + ky * y;
    path.moveTo(xg, yg);
    QPen pen;
    pen.setColor(Qt::black);
    painter.setPen(pen);
    painter.drawLine(xgmin,y0, xgmax, y0);
    painter.drawLine(x0,ygmin, x0, ygmax);

    pen.setColor(Qt::yellow);
    painter.setPen(pen);
    while(x <= xmax) {
        QString xs;
        xs = QString::number(x);
        fun.replace(QRegularExpression("x"), '(' + xs +')');
        int pr = calc(fun.toStdString(),rez);
        if (pr != -1) {
            y = rez;
            xg = x0 + kx * x;
            yg = y0 + ky * y;
            path.lineTo(xg, yg);
            painter.drawPath(path);
        }
        fun.replace(xs, "x");
        x += stepx;
    }
    ui->label->setPixmap(pm);
    painter.end();
}
