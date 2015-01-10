/**
 * Created by leadprogrammer on 9/29/14.
 */

var CocosHelper = {
    traverseNode: function (node, node_list) {
        node_list.push(node);
        var children_list = node.getChildren();
        for (var idx = 0; idx < children_list.length; idx++) {
            CocosHelper.traverseNode(children_list[idx], node_list);
        }
    },

    // todo: 未测试
    traverseNodeAndDoFunc: function (node, func) {
        func.call(node); // 方法 func 放在 node 上面用
        var children_list = node.getChildren();
        for (var idx = 0; idx < children_list.length; idx++) {
            CocosHelper.traverseNode(children_list[idx], func);
        }
    },

    getChildrenByTag: function (ori_node, tag) {
        var type = typeof(ori_node);

        var flitered_children = [];
        var node_list = [];
        CocosHelper.traverseNode(ori_node, node_list);
        for (var idx = 0; idx < node_list.length; idx++) {
            var node = node_list[idx];
            if (node.getTag() == tag) {
                flitered_children.push(node);
            }
        }
        return flitered_children;
    },

    setBlend: function (node) {
        if (sys.platform == 'browser') {
            var node_list = [];
            CocosHelper.traverseNode(node, node_list);
            for (var idx = 0; idx < node_list.length; idx++) {
                var node = node_list[idx];
                if (node.getTag() == 1001) {
                    node.setBlendFunc(
                        {src: cc.BLEND_SRC, dst: cc.BLEND_DST}
                    )
                }
            }
        }
    },

    setParticle: function (node) {
        var node_list = [];
        CocosHelper.traverseNode(node, node_list);
        for (var idx = 0; idx < node_list.length; idx++) {
            var node = node_list[idx];
            if (node.getTag() == 1002) {
                node.setPositionType(cc.PARTICLE_TYPE_RELATIVE);
            }
        }
    },

    setToGridContainer: function (node) {
        var node_list = [];
        CocosHelper.traverseNode(node, node_list);
        for (var idx = 0; idx < node_list.length; idx++) {
            var node = node_list[idx];
            if (node.getTag() == 1003) {
                node.removeFromParent(false);
                var z = gLayer_GamePlayer.positionToZOrder(node.getPosition());
                gLayer_GamePlayer['grid_container'].addChild(node, z);
                node.setVisible(true);


            } else if (node.getTag() == 1013) {

                node.removeFromParent(false);
                var z = gLayer_GamePlayer.positionToZOrder(node.getPosition());
                gLayer_GamePlayer['grid_container'].addChild(node, z);
                node.setVisible(true);

                node.action_call_fun = function () {
                    this.stopAllActions();
                    this.runAction(
                        cc.RepeatForever.create(
                            cc.Sequence.create(
                                cc.SkewTo.create(Math.random() + 2, -3, 0),
                                cc.SkewTo.create(Math.random() + 2, 3, 0)
                            )
                        )
                    )
                };
                node.runAction(
                    cc.Sequence.create(
                        cc.DelayTime.create(Math.random() * 2),
                        cc.CallFunc.create(node.action_call_fun, node)
                    )
                );
            }
        }
    },

    takeTouchArea: function (ori_node) {
        var touch_area = {top: 30, bottom: -10, left: -20, right: 20};
        var node_list = [];
        CocosHelper.traverseNode(ori_node, node_list);
        for (var idx = 0; idx < node_list.length; idx++) {
            var node = node_list[idx];
            if (node.getTag() == 1004) {
                touch_area = {
                    top: node.getPosition().y + node.getContentSize().height,
                    bottom: node.getPosition().y,
                    left: node.getPosition().x,
                    right: node.getPosition().x + node.getContentSize().width
                };
                node.removeFromParent();
                break;
            }
        }
        return touch_area;
    },

    takeViewArea: function (ori_node, remove) {
        if (remove == null) remove = true;
        var touch_area = {top: 160, bottom: -160, left: -480, right: 480};
        var node_list = [];
        CocosHelper.traverseNode(ori_node, node_list);
        for (var idx = 0; idx < node_list.length; idx++) {
            var node = node_list[idx];
            if (node.getTag() == 1005) {
                touch_area = {
                    top: node.getPosition().y + node.getContentSize().height,
                    bottom: node.getPosition().y,
                    left: node.getPosition().x,
                    right: node.getPosition().x + node.getContentSize().width
                };
                if (remove) {
                    node.removeFromParent();
                }
                break;
            }
        }
        return touch_area;
    },

    setFinishingHeart: function (ori_node) {
        gLayer_GamePlayer.finishing_heart_node_list = [];
        var node_list = [];
        CocosHelper.traverseNode(ori_node, node_list);
        for (var idx = 0; idx < node_list.length; idx++) {
            var node = node_list[idx];
            if (node.getTag() == 1006) {
                gLayer_GamePlayer.finishing_heart_node_list.push(node);
            }
        }
    }

};