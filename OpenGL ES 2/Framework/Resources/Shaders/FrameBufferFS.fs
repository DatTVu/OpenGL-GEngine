precision mediump float;
varying vec2 textCoord;
uniform sampler2D u_Texture0;

void main()
{
	vec4 tempColor = texture2D(u_Texture0, textCoord);
	float average = 0.2126* tempColor.r +0.7152*tempColor.g+ 0.0722* tempColor.b;
	gl_FragColor = texture2D(u_Texture0, textCoord);
	//gl_FragColor = vec4(average, average, average, 1.0);
}
