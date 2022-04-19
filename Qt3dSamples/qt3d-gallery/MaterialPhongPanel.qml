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
        text: "shininess: "+parseInt(shininessSlider.value)
    }
    Slider {
        id: shininessSlider
        value: 18
        minimumValue: 1
        maximumValue: 20
        Layout.fillWidth: true
        onValueChanged: phongMaterial.shininess = this.value
    }
}

