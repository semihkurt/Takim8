#include "hdbcontroller.h"

HDBController::HDBController() :
    mDatabaseService(nullptr)
{
    std::string tErr;
    mDatabaseService = HIDatabaseFactory::createDbConnector(tErr);

    if(!tErr.empty())
        std::cout << "DB Connection error occurred: " << tErr << std::endl;
}

bool HDBController::loginLDAP(std::string pUsername, std::string pPassword)
{
    std::string tErr;
    HIUser response = mDatabaseService->loginUser(pUsername,pPassword,"en",tErr);
    if(!tErr.empty()){
        std::cout << "Login LDAP Error occurred: " << tErr << std::endl;
        return false;
    }
    else{
        std::cout << "Welcome, " << response.name << " , " << response.email;
        emit ldapSuccess();
        return true;
    }
}
