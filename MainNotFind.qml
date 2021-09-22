import QtQuick 2.3
import QtMultimedia 5.0

Item {
    id: window
    visible: true
    width: 320
    height: 240

    MouseArea {
        anchors.fill: parent
        onClicked: Qt.quit();
    }

    Text {
        objectName: "IntroPage"
        anchors.fill: parent
        color: "#ff0000"
        text: "未找到评价qml界面文件"
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }
}
