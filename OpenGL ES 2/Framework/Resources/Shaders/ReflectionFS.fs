precision mediump float;
uniform samplerCube u_samplerCubeMap0;
uniform vec4 u_camPos; 
varying vec3 v_posW;
varying vec3 v_normW;
void main()
{
    vec3 I = u_camPos.xyz - v_posW;
    vec3 R = reflect(normalize(-I), normalize(v_normW));  // reflect() in non linear
    gl_FragColor = textureCube(u_samplerCubeMap0, R);	
}