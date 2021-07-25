import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.11
import QtQuick.Window 2.2 
//import src.backend 1.0

Window
{
    id: appWindow
    color: "black"
//    BackEnd {
//        id: backend
//    }
//    width: 640
//    height: 480
//
//    ColumnLayout {
//        visible: false
//        ListView {
//            id: mainMenu
//            focus: true
//            highlight: Rectangle { color: "blue"; radius: 5 }
//            highlightMoveDuration: 50
//            highlightResizeDuration: 50
//            model: backend.menuItems
//            delegate: Text {
//                text: model.modelData.html
//                color: "white"
//                font.pointSize: appWindow.width / 50
//                width: Math.min(mainMenu.width, implicitWidth)
//                wrapMode: Text.WrapAnywhere
//                Keys.onPressed: {
//                    if(event.key == Qt.Key_Enter || event.key == Qt.Key_Return) {
//                        if(backend.activateMenuItem(this.text) == "video") {
//                            stackView.push(videoOptions)
//                            videoOptions.forceActiveFocus()
//                        }
//                        event.accepted = true;
//                    } else if(event.key == Qt.Key_Back || event.key == Qt.Key_Escape) {
//                        backend.previousMenu()
//                        event.accepted = true;
//                    }
//                }
//            }
//        }
//
//        ListView {
//            id: videoOptions
//            focus: true
//            highlight: Rectangle { color: "blue"; radius: 5 }
//            highlightMoveDuration: 50
//            highlightResizeDuration: 50
//            model: backend.videoOptionsList
//            Layout.fillHeight: true
//            delegate: Text {
//                text: model.modelData.html
//                color: "white"
//                font.pointSize: appWindow.width / 50
//                width: Math.min(videoOptions.width, implicitWidth)
//                wrapMode: Text.WordWrap
//                Keys.onPressed: {
//                    if(event.key == Qt.Key_Enter || event.key == Qt.Key_Return) {
//                        appWindow.visible = false
//                        backend.playVideo()
//                        appWindow.visible = true
//                    } else if(event.key == Qt.Key_Back || event.key == Qt.Key_Escape) {
//                        backend.previousMenu()
//                        stackView.pop()
//                        mainMenu.forceActiveFocus()
//                        event.accepted = true;
//                    } else if(event.key == Qt.Key_Left) {
//                        this.ListView.view.model[this.ListView.view.currentIndex].decrement();
//                        event.accepted = true;
//                    } else if(event.key == Qt.Key_Right) {
//                        this.ListView.view.model[this.ListView.view.currentIndex].increment();
//                        event.accepted = true;
//                    }
//                }
//            }
//        }
/*        RowLayout {
            id: videoOptions
            Text {
                text: "Play"
                font.pointSize: 100
                color: "white"
            }
            Keys.onPressed: {
                if(event.key == Qt.Key_Enter || event.key == Qt.Key_Return) {
                    appWindow.visible = false
                    backend.playVideo()
                    appWindow.visible = true
                    
                } else if(event.key == Qt.Key_Back || event.key == Qt.Key_Escape) {
                    backend.previousMenu()
                    stackView.pop()
                    mainMenu.forceActiveFocus()
                    event.accepted = true;
                }
            }
        }*/
//    }
//   ThemedMenuView {
//       id: mainMenu
//       model: backend.menuItems
//   }

    
    property real aspectRatio: 2.08;
    visible: true
//    visibility: Window.FullScreen
    title: qsTr("Minimal Qml")
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
