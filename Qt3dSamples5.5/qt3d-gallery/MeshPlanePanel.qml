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
        text: "height: "+planeMesh.height.toFixed(1)
    }
    Slider {
        value: 5
        stepSize: 0.1
        minimumValue: 1
        maximumValue: 20
        Layout.fillWidth: true
        onValueChanged: planeMesh.height = this.value
    }

    Label {
        text: "width: "+planeMesh.width.toFixed(1)
    }
    Slider {
        value: 5
        stepSize: 0.1
        minimumValue: 1
        maximumValue: 20
        Layout.fillWidth: true
        onValueChanged: planeMesh.width = this.value
    }


    Label {
        text: "mesh: "+planeMesh.meshResolution
    }
    Slider {
        value: 2
        stepSize: 1
        minimumValue: 1
        maximumValue: 20
        Layout.fillWidth: true
        onValueChanged: planeMesh.meshResolution = Qt.size(this.value, this.value)
    }

}

