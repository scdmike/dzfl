import QtQuick 2.13

Grid {
    width: 380
    height: 22
    clip: true
    property string text: ""
    property string color: "#ffffff"
    property int style: Text.Raised
    property int horizontalAlignment: Text.AlignLeft
    property int verticalAlignment: Text.AlignVCenter
    property int fontSize: 15
    property string fontFamily: "黑体"
    property bool fontBold: true
    property string roll: "true"

    Text {
        objectName: "msg"
        color: parent.color
        height: parent.height
        style: parent.style
        horizontalAlignment: parent.horizontalAlignment
        verticalAlignment: Text.AlignVCenter
        font.pixelSize: parent.fontSize
        font.family : parent.fontFamily
        font.bold: parent.fontBold
    }

    Text {
        objectName: "msgBak"
        color: parent.color
        height: parent.height
        style: parent.style
        horizontalAlignment: parent.horizontalAlignment
        verticalAlignment: Text.AlignVCenter
        font.pixelSize: parent.fontSize
        font.family : parent.fontFamily
        font.bold: parent.fontBold
    }

    Text {
        objectName: "msgRoll"
        text: roll
        visible: false
    }
}
