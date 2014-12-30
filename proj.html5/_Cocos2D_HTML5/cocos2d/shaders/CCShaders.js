/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org
 Copyright (c) 2008-2010 Ricardo Quesada
 Copyright (c) 2011      Zynga Inc.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

//-----------------------Shader_Position_uColor Shader Source--------------------------
/**
 * @constant
 * @type {String}
 */
cc.SHADER_POSITION_UCOLOR_FRAG =
    "                                           \n"
        + "precision lowp float;                    \n"
        + "                                         \n"
        + "varying vec4 v_fragmentColor;            \n"
        + "                                         \n"
        + "void main()                              \n"
        + "{                                        \n"
        + "    gl_FragColor = v_fragmentColor;      \n"
        + "}                                        \n";

/**
 * @constant
 * @type {String}
 */
cc.SHADER_POSITION_UCOLOR_VERT =
    "                                               \n"
        + "attribute vec4 a_position;               \n"
        + "uniform    vec4 u_color;                 \n"
        + "uniform float u_pointSize;               \n"
        + "                                         \n"
        + "varying lowp vec4 v_fragmentColor;       \n"
        + "                                         \n"
        + "void main(void)                          \n"
        + "{                                        \n"
        //+ "    gl_Position = CC_MVPMatrix * a_position;  \n"
        + "    gl_Position = (CC_PMatrix * CC_MVMatrix) * a_position;  \n"
        + "    gl_PointSize = u_pointSize;          \n"
        + "    v_fragmentColor = u_color;           \n"
        + "}";


//---------------------Shader_PositionColor Shader Source-----------------------
/**
 * @constant
 * @type {String}
 */
cc.SHADER_POSITION_COLOR_FRAG =
    "                                        \n"
        + "precision lowp float;                 \n"
        + "varying vec4 v_fragmentColor;         \n"
        + "                                      \n"
        + "void main()                           \n"
        + "{                                     \n"
        + "     gl_FragColor = v_fragmentColor;       \n"
        + "} ";


/**
 * @constant
 * @type {String}
 */
cc.SHADER_POSITION_COLOR_VERT =
    "                                                \n"
        + "attribute vec4 a_position;                \n"
        + "attribute vec4 a_color;                   \n"
        + "                                          \n"
        + "varying lowp vec4 v_fragmentColor;        \n"
        + "                                          \n"
        + "void main()                               \n"
        + "{                                         \n"
        //+ "    gl_Position = CC_MVPMatrix * a_position;  \n"
        + "    gl_Position = (CC_PMatrix * CC_MVMatrix) * a_position;  \n"
        + "    v_fragmentColor = a_color;             \n"
        + "}";

// --------------------- Shader_PositionColorLengthTexture Shader source------------------------
/**
 * @constant
 * @type {String}
 */
cc.SHADER_POSITION_COLOR_LENGTH_TEXTURE_FRAG =
    "                                               \n"
        + "// #extension GL_OES_standard_derivatives : enable																			\n"
        + "\n"
        + "varying mediump vec4 v_color;																								\n"
        + "varying mediump vec2 v_texcoord;																							    \n"
        + "\n"
        + "void main()																													\n"
        + "{																															\n"
        + "// #if defined GL_OES_standard_derivatives																					\n"
        + "// gl_FragColor = v_color*smoothstep(0.0, length(fwidth(v_texcoord)), 1.0 - length(v_texcoord));							    \n"
        + "// #else																														\n"
        + "gl_FragColor = v_color * step(0.0, 1.0 - length(v_texcoord));														        \n"
        + "// #endif																													\n"
        + "}";

/**
 * @constant
 * @type {String}
 */
cc.SHADER_POSITION_COLOR_LENGTH_TEXTURE_VERT =
    "																	        \n"
        + "attribute mediump vec4 a_position;									\n"
        + "attribute mediump vec2 a_texcoord;									\n"
        + "attribute mediump vec4 a_color;										\n"
        + "\n"
        + "varying mediump vec4 v_color;										\n"
        + "varying mediump vec2 v_texcoord;									    \n"
        + "\n"
        + "void main()															\n"
        + "{																	\n"
        + "     v_color = a_color;//vec4(a_color.rgb * a_color.a, a_color.a);				\n"
        + "     v_texcoord = a_texcoord;										\n"
        + "																        \n"
        //+ "    gl_Position = CC_MVPMatrix * a_position;  \n"
        + "    gl_Position = (CC_PMatrix * CC_MVMatrix) * a_position;  \n"
        + "}";

// ----------------------Shader_PositionTexture Shader Source-------------------------------------
/**
 * @constant
 * @type {String}
 */
