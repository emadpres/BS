// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Rectangle {
     width: 800; height: 480
     color: "#464646"

     signal textEdit(string text)

     id :mainPage

     function add2Lisr()
     {
//         var component = Qt.createComponent("ListElement");
//         var pItem = component.createObject(list, {"noteText" : "vali" });

        // var com = Qt.createQmlObject('import QtQuick 1.1;notes: [ListElement { noteText: "Luncsfdsdfsdfh" }]',list)
         var ali = ["21321231" ,"5756786678","445454564"]

         var test =  list.append({"name" : "ali" } )





     }

//     ListModel {
//         id: list

//         ListElement {
//             name : "kjjkdsffds"
//             //vali :["sdsfdsfd","sdffsdsfd","sfdsdfsdf"]

//         }

//         ListElement {
//             name : "kjjkdsffds"
//             //vali :["sdsfdsfd","sdffsdsfd","sfdsdfsdf"]

//         }

//         ListElement {
//             name : "sasda"
//             //vali :["sdsfdsfd","sdffsdsfd","sfdsdfsdf"]
//         }
//     }

//     ListModel {
//             id: list

//             ListElement {
//                 name: "Sunday"


//             }

//             ListElement {
//                 name: "Monday"
//                 notes: [
//                     ListElement { noteText: "call alireza for new\n change" },
//                     ListElement { noteText: "test" }, ListElement { noteText: "Read email" }
//                 ]
//             }

//             ListElement {
//                 name: "Tuesday"
//                 notes: [
//                     ListElement { noteText: "Alireza" },
//                     ListElement { noteText: "Beydaghi" }
//                 ]
//             }

//             ListElement {
//                 name: "Wednesday"
//                 notes: [ ListElement { noteText: "commit new \n project" } ]
//             }

//             ListElement {
//                 name: "Thursday"
//                 notes: [
//                     ListElement { noteText: "Meeting\n5.30pm" },
//                     ListElement { noteText: "Weed garden" }
//                 ]
//             }

//             ListElement {
//                 name: "Friday"
//                 notes: [
//                     ListElement { noteText: "More work" },
//                     ListElement { noteText: "Grocery shopping" }
//                 ]
//             }

//             ListElement {
//                 name: "Saturday"
//                 notes: [
//                     ListElement { noteText: "Drink" },
//                     ListElement { noteText: "Download Qt\nPlay with QML" }
//                 ]
//             }
//         }

     ListView {
             id: flickable

             anchors.fill: parent
             focus: true
             highlightRangeMode: ListView.StrictlyEnforceRange
             orientation: ListView.Horizontal
             snapMode: ListView.SnapOneItem
             model: dummyModel
             delegate: Day{}
     }

     Connections
     {
         target: mainPage
         onTextEdit :
         {
             console.debug("hehe",text)
         }
     }
 }



//Rectangle {
//    id: base
//    width: 500
//    height: 360
//    Repeater {
//    model: dummyModel
//    delegate: myDelegate
//    }

//    Component {
//    id: myDelegate
//    Rectangle {
//        x: 10
//        y: index*35+10
//        width: 200
//        height: 30
//        color: "yellow"
//        TextEdit {
//        text: title
//        font.pointSize: 18
//        }
//        MouseArea {
//        anchors.fill:  parent
//        onClicked: {
//            console.log("Clicked index:",index);
//            title="test"
//        }
//        }
//    }
//  }
//}
