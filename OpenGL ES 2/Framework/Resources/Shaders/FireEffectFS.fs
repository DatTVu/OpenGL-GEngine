precision mediump float;

varying vec2 textCoord;
uniform sampler2D u_Texture0;
uniform sampler2D u_Texture1;
uniform sampler2D u_Texture2;
uniform sampler2D u_BlendMap;
uniform float u_Time;
void main()
{
	float dMax = 0.2;	
	vec2 disp = texture2D(u_Texture1, vec2(textCoord.x, textCoord.y + u_Time)).rg;
	vec2 offset = (2.0 * disp - 1.0) * dMax;
	vec2 Tex_coords_displaced = textCoord + offset;
	vec4 fire_color = texture2D (u_Texture0, Tex_coords_displaced);
	vec4 AlphaValue = texture2D(u_Texture2, textCoord);
    gl_FragColor = fire_color * (1.0, 1.0, 1.0, AlphaValue.r);
	//gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
}
