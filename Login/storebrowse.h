#ifndef STOREBROWSE_H
#define STOREBROWSE_H

#include <QString>
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

    bool try_login(void);

private:
    std::string username;
    std::string password;

    QProcess *loginProcess;

    // Shared memory:
    key_t shared_memory_key;
    int shared_memory_ID;
    void *shared_memory;
    sharedStruct *shared_memory_struct;

    void shared_memory_init(void);
    void shared_memory_struct_init(void);
};

#endif // STOREBROWSE_H
