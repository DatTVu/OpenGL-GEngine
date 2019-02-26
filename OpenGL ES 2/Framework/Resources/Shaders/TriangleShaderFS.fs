precision mediump float;
varying vec2 textCoord;
uniform sampler2D u_Texture1;
void main()
{
	gl_FragColor = texture2D(u_Texture1, textCoord);
}
