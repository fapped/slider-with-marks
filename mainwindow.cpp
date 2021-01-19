#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "slidermarks.h"

#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QWindowStateChangeEvent>

#include <QStyle>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//    QGraphicsScene scene;
//    QGraphicsView *view = new QGraphicsView();

//    this->setCentralWidget(view);

    m_slider = new SliderMarks(this);
    ui->horizontalLayout->addWidget(m_slider);

/*    ClickableQLabel *label = new ClickableQLabel(10000, 0, m_slider);
    label->move(100, 0)*/;

}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QMainWindow::paintEvent(event);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btn_add_clicked()
{
    m_slider->AddMark();
}
