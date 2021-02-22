#version 420 core
in vec3 a_position;

uniform mat4 u_model_matrix;
uniform mat4 u_view_matrix;
uniform mat4 u_projection_matrix;

void main()
{
    gl_Position = u_projection_matrix * u_view_matrix * u_model_matrix * vec4(a_position, 1.0);
}