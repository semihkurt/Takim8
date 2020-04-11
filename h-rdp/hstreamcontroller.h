#ifndef HSTREAMCONTROLLER_H
#define HSTREAMCONTROLLER_H
#include <QObject>
#include <QMainWindow>
#include <stream/hstreamfactory.h>
#include <functional>
using namespace harf::stream;
using namespace harf::stream::video;

class HStreamController : public QObject
{
    Q_OBJECT
public:
    HStreamController();

    void setWindowID(WId pWID);
signals:
    void encodedScreenDataReady(char* data, int size);
public slots:
    void createScreenSendStream();
    void createVideoReceiveStream();

    void onEncodedScreenDataCome(char* data,int size);
private:
    HIScreenSendStream* mScreenSendStream;
    HIVideoReceiveStream* mVideoReceiveStream;

    void encodedScreenDataReceived(char* data, int size);

    int mWId;
};

#endif // HSTREAMCONTROLLER_H
