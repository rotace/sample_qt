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
        text: "shininess: "+normalDiffuseMapAlphaMaterial.shininess.toFixed(2)
    }
    Slider {
        value: 100
        minimumValue: 0
        maximumValue: 100
        Layout.fillWidth: true
        onValueChanged: normalDiffuseMapAlphaMaterial.shininess = this.value
    }

    Label {
        text: "textureScale: "+normalDiffuseMapAlphaMaterial.textureScale.toFixed(2)
    }
    Slider {
        value: 1.0
        minimumValue: 0.1
        maximumValue: 10
        Layout.fillWidth: true
        onValueChanged: normalDiffuseMapAlphaMaterial.textureScale = this.value
    }

    Label {
        text: "ambient: "
    }
    Button {
        style: ButtonStyle { label: Rectangle { color: normalDiffuseMapAlphaMaterial.ambient } }
        onClicked: colorDialog.open()
        Layout.fillWidth: true
        property ColorDialog colorDialog: ColorDialog {
            title: "Ambient Color"
            onAccepted: normalDiffuseMapAlphaMaterial.ambient = this.color
        }
    }

    Label {
        text: "normal: "
    }
    ComboBox {
        Layout.fillWidth: true
        model: [
            "assets/t1.png",
            "assets/t2.png",
            "assets/t3.png",
        ]
        onCurrentTextChanged: normalDiffuseMapAlphaMaterial.normal = currentText
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
        onCurrentTextChanged: normalDiffuseMapAlphaMaterial.diffuse = currentText
    }

    Label {
        text: "specular: "
    }
    Button {
        style: ButtonStyle { label: Rectangle { color: normalDiffuseMapAlphaMaterial.specular } }
        onClicked: colorDialog.open()
        Layout.fillWidth: true
        property ColorDialog colorDialog: ColorDialog {
            title: "Specular Color"
            onAccepted: normalDiffuseMapAlphaMaterial.specular = this.color
        }
    }

}

