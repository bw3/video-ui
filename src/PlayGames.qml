import QtQuick 2.0
import Process 1.0

Item {

    property string headerText: "Games";

    Component.onCompleted: {
        adjust.input = 2;
        adjust.running = true;
    }

    Keys.onPressed: {
        if(event.key == Qt.Key_Back || event.key == Qt.Key_Escape) {
            stack.pop();
            adjust.input = 1;
            adjust.running = true;
            event.accepted = true;
        }
    }

}
