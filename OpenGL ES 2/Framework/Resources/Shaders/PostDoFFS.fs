precision mediump float;
uniform sampler2D u_Texture0; //origin
uniform sampler2D u_Texture1; //blurred
uniform sampler2D u_Texture2; //depth
uniform vec4 step;
varying vec2 vTexCoord;

float CalculateMixFactor(vec2 uv)
{
 float near = 2.0;
 float far = 50.0;
 float fade = 8.0;
 float clarity = 10.0;
 
 float depth = texture2D(u_Texture2, uv).x;
 float z = -far*near/(depth*(far-near)-far);
 float k = clamp(abs(z-clarity)/fade, 0.0, 1.0);
 return k;
}
void main()	
{
vec2 uv2 = vTexCoord + vec2(step.x, 0.0);
vec2 uv3 = vTexCoord + vec2(step.z, step.w);
vec2 uv4 = vTexCoord + vec2(0.0, step.y);
vec2 uv5 = vTexCoord + vec2(-step.z, step.w);
vec2 uv6 = vTexCoord + vec2(-step.x, 0.0);
vec2 uv7 = vTexCoord + vec2(-step.z, -step.w);
vec2 uv8 = vTexCoord + vec2(0, -step.y);
vec2 uv9 = vTexCoord + vec2(step.z, -step.w);

vec4 color1 = texture2D(u_Texture1, vTexCoord);
vec4 color2 = texture2D(u_Texture1, uv2);
vec4 color3 = texture2D(u_Texture1, uv3);
vec4 color4 = texture2D(u_Texture1, uv4);
vec4 color5 = texture2D(u_Texture1, uv5);
vec4 color6 = texture2D(u_Texture1, uv6);
vec4 color7 = texture2D(u_Texture1, uv7);
vec4 color8 = texture2D(u_Texture1, uv8);
vec4 color9 = texture2D(u_Texture1, uv9);

float d1 = CalculateMixFactor(vTexCoord);
float d2 = CalculateMixFactor(uv2);
float d3 = CalculateMixFactor(uv3);
float d4 = CalculateMixFactor(uv4);
float d5 = CalculateMixFactor(uv5);
float d6 = CalculateMixFactor(uv6);
float d7 = CalculateMixFactor(uv7);
float d8 = CalculateMixFactor(uv8);
float d9 = CalculateMixFactor(uv9);

float total = 2.0+d2+d3+d4+d5+d6+d7+d8+d9;

vec4 colorOriginal = texture2D(u_Texture0, vTexCoord);
vec4 colorBlur = (2.0*color1+color2*d2+color3*d3+color4*d4+color5*d5+color6*d6+color7*d7+color8*d8+color9*d9)/total; 
gl_FragColor = mix(colorOriginal, colorBlur, d1);
}