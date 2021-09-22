import QtQuick 2.3

Item {
    width: 572
    height: 370

    Image {

        width: parent.width
        height: parent.height
        source: "images/zaigang.png"

    }



    Text {
        x: 2215
        y: 33
        width: 341
        height: 39
        color: "#165da3"
        text: "办理类型："
        font.family: "黑体"
        font.bold: true
        style: Text.Sunken
        font.pixelSize: 32
    }

    Grid {
        x: 2241
        y: 73
        width: 342
        height: 194
        flow: Grid.TopToBottom
        columns: 1
        rows: 6
        objectName: "project"
        clip: true
        ScrollMessagePage {
            x: 64
            y: 39
            width: 342
            height: 32
            color: "#165da3"
            objectName: "ProjectNameGridItem0"
            text: "综合业务"
            style: Text.Raised
            fontFamily: "黑体"
            fontSize: 32

            MouseArea {
                //anchors.fill: parent
                z: 2
                enabled: true
                onClicked: ServiceInfo.approvalClick(0)
            }
        }
        ScrollMessagePage {
            x: 64
            y: 39
            width: 342
            height: 32
            objectName: "ProjectNameGridItem1"
            color: "#165da3"
            style: Text.Raised
            fontFamily: "黑体"
            fontSize: 32

            MouseArea {
                //anchors.fill: parent
                z: 2
                enabled: true
                onClicked: ServiceInfo.approvalClick(1)
            }
        }
        ScrollMessagePage {
            x: 64
            y: 39
            width: 342
            height: 32
            objectName: "ProjectNameGridItem2"
            color: "#165da3"
            style: Text.Raised
            fontFamily: "黑体"
            fontSize: 32

            MouseArea {
                //anchors.fill: parent
                z: 2
                enabled: true
                onClicked: ServiceInfo.approvalClick(2)
            }
        }
        ScrollMessagePage {
            x: 64
            y: 39
            width: 342
            height: 32
            objectName: "ProjectNameGridItem3"
            color: "#165da3"
            style: Text.Raised
            fontFamily: "黑体"
            fontSize: 32

            MouseArea {
                //anchors.fill: parent
                z: 2
                enabled: true
                onClicked: ServiceInfo.approvalClick(3)
            }
        }
        ScrollMessagePage {
            x: 64
            y: 39
            width: 342
            height: 32
            objectName: "ProjectNameGridItem4"
            color: "#165da3"
            style: Text.Raised
            fontFamily: "黑体"
            fontSize: 32

            MouseArea {
                //anchors.fill: parent
                z: 2
                enabled: true
                onClicked: ServiceInfo.approvalClick(4)
            }
        }
        ScrollMessagePage {
            x: 64
            y: 39
            width: 342
            height: 32
            objectName: "ProjectNameGridItem5"
            color: "#165da3"
            style: Text.Raised
            fontFamily: "黑体"
            fontSize: 32

            MouseArea {
                //anchors.fill: parent
                z: 2
                enabled: true
                onClicked: ServiceInfo.approvalClick(5)
            }
        }
    }

    Image {
        x: 2184
        y: 141
        width: 54
        height: 85
        source: "images/xzuobutton.png"
        MouseArea {
            width: parent.width
            height: parent.height
            onClicked: ServiceInfo.projectPageUp()
            objectName: "btnProjectPageUp"
            onEnabledChanged: parent.opacity = enabled ? 1.0 : 0.2
        }
    }

    Image {
        x: 2586
        y: 141
        width: 54
        height: 85
        source: "images/xyaobutton.png"
        MouseArea {
            width: parent.width
            height: parent.height
            onClicked: ServiceInfo.projectPageDown()
            objectName: "btnProjectPageDown"
            onEnabledChanged: parent.opacity = enabled ? 1.0 : 0.2
        }
    }
}
