#version 420 core
in vec3 a_position;

uniform mat4 u_projection_matrix;
uniform mat4 u_view_matrix;

out vec3 TexCoords;

void main() {
  TexCoords = a_position;
  vec4 pos = u_projection_matrix * u_view_matrix * vec4(a_position, 1.0);
  gl_Position = pos.xyww;
}