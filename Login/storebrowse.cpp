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

    // Initialise login_process
    login_process = new QProcess();
    login_process->start("sh");
}

Storebrowse::~Storebrowse() {
    // Delete shared memory segment
    shmctl(shared_memory_ID, IPC_RMID, NULL);

    // Terminate login_process
    login_process->close();
    login_process->deleteLater();
    login_process = NULL;
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

bool Storebrowse::storebrowse_launch(QString &desktop) {

    bool login_process_finished;

    QString launchDekstop = "/opt/Citrix/ICAClient/util/storebrowse -L '" + desktop + "' 'https://ddcxd1.ass-hn.de/citrix/xdstore/discovery'";

    login_process->write(launchDekstop.toLatin1());
    login_process->closeWriteChannel();

    qDebug() << "login_process: wait" << endl;
    login_process_finished = login_process->waitForFinished(20000);

    if (!login_process_finished) {
        login_process->kill();
        qDebug() << "Kill login_process" << endl;
    } else {
        qDebug() << "login_success: \t" << shared_memory_struct->login_success << endl;
    }

    qDebug() << login_process->readAllStandardOutput() << endl;

    return shared_memory_struct->login_success;
}

bool Storebrowse::storebrowse_enumerate(QStringList* desktops) {

    QByteArray buffer;
    bool login_process_finished;

    login_process->write("/opt/Citrix/ICAClient/util/storebrowse -E 'https://ddcxd1.ass-hn.de/citrix/xdstore/discovery'");
    //login_process->closeWriteChannel();

    qDebug() << "login_process: wait" << endl;
    while(login_process->waitForFinished(20000))
        buffer.append(login_process->readAllStandardOutput());

    if (!login_process_finished) {
        login_process->kill();
        return false;
    } else {
        qDebug() << shared_memory_struct->login_success << endl;
    }

    qDebug() << login_process->readAllStandardOutput() << endl;

    parse_desktops(&buffer, desktops);

    return shared_memory_struct->login_success;
}

void Storebrowse::parse_desktops(QByteArray* buffer, QStringList* desktops) {

    // Split desktop string:
    QString sbuf = buffer->data();
    sbuf.remove("'");
    QStringList zeilen = sbuf.split("\n", QString::SkipEmptyParts);

    // Split in lines
    for (int i=0;i<zeilen.size();i++) {
        // Spilt in columns
        QStringList spalten = zeilen.at(i).split("\t", QString::SkipEmptyParts);
        //names.push_back(spalten.at(1).toLocal8Bit());
        //links.push_back(spalten.at(0).toLocal8Bit());
    }
}
