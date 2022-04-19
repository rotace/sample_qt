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
        value: 5
        stepSize: 1
        minimumValue: 1
        maximumValue: 20
        Layout.fillWidth: true
        onValueChanged: sphereMesh.radius = this.value
    }

    Label {
        text: "rings: "+parseInt(ringsSlider.value)
    }
    Slider {
        id: ringsSlider
        value: 10
        stepSize: 1
        minimumValue: 3
        maximumValue: 20
        Layout.fillWidth: true
        onValueChanged: sphereMesh.rings = this.value
    }

    Label {
        text: "slices: "+parseInt(slicesSlider.value)
    }
    Slider {
        id: slicesSlider
        value: 10
        stepSize: 1
        minimumValue: 3
        maximumValue: 20
        Layout.fillWidth: true
        onValueChanged: sphereMesh.slices = this.value
    }
}

