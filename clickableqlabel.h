#ifndef CLICKABLEQLABEL_H
#define CLICKABLEQLABEL_H

#include <QLabel>

class ClickableQLabel : public QLabel
{
    Q_OBJECT
public:
    explicit ClickableQLabel(qint32 posX, QString text, QWidget *parent = nullptr);
    ClickableQLabel(qint32 posX, qint32 posY, qint32 originalValue, QString text, qint32 minVal, qint32 maxVal, QWidget *parent = nullptr);

    qint32 positionX() const;
    qint32 positionY() const;

    void setPositionX(qint32 newPosX, bool center = true);
    void setPositionY(qint32 newPosY);

    qint32 maxVal() const;
    qint32 minVal() const;

    void setMaxVal(qint32 maxVal);
    void setMinVal(qint32 minVal);

    qint32 originalValue() const;

    static bool isLabelGreater(const ClickableQLabel *first, const ClickableQLabel *second);

signals:
    void originalValueChanged(ClickableQLabel* label, qint32 value);

protected:
    void mouseDoubleClickEvent(QMouseEvent *event) override;

private:
    qint32 m_posX;
    qint32 m_posY;
    qint32 m_originalValue;

    qint32 m_minVal;    //change it with slot
    qint32 m_maxVal;
};

#endif // CLICKABLEQLABEL_H
