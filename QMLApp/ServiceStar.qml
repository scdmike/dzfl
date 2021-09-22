import QtQuick 2.3

Item {
    width: 300
    height: 49

    Text {
        x: 0
        y: 13
        color: "#0c71c7"
        text: "月度服务之星"
        style: Text.Sunken
        font.bold: true
        font.family: "黑体"
        font.pixelSize: 22
    }

    Grid {
        id: star
        x: 141
        y: 0
        width: 159
        height: 49
        columns: 5

        Item {
            objectName: "month1"
            x: 36
            y: 19
            width: 31
            height: 49
            visible: false

            Image {
                x: 6
                y: 6
                width: 20
                height: 20
                anchors.horizontalCenterOffset: 0
                anchors.horizontalCenter: parent.horizontalCenter
                source: "images/star.png"
            }

            Text {
                objectName: "tbMonth1"
                y: 31
                width: 31
                text: "月份"
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 12
            }
        }

        Item {
            objectName: "month2"
            x: 36
            y: 19
            width: 32
            height: 49
            visible: false

            Image {
                x: 6
                y: 6
                width: 20
                height: 20
                anchors.horizontalCenterOffset: 0
                anchors.horizontalCenter: parent.horizontalCenter
                source: "images/star.png"
            }

            Text {
                objectName: "tbMonth2"
                y: 31
                width: 31
                text: "月份"
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 12
            }
        }

        Item {
            objectName: "month3"
            x: 36
            y: 19
            width: 32
            height: 49
            visible: false

            Image {
                x: 6
                y: 6
                width: 20
                height: 20
                anchors.horizontalCenterOffset: 0
                anchors.horizontalCenter: parent.horizontalCenter
                source: "images/star.png"
            }

            Text {
                objectName: "tbMonth3"
                y: 31
                width: 31
                text: "月份"
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 12
            }
        }

        Item {
            objectName: "month4"
            x: 36
            y: 19
            width: 32
            height: 49
            visible: false

            Image {
                x: 6
                y: 6
                width: 20
                height: 20
                anchors.horizontalCenterOffset: 0
                anchors.horizontalCenter: parent.horizontalCenter
                source: "images/star.png"
            }

            Text {
                objectName: "tbMonth4"
                y: 31
                width: 31
                text: "月份"
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 12
            }
        }

        Item {
            objectName: "month5"
            x: 36
            y: 19
            width: 32
            height: 49
            visible: false

            Image {
                x: 6
                y: 6
                width: 20
                height: 20
                anchors.horizontalCenterOffset: 0
                anchors.horizontalCenter: parent.horizontalCenter
                source: "images/star.png"
            }

            Text {
                objectName: "tbMonth5"
                y: 31
                width: 31
                text: "月份"
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 12
            }
        }
    }
}
