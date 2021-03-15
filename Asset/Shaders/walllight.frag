#version 420 core

in Value  
{  
    vec2 v_texCoord;
    vec3 v_normal;
    vec3 v_FragPos;
    vec3 v_camera_pos;
}inValue; 

uniform sampler2D shadowMap;
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
    
    mat4 u_projection_matrix;
    mat4 u_view_matrix;
} ;

layout(std140) uniform LightInfo {
    LightProperty lights[100];
    int numsLight;
 } lightInfo;


out vec4 FragColor;

float ShadowCalculation(LightProperty light)
{
    // perform perspective divide
    vec4 fragPosLightSpace = light.u_projection_matrix * light.u_view_matrix * vec4(inValue.v_FragPos,1.0);
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;
    // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture(shadowMap, projCoords.xy).r; 
    // get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;
    // check whether current frag pos is in shadow
    float shadow = currentDepth > closestDepth  ? 1.0 : 0.0;

    return shadow;
}

vec3 CalcDirLight(LightProperty light, vec3 normal, vec3 viewDir)
{
    vec3 color = texture(diffuse, inValue.v_texCoord).rgb;

    vec3 lightColor = vec3(0.3);
    // ambient
    vec3 ambient = 0.3 * color;
    // diffuse
    vec3 lightDir = normalize(light.position - inValue.v_FragPos);
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = diff * lightColor;
    // specular
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = 0.0;
    vec3 halfwayDir = normalize(lightDir + viewDir);  
    spec = pow(max(dot(normal, halfwayDir), 0.0), 64.0);
    vec3 specular = spec * lightColor;    
    // calculate shadow
    float shadow = ShadowCalculation(light);                      
    vec3 lighting = (ambient + (1.0 - shadow) * (diffuse + specular)) * color;    

    return lighting;
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
    vec3 ambient = light.ambient * vec3(texture(diffuse, inValue.v_texCoord));
    vec3 diffuse = light.diffuse * diff * vec3(texture(diffuse, inValue.v_texCoord));
    vec3 specular = light.specular * spec * vec3(texture(specular, inValue.v_texCoord));
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}

// calculates the color when using a spot light.
vec3 CalcSpotLight(LightProperty light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    // ambient
    vec3 ambient = light.ambient * texture(diffuse, inValue.v_texCoord).rgb;
    
    // diffuse 
    vec3 lightDir = normalize(light.position - fragPos);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * texture(diffuse, inValue.v_texCoord).rgb;  
    
    // specular
    vec3 reflectDir = reflect(-lightDir, normal);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = light.specular * spec * texture(specular, inValue.v_texCoord).rgb;  
    
    // spotlight (soft edges)
    float theta = dot(lightDir, normalize(-light.direction)); 
    float epsilon = (light.cutOff - light.outerCutOff);
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    diffuse  *= intensity;
    specular *= intensity;
    
    // attenuation
    float distance    = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    ambient  *= attenuation; 
    diffuse   *= attenuation;
    specular *= attenuation;   

    return ambient + diffuse + specular;
}

void main() {
    // properties
    vec3 normal = normalize(inValue.v_normal);
    vec3 viewDir = normalize(inValue.v_camera_pos - inValue.v_FragPos);
    vec3 result;
    for(int i = 0; i < lightInfo.numsLight; i++)
    {
      LightProperty l = lightInfo.lights[i];
      if(l.type == 4)
          result += CalcDirLight(l, normal, viewDir);
      else if(l.type == 3)
          result += CalcSpotLight(l, normal, inValue.v_FragPos, viewDir);    
      else if(l.type == 1)
          result += CalcPointLight(l, normal, inValue.v_FragPos, viewDir);    
    }
    FragColor = vec4(result, 1.0);
}