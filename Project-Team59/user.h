#ifndef USER_H
#define USER_H

#include "session.h"
#include <QStringList>


class User
{
public:
    User();
    //function to check if user has any sessions
    int numSessions();
    //function that returns QStringList of all the sessions
    QStringList getSessionList();
    //function that parameter returns a session object matching the name parameter
    void getSession(QString name, Session **s);
    //function that takes a session pointer as a parameter and adds it to our list
    void addSession(Session *s);

private:
    QList<Session *> sessions;
};

#endif // USER_H
