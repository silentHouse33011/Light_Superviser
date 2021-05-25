#include "superviser.h"

#include <QDir>
#include<QProcess>
#include<QDebug>

superviser::superviser()
{
    services_directory = QDir::homePath() + "/" + "services";
}

void superviser::slot_start_microservice(const QString &name)
{
    already_run = false;
    qint64 pid;

    for(int i = 0; i < services_map.size(); ++i)
    {
        if(services_map.at(i).first == name)
        {
            qDebug() << "This microservice is already run";
            already_run = true;
            break;
        }
    }
    if(!already_run)
    {
        if(!QProcess::startDetached(services_directory + QDir::separator() + name,
                                    arguments, services_directory, &pid))
        {
            qDebug() << "Cant start the service " << name;
        }
        else
        {
            qDebug() << "Stasrted service " << name;
            this->services_map.push_back(QPair<QString ,int>(name, pid));
        }
    }
}

void superviser::slot_kill_microservice(const QString &name)
{
#ifdef __linux__
    QProcess kill_process;
    kill_process.start("pkill -f " + name);
    kill_process.kill();
#elif __WIN32__
    QProcess::execute("taskkill /F /IM " + name);
#endif
    //delete elem from services map after killing

    for(int i = 0; i < services_map.size(); ++i)
    {
        if(services_map.at(i).first == name)
        {
            services_map.erase(services_map.begin() + i);
        }
    }
}

void superviser::look_all_services()
{
    for(auto elem :services_map)
    {
        qDebug() << elem.first << " With pid " << elem.second;
    }
}
superviser::~superviser()
{

}
