/**
 * Created by leadprogrammer on 12/29/14.
 */


var SBox = cc.Node.extend({
    // ccb Callback

    ctor: function () {
        this._super();
        cc.associateWithNative(this, cc.Sprite);
    },

    onDidLoadFromCCB: function () {
    }
});