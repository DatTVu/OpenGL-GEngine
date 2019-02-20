attribute vec3 a_posL;
attribute vec3 a_normal;
attribute vec3 a_binormal;
attribute vec3 a_tangent;
attribute vec2 a_texCoord;

uniform mat4 m4_translation;

varying vec2 textCoord;
void main()
{
vec4 posL = vec4(a_posL, 1.0) ;
gl_Position = m4_translation* posL;
textCoord = a_texCoord;
}
   