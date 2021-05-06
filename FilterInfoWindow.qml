import QtQuick 2.12
import QtQuick.Dialogs 1.2
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Controls 2.15 as NewControls
import QtQuick.Controls.Styles 1.4
Window
{
    visible: true
    id: filterInfoWindow
    objectName: "filterInfoWindow"
    title: "Filter Info"
    width: 300
    height: 200
    Rectangle
    {
        id: filterNameTextRectangle
        anchors.left: filterInfoWindow.left
        width: 100
        height: 30
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
        id: filterNameField
        objectName: "filterNameField"
        font.family: "Times New Roman"
        font.pixelSize: 14
        height: filterNameTextRectangle.height
        width: filterInfoWindow.width - filterNameTextRectangle.width
        anchors.left: filterNameTextRectangle.right
        anchors.leftMargin: 4
        anchors.topMargin: 1
    }

    Rectangle
    {
        id: filterValueTextRectangle
        anchors.top: filterNameTextRectangle.bottom
        anchors.topMargin: 1
        width: 100
        height: 30
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
        id: filterValueField
        objectName: "filterValueField"
        font.family: "Times New Roman"
        font.pixelSize: 14
        height: filterValueTextRectangle.height
        width: filterInfoWindow.width - filterValueTextRectangle.width
        anchors.left: filterValueTextRectangle.right
        anchors.top: filterNameField.bottom
        anchors.leftMargin: 4
        anchors.topMargin: 1
    }

    Rectangle
    {
        id: searchTypeTextRectangle
        anchors.top: filterValueTextRectangle.bottom
        anchors.topMargin: 1
        width: 100
        height: 30
        Text
        {
            anchors.fill: parent
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.family: "Times New Roman"
            font.pixelSize: 14
            text: qsTr("SearchType")
        }
        border.width: 1
    }

    ComboBox
    {
        id: searchTypeBox
        anchors.left: searchTypeTextRectangle.right
        anchors.top: filterValueField.bottom
        anchors.leftMargin: 4
        anchors.topMargin: 1
        width: 200
        height: 30
        model: [ "Name", "Value", "AttributeName", "AttributeValue", "Compound"]
    }

    Rectangle
    {
        id: searchActionTextRectangle
        anchors.top: searchTypeTextRectangle.bottom
        anchors.topMargin: 1
        width: 100
        height: 30
        Text
        {
            anchors.fill: parent
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.family: "Times New Roman"
            font.pixelSize: 14
            text: qsTr("SearchAction")
        }
        border.width: 1
    }

    ComboBox
    {
        id: searchActionBox
        anchors.left: searchActionTextRectangle.right
        anchors.top: searchTypeBox.bottom
        anchors.leftMargin: 4
        anchors.topMargin: 1
        width: 200
        height: 30
        model: [ "Equal", "NotEqual", "Contains", "NotContains" ]
    }

    MessageDialog
    {
        id: errorMessage
        title: "Error"
        visible: false
        icon: StandardIcon.Critical
        standardButtons: StandardButton.Ok
    }


    NewControls.Button
    {
        id: createButton
        anchors.topMargin: 2
        anchors.top: searchActionTextRectangle.bottom
        width: 130
        height: 40
        background: Rectangle
        {
            implicitWidth: 100
            implicitHeight: 25
            border.width: createButton.activeFocus ? 2 : 1
            border.color: "#888"
            radius: 4
            gradient: Gradient
            {
                GradientStop { position: 0 ; color: createButton.pressed ? "#ccc" : "#eee" }
                GradientStop { position: 1 ; color: createButton.pressed ? "#aaa" : "#ccc" }
            }
        }
       text: qsTr("Create")
       onClicked:
       {
           var error = filtersModel.AddFilter(filterNameField.text, filterValueField.text, searchTypeBox.currentIndex, searchActionBox.currentIndex)
           if (error.length !== 0)
           {
               errorMessage.text = "Incorrect Compound filter expression! Please check your input." + " Details: " + error
               errorMessage.visible = true
           }
       }
    }
    onClosing:
    {
        filterWindowLoader.active = false
    }
}
