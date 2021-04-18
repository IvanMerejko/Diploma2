import QtQuick 2.12
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
Window
{
    visible: true
    id: nodeInfoWindow
    objectName: "nodeInfoWindow"
    title: "Node Info"
    width: 400
    height: 500
    Rectangle
    {
        id: nameTextRectangle
        anchors.left: nodeInfoWindow.left
        width: 100
        height: 20
        border.width: 1
        Text
        {
            anchors.fill: parent
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.family: "Times New Roman"
            font.pixelSize: 14
            text: qsTr("Name")
        }
    }

    TextField
    {
        id: nameField
        objectName: "nameField"
        font.family: "Times New Roman"
        font.pixelSize: 14
        height: nameTextRectangle.height
        width: nodeInfoWindow.width - nameTextRectangle.width - 20
        anchors.left: nameTextRectangle.right
        anchors.leftMargin: 4
        textColor: nodeInfoWindowObject.IsNameMatchFilter() ? "green" : "black"
    }

    Rectangle
    {
        id: valueTextRectangle
        anchors.top: nameTextRectangle.bottom
        anchors.topMargin: 1
        width: 100
        height: 20
        Text
        {
            anchors.fill: parent
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.family: "Times New Roman"
            font.pixelSize: 14
            text: qsTr("Value")
        }
        border.width: 1
    }

    TextField
    {
        id: valueField
        objectName: "valueField"
        font.family: "Times New Roman"
        font.pixelSize: 14
        height: valueTextRectangle.height
        width: nodeInfoWindow.width - valueTextRectangle.width - 20
        anchors.left: valueTextRectangle.right
        anchors.top: nameField.bottom
        anchors.leftMargin: 4
        textColor: nodeInfoWindowObject.IsValueMatchFilter() ? "green" : "black"
    }

    Rectangle
    {
        id: attributesRectangleText
        anchors.top: valueTextRectangle.bottom
        width: nodeInfoWindow.width
        height: 20
        Text
        {
            anchors.fill: parent
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            text: qsTr("Attributes")
        }
    }

    TableView
    {
        id: attributesTable
        model: attributtesModel
        width: nodeInfoWindow.width
        height: nodeInfoWindow.height - valueField.height - nameField.height - 2
        anchors.top: attributesRectangleText.bottom
        anchors.topMargin: 2
        style: TableViewStyle
        {
            transientScrollBars: true
            scrollToClickedPosition: true
            headerDelegate: Rectangle
            {
               height: 15
               width: attributesTableText.implicitWidth
               border.color: "grey"
               color: "#ffe082"
               radius: 3
               Text
               {
                  id: attributesTableText
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
               color: attributtesModel && attributtesModel.IsItemMatchFilter(styleData.row, styleData.column) ? "green" : "#00000000"
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
                   var isSelectedRow = attributesTable.currentRow === styleData.row;
                   var isWhiteRow = styleData.row % 2;
                   isSelectedRow? "green" : isWhiteRow ? "white" : "#e0e0e0"
                }
                Text
                {
                   id: textInRow
                }
            }
        }
        TableViewColumn
        {
           width: attributesTable.width / attributesTable.columnCount
           role: "name"
           title: "Name"
        }
        TableViewColumn
        {
           width: attributesTable.width / attributesTable.columnCount
           role: "value"
           title: "Value"
        }
    }
}
