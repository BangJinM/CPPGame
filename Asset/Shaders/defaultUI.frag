varying vec2 v_texCoord;
uniform sampler2D MainTextures;
out vec4 outColor;

void main()
{
    outColor = texture(MainTextures, v_texCoord);
}