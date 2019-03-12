precision mediump float;
uniform vec3 u_LightPos0;
uniform vec3 u_LightColor0;
uniform vec4 u_camPos;
uniform sampler2D u_Texture0;
varying vec3 FragPos;
varying vec3 Normal;
varying vec2 textCoord;
void main()
{
//declare object color
vec3 objectColor = vec3(texture2D(u_Texture0, textCoord));
//declare ambient Strength
float ambientStrength = 0.5;
float attenuation = 1.0/pow(distance(u_LightPos0, FragPos), 2.0);
//calculate ambient color
vec3 ambient = ambientStrength* u_LightColor0;
//calculate light vector
vec3 lightDir = normalize(u_LightPos0 - FragPos);
vec3 norm = normalize(Normal);
//calculate diffuse light
float diff = max(dot(norm, lightDir), 0.0);
vec3 diffuse = diff* u_LightColor0*attenuation;
//calculate specular light
float specularStrength = 0.5;
vec3 viewDir = normalize(u_camPos.xyz- FragPos);
vec3 reflectDir = reflect(-lightDir, norm);
float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
vec3 specular = specularStrength* spec* u_LightColor0;
//calculate final color
float weight = 0.5;
vec3 resultColor = (ambient* weight+ diffuse*(1.0-weight))*objectColor + specular;
gl_FragColor = vec4(resultColor, 1.0);
}