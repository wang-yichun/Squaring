/**
 * Created by leadprogrammer on 1/2/15.
 */

var Core = {
    init: function (stage_node) {
        this.stage = stage_node;
    },
    reset: function () {
        this.box_lists = null;
        this.cur_n = null;
        this.locByTouchesIdxs = null;
    },

    onTouchesBegan: function (touches, event) {
        for (var tid = 0; tid < touches.length; tid++) {
            var pos_on_stage = this.stage.convertTouchToNodeSpace(touches[tid]);
            var loc = this.pos2loc(pos_on_stage);

            var box = this.box_lists[loc.x][loc.y];
            if (box) {
                box.controller.onTouchDown();
            }

            this.locByTouchesIdxs[touches[tid].getId()] = loc;

        }
    },
    onTouchesMoved: function (touches, event) {
        for (var tid = 0; tid < touches.length; tid++) {
            var pos_on_stage = this.stage.convertTouchToNodeSpace(touches[0]);
            var loc = this.pos2loc(pos_on_stage);

            var old_loc = this.locByTouchesIdxs[touches[tid].getId()];
            if (cc.pointEqualToPoint(old_loc, loc)) {
                // 内部移动
                var box = this.box_lists[loc.x][loc.y];
                if (box) {
                    box.controller.onTouchInnerDrag();
                }
            } else {
                var old_box = this.box_lists[old_loc.x][old_loc.y];
                if (old_box) {
                    old_box.controller.onTouchOut();
                }
                var new_box = this.box_lists[loc.x][loc.y];
                if (new_box) {
                    new_box.controller.onTouchIn();
                }
            }

            this.locByTouchesIdxs[touches[tid].getId()] = loc;
        }
    },
    onTouchesEnded: function (touches, event) {
        for (var tid = 0; tid < touches.length; tid++) {
            var pos_on_stage = this.stage.convertTouchToNodeSpace(touches[0]);
            var loc = this.pos2loc(pos_on_stage);

            var box = this.box_lists[loc.x][loc.y];
            if (box) {
                box.controller.onTouchUp();
            }

            this.locByTouchesIdxs[touches[tid].getId()] = null;
        }
    },
    onTouchesCancelled: function () {
        this.locByTouchesIdxs = new Array(10);
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

        this.locByTouchesIdxs = new Array(10);
    },

    create_a_column: function () {
        var data_column = Data.data[this.cur_n];
        var box_column = [];
        for (var m in data_column) {
            var it = data_column[m];
            if (it == 1) {
                var mid_node = cc.Node.create();
                var ccb_node = cc.BuilderReader.load(RES_CCBI_NBox_01);

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

    remove_box_data: function (loc) {
        this.box_lists[loc.x][loc.y] = null;
    },

    remove_box_by_loc: function (loc) {
        var box = this.box_lists[loc.x][loc.y];
        if (box) {
            box.getParent().removeFromParent();
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