precision mediump float;
varying vec2 textCoord;
varying vec4 tempPos;
uniform sampler2D u_Texture1;
uniform sampler2D u_Texture2;
uniform sampler2D u_Texture3;
uniform sampler2D u_BlendMap;
uniform vec4 u_camPos;
void main()
{
	float fog_maxdist = 2.0;
	float fog_mindist = 0.5;
	vec4 fog_color = vec4(1.0, 1.0, 1.0 ,1.0);
	float distCam = distance(u_camPos, tempPos);
	float lerpValue = (fog_maxdist - distCam)/(fog_maxdist-fog_mindist);
	lerpValue = clamp(lerpValue, 0.0, 1.0);

    vec4 color1 = texture2D(u_Texture1, 20.0*textCoord);
	vec4 color2 = texture2D(u_Texture2, 20.0*textCoord);
	vec4 color3 = texture2D(u_Texture3, 20.0*textCoord);
	vec4 blendcolor = texture2D(u_BlendMap, textCoord);
	vec4 texelColor = (blendcolor.r * color1+ blendcolor.g* color2 + blendcolor.b* color3)/(blendcolor.r + blendcolor.g +blendcolor.b);

	gl_FragColor = mix(fog_color, texelColor, lerpValue);
}
