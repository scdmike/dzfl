import QtQuick 2.3

Rectangle {
    id:comboBox
    property alias selectedItem: chosenItemText.text
    property alias selectedIndex: listView.currentIndex
    property string selectedItemID: ""
    property int   itemHeight: 40
    property int   displaySize: 3
    signal comboClicked
    signal onSelectedIndexChanged

    width: 410
    smooth: true
    height: 40

    Rectangle {
        id: dropDown
        width: comboBox.width
        clip: true
        radius: 4
        border.color: "#51a8f9"
        anchors.top: chosenItem.bottom
        color: "#e6e1e1"

        ListView {
            id: listView
            height: itemHeight * displaySize + 3
            width: dropDown.width - 4
            anchors.horizontalCenter: parent.horizontalCenter
            currentIndex: 0
            model: ListModel { id: listModel }

            delegate: Item {
                width: listView.width
                height: comboBox.itemHeight
                Rectangle {
                    id: mouseMoveHighLight
                    width: listView.width
                    height: comboBox.itemHeight
                    color: "green"
                    opacity: 0
                    radius: 4
                }
                Text {
                    text: itemText
                    //anchors.top: parent.top
                    anchors.left: parent.left
                    anchors.fill: parent;
                    //anchors.centerIn: parent;
                    anchors.verticalCenter: parent.verticalCenter
                    //anchors.margins: 5
                    font.pointSize: 8
                    wrapMode: Text.WordWrap
                    //horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
                MouseArea {
                    anchors.fill: parent;
                    hoverEnabled: true
                    onClicked: {
                        comboBox.state = "";
                        var preSelection = chosenItemText.text;
                        chosenItemText.text = itemText;
                        if(chosenItemText.text != preSelection) {
                            comboBox.comboClicked();
                        }
                        var change = listView.currentIndex != index;
                        listView.currentIndex = index;
                        selectedItemID = itemID;

                        if(change) comboBox.onSelectedIndexChanged();
                    }
                    onEntered: mouseMoveHighLight.opacity = 0.5;
                    onExited: mouseMoveHighLight.opacity = 0;
                }
            }
            highlight: Rectangle {
                width: listView.width
                height: comboBox.itemHeight
                color: "green"
                radius: 4
            }
        }
    }
    Rectangle {
        id: chosenItem
        radius: 4
        border.color: "#51a8f9"
        width: parent.width
        height: comboBox.itemHeight
        color: "#dbf5e3"
        clip: true
        smooth: true
        Text {
            //anchors.top: parent.top
            anchors.left: parent.left
            //anchors.margins: 0
            anchors.verticalCenter: parent.verticalCenter
            anchors.fill: parent;
            //anchors.centerIn: parent;
            id: chosenItemText
            //font.family: "仿宋"
            font.pointSize: 8
            smooth: true
            wrapMode: Text.WordWrap
            //horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
        MouseArea {
            anchors.fill: parent
            onClicked: comboBox.state = comboBox.state === "dropDown" ? "" : "dropDown";
        }
    }

    states: State {
        name: "dropDown";
        PropertyChanges {
            target: dropDown
            height: listModel.count * comboBox.itemHeight + 5 > comboBox.itemHeight * displaySize + 5 ?
                        comboBox.itemHeight * displaySize + 5 : listModel.count * comboBox.itemHeight + 5
                        color: "#f1e8e8"
                        border.width: 2
                        border.color: "#8cf9b6"
        }
    }
    transitions: Transition {
        NumberAnimation {
            target: dropDown
            properties: "height"
            easing.type: Easing.OutExpo
            duration: 400
        }
    }

    function setComboBoxValue(value, key, show) {
        listModel.clear();

        for (var i = 0; i < value.length; i++) {
            listModel.append({ "itemID" : value[i][key], "itemText" : value[i][show] });
        }

        selectedIndex = value.length > 0 ? 0 : -1;
        chosenItemText.text = value.length > 0 ? value[0][show] : "";
        selectedItemID = value.length > 0 ? value[0][key] : "";
        comboBox.state = "";
    }
}
