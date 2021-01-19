#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class SliderMarks;
class ClickableQLabel;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *event) override;

private slots:
    void on_btn_add_clicked();

private:
    Ui::MainWindow *ui;
    SliderMarks *m_slider;
    QList<ClickableQLabel*> m_labels;
};
#endif // MAINWINDOW_H
