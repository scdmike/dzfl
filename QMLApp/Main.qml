import QtQuick 2.3
Item {
    visible: true
    property real sx: 1
    property real sy: 1
    width: 1280*sx
    height: 800*sy
    transformOrigin: Item.TopLeft

    scale: 1

    Intro {
        visible: true
        objectName: "IntroPage"
        transform: Scale { xScale: sx; yScale: sy}
    }

    Frame {
        x: 0
        y: 0
        objectName: "FramePage"
        visible: false
        transform: Scale { xScale: sx; yScale: sy}
    }
}
