import QtQuick 2.0
import Qt3D 2.0
import Qt3D.Renderer 2.0

Entity {
    id: sceneRoot

    // c++ IF (property) c++->qml
    property alias origin:      camera.position
    property alias viewCenter:  camera.viewCenter
    property alias fieldOfView: camera.fieldOfView
    property alias aspectRatio: camera.aspectRatio
    property double altitude: 3.0

    Camera {
        id: camera
        projectionType: CameraLens.PerspectiveProjection
        fieldOfView: 45
        aspectRatio: 1.0
        nearPlane : 1.0
        farPlane : 5000.0
        position: Qt.vector3d( 0.0, 0.0, parent.altitude )
        upVector: Qt.vector3d( 0.0, 0.0, 1.0 )
        viewCenter: Qt.vector3d( 0.0, 1.0, parent.altitude )
    }

    Configuration  {
        controlledCamera: camera
    }

    components: [
        FrameGraph {
            activeFrameGraph: ForwardRenderer {
                clearColor: Qt.rgba(0, 0.5, 1, 1)
                camera: camera
            }
        }
    ]

    Entity {

        PhongMaterial {
            id: cMate
        }

        Transform {
            id: cTrans
            Translate {
                translation: Qt.vector3d(0, 0, 0)
            }
        }

        CuboidMesh {
            id: cMesh
            xExtent: 5000
            yExtent: 5000
        }
        components: [cTrans, cMate, cMesh]
    }

    function insertTarget(i)
    {
        console.log("insertTarget")
        targetModel.insert(i, {"x":0.0, "y":0.0})
    }
    function updateTarget(i, p)
    {
        console.log("updateTarget")
        targetModel.setProperty(i, "x", p.x)
        targetModel.setProperty(i, "y", p.y)
    }
    function removeTarget(i)
    {
        console.log("removeTarget")
        targetModel.remove(i)
    }

    ListModel {id: targetModel }

    NodeInstantiator {
        model: targetModel

        Entity {

            PhongMaterial {
                id: targetMaterial
            }

            SphereMesh {
                id: targetMesh
                radius: 3
            }

            Transform {
                id: targetTrans
                Translate {
                    translation: Qt.vector3d(x, y, 0)
                }

                Rotate {
                    id: targetRotate
                    axis: Qt.vector3d(0, 0, 1)
                }
            }
            components: [
                targetMesh,
                targetTrans,
                targetMaterial
            ]
        }
    }
}
