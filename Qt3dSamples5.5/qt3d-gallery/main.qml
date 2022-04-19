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
    property var trans
    function updateViewer() {
        viewerEntity.components = [this.mesh, this.material, this.trans]
    }

    MessageDialog {
        id: aboutDialog
        icon: StandardIcon.Information
        title: "About"
        text: "Qt3D Collection"
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
                    position: Qt.vector3d( 0.0, 0.0, -50.0 )
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
                PerVertexColorMaterial { id: perVertexColorMaterial }
                GoochMaterial { id: goochMaterial }
                PhongMaterial { id: phongMaterial }
                DiffuseMapMaterial { id: diffuseMapMaterial }
                DiffuseSpecularMapMaterial { id: diffuseSpecularMapMaterial }
                NormalDiffuseMapMaterial { id: normalDiffuseMapMaterial }
                NormalDiffuseMapAlphaMaterial { id: normalDiffuseMapAlphaMaterial }
                NormalDiffuseSpecularMapMaterial { id: normalDiffuseSpecularMapMaterial }

                // Transform
                Transform {
                    id: transform
                    Translate { translation: Qt.vector3d(0, 0, 0) }
//                    Scale { scale3D: Qt.vector3d(1.5, 1, 0.5) }
//                    Rotate {
//                        angle: 45
//                        axis: Qt.vector3d(1, 0, 0)
//                    }
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
//                            "CylinderMesh",
//                            "CuboidMesh",
                            "SphereMesh",
                            "TorusMesh",
//                            "PlaneMesh",
                        ]
                        onCurrentTextChanged: {
                            switch(currentText) {
                            case "CylinderMesh":
                                root.mesh = cylinderMesh
                                console.log("Not Implemented")
                                break;
                            case "CuboidMesh":
                                root.mesh = cuboidMesh
                                console.log("Not Implemented")
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
                                console.log("Not Implemented")
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
//                            "GoochMaterial",
//                            "PerVertexColorMaterial",
//                            "DiffuseMapMaterial",
//                            "DiffuseSpecularMapMaterial",
//                            "NormalDiffuseMapMaterial",
//                            "NormalDiffuseMapAlphaMaterial",
//                            "NormalDiffuseSpecularMapMaterial",
                        ]
                        onCurrentTextChanged: {
                            switch(currentText) {
                            case "PhongMaterial":
                                root.material = phongMaterial
                                materialLoader.source = "MaterialPhongPanel.qml"
                                break;
                            case "GoochMaterial":
                                root.material = goochMaterial
                                console.log("Not Implemented")
                                break;
                            case "PerVertexColorMaterial":
                                root.material = perVertexColorMaterial
                                console.log("Not Implemented")
                                break;
                            case "DiffuseMapMaterial":
                                root.material = diffuseMapMaterial
                                console.log("Not Implemented")
                                break;
                            case "DiffuseSpecularMapMaterial":
                                root.material = diffuseSpecularMapMaterial
                                console.log("Not Implemented")
                                break;
                            case "NormalDiffuseMapMaterial":
                                root.material = normalDiffuseMapMaterial
                                console.log("Not Implemented")
                                break;
                            case "NormalDiffuseMapAlphaMaterial":
                                root.material = normalDiffuseMapAlphaMaterial
                                console.log("Not Implemented")
                                break;
                            case "NormalDiffuseSpecularMapMaterial":
                                root.material = normalDiffuseSpecularMapMaterial
                                console.log("Not Implemented")
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

            }
        }

    }
}

