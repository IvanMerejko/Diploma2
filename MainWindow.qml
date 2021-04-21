import QtQuick 2.0
import QtQuick 2.15
import QtQuick.Window 2.12
import QtQuick.Controls 2.15 as NewControls
import QtQuick.Controls 1.4 as OldControls
import QtQuick.Controls.Styles 1.4
import QtQuick.Dialogs 1.0
import "Utils.js" as Utils
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

   Loader
   {
       id: searchWindowLoader
       source: "SearchWindow.qml"
       active: false
   }

   NewControls.Action
   {
       shortcut: "Ctrl+F"
       onTriggered: searchWindowLoader.active = true
   }

   NewControls.Action
   {
       shortcut: "Ctrl+H"
       onTriggered: Utils.expandAll()
   }

   FileDialog
   {
       id: fileDialog
       objectName: "fileDialog"
       title: "Please choose a file"
       onAccepted:
       {
           treeModel.LoadData(basename(fileDialog.fileUrl.toString()))
           treeColumn.title = treeModel.GetTitle()
       }
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
       style: TreeViewStyle
       {
           transientScrollBars: true
           scrollToClickedPosition: true
           headerDelegate: Rectangle
           {
              height: 15
              width: xmlTree.implicitWidth
              border.color: "grey"
              color: "#ffe082"
              radius: 3
              Text
              {
                 anchors.fill: parent
                 horizontalAlignment: Text.AlignHCenter
                 verticalAlignment: Text.AlignVCenter
                 font.family: "Times New Roman"
                 font.pixelSize: 14
                 text: styleData.value
              }
           }
           itemDelegate: Rectangle
           {
              color: "#00000000"

              Text
              {
                 anchors.fill: parent
                 elide: Text.ElideRight
                 text: styleData.value ? styleData.value : ""
                 font.family: "Times New Roman"
                 font.pixelSize: 14
                 horizontalAlignment: Text.AlignLeft
                 verticalAlignment: Text.AlignVCenter
              }
           }
           rowDelegate: Rectangle
           {
               width: item.width
               height: item.height
               color:
               {
                  var isSelectedRow = xmlTree.currentRow === styleData.row;
                  var isWhiteRow = styleData.row % 2;

                  if (treeModel && treeModel.IsRowMathFilter(styleData.row))
                  {
                      return "green";
                  }
                  else if (isSelectedRow)
                  {
                      return "lightblue"
                  }
                  else
                  {
                      return isWhiteRow ? "white" : "#e0e0e0"
                  }
               }
           }
       }

       OldControls.TableViewColumn
       {
           id: treeColumn
           width: xmlTree.width / xmlTree.columnCount
           role: "fileType"
       }

       onDoubleClicked: mainWindowObject.CreateNodeInfoWindow(currentIndex)
   }


   OldControls.TableView
   {
       id: filterResultTable
       model: filterResultModel
       width: window.width
       height: window.height - xmlTree.height - loadFileButton.height - 10
       anchors.top: xmlTree.bottom
       anchors.topMargin: 2
       style: TableViewStyle
       {
           transientScrollBars: true
           scrollToClickedPosition: true
           headerDelegate: Rectangle
           {
              height: 15
              width: filterResultText.implicitWidth
              border.color: "grey"
              color: "#ffe082"
              radius: 3
              Text
              {
                 id: filterResultText
                 anchors.fill: parent
                 horizontalAlignment: Text.AlignHCenter
                 verticalAlignment: Text.AlignVCenter
                 font.family: "Times New Roman"
                 font.pixelSize: 14
                 text: styleData.value
              }
           }
           itemDelegate: Rectangle
           {
              border.width: 0.5
              color:  "#00000000"
              Text
              {
                 anchors.fill: parent
                 elide: Text.ElideRight
                 text: styleData.value ? styleData.value : ""
                 font.family: "Times New Roman"
                 font.pixelSize: 14
                 horizontalAlignment: Text.AlignHCenter
                 verticalAlignment: Text.AlignVCenter
              }
           }
           rowDelegate: Rectangle
           {
               width: item.width
               height: item.height
               color:
               {
                  var isSelectedRow = filterResultTable.currentRow === styleData.row;
                  var isWhiteRow = styleData.row % 2;
                  isSelectedRow? "green" : isWhiteRow ? "white" : "#e0e0e0"
               }
               Text
               {
                  id: textInRow
               }
           }
       }

       OldControls.TableViewColumn
       {
          width: filterResultTable.width / filterResultTable.columnCount
          role: "result"
          title: "result"
       }
   }
}
