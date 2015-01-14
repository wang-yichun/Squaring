/**
 * Created by leadprogrammer on 12/29/14.
 */
/**
 * Created by leadprogrammer on 11/10/14.
 */
var gLCore2 = null;
var LCore2 = cc.Layer.extend({
    // ccb Callback
    id: "LCore2",

    ctor: function () {
        this._super();
        cc.associateWithNative(this, cc.Layer);
        gLCore2 = this;
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
        Core2.init(this['stage'], this['stage_gfx'], this['stage2'], this['stage2_gfx']);
        this.reset();
    },

    switchMenuItem: function () {
        return [
            this
        ]
    },

    setEnabled: function (enabled) {
        this.my_layer_enabled = enabled;
        this['menu_btn'].setEnabled(enabled);
    },

    my_layer_enabled: false,

    my_hp_value: 100,
    enemy_hp_value: 100,

    reset: function () {
        Core2.reset();
        this.refresh_hp();
    },

    my_hp_add: function (value) {
        this.my_hp_value += value;
        this.refresh_hp();
        if (this.my_hp_value <= 0) {
            this.game_lose();
        }
    },

    enemy_hp_add: function (value) {
        this.enemy_hp_value += value;
        this.refresh_hp();
        if (this.enemy_hp_value <= 0) {
            this.game_win();
        }
    },

    refresh_hp: function () {
        this['my_hp'].setString(this.my_hp_value);
        this['enemy_hp'].setString(this.enemy_hp_value);
    },

    onTouchesBegan: function (touches, event) {
        Core2.onTouchesBegan(touches, event);
    },
    onTouchesMoved: function (touches, event) {
        Core2.onTouchesMoved(touches, event);
    },
    onTouchesEnded: function (touches, event) {
        Core2.onTouchesEnded(touches, event);
    },
    onTouchesCancelled: function () {
        Core2.onTouchesCancelled();
    },

    layerInCall: function () {
        Data.gLCore = gLCore2;
        Core2.prepare_new_game();
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

    menu_btn_clicked: function () {
        Core2.game_pause();
        Switcher.gotoLayer({
            group_id: 'popup_group',
            layer_id: 'LMenuInGame',
            out_delay_time: 0,
            in_delay_time: 0
        });
    },

    game_lose: function () {
        Core2.game_pause();

        gLMenuInGame['info'].setString('你失败了!');

        Switcher.gotoLayer({
            group_id: 'popup_group',
            layer_id: 'LMenuInGame',
            out_delay_time: 0,
            in_delay_time: 0
        });
    },
    game_win: function () {
        Core2.game_pause();

        gLMenuInGame['info'].setString('你胜利了!');

        Switcher.gotoLayer({
            group_id: 'popup_group',
            layer_id: 'LMenuInGame',
            out_delay_time: 0,
            in_delay_time: 0
        });
    }
});