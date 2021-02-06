// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Item
{
    id : label

    property alias str: labelText.text
    property color tint: "transparent"
    signal clicked

    width: labelText.width + 70 ; height: labelText.height + 18

    BorderImage {
        anchors { fill: label; leftMargin: -6; topMargin: -6; rightMargin: -8; bottomMargin: -8 }
        source: 'images/box-shadow.png'; smooth: true
        border.left: 10; border.top: 10; border.right: 10; border.bottom: 10
    }

    Image { anchors.fill: parent; source: "images/cardboard.png"; smooth: true }

    Rectangle {
        anchors.fill: label; color: label.tint; visible: label.tint != ""
        opacity: 0.25; smooth: true
    }

    Text { id: labelText; font.pixelSize: 15; anchors.centerIn: parent; smooth: true }

    MouseArea {
        anchors { fill: parent; leftMargin: -20; topMargin: -20; rightMargin: -20; bottomMargin: -20 }
        onClicked: label.clicked()
    }

}
