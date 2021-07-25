import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.11
import QtQuick.Window 2.2 
//import src.backend 1.0

Window
{
    id: appWindow
    color: "black"
    
    property real aspectRatio: 2.08;
    visible: true
    visibility: Window.FullScreen
    title: qsTr("Minimal Qml")
    Adjust {
        id: adjust
    }
    Item {
        id: topSpacer
        anchors.top: parent.top
        height: Math.max((appWindow.height - (appWindow.width / aspectRatio)) / 2,0)
    }
    Text {
        id: header
        text: stack.currentItem.headerText
        color: "white"
        font.pointSize: appWindow.width/25
        anchors.top: topSpacer.bottom
    }
    StackView {
        id: stack
        focus: true
        initialItem: RootMenu {}
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: header.bottom
        anchors.bottom: bottomSpacer.top
    }
    Item {
        id: bottomSpacer
        anchors.bottom: parent.bottom
        height: Math.max((appWindow.height - (appWindow.width / aspectRatio)) / 2,0)
    }
}
