attribute vec3 a_position;
attribute vec2 a_texCoord;
attribute vec4 a_color;
attribute vec3 a_normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

varying vec4 v_fragmentColor;
varying vec2 v_texCoord;

void main()
{
    // gl_Position = projection * view * model * vec4(a_position, 1.0f);
    gl_Position = view *model *vec4( a_position, 1);
    v_fragmentColor = vec4( a_normal, 1.0f);
    v_texCoord = a_texCoord;
}