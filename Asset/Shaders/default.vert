attribute vec3 a_position;
attribute vec2 a_texCoord;
attribute vec4 a_color;
attribute vec3 a_normal;

#ifdef GL_ES
varying lowp vec4 v_fragmentColor;
varying mediump vec2 v_texCoord;
#else
varying vec4 v_fragmentColor;
varying vec2 v_texCoord;
#endif

void main()
{
    gl_Position = vec4( a_position, 1);
    v_fragmentColor = vec4(a_normal, 1.0f);
    v_texCoord = a_texCoord;
}