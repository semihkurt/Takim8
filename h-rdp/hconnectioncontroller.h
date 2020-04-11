#ifndef HCONNECTIONCONTROLLER_H
#define HCONNECTIONCONTROLLER_H
#include <QObject>
#include <hrdpenums.h>
#include <harfconnection/hconnectionfactory.h>
#include <harfconnection/hicontinuousconnection.h>
#include <functional>

using namespace harf::connection;

class HConnectionController : public QObject
{
    Q_OBJECT
public:
    HConnectionController();
    void setMode(HMode mode);
    HarfConnectionEnum getConnectionStatus();

signals:
    bool checkLDAP(std::string pUsername, std::string pPassword);
    void permissionGranted();
    void encodedScreenDataCome(char* data,int size);

public slots:
    void onConnectionStart(std::string tID, std::string tPasscode);
    void onConnectionStop();
    void onLDAPConnectClicked(std::string pUsername, std::string pPassword);

    void onEncodedScreenDataReady(char* data, int size);
private:
    HIContinuousConnection* mContinousConnection;
    std::string mID;
    std::string mPasscode;
    HMode mMode;


    void sendData(char* data, int size);

    void onConnected(HIConnectionHelper *connectionHelper, HClientInfo *fromClient);
    void onDataReceived(unsigned short channelID, char *data, int size, char *clientID);
    void onDisconnected();
};

#endif // HCONNECTIONCONTROLLER_H
