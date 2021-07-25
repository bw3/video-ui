import QtQuick 2.0

Menu {
    id: menu
    headerText: "TV"
    model: ListModel { }
    Component.onCompleted: {
        var request = new XMLHttpRequest();
        request.open("GET", BackEnd.mediaDbUri + "/tv");
        request.onload = function()  {
            request.responseType = "json";
            request.response["item_list"].forEach(function (item) {
                model.append({"name": item["text"], "link": item["link"]});
            });
        }
        request.send();
    }

    function action() {
        var element = menu.model.get(menu.currentIndex);
        let uri = BackEnd.mediaDbUri + "/tv/" + element["link"];
        stack.push('TvSeasonMenu.qml', {"uri": uri, "showName": element["name"]});
    }

}
