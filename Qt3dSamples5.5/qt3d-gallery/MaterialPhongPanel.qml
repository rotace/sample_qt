import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

GridLayout {
    columns: 2
    rowSpacing: 5
    columnSpacing: 5
    flow: GridLayout.LeftToRight

    Label {
        text: "shininess: "+phongMaterial.shininess.toFixed(2)
    }
    Slider {
        value: 100
        minimumValue: 0
        maximumValue: 100
        Layout.fillWidth: true
        onValueChanged: phongMaterial.shininess = this.value
    }

    Label {
        text: "ambient: "
    }
    Button {
        style: ButtonStyle { label: Rectangle { color: phongMaterial.ambient } }
        onClicked: colorDialog.open()
        Layout.fillWidth: true
        property ColorDialog colorDialog: ColorDialog {
            title: "Ambient Color"
            onAccepted: phongMaterial.ambient = this.color
        }
    }

    Label {
        text: "diffuse: "
    }
    Button {
        style: ButtonStyle { label: Rectangle { color: phongMaterial.diffuse } }
        onClicked: colorDialog.open()
        Layout.fillWidth: true
        property ColorDialog colorDialog: ColorDialog {
            title: "Diffuse Color"
            onAccepted: phongMaterial.diffuse = this.color
        }
    }

    Label {
        text: "specular: "
    }
    Button {
        style: ButtonStyle { label: Rectangle { color: phongMaterial.specular } }
        onClicked: colorDialog.open()
        Layout.fillWidth: true
        property ColorDialog colorDialog: ColorDialog {
            title: "Specular Color"
            onAccepted: phongMaterial.specular = this.color
        }
    }

}

