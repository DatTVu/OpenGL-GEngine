attribute vec3 a_posL;
attribute vec3 a_normal;
uniform mat4 u_WVP;//World * View * Projection
uniform mat4 u_W;
varying vec3 v_normW;
varying vec3 v_posW;
void main()
{
    gl_Position  = u_WVP * vec4(a_posL, 1.0);
    // calculate v_normW
    v_normW = vec3(u_WVP*vec4(a_normal, 0.0));
    // calculate v_posW    
	v_posW = a_posL;
}
   