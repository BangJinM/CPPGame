attribute vec3 a_position;
attribute vec2 a_texCoord;

uniform mat4 model;
uniform mat4 view;

varying vec2 v_texCoord;

void main()
{
    gl_Position = vec4( a_position.xy,0, 1);
    v_texCoord = a_texCoord;
}
