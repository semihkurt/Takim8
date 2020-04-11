#include "hscreenwidget.h"
#include "ui_hscreenwidget.h"
#include <arengine/harenginefactory.h>

HScreenWidget::HScreenWidget(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::HScreenWidget)
{
    ui->setupUi(this);

}

HScreenWidget::~HScreenWidget()
{
    delete ui;
}


void HScreenWidget::createScreenWindow()
{
    initialize();
}

void HScreenWidget::mousePressEvent(QMouseEvent *pEvent)
{
    QMainWindow::mousePressEvent(pEvent);

    if(mRenderer)
    {
        int tButton = 0;
        if(pEvent->button() == Qt::MouseButton::LeftButton)
            tButton = 1;
        if(pEvent->button() == Qt::MouseButton::RightButton)
            tButton = 2;
        if(pEvent->button() == Qt::MouseButton::MiddleButton)
            tButton = 3;

        mRenderer->onMouseEventRaw(0, pEvent->pos().x(), pEvent->pos().y(), tButton);
    }
}

void HScreenWidget::mouseReleaseEvent(QMouseEvent *pEvent)
{
    QMainWindow::mouseReleaseEvent(pEvent);

    if(mRenderer)
    {
        int tButton = 0;
        if(pEvent->button() == Qt::MouseButton::LeftButton)
            tButton = 1;
        if(pEvent->button() == Qt::MouseButton::RightButton)
            tButton = 2;
        if(pEvent->button() == Qt::MouseButton::MiddleButton)
            tButton = 3;

        mRenderer->onMouseEventRaw(1, pEvent->pos().x(), pEvent->pos().y(), tButton);
    }
}

void HScreenWidget::mouseMoveEvent(QMouseEvent *pEvent)
{
    QMainWindow::mouseMoveEvent(pEvent);

    if(mRenderer)
    {
        int tButton = 0;
        if(pEvent->button() == Qt::MouseButton::LeftButton)
            tButton = 1;
        if(pEvent->button() == Qt::MouseButton::RightButton)
            tButton = 2;
        if(pEvent->button() == Qt::MouseButton::MiddleButton)
            tButton = 3;

        mRenderer->onMouseEventRaw(2, pEvent->pos().x(), pEvent->pos().y(), tButton);
    }
}

void HScreenWidget::wheelEvent(QWheelEvent *pEvent)
{
    QMainWindow::wheelEvent(pEvent);

    if(mRenderer)
        mRenderer->onMouseWheelEventRaw(3, pEvent->pos().x(), pEvent->pos().y(), pEvent->delta(), 3);
}

void HScreenWidget::mouseDoubleClickEvent(QMouseEvent *pEvent)
{
    QMainWindow::mouseDoubleClickEvent(pEvent);

    if(mRenderer)
    {
        int tButton = 0;
        if(pEvent->button() == Qt::MouseButton::LeftButton)
            tButton = 1;
        if(pEvent->button() == Qt::MouseButton::RightButton)
            tButton = 2;
        if(pEvent->button() == Qt::MouseButton::MiddleButton)
            tButton = 3;

        mRenderer->onMouseEventRaw(4, pEvent->pos().x(), pEvent->pos().y(), tButton);
    }
}

void HScreenWidget::keyPressEvent(QKeyEvent *event)
{
    QMainWindow::keyPressEvent(event);

    if(mRenderer == nullptr)
        return;

    mRenderer->onKeyboardEventRaw(event->text().toStdString(), (int)harf::io::KeyboardEvents::Press, event->nativeVirtualKey());
}

void HScreenWidget::keyReleaseEvent(QKeyEvent *event)
{
    QMainWindow::keyReleaseEvent(event);

    if(mRenderer == nullptr)
        return;

    mRenderer->onKeyboardEventRaw(event->text().toStdString(),(int)harf::io::KeyboardEvents::Release, event->nativeVirtualKey());
}

void HScreenWidget::initialize()
{
//    setClearColor(Qt::transparent);
    setAttribute(Qt::WA_AlwaysStackOnTop, true);
    setAttribute(Qt::WA_TranslucentBackground, true);
    setAttribute(Qt::WA_TransparentForMouseEvents, false);
    setAttribute(Qt::WA_AcceptTouchEvents, true);

//    QSurfaceFormat tFormat = format();
//    tFormat.setSamples(0);
//    setFormat(tFormat);

//    setResizeMode(SizeRootObjectToView);

    installEventFilter(this);

    show();
//    connect(engine(), &QQmlEngine::quit, [=]{
//        QApplication::quit();
//    });
}
