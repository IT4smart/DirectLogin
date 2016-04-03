#include "loginbox.h"

LoginBox::LoginBox(QObject *parent) : QObject(parent)
{

}


// Get functions:
QString LoginBox::username(void) {
    return m_username;
}

QString LoginBox::password(void) {
    return m_username;
}


// Set funtions:
void LoginBox::setUsername(QString &u) {
    if (u != m_username) {
        m_username = u;
        emit usernameChanged();
        qDebug() << u << endl;
    }
}

void LoginBox::setPassword(QString &p) {
    if (p != m_password) {
        m_password = p;
        emit passwordChanged();
        qDebug() << p << endl;
    }
}

// Launch a Citrix session
void LoginBox::do_login(void) {
    storebrowse_login = new Storebrowse(this->m_username, this->m_password);

    QStringList names;
    QStringList links;
    login_success = storebrowse_login->storebrowse_enumerate(&names, &links);

    QString desktop = "ddcxd1.W7 Lehrer Test $S5-3";
    login_success = storebrowse_login->storebrowse_launch(desktop);

    qDebug() << "LoginbBox->login_success:\t" << login_success << endl;

    delete storebrowse_login;

    emit loginDone(login_success);

    this->m_username.clear();
    this->m_password.clear();
}

// Slots:
void LoginBox::login_clicked(void) {
    qDebug() << "Login clicked" << endl;
    do_login();
}
