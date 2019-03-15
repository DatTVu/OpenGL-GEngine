precision mediump float;
uniform sampler2D u_Texture0;
varying vec2 textCoord;

void main()	{
float limit = 0.3;
vec3 color = texture2D(u_Texture0, textCoord).rgb;
float brightness = 0.3*color.r + 0.59*color.g + 0.11*color.b;
float val = step(limit, brightness);
gl_FragColor = vec4(color*val, 1.0);
}