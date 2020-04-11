#include "hscreenuiwidget.h"
#include <iostream>
#include <QQmlEngine>
#include <QApplication>
#include <arengine/harenginefactory.h>
using namespace std;

HScreenUIWidget::HScreenUIWidget() :
    mRenderer(nullptr)
{
    mRenderer = harf::HAREngineFactory::createRenderer(640,480);

//    mRenderer->setContextGeometryChangedFunction(std::bind(&HMainWindow::rendererGeometryChanged,this, std::placeholders::_1, std::placeholders::_2));
//    mRenderer->setMouseEventFunction(std::bind(&HMainWindow::mouseHandlerFunction, this, std::placeholders::_1, std::placeholders::_2));
//    mRenderer->enableMouseEventHandler();
//    mRenderer->setKeyboardEventFunction(std::bind(&HMainWindow::keyboardHandlerFunction, this, std::placeholders::_1, std::placeholders::_2));


    setSource(QUrl("qrc:/ScreenWindow.qml"));

//    initialize();
}

HScreenUIWidget::HScreenUIWidget(HIRenderer *renderer)
{
    this->mRenderer = renderer;
    initialize();
}

void HScreenUIWidget::createScreenWindow()
{
    initialize();
}

void HScreenUIWidget::mousePressEvent(QMouseEvent *pEvent)
{
    QQuickWidget::mousePressEvent(pEvent);

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

void HScreenUIWidget::mouseReleaseEvent(QMouseEvent *pEvent)
{
    QQuickWidget::mouseReleaseEvent(pEvent);

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

void HScreenUIWidget::mouseMoveEvent(QMouseEvent *pEvent)
{
    QQuickWidget::mouseMoveEvent(pEvent);

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

void HScreenUIWidget::wheelEvent(QWheelEvent *pEvent)
{
    QQuickWidget::wheelEvent(pEvent);

    if(mRenderer)
        mRenderer->onMouseWheelEventRaw(3, pEvent->pos().x(), pEvent->pos().y(), pEvent->delta(), 3);
}

void HScreenUIWidget::mouseDoubleClickEvent(QMouseEvent *pEvent)
{
    QQuickWidget::mouseDoubleClickEvent(pEvent);

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

void HScreenUIWidget::keyPressEvent(QKeyEvent *event)
{
    QQuickWidget::keyPressEvent(event);

    if(mRenderer == nullptr)
        return;

    std::cout << "HvlcomUIWidget keyPressEvent QKeyEvent key: " << event->key()
             << " ,native scan code: " << event->nativeScanCode()
             << " ,native virtual key: " << event->nativeVirtualKey()
             << " ,native modifiers: " << event->nativeModifiers() << std::endl;
    mRenderer->onKeyboardEventRaw(event->text().toStdString(), (int)harf::io::KeyboardEvents::Press, event->nativeVirtualKey());
}

void HScreenUIWidget::keyReleaseEvent(QKeyEvent *event)
{
    QQuickWidget::keyReleaseEvent(event);

    if(mRenderer == nullptr)
        return;

    std::cout << "HvlcomUIWidget keyReleaseEvent QKeyEvent key: " << event->key()
             << " ,native scan code: " << event->nativeScanCode()
             << " ,native virtual key: " << event->nativeVirtualKey()
             << " ,native modifiers: " << event->nativeModifiers() << std::endl;
    mRenderer->onKeyboardEventRaw(event->text().toStdString(),(int)harf::io::KeyboardEvents::Release, event->nativeVirtualKey());
}

void HScreenUIWidget::initialize()
{
    setClearColor(Qt::transparent);
    setAttribute(Qt::WA_AlwaysStackOnTop, true);
    setAttribute(Qt::WA_TranslucentBackground, true);
    setAttribute(Qt::WA_TransparentForMouseEvents, false);
    setAttribute(Qt::WA_AcceptTouchEvents, true);

    QSurfaceFormat tFormat = format();
    tFormat.setSamples(0);
    setFormat(tFormat);

    setResizeMode(SizeRootObjectToView);

    installEventFilter(this);

    connect(engine(), &QQmlEngine::quit, [=]{
        QApplication::quit();
    });
}
