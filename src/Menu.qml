import QtQuick 2

ListView {
    id: listView
    property string headerText: "Undefined Menu";
    function action() {
        stack.pop()
    }
    focus: true
    highlight: Rectangle { color: "brown"; radius: 2 }
    clip: true
    model: ListModel {
        ListElement {
            name: "undefined menu"
        }
    }
    delegate: Text {
        text: name
        color: "white"
        font.pointSize: appWindow.width / 45
        wrapMode: Text.WrapAnywhere
        MouseArea {
            anchors.fill: parent
            onClicked: {
                if( typeof model.action === "function" ) {
                    model.action();
                } else {
                    listView.currentIndex = index;
                    listView.action();
                }
            }
        }
        Keys.onPressed: {
            if(event.key == Qt.Key_Enter || event.key == Qt.Key_Return) {
                if( typeof model.action === "function" ) {
                    model.action();
                } else {
                    listView.currentIndex = index;
                    listView.action();
                }
                event.accepted = true;
            }
        }
    }
    Keys.onPressed: {
        if(event.key == Qt.Key_Back || event.key == Qt.Key_Escape) {
            stack.pop();
            event.accepted = true;
        }
    }
}
