/**
 * Created by leadprogrammer on 12/29/14.
 */

var NBox_01 = NBox.extend({
    // ccb Callback

    ctor: function () {
        this._super();
        cc.associateWithNative(this, NBox);
    },

    onDidLoadFromCCB: function () {
        this.reset();
    },

    reset: function () {
    },

    setEnabled: function (enabled) {
    },

    onTouchDown: function () {
        Core.show_related_box(false);
        Core.related_boxs_loc = Core.getRelatedBoxLoc(this.loc);
        Core.show_related_box(true);
    },

    onTouchIn: function () {
        Core.show_related_box(false);
        Core.related_boxs_loc = Core.getRelatedBoxLoc(this.loc);
        Core.show_related_box(true);
    },

    onTouchOut: function () {
        Core.show_related_box(false);
        Core.related_boxs_loc = null;
    },

    onTouchUp: function () {
        Core.show_related_box(false);
        Core.remove_related_box();
        Core.related_boxs_loc = null;
        Core.repair_map();
    },

    remove: function () {
        var mid_node = this.rootNode.getParent();

        var diff = cc.p(Math.random() * 40 - 20, -80);

        Core.remove_box_data(this.loc);

        mid_node.runAction(
            cc.Sequence.create(
                cc.CallFunc.create(
                    function () {
                        this['ccb_sbox'].runAction(
                            cc.Sequence.create(
                                cc.DelayTime.create(0.2),
                                cc.FadeOut.create(0.2)
                            )
                        )
                    }, this
                ),
                cc.Spawn.create(
                    cc.JumpBy.create(0.4, diff, 40, 1),
                    cc.EaseIn.create(cc.RotateBy.create(0.4, 360), 2)
                ),
                cc.CallFunc.create(
                    function () {
                        this.rootNode.getParent().removeFromParent();
                    }, this
                )
            )
        );
    },

    remove_gfx: function () {
        var particle = cc.BuilderReader.load(RES_CCBI_PLight_01);
        var pos = this.rootNode.getParent().getPosition();
        particle.setPosition(pos);
        particle.resetSystem();
        particle.setAutoRemoveOnFinish(true);
        Core.stage.addChild(particle);
    }
});