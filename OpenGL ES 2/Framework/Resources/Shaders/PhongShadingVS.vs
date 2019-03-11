attribute vec3 a_posL;
attribute vec3 a_normal;
attribute vec2 a_texCoord;
uniform mat4 u_WVP;
uniform mat4 u_W;
varying vec3 FragPos;
varying vec3 Normal;
varying vec2 textCoord;
void main()
{
vec4 posL = vec4(a_posL, 1.0);
gl_Position = u_WVP* posL;
FragPos = vec3(u_W*vec4(a_posL, 1.0));
Normal = vec3(u_W*vec4(a_normal, 0.0));
textCoord = a_texCoord;
}