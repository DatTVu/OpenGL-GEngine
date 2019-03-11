attribute vec3 a_posL;
attribute vec3 a_normal;
uniform mat4 u_WVP;//World * View * Projection
uniform mat4 u_W;
varying vec3 v_normW;
varying vec3 v_posW;
void main()
{
	vec4 posL = vec4(a_posL, 1.0);
    gl_Position  = u_WVP * posL;    
    v_normW = vec3(u_W*vec4(a_normal, 0.0));
    v_posW = vec3(u_W*posL);
}
   