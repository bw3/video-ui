import QtQuick 2.0

Menu {
    headerText: "Main Menu"
    model: ListModel {
        ListElement {
            name: "TV"
            action: function action() {
                stack.push('TvShowMenu.qml');
            }
        }
        ListElement {
            name: "Movies"
            action: function action() {
                stack.push('MovieMenu.qml');
            }
        }
        ListElement {
            name: "Games"
            action: function action() {
                stack.push('PlayGames.qml');
            }
        }
        ListElement {
            name: "Youtube"
            action: function action() {
                stack.push('Youtube.qml');
            }
        }
    }
}
