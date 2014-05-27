#include "UBCellPropertiesPalette.h"
#include <QPainter>
#include <QDebug>

UBCellPropertiesPalette::UBCellPropertiesPalette(QWidget *parent) :
    UBFloatingPalette(Qt::TopLeftCorner, parent)
    , mVLayout(new QVBoxLayout(this))
    , mWidthLayout(new QHBoxLayout(this))
    , mWidthLabel(new QLabel(tr("Width :"), this))
    , mWidthInput(new QSpinBox(this))
    , mValidateButton(new QPushButton(tr("validate"),this))
    , mClosePixmap(QPixmap(":/images/close.svg"))
    , mMinimumTableSize(1)
{
    mWidthInput->setMinimum(mMinimumTableSize);

    mWidthLayout->addWidget(mWidthLabel);
    mWidthLayout->addWidget(mWidthInput);

    mVLayout->addItem(mWidthLayout);
    mVLayout->addWidget(mValidateButton);

    mVLayout->setMargin(mClosePixmap.width());

    setGeometry(QRect(QPoint(), mVLayout->sizeHint()));

    connect(mValidateButton, SIGNAL(clicked()), this, SIGNAL(validationRequired()));
}

void UBCellPropertiesPalette::setPos(QPoint pos)
{
    move(pos);
}

UBCellPropertiesPalette::~UBCellPropertiesPalette()
{

}

int UBCellPropertiesPalette::width() const
{
    return mWidthInput->value();
}

void UBCellPropertiesPalette::paintEvent(QPaintEvent *event)
{
    UBFloatingPalette::paintEvent(event);

    QPainter painter(this);
    painter.drawPixmap(0, 0, mClosePixmap);
}

void UBCellPropertiesPalette::mouseReleaseEvent(QMouseEvent * event)
{
    if (event->pos().x() >= 0 && event->pos().x() < QPixmap(":/images/close.svg").width()
        && event->pos().y() >= 0 && event->pos().y() < QPixmap(":/images/close.svg").height())
    {
        event->accept();
        hide();
    }

    UBFloatingPalette::mouseReleaseEvent(event);
}

