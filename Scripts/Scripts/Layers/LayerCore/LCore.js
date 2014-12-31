/**
 * Created by leadprogrammer on 12/29/14.
 */
/**
 * Created by leadprogrammer on 11/10/14.
 */
var gLCore = null;
var LCore = cc.Layer.extend({
    // ccb Callback
    id: "LCore",

    ctor: function () {
        this._super();
        cc.associateWithNative(this, cc.Layer);
        gLCore = this;
    },

    stage: undefined,

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

        cc.log();
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
        this.box_list = null;
        this.cur_n = null;
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
        this.prepare_new_game();
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

    },

    prepare_new_game: function () {
        Data.init();
        this.box_lists = [];
        this.cur_n = 0;

        this.create_a_column();
        this.create_a_column();
        this.create_a_column();
        this.create_a_column();
        this.create_a_column();
        this.create_a_column();
        this.create_a_column();
        this.create_a_column();
        this.create_a_column();
        this.create_a_column();
        this.create_a_column();
        this.create_a_column();
        this.create_a_column();
        this.create_a_column();
        this.create_a_column();
        this.create_a_column();
        this.create_a_column();
        this.create_a_column();
        this.create_a_column();
        this.create_a_column();
    },

    create_a_column: function () {
        var data_column = Data.data[this.cur_n];
        var box_column = [];
        for (var m in data_column) {
            var it = data_column[m];
            if (it == 1) {
                var mid_node = cc.Node.create();
                var ccb_node = cc.BuilderReader.load(RES_CCBI_NBox);
                mid_node.addChild(ccb_node, 0, 1);
                mid_node.setPosition(this.loc2pos(cc.p(this.cur_n, m)));
                this.stage.addChild(mid_node);
            }
        }

        this.cur_n++;
    },

    loc2pos: function (loc) {
        var pos = cc.pMult(loc, 30);
        return cc.pAdd(pos, cc.p(13, 20));
    }
});