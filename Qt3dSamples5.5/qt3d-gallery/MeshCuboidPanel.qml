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
        text: "xExtent: "+cuboidMesh.xExtent.toFixed(1)
    }
    Slider {
        value: 5
        stepSize: 0.1
        minimumValue: 1
        maximumValue: 20
        Layout.fillWidth: true
        onValueChanged: cuboidMesh.xExtent = this.value
    }

    Label {
        text: "yExtent: "+cuboidMesh.yExtent.toFixed(1)
    }
    Slider {
        value: 5
        stepSize: 0.1
        minimumValue: 1
        maximumValue: 20
        Layout.fillWidth: true
        onValueChanged: cuboidMesh.yExtent = this.value
    }

    Label {
        text: "zExtent: "+cuboidMesh.zExtent.toFixed(1)
    }
    Slider {
        value: 5
        stepSize: 0.1
        minimumValue: 1
        maximumValue: 20
        Layout.fillWidth: true
        onValueChanged: cuboidMesh.zExtent = this.value
    }

    Label {
        text: "xyMesh: "+cuboidMesh.xyMeshResolution
    }
    Slider {
        value: 2
        stepSize: 1
        minimumValue: 1
        maximumValue: 20
        Layout.fillWidth: true
        onValueChanged: cuboidMesh.xyMeshResolution = Qt.size(this.value, this.value)
    }

    Label {
        text: "yzMesh: "+cuboidMesh.yzMeshResolution
    }
    Slider {
        value: 2
        stepSize: 1
        minimumValue: 1
        maximumValue: 20
        Layout.fillWidth: true
        onValueChanged: cuboidMesh.yzMeshResolution = Qt.size(this.value, this.value)
    }

    Label {
        text: "xzMesh: "+cuboidMesh.xzMeshResolution
    }
    Slider {
        value: 2
        stepSize: 1
        minimumValue: 1
        maximumValue: 20
        Layout.fillWidth: true
        onValueChanged: cuboidMesh.xzMeshResolution = Qt.size(this.value, this.value)
    }

}

