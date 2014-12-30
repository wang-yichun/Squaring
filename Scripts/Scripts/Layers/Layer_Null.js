/**
 * Created by leadprogrammer on 11/10/14.
 */
var gLayer_Null = null;
var Layer_Null = cc.Layer.extend({
    // ccb Callback
    id: "Null",

    ctor: function () {
        this._super();
        cc.associateWithNative(this, cc.Layer);
        gLayer_Null = this;
    },

    onDidLoadFromCCB: function () {
        this.rootNode.setTouchEnabled(true);
        this.rootNode.onTouchesBegan = function (touches, event) {
            this.controller.onTouchesBegan(touches, event);
            return true;
        };
        this.rootNode.onTouchesEnded = function (touches, event) {
            this.controller.onTouchesEnded(touches, event);
            return true;
        };
        this.rootNode.onTouchesMoved = function (touches, event) {
            this.controller.onTouchesMoved(touches, event);
            return true;
        };
        this.rootNode.onTouchesCancelled = function () {
            this.controller.onTouchesCancelled();
            return true;
        };
    },

    switchMenuItem: function () {
        return [
            this
        ]
    },

    setEnabled: function (enabled) {
        this.my_layer_enabled = enabled;
    },

    my_layer_enabled: false,

    reset: function () {

    },

    onTouchesBegan: function (touches, event) {
        
    },
    onTouchesMoved: function (touches, event) {

    },
    onTouchesEnded: function (touches, event) {

    },
    onTouchesCancelled: function (touches, event) {

    },

    layerInCall: function () {
        
    },
    layerInStart: function () {
        
    },
    layerInEnd: function () {
        
    },
    layerOutCall: function () {
        
    },
    layerOutStart: function () {
        
    },
    layerOutEnd: function () {
        
    }
});