cc.SHADER_POSITION_TEXTURE_FRAG =
    "                                             \n"
        + "precision lowp float;                      \n"
        + "                                           \n"
        + "varying vec2 v_texCoord;                   \n"
        + "uniform sampler2D CC_Texture0;             \n"
        + "                                           \n"
        + "void main()                                \n"
        + "{                                          \n"
        + "    gl_FragColor =  texture2D(CC_Texture0, v_texCoord);   \n"
        + "}";

/**
 * @constant
 * @type {String}
 */
cc.SHADER_POSITION_TEXTURE_VERT =
    "                                                   \n"
        + "attribute vec4 a_position;                   \n"
        + "attribute vec2 a_texCoord;                  \n"
        + "                                            \n"
        + "varying mediump vec2 v_texCoord;           \n"
        + "                                           \n"
        + "void main()                                \n"
        + "{                                          \n"
        //+ "    gl_Position = CC_MVPMatrix * a_position;  \n"
        + "    gl_Position = (CC_PMatrix * CC_MVMatrix) * a_position;  \n"
        + "    v_texCoord = a_texCoord;               \n"
        + "}";

// ------------------------Shader_PositionTexture_uColor Shader Source-------------------------------
/**
 * @constant
 * @type {String}
 */
cc.SHADER_POSITION_TEXTURE_UCOLOR_FRAG =
    "                                                \n"
        + "precision lowp float;                        \n"
        + "                                             \n"
        + "uniform vec4 u_color;                        \n"
        + "varying vec2 v_texCoord;                     \n"
        + "                                             \n"
        + "uniform sampler2D CC_Texture0;               \n"
        + "                                             \n"
        + "void main()                                  \n"
        + "{                                            \n"
        + "    gl_FragColor =  texture2D(CC_Texture0, v_texCoord) * u_color;    \n"
        + "}";

/**
 * @constant
 * @type {String}
 */
cc.SHADER_POSITION_TEXTURE_UCOLOR_VERT =
    "                                               \n"
        + "attribute vec4 a_position;                   \n"
        + "attribute vec2 a_texCoord;                   \n"
        + "                                             \n"
        + "varying mediump vec2 v_texCoord;             \n"
        + "                                             \n"
        + "void main()                                  \n"
        + "{                                            \n"
        //+ "    gl_Position = CC_MVPMatrix * a_position;  \n"
        + "    gl_Position = (CC_PMatrix * CC_MVMatrix) * a_position;  \n"
        + "    v_texCoord = a_texCoord;                 \n"
        + "}";

//---------------------Shader_PositionTextureA8Color Shader source-------------------------------
/**
 * @constant
 * @type {String}
 */
cc.SHADER_POSITION_TEXTURE_A8COLOR_FRAG =
    "                                               \n"
        + "precision lowp float;                        \n"
        + "                                             \n"
        + "varying vec4 v_fragmentColor;                \n"
        + "varying vec2 v_texCoord;                     \n"
        + "uniform sampler2D CC_Texture0;                 \n"
        + "                                             \n"
        + "void main()                                  \n"
        + "{                                            \n"
        + "    gl_FragColor = vec4( v_fragmentColor.rgb,         \n"                            // RGB from uniform
        + "        v_fragmentColor.a * texture2D(CC_Texture0, v_texCoord).a   \n"                  // A from texture and uniform
        + "    );                                       \n"
        + "}";

/**
 * @constant
 * @type {String}
 */
cc.SHADER_POSITION_TEXTURE_A8COLOR_VERT =
    "                                               \n"
        + "attribute vec4 a_position;                   \n"
        + "attribute vec2 a_texCoord;                   \n"
        + "attribute vec4 a_color;                      \n"
        + "                                             \n"
        + "varying lowp vec4 v_fragmentColor;           \n"
        + "varying mediump vec2 v_texCoord;             \n"
        + "                                             \n"
        + "void main()                                  \n"
        + "{                                            \n"
        //+ "    gl_Position = CC_MVPMatrix * a_position;  \n"
        + "    gl_Position = (CC_PMatrix * CC_MVMatrix) * a_position;  \n"
        + "    v_fragmentColor = a_color;               \n"
        + "    v_texCoord = a_texCoord;                 \n"
        + "}";

// ------------------------Shader_PositionTextureColor Shader source------------------------------------
/**
 * @constant
 * @type {String}
 */
cc.SHADER_POSITION_TEXTURE_COLOR_FRAG =
    "                                               \n"
        + "precision lowp float;                        \n"
        + "                                             \n"
        + "varying vec4 v_fragmentColor;                \n"
        + "varying vec2 v_texCoord;                     \n"
        + "uniform sampler2D CC_Texture0;               \n"
        + "                                             \n"
        + "void main()                                  \n"
        + "{                                            \n"
        + "    gl_FragColor = v_fragmentColor * texture2D(CC_Texture0, v_texCoord);         \n"
        + "}";

