import Qt3D 2.0
import Qt3D.Renderer 2.0
import QtQuick 2.5 as QQ

Entity {
    id: sceneRoot
    // c++ IF (signal)   qml->c++ (not used)
    signal signalOccured(string message);
    // c++ IF (property) c++->qml
    property int radius: 5
    // c++ IF (function) c++->qml
    function echo(text)
    {
        console.log("echo:", text)
        return text;
    }

    Camera {
        id: camera
        projectionType: CameraLens.PerspectiveProjection
        fieldOfView: 45
        aspectRatio: 16/9
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
            activeFrameGraph: ForwardRenderer {
                clearColor: Qt.rgba(0, 0.5, 1, 1)
                camera: camera
            }
        }
    ]

    PhongMaterial {
        id: material
    }

    Entity {
        id: torusEntity

        TorusMesh {
            id: torusMesh
            radius: sceneRoot.radius
            minorRadius: 1
            rings: 100
            slices: 20
        }

        Transform {
            id: torusTransform
            Scale { scale3D: Qt.vector3d(1.5, 1, 0.5) }
            Rotate {
                angle: 45
                axis: Qt.vector3d(1, 0, 0)
            }
        }

        components: [ torusMesh, material, torusTransform ]
    }



    Entity {
        id: sphereEntity

        SphereMesh {
            id: sphereMesh
            radius: sceneRoot.radius
        }

        Transform {
            id: sphereTransform
            Translate {
                translation: Qt.vector3d(20+sceneRoot.radius, 0, 0)
            }

            Rotate {
                id: sphereRotation
                axis: Qt.vector3d(0, 1, 0)
            }
        }

        QQ.NumberAnimation {
            target: sphereRotation
            property: "angle"
            duration: 10000
            from: 0
            to: 360

            loops: QQ.Animation.Infinite
            running: true
        }

        components: [ sphereMesh, material, sphereTransform ]
    }
}
