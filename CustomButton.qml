import QtQuick 2.3

Rectangle {
    width: 75
    height: 59
    radius: 1
    property string btncolor:"#40abfd"
    property string btnTextcolor:"#ffffff"
    property string btnBordercolor:"#7574cc"
    property int btnTextSize:16
    gradient: Gradient {
        GradientStop {
            position: 0
            color: btncolor
        }

        GradientStop {
            position: 0.520
            color: btncolor
        }

        GradientStop {
            position: 1
            color: btncolor
        }
    }

    signal buttonClick()
    property string label: qsTr("按钮")

    border.color: btnBordercolor

    Text {
        anchors.centerIn: parent
        text: parent.label
        style: Text.Normal
        font.bold: true
        //font.family: qsTr("宋体")
        font.pixelSize: btnTextSize
        color:btnTextcolor
    }

    MouseArea {
        enabled: parent.enabled
        anchors.fill: parent
        onClicked: buttonClick()
    }

    Rectangle {
        color: "#1c1b1b"
        opacity: parent.enabled ? 0 : 0.8
        anchors.fill: parent
    }

}

