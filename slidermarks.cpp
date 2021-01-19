#include "slidermarks.h"

#include <QLabel>
#include <QSlider>
#include <QHBoxLayout>
#include <QStyle>
#include <QPainter>
#include <QPaintEvent>
#include <QStyleOptionGraphicsItem>

#include <QGraphicsScene>
#include <QGraphicsView>

#include <QDebug>

SliderMarks::SliderMarks(QWidget *parent)
    : QWidget(parent),
      m_addNew(false)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QHBoxLayout *sliderLayout = new QHBoxLayout(/*this*/);


    m_labelLeft = new QLabel("0", this);

    m_slider = new QSlider(Qt::Horizontal, this);
    m_slider->setRange(0, 150);

    m_labelRight = new QLabel("10:00", this);
    m_labelLeft->adjustSize();

    sliderLayout->addWidget(m_labelLeft);
    sliderLayout->addWidget(m_slider);
    sliderLayout->addWidget(m_labelRight);

    m_labelLeft->setMinimumWidth(30);
    m_labelLeft->adjustSize();

    m_widget = new QWidget(this);
    //m_widget->setStyleSheet("background-color: #0081FF");
    m_widget->setFixedHeight(m_slider->height());
    //m_widget->setMinimumWidth(m_slider->width() + 100);

    m_spacerUp = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);
    m_spacerDown = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

    mainLayout->addItem(m_spacerUp);
    mainLayout->addWidget(m_widget);
    //mainLayout->addWidget(m_slider);
    mainLayout->addItem(sliderLayout);
    mainLayout->addItem(m_spacerDown);

    connect(m_slider, &QSlider::valueChanged, this, &SliderMarks::OnSliderValueChanged);
    connect(m_slider, &QSlider::rangeChanged, this, &SliderMarks::OnSliderRangeChanged);
}

void SliderMarks::OnSliderValueChanged(qint32 value)
{
    m_labelLeft->setText(QString::number(value));
    m_labelLeft->adjustSize();
}

void SliderMarks::OnSliderRangeChanged(qint32 min, qint32 max)  //not tested
{
    for (int idx = m_labels.count() - 1; idx >= 0; idx--)
    {
        ClickableQLabel *label = m_labels.at(idx);

        if(label->originalValue() < min || label->originalValue() > max)
        {
            m_labels.removeAll(label);
            label->setParent(nullptr);
            disconnect(label, &ClickableQLabel::originalValueChanged, this, &SliderMarks::OnOriginalValueChanged);
            delete label;       //sure ?
            label = nullptr;
            continue;
        }

        label->setMinVal(min);
        label->setMaxVal(max);
    }

    redrawAll();
}

void SliderMarks::OnOriginalValueChanged(ClickableQLabel *label, qint32 value)
{
    if(label == nullptr || m_labels.contains(label) == false)
        return;

    int position = 9 + QStyle::sliderPositionFromValue(m_slider->minimum(),
                                                       m_slider->maximum(),
                                                       value,
                                                       m_slider->width() - 20);

    label->setPositionX(position + m_labelLeft->width());

    OnSliderRangeChanged(m_slider->minimum(), m_slider->maximum());
}

void SliderMarks::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
}

void SliderMarks::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

    foreach(auto label, m_labels)
    {
        int position = 9 + QStyle::sliderPositionFromValue(m_slider->minimum(),
                                                           m_slider->maximum(),
                                                           label->originalValue(),
                                                           m_slider->width() - 20);

        label->setPositionX(position + m_labelLeft->width());
        redrawAll();
    }
}

void SliderMarks::AddMark()
{
    bool exist = false;
    foreach (const auto label, m_labels)
    {
        if(label->originalValue() == m_slider->value())
            exist = true;
    }

    if(exist)
        return;

    int position = 9 + QStyle::sliderPositionFromValue(m_slider->minimum(),
                                                       m_slider->maximum(),
                                                       m_slider->value(),
                                                       m_slider->width() - 20);

    qint32 posY = 0;
    if(m_labels.count() % 2 == 0)
        posY = 16;

    ClickableQLabel *label = new ClickableQLabel(position + m_labelLeft->width(), posY, m_slider->value(),
                                                 QString::number(m_slider->value()), m_slider->minimum(),
                                                 m_slider->maximum(), m_widget);

    connect(label, &ClickableQLabel::originalValueChanged, this, &SliderMarks::OnOriginalValueChanged);

    m_labels.append(label);
    std::sort(m_labels.begin(), m_labels.end(), ClickableQLabel::isLabelGreater);

    redrawAll();

    this->update();
}

void SliderMarks::redrawAll()
{
    for (int idx = 0; idx < m_labels.count(); idx++)
    {
        ClickableQLabel *label = m_labels.at(idx);

        qint32 posY = 0;
        if (idx % 2 == 0)
            posY = 16;

        label->setPositionY(posY);

        label->move(label->positionX(), label->positionY());
        label->show();
    }
}

void SliderMarks::checkVal()
{

}
