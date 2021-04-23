import QtQuick 2.12
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Controls 2.15 as NewControls
import QtQuick.Controls.Styles 1.4
import "Utils.js" as Utils
Window
{
    visible: true
    id: rulesWindow
    objectName: "rulesWindow"
    title: "Search"
    width: 800
    height: 800

    NewControls.Action
    {
        shortcut: "Delete"
//        onTriggered:
//        {
//            if (actionsTable.currentRow != -1)
//            {
//                filtersModel.DeleteFilter(actionsTable.currentRow )
//            }

//        }
    }

    Rectangle
    {
        id: rulesText
        anchors.top: parent.top
        width: rulesWindow.width
        height: 20
        Text
        {
            anchors.fill: parent
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            text: qsTr("Rules")
        }
    }

    TableView
    {
        id: rulesTable
        model: rulesTableModel
        width: rulesWindow.width
        height: rulesWindow.height * 0.35
        anchors.top: rulesText.bottom
        anchors.topMargin: 5
        style: TableViewStyle
        {
            transientScrollBars: true
            scrollToClickedPosition: true
            headerDelegate: Rectangle
            {
               height: 15
               width: rulesTableHeaderText.implicitWidth
               border.color: "grey"
               color: "#ffe082"
               radius: 3
               Text
               {
                  id: rulesTableHeaderText
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
               color: "#00000000"
               Text
               {
                  anchors.fill: parent
                  elide: Text.ElideRight
                  text: styleData.value ? styleData.value : ""
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
                   var isSelectedRow = rulesTable.currentRow == styleData.row;
                   var isWhiteRow = styleData.row % 2;
                   return isSelectedRow? "lightblue" : isWhiteRow ? "white" : "#e0e0e0"
                }
                MouseArea
                {
                   anchors.bottom: parent.bottom
                   width: parent.width
                   anchors.fill: parent
                   height: parent.height
                   hoverEnabled: true
                   onClicked:
                   {
                      rulesTable.currentRow = styleData.row
                   }
                }
            }
        }
        TableViewColumn
        {
           width: rulesTable.width / rulesTable.columnCount
           role: "rulename"
           title: "Rule name"
        }
        TableViewColumn
        {
           width: rulesTable.width / rulesTable.columnCount
           role: "actionname"
           title: "Action name"
        }
        TableViewColumn
        {
           width: rulesTable.width / rulesTable.columnCount
           role: "filtername"
           title: "Filter name"
        }
    }
    NewControls.Button
    {
        id: createRuleButton
        anchors.topMargin: 2
        anchors.top: rulesTable.bottom
        width: 130
        height: 40
        objectName: "createActionButton"
        background: Rectangle
        {
            border.width: createRuleButton.activeFocus ? 2 : 1
            border.color: "#888"
            radius: 4
            gradient: Gradient
            {
                GradientStop { position: 0 ; color: createRuleButton.pressed ? "#ccc" : "#eee" }
                GradientStop { position: 1 ; color: createRuleButton.pressed ? "#aaa" : "#ccc" }
            }
        }
       text: qsTr("Create Rule")
       onClicked:
       {
           actionWindowLoader.active = true
       }
    }


    Rectangle
    {
        id: actionsText
        anchors.top: createRuleButton.bottom
        anchors.topMargin: 2
        width: rulesWindow.width
        height: 20
        Text
        {
            anchors.fill: parent
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            text: qsTr("Actions")
        }
    }

    TableView
    {
        id: actionsTable
        model: actionsTableModel
        width: rulesWindow.width
        height: rulesWindow.height * 0.35
        anchors.top: actionsText.bottom
        anchors.topMargin: 5
        style: TableViewStyle
        {
            transientScrollBars: true
            scrollToClickedPosition: true
            headerDelegate: Rectangle
            {
               height: 15
               width: actionsTableHeaderText.implicitWidth
               border.color: "grey"
               color: "#ffe082"
               radius: 3
               Text
               {
                  id: actionsTableHeaderText
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
               color: "#00000000"
               Text
               {
                  anchors.fill: parent
                  elide: Text.ElideRight
                  text: styleData.value ? styleData.value : ""
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
                   var isSelectedRow = actionsTable.currentRow == styleData.row;
                   var isWhiteRow = styleData.row % 2;
                   return isSelectedRow? "lightblue" : isWhiteRow ? "white" : "#e0e0e0"
                }
                MouseArea
                {
                   anchors.bottom: parent.bottom
                   width: parent.width
                   anchors.fill: parent
                   height: parent.height
                   hoverEnabled: true
                   onClicked:
                   {
                      actionsTable.currentRow = styleData.row
                   }
                }
            }
        }
        TableViewColumn
        {
           width: actionsTable.width / actionsTable.columnCount
           role: "actionname"
           title: "ActionName"
        }
        TableViewColumn
        {
           width: actionsTable.width / actionsTable.columnCount
           role: "actiontype"
           title: "ActionType"
        }
        TableViewColumn
        {
           width: actionsTable.width / actionsTable.columnCount
           role: "name"
           title: "Name"
        }
        TableViewColumn
        {
           width: actionsTable.width / actionsTable.columnCount
           role: "value"
           title: "Value"
        }
    }

    Loader
    {
        id: actionWindowLoader
        source: "ActionInfoWindow.qml"
        active: false
    }

    NewControls.Button
    {
        id: createActionButton
        anchors.topMargin: 2
        anchors.top: actionsTable.bottom
        width: 130
        height: 40
        objectName: "createActionButton"
        background: Rectangle
        {
            border.width: createActionButton.activeFocus ? 2 : 1
            border.color: "#888"
            radius: 4
            gradient: Gradient
            {
                GradientStop { position: 0 ; color: createActionButton.pressed ? "#ccc" : "#eee" }
                GradientStop { position: 1 ; color: createActionButton.pressed ? "#aaa" : "#ccc" }
            }
        }
       text: qsTr("Create Action")
       onClicked:
       {
           actionWindowLoader.active = true
       }
    }
   onClosing: rulesWindowLoader.active = false
}
