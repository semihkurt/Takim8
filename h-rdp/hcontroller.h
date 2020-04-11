#ifndef HCONTROLLER_H
#define HCONTROLLER_H
#include <QObject>
#include "hrdpenums.h"
#include "hconnectioncontroller.h"
#include "hstreamcontroller.h"
#include "hdbcontroller.h"
#include "hscreenuiwidget.h"
#include "hscreenwidget.h"

class HController : public QObject
{
    Q_OBJECT
public:
    HController();
    ~HController();

    HConnectionController *connectionController() const;
    HStreamController *streamController() const;
public slots:
    void onUserConnectSlot(QString pId, QString pPassCode, int pMode);
    void onLDAPConnectSlot(QString pUsername, QString pPassword);
private:
    HConnectionController* mConnectionController;
    HStreamController* mStreamController;
    HDBController* mDBController;
    HScreenUIWidget* mScreenUIWidget;
    HScreenWidget* mScreenWidget;

    std::string mID;
    std::string mPassCode;
    HMode mMode;

    std::string mUsername;
    std::string mPassword;

};

#endif // HCONTROLLER_H
