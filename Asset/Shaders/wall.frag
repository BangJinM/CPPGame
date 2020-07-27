varying vec2 v_texCoord;
varying vec3 v_normal;
uniform sampler2D MainTextures;
uniform sampler2D texture2;
out vec4 outColor;

void main()
{
    //texture(MainTextures, v_texCoord);
    //outColor =texture(texture2, v_texCoord);
    outColor = mix(texture(MainTextures, v_texCoord), texture(texture2, v_texCoord), 0.2);
}