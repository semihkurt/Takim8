import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1
import QtQuick.LocalStorage 2.0

import "backend.js" as Backend

ApplicationWindow {
    id: rootWindow
    visible: true
    width: 420
    height: 680
    title: qsTr("Login Demo")

    Connections{
        target: controller
        onCppSignal:{
            console.debug("signal emitted:" + pTest)
        }
    }

    Connections{
        target: idpage
        onIdPageSignal:{
            controller.onUserConnectSlot(pId, pPassCode, pType)
        }
    }

    Connections{
        target: login
        onLoginSignal:{
            controller.onLDAPConnectSlot(pUsername, pPassword)
        }
    }
    property color backGroundColor : "#394454"
    property color mainAppColor: "#6fda9c"
    property color mainTextCOlor: "#f0f0f0"
    property color popupBackGroundColor: "#b44"
    property color popupTextCOlor: "#ffffff"

    FontLoader {
        id: fontAwesome
        name: "fontawesome"
        source: "qrc:/fontawesome-webfont.ttf"
    }

    // Main stackview
    StackView{
        id: stackView
        focus: true
        anchors.fill: parent
    }

    // After loading show initial Login Page
    Component.onCompleted: {
//        stackView.push("qrc:/IdPage.qml")   //initial page
        stackView.push(idpage)
    }

    IdPage{
        id: idpage
    }
    LogInPage{
        id:login
        visible: false
    }

    //Popup to show messages or warnings on the bottom postion of the screen
    Popup {
        id: popup
        property alias popMessage: message.text

        background: Rectangle {
            implicitWidth: rootWindow.width
            implicitHeight: 60
            color: popupBackGroundColor
        }
        y: (rootWindow.height - 60)
        modal: true
        focus: true
        closePolicy: Popup.CloseOnPressOutside
        Text {
            id: message
            anchors.centerIn: parent
            font.pointSize: 12
            color: popupTextCOlor
        }
        onOpened: popupClose.start()
    }

    // Popup will be closed automatically in 2 seconds after its opened
    Timer {
        id: popupClose
        interval: 2000
        onTriggered: popup.close()
    }

    // Logout and show login page
    function logoutSession()
    {
        stackView.replace("qrc:/LogInPage.qml")
    }


}
