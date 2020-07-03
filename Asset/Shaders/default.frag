#ifdef GL_ES
precision lowp float;
#endif

varying vec4 v_fragmentColor;
varying vec2 v_texCoord;

out vec4 outColor;

void main()
{
    outColor = vec4(1.f, 1.f, 1.f, 1.f);
}