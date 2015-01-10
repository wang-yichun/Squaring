/**
 * Created by leadprogrammer on 12/29/14.
 */

var CTest = cc.Node.extend({
    // ccb Callback

    ctor: function () {
        this._super();
        cc.associateWithNative(this, cc.Node);
    },

    onDidLoadFromCCB: function () {
        cc.log('Hi, CTest!');
    },

    control_button_1_clicked: function (sender, event) {
        cc.log('control_button_1_clicked: ' + event);
    }
});