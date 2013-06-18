#include "RotatableGLDemo.hpp"

#include <QBoxLayout>
#include "GLWidget.hpp"

RotatableGLDemo::RotatableGLDemo(GLWidget* const widget, QWidget* parent) :
	QWidget(parent),
	glWidget(widget)
{
    xSlider = createSlider();
    xSlider->setInvertedControls(true);
    xSlider->setTickPosition(QSlider::TicksLeft);

    ySlider = createSlider();
    ySlider->setOrientation(Qt::Horizontal);
    ySlider->setTickPosition(QSlider::TicksAbove);

    zSlider = createSlider();
    zSlider->setTickPosition(QSlider::TicksRight);

    connect(xSlider, SIGNAL(valueChanged(int)), glWidget, SLOT(setScaledXRotation(int)));
    connect(glWidget, SIGNAL(xRotationChanged(int)), xSlider, SLOT(setValue(int)));
    connect(ySlider, SIGNAL(valueChanged(int)), glWidget, SLOT(setScaledYRotation(int)));
    connect(glWidget, SIGNAL(yRotationChanged(int)), ySlider, SLOT(setValue(int)));
    connect(zSlider, SIGNAL(valueChanged(int)), glWidget, SLOT(setScaledZRotation(int)));
    connect(glWidget, SIGNAL(zRotationChanged(int)), zSlider, SLOT(setValue(int)));

    QBoxLayout *vLayout = new QBoxLayout(QBoxLayout::TopToBottom);
    ySlider->setContentsMargins(xSlider->width(), 0, zSlider->width(), 0);
    vLayout->addWidget(ySlider);

    QBoxLayout *hLayout = new QBoxLayout(QBoxLayout::LeftToRight);
    hLayout->addWidget(xSlider);
    hLayout->addWidget(glWidget);
    hLayout->addWidget(zSlider);

    vLayout->addLayout(hLayout);
    setLayout(vLayout);
}

QSlider *RotatableGLDemo::createSlider() const
{
    static const int SCALE = 16;
    QSlider *slider = new QSlider(Qt::Vertical);
    slider->setRange(0, 360 * SCALE);
    slider->setSingleStep(SCALE);
    slider->setPageStep(30 * SCALE);
    slider->setTickInterval(15 * SCALE);
    return slider;
}

// vim: set ts=4 sw=4 et! :
