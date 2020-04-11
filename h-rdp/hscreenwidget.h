#ifndef HSCREENWIDGET_H
#define HSCREENWIDGET_H

#include <QMainWindow>

#include <arengine/render/hirenderer.h>
#include <QMouseEvent>
#include <QKeyEvent>
using namespace harf::render;

namespace Ui {
class HScreenWidget;
}

class HScreenWidget : public QMainWindow
{
    Q_OBJECT
public:
    explicit HScreenWidget(QWidget *parent = nullptr);
    ~HScreenWidget();
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
private:
    Ui::HScreenWidget *ui;
};

#endif // HSCREENWIDGET_H
