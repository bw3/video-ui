import QtQuick 2.0
import Process 1.0
import Mpv 1.0

Item {
    property string uri;
    property string headerText: adjust_proj.isFinished;

    Process {
        id: adjust_proj
    }

    Process {
        id: adjust_inputs
    }

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
                let res = "3840x2160";
                let rate = request.response["fps"];
                let lens_mem = request.response["lens_memory"];
                let settings_mem = lens_mem;
                let color_space = request.response["color_space"];               
                adjust_proj.start(".config/video-ui/adjust_projector",[ res, rate, lens_mem, settings_mem, color_space ]);
                adjust_inputs.start(".config/video-ui/adjust_inputs", ["1"]);
                adjust_proj.waitForFinished();
                adjust_inputs.waitForFinished();
                appWindow.visible = false;
                mpv.init();
                request.response["profile"].forEach(function (item) {
                    mpv.cmd("apply-profile " + item);
                });
                mpv.cmd("loadfile " + uri +"/data");
                mpv.waitForExit();
                appWindow.visible = true;
                stack.pop();
            }
            request.send();
        }
    }

    Component.onCompleted: {
        timer.running = true;
    }

    
}
