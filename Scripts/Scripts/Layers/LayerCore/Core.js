/**
 * Created by leadprogrammer on 1/2/15.
 */

var Core = {
    init: function (stage_node, stage_gfx_node) {
        this.stage = stage_node;
        this.stage_gfx = stage_gfx_node;
    },
    reset: function () {
        this.box_lists = null;
        this.cur_n = null;
        this.locByTouchesIdxs = null;
        this.posByTouchesIdxs = null;
        this.game_going = false;
        this.speed = 1;
        this.win_size = cc.Director.getInstance().getWinSize();
        this.column_had_removed = 0;

        this.touch_slow = false;
        this.touch_hold_count = -1;
    },

    refreshTouchSlow: function () {
        if (this.locByTouchesIdxs == null) {
            this.touch_slow = false;
            return;
        }
        for (var i = 0; i < this.locByTouchesIdxs.length; i++) {
            if (this.locByTouchesIdxs[i] != null) {
                this.touch_slow = true;
                return;
            }
        }
        this.touch_slow = false;
    },

    onTouchesBegan: function (touches, event) {
        if (this.game_going == false) {
            this.game_start();
            return;
        }
        for (var tid = 0; tid < touches.length; tid++) {
            var pos_on_stage = this.stage.convertTouchToNodeSpace(touches[tid]);
            var loc = this.pos2loc(pos_on_stage);

            if (this.box_lists[loc.x]) {
                var box = this.box_lists[loc.x][loc.y];
                if (box) {
                    box.controller.onTouchDown();

                    Core.touch_hold_count = 0;
                }
            }

            this.locByTouchesIdxs[touches[tid].getId()] = loc;
            this.posByTouchesIdxs[touches[tid].getId()] = pos_on_stage;
        }
        this.refreshTouchSlow();
    },
    onTouchesMoved: function (touches, event) {
        if (this.game_going == false)  return;
        for (var tid = 0; tid < touches.length; tid++) {
            var pos_on_stage = this.stage.convertTouchToNodeSpace(touches[0]);
            var loc = this.pos2loc(pos_on_stage);
            var old_loc = this.locByTouchesIdxs[touches[tid].getId()];

            if (cc.pointEqualToPoint(old_loc, loc)) {
                // 内部移动
                if (this.box_lists[loc.x]) {
                    var box = this.box_lists[loc.x][loc.y];
                    if (box) {
                        box.controller.onTouchInnerDrag();
                    }
                }
            } else {
                if (Core.touch_hold_count >= 0) {
                    Core.touch_hold_count = -1;
                }

                if (old_loc && this.box_lists[old_loc.x]) {
                    var old_box = this.box_lists[old_loc.x][old_loc.y];
                    if (old_box) {
                        old_box.controller.onTouchOut();
                    }
                }
                if (this.box_lists[loc.x]) {
                    var new_box = this.box_lists[loc.x][loc.y];
                    if (new_box) {
                        new_box.controller.onTouchIn();
                    }
                }
            }

            this.locByTouchesIdxs[touches[tid].getId()] = loc;
            this.posByTouchesIdxs[touches[tid].getId()] = pos_on_stage;
        }
    },
    onTouchesEnded: function (touches, event) {
        if (this.game_going == false)  return;
        for (var tid = 0; tid < touches.length; tid++) {
            var pos_on_stage = this.stage.convertTouchToNodeSpace(touches[0]);
            var loc = this.pos2loc(pos_on_stage);

            if (this.box_lists[loc.x]) {
                var box = this.box_lists[loc.x][loc.y];
                if (box) {
                    box.controller.onTouchUp();
                }
            }

            this.locByTouchesIdxs[touches[tid].getId()] = null;
            this.posByTouchesIdxs[touches[tid].getId()] = null;
        }
        this.refreshTouchSlow();
        if (Core.touch_hold_count >= 0) {
            Core.touch_hold_count = 0;
        }
    },
    onTouchesCancelled: function () {
        this.locByTouchesIdxs = new Array(10);
        this.posByTouchesIdxs = new Array(10);
    },
    callOnTouchesHold: function () {
        if (this.locByTouchesIdxs[0]) {
            var loc = this.locByTouchesIdxs[0];
            if (this.box_lists[loc.x]) {
                var box = this.box_lists[loc.x][loc.y];
                if (box) {
                    box.controller.onTouchHold();
                }
            }
        }
    },

    game_start: function () {
        this.game_going = true;
        gLCore.rootNode.unschedule(this.game_step);
        gLCore.rootNode.schedule(this.game_step, 1 / 60);
    },

    game_step: function () {
        var ori_pos = Core.stage.getPosition();
        var speed = Core.speed;
        if (Core.touch_slow) {
            speed *= .2;
            if (Core.touch_hold_count >= 0) {
                Core.touch_hold_count++;
            }
            if (Core.touch_hold_count > 15) {
                Core.callOnTouchesHold();
                Core.touch_hold_count = -1;
            }
        }
        var new_pos = cc.pAdd(ori_pos, cc.p(-speed, 0));
        Core.stage.setPosition(new_pos);

        var right_pos_in_stage = Core.stage.convertToNodeSpace(cc.p(Core.win_size.width, 0));
        var right_loc = Core.pos2loc(right_pos_in_stage);
        var left_pos_in_stage = Core.stage.convertToNodeSpace(cc.p(-Core.cell_side, 0));
        var left_loc = Core.pos2loc(left_pos_in_stage);

        if (right_loc.x >= Core.cur_n) {
            Core.create_a_column();
        }

        if (Core.column_had_removed < left_loc.x) {
            Core.column_had_removed = left_loc.x;
            Core.remove_a_column(left_loc.x);
        }
    },

    prepare_new_game: function () {
        Data.init();
        this.box_lists = [];
        this.cur_n = 0;

        this.locByTouchesIdxs = new Array(10);
        this.posByTouchesIdxs = new Array(10);
    },

    create_a_column: function () {
        var data_column = Data.data[this.cur_n];
        var box_column = [];
        for (var m in data_column) {
            var it = data_column[m];
            if (it >= 0 && it <= 4) {
                var mid_node = cc.Node.create();
                var ccbi_name = Data.box[it].ccbi_file;
                var ccb_node = cc.BuilderReader.load(ccbi_name);

                ccb_node.controller.loc = cc.p(this.cur_n, m);

                mid_node.addChild(ccb_node, 0, 1);
                mid_node.setPosition(this.loc2pos(cc.p(this.cur_n, m)));
                this.stage.addChild(mid_node);

                box_column.push(ccb_node);
            } else {
                box_column.push(null);
            }


        }
        this.box_lists.push(box_column);

        this.cur_n++;
    },

    remove_a_column: function (n) {
        for (var m = 0; m < Data.height; m++) {
            var loc = cc.p(n, m);
            this.remove_box_by_loc(loc);
            this.remove_box_data(loc);
        }
    },

    remove_box_data: function (loc) {
        if (this.box_lists[loc.x]) {
            this.box_lists[loc.x][loc.y] = null;
        }
    },

    remove_box_by_loc: function (loc) {
        if (this.box_lists[loc.x]) {
            var box = this.box_lists[loc.x][loc.y];
            if (box) {
                box.getParent().removeFromParent();
            }
        }
    },

    cell_side: 30,
    cell_diff: cc.p(13, 20),
    cell_diff2: cc.p(2, -3),

    loc2pos: function (loc) {
        var pos = cc.pMult(loc, this.cell_side);
        return cc.pAdd(pos, this.cell_diff);
    },

    pos2loc: function (pos) {
        var pos2 = cc.pAdd(pos, this.cell_diff2);
        return cc.p(Math.floor(pos2.x / 30), Math.floor(pos2.y / 30));
    }
};