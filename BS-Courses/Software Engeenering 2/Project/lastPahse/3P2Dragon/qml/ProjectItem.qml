// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1
import FileBrowserComponent 1.0

Item {
   id : projectItem

   property string iconPath: "./Intranet.png"
   property string str: "alireza"//projectLabel.str
   property bool goDetail: false
   property bool isHide: false
   property string type : ""
   property string url : ""
   property string path : ""

   property double randomAngle: Math.random() * (2 * 6 + 1) - 6

   width: projecIcon.width + projectLabel.width
   height:  projecIcon.height + projectLabel.height + 10

   FileBrowser
   {
       id : browser
       mProjectPath : path
	   mProjectType : type
	   mProjectName : str
       x : 300
       y : 300
       opacity:  0
      // width : 400
      // height: 400
   }

   Image {
       id: projecIcon

       source: iconPath
       width: 56
       height: 62
       anchors.top: parent.top
       anchors.topMargin: 0
       anchors.horizontalCenter: parent.horizontalCenter

       MouseArea
       {
           id:mouseArea
           anchors.fill: projecIcon
           onClicked:
           {
               projectItem.goDetail = !projectItem.goDetail
               console.debug("s", projectItem.goDetail)

               mainPage.hide(projectItem.goDetail)
           }
       }
   }

   Text{
       id : projectName
       text : "ProjectName: " + str
       font.bold: true
       font.pointSize: 10
       opacity: 0
       x : -120
       y :projectItem.height + projectName.height + 5
	   
	   color: "white"
   }
   Text
   {
       id : projectPath
       text : "projectPath:" + path
       opacity: 0
       font.pointSize: 10

       x : -120
       y :projectItem.height + projectName.height + projectPath.height + (5*2)
	   
	   color: "white"
   }
   Text
   {
       id: projcetRepository
       text: "projcetRepository:" + url
       font.pointSize: 10
       x: -120
       opacity: 0
       y:projectItem.height + projectName.height + projectPath.height +projcetRepository.height + (5*3)
	   
	   color: "white"
   }
   Text
   {
       id: mtype
       text: "type:" + type
       font.pointSize: 10
       x: -120
       opacity: 0
       y:projectItem.height + projectName.height + projectPath.height +projcetRepository.height +mtype.height + (5*4)
	   
	   color: "white"
   }
   Label
    {
	    id:chart
        str : "chart"
        x: -120
        y:projectItem.height + projectName.height + projectPath.height +projcetRepository.height + mtype.height + chart.height +(5*5)

        rotation: Math.random() * (2 * 6 + 1) - 6
		opacity: 0
        onClicked:
        {
            mainPage.chart(path)
        }
    }

   Flipable
   {
        id : flipable

        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.horizontalCenter: parent.horizontalCenter

        width: projectLabel.width
        height: projectLabel.height
   front
   {
        Label
        {
            id : projectLabel

            str: projectItem.str


            rotation: projectItem.randomAngle

            anchors.fill:  flipable.anchors.fill

        }
   }
   back
   {
       Label
       {
           id : projectLabelBack

           str: "Detail"


           rotation: projectLabel.rotation

            anchors.fill:  flipable.anchors.fill
       }
   }


   transform: Rotation {
            id: rotation
            origin.x: projectLabel.width/2
            origin.y: projectLabel.height/2
            axis.x: 1; axis.y: 0; axis.z: 0     // set axis.y to 1 to rotate around y-axis
            angle: 0    // the default angle
   }
   }




         states: [State {
            when: projectItem.goDetail
            name: "Detail_first"

            PropertyChanges {
                target: projectItem
                z : 10
            }
            PropertyChanges {
                target: projectItem
                y : flick.contentY + 20
            }
            PropertyChanges {
                target: projecIcon
                rotation : 720
            }
            PropertyChanges {
                target: projectItem
                x : 20
            }
            PropertyChanges {
                target: rotation
                angle : 180
            }
            PropertyChanges {
                target: projectName
                x : 5
                opacity : 1
            }
            PropertyChanges {
                target: projectPath
                x : 5
                opacity : 1
            }
            PropertyChanges {
                target: projcetRepository
                x : 5
                opacity : 1
            }
			PropertyChanges {
                target: mtype
                x : 5
                opacity : 1
            }
            PropertyChanges {
                target: browser
                opacity : 1
            }
			PropertyChanges {
                target: chart
                x : 5
                opacity : 1
            }

        }
             ,State {
                 name: "hide"
                 when: isHide
                 PropertyChanges {
                     target: projectItem
                     opacity : 0

                 }
             }
]
         transitions:[ Transition {
                reversible: true
                from : "*"
                to: "Detail_first"
                SequentialAnimation
                {
                    ScriptAction{script: console.debug("sa")}
                    ParallelAnimation
                    {
                        NumberAnimation {target: projectItem ; property: "y" ; duration: 1200}
                        NumberAnimation {target: projectItem ; property: "x" ; duration: 1200}
                        NumberAnimation {target: projecIcon ; property: "rotation" ; duration: 1200}
                    }
                     NumberAnimation { target: rotation; property: "angle"; duration: 700 }

                     ParallelAnimation
                     {
                         NumberAnimation { target: projectName; property: "x"; duration: 600; easing.type: Easing.OutElastic }
                         NumberAnimation { target: projectName; property: "opacity"; duration: 600; easing.type: Easing.OutElastic }

                         NumberAnimation { target: projectPath; property: "x"; duration: 600; easing.type: Easing.OutElastic }
                         NumberAnimation { target: projectPath; property: "opacity"; duration: 600; easing.type: Easing.OutElastic }

                         NumberAnimation { target: projcetRepository; property: "x"; duration: 600; easing.type: Easing.OutElastic }
                         NumberAnimation { target: projcetRepository; property: "opacity"; duration: 600; easing.type: Easing.OutElastic }
						 
						 NumberAnimation { target: mtype; property: "x"; duration: 600; easing.type: Easing.OutElastic }
                         NumberAnimation { target: mtype; property: "opacity"; duration: 600; easing.type: Easing.OutElastic }
						 
						 NumberAnimation { target: chart; property: "x"; duration: 600; easing.type: Easing.OutElastic }
						 NumberAnimation { target: chart; property: "opacity"; duration: 600; easing.type: Easing.OutElastic }
						 
                         NumberAnimation { target: browser; property: "opacity"; duration: 600; easing.type: Easing.OutElastic }
                     }
                }
            }
             ,Transition
             {
                 reversible: true
                 from : "*"
                 to: "hide"
                 NumberAnimation { target: projectItem; property: "opacity"; duration: 600; easing.type: Easing.InOutQuad }
				 PauseAnimation { duration: 2000 }
             }

         ]



   /*SequentialAnimation
   {
       id : goForDetail
        running: goDetail

        PropertyAction {target: projectItem ; property: "z" ; value : 2}
        ParallelAnimation
        {
            NumberAnimation {target: projectItem ; property: "y" ; to :Math.random(10) * 12 ; duration: 1200}
            //NumberAnimation {target: projectItem ; property: "x" ; to :Math.random(3) * 12 ; duration: 1200}
            NumberAnimation {target: projecIcon ; property: "rotation" ; to :Math.random() * 360 ; duration: 1200}
        }
        ParallelAnimation
        {
            NumberAnimation {target: projectItem ; property: "y" ; to :20 ; duration: 1200}
            NumberAnimation {target: projectItem ; property: "x" ; to :20 ; duration: 1200}
            NumberAnimation {target: projecIcon ; property: "rotation" ; to :720 ; duration: 1200}
        }
        NumberAnimation { target: rotation; property: "angle";to : 180; duration: 700 }

   }*/

         Connections
         {
             target: mainPage
             onHide :{
                 if (iAmHide)
                 {
                    isHide = goDetail ? false  : true
                    console.debug("saas",isHide,goDetail)
                 }
                 else
                 {
                     isHide = false
                 }
             }
         }

}
