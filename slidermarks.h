#ifndef SLIDERMARKS_H
#define SLIDERMARKS_H

#include <QWidget>

#include "clickableqlabel.h"

QT_BEGIN_NAMESPACE
class QLabel;
class QSlider;
class QSpacerItem;
QT_END_NAMESPACE

class SliderMarks : public QWidget
{
    Q_OBJECT
public:
    explicit SliderMarks(QWidget *parent = nullptr);

    void AddMark();

signals:

private slots:
    void OnSliderValueChanged(qint32 value);
    void OnSliderRangeChanged(qint32 min, qint32 max);
    void OnOriginalValueChanged(ClickableQLabel *label, qint32 value);

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    QLabel *m_labelLeft;
    QLabel *m_labelRight;
    QWidget *m_widget;
    QSlider *m_slider;

    QSpacerItem *m_spacerUp;
    QSpacerItem *m_spacerDown;

    bool m_addNew;
    QList<ClickableQLabel*> m_labels;

    void checkVal();
    void redrawAll();
};

#endif // SLIDERMARKS_H