cc.SHADER_POSITION_TEXTURE_COLOR_GRAY_FRAG =
    "                                               \n"
    + "precision lowp float;                        \n"
    + "                                             \n"
    + "varying vec4 v_fragmentColor;                \n"
    + "varying vec2 v_texCoord;                     \n"
    + "uniform sampler2D CC_Texture0;               \n"
    + "                                             \n"
    + "void main()                                  \n"
    + "{                                            \n"
    + "    vec4 v_orColor = v_fragmentColor * texture2D(CC_Texture0, v_texCoord);         \n"
    + "    float gray = dot(v_orColor.rgb, vec3(0.299, 0.587, 0.114));         \n"
    + "    gl_FragColor = vec4(gray, gray, gray, v_orColor.a);         \n"
    + "    //gl_FragColor = v_fragmentColor * texture2D(CC_Texture0, v_texCoord);         \n"
    + "}";

cc.SHADER_POSITION_TEXTURE_COLOR_LIGHTBLUE_FRAG =
    "                                               \n"
    + "precision lowp float;                        \n"
    + "                                             \n"
    + "varying vec4 v_fragmentColor;                \n"
    + "varying vec2 v_texCoord;                     \n"
    + "uniform sampler2D CC_Texture0;               \n"
    + "                                             \n"
    + "void main()                                  \n"
    + "{                                            \n"
    + "    vec4 v_orColor = v_fragmentColor * texture2D(CC_Texture0, v_texCoord);         \n"
    + "    float red = dot(v_orColor.rgb, vec3(1, 0, 0));         \n"
    + "    float green = dot(v_orColor.rgb, vec3(0, 1, 0));         \n"
    + "    float blue = dot(v_orColor.rgb, vec3(0.299, 0.587, 2));         \n"
    + "    gl_FragColor = vec4(red, green, blue, v_orColor.a);         \n"
    + "    //gl_FragColor = v_fragmentColor * texture2D(CC_Texture0, v_texCoord);         \n"
    + "}";

cc.SHADER_POSITION_TEXTURE_COLOR_DARKBLUE_FRAG =
    "                                               \n"
    + "precision lowp float;                        \n"
    + "                                             \n"
    + "varying vec4 v_fragmentColor;                \n"
    + "varying vec2 v_texCoord;                     \n"
    + "uniform sampler2D CC_Texture0;               \n"
    + "                                             \n"
    + "void main()                                  \n"
    + "{                                            \n"
    + "    vec4 normalColor = v_fragmentColor * texture2D(CC_Texture0, v_texCoord);         \n"
    + "    normalColor *= vec4(0.3, 0.3, 0.5, 1);         \n"
    + "    normalColor.b += normalColor.a * 0.2;         \n"
    + "    gl_FragColor = normalColor;         \n"
    + "}";


cc.SHADER_POSITION_TEXTURE_COLOR_STROKE_FRAG =
    "                                               \n"
    + "precision highp float;                       \n"
    + "                                             \n"
    + "varying vec4 v_fragmentColor;                \n"
    + "varying vec2 v_texCoord;                     \n"
    + "uniform sampler2D CC_Texture0;               \n"
    + "uniform ivec2 u_texture_size;                \n"
    + "uniform ivec2 u_font_size;                   \n"
    + "                                             \n"
    + "void main(void)                              \n"
    + "{                                            \n"
    + "    vec4 color = v_fragmentColor * texture2D(CC_Texture0, v_texCoord);                                                 \n"
    + "    vec4 color1 = color;                                                                                               \n"
    + "    vec4 color2 = color;                                                                                               \n"
    + "    float k = float(u_font_size.x)/24.0;                                                                               \n"
    + "    float a1 = texture2D(CC_Texture0, vec2(v_texCoord.x + 0.302*k/float(u_texture_size.x), v_texCoord.y + 0.33*k/float(u_texture_size.y) )).a;      \n"
    + "    float a2 = texture2D(CC_Texture0, vec2(v_texCoord.x, v_texCoord.y - 0.33*k/float(u_texture_size.y))).a;                                         \n"
    + "    float a3 = texture2D(CC_Texture0, vec2(v_texCoord.x - 0.302*k/float(u_texture_size.x), v_texCoord.y - 1.32*k/float(u_texture_size.y))).a;       \n"
    + "    float am = max(max(a1,a2), a3);                                                                                    \n"
    + "    am = clamp(am * 2.0, 0.0, 1.0);                                                                                    \n"
    + "    if (color.a > 0.8) {                                                                                               \n"
    + "        color1 = color;                                                                                                \n"
    + "        //return;                                                                                                      \n"
    + "    } else {                                                                                                           \n"
    + "        color1 = color * vec4(color.a, color.a, color.a, 1);                                                           \n"
    + "    }                                                                                                                  \n"
    + "    if (a1 > 0.1 || a2 > 0.1 || a3 > 0.1) {                                                                            \n"
    + "        color2 = vec4(0.0, 0.0, 0.0, 1.0) * vec4(am, am, am, am);                                                      \n"
    + "                                                                                                                       \n"
    + "    }                                                                                                                  \n"
    + "    gl_FragColor = color1 * vec4(1,1,1,0.5) + color2 * vec4(0.5,0.5,0.5,1);                                            \n"
    + "}";

