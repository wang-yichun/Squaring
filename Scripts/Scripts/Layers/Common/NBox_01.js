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

    remove: function (hit_myself) {
        if (hit_myself == null) hit_myself = false;

        var mid_node = this.rootNode.getParent();

        if (hit_myself) {
            var world_pos = Data.gLCore['my_hp'].getParent().convertToWorldSpace(Data.gLCore['my_hp'].getPosition());
            var dest_pos = Data.gLCore['stage'].convertToNodeSpace(world_pos);
        } else {
            var world_pos = Data.gLCore['enemy_hp'].getParent().convertToWorldSpace(Data.gLCore['enemy_hp'].getPosition());
            var dest_pos = Data.gLCore['stage'].convertToNodeSpace(world_pos);
        }

        if (this.panel_id == 1) {
            Data.core.remove_box_data(this.loc);
        } else {
            Data.core.remove_box_data2(this.loc);
        }

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
                    cc.JumpTo.create(0.4, dest_pos, 40, 1),
                    cc.EaseIn.create(cc.RotateBy.create(0.4, 360), 2)
                ),
                cc.CallFunc.create(
                    function () {
                        this.remove_gfx_attack();
                        this.rootNode.getParent().removeFromParent();

                        if (hit_myself) {
                            Data.gLCore.my_hp_add(-this.number_value);
                        } else {
                            Data.gLCore.enemy_hp_add(-this.number_value);
                        }
                    }, this
                )
            )
        );
    },

    remove_gfx_attack: function () {
        var particle = cc.BuilderReader.load(RES_CCBI_PLight_02);
        var pos = this.rootNode.getParent().getPosition();
        particle.setPosition(pos);
        particle.resetSystem();
        particle.setAutoRemoveOnFinish(true);

        if (this.panel_id == 1) {
            Data.core.stage.addChild(particle, 300);
        } else {
            Data.core.stage2.addChild(particle, 300);
        }
    }
});