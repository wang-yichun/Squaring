/**
 * Created by leadprogrammer on 11/19/14.
 */

var TTFHelper = {

    // todo: 未测试
    setNormalString: function (ttf_node, text) {
        if (text != null) {
            ttf_node.setString(text);
        }
        var program = cc.ShaderCache.getInstance().getProgram('ShaderPositionTextureColor');
        ttf_node.setShaderProgram(program);
    },

    setStrokeString: function (ttf_node, text) {
        if (text != null) {
            ttf_node.setString(text);
        }

        // 描边需要扩展
        var dim = ttf_node.getContentSize();
        dim.width += 2;
        dim.height += 5;
        ttf_node.setContentSize(dim);
        ttf_node.setDimensions(dim);

        var font_size = ttf_node.getFontSize();

        var program = cc.ShaderCache.getInstance().getProgram('ShaderPositionTextureColorStroke');
        program.updateUniforms();
        var u_texture_size = program.getUniformLocationForName('u_texture_size');
        program.setUniformLocationWith2i(u_texture_size, dim.width, dim.height);
        var u_font_size = program.getUniformLocationForName('u_font_size');
        program.setUniformLocationWith2i(u_font_size, font_size, font_size);
        ttf_node.setShaderProgram(program);
    }
};