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
}

Storebrowse::~Storebrowse() {
    // Delete shared memory segment
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

bool Storebrowse::storebrowse_launch(QString &desktop) {

    QByteArray buffer;
    bool launch_process_finished;
    bool launch_succeeded;

    // Initialise launch_process
    launch_process = new QProcess();
    launch_process->start("sh");

    QString launchDekstop = "/opt/Citrix/ICAClient/util/storebrowse -L '" + desktop + "' 'https://ddcxd1.ass-hn.de/citrix/xdstore/discovery'";

    launch_process->write(launchDekstop.toLatin1());
    launch_process->closeWriteChannel();

    qDebug() << "Launch_process:\t" << "Wait" << endl;
    launch_process_finished = launch_process->waitForFinished(20000);
    buffer = launch_process->readAll();

    //buffer = enumerate_process->readAllStandardOutput();
    qDebug() << "Buffer:\t" << QString(buffer) << endl;

    if (!launch_process_finished) {
        qDebug() << "launch_process_finished:\t" << launch_process_finished << endl;
        enumerate_process->kill();
        launch_succeeded = false;
    } else if (!shared_memory_struct->login_success) {
        qDebug() << "shared_memory_struct->login_success:\t" << shared_memory_struct->login_success << endl;
        launch_succeeded = false;
    } else {
        qDebug() << "Login_success: \t" << shared_memory_struct->login_success << endl;
        launch_succeeded = true;
    }

    // Terminate launch_process
    launch_process->close();
    launch_process->deleteLater();
    launch_process = NULL;

    return launch_succeeded;
}

bool Storebrowse::storebrowse_enumerate(QStringList* names, QStringList *links) {

    QByteArray buffer;
    bool enumerate_process_finished;
    bool enumerate_succeeded;

    // Initialise enumerate_process
    enumerate_process = new QProcess();
    enumerate_process->start("sh");
    enumerate_process->write("/opt/Citrix/ICAClient/util/storebrowse -E 'https://ddcxd1.ass-hn.de/citrix/xdstore/discovery'");
    enumerate_process->closeWriteChannel();

    qDebug() << "enumerate_process: wait" << endl;
    enumerate_process_finished = enumerate_process->waitForFinished(20000);

    buffer = enumerate_process->readAllStandardOutput();

    if (!enumerate_process_finished) {
        qDebug() << "enumerate_process_finished:\t" << enumerate_process_finished << endl;
        enumerate_process->kill();
        enumerate_succeeded = false;
    } else if (!shared_memory_struct->login_success) {
        qDebug() << "shared_memory_struct->login_success:\t" << shared_memory_struct->login_success << endl;
        enumerate_succeeded = false;
    } else {
        qDebug() << "shared_memory_struct->login_success:\t" << shared_memory_struct->login_success << endl;
        qDebug() << buffer << endl;
        parse_desktops(&buffer, names, links);
    }

    // Terminate launch_process
    enumerate_process->close();
    enumerate_process->deleteLater();
    enumerate_process = NULL;

    return enumerate_succeeded;
}

void Storebrowse::parse_desktops(QByteArray* buffer, QStringList* names, QStringList *links) {

    // Split desktop string:
    QString sbuf = buffer->data();
    sbuf.remove("'");
    QStringList zeilen = sbuf.split("\n", QString::SkipEmptyParts);

    // Split in lines
    for (int i=0;i<zeilen.size();i++) {
        // Spilt in columns
        QStringList spalten = zeilen.at(i).split("\t", QString::SkipEmptyParts);
        names->push_back(spalten.at(1).toLocal8Bit());
        qDebug() << spalten.at(1) << endl;
        links->push_back(spalten.at(0).toLocal8Bit());
        qDebug() << spalten.at(0) << endl;
    }
}
