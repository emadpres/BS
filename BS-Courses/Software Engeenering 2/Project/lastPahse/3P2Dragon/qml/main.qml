// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1



Item {
    id: mainPage

    width: 600
    height: 800
   
   

    signal hide(bool iAmHide)
    signal addProject(string projectName,string path , string type,string URL)
	signal chart(string path)
	signal showReminder()

   Image
   {
	id : img_bg
	source : "backGround.jpg"
	
	anchors.fill : parent
   }
   
   Button
    {
        str : "Add"
        x: mainPage.width - 150
        y : 300

        rotation: Math.random() * (2 * 6 + 1) - 6
    }
    Label
    {
        str : "Reminder"
        x: mainPage.width - 150
        y : 400

        rotation: Math.random() * (2 * 6 + 1) - 6
        onClicked:
        {
            mainPage.showReminder()
        }
    }

Flickable {

	states: State {
             name: "ShowBars"
             when: flick.movingVertically || flick.movingHorizontally
             PropertyChanges { target: verticalScrollBar; opacity: 1 }
             PropertyChanges { target: horizontalScrollBar; opacity: 1 }
         }

         transitions: Transition {
             NumberAnimation { properties: "opacity"; duration: 400 }
         }

    id :flick
    objectName: "Flickable"

    property double validX: 100
    property double validY: 50
    property bool firstOrSecond: true //true = first or frist column

    function createProjectItem(name,objectName,path,type,url)
        {
            var component = Qt.createComponent("ProjectItem.qml");
            var pItem = component.createObject(flick.contentItem, {"str" : name,"objectName":objectName,"path":path,"type":type,"url":url });
        if (firstOrSecond)
        {
            validY += 100
            pItem.x = 100
            pItem.y = validY
            firstOrSecond =false
			
			contentHeight += 100
        }
        else
        {
            pItem.x = 250
            pItem.y = validY
            firstOrSecond =true
        }




            if (pItem == null) {
              // Error Handling
              console.log("Error creating object in ProjectItem.qml");
            }
        }

    //clip: true
    anchors.fill: parent
    flickableDirection: Flickable.AutoFlickDirection
    contentWidth: 400; contentHeight: 100
    x: 0
    y: 0
    width: 417
    height: 800
    anchors.rightMargin: 183
	
	 
     
}

 ScrollBar {
         id: verticalScrollBar
         width: 12; height: flick.height-12
         anchors.right: flick.right
         opacity: 0
         orientation: Qt.Vertical
         position: flick.visibleArea.yPosition
         pageSize: flick.visibleArea.heightRatio
     }

     ScrollBar {
         id: horizontalScrollBar
         width: flick.width-12; height: 12
         anchors.bottom: flick.bottom
         opacity: 0
         orientation: Qt.Horizontal
         position: flick.visibleArea.xPosition
         pageSize: flick.visibleArea.widthRatio
     }
 

}
