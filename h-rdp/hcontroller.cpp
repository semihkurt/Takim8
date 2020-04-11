#include "hcontroller.h"
#include <QDebug>
#include <QString>
HController::HController() :
    mMode(HMode::Unknown),
    mConnectionController(nullptr),
    mStreamController(nullptr),
    mDBController(nullptr)
{
    mConnectionController = new HConnectionController();
    mStreamController = new HStreamController;
}

HController::~HController()
{
    //TODO: Destructor lar yazilacak.
}

HConnectionController *HController::connectionController() const
{
    return mConnectionController;
}

HStreamController *HController::streamController() const
{
    return mStreamController;
}

void HController::onUserConnectSlot(QString pId, QString pPassCode, int pMode)
{
    qDebug() << "received id " << pId << "received passCode: " << pPassCode << "mode: " << pMode;

    this->mID = pId.toStdString();
    this->mPassCode = pPassCode.toStdString();
    this->mMode = (HMode)pMode;

    if(mMode == HMode::Office){

        QObject::connect(mConnectionController,&HConnectionController::permissionGranted,mStreamController,&HStreamController::createScreenSendStream);
        QObject::connect(mStreamController,&HStreamController::encodedScreenDataReady,mConnectionController,&HConnectionController::onEncodedScreenDataReady);
        QObject::connect(mConnectionController, &HConnectionController::checkLDAP, mDBController, &HDBController::loginLDAP);

    }else if(mMode == HMode::Home){
//        mScreenUIWidget = new HScreenUIWidget; //QQuickWidget
        mScreenWidget = new HScreenWidget();   //QMainWindow
        WId tWID = mScreenWidget->winId();

        mStreamController->setWindowID(tWID);
    }

    mConnectionController->setMode(mMode);
    mConnectionController->onConnectionStart(mID,mPassCode);
}

void HController::onLDAPConnectSlot(QString pUsername, QString pPassword)
{
    if(mMode == HMode::Home){
        qDebug() << "received pUsername " << pUsername << "received pPassword: " << pPassword;

        this->mUsername = pUsername.toStdString();
        this->mPassword = pPassword.toStdString();

        mConnectionController->onLDAPConnectClicked(mUsername,mPassword);

        QObject::connect(mConnectionController,&HConnectionController::permissionGranted,mStreamController,&HStreamController::createVideoReceiveStream);
        QObject::connect(mConnectionController,&HConnectionController::permissionGranted,mScreenWidget,&HScreenWidget::createScreenWindow);
        QObject::connect(mConnectionController,&HConnectionController::encodedScreenDataCome,mStreamController,&HStreamController::onEncodedScreenDataCome);

    }else{
        qDebug() << "You shouldnt have clicked ldap connect button";
    }
}
