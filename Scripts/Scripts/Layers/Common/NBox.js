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
    }


});