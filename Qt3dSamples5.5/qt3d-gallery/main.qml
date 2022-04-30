import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.4
import QtQuick.Scene3D 2.0
import Qt3D 2.0
import Qt3D.Renderer 2.0

ApplicationWindow {
    id: root
    visible: true
    title: "Qt3D Gallery"
    width: 640
    height: 480

    property var mesh
    property var material
    function updateViewer() {
        viewerEntity.components = [this.mesh, this.material, transform]
    }
    function updateScale(x, y, z) {
        scale.scale3D = Qt.vector3d(x, y, z)
    }


    MessageDialog {
        id: aboutDialog
        icon: StandardIcon.Information
        title: "About"
        text: "Qt3D Gallery"
        informativeText: "This example demonstrates most of the available Qt3D Entities."
    }

    ColorDialog {
        id: colorDialog
        title: "Please choose a color"
        onAccepted: {
            console.log("You chose: " + colorDialog.color)
        }
        onRejected: {
            console.log("Canceled")
        }
    }

    Action {
        id: copyAction
        text: "&Copy"
        shortcut: StandardKey.Copy
        iconName: "edit-copy"
        enabled: (!!activeFocusItem && !!activeFocusItem["copy"])
        onTriggered: activeFocusItem.copy()
    }

    Action {
        id: cutAction
        text: "Cu&t"
        shortcut: StandardKey.Cut
        iconName: "edit-cut"
        enabled: (!!activeFocusItem && !!activeFocusItem["cut"])
        onTriggered: activeFocusItem.cut()
    }

    Action {
        id: pasteAction
        text: "&Paste"
        shortcut: StandardKey.Paste
        iconName: "edit-paste"
        enabled: (!!activeFocusItem && !!activeFocusItem["paste"])
        onTriggered: activeFocusItem.paste()
    }

    toolBar: ToolBar {
        RowLayout {
            anchors.fill: parent
            anchors.margins: spacing
            Button {
                text: "Info"
                onClicked: {
                    console.log("Scen3D:", scene3d.width, scene3d.height)
                    console.log("TabView", tabView.width, tabView.height)
                    console.log("Camera View Center:", camera.viewCenter)
                    console.log("Scale:", scale.scale)
                }
            }
            Item { Layout.fillWidth: true }
        }
    }

    menuBar: MenuBar {
        Menu {
            title: "&File"
            MenuItem {
                text: "E&xit"
                shortcut: StandardKey.Quit
                onTriggered: Qt.quit()
            }
        }
        Menu {
            title: "&Edit"
            MenuItem { action: cutAction }
            MenuItem { action: copyAction }
            MenuItem { action: pasteAction }
        }
        Menu {
            title: "&Help"
            MenuItem {
                text: "Color"
                onTriggered: colorDialog.open()
            }
            MenuItem {
                text: "About..."
                onTriggered: aboutDialog.open()
            }
        }
    }

    RowLayout{
        spacing: 10
        anchors.margins: 10
        anchors.fill: parent

        Scene3D {
            id: scene3d
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.minimumWidth: 500

            focus: true
            aspects: "input"

            Entity {
                id: sceneRoot

                Camera{
                    id: camera
                    projectionType: CameraLens.PerspectiveProjection
                    fieldOfView: 45
                    aspectRatio: root.width/root.height
                    nearPlane : 0.1
                    farPlane : 1000.0
                    position: Qt.vector3d( 0.0, +20, -50.0 )
                    upVector: Qt.vector3d( 0.0, 1.0, 0.0 )
                    viewCenter: Qt.vector3d( 0.0, 0.0, 0.0 )
                }

                Configuration  { controlledCamera: camera }
                FrameGraph { activeFrameGraph: ForwardRenderer { camera: camera } }

                // Mesh
                CylinderMesh { id: cylinderMesh }
                CuboidMesh { id: cuboidMesh }
                SphereMesh { id: sphereMesh }
                TorusMesh { id: torusMesh }
                PlaneMesh { id: planeMesh }

                // Material
                GoochMaterial { id: goochMaterial }
                PhongMaterial { id: phongMaterial }
                DiffuseMapMaterial { id: diffuseMapMaterial }
                DiffuseSpecularMapMaterial { id: diffuseSpecularMapMaterial }
                NormalDiffuseMapMaterial { id: normalDiffuseMapMaterial }
                NormalDiffuseMapAlphaMaterial { id: normalDiffuseMapAlphaMaterial }
                NormalDiffuseSpecularMapMaterial { id: normalDiffuseSpecularMapMaterial }
                PerVertexColorMaterial { id: perVertexColorMaterial }
                CustomPhongMaterial{ id: customPhongMaterial }
                CustomGoochMaterial{ id: customGoochMaterial }

                // Transform
                Transform {
                    id: transform
                    Translate { translation: Qt.vector3d(0, 0, 0) }
                    Scale { id: scale }
                    Rotate { id: rotate; axis: Qt.vector3d(0, 1, 0) }
                }

                SequentialAnimation {
                    running : true
                    loops: Animation.Infinite
                    NumberAnimation {target : rotate; property : "angle"; to : 360; duration : 10000;}
                }

                Entity {
                    id: viewerEntity
                }
            }
        }


        TabView {
            id: tabView
            Layout.margins: 10
            Layout.fillHeight: true
            Layout.minimumWidth: 250

            Tab {
                title: "Mesh"
                anchors.topMargin: 5
                anchors.leftMargin: 5
                anchors.rightMargin: 5

                ColumnLayout {

                    ComboBox {
                        Layout.fillWidth: true
                        model: [
                            "SphereMesh",
                            "CylinderMesh",
                            "CuboidMesh",
                            "TorusMesh",
                            "PlaneMesh",
                        ]
                        onCurrentTextChanged: {
                            switch(currentText) {
                            case "CylinderMesh":
                                root.mesh = cylinderMesh
                                meshLoader.source = "MeshCylinderPanel.qml"
                                break;
                            case "CuboidMesh":
                                root.mesh = cuboidMesh
                                meshLoader.source = "MeshCuboidPanel.qml"
                                break;
                            case "SphereMesh":
                                root.mesh = sphereMesh
                                meshLoader.source = "MeshSpherePanel.qml"
                                break;
                            case "TorusMesh":
                                root.mesh = torusMesh
                                meshLoader.source = "MeshTorusPanel.qml"
                                break;
                            case "PlaneMesh":
                                root.mesh = planeMesh
                                meshLoader.source = "MeshPlanePanel.qml"
                                break;
                            }
                            root.updateViewer()
                        }
                    }
                    Item {
                        id: meshPage
                        Layout.fillWidth: true
                        height: meshLoader.height

                        Loader {
                            id: meshLoader
                            width: meshPage.width
                        }
                    }
                    Item {
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                    }
                }


            }
            Tab {
                title: "Material"
                anchors.topMargin: 5
                anchors.leftMargin: 5
                anchors.rightMargin: 5

                ColumnLayout {

                    ComboBox {
                        Layout.fillWidth: true
                        model: [
                            "PhongMaterial",
                            "GoochMaterial",
                            "DiffuseMapMaterial",
                            "DiffuseSpecularMapMaterial",
                            "NormalDiffuseMapMaterial",
                            "NormalDiffuseMapAlphaMaterial",
                            "NormalDiffuseSpecularMapMaterial",
                            "CustomPhongMaterial",
                            "CustomGoochMaterial",
//                            "PerVertexColorMaterial",
                        ]
                        onCurrentTextChanged: {
                            switch(currentText) {
                            case "PhongMaterial":
                                root.material = phongMaterial
                                materialLoader.source = "MaterialPhongPanel.qml"
                                break;
                            case "GoochMaterial":
                                root.material = goochMaterial
                                materialLoader.source = "MaterialGoochPanel.qml"
                                break;
                            case "DiffuseMapMaterial":
                                root.material = diffuseMapMaterial
                                materialLoader.source = "MaterialDiffuseMapPanel.qml"
                                break;
                            case "DiffuseSpecularMapMaterial":
                                root.material = diffuseSpecularMapMaterial
                                materialLoader.source = "MaterialDiffuseSpecularMapPanel.qml"
                                break;
                            case "NormalDiffuseMapMaterial":
                                root.material = normalDiffuseMapMaterial
                                materialLoader.source = "MaterialNormalDiffuseMapPanel.qml"
                                break;
                            case "NormalDiffuseMapAlphaMaterial":
                                root.material = normalDiffuseMapAlphaMaterial
                                materialLoader.source = "MaterialNormalDiffuseMapAlphaPanel.qml"
                                break;
                            case "NormalDiffuseSpecularMapMaterial":
                                root.material = normalDiffuseSpecularMapMaterial
                                materialLoader.source = "MaterialNormalDiffuseSpecularMapPanel.qml"
                                break;
                            case "PerVertexColorMaterial":
                                root.material = perVertexColorMaterial
                                console.log("Not Implemented")
                                break;
                            case "CustomPhongMaterial":
                                root.material = customPhongMaterial
                                materialLoader.source = "MaterialCustomPhongPanel.qml"
                                break;
                            case "CustomGoochMaterial":
                                root.material = customGoochMaterial
                                materialLoader.source = "MaterialCustomGoochPanel.qml"
                                break;
                            }
                            root.updateViewer()
                        }
                    }
                    Item {
                        id: materialPage
                        Layout.fillWidth: true
                        height: materialLoader.height

                        Loader {
                            id: materialLoader
                            width: materialPage.width
                        }
                    }
                    Item {
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                    }
                }

            }

            Tab {
                title: "Transform"
                anchors.topMargin: 5
                anchors.leftMargin: 5
                anchors.rightMargin: 5

                GridLayout {
                    columns: 2
                    rowSpacing: 5
                    columnSpacing: 5
                    flow: GridLayout.LeftToRight

                    Label {
                        text: "scaleX: "+scaleX.value.toFixed(1)
                    }
                    Slider {
                        id: scaleX
                        value: 1
                        stepSize: 0.1
                        minimumValue: 0.1
                        maximumValue: 10
                        Layout.fillWidth: true
                        onValueChanged: root.updateScale(scaleX.value, scaleY.value, scaleZ.value)
                    }

                    Label {
                        text: "scaleY: "+scaleY.value.toFixed(1)
                    }
                    Slider {
                        id: scaleY
                        value: 1
                        stepSize: 0.1
                        minimumValue: 0.1
                        maximumValue: 10
                        Layout.fillWidth: true
                        onValueChanged: root.updateScale(scaleX.value, scaleY.value, scaleZ.value)
                    }

                    Label {
                        text: "scaleZ: "+scaleZ.value.toFixed(1)
                    }
                    Slider {
                        id: scaleZ
                        value: 1
                        stepSize: 0.1
                        minimumValue: 0.1
                        maximumValue: 10
                        Layout.fillWidth: true
                        onValueChanged: root.updateScale(scaleX.value, scaleY.value, scaleZ.value)
                    }
                    Item {
                        Layout.columnSpan: 2
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                    }
                }

            }
        }

    }
}

