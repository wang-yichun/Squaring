
attribute mediump vec4 a_position;
attribute mediump vec2 a_texcoord;
attribute mediump vec4 a_color;

varying mediump vec4 v_fragmentColor;
varying mediump vec2 v_texcoord;

void main()
{
	gl_Position = CC_PMatrix * a_position;
	v_fragmentColor = a_color;
	v_texcoord = a_texcoord;
	// gl_Position = (CC_PMatrix * CC_MVMatrix) * a_position;
}