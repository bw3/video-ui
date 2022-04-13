import QtQuick 2.0
import Process 1.0

Item {

    property string headerText: "Youtube: Updating ...";
    //focus: true

    Component.onCompleted: {
        timer.running = true;
    }

    Timer {
        id: timer
        interval: 1
        repeat: false
        onTriggered: {
            my_proc.start('virtualenv',['.cache/videouir/venv']);
            my_proc.waitForFinished();
            my_proc.start('videoui_venv/bin/pip',['install', 'youtube-search']);
            my_proc.waitForFinished();
            my_proc.start('videoui_venv/bin/pip',['install', 'youtube_dl']);
            my_proc.waitForFinished();
            headerText = 'Youtube';
            search_query.focus = true;
        }
    }

    Keys.onPressed: {
        if(event.key == Qt.Key_Back || event.key == Qt.Key_Escape) {
            stack.pop();
            event.accepted = true;
        }
    }

    Process {
        id: my_proc
    }

    TextInput {
        id: search_query
        text: ""
        color: "red"
        focus: true
        //anchors.centerIn: parent
        font.pixelSize: appWindow.width / 40
//        width: 180; 
//        height: 28
        onAccepted: {
            stack.push('YoutubeResults.qml', {"searchQuery": search_query.text});
        }
    }

}

