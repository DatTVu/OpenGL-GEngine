attribute vec4 a_CubeVertexPos;
uniform mat4 m4_translation;
varying vec4 v_pos;

void main(void)
{
	gl_Position = m4_translation * a_CubeVertexPos;
	
	v_pos = a_CubeVertexPos;
}