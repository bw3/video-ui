import QtQuick 2.0
import Process 1.0

Menu {
    id: menu
    property string searchQuery;
    headerText: "Youtube: " + searchQuery
    model: ListModel { }
    Component.onCompleted: {
        let python_code = 'from youtube_search import YoutubeSearch\nimport sys\nresults = YoutubeSearch(sys.argv[1], max_results=10).to_json()\nprint(results)'
        my_proc.start('videoui_venv/bin/python',['-c', python_code, searchQuery]);
        my_proc.waitForFinished();
        var result = JSON.parse(my_proc.readAllStandardOutput());
        result["videos"].forEach(function (item) {
            model.append({"name": item["title"], "url_suffix": item["url_suffix"]});
        });
    }

    function action() {
        var element = menu.model.get(menu.currentIndex);
        let uri = "https://www.youtube.com" + element["url_suffix"];
        stack.push('PlayVideo.qml', {"uri": uri, "getInfo":false});
    }

    Process {
        id: my_proc
    }


}

