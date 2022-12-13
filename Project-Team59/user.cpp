#include <QTextStream>
#include "user.h"

User::User()
{

}

int User::numSessions() {
    return sessions.length();
}

QStringList User::getSessionList() {
    QStringList records;
    for (int i = 0; i < sessions.length(); i++) {
        records << sessions.at(i)->getName();
    }
    return records;
}

void User::getSession(QString name, Session** s) {
    QTextStream out(stdout);
    for (int i = 0; i < sessions.length(); i++) {
        if (sessions.at(i)->getName() == name ) {
            *s = sessions.at(i);
        }
    }
}

void User::addSession(Session *s) {
    sessions.append(s);
}

