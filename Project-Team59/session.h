#ifndef SESSION_H
#define SESSION_H

#include <QString>

class Session
{
public:
    Session(int sessionGroup, int sessionType, int sessionIntensity, QString sessionName);
    int getGroup();
    int getType();
    int getIntensity();
    QString getName();

private:
    int group;
    int type;
    int intensity;
    QString name;
};

#endif // SESSION_H
