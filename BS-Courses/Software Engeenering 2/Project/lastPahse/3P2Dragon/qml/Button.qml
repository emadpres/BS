// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Rectangle {
    id : button

    property alias str: labelText.text
    property color tint: "transparent"
    property bool addMode: false
    signal clicked

    width: labelText.width + 70 ; height: labelText.height + 18


    BorderImage {
        anchors { fill: button; leftMargin: -6; topMargin: -6; rightMargin: -8; bottomMargin: -8 }
        source: 'images/box-shadow.png'; smooth: true
        border.left: 10; border.top: 10; border.right: 10; border.bottom: 10

        transform : Scale
        {
        id : scalceT1
        origin.x : button.width/2
        origin.y : button.height/2
        xScale : 1
        yScale : 1


    }
}

Image {
    scale: 1
    anchors.fill: parent; source: "images/cardboard.png"; smooth: true
    transform : Scale
    {
    id : scalceT
    origin.x : button.width/2
    origin.y : button.height/2
    xScale : 1
    yScale : 1


}
}

Rectangle {
    anchors.fill: button; color: button.tint; visible: button.tint != ""
    opacity: 0.25; smooth: true
}

Text { id: labelText; font.pixelSize: 15; anchors.centerIn: parent; smooth: true }

MouseArea {
    id : mouseArea
    anchors { fill: parent; leftMargin: 0; topMargin: 0; rightMargin: 0; bottomMargin: 0 }
    onClicked:
    {
        addMode = !addMode
        console.debug( "a",addMode)
        browseFile.text = ""
        browseRep.text = ""
        name.text = ""
		type.text = ""
    }
}

Text
{
    id : browseFileLable
    x: -34
    y: 2

    text : "FileLocation"
    opacity : 0
}

Rectangle
{
    id : rec_browseFile
    width: browseFile.width + 2
    height: browseFile.height +2
    x: 42
    y: 2
    radius: 5
    opacity : 0

    smooth: true

    TextInput
    {
        id : browseFile
        x: 0
        y: 0
        width: 99
        height: 13
        text: qsTr("test")
        selectionColor: "#ecdd67"
        selectedTextColor: "#3740c0"

    }
}
Text
{
    id : browseRepLable
    x: -30
    y: 20
    text : "File rep:"

    opacity : 0
}

Rectangle
{
    id : rec_browseRep
    x: 42
    y: 20

    width: browseRep.width + 2
    height: browseRep.height +2
    radius: 5

    opacity : 0

     smooth: true
    TextInput
    {
        id : browseRep
        x: 0
        y: 0
        width: 99
        height: 13
        selectionColor: "#ecdd67"
        selectedTextColor: "#3740c0"
        text : "test rep"


    }

}


Rectangle
{
    id : rec_name
    width: browseFile.width + 2
    height: browseFile.height +2
    x: 42
    y: -18
    radius: 5
    opacity : 0

     smooth: true
    TextInput
    {
        id : name
        x: 0
        y: 0
        width: 99
        height: 13
        text: qsTr("name")
        selectionColor: "#ecdd67"
        selectedTextColor: "#3740c0"

    }
}
Text
{
    id : nameLabel
    x: -34
    y: -18
    text : "projectName:"

    opacity : 0
}

/// new Type

Rectangle
{
    id : rec_type
    width: browseFile.width + 2
    height: browseFile.height +2
    x: 0
    y: 37
    radius: 5
    opacity : 0

     smooth: true
    TextInput
    {
        id : type
        x: 0
        y: 0
        width: 99
        height: 13
        text: qsTr("name")
        selectionColor: "#ecdd67"
        selectedTextColor: "#3740c0"

    }
}
Text
{
    id : typeLabel
    x: -34
    y: 37
    text : "type:"

    opacity : 0
}

// end new Type

Image
{
    id : img
    x: 120
    y: 33
    width: 23
    height: 24
    source: "add_pic.png"

    opacity: 0

    MouseArea
    {
        id : mouseArea2
        anchors.fill : img

        onClicked:
        {
            console.debug("w")
            addMode = false
            mainPage.addProject(name.text.toString(),browseFile.text,type.text,browseRep.text)
        }
    }
}

states: [State {
    when: button.addMode
    name: "addMode"

    PropertyChanges {
        target: labelText
        opacity : 0
    }
    PropertyChanges {
        target: browseFileLable
        opacity : 1
    }
    PropertyChanges {
        target: rec_browseFile
        opacity : 1
    }
    PropertyChanges {
        target: nameLabel
        opacity : 1
    }
    PropertyChanges {
        target: browseRepLable
        opacity : 1
    }
    PropertyChanges {
        target: rec_browseRep
        opacity : 1
    }
    PropertyChanges {
        target: rec_name
        opacity : 1
    }
	PropertyChanges {
        target: rec_type
        opacity : 1
    }
	PropertyChanges {
        target: typeLabel
        opacity : 1
    }
    PropertyChanges {
        target: img
        opacity : 1
    }
    PropertyChanges {
        target: scalceT
        xScale : 2
        yScale : 2
    }
    PropertyChanges {
        target: scalceT1
        xScale : 2
        yScale : 2
    }
}
]

transitions:[ Transition {
    reversible: true
    from : "*"
    to: "addMode"
    SequentialAnimation
    {

        NumberAnimation { target: labelText; property: "opacity"; duration: 10; easing.type: Easing.InOutQuad }
        ParallelAnimation
        {
            NumberAnimation { target: scalceT; property: "xScale"; duration: 700 }
            NumberAnimation { target: scalceT; property: "yScale"; duration: 700 }
            NumberAnimation { target: scalceT1; property: "xScale"; duration: 700 }
            NumberAnimation { target: scalceT1; property: "yScale"; duration: 700 }
        }
        ParallelAnimation
        {

            NumberAnimation {target: browseFileLable ; property: "opacity" ; duration: 1200}
            NumberAnimation {target: browseRepLable ; property: "opacity" ; duration: 1200}
            NumberAnimation {target: nameLabel ; property: "opacity" ; duration: 1200}
            NumberAnimation {target: rec_browseRep ; property: "opacity" ; duration: 1200}
            NumberAnimation {target: rec_browseFile ; property: "opacity" ; duration: 1200}
            NumberAnimation {target: rec_name ; property: "opacity" ; duration: 1200}
            NumberAnimation {target: img ; property: "opacity" ; duration: 1200}
			NumberAnimation {target: rec_type ; property: "opacity" ; duration: 1200}
			NumberAnimation {target: typeLabel ; property: "opacity" ; duration: 1200}
        }


    }
}
]

}
