#version 420 core
in vec3 a_position;

uniform mat4 projection;
uniform mat4 view;

out vec3 TexCoords;

void main() {
  TexCoords = a_position;
  vec4 pos = projection * view * vec4(a_position, 1.0);
  gl_Position = pos.xyww;
}