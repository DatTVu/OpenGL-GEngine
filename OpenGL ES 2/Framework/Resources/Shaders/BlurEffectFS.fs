precision mediump float;
uniform sampler2D u_Texture0;
uniform vec4 step;
varying vec2 vTexCoord;

void main()	
{
vec3 color1 = texture2D(u_Texture0, vTexCoord).xyz;
vec3 color2 = texture2D(u_Texture0, vec2(vTexCoord.x +step.x, vTexCoord.y)).xyz;
vec3 color3 = texture2D(u_Texture0, vec2(vTexCoord.x -step.x, vTexCoord.y)).xyz;
vec3 color4 = texture2D(u_Texture0, vec2(vTexCoord.x, vTexCoord.y+ step.y)).xyz;
vec3 color5 = texture2D(u_Texture0, vec2(vTexCoord.x, vTexCoord.y- step.y)).xyz;
vec3 color6 = texture2D(u_Texture0, vec2(vTexCoord.x +step.z, vTexCoord.y+ step.w)).xyz;
vec3 color7 = texture2D(u_Texture0, vec2(vTexCoord.x -step.z, vTexCoord.y+ step.w)).xyz;
vec3 color8 = texture2D(u_Texture0, vec2(vTexCoord.x -step.z, vTexCoord.y- step.w)).xyz;
vec3 color9 = texture2D(u_Texture0, vec2(vTexCoord.x +step.z, vTexCoord.y- step.w)).xyz;
gl_FragColor = vec4((color1*2.0+color2+color3+color4+color5+color6+color7+color8+color9)*0.1, 1.0);
}