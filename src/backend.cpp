#include "backend.h"
#include "menu_option.h"
#include "json.hpp"
#include "httplib.h"

#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <iostream>
#include <QProcess>
#include <mpv/client.h>
#include <locale.h>
#include <regex>

const std::string ROOT_PATH = "http://hostname";
const std::string GAMES_MENU = "games";

//#define PYTHON_SCRIPT_NAME "/home/user/bin/adjust_projector.py"
#define PYTHON_SCRIPT_NAME "/home/brad/test.py"

using json = nlohmann::json;

MenuItem::MenuItem(const QString& name, const QString& link)
{
    m_name = name;
    m_link = link;
}

const QString MenuItem::name()
{
    return m_name;
}

void MenuItem::setName(const QString& name)
{
    if(name == m_name) {
        return;
    }
    m_name = name;
    emit changed();
}

const QString MenuItem::link()
{
    return m_link;
}

void MenuItem::setLink(const QString& link)
{
    if(link == m_link) {
        return;
    }
    m_link = link;
    emit changed();
}

const json MenuItem::videoFileInfo() {
    return m_videoFileInfo;
}

void MenuItem::setVideoFileInfo(const json& info) {
    m_videoFileInfo = info;
}


void BackEnd::adjustInputs(int num)
{
    QProcess *pyProcess = new QProcess(this);
    QStringList arguments;
    arguments << "/home/user/bin/adjust_inputs.py";
    arguments << std::to_string(num).c_str();
    pyProcess->start("/usr/bin/python", arguments);
    pyProcess->waitForFinished(-1);
    delete pyProcess;
}

BackEnd::BackEnd(QObject *parent) :
    QObject(parent)
{
    m_filePath = "/";
    generateMenuItems();
    adjustInputs(0);
}

std::string fullFilePath(std::string path) {
    return ROOT_PATH + "/" + path;
}

bool includeInMenu(struct dirent* entry) {
    std::string filename(entry->d_name);
    if(filename[0] == '.') {
        return false;
    }
    if(entry->d_type == DT_DIR) {
        return true;
    }
    if(filename.rfind(".mkv") == filename.length() - 4) {
        return true;
    }
    return false;
}

std::string getSingleFilename(std::string dir_path) {
    DIR* dir_ptr = opendir( dir_path.c_str() );
    if( dir_ptr == NULL ) {
        std::cout << "NULL\n";
        return "";
    }
    std::string filename;
    int numEntries = 0;
    struct dirent* entry = readdir(dir_ptr);
    while(entry != NULL && numEntries < 2) {
        if(!includeInMenu(entry)) {
            entry = readdir(dir_ptr);
            continue;
        }
        if(entry->d_type == DT_DIR) {
            numEntries = 0;
            break;
        }
        filename = entry->d_name;
        numEntries++;
        entry = readdir(dir_ptr);
    }
    closedir(dir_ptr);
    std::cout << numEntries << "\n";
    if(numEntries == 1) {
        return "/" + filename;
    } else {
        return "";
    }
}

Q_INVOKABLE QString BackEnd::activateMenuItem(const QString &link)
{
    if(link == "")
        return "menu";
    std::regex is_inode("inode[0-9]*");
    if( std::regex_match( link.toUtf8().toStdString(), is_inode) ) {
        inode = link.toUtf8().toStdString().substr(5);
        return "video";
    }
    m_filePath = m_filePath + link.toUtf8().toStdString() + "/";
    generateMenuItems();
    emit menuItemsChanged();
    return "menu";
}

Q_INVOKABLE QString BackEnd::selectMenuItem(const int link) {
    return "";
}

Q_INVOKABLE void BackEnd::previousMenu()
{
    if( m_filePath == "/games/" ) {
        adjustInputs(1);
    }
    qWarning(m_filePath.c_str());
    size_t slash_pos = m_filePath.rfind('/',m_filePath.length() - 2);
    if( m_filePath.length() > 1 ) {
        m_filePath.erase(slash_pos+1);
        generateMenuItems();
        emit menuItemsChanged();
    }
}

static inline void check_error(int status)
{
    if (status < 0) {
        printf("mpv API error: %s\n", mpv_error_string(status));
        exit(1);
    }
}

