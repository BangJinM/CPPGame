#version 420 core
in vec3 a_position;

layout(std140) uniform ModelInfos{ 
    mat4 u_model_matrix;
} modelInfos;

uniform mat4 projectionMatrix;

void main()
{
    gl_Position = projectionMatrix * modelInfos.u_model_matrix * vec4(a_position, 1.0);
}