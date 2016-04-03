#ifndef LOGINBOX_H
#define LOGINBOX_H

#include <QObject>
#include <QDebug>
#include <QString>
#include <QStringList>

#include "storebrowse.h"

class LoginBox : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString username READ username WRITE setUsername NOTIFY usernameChanged)
    Q_PROPERTY(QString password READ password WRITE setPassword NOTIFY passwordChanged)
public:
    explicit LoginBox(QObject *parent = 0);

    // Get functions:
    QString username(void);
    QString password(void);

    // Set functions:
    void setUsername(QString &u);
    void setPassword(QString &p);

signals:
    void usernameChanged(void);
    void passwordChanged(void);
    void loginDone(bool loginBool);
    
public slots:
    void login_clicked(void);

private:
    QString m_username;
    QString m_password;

    bool login_success;

    Storebrowse *storebrowse_login;
    void do_login(void);
};

#endif // LOGINBOX_H
