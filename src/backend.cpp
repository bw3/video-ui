#include "backend.h"

BackEnd::BackEnd(QObject *parent) :
    QObject(parent), m_settings("video-ui")
{

}

QString BackEnd::mediaDbUri() {
    return m_settings.value("mediadb-uri").toString();
}
