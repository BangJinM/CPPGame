#version 420 core
in vec3 a_position;
in vec3 a_normal;
in vec2 a_texCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 v_texCoord;
out vec3 v_normal;
out vec3 v_FragPos;

void main() {
  gl_Position = projection * view * model * vec4(a_position, 1);
  v_FragPos = vec3(model * vec4(a_position, 1));
  v_texCoord = a_texCoord;
  v_normal = a_normal;
}
