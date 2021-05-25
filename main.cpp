#include <QCoreApplication>

#include "superviser.h"

#include <QDebug>
#include<iostream>
#include<QTextStream>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    superviser test;
    QTextStream in (stdin);
    QMap<QString, int> mapping;

    mapping["start"] = 1;
    mapping["kill"] = 2;
    mapping["exit"] = 3;
    mapping["look_all"] = 4;

    QString answer, ms_name;

    while(true)
    {
        qDebug() << Qt::endl << "If u want to start service, write start, \n"
                                "If u want to  kill service, writel kill \n"
                                "if u want to look which services has run write look_all\n"
                                "if u want to exit, write exit ";
        in >> answer;
        \
        switch(mapping[answer])
        {
            case 1:
            {
                qDebug() << Qt::endl << "Enter name of the service ";
                in >> ms_name;
                test.slot_start_microservice(ms_name);
                break;
            }

            case 2:
            {
                qDebug() << Qt::endl << "Enter name of the service ";
                in >> ms_name;
                test.slot_kill_microservice(ms_name);
                break;
            }

            case 3:
            {
                qDebug() << Qt::endl << "Good Bye ";
                exit(0);
                break;
            }

            case 4:
            {
                test.look_all_services();
                break;
            }
        default:
            qDebug() << "Incorrect input, try again \n";

        }
    }

    return a.exec();
}
