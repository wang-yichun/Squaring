/*
 * cocos2d for iPhone: http://www.cocos2d-iphone.org
 *
 * Copyright (c) 2011 Ricardo Quesada
 * Copyright (c) 2012 Zynga Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

"																								  \n\
								            													  \n\
//precision highp float;																	      \n\
										    													  \n\
																								  \n\
varying vec4 v_fragmentColor;																	  \n\
varying vec2 v_texCoord;																		  \n\
uniform sampler2D CC_Texture0;																	  \n\
uniform ivec2 u_texture_size;                                                                     \n\
uniform ivec2 u_font_size;                                                                        \n\
                                                                                                  \n\
void main()																						  \n\
{																								  \n\
    vec4 color = v_fragmentColor * texture2D(CC_Texture0, v_texCoord);                                                                          \n\
    vec4 color0 = v_fragmentColor * texture2D(CC_Texture0, vec2(v_texCoord.x, v_texCoord.y));                                                   \n\
    vec4 color00 = v_fragmentColor * texture2D(CC_Texture0, vec2(v_texCoord.x, v_texCoord.y));                                                  \n\
    vec4 color1 = color;                                                                                                                        \n\
    vec4 color2 = color;                                                                                                                        \n\
    float k = float(u_font_size.x)/24.0;                                                                                                        \n\
    float a1 = texture2D(CC_Texture0, vec2(v_texCoord.x + 0.5*k/float(u_texture_size.x), v_texCoord.y + 0.0*k/float(u_texture_size.y))).a;      \n\
    float a2 = texture2D(CC_Texture0, vec2(v_texCoord.x + 0.5*k/float(u_texture_size.x), v_texCoord.y + 0.5*k/float(u_texture_size.y))).a;      \n\
    float a3 = texture2D(CC_Texture0, vec2(v_texCoord.x + 0.0*k/float(u_texture_size.x), v_texCoord.y + 0.5*k/float(u_texture_size.y))).a;      \n\
    float a4 = texture2D(CC_Texture0, vec2(v_texCoord.x - 0.5*k/float(u_texture_size.x), v_texCoord.y + 0.5*k/float(u_texture_size.y))).a;      \n\
    float a5 = texture2D(CC_Texture0, vec2(v_texCoord.x - 0.5*k/float(u_texture_size.x), v_texCoord.y + 0.0*k/float(u_texture_size.y))).a;      \n\
    float a6 = texture2D(CC_Texture0, vec2(v_texCoord.x - 0.5*k/float(u_texture_size.x), v_texCoord.y - 1.0*k/float(u_texture_size.y))).a;      \n\
    float a7 = texture2D(CC_Texture0, vec2(v_texCoord.x + 0.0*k/float(u_texture_size.x), v_texCoord.y - 1.0*k/float(u_texture_size.y))).a;      \n\
    float a8 = texture2D(CC_Texture0, vec2(v_texCoord.x + 0.5*k/float(u_texture_size.x), v_texCoord.y - 1.0*k/float(u_texture_size.y))).a;      \n\
    float am = max(max(max(max(max(max(max(a1, a2),a3),a4), a5), a6), a7), a8);                                                                 \n\
    am = clamp(am * 2.0, 0.0, 1.0);                                                               \n\
    if (color.a > 0.5 || color0.a > 0.5 || color00.a > 0.5) {                                     \n\
        color = color.a > color0.a ? color : color0;                                              \n\
        color = color.a > color00.a ? color : color00;                                            \n\
        color1 = color;                                                                           \n\
    } else {                                                                                      \n\
        color = color.a > color0.a ? color : color0;                                              \n\
        color = color.a > color00.a ? color : color00;                                            \n\
        color1 = color * vec4(color.a, color.a, color.a, 1);                                      \n\
    }                                                                                             \n\
    if (a1 > 0.1 || a2 > 0.1 || a3 > 0.1 || a4 > 0.1 || a5 > 0.1 || a6 > 0.1 || a7 > 0.1 || a8 > 0.1) {                   \n\
        color2 = vec4(0.0, 0.0, 0.0, 1.0) * vec4(am, am, am, am);                                 \n\
    }                                                                                             \n\
                                                                                                  \n\
    gl_FragColor = color1 * vec4(1,1,1,0.5) + color2 * vec4(0.5,0.5,0.5,1);                       \n\
}											                                                      \n\
";