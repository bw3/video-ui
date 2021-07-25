import QtQuick 2.0
import Process 1.0

Item {

    property string headerText: "Games";

    Process {
        id: adjust_inputs
    }


    Component.onCompleted: {
        adjust_inputs.start(".config/video-ui/adjust_inputs", ["2"]);
    }

    Keys.onPressed: {
        if(event.key == Qt.Key_Back || event.key == Qt.Key_Escape) {
            stack.pop();
            adjust_inputs.waitForFinished();
            adjust_inputs.start(".config/video-ui/adjust_inputs", ["2"]);
            adjust_inputs.waitForFinished();
            event.accepted = true;
        }
    }

}