Q_INVOKABLE void BackEnd::playVideo()
{
    httplib::Client cli("hostname", 80);

    std::string video_info_uri = "/video_file/" + inode + "/info";
    auto res = cli.Get(video_info_uri.c_str());
    std::list<std::string> profiles;
    if (res && res->status == 200) {
        profiles = m_videoOptions.doAdjustment(res->body.c_str());
    } else {
        return;
    }
    adjustInputs(1);
    
    setlocale(LC_NUMERIC, "C");
    mpv_handle *ctx = mpv_create();
    if (!ctx) {
        printf("failed creating context\n");
        return;
    }

    // Enable default key bindings, so the user can actually interact with
    // the player (and e.g. close the window).
    check_error(mpv_set_option_string(ctx, "input-default-bindings", "yes"));
    mpv_set_option_string(ctx, "input-vo-keyboard", "yes");
    int val = 1;
    check_error(mpv_set_option(ctx, "osc", MPV_FORMAT_FLAG, &val));
    mpv_set_option_string(ctx, "config", "yes");
    /*std::string config_file = getenv("HOME");
    config_file += "/.config/mpv/mpv.conf";
    std::cout << config_file << "\n";
    check_error(mpv_load_config_file(ctx, config_file.c_str()));*/

    // Done setting up options.
    check_error(mpv_initialize(ctx));

    for(std::string profile: profiles) {
        std::string cmd = "apply-profile "+profile;
        check_error(mpv_command_string(ctx, cmd.c_str()));
    }

    std::string url = ROOT_PATH + "/video_file/" + inode + "/data";
    // Play this file.
    const char *cmd[] = {"loadfile",url.c_str(),NULL};
    check_error(mpv_command(ctx, cmd));

    // Let it play, and wait until the user quits.
    while (1) {
        mpv_event *event = mpv_wait_event(ctx, 10000);
        printf("event: %s\n", mpv_event_name(event->event_id));
        if (event->event_id == MPV_EVENT_SHUTDOWN || event->event_id == MPV_EVENT_IDLE)
            break;
    }

    mpv_terminate_destroy(ctx);
}

bool comparePointer(QObject* a, QObject* b) { return (*static_cast<MenuItem*>(a)) < (*static_cast<MenuItem*>(b)); }


QList<QObject*> BackEnd::menuItems()
{
    return m_menuItems;
}

void BackEnd::generateMenuItems() {
    QList<QObject*> dataList;
    std::string dir_path = ROOT_PATH + m_filePath.c_str();
    if(m_filePath == "/") {
        dataList.append(new MenuItem("TV","tv"));
        dataList.append(new MenuItem("Movies","movies"));
        dataList.append(new MenuItem("Games","games"));
    } else if (m_filePath == "/games/") {
        adjustInputs(2);
        dataList.append(new MenuItem("Press back/esc to exit games mode",""));
    } else  {
        httplib::Client cli("hostname", 80);

        auto res = cli.Get(m_filePath.c_str());
        if (res && res->status == 200) {
            auto j = json::parse(res->body.c_str());
            if(j["item_list"].is_array()) {
                for(auto& item: j["item_list"]) {
                    QString text = QString::fromStdString(item["text"].get<std::string>());
                    QString link = QString::fromStdString(item["link"].get<std::string>());
                    dataList.append(new MenuItem(text,link));
                }
            } else if(j["video_files"].is_array()) {
                for(auto& item: j["video_files"]) {
                    QString text = QString::fromStdString(item["filename"].get<std::string>());
                    QString link = QString::fromStdString("inode"+std::to_string(item["inode"].get<long>()));
                    MenuItem* mi = new MenuItem(text,link);
                    mi->setVideoFileInfo(item["info"]);
                    dataList.append(mi);
                }
            }
        } else {
            previousMenu();
        }
    }
    m_menuItems = dataList;
}

QList<QObject*> BackEnd::videoOptionsList()
{
    QList<QObject*> list;
    /*list.append(new MenuItem("Play",""));
    for(size_t i=0; i< m_videoOptions.getListOptions().size();i++) {
        list.append(m_videoOptions.getListOptions()[i]);
    }*/
    return (QList<QObject*>)list;
}


