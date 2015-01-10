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
    },

    onTouchIn: function () {
    },

    onTouchInnerDrag: function () {
    },

    onTouchHold: function () {
        cc.log('NBox onTouchHold');
    },

    onTouchOut: function () {
    },

    onTouchUp: function () {
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
    }
});