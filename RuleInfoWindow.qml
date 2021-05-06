import QtQuick 2.12
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Controls 2.15 as NewControls
import QtQuick.Controls.Styles 1.4
Window
{
    visible: true
    id: ruleInfoWindow
    title: "Rule Info"
    width: 300
    height: 200
    Rectangle
    {
        id: ruleNameTextRectangle
        anchors.left: ruleInfoWindow.left
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
            text: qsTr("Rule Name")
        }
    }

    TextField
    {
        id: ruleNameField
        font.family: "Times New Roman"
        font.pixelSize: 14
        height: ruleNameTextRectangle.height
        width: ruleInfoWindow.width - ruleNameTextRectangle.width
        anchors.left: ruleNameTextRectangle.right
        anchors.leftMargin: 4
        anchors.topMargin: 1
    }

    Rectangle
    {
        id: actionNameTextRectangle
        anchors.left: ruleInfoWindow.left
        anchors.top: ruleNameTextRectangle.bottom
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
            text: qsTr("Action Name")
        }
    }

    ComboBox
    {
        id: actionNameBox
        height: actionNameTextRectangle.height
        width: ruleInfoWindow.width - actionNameTextRectangle.width
        anchors.left: ruleNameTextRectangle.right
        anchors.top: ruleNameField.bottom
        anchors.leftMargin: 4
        anchors.topMargin: 1
        model: actionsTableModel.GetActionsName()
    }

    Rectangle
    {
        id: filterNameTextRectangle
        anchors.left: ruleInfoWindow.left
        anchors.top: actionNameTextRectangle.bottom
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
            text: qsTr("Filter Name")
        }
    }

    ComboBox
    {
        id: filtersNameBox
        height: actionNameTextRectangle.height
        width: ruleInfoWindow.width - actionNameTextRectangle.width
        anchors.left: ruleNameTextRectangle.right
        anchors.top: actionNameBox.bottom
        anchors.leftMargin: 4
        anchors.topMargin: 1
        model: filtersModel.GetFiltersName()
    }


    NewControls.Button
    {
        id: createButton
        anchors.topMargin: 2
        anchors.top: filterNameTextRectangle.bottom
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
           rulesTableModel.AddRule(ruleNameField.text, filtersNameBox.currentIndex, actionNameBox.currentIndex)
       }
    }
    onClosing:
    {
        ruleWindowLoader.active = false
    }
}
