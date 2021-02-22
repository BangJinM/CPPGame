#version 420 core
in vec2 v_texCoord;
in vec3 v_normal;
in vec3 v_FragPos;

uniform vec3 u_camera_pos;

uniform sampler2D diffuse;
uniform sampler2D specular;

struct LightProperty
{
    int type; // 4

    float constant;// 4
    float linear;// 4
    float quadratic;// 4

    float cutOff;// 4
    float outerCutOff;// 4
    vec3 position; // 16
    vec3 direction; // 16
  
    vec4 color; //16

    vec3 ambient;// 16
    vec3 diffuse;// 16
    vec3 specular;// 16
} ;

layout(std140) uniform LightInfo {
    LightProperty lights[100];
    int numsLight;
 } lightInfo;

out vec4 FragColor;

vec3 CalcDirLight(LightProperty light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    // 漫反射着色
    float diff = max(dot(normal, lightDir), 0.0);
    // 镜面光着色
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    // 合并结果
    vec3 ambient  = light.ambient  * vec3(texture(diffuse, v_texCoord));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(diffuse, v_texCoord));
    vec3 specular = light.specular * spec * vec3(texture(specular, v_texCoord));
    return (ambient + diffuse + specular);
}


// calculates the color when using a point light.
vec3 CalcPointLight(LightProperty light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    // combine results
    vec3 ambient = light.ambient * vec3(texture(diffuse, v_texCoord));
    vec3 diffuse = light.diffuse * diff * vec3(texture(diffuse, v_texCoord));
    vec3 specular = light.specular * spec * vec3(texture(specular, v_texCoord));
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}

// calculates the color when using a spot light.
vec3 CalcSpotLight(LightProperty light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    // spotlight intensity
    float theta = dot(lightDir, normalize(-light.direction)); 
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    // combine results
    vec3 ambient = light.ambient * vec3(texture(diffuse, v_texCoord));
    vec3 diffuse = light.diffuse * diff * vec3(texture(diffuse, v_texCoord));
    vec3 specular = light.specular * spec * vec3(texture(specular, v_texCoord));
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;
    return (ambient + diffuse + specular);
}

void main() {
    // properties
    vec3 norm = normalize(v_normal);
    vec3 viewDir = normalize(u_camera_pos - v_FragPos);

    vec3 result;
    for(int i = 0; i < lightInfo.numsLight; i++)
    {
      LightProperty l = lightInfo.lights[i];
      if(l.type == 4)
          result += CalcDirLight(l, norm, viewDir);
      else if(l.type == 3)
          result += CalcSpotLight(l, norm, v_FragPos, viewDir);    
      else if(l.type == 1)
          result += CalcPointLight(l, norm, v_FragPos, viewDir);    
    }
    FragColor = vec4(result, 1.0);
}