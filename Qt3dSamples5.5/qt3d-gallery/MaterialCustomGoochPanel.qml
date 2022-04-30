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
        text: "alpha: "+customGoochMaterial.alpha.toFixed(2)
    }
    Slider {
        value: 0.25
        stepSize: 0.05
        minimumValue: 0
        maximumValue: 1
        Layout.fillWidth: true
        onValueChanged: customGoochMaterial.alpha = this.value
    }

    Label {
        text: "beta: "+customGoochMaterial.beta.toFixed(2)
    }
    Slider {
        value: 0.5
        stepSize: 0.05
        minimumValue: 0
        maximumValue: 1
        Layout.fillWidth: true
        onValueChanged: customGoochMaterial.beta = this.value
    }

    Label {
        text: "shininess: "+parseInt(customGoochMaterial.shininess)
    }
    Slider {
        value: 100
        minimumValue: 0
        maximumValue: 100
        Layout.fillWidth: true
        onValueChanged: customGoochMaterial.shininess = this.value
    }

    Label {
        text: "cool: "
    }
    Button {
        style: ButtonStyle { label: Rectangle { color: customGoochMaterial.kblue } }
        onClicked: colorDialog.open()
        Layout.fillWidth: true
        property ColorDialog colorDialog: ColorDialog {
            title: "Cool Color"
            onAccepted: customGoochMaterial.kblue = this.color
        }
    }

    Label {
        text: "warm: "
    }
    Button {
        style: ButtonStyle { label: Rectangle { color: customGoochMaterial.kyellow } }
        onClicked: colorDialog.open()
        Layout.fillWidth: true
        property ColorDialog colorDialog: ColorDialog {
            title: "Warm Color"
            onAccepted: customGoochMaterial.kyellow = this.color
        }
    }

    Label {
        text: "diffuse: "
    }
    Button {
        style: ButtonStyle { label: Rectangle { color: customGoochMaterial.diffuse } }
        onClicked: colorDialog.open()
        Layout.fillWidth: true
        property ColorDialog colorDialog: ColorDialog {
            title: "Diffuse Color"
            onAccepted: customGoochMaterial.diffuse = this.color
        }
    }

    Label {
        text: "specular: "
    }
    Button {
        style: ButtonStyle { label: Rectangle { color: customGoochMaterial.specular } }
        onClicked: colorDialog.open()
        Layout.fillWidth: true
        property ColorDialog colorDialog: ColorDialog {
            title: "Specular Color"
            onAccepted: customGoochMaterial.specular = this.color
        }
    }

}

