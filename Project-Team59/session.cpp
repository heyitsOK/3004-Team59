#include "session.h"

Session::Session(int sessionGroup, int sessionType, int sessionIntensity, QString sessionName)
{
    group = sessionGroup;
    type = sessionType;
    intensity = sessionIntensity;
    name = sessionName;
}

int Session::getGroup() {
    return group;
}

int Session::getType() {
    return type;
}

int Session::getIntensity() {
    return intensity;
}

QString Session::getName() {
    return name;
}
