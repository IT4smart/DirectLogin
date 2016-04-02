#ifndef STOREBROWSE_H
#define STOREBROWSE_H

#include <QString>
#include <QStringList>
#include <QDebug>
#include <QProcess>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include <stdio.h>
#include <stdlib.h>

struct sharedStruct {
    bool terminated;
    bool login_success;
    int n_login;
    char username[128];
    char password[128];
};

class Storebrowse
{
public:
    Storebrowse(QString username, QString password);
    ~Storebrowse();

    /*
     * Executes the storebrowse -E command to get the available desktops
     *
     * Input: QStringList* to save the desktops
     *
     * Return: true if login was successful; false if login failed
     *
     **/
    bool storebrowse_enumerate(QStringList *desktops);

    /*
     * Executes the storebrowse -L command to launch a Citrix session
     *
     * Input: QString &desktop to specify the desktop to be launched
     *
     * Return: true if session launch was successful; false if session launch failed
     *
     **/
    bool storebrowse_launch(QString &desktop);

private:
    std::string username;
    std::string password;

    QProcess *login_process;

    void parse_desktops(QByteArray* buffer, QStringList* desktops);

    // Shared memory:
    key_t shared_memory_key;
    int shared_memory_ID;
    void *shared_memory;
    sharedStruct *shared_memory_struct;

    void shared_memory_init(void);
    void shared_memory_struct_init(void);
};

#endif // STOREBROWSE_H
