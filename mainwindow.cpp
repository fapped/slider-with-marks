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

    m_slider = new SliderMarks(this);
    ui->horizontalLayout->addWidget(m_slider);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btn_add_clicked()
{
    m_slider->AddMark();
}
