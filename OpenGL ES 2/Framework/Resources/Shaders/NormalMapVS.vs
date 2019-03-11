attribute vec3 a_posL;
attribute vec3 a_normal;
attribute vec3 a_binormal;
attribute vec3 a_tangent;
attribute vec2 a_texCoord;
uniform mat4 u_WVP;
uniform mat4 u_W;
varying vec3 FragPos;//?
varying vec3 v_tangentW;
varying vec3 v_bitangentW;
varying vec3 v_normalW;
varying vec2 v_UV;

void main()
{
vec4 posL = vec4(a_posL, 1.0);
gl_Position = u_WVP* posL;
FragPos = vec3(u_W*vec4(a_posL, 1.0)); //?
v_normalW = normalize((u_W*vec4(a_normal, 0.0)).xyz);
v_tangentW = normalize((u_W*vec4(a_tangent, 0.0)).xyz);
v_bitangentW = normalize((u_W*vec4(a_binormal, 0.0)).xyz);
v_UV = a_texCoord;
}