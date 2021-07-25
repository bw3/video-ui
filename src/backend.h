#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <QString>
#include <QSettings>

class BackEnd : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString mediaDbUri READ mediaDbUri)
public:
    explicit BackEnd(QObject *parent = nullptr);

    QString mediaDbUri();

signals:
private:
    QSettings m_settings;
};

#endif // BACKEND_H
