#include "storebrowse.h"

Storebrowse::Storebrowse(QString username, QString password)
{
    // Set login variables
    this->username = username.toStdString();
    this->password = password.toStdString();

    // Name of the shared memory segment
    shared_memory_key = 1234;

    shared_memory_init();
    shared_memory_struct_init();

    loginProcess = NULL;
}

Storebrowse::~Storebrowse() {
    shmctl(shared_memory_ID, IPC_RMID, NULL);
}

void Storebrowse::shared_memory_init(void) {

    // Create the shared memory segment
    shared_memory_ID = shmget(shared_memory_key, sizeof(sharedStruct), IPC_CREAT | 0666);

    // Now we attach the segment to our data space.
    shared_memory = shmat(shared_memory_ID, NULL, 0);

    // Set sharedStruct to shared memory
    shared_memory_struct = (sharedStruct*) shared_memory;

}

void Storebrowse::shared_memory_struct_init(void) {
    shared_memory_struct->terminated = false;
    shared_memory_struct->login_success = false;
    shared_memory_struct->n_login = 0;
    strcpy(shared_memory_struct->username, this->username.c_str());
    strcpy(shared_memory_struct->password, this->password.c_str());
}

bool Storebrowse::try_login(void) {

    bool processFinished;

    loginProcess = new QProcess();

    loginProcess->start("sh");
    // loginProcess->write("/opt/Citrix/ICAClient/util/storebrowse -E 'https://ddcxd1.ass-hn.de/citrix/xdstore/discovery'");
    loginProcess->write("/opt/Citrix/ICAClient/util/storebrowse -L 'ddcxd1.W7 Lehrer Test $S5-3' 'https://ddcxd1.ass-hn.de/citrix/xdstore/discovery'");
    loginProcess->closeWriteChannel();

    qDebug() << "Wait" << endl;
    processFinished = loginProcess->waitForFinished(30000);

    if (!processFinished)
        loginProcess->kill();
    else
        qDebug() << shared_memory_struct->login_success << endl;

    qDebug() << loginProcess->readAllStandardOutput() << endl;

    loginProcess->close();
    loginProcess->deleteLater();

    loginProcess = NULL;

    return shared_memory_struct->login_success;
}
