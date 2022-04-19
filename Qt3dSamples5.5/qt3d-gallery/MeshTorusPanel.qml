import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.4


GridLayout {
    columns: 2
    rowSpacing: 5
    columnSpacing: 5
    flow: GridLayout.LeftToRight

    Label {
        text: "radius: "+torusMesh.radius.toFixed(1)
    }
    Slider {
        value: 4
        stepSize: 0.1
        minimumValue: 1
        maximumValue: 20
        Layout.fillWidth: true
        onValueChanged: torusMesh.radius = this.value
    }

    Label {
        text: "minorRadius: "+torusMesh.minorRadius.toFixed(1)
    }
    Slider {
        value: 2
        stepSize: 0.1
        minimumValue: 1
        maximumValue: 20
        Layout.fillWidth: true
        onValueChanged: torusMesh.minorRadius = this.value
    }

    Label {
        text: "rings: "+torusMesh.rings
    }
    Slider {
        value: 16
        stepSize: 1
        minimumValue: 3
        maximumValue: 20
        Layout.fillWidth: true
        onValueChanged: torusMesh.rings = this.value
    }

    Label {
        text: "slices: "+torusMesh.slices
    }
    Slider {
        value: 16
        stepSize: 1
        minimumValue: 3
        maximumValue: 20
        Layout.fillWidth: true
        onValueChanged: torusMesh.slices = this.value
    }
}
