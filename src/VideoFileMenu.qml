import QtQuick 2.0

Menu {
    id: menu
    property string uri;
    model: ListModel { }
    Component.onCompleted: {
        var request = new XMLHttpRequest();
        request.open("GET", uri);
        request.onload = function()  {
            print(request.response)
            request.responseType = "json";
            headerText = request.response["header"];
            request.response["video_files"].forEach(function (item) {
                item["name"] = item["filename"];
                model.append(item);
            });
        }
        request.send();
    }

    function action() {
        var element = menu.model.get(menu.currentIndex);
        let uri = BackEnd.mediaDbUri + "/video_file/" + element["inode"];
        print(uri);
        stack.push('PlayVideo.qml', {"uri": uri});
    }

}
