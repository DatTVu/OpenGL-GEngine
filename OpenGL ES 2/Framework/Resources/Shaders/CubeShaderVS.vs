attribute vec3 a_posL;
uniform mat4 m4_translation;
varying vec4 v_pos;

void main(void)
{   	
	gl_Position = m4_translation* vec4(a_posL, 1.0);	
	v_pos = vec4(a_posL, 1.0);
}