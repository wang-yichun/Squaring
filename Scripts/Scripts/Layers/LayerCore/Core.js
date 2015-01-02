/**
 * Created by leadprogrammer on 1/2/15.
 */

var Core = {
    init: function (stage_node) {
        this.stage = stage_node;
    },
    reset: function () {
        this.box_list = null;
        this.cur_n = null;
    },

    onTouchesBegan: function (touches, event) {
        var pos_on_stage = this.stage.convertTouchToNodeSpace(touches[0]);
        this.pos2loc(pos_on_stage);
    },
    onTouchesMoved: function (touches, event) {

    },
    onTouchesEnded: function (touches, event) {

    },
    onTouchesCancelled: function () {

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

    cell_side: 30,
    cell_diff: cc.p(13, 20),
    cell_diff2: cc.p(2, -3),

    loc2pos: function (loc) {
        var pos = cc.pMult(loc, this.cell_side);
        return cc.pAdd(pos, this.cell_diff);
    },

    pos2loc: function (pos) {
        var pos = cc.pAdd(pos, this.cell_diff2);
        var loc = cc.p(Math.floor(pos.x / 30), Math.floor(pos.y / 30));
        cc.log('loc: ' + JSON.stringify(loc));
    }
};