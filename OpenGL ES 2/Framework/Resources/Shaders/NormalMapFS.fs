precision mediump float;
uniform vec3 u_LightPos0;
uniform vec3 u_LightColor0;
uniform vec4 u_camPos;
uniform sampler2D u_Texture0;
uniform sampler2D u_Texture1;
varying vec3 FragPos; //?
varying vec3 v_tangentW;
varying vec3 v_bitangentW;
varying vec3 v_normalW;
varying vec2 v_UV;

void main()
{
vec3 normal = texture2D(u_Texture1,v_UV).xyz;
mat3 TBN = mat3(normalize(v_tangentW),normalize(v_bitangentW),normalize(v_normalW));
vec3 normalW = normalize(TBN * (2.0 * normal - 1.0));
vec3 objectColor = texture2D(u_Texture0,v_UV).xyz;
float attenuation = 1.0/pow(distance(u_LightPos0, FragPos), 2.0);
//declare ambient Strength
float ambientStrength = 0.5;
//calculate ambient color
vec3 ambient = ambientStrength* u_LightColor0;
//calculate light vector
vec3 lightDir = normalize(u_LightPos0 - FragPos);
//calculate diffuse light
float diff = max(dot(normalW, lightDir), 0.0);
vec3 diffuse = diff* u_LightColor0*attenuation;
//calculate specular light
float specularStrength = 0.5;
vec3 viewDir = normalize(u_camPos.xyz- FragPos);
vec3 reflectDir = reflect(-lightDir, normalW);
float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
vec3 specular = specularStrength* spec* u_LightColor0;
//calculate final color
float weight = 0.5;
vec3 resultColor = (ambient* weight+ diffuse*(1.0-weight))*objectColor + specular;
gl_FragColor = vec4(resultColor, 1.0);
}