#ifndef VIDEO_OPTIONS_H
#define VIDEO_OPTIONS_H

#include "menu_option.h"

#include <QObject>

class VideoOptions : public QObject {
public:
    VideoOptions();
    std::list<std::string> doAdjustment(std::string);
    bool isAdjustmentInstant() const;
private:

    std::string m_curRefreshRate;
    int m_curLensMemory;
    int m_curSettingsMemory;
};

#endif //VIDEO_OPTIONS_H
