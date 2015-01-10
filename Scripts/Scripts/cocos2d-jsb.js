/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org

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

// boot code needed for cocos2d + JS bindings.
// Not needed by cocos2d-html5

require("jsb.js");
require("Scripts/AppFiles.js");

cc.dumpConfig();

for (var i = 0; i < appFiles.length; i++) {
    require(appFiles[i]);
}

var director = cc.Director.getInstance();
director.setDisplayStats(false);

// set FPS. the default value is 1.0/60 if you don't call this
director.setAnimationInterval(1.0 / 60);

// Switcher init.
Switcher.initSwitcher();

//Local.addCardFirstTime(); // 测试时加入了一些牌
//
//var para = {
//    'scene_id': 'SceneA',  // 目标场景
//    'groups': {             // 每个组的目标层
//        'group_bmob': 'BmobTest'
//    },
//    'out_animation': {func_name: 'scene_out_animation_blackfade', para: [0.1]},
//    'in_animation': {func_name: 'scene_in_animation_blackfade', para: [0.2]}
//};
//var para = {
//    'scene_id': 'InnerGameScene',  // 目标场景
//    'groups': {             // 每个组的目标层
//        'group1': 'InnerGameBoard',
//        'group2': 'InnerGameMain'
//    },
//    'out_animation': {func_name: 'scene_out_animation_blackfade', para: [0.1]},
//    'in_animation': {func_name: 'scene_in_animation_blackfade', para: [0.1]}
//};
//var para = {
//    'scene_id': 'SceneA',  // 目标场景
//    'groups': {             // 每个组的目标层
//        'group1': 'SAL1',
//        'group3': 'BG1'
//    },
//    'layers_para': {
//        'SAL1': {
//            zorder: 50
//        },
//        'BG1': {
//            zorder: 10
//        }
//    },
//    'out_animation': {func_name: 'scene_out_animation_blackfade', para: [0.1]},
//    'in_animation': {func_name: 'scene_in_animation_blackfade', para: [0.2]}
//};

//var para = {
//    'scene_id': 'SceneML',  // 目标场景
//    'groups': {             // 每个组的目标层
////        'group_editer': 'RouteEditer'
//			'group1' : 'GameLoading'
//    },
//    'out_animation': {func_name: 'scene_out_animation_blackfade', para: [1]},
//    'in_animation': {func_name: 'scene_in_animation_blackfade', para: [0.2]}
//};
//Switcher.gotoScene(para);

cc.SpriteFrameCache.getInstance().addSpriteFrames(RES_BMF_PLIST);
cc.SpriteFrameCache.getInstance().addSpriteFrames(RES_TEX_PLIST_UI);
cc.SpriteFrameCache.getInstance().addSpriteFrames(RES_TEX_PLIST_LayerCore);

cc.ShaderCache.getInstance().loadDefaultShaders();

var para = {
    'scene_id': 'SceneA',  // 目标场景
    'groups': {             // 每个组的目标层
        'core_group': 'LCore',
        'popup_group': 'LMenuInGame'
    },
    'out_animation': {func_name: 'scene_out_animation_blackfade', para: [1]},
    'in_animation': {func_name: 'scene_in_animation_blackfade', para: [0.2]}
};
Switcher.gotoScene(para);

// Javascript - OC - Cpp - JAVA

//var send_para = {
//    'call_back': 'test_callback',
//    'number_int': 1234,
//    'number_float': 1234.1234,
//    'string_value1': 'abc',
//    'string_value2': '藌柚软件科技',
//    'vector_value': [1234, '郑东新区'],
//    'object_value': {'key1':123, 'key2': 'abc'}
//};
//
//var test_callback = function (para) {
//    cc.log('JS: test_callback successful!');
//    cc.log(JSON.stringify(para));
//};
//
//JSBHelper.AddSelector('test_callback', test_callback);
//
//JSBHelper.SendMessageToCPP("cppb_test", send_para);
//JSBHelper.SendMessageToOC("ocb_test", send_para);
//JSBHelper.SendMessageToJAVA("javab_test", send_para);
//
//
