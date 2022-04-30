import Qt3D 2.0
import Qt3D.Renderer 2.0

Material {
    id: root

    property color kblue: Qt.rgba( 0.0, 0.0, 0.4, 1.0 )
    property color kyellow: Qt.rgba( 0.4, 0.4, 0.0, 1.0 )
    property color diffuse: Qt.rgba( 0.7, 0.7, 0.7, 1.0 )
    property color specular: Qt.rgba( 0.95, 0.95, 0.95, 1.0 )
    property real shininess: 150.0
    property real alpha: 0.25
    property real beta: 0.5

    parameters: [
        Parameter { name: "kblue"; value: Qt.vector3d(root.kblue.r, root.kblue.g, root.kblue.b) },
        Parameter { name: "kyellow"; value: Qt.vector3d(root.kyellow.r, root.kyellow.g, root.kyellow.b) },
        Parameter { name: "diffuse"; value: Qt.vector3d(root.diffuse.r, root.diffuse.g, root.diffuse.b) },
        Parameter { name: "specular"; value: Qt.vector3d(root.specular.r, root.specular.g, root.specular.b) },
        Parameter { name: "shininess"; value: root.shininess },
        Parameter { name: "alpha"; value: root.alpha },
        Parameter { name: "beta"; value: root.beta },
        Parameter { name: "lightPosition"; value: Qt.vector4d( 0.0, 0.0, 0.0, 1.0 ) },
        Parameter { name: "lightIntensity"; value: Qt.vector3d( 1.0, 1.0, 1.0 ) }
    ]

    effect: Effect {


        techniques: [
            // !! Important !!
            // At runtime, 'openGLFilter' will select the most appropriate QTechnique based on which graphics API versions are supported
            // See QTechnique API for more details
            // Example below shows 3 version supports ( OpenGL3.1 or above / OpenGL2.0 or above / OpenGL ES2.0 or above )
            // ex) https://github.com/qt/qt3d/blob/5.5/src/render/defaults/qphongmaterial.cpp

            Technique {
                openGLFilter {
                    api: OpenGLFilter.Desktop
                    profile: OpenGLFilter.None
                    majorVersion: 0
                    minorVersion: 0
                }

                renderPasses: [
                    RenderPass {

                        bindings: [
                            ParameterMapping { parameterName: "diffuse";  shaderVariableName: "kd"; bindingType: ParameterMapping.Uniform },
                            ParameterMapping { parameterName: "specular"; shaderVariableName: "ks"; bindingType: ParameterMapping.Uniform }
                        ]

                        shaderProgram: ShaderProgram {
                            vertexShaderCode:   loadSource("qrc:/shaders/CustomGooch.vert")
                            fragmentShaderCode: loadSource("qrc:/shaders/CustomGooch.frag")
                        }
                    }
                ]
            }
        ]
    }
}
