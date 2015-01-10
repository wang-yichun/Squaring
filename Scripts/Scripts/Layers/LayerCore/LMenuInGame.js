/**
 * Created by leadprogrammer on 12/29/14.
 */
/**
 * Created by leadprogrammer on 11/10/14.
 */
var gLMenuInGame = null;
var LMenuInGame = cc.Layer.extend({
    // ccb Callback
    id: "MenuInGame",

    ctor: function () {
        this._super();
        cc.associateWithNative(this, cc.Layer);
        gLMenuInGame = this;
    },

    onDidLoadFromCCB: function () {
    },

    switchMenuItem: function () {
        return [
            this
        ]
    },

    setEnabled: function (enabled) {
        this.my_layer_enabled = enabled;
        this['start_btn'] = enabled;
    },

    my_layer_enabled: false,

    start_btn_clicked: function () {

        Core.reset();
        Core.prepare_new_game();

        gLMenuInGame['info'].setString('- 规则 -');

        Switcher.gotoLayer({
            group_id: 'popup_group',
            layer_id: null,
            out_delay_time: 0,
            in_delay_time: 0
        });
        Core.game_start();
    }
});