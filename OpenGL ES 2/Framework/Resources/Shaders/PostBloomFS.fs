precision mediump float;
uniform sampler2D u_Texture0;
uniform sampler2D u_Texture1;
varying vec2 textCoord;
void main(){
vec4 color = texture2D(u_Texture0, textCoord);
vec4 blur = texture2D(u_Texture1, textCoord);
gl_FragColor = color +1.2*blur;
}
