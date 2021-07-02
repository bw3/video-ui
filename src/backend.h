#ifndef BACKEND_H
#define BACKEND_H

#include "video_options.h"
#include "json.hpp"

#include <QObject>
#include <QString>

class MenuItem : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString html READ name WRITE setName NOTIFY changed)
    Q_PROPERTY(QString link READ link WRITE setLink NOTIFY changed)

public:
    MenuItem(const QString &name, const QString &link);

    bool operator == ( const MenuItem& rhs) const { return m_name == rhs.m_name; }
    bool operator != ( const MenuItem& rhs) const { return m_name != rhs.m_name; }
    bool operator <  ( const MenuItem& rhs) const { return m_name <  rhs.m_name; }
    bool operator >  ( const MenuItem& rhs) const { return m_name >  rhs.m_name; }
    bool operator <= ( const MenuItem& rhs) const { return m_name <= rhs.m_name; }
    bool operator >= ( const MenuItem& rhs) const { return m_name >= rhs.m_name; }

    const QString name();
    void setName(const QString &name);
    const QString link();
    void setLink(const QString &link);
    const nlohmann::json videoFileInfo();
    void setVideoFileInfo(const nlohmann::json& info);

signals:
    void changed();

private:
    QString m_name;
    QString m_link;
    nlohmann::json m_videoFileInfo;
};

class BackEnd : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QList<QObject*> menuItems READ menuItems NOTIFY menuItemsChanged)
    Q_PROPERTY(QList<QObject*> videoOptionsList READ videoOptionsList NOTIFY videoOptionsListChanged)

public:
    explicit BackEnd(QObject *parent = nullptr);

    QList<QObject*> menuItems();
    QList<QObject*> videoOptionsList();

    Q_INVOKABLE QString activateMenuItem(const QString &link);
    Q_INVOKABLE QString selectMenuItem(const int index);
    Q_INVOKABLE void previousMenu();
    Q_INVOKABLE void playVideo();
signals:
    void filePathChanged();
    void menuItemsChanged();
    void videoOptionsListChanged();
private:
    void adjustInputs(int num);
    void generateMenuItems();

    std::string inode;
    std::string m_filePath;
    QList<QObject*> m_menuItems;
    VideoOptions m_videoOptions;
};

#endif // BACKEND_H
