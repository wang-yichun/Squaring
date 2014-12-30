/**
 * Created by leadprogrammer on 12/29/14.
 */

var PTest = cc.ParticleSystem.extend({
    // ccb Callback

    ctor: function () {
        this._super();
        cc.associateWithNative(this, cc.ParticleSystem);
    },

    onDidLoadFromCCB: function () {
        cc.log('Hi, PTest!');
    }
});