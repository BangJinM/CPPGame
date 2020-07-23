uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

varying vec4 v_fragmentColor;
varying vec2 v_texCoord;

uniform sampler2D MainTextures;

void main()
{
    gl_Position = projection * view * model *vec4( a_position, 1);
    v_fragmentColor = vec4( a_normal, 1.0f);
    v_texCoord = a_texCoord;
}