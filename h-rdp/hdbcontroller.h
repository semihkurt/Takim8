#ifndef HDBCONTROLLER_H
#define HDBCONTROLLER_H
#include <harfdb/hdatabasefactory.h>
#include <QObject>

using namespace harf::database;

class HDBController : public QObject
{
    Q_OBJECT
public:
    HDBController();
signals:
    void ldapSuccess();
public slots:
    bool loginLDAP(std::string pUsername,std::string pPassword);
private:
    HIDatabaseService* mDatabaseService;
};

#endif // HDBCONTROLLER_H
