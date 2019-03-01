attribute vec4 a_CubeVertexPos;
uniform mat4 u_CubeMVPMatrix;
varying vec4 v_pos;

void main(void)
{    
	gl_Position = u_CubeMVPMatrix* a_CubeVertexPos;	
	v_pos = a_CubeVertexPos;
}