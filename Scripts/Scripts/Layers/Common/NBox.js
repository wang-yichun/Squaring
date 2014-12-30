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
        cc.log('Hi, NBox!');
        this.reset();
    },

    reset: function () {
    },
    setEnabled: function (enabled) {
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
    }
});