varying vec2 v_texCoord;
varying vec3 v_normal;
uniform sampler2D MainTextures;

out vec4 outColor;

void main()
{
    //texture(MainTextures, v_texCoord);
    outColor = texture(MainTextures, v_texCoord);//texture(MainTextures, v_texCoord);
}