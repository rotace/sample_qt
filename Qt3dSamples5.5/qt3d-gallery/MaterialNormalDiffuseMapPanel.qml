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
        text: "shininess: "+normalDiffuseMapMaterial.shininess.toFixed(2)
    }
    Slider {
        value: 100
        minimumValue: 0
        maximumValue: 100
        Layout.fillWidth: true
        onValueChanged: normalDiffuseMapMaterial.shininess = this.value
    }

    Label {
        text: "textureScale: "+normalDiffuseMapMaterial.textureScale.toFixed(2)
    }
    Slider {
        value: 1.0
        minimumValue: 0.1
        maximumValue: 10
        Layout.fillWidth: true
        onValueChanged: normalDiffuseMapMaterial.textureScale = this.value
    }

    Label {
        text: "ambient: "
    }
    Button {
        style: ButtonStyle { label: Rectangle { color: normalDiffuseMapMaterial.ambient } }
        onClicked: colorDialog.open()
        Layout.fillWidth: true
        property ColorDialog colorDialog: ColorDialog {
            title: "Ambient Color"
            onAccepted: normalDiffuseMapMaterial.ambient = this.color
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
        onCurrentTextChanged: normalDiffuseMapMaterial.normal = currentText
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
        onCurrentTextChanged: normalDiffuseMapMaterial.diffuse = currentText
    }

    Label {
        text: "specular: "
    }
    Button {
        style: ButtonStyle { label: Rectangle { color: normalDiffuseMapMaterial.specular } }
        onClicked: colorDialog.open()
        Layout.fillWidth: true
        property ColorDialog colorDialog: ColorDialog {
            title: "Specular Color"
            onAccepted: normalDiffuseMapMaterial.specular = this.color
        }
    }

}