/**
 * @constant
 * @type {String}
 */
cc.SHADER_POSITION_TEXTURE_COLOR_VERT =
    "                                               \n"
        + "attribute vec4 a_position;                   \n"
        + "attribute vec2 a_texCoord;                   \n"
        + "attribute vec4 a_color;                      \n"
        + "                                             \n"
        + "varying lowp vec4 v_fragmentColor;           \n"
        + "varying mediump vec2 v_texCoord;             \n"
        + "                                             \n"
        + "void main()                                  \n"
        + "{                                            \n"
        + "    gl_Position = (CC_PMatrix * CC_MVMatrix) * a_position;  \n"
        + "    v_fragmentColor = a_color;               \n"
        + "    v_texCoord = a_texCoord;                 \n"
        + "}";

/**
 * @constant
 * @type {String}
 */
cc.SHADER_POSITION_TEXTURE_COLOR_STROKE_VERT =
    "                                               \n"
    + "attribute vec4 a_position;                   \n"
    + "attribute vec2 a_texCoord;                   \n"
    + "attribute vec4 a_color;                      \n"
    + "                                             \n"
    + "varying lowp vec4 v_fragmentColor;           \n"
    + "varying mediump vec2 v_texCoord;             \n"
    + "                                             \n"
    + "void main()                                  \n"
    + "{                                            \n"
    + "    gl_Position = (CC_PMatrix * CC_MVMatrix) * a_position;  \n"
    + "    v_fragmentColor = a_color;               \n"
    + "    v_texCoord = a_texCoord;                 \n"
    + "}";

//-----------------------Shader_PositionTextureColorAlphaTest_frag Shader Source----------------------------
/**
 * @constant
 * @type {String}
 */
cc.SHADER_POSITION_TEXTURE_COLOR_ALPHATEST_FRAG =
    "                                                  \n"
        + "precision lowp float;                           \n"
        + "                                                \n"
        + "varying vec4 v_fragmentColor;                   \n"
        + "varying vec2 v_texCoord;                        \n"
        + "uniform sampler2D CC_Texture0;                  \n"
        + "uniform float CC_alpha_value;                   \n"
        + "                                                \n"
        + "void main()                                     \n"
        + "{                                               \n"
        + "    vec4 texColor = texture2D(CC_Texture0, v_texCoord);          \n"
        + "                                                \n"
        + "    // mimic: glAlphaFunc(GL_GREATER)           \n"
        + "    //pass if ( incoming_pixel >= CC_alpha_value ) => fail if incoming_pixel < CC_alpha_value         \n"
        + "                                                \n"
        + "    if ( texColor.a <= CC_alpha_value )          \n"
        + "        discard;                                \n"
        + "                                                \n"
        + "    gl_FragColor = texColor * v_fragmentColor;  \n"
        + "}";

//-----------------------ShaderEx_SwitchMask_frag Shader Source----------------------------
/**
 * @constant
 * @type {String}
 */
cc.SHADEREX_SWITCHMASK_FRAG =
    "                                                   \n"
        + "precision lowp float;                            \n"
        + "                                                 \n"
        + "varying vec4 v_fragmentColor;                    \n"
        + "varying vec2 v_texCoord;                         \n"
        + "uniform sampler2D u_texture;                     \n"
        + "uniform sampler2D   u_mask;                      \n"
        + "                                                 \n"
        + "void main()                                      \n"
        + "{                                                \n"
        + "    vec4 texColor   = texture2D(u_texture, v_texCoord);          \n"
        + "    vec4 maskColor  = texture2D(u_mask, v_texCoord);             \n"
        + "    vec4 finalColor = vec4(texColor.r, texColor.g, texColor.b, maskColor.a * texColor.a);        \n"
        + "    gl_FragColor    = v_fragmentColor * finalColor;              \n"
        + "}";