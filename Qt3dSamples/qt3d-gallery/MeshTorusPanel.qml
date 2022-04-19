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
        text: "radius: "+parseInt(radiusSlider.value)
    }
    Slider {
        id: radiusSlider
        value: 4
        stepSize: 1
        minimumValue: 1
        maximumValue: 20
        Layout.fillWidth: true
        onValueChanged: torusMesh.radius = this.value
    }

    Label {
        text: "minorRadius: "+parseInt(minorRadiusSlider.value)
    }
    Slider {
        id: minorRadiusSlider
        value: 2
        stepSize: 1
        minimumValue: 1
        maximumValue: 20
        Layout.fillWidth: true
        onValueChanged: torusMesh.minorRadius = this.value
    }

    Label {
        text: "rings: "+parseInt(ringsSlider.value)
    }
    Slider {
        id: ringsSlider
        value: 20
        stepSize: 1
        minimumValue: 3
        maximumValue: 20
        Layout.fillWidth: true
        onValueChanged: torusMesh.rings = this.value
    }

    Label {
        text: "slices: "+parseInt(slicesSlider.value)
    }
    Slider {
        id: slicesSlider
        value: 20
        stepSize: 1
        minimumValue: 3
        maximumValue: 20
        Layout.fillWidth: true
        onValueChanged: torusMesh.slices = this.value
    }
}
