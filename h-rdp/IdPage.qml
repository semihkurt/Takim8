import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1

Page {
    id: idPage

    signal idPageSignal(string pId, string pPassCode, int pType)

    background: Rectangle {
        color: backGroundColor
    }

    Rectangle {
        id: iconRect
        width: parent.width
        height: parent.height / 3
        color: backGroundColor

        Text {
            id: icontext
            text: qsTr("\u2601")
            anchors.centerIn: parent
            font.pointSize: 112
            font.family: "fontawesome"
            color: mainAppColor
        }
    }

    ColumnLayout {
        width: parent.width
        anchors.top: iconRect.bottom
        spacing: 15

        TextField {
            id: loginUserId
            placeholderText: qsTr("Connection ID")
            Layout.preferredWidth: parent.width - 20
            Layout.alignment: Qt.AlignHCenter
            color: mainTextCOlor
            font.pointSize: 14
            font.family: "fontawesome"
            leftPadding: 30
            background: Rectangle {
                implicitWidth: 200
                implicitHeight: 50
                radius: implicitHeight / 2
                color: "transparent"

                Text {
                    text: "\uf007"
                    font.pointSize: 14
                    font.family: "fontawesome"
                    color: mainAppColor
                    anchors.left: parent.left
                    anchors.verticalCenter: parent.verticalCenter
                    leftPadding: 10
                }

                Rectangle {
                    width: parent.width - 10
                    height: 1
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.bottom: parent.bottom
                    color: mainAppColor
                }
            }
        }
        TextField {
            id: loginPasscode
            placeholderText: qsTr("Pass Code")
            Layout.preferredWidth: parent.width - 20
            Layout.alignment: Qt.AlignHCenter
            color: mainTextCOlor
            font.pointSize: 14
            font.family: "fontawesome"
            leftPadding: 30
            passwordCharacter: "*"
            echoMode: TextInput.Password
            background: Rectangle {
                implicitWidth: 200
                implicitHeight: 50
                radius: implicitHeight / 2
                color: "transparent"

                Text {
                    text: "\uf05a"
                    font.pointSize: 14
                    font.family: "fontawesome"
                    color: mainAppColor
                    anchors.left: parent.left
                    anchors.verticalCenter: parent.verticalCenter
                    leftPadding: 10                    
                }

                Rectangle {
                    width: parent.width - 10
                    height: 1
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.bottom: parent.bottom
                    color: mainAppColor
                }
            }
        }

        Item {
            height: 20
        }
        RadioButton {
            id: typeBtn
            Layout.preferredWidth: parent.width - 20
            Layout.alignment: Qt.AlignHCenter
            font.pointSize: 14
            font.family: "fontawesome"
            leftPadding: 30
            checked: true
            text: qsTr("Home")
        }
        RadioButton {
            Layout.preferredWidth: parent.width - 20
            Layout.alignment: Qt.AlignHCenter
            font.pointSize: 14
            font.family: "fontawesome"
            leftPadding: 30
            text: qsTr("Office")
        }

        Item {
            height: 20
        }

        CustomBtn{
            height: 50
            Layout.preferredWidth: idPage.width - 20
            Layout.alignment: Qt.AlignHCenter
            name: "Send ID"
            baseColor: mainAppColor
            borderColor: mainAppColor
            onClicked:{
                stackView.push(login) //registerClicked()
                var type = typeBtn.checked ? 0 : 1

                idPage.idPageSignal(loginUserId.text, loginPasscode.text, type)
            }
        }

    }
}
