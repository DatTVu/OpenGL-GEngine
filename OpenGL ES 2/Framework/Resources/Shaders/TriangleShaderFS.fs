precision mediump float;
varying vec2 textCoord;
uniform sampler2D ourTexture;
void main()
{
	gl_FragColor = texture2D(ourTexture, textCoord);
}
