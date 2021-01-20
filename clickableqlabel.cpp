#include "clickableqlabel.h"
#include <QInputDialog>
#include <QMessageBox>

#include <QDebug>

ClickableQLabel::ClickableQLabel(qint32 posX, QString text, QWidget *parent)
    : QLabel(parent)
{
    this->setText(text);
    this->adjustSize();

    m_posX = posX - this->width();    //set after text
}

ClickableQLabel::ClickableQLabel(qint32 posX, qint32 posY, qint32 originalValue, QString text, qint32 minVal, qint32 maxVal, QWidget *parent)
    : QLabel(parent)
{
    this->setText(text);
    this->adjustSize();

    m_posX = posX - this->width();    //set after text
    m_posY = posY;

    m_originalValue = originalValue;        //rename to originalPosition
    this->setToolTip(QString::number(m_originalValue)); //final version: time - pages e.g. 2:34 - 1, 2, 3, 4, 5
                                                        //if there are a lot of pages show on label two first and ... e.g. 1, 2, ...
                                                        //and show all of them in tooltip along with time

    m_minVal = minVal;
    m_maxVal = maxVal;
}

qint32 ClickableQLabel::positionX() const
{
    return m_posX;
}

qint32 ClickableQLabel::positionY() const
{
    return m_posY;
}

void ClickableQLabel::setPositionX(qint32 newPosX, bool center)
{
    m_posX = newPosX;

    if(center)
        m_posX -= this->width();
}

void ClickableQLabel::setPositionY(qint32 newPosY)
{
    m_posY = newPosY;
}

qint32 ClickableQLabel::maxVal() const
{
    return m_maxVal;
}

qint32 ClickableQLabel::minVal() const
{
    return m_minVal;
}

void ClickableQLabel::setMaxVal(qint32 maxVal)
{
    m_maxVal = maxVal;
}

void ClickableQLabel::setMinVal(qint32 minVal)
{
    m_minVal = minVal;
}

bool ClickableQLabel::isLabelGreater(const ClickableQLabel *first, const ClickableQLabel *second)
{
    if(first == nullptr || second == nullptr)
        return false;

    return first->originalValue() < second->originalValue();
}

qint32 ClickableQLabel::originalValue() const
{
    return m_originalValue;
}

void ClickableQLabel::mouseDoubleClickEvent(QMouseEvent *event)
{
    qDebug() << "mouseDoubleClickEvent";

    bool ok = false;
    QString text = QInputDialog::getText(this, tr("Podaj wartość"),
                                         tr("Wartość w zakresie %1 - %2:").arg(QString::number(m_minVal), QString::number(m_maxVal)), QLineEdit::Normal,
                                         QString::number(this->originalValue()), &ok);

    //handle input for ms and hh:mm:ss.qq
    if (ok && !text.isEmpty())
    {
        bool isNumber = false;
        int newVal = text.toUInt(&isNumber, 10);
        if(isNumber == false)
        {
            QMessageBox::critical(this, tr("Błędna wartość"), tr("%1 nie jest poprawną wartością").arg(text));
        }
        else if (newVal < m_minVal || newVal > m_maxVal)
        {
            QMessageBox::critical(this, tr("Błędna wartość"), tr("%1 nie znajduje się w zakresie %1 - %2").arg(QString::number(m_minVal), QString::number(m_maxVal)));
        }
        else
        {
            m_originalValue = newVal;
            this->setToolTip(QString::number(m_originalValue)); //connect signal

            this->setText(text);
            this->adjustSize();

            emit originalValueChanged(this, m_originalValue);
        }
    }

    QLabel::mouseDoubleClickEvent(event);
}
