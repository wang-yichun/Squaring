/**
 * Created by leadprogrammer on 12/29/14.
 */

var PTest = cc.Node.extend({
    // ccb Callback

    ctor: function () {
        this._super();
        cc.associateWithNative(this, cc.Node);
    },

    onDidLoadFromCCB: function () {
    }
});