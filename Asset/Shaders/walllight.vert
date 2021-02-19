#version 420 core
in vec3 a_position;
in vec3 a_normal;
in vec2 a_texCoord;

uniform mat4 u_model_matrix;
uniform mat4 u_view_matrix;
uniform mat4 u_projection_matrix;

out vec2 v_texCoord;
out vec3 v_normal;
out vec3 v_FragPos;

void main() {
  gl_Position = u_projection_matrix * u_view_matrix * u_model_matrix * vec4(a_position, 1);
  v_FragPos = vec3(u_model_matrix * vec4(a_position, 1));
  v_texCoord = a_texCoord;
  v_normal = a_normal;
}
