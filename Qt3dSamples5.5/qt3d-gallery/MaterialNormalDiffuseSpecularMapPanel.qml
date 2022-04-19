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
        text: "shininess: "+normalDiffuseSpecularMapMaterial.shininess.toFixed(2)
    }
    Slider {
        value: 100
        minimumValue: 0
        maximumValue: 100
        Layout.fillWidth: true
        onValueChanged: normalDiffuseSpecularMapMaterial.shininess = this.value
    }

    Label {
        text: "textureScale: "+normalDiffuseSpecularMapMaterial.textureScale.toFixed(2)
    }
    Slider {
        value: 1.0
        minimumValue: 0.1
        maximumValue: 10
        Layout.fillWidth: true
        onValueChanged: normalDiffuseSpecularMapMaterial.textureScale = this.value
    }

    Label {
        text: "ambient: "
    }
    Button {
        style: ButtonStyle { label: Rectangle { color: normalDiffuseSpecularMapMaterial.ambient } }
        onClicked: colorDialog.open()
        Layout.fillWidth: true
        property ColorDialog colorDialog: ColorDialog {
            title: "Ambient Color"
            onAccepted: normalDiffuseSpecularMapMaterial.ambient = this.color
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
        onCurrentTextChanged: normalDiffuseSpecularMapMaterial.normal = currentText
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
        onCurrentTextChanged: normalDiffuseSpecularMapMaterial.diffuse = currentText
    }

    Label {
        text: "specular: "
    }
    ComboBox {
        Layout.fillWidth: true
        model: [
            "assets/t1.png",
            "assets/t2.png",
            "assets/t3.png",
        ]
        onCurrentTextChanged: normalDiffuseSpecularMapMaterial.specular = currentText
    }

}

