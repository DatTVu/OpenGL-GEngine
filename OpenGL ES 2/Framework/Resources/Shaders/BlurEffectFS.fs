precision mediump float;
const float offset = 1.0 / 300.0;  
varying vec2 textCoord;
uniform sampler2D u_Texture0;
void main()
{
    vec2 topleft = vec2(-offset,  offset); // top-left
    vec2 topcenter = vec2( 0.0,    offset); // top-center
    vec2 topright =vec2( offset,  offset); // top-right
    vec2 centerleft=vec2(-offset,  0.0);   // center-left
    vec2 centercenter = vec2( 0.0,    0.0);   // center-center
    vec2 centerright= vec2( offset,  0.0);   // center-right
    vec2 bottomleft = vec2(-offset, -offset); // bottom-left
    vec2 bottomcenter= vec2( 0.0,   -offset); // bottom-center
    vec2 bottomright = vec2( offset, -offset);  // bottom-right          
	vec3 sampleTex0 = vec3(texture2D(u_Texture0, textCoord.st + topleft));
	vec3 sampleTex1 = vec3(texture2D(u_Texture0, textCoord.st + topcenter));
	vec3 sampleTex2 = vec3(texture2D(u_Texture0, textCoord.st + topright));
	vec3 sampleTex3 = vec3(texture2D(u_Texture0, textCoord.st + centerleft));
	vec3 sampleTex4 = vec3(texture2D(u_Texture0, textCoord.st + centercenter));
	vec3 sampleTex5 = vec3(texture2D(u_Texture0, textCoord.st + centerright));
	vec3 sampleTex6 = vec3(texture2D(u_Texture0, textCoord.st + bottomleft));
	vec3 sampleTex7 = vec3(texture2D(u_Texture0, textCoord.st + bottomcenter));
	vec3 sampleTex8 = vec3(texture2D(u_Texture0, textCoord.st + bottomright));
    vec3 col = vec3(0.0);
    col = sampleTex0*(1.0/16.0)+ sampleTex1*(2.0/16.0)+ sampleTex2*(1.0/16.0)+sampleTex3*(2.0/16.0)+sampleTex4*(4.0/16.0)+sampleTex5*(2.0/16.0)+sampleTex6*(1.0/16.0)+sampleTex7*(2.0/16.0)+sampleTex8*(1.0/16.0);
    gl_FragColor = vec4(col, 1.0);
}  