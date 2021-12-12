import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.12

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")
    Image {
        anchors.fill: parent
        source: "qrc:/image/%1.gif".arg(qsTr("__country_code__"))
        Text {
            anchors {left: parent.left; top: parent.top; margins: 25}
            font.pixelSize: 24
            text: qsTr("__country_name__")
        }
        MouseArea {
            anchors.fill: parent
            acceptedButtons: Qt.RightButton
            onClicked: contextMenu.open()
        }
    }
    Menu {
        id: contextMenu
        Repeater {
            model: languages
            delegate: MenuItem {
                width: 200
                height: 30
                text: modelData.text
                onTriggered: modelData.trigger()
            }
        }
    }
}
