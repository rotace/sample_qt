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

    MessageDialog {
        id: aboutDialog
        icon: StandardIcon.Information
        title: "About"
        text: "Qt3D Collection"
        informativeText: "This example demonstrates most of the available Qt3D Entities."
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
                text: "About..."
                onTriggered: aboutDialog.open()
            }
        }
    }



    RowLayout{
        spacing: 10
        anchors.margins: 10
        anchors.fill: parent

        TabView {
            id: tabView
            Layout.margins: 10
            Layout.fillHeight: true
            Layout.minimumWidth: 300

            property var mesh
            property var material
            property var trans
            function updateViewer() {
                viewerEntity.components = [this.mesh, material, transform]
            }

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
                                tabView.mesh = cylinderMesh
                                console.log("Not Implemented")
                                break;
                            case "CuboidMesh":
                                tabView.mesh = cuboidMesh
                                console.log("Not Implemented")
                                break;
                            case "SphereMesh":
                                tabView.mesh = sphereMesh
                                meshLoader.source = "MeshSpherePanel.qml"
                                break;
                            case "TorusMesh":
                                tabView.mesh = torusMesh
                                meshLoader.source = "MeshTorusPanel.qml"
                                break;
                            case "PlaneMesh":
                                tabView.mesh = planeMesh
                                console.log("Not Implemented")
                                break;
                            }
                            tabView.updateViewer()
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
                                tabView.material = phongMaterial
                                materialLoader.source = "MaterialPhongPanel.qml"
                                break;
                            case "GoochMaterial":
                                tabView.material = goochMaterial
                                console.log("Not Implemented")
                                break;
                            case "PerVertexColorMaterial":
                                tabView.material = perVertexColorMaterial
                                console.log("Not Implemented")
                                break;
                            case "DiffuseMapMaterial":
                                tabView.material = diffuseMapMaterial
                                console.log("Not Implemented")
                                break;
                            case "DiffuseSpecularMapMaterial":
                                tabView.material = diffuseSpecularMapMaterial
                                console.log("Not Implemented")
                                break;
                            case "NormalDiffuseMapMaterial":
                                tabView.material = normalDiffuseMapMaterial
                                console.log("Not Implemented")
                                break;
                            case "NormalDiffuseMapAlphaMaterial":
                                tabView.material = normalDiffuseMapAlphaMaterial
                                console.log("Not Implemented")
                                break;
                            case "NormalDiffuseSpecularMapMaterial":
                                tabView.material = normalDiffuseSpecularMapMaterial
                                console.log("Not Implemented")
                                break;
                            }
                            tabView.updateViewer()
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

        Scene3D {
            id: scene3d
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.minimumWidth: 400

            focus: true
            aspects: "input"

            Entity {
                id: sceneRoot

                Camera {
                    id: camera
                    projectionType: CameraLens.PerspectiveProjection
                    fieldOfView: 45
                    aspectRatio: scene3d.width/scene3d.height
                    nearPlane : 0.1
                    farPlane : 1000.0
                    position: Qt.vector3d( 0.0, 0.0, -40.0 )
                    upVector: Qt.vector3d( 0.0, 1.0, 0.0 )
                    viewCenter: Qt.vector3d( 0.0, 0.0, 0.0 )
                }

                Configuration  {
                    controlledCamera: camera
                }

                components: [
                    FrameGraph {
                        activeFrameGraph: Viewport {
                            id: viewport
                            rect: Qt.rect(0.0, 0.0, 1.0, 1.0)
                            clearColor: "transparent"

                            CameraSelector {
                                id : cameraSelector
                                camera: camera

                                ClearBuffer {
                                    buffers : ClearBuffer.ColorDepthBuffer
                                }
                            }
                        }
                    }
                ]


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


    }
}

