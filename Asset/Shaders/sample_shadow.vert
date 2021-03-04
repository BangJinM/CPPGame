#version 420 core
in vec3 a_position;

layout(std140) uniform ModelInfos{ 
    mat4 u_model_matrix;
} modelInfos;

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

uniform int layer_index;

void main()
{
    gl_Position = lightInfo.lights[layer_index].u_projection_matrix* lightInfo.lights[layer_index].u_view_matrix * modelInfos.u_model_matrix * vec4(a_position, 1.0);
}