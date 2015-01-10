/**
 * Created by leadprogrammer on 12/29/14.
 */

var NBox = cc.Node.extend({
    // ccb Callback

    ctor: function () {
        this._super();
        cc.associateWithNative(this, cc.Node);
    },

    onDidLoadFromCCB: function () {
        this.reset();
    },

    reset: function () {
    },

    setEnabled: function (enabled) {
    },

    onTouchDown: function () {
        Core.show_related_box(false);
        Core.related_boxs_loc = Core.getRelatedBoxLoc(this.loc);
        Core.show_related_box(true);
    },

    onTouchIn: function () {
        Core.show_related_box(false);
        Core.related_boxs_loc = Core.getRelatedBoxLoc(this.loc);
        Core.show_related_box(true);
    },

    onTouchInnerDrag: function () {
    },

    onTouchHold: function () {
        cc.log('NBox_01 onTouchHold');

        Core.show_related_box(false);
        Core.related_boxs_loc = Core.getRelatedBoxLoc(this.loc);

        Core.combine_related_box(this.loc);
        Core.related_boxs_loc = Core.getRelatedBoxLoc(this.loc);
    },

    onTouchOut: function () {
        Core.show_related_box(false);
        Core.related_boxs_loc = null;
    },

    onTouchUp: function () {
        Core.show_related_box(false);
        Core.remove_related_box();
        Core.related_boxs_loc = null;
        Core.repair_map();
    },

    refresh_show: function () {
        if (this.number_value == null || this.number_value == 1) {
            this['number'].setVisible(false);
        } else {
            this['number'].setVisible(true);
            this['number'].setString(this.number_value);
        }
    },

    scale_big: function () {
        this['core_node'].stopActionByTag(1);
        var action = cc.EaseElasticOut.create(cc.ScaleTo.create(0.25, 1.2));
        action.setTag(1);
        this['core_node'].runAction(action);
    },
    scale_normal: function () {
        this['core_node'].stopActionByTag(1);
        var action = cc.EaseElasticOut.create(cc.ScaleTo.create(0.3, 1));
        action.setTag(1);
        this['core_node'].runAction(action);
    },

    scale_big_then_normal: function () {
        this['core_node'].stopActionByTag(1);
        var action1 = cc.EaseElasticOut.create(cc.ScaleTo.create(0.25, 1.2));
        var action2 = cc.EaseElasticOut.create(cc.ScaleTo.create(0.25, 1));
        var action_sequence = cc.Sequence.create(action1, action2);
        action_sequence.setTag(1);
        this['core_node'].runAction(action_sequence);
    },

    delay_scale_big_then_normal: function () {
        this['core_node'].stopActionByTag(1);
        var delay_action = cc.DelayTime.create(0.4);
        var action1 = cc.EaseOut.create(cc.ScaleTo.create(0.1, 1.4), 2);
        var action2 = cc.EaseOut.create(cc.ScaleTo.create(0.1, 1), 2);
        var gfx_call_action = cc.CallFunc.create(
            function () {
                this.remove_gfx();
                this.refresh_show();
            }, this
        );
        var action_sequence = cc.Sequence.create(delay_action, gfx_call_action, action1, action2);
        action_sequence.setTag(1);
        this['core_node'].runAction(action_sequence);
        this.remove_gfx();
    },

    rot_and_big: function () {
        this['mid_node'].setZOrder(200);
        var action = cc.Spawn.create(
            cc.ScaleTo.create(0.2, 1.2),
            cc.RotateTo.create(0.2, 30)
        );
        action.setTag(2);
        this['mid_node'].stopActionByTag(2);
        this['mid_node'].runAction(action);
    },

    rot_and_big_reset: function () {
        this['mid_node'].setZOrder(100);
        var action = cc.Spawn.create(
            cc.ScaleTo.create(0.2, 1),
            cc.RotateTo.create(0.2, 0)
        );
        action.setTag(2);
        this['mid_node'].stopActionByTag(2);
        this['mid_node'].runAction(action);
    },

    remove: function () {
        var mid_node = this.rootNode.getParent();

        var diff = cc.p(Math.random() * 40 - 20, -80);

        Core.remove_box_data(this.loc);

        mid_node.runAction(
            cc.Sequence.create(
                cc.CallFunc.create(
                    function () {
                        this['ccb_sbox'].runAction(
                            cc.Sequence.create(
                                cc.DelayTime.create(0.2),
                                cc.FadeOut.create(0.2)
                            )
                        )
                    }, this
                ),
                cc.Spawn.create(
                    cc.JumpBy.create(0.4, diff, 40, 1),
                    cc.EaseIn.create(cc.RotateBy.create(0.4, 360), 2)
                ),
                cc.CallFunc.create(
                    function () {
                        this.rootNode.getParent().removeFromParent();
                    }, this
                )
            )
        );
    },

    combine_remove: function (dest_pos) {
        var mid_node = this.rootNode.getParent();

        Core.remove_box_data(this.loc);

        mid_node.runAction(
            cc.Sequence.create(
                cc.CallFunc.create(
                    function () {
                        this['ccb_sbox'].runAction(
                            cc.Sequence.create(
                                cc.DelayTime.create(0.2),
                                cc.FadeOut.create(0.2)
                            )
                        )
                    }, this
                ),
                cc.Spawn.create(
                    cc.JumpTo.create(0.4, dest_pos, 40, 1),
                    cc.EaseIn.create(cc.RotateBy.create(0.4, 360), 2)
                ),
                cc.CallFunc.create(
                    function () {
                        this.rootNode.getParent().removeFromParent();
                    }, this
                )
            )
        );
    },

    remove_gfx: function () {
        var particle = cc.BuilderReader.load(RES_CCBI_PLight_01);
        var pos = this.rootNode.getParent().getPosition();
        particle.setPosition(pos);
        particle.resetSystem();
        particle.setAutoRemoveOnFinish(true);
        Core.stage.addChild(particle, 300);
    }
});