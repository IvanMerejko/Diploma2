import QtQuick 2.12
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Controls 2.15 as NewControls
import QtQuick.Controls.Styles 1.4
import "Utils.js" as Utils
Window
{
    visible: true
    id: searchWindow
    objectName: "searchWindow"
    title: "Search"
    width: 800
    height: 600
    TextField
    {
        id: searchField
        objectName: "searchField"
        font.family: "Times New Roman"
        font.pixelSize: 20
        anchors.top: parent.top
        anchors.topMargin: 5
        height: 25
        width: searchWindow.width - 20
    }

    Rectangle
    {
        id: filtersText
        anchors.top: searchField.bottom
        width: searchWindow.width
        height: 20
        Text
        {
            anchors.fill: parent
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            text: qsTr("Filters")
        }
    }

    TableView
    {
        id: filtersTable
        model: filtersModel
        width: searchWindow.width
        height: searchWindow.height - searchField.height - filtersText.height - createFilterButton.height - 60
        anchors.top: filtersText.bottom
        anchors.topMargin: 5
        style: TableViewStyle
        {
            transientScrollBars: true
            scrollToClickedPosition: true
            headerDelegate: Rectangle
            {
               height: 15
               width: searchTableHeaderText.implicitWidth
               border.color: "grey"
               color: "#ffe082"
               radius: 3
               Text
               {
                  id: searchTableHeaderText
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
                   var isSelectedRow = filtersTable.currentRow == styleData.row;
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
                      filtersTable.currentRow = styleData.row
                   }
                }
            }
        }
        TableViewColumn
        {
           width: filtersTable.width / filtersTable.columnCount
           role: "name"
           title: "Name"
        }
        TableViewColumn
        {
           width: filtersTable.width / filtersTable.columnCount
           role: "searchType"
           title: "SearchType"
        }
        TableViewColumn
        {
           width: filtersTable.width / filtersTable.columnCount
           role: "searchAction"
           title: "SearchAction"
        }
        TableViewColumn
        {
           width: filtersTable.width / filtersTable.columnCount
           role: "value"
           title: "Value"
        }
    }

    Loader
    {
        id: filterWindowLoader
        source: "FilterInfoWindow.qml"
        active: false
    }

    NewControls.Button
    {
        id: createFilterButton
        anchors.topMargin: 2
        anchors.top: filtersTable.bottom
        width: 130
        height: 40
        objectName: "CreateFilterButton"
        background: Rectangle
        {
            border.width: createFilterButton.activeFocus ? 2 : 1
            border.color: "#888"
            radius: 4
            gradient: Gradient
            {
                GradientStop { position: 0 ; color: createFilterButton.pressed ? "#ccc" : "#eee" }
                GradientStop { position: 1 ; color: createFilterButton.pressed ? "#aaa" : "#ccc" }
            }
        }
       text: qsTr("Create Filter")
       onClicked:
       {
           filterWindowLoader.active = true
       }

    }

    NewControls.Button
    {
        id: searchButton
        anchors.leftMargin: 2
        anchors.topMargin: 2
        anchors.right: parent.right
        anchors.top: filtersTable.bottom
        width: 130
        height: 40
        background: Rectangle
        {
            border.width: searchButton.activeFocus ? 2 : 1
            border.color: "#888"
            radius: 4
            gradient: Gradient
            {
                GradientStop { position: 0 ; color: searchButton.pressed ? "#ccc" : "#eee" }
                GradientStop { position: 1 ; color: searchButton.pressed ? "#aaa" : "#ccc" }
            }
        }
       text: qsTr("Search")
       onClicked:
       {
           console.log(searchField.text)
           if (searchField.text != "")
           {
               mainWindowObject.Search(searchField.text)
               Utils.expandAll()
           }
           else if (filtersTable.currentRow != -1)
           {
               mainWindowObject.Search(filtersTable.currentRow)
               Utils.expandAll()
           }
       }

    }
   onClosing: searchWindowLoader.active = false
}
