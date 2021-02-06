// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Component {
     Item {
         property variant stickies
         //property variant notes: ["dfsfsdf","fsdfsdsdf"]

         function add()
         {
             notes = ["alireza"]
         }

         id: page
         width: ListView.view.width+40; height: ListView.view.height

         Image {
             source: "cork.jpg"
             width: page.ListView.view.width
             height: page.ListView.view.height
             fillMode: Image.PreserveAspectCrop
             clip: true
         }

         MouseArea {
             anchors.fill: parent
             onClicked: page.focus = false;
         }

         Text {
             text: name; x: 15; y: 8; height: 40; width: 370
             font.pixelSize: 18; font.bold: true; color: "white"
             style: Text.Outline; styleColor: "black"
         }

         Repeater {
             model: notes
             Item {
                 id: stickyPage

                 property int randomX: Math.random() * (page.ListView.view.width-0.5*stickyImage.width) +100
                 property int randomY: Math.random() * (page.ListView.view.height-0.5*stickyImage.height) +50

                 x: randomX; y: randomY

                 rotation: -flickable.horizontalVelocity / 100;
                 Behavior on rotation {
                     SpringAnimation { spring: 2.0; damping: 0.15 }
                 }

                 Item {
                     id: sticky
                     scale: 0.7

                     Image {
                         id: stickyImage
                         x: 8 + -width * 0.6 / 2; y: -20
                         source: "note-yellow.png"
                         scale: 0.6; transformOrigin: Item.TopLeft
                         smooth: true
                     }

                     TextEdit {
                         id: myText
                         x: -104; y: 36; width: 215; height: 200
                         smooth: true
                         font.pixelSize: 24
                         readOnly: false
                         rotation: -8
                         text: modelData
                         onTextChanged:
                         {
                             mainPage.textEdit(text)
                         }
                     }

                     Item {
                         x: stickyImage.x; y: -20
                         width: stickyImage.width * stickyImage.scale
                         height: stickyImage.height * stickyImage.scale

                         MouseArea {
                             id: mouse
                             anchors.fill: parent
                             drag.target: stickyPage
                             drag.axis: Drag.XandYAxis
                             drag.minimumY: 0
                             drag.maximumY: page.height - 80
                             drag.minimumX: 100
                             drag.maximumX: page.width - 140
                             onClicked: { myText.focus = true; myText.openSoftwareInputPanel(); }
                         }
                     }
                 }

                 Image {
                     x: -width / 2; y: -height * 0.5 / 2
                     source: "tack.png"
                     scale: 0.7; transformOrigin: Item.TopLeft
                 }

                 states: State {
                     name: "pressed"
                     when: mouse.pressed
                     PropertyChanges { target: sticky; rotation: 8; scale: 1 }
                     PropertyChanges { target: page; z: 8 }
                 }

                 transitions: Transition {
                     NumberAnimation { properties: "rotation,scale"; duration: 200 }
                 }
             }
         }
     }
 }
