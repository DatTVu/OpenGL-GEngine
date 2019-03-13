attribute vec3 a_posL;
varying vec2 vTexCoord;
 
void main(void)
{
// Clean up inaccuracies
gl_Position = vec4(a_posL.xy, 0.0, 1.0);
vTexCoord = a_posL.xy*0.5 + 0.5;
}