#ifndef MPV_H
#define MPV_H

#include <mpv/client.h>
#include <QObject>

class Mpv : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isPaused READ isPaused NOTIFY isPausedChanged)
public:
    explicit Mpv(QObject *parent = nullptr) {
    }

    Q_INVOKABLE void init() {
        setlocale(LC_NUMERIC, "C");
        m_handle = mpv_create();
        mpv_set_option_string(m_handle, "input-default-bindings", "yes");
        mpv_set_option_string(m_handle, "input-vo-keyboard", "yes");
        int val = 1;
        mpv_set_option(m_handle, "osc", MPV_FORMAT_FLAG, &val);
        mpv_set_option_string(m_handle, "config", "yes");
        mpv_initialize(m_handle);
        mpv_observe_property(m_handle, 0, "pause", MPV_FORMAT_FLAG);
    }

    Q_INVOKABLE void cmd(QString cmd) {
        mpv_command_string(m_handle, cmd.toStdString().c_str());
    }

    bool isPaused() { return m_paused; }

    Q_INVOKABLE void waitForExit() {
        while (1) {
            mpv_event *event = mpv_wait_event(m_handle, 10000);
            if (event->event_id == MPV_EVENT_SHUTDOWN || event->event_id == MPV_EVENT_IDLE) {
                break;
            } else if (event->event_id == MPV_EVENT_PROPERTY_CHANGE) {
                mpv_event_property* event_property = reinterpret_cast<mpv_event_property*>(event->data);
                if(strcmp(event_property->name,"pause") == 0 && event_property->format == MPV_FORMAT_FLAG) {
                    int flag = * reinterpret_cast<int*> (event_property->data);
                    m_paused = (flag == 1);
                    emit isPausedChanged();
                }
            }
        }
        mpv_terminate_destroy(m_handle);
    }
    
signals:
    void isPausedChanged();
private:
    mpv_handle* m_handle;
    bool m_paused;
};

#endif // MPV_H
