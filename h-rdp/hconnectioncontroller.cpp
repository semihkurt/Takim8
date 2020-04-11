#include "hconnectioncontroller.h"
#include <QRandomGenerator>
#include <iostream>
#include<vector>
#include<sstream>

HConnectionController::HConnectionController() :
    mContinousConnection(nullptr),
    mID(""),
    mPasscode("")
{
    mContinousConnection = HConnectionFactory::createContinuousConnection();
    mContinousConnection->setAutoReconnect(true);
    mContinousConnection->setDefaultChannelCount(5);
    mContinousConnection->setOnConnectedFunction(std::bind(&HConnectionController::onConnected,this,std::placeholders::_1,std::placeholders::_2));
    mContinousConnection->setOnDisconnectedFunction(std::bind(&HConnectionController::onDisconnected,this));
    mContinousConnection->setOnDataReceivedFunction(std::bind(&HConnectionController::onDataReceived,this,std::placeholders::_1,std::placeholders::_2
                                                              ,std::placeholders::_3,std::placeholders::_4));

}

void HConnectionController::setMode(HMode mode)
{
    this->mMode = mode;
}

HarfConnectionEnum HConnectionController::getConnectionStatus()
{
    if(mContinousConnection != nullptr)
        return mContinousConnection->getConnectionStatus();
    return HarfConnectionEnum::HarfConnectionNotConnected;
}

void HConnectionController::onConnectionStart(std::string tID, std::string tPasscode)
{
    this->mPasscode = tPasscode;
    this->mID = tID;

    std::string username = "test";
    std::string password = "MjQxNjU5Qz";
    std::string err;

    switch (mMode) {
    case HMode::Home:
    {
        std::string tDisplayName = "Test Test Deneme 1 2 3";
        auto randomvalue = QRandomGenerator::securelySeeded().bounded(1000,1000000);
        std::string tSelfName = tDisplayName + "|" + QString::number(randomvalue).toStdString();

        mContinousConnection->startConnection(username,password,tSelfName,tID,"RDP",err);
        mContinousConnection->sendData((unsigned short)HConnectionChannels::Passcode,(char*)tPasscode.c_str(),tPasscode.size());

        emit permissionGranted(); //TODO, LDAP sayfasindan gelene kadar burada
        break;
    }
    case HMode::Office:
        mContinousConnection->waitForConnection(username,password,tID,"RDP",err);
        break;
    case HMode::Unknown:

        break;
    }

    if (!err.empty())
       std::cout << "Continuous Connection Error : " << err <<  std::endl;
}

void HConnectionController::onConnectionStop()
{
    std::cout << "Connection Stopped by User" << std::endl;
}

void HConnectionController::onLDAPConnectClicked(std::string pUsername, std::string pPassword)
{
    std::string tEncryptedMessage = pUsername + "_" + pPassword;
    if(mContinousConnection != nullptr && mContinousConnection->getConnectionStatus() == HarfConnectionEnum::HarfConnectionConnected){
        mContinousConnection->sendData((unsigned short)HConnectionChannels::LDAP,tEncryptedMessage.c_str(),tEncryptedMessage.size());
    }
}

void HConnectionController::onEncodedScreenDataReady(char *data,int size)
{
    if(HMode::Office == mMode){
        if(mContinousConnection != nullptr && mContinousConnection->getConnectionStatus() == HarfConnectionEnum::HarfConnectionConnected){
            mContinousConnection->sendData((unsigned short) HConnectionChannels::Video,data,size);
        }
    }
}

void HConnectionController::onConnected(HIConnectionHelper *connectionHelper, HClientInfo *fromClient)
{
    std::cout << fromClient->name << " ile baglanti kuruldu";
}

void HConnectionController::onDataReceived(unsigned short channelID, char *data, int size, char *clientID)
{
    std::string tMsg(data,size);
//    std::cout << clientID << " dan mesaj geldi, " << tMsg;
    switch ((HConnectionChannels) channelID) {
    case HConnectionChannels::Passcode:
        if(mMode == HMode::Office){
            std::string tEncryptedMessage = "";
            if(tMsg.compare(mPasscode) == 0){
                std::string tSuccessMsg = "Passcode successfully matched";

                tEncryptedMessage += "1_" + tSuccessMsg; //TODO: SSL ile yollanacak. Okunabilir olmayacak.

                emit permissionGranted();

                mContinousConnection->sendData(channelID,tEncryptedMessage.c_str(),tEncryptedMessage.size());
                //TODO Mode Home oldugunda 0 sa UI a uyarı mesajı verılecek ve sayfa gecilmeyecek, 1 ise success message gosterilip LDAP sayfasına gecilecek.
            }else{
                std::string tErr = "Passcode does not match, Try again!";

                tEncryptedMessage += "0_" + tErr; //TODO: SSL ile yollanacak. Okunabilir olmayacak.

                mContinousConnection->sendData(channelID,tEncryptedMessage.c_str(),tEncryptedMessage.size());
            }
        }else if(mMode == HMode::Home){ //TODO Buraya yazılacak
            if(tMsg.compare("1")){
                std::cout << "Passcode matched" << std::endl;
            }else {
                std::cout << "Passcode did not match" << std::endl;
            }
        }
        break;
    case HConnectionChannels::LDAP:
        if(mMode == HMode::Office){
            std::vector<std::string> result;
            std::stringstream s_stream(tMsg); //create string stream from the string
            while(s_stream.good()) {
                std::string substr;
                getline(s_stream, substr, '_'); //get first string delimited by comma
                result.push_back(substr);
            }

            bool tLDAP = emit checkLDAP(result.at(0), result.at(1));
            if(tLDAP){
                std::cout << "LDAP success" << std::endl;
                std::string tEncryptedMsg = "success"; //TODO: SSL ile yollanacak. Okunabilir olmayacak.
                mContinousConnection->sendData((unsigned short)HConnectionChannels::LDAP,tEncryptedMsg.c_str(),tEncryptedMsg.size());

            }else{
                std::cout << "LDAP Fail!" << std::endl;
            }
        }else if(mMode == HMode::Home){
            if(tMsg.compare("success") == 0){
                std::cout << "success harbi success";
                emit permissionGranted();
            }
        }
        break;
    case HConnectionChannels::Video:
        if(mMode == HMode::Home){
//            std::cout << "Data come with size: " << size;
            emit encodedScreenDataCome(data,size);
        }
        break;
    }
}

void HConnectionController::onDisconnected()
{
    std::cout << "Baglanti koptu!";
}


