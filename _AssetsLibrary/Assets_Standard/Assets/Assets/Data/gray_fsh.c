// #extension GL_OES_standard_derivatives : enable	
varying vec4 v_fragmentColor;
varying vec2 v_texcoord;
uniform sampler2D CC_Texture0;

void main()
{
	vec4 v_orColor = v_fragmentColor * texture2D(CC_Texture0, v_texcoord);
	float gray = dot(v_orColor.rgb, vec3(0.299, 0.587, 0.114));
	gl_FragColor = vec4(gray, gray, gray, v_orColor.a);
}