precision mediump float;
varying vec2 textCoord;
uniform sampler2D u_Texture0;

void main()
{
	gl_FragColor = texture2D(u_Texture0, textCoord);
}
