#include "video_options.h"
#include "json.hpp"

#include <QProcess>
#include <iostream>

#define ASPECT_RATIO "Aspect Ratio"
#define REFRESH_RATE "Refresh Rate"
#define COLOR_SPACE "Color Space"
#define BW_MODE "Black+White Mode"

#define PYTHON_SCRIPT_NAME "/home/user/bin/adjust_projector.py"
//#define PYTHON_SCRIPT_NAME "/home/brad/test.py"

using json = nlohmann::json;

VideoOptions::VideoOptions() {
    m_curRefreshRate = "";
    m_curLensMemory = 0;
    m_curSettingsMemory = 0;
}

std::list<std::string> VideoOptions::doAdjustment(std::string video_info) {
    auto j = json::parse(video_info.c_str());
    std::string refresh_rate = j["fps"].get<std::string>();
    int lens_memory = j["lens_memory"].get<int>();
    if( lens_memory == 5 ) {
        lens_memory = 2; // For auto, lens memory uses the widest aspect ratio
    }
    int settings_memory = j["settings_memory"].get<int>();
    if(false) { //TODO: Black and White
        settings_memory = 10;
    }
    int color_space = j["color_space"].get<int>();
    if(m_curRefreshRate == refresh_rate) {
        refresh_rate = "-1";
    } else {
        m_curRefreshRate = refresh_rate;
    }
    if(m_curLensMemory == lens_memory) {
        lens_memory = -1;
    } else { 
        m_curLensMemory = lens_memory;
    }
    if(m_curSettingsMemory == settings_memory) {
        settings_memory = -1;
    } else {
        m_curSettingsMemory = settings_memory;
    }
    QProcess *process = new QProcess(this);
    QStringList arguments;
    arguments << PYTHON_SCRIPT_NAME;
    arguments << "3840x2160"; //resolution
    arguments << refresh_rate.c_str(); // refresh rate
    arguments << std::to_string( lens_memory ).c_str(); // lens memory (single digit)
    if(settings_memory == 10) {
        arguments << "A";
    } else {
        arguments << std::to_string( settings_memory ).c_str(); // settings memory (single digit)
    }
    arguments << std::to_string( color_space ).c_str(); // color space (single digit)
    process->setProcessChannelMode(QProcess::MergedChannels);
    process->setStandardOutputFile("adjust_projector.log");
    process->start("/usr/bin/python", arguments);
    process->waitForFinished(-1);
    delete process;
    std::list<std::string> profiles;
    profiles.push_back("default");
    for(json::iterator it = j["profile"].begin();it !=j["profile"].end();it++) {
        profiles.push_back(it->get<std::string>());
        std::cout << it->get<std::string>() << "\n";
    }
    return profiles;
}

/*std::string VideoOptions::getMpvArguments() const {
    std::string strArg = "--profile=";
    strArg += "refresh-" + getMenuOption(REFRESH_RATE)->getSelectedString();
    strArg += ",aspect-" + getMenuOption(ASPECT_RATIO)->getSelectedString();
    strArg += ",colorspace-" + getMenuOption(COLOR_SPACE)->getSelectedString();
    return strArg;
}*/

bool VideoOptions::isAdjustmentInstant() const {
    return false;
}
