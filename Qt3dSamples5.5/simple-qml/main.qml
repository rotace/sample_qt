import QtQuick 2.0
import Qt3D 2.0
import Qt3D.Renderer 2.0

Entity {
    id: sceneRoot

    property alias aspectRatio: camera.aspectRatio

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
            radius: 5
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



    NodeInstantiator {
        id: collection
        model: 3

        delegate: Entity {
            id: sphereEntity

            SphereMesh {
                id: sphereMesh
                radius: 1+index
            }

            Transform {
                id: sphereTransform
                Translate {
                    translation: Qt.vector3d(20, 0, 0)
                }

                Rotate {
                    id: sphereRotation
                    axis: Qt.vector3d(0, 1, 0)
                }
            }
            NumberAnimation {
                target: sphereRotation
                property: "angle"
                duration: 10000
                from: 60*index
                to: 360 + 60*index

                loops: Animation.Infinite
                running: true
            }

            components: [ sphereMesh, material, sphereTransform ]
        }

        onObjectAdded: console.log("object added")
        onObjectRemoved: console.log("object deleted")
    }
}
