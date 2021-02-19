#version 420 core
struct DirLight {
  vec3 direction;

  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
};

in vec2 v_texCoord;
in vec3 v_normal;
in vec3 v_FragPos;

uniform sampler2D diffuse;
uniform sampler2D specular;

uniform DirLight light;

uniform vec3 u_camera_pos;

out vec4 FragColor;

void main() {

  // ambient
  vec3 ambient = light.ambient * texture(diffuse, v_texCoord).rgb;

  // diffuse
  vec3 norm = normalize(v_normal);
  vec3 lightDir = normalize(-light.direction);
  float diff = max(dot(norm, lightDir), 0.0);
  vec3 diffuse = light.diffuse * diff * texture(diffuse, v_texCoord).rgb;

  // specular
  vec3 viewDir = normalize(u_camera_pos - v_FragPos);
  vec3 reflectDir = reflect(-lightDir, norm);
  float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
  vec3 specular = light.specular * spec * texture(specular, v_texCoord).rgb;

  vec3 result = ambient + diffuse + specular;
  FragColor = vec4(result, 1.0);
}