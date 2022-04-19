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
        text: "alpha: "+goochMaterial.alpha.toFixed(2)
    }
    Slider {
        value: 0.25
        stepSize: 0.05
        minimumValue: 0
        maximumValue: 1
        Layout.fillWidth: true
        onValueChanged: goochMaterial.alpha = this.value
    }

    Label {
        text: "beta: "+goochMaterial.beta.toFixed(2)
    }
    Slider {
        value: 0.5
        stepSize: 0.05
        minimumValue: 0
        maximumValue: 1
        Layout.fillWidth: true
        onValueChanged: goochMaterial.beta = this.value
    }

    Label {
        text: "shininess: "+parseInt(goochMaterial.shininess)
    }
    Slider {
        value: 100
        minimumValue: 0
        maximumValue: 100
        Layout.fillWidth: true
        onValueChanged: goochMaterial.shininess = this.value
    }

    Label {
        text: "diffuse: "
    }
    Button {
        style: ButtonStyle { label: Rectangle { color: goochMaterial.diffuse } }
        onClicked: colorDialog.open()
        Layout.fillWidth: true
        property ColorDialog colorDialog: ColorDialog {
            title: "Diffuse Color"
            onAccepted: goochMaterial.diffuse = this.color
        }
    }

    Label {
        text: "specular: "
    }
    Button {
        style: ButtonStyle { label: Rectangle { color: goochMaterial.specular } }
        onClicked: colorDialog.open()
        Layout.fillWidth: true
        property ColorDialog colorDialog: ColorDialog {
            title: "Specular Color"
            onAccepted: goochMaterial.specular = this.color
        }
    }

}

