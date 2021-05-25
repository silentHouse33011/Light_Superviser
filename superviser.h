#pragma once
#include <QObject>

class superviser : public QObject
{
public:
    superviser();
    ~superviser();
    void look_all_services();
private:
    QString services_directory;
    QStringList arguments;

    QVector<QPair<QString, int >> services_map;

public slots:
    void slot_start_microservice(const QString &name);
    void slot_kill_microservice(const QString &name);
    bool already_run;
};
