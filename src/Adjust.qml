import QtQuick 2.0
import Process 1.0

Item {
    property int lensMemory: -1
    property int colorSpace: -1
    property int settingsMemory: -1
    property string resolution: ""
    property real   refreshRate: -1
    property int input: -1
    property bool running: false
    property int _lensMemory: -1
    property string _resolution: ""
    property real   _refreshRate: -1

    onRunningChanged: {
        if(!running) {
            return;
        }
        var res = resolution
        var rate = refreshRate
        var lens = lensMemory
        if( _resolution == resolution ) {
            res = -1;
        } else {
            _resolution = resolution;
        }
        if( _refreshRate == refreshRate ) {
            rate = -1;
        } else {
            _refreshRate = refreshRate;
        }
        if( _lensMemory == lensMemory ) {
            lens = -1;
        } else {
            _lensMemory = lensMemory;
        }
        adjust_proj.start(".config/video-ui/adjust_projector",[ res, rate, lens, settingsMemory, colorSpace ]);
        adjust_inputs.start(".config/video-ui/adjust_inputs", [ input ]);
        adjust_proj.waitForFinished();
        adjust_inputs.waitForFinished();
        running = false;
    }

    Process {
        id: adjust_proj
    }

    Process {
        id: adjust_inputs
    }

}
