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
        text: "shininess: "+diffuseMapMaterial.shininess.toFixed(2)
    }
    Slider {
        value: 100
        minimumValue: 0
        maximumValue: 100
        Layout.fillWidth: true
        onValueChanged: diffuseMapMaterial.shininess = this.value
    }

    Label {
        text: "textureScale: "+diffuseMapMaterial.textureScale.toFixed(2)
    }
    Slider {
        value: 1.0
        minimumValue: 0.1
        maximumValue: 10
        Layout.fillWidth: true
        onValueChanged: diffuseMapMaterial.textureScale = this.value
    }

    Label {
        text: "ambient: "
    }
    Button {
        style: ButtonStyle { label: Rectangle { color: diffuseMapMaterial.ambient } }
        onClicked: colorDialog.open()
        Layout.fillWidth: true
        property ColorDialog colorDialog: ColorDialog {
            title: "Ambient Color"
            onAccepted: diffuseMapMaterial.ambient = this.color
        }
    }

    Label {
        text: "diffuse: "
    }
    ComboBox {
        Layout.fillWidth: true
        model: [
            "assets/t1.png",
            "assets/t2.png",
            "assets/t3.png",
        ]
        onCurrentTextChanged: diffuseMapMaterial.diffuse = currentText
    }

    Label {
        text: "specular: "
    }
    Button {
        style: ButtonStyle { label: Rectangle { color: diffuseMapMaterial.specular } }
        onClicked: colorDialog.open()
        Layout.fillWidth: true
        property ColorDialog colorDialog: ColorDialog {
            title: "Specular Color"
            onAccepted: diffuseMapMaterial.specular = this.color
        }
    }

}

