import QtQuick 2.0
import Process 1.0
import Mpv 1.0

Item {
    property string uri;
    property string headerText: "Adjusting ..."

    Mpv {
        id: mpv
        onIsPausedChanged: {
            print(mpv.isPaused);
        }
    }

    Timer {
        id: timer
        interval: 1
        repeat: false
        onTriggered: {
        var request = new XMLHttpRequest();
            request.open("GET", uri + "/info");
            request.onload = function()  {
                print(request.response)
                request.responseType = "json";
                //"color_space":1,"filesize":"5.57 GB","fps":"23.976","lens_memory":1
                adjust.resolution = "3840x2160";
                adjust.refreshRate = request.response["fps"];
                adjust.lensMemory = request.response["lens_memory"];
                adjust.settingsMemory = request.response["settings_memory"];
                adjust.colorSpace = request.response["color_space"];
                adjust.input = 1
                adjust.running = true;
                appWindow.visible = false;
                mpv.init();
                request.response["profile"].forEach(function (item) {
                    mpv.cmd("apply-profile " + item);
                });
                mpv.cmd("loadfile " + uri +"/data");
                mpv.waitForExit();
                appWindow.visible = true;
                adjust.colorSpace = 1;
                adjust.running = true;
                stack.pop();
            }
            request.send();
        }
    }

    Component.onCompleted: {
        timer.running = true;
    }

    
}
