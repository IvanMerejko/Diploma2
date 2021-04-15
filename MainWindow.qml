import QtQuick 2.0
import QtQuick 2.15
import QtQuick.Window 2.12
import QtQuick.Controls 2.15 as NewControls
import QtQuick.Controls 1.4 as OldControls
import QtQuick.Controls.Styles 1.4
import QtQuick.Dialogs 1.0
Window
{
   visible: true
   id: window
   objectName: "window"
   width: 1000
   height: 800

   function basename(str)
   {
       return (str.slice(str.lastIndexOf(":")-1))
   }

   FileDialog
   {
       id: fileDialog
       objectName: "fileDialog"
       title: "Please choose a file"
       onAccepted: treeModel.LoadData(basename(fileDialog.fileUrl.toString()))
   }

   NewControls.Button
   {
       id: loadFileButton
       objectName: "LoadFileButton"
       background: Rectangle
       {
           implicitWidth: 100
           implicitHeight: 25
           border.width: loadFileButton.activeFocus ? 2 : 1
           border.color: "#888"
           radius: 4
           gradient: Gradient
           {
               GradientStop { position: 0 ; color: loadFileButton.pressed ? "#ccc" : "#eee" }
               GradientStop { position: 1 ; color: loadFileButton.pressed ? "#aaa" : "#ccc" }
           }
       }
      text: qsTr("Load File")
      onClicked: fileDialog.open()
   }

   OldControls.TreeView
   {
       id: xmlTree
       width: window.width
       height: window.height * 0.75
       anchors.top: loadFileButton.bottom
       anchors.topMargin: 5
       model: treeModel
       OldControls.TableViewColumn
       {
           role: "xml"
           title: "XML"
       }
       onDoubleClicked: mainWindowObject.CreateNodeInfoWindow(currentIndex)
//       rowDelegate: Rectangle
//       {

//       }
   }

}
