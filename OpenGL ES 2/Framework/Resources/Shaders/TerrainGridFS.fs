precision mediump float;
varying vec2 textCoord;
uniform sampler2D u_Texture1;
uniform sampler2D u_Texture2;
uniform sampler2D u_Texture3;
uniform sampler2D u_BlendMap;
void main()
{
    vec4 color1 = texture2D(u_Texture1, textCoord);
	vec4 color2 = texture2D(u_Texture2, textCoord);
	vec4 color3 = texture2D(u_Texture3, textCoord);
	vec4 blendcolor = texture2D(u_BlendMap, textCoord);
	gl_FragColor = (blendcolor.r * color3+ blendcolor.g* color2 + blendcolor.b* color1)/(blendcolor.r + blendcolor.g +blendcolor.b);
	
}
