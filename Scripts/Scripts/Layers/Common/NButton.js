/**
 * Created by leadprogrammer on 12/29/14.
 */

var NButton = cc.Node.extend({
    // ccb Callback

    ctor: function () {
        this._super();
        cc.associateWithNative(this, cc.Node);
    },

    onDidLoadFromCCB: function () {
        cc.log('Hi, NButton!');
        this.reset();
    },

    reset: function () {
        this.btn_func = undefined;
        this.btn_owner = undefined;
        this.btn_drag_outside = undefined;
    },
    setEnabled: function (enabled) {
        this['btn'].setEnabled(enabled);
    },
    setBtnFunc: function (call_func, owner, enabled) {
        this.btn_func = call_func;
        this.btn_owner = owner;

        if (enabled != null) {
            this.setEnabled(enabled);
        }
    },
    btn_clicked: function (sender, event) {
        switch(event) {
            case 1:
                this.btn_drag_outside = true;
                this.scale_big();
                break;
            case 4:
                if (this.btn_drag_outside) {
                    this.btn_drag_outside = false;
                    this.scale_normal();
                }
                break;
            case 32:
                this.btn_drag_outside = false;
                this.scale_normal();
                break;
            default:
                this.btn_drag_outside = false;
                this.scale_normal();
        }

        if (this.btn_func == null || this.btn_owner == null) {
            cc.log('No callback func.');
        } else {
            this.btn_func.call(this.btn_owner, sender, event);
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
    }
});