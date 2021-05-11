import QtQuick 2.12
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import QtQuick.Controls 1.4
import QtQuick.Controls 2.15 as NewControls
import QtQuick.Controls.Styles 1.4
Window
{
    visible: true
    id: actionInfoWindow
    objectName: "actionInfoWindow"
    title: "Action Info"
    width: 300
    height: 200
    Rectangle
    {
        id: actionNameTextRectangle
        anchors.left: actionInfoWindow.left
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
            text: qsTr("Action Name")
        }
    }

    TextField
    {
        id: actionNameField
        objectName: "actionNameField"
        font.family: "Times New Roman"
        font.pixelSize: 14
        height: actionNameTextRectangle.height
        width: actionInfoWindow.width - actionNameTextRectangle.width
        anchors.left: actionNameTextRectangle.right
        anchors.leftMargin: 4
        anchors.topMargin: 1
    }

    Rectangle
    {
        id: actionTypeTextRectangle
        anchors.top: actionNameTextRectangle.bottom
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
            text: qsTr("Action Type")
        }
        border.width: 1
    }

    ComboBox
    {
        id: actionTypeBox
        anchors.left: actionTypeTextRectangle.right
        anchors.top: actionNameField.bottom
        anchors.leftMargin: 4
        anchors.topMargin: 1
        width: 200
        height: 30
        model: [ "DeleteNode", "DeleteAttribute", "ModifyAttributeName", "ModifyAttributeValue", "ModifyNodeName", "ModifyNodeValue", "AddAttribute" ]
    }

    Rectangle
    {
        id: nameTextRectangle
        anchors.left: actionInfoWindow.left
        anchors.top: actionTypeTextRectangle.bottom
        anchors.topMargin: 2
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
        id: nameField
        objectName: "nameField"
        font.family: "Times New Roman"
        font.pixelSize: 14
        height: actionNameTextRectangle.height
        width: actionInfoWindow.width - actionNameTextRectangle.width
        anchors.left: actionNameTextRectangle.right
        anchors.top: actionTypeBox.bottom
        anchors.leftMargin: 4
        anchors.topMargin: 1
    }

    Rectangle
    {
        id: valueTextRectangle
        anchors.left: actionInfoWindow.left
        anchors.top: nameTextRectangle.bottom
        anchors.topMargin: 2
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
            text: qsTr("Value")
        }
    }

    TextField
    {
        id: valueField
        objectName: "valueField"
        font.family: "Times New Roman"
        font.pixelSize: 14
        height: valueTextRectangle.height
        width: actionInfoWindow.width - valueTextRectangle.width
        anchors.left: valueTextRectangle.right
        anchors.top: nameField.bottom
        anchors.leftMargin: 4
        anchors.topMargin: 1
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
        anchors.top: valueTextRectangle.bottom
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
           var error = actionsTableModel.AddAction(actionNameField.text, actionTypeBox.currentIndex, nameField.text, valueField.text)
           if (error.length !== 0)
           {
               errorMessage.text = error
               errorMessage.visible = true
           }
       }
    }
    onClosing:
    {
        actionWindowLoader.active = false
    }
}
