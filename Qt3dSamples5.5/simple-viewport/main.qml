import QtQuick 2.0
import Qt3D 2.0
import Qt3D.Renderer 2.0

Entity {
    id : rootNode

    property alias aspectRatio: cameraLens.aspectRatio

    CameraLens {
        id : cameraLens
        projectionType: CameraLens.PerspectiveProjection
        fieldOfView: 45
        nearPlane : 0.01
        farPlane : 1000.0
    }

    Entity {
        id : sceneRoot
        components: [frameGraph]
        property real rotationAngle : 0

        SequentialAnimation {
            running : true
            loops: Animation.Infinite
            NumberAnimation {target : sceneRoot; property : "rotationAngle"; to : 360; duration : 2000;}
        }

        FrameGraph {
            id : frameGraph

            Viewport {
                rect: Qt.rect(0, 0, 1, 1)
                clearColor: "white"

                ClearBuffer {
                    buffers : ClearBuffer.ColorDepthBuffer
                }

                Viewport {
                    rect : Qt.rect(0, 0, 0.5, 0.5)
                    CameraSelector { camera : cameraViewport1}
                }

                Viewport {
                    rect : Qt.rect(0.5, 0, 0.5, 0.5)
                    CameraSelector { camera : cameraViewport2}
                }

                Viewport {
                    rect : Qt.rect(0, 0.5, 0.5, 0.5)
                    CameraSelector { camera : cameraViewport3}
                }

                Viewport {
                    rect : Qt.rect(0.5, 0.5, 0.5, 0.5)
                    CameraSelector { camera : cameraViewport4}
                }

            }
        }

        Entity {
            id : cameraViewport1
            property Transform transform : Transform {
                LookAt {
                    position: Qt.vector3d( 0.0, 0.0, -20.0 )
                    upVector: Qt.vector3d( 0.0, 1.0, 0.0 )
                    viewCenter: Qt.vector3d( 0.0, 0.0, 0.0 )
                }
            }
            components : [cameraLens, transform]
        }

        Entity {
            id : cameraViewport2
            property Transform transform : Transform {
                Rotate {
                    angle : sceneRoot.rotationAngle
                    axis : Qt.vector3d(0, 1, 0)
                }
                LookAt {
                    position: Qt.vector3d( 0.0, 0.0, 20.0 )
                    upVector: Qt.vector3d( 0.0, 1.0, 0.0 )
                    viewCenter: Qt.vector3d( 0.0, 0.0, 0.0 )
                }
            }
            components : [cameraLens, transform]
        }

        Entity {
            id : cameraViewport3
            property Transform transform : Transform {
                LookAt {
                    position: Qt.vector3d( 0.0, 30.0, 30.0 )
                    upVector: Qt.vector3d( 0.0, 1.0, 0.0 )
                    viewCenter: Qt.vector3d( 0.0, 0.0, 0.0 )
                }
            }
            components : [cameraLens, transform]
        }

        Entity {
            id : cameraViewport4
            property Transform transform : Transform {
                LookAt {
                    position: Qt.vector3d( 0.0, 15.0, 20.0 )
                    upVector: Qt.vector3d( 0.0, 0.0, 1.0 )
                    viewCenter: Qt.vector3d( 0.0, 0.0, 0.0 )
                }
            }
            components : [cameraLens, transform]
        }

        Entity {
            components : [
                Transform {
                    Rotate {
                        angle : -sceneRoot.rotationAngle
                        axis : Qt.vector3d(0, 0, 1)
                    }
                },
                CylinderMesh {length:5; radius:5},
                PhongMaterial {}
            ]
        }
    }

}
