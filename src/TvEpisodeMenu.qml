import QtQuick 2.0

Menu {
    id: menu
    property string uri;
    property string showName;
    property string season;
    headerText: showName + " - Season " + season
    model: ListModel { }
    Component.onCompleted: {
        var request = new XMLHttpRequest();
        print(showName);
        request.open("GET", uri);
        print(uri)
        request.onload = function()  {
            print(request.response)
            request.responseType = "json";
            request.response["item_list"].forEach(function (item) {
                model.append({"name": item["text"], "link": item["link"]});
            });
        }
        request.send();
    }

    function action() {
        var element = menu.model.get(menu.currentIndex);
        let uri = menu.uri + "/" + element["link"];
        stack.push('VideoFileMenu.qml', {"uri": uri});
    }

}
