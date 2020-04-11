#ifndef HSCREENUIWIDGET_H
#define HSCREENUIWIDGET_H
#include <QQuickWidget>
#include <arengine/render/hirenderer.h>

using namespace harf::render;

class HScreenUIWidget : public QQuickWidget
{
public:
    HScreenUIWidget();
    HScreenUIWidget(HIRenderer *renderer);

public slots:
    void createScreenWindow();
protected:
    void mousePressEvent(QMouseEvent *pEvent) override;
    void mouseReleaseEvent(QMouseEvent *pEvent) override;
    void mouseMoveEvent(QMouseEvent *pEvent) override;
    void wheelEvent(QWheelEvent *pEvent) override;
    void mouseDoubleClickEvent(QMouseEvent* pEvent) override;

    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;
private:
    HIRenderer* mRenderer;
    void initialize();
};

#endif // HSCREENUIWIDGET_H
