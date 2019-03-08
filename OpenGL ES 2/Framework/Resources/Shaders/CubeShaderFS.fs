precision mediump float;
uniform samplerCube u_samplerCubeMap0;
varying vec4 v_pos;

void main(void)
{
	gl_FragColor = textureCube(u_samplerCubeMap0, v_pos.xyz);
}