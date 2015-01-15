/**
 * Created by leadprogrammer on 1/2/15.
 */

var Core2 = {
    mode: 2,
    init: function (stage_node, stage_gfx_node, stage2_node, stage2_gfx_node) {
        this.stage = stage_node;
        this.stage_gfx = stage_gfx_node;
        this.stage2 = stage2_node;
        this.stage2_gfx = stage2_gfx_node;

    },
    reset: function () {

        gLCore2.my_hp_value = 200;
        gLCore2.enemy_hp_value = 200;

        this.box_lists = null;
        this.box2_lists = null;
        this.cur_n = null;
        this.cur2_n = null;
        this.locByTouchesIdxs = null;
        this.posByTouchesIdxs = null;
        this.game_going = false;
        this.speed = 1;
        this.speed2 = 1;

        this.win_size = cc.Director.getInstance().getWinSize();

        this.column_had_removed = 0;
        this.column_had_removed2 = 0;

        this.touch_slow = false;
        this.touch_slow2 = false;

        this.touch_hold_count = [-1, -1, -1, -1, -1, -1, -1, -1, -1, -1];
        this.touch_hold_count2 = [-1, -1, -1, -1, -1, -1, -1, -1, -1, -1];
        this.related_boxs_loc = null;
        this.related_boxs_loc2 = null;

        this.stage.removeAllChildren();
        this.stage.setPosition(cc.p(0, 0));

        this.stage2.removeAllChildren();
        this.stage2.setPosition(cc.p(0, 0));
    },

    refreshTouchSlow: function () {
        if (this.locByTouchesIdxs == null) {
            this.touch_slow = false;
            this.touch_slow2 = false;
            return;
        }
        for (var i = 0; i < this.locByTouchesIdxs.length; i++) {
            if (this.locByTouchesIdxs[i] != null) {
                this.touch_slow = true;
                this.touch_slow2 = true;
                return;
            }
        }
        this.touch_slow = false;
        this.touch_slow2 = false;
    },

    onTouchesBegan: function (touches, event) {
        //if (this.game_going == false) {
        //    this.game_start();
        //    return;
        //}
        for (var tid = 0; tid < touches.length; tid++) {
            var pos_on_stage = this.stage.convertTouchToNodeSpace(touches[tid]);
            var loc = this.pos2loc(pos_on_stage);

            var pos_on_stage2 = this.stage2.convertTouchToNodeSpace(touches[tid]);
            var loc2 = this.pos2loc(pos_on_stage2);

            if (loc.y < loc2.y) {
                if (this.box_lists[loc.x]) {
                    var box = this.box_lists[loc.x][loc.y];
                    if (box) {
                        box.controller.onTouchDown();
                        Core2.touch_hold_count[touches[tid].getId()] = 0;
                    }
                }
                this.locByTouchesIdxs[touches[tid].getId()] = loc;
                this.posByTouchesIdxs[touches[tid].getId()] = pos_on_stage;
            } else {
                if (this.box2_lists[loc2.x]) {
                    var box2 = this.box2_lists[loc2.x][loc2.y];
                    if (box2) {
                        box2.controller.onTouchDown();
                        Core2.touch_hold_count2[touches[tid].getId()] = 0;
                    }
                }
                this.locByTouchesIdxs[touches[tid].getId()] = loc2;
                this.posByTouchesIdxs[touches[tid].getId()] = pos_on_stage2;
            }
        }
        this.refreshTouchSlow();
    },
    onTouchesMoved: function (touches, event) {
        if (this.game_going == false)  return;
        for (var tid = 0; tid < touches.length; tid++) {

            var pos_on_stage = this.stage.convertTouchToNodeSpace(touches[0]);
            var loc = this.pos2loc(pos_on_stage);

            var pos_on_stage2 = this.stage2.convertTouchToNodeSpace(touches[0]);
            var loc2 = this.pos2loc(pos_on_stage2);

            var old_loc = this.locByTouchesIdxs[touches[tid].getId()];

            if (loc.y < loc2.y) {
                if (cc.pointEqualToPoint(old_loc, loc)) {
                    // 内部移动
                    if (this.box_lists[loc.x]) {
                        var box = this.box_lists[loc.x][loc.y];
                        if (box) {
                            box.controller.onTouchInnerDrag();
                        }
                    }
                } else {
                    if (Core2.touch_hold_count[touches[tid].getId()] >= 0) {
                        Core2.touch_hold_count[touches[tid].getId()] = -1;
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
            } else {
                if (cc.pointEqualToPoint(old_loc, loc2)) {
                    // 内部移动
                    if (this.box2_lists[loc2.x]) {
                        var box2 = this.box2_lists[loc2.x][loc2.y];
                        if (box2) {
                            box2.controller.onTouchInnerDrag();
                        }
                    }
                } else {
                    if (Core2.touch_hold_count2[touches[tid].getId()] >= 0) {
                        Core2.touch_hold_count2[touches[tid].getId()] = -1;
                    }
                    if (old_loc && this.box2_lists[old_loc.x]) {
                        var old_box2 = this.box2_lists[old_loc.x][old_loc.y];
                        if (old_box2) {
                            old_box2.controller.onTouchOut();
                        }
                    }
                    if (this.box2_lists[loc2.x]) {
                        var new_box2 = this.box2_lists[loc2.x][loc2.y];
                        if (new_box2) {
                            new_box2.controller.onTouchIn();
                        }
                    }
                }
                this.locByTouchesIdxs[touches[tid].getId()] = loc2;
                this.posByTouchesIdxs[touches[tid].getId()] = pos_on_stage2;
            }
        }
    },
    onTouchesEnded: function (touches, event) {
        if (this.game_going == false)  return;
        for (var tid = 0; tid < touches.length; tid++) {
            var pos_on_stage = this.stage.convertTouchToNodeSpace(touches[0]);
            var loc = this.pos2loc(pos_on_stage);
            var pos_on_stage2 = this.stage2.convertTouchToNodeSpace(touches[0]);
            var loc2 = this.pos2loc(pos_on_stage2);

            var up_call = false;
            if (loc.y < loc2.y) {
                if (this.box_lists[loc.x]) {
                    var box = this.box_lists[loc.x][loc.y];
                    if (box) {
                        box.controller.onTouchUp();
                        up_call = true;
                    }
                }
                if (Core2.touch_hold_count[touches[tid].getId()] >= 0) {
                    Core2.touch_hold_count[touches[tid].getId()] = 0;
                }
            } else {
                if (this.box2_lists[loc2.x]) {
                    var box2 = this.box2_lists[loc2.x][loc2.y];
                    if (box2) {
                        box2.controller.onTouchUp();
                        up_call = true;
                    }
                }
                if (Core2.touch_hold_count2[touches[tid].getId()] >= 0) {
                    Core2.touch_hold_count2[touches[tid].getId()] = 0;
                }
            }

            this.locByTouchesIdxs[touches[tid].getId()] = null;
            this.posByTouchesIdxs[touches[tid].getId()] = null;

            if (up_call == false) {
                cc.log();
            }

        }
        this.refreshTouchSlow();

    },
    onTouchesCancelled: function () {
        this.locByTouchesIdxs = new Array(10);
        this.posByTouchesIdxs = new Array(10);
    },
    callOnTouchesHold: function (touch_idx, panel_id) {
        if (this.locByTouchesIdxs[touch_idx]) {
            var loc = this.locByTouchesIdxs[touch_idx];
            if (panel_id == 1) {
                if (this.box_lists[loc.x]) {
                    var box = this.box_lists[loc.x][loc.y];
                    if (box) {
                        box.controller.onTouchHold();
                    }
                }
            } else {
                if (this.box2_lists[loc.x]) {
                    var box2 = this.box2_lists[loc.x][loc.y];
                    if (box2) {
                        box2.controller.onTouchHold();
                    }
                }
            }
        }
    },

    game_start: function () {
        this.game_going = true;
        gLCore2.rootNode.unschedule(this.game_step);
        gLCore2.rootNode.schedule(this.game_step, 1 / 60);
    },

    game_pause: function () {
        this.game_going = false;
        gLCore2.rootNode.unschedule(this.game_step);
    },

    game_step: function () {
        Core2.game_step1();
        Core2.game_step2();
    },
    game_step1: function () {
        var ori_pos = Core2.stage.getPosition();
        var speed = Core2.speed;
        if (Core2.touch_slow) {
            speed *= .2;
            for (var touch_idx in Core2.touch_hold_count) {
                if (Core2.touch_hold_count[touch_idx] >= 0) {
                    Core2.touch_hold_count[touch_idx]++;
                }
                if (Core2.touch_hold_count[touch_idx] > 10) {
                    Core2.callOnTouchesHold(touch_idx, 1);
                    Core2.touch_hold_count[touch_idx] = -1;
                }
            }
        }
        var new_pos = cc.pAdd(ori_pos, cc.p(-speed, 0));
        Core2.stage.setPosition(new_pos);

        var right_pos_in_world = gLCore2['stage_start_node'].getParent().convertToWorldSpace(gLCore2['stage_start_node'].getPosition());
        var right_pos_in_stage = Core2.stage.convertToNodeSpace(right_pos_in_world);
        var right_loc = Core2.pos2loc(right_pos_in_stage);
        var left_pos_in_world = gLCore2['stage_end_node'].getParent().convertToWorldSpace(gLCore2['stage_end_node'].getPosition());
        var left_pos_in_stage = Core2.stage.convertToNodeSpace(left_pos_in_world);
        var left_loc = Core2.pos2loc(left_pos_in_stage);

        if (right_loc.x >= Core2.cur_n) {
            Core2.create_a_column();
        }

        if (Core2.column_had_removed < left_loc.x) {
            Core2.column_had_removed = left_loc.x;
            Core2.remove_a_column(left_loc.x);
        }
    },
    game_step2: function () {
        var ori_pos = Core2.stage2.getPosition();
        var speed = Core2.speed2;
        if (Core2.touch_slow2) {
            speed *= .2;
            for (var touch_idx in Core2.touch_hold_count2) {
                if (Core2.touch_hold_count2[touch_idx] >= 0) {
                    Core2.touch_hold_count2[touch_idx]++;
                }
                if (Core2.touch_hold_count2[touch_idx] > 10) {
                    Core2.callOnTouchesHold(touch_idx, 2);
                    Core2.touch_hold_count2[touch_idx] = -1;
                }
            }
        }
        var new_pos = cc.pAdd(ori_pos, cc.p(-speed, 0));
        Core2.stage2.setPosition(new_pos);

        var right_pos_in_world = gLCore2['stage2_start_node'].getParent().convertToWorldSpace(gLCore2['stage2_start_node'].getPosition());
        var right_pos_in_stage = Core2.stage2.convertToNodeSpace(right_pos_in_world);
        var right_loc = Core2.pos2loc(right_pos_in_stage);
        var left_pos_in_world = gLCore2['stage2_end_node'].getParent().convertToWorldSpace(gLCore2['stage2_end_node'].getPosition());
        var left_pos_in_stage = Core2.stage2.convertToNodeSpace(left_pos_in_world);
        var left_loc = Core2.pos2loc(left_pos_in_stage);

        if (right_loc.x >= Core2.cur2_n) {
            Core2.create_a_column2();
        }

        if (Core2.column_had_removed2 < left_loc.x) {
            Core2.column_had_removed2 = left_loc.x;
            Core2.remove_a_column2(left_loc.x);
        }
    },

    prepare_new_game: function () {
        Data.init();
        this.box_lists = [];
        this.cur_n = 0;
        this.box2_lists = [];
        this.cur2_n = 0;

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

                ccb_node.controller.panel_id = 1;
                ccb_node.controller.loc = cc.p(this.cur_n, parseInt(m));
                ccb_node.controller.mid_node = mid_node;
                ccb_node.controller.box_id = it;
                ccb_node.controller.number_value = 1;
                ccb_node.controller.refresh_show();
                ccb_node.controller.is_reward = false;

                mid_node.addChild(ccb_node, 0, 1);
                mid_node.setPosition(this.loc2pos(cc.p(this.cur_n, parseInt(m))));
                this.stage.addChild(mid_node, 100);

                box_column.push(ccb_node);
            } else {
                box_column.push(null);
            }
        }
        this.box_lists.push(box_column);

        this.cur_n++;
    },

    create_a_column2: function () {
        var data_column = Data.data[this.cur2_n];
        var box_column = [];
        for (var m in data_column) {
            var it = data_column[m];
            if (it >= 0 && it <= 4) {
                var mid_node = cc.Node.create();
                var ccbi_name = Data.box[it].ccbi_file;
                var ccb_node = cc.BuilderReader.load(ccbi_name);

                ccb_node.controller.panel_id = 2;
                ccb_node.controller.loc = cc.p(this.cur2_n, parseInt(m));
                ccb_node.controller.mid_node = mid_node;
                ccb_node.controller.box_id = it;
                ccb_node.controller.number_value = 1;
                ccb_node.controller.refresh_show();
                ccb_node.controller.is_reward = false;

                mid_node.addChild(ccb_node, 0, 1);
                mid_node.setPosition(this.loc2pos(cc.p(this.cur2_n, parseInt(m))));
                this.stage2.addChild(mid_node, 100);

                box_column.push(ccb_node);
            } else {
                box_column.push(null);
            }
        }
        this.box2_lists.push(box_column);

        this.cur2_n++;
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
    remove_box_data2: function (loc) {
        if (this.box2_lists[loc.x]) {
            this.box2_lists[loc.x][loc.y] = null;
        }
    },

    remove_box_by_loc: function (loc) {
        if (this.box_lists[loc.x]) {
            var box = this.box_lists[loc.x][loc.y];
            if (box) {
                if (box.controller.is_reward == false && box.controller.box_id == 0) {
                    box.controller.remove(null);
                } else if (box.controller.is_reward == false && box.controller.box_id == 3) {
                    box.controller.remove(null);
                } else {
                    box.getParent().removeFromParent();
                }
            }
        }
    },
    remove_box_by_loc2: function (loc) {
        if (this.box2_lists[loc.x]) {
            var box = this.box2_lists[loc.x][loc.y];
            if (box) {
                if (box.controller.box_id == 0) {
                    box.controller.remove(null);
                } else if (box.controller.box_id == 3) {
                    box.controller.remove(null);
                } else {
                    box.getParent().removeFromParent();
                }
            }
        }
    },

    remove_a_column2: function (n) {
        for (var m = 0; m < Data.height; m++) {
            var loc = cc.p(n, m);
            this.remove_box_by_loc2(loc);
            this.remove_box_data2(loc);
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
    },

    getBoxAtLoc: function (loc, panel_id) {
        if (panel_id == 1) {
            if (this.box_lists[loc.x]) {
                var box = this.box_lists[loc.x][loc.y];
                if (box) {
                    return box;
                }
            }
        } else if (panel_id == 2) {
            if (this.box2_lists[loc.x]) {
                var box = this.box2_lists[loc.x][loc.y];
                if (box) {
                    return box;
                }
            }
        } else {
            cc.log();
        }

        return null;
    },
    getRelatedBoxLoc: function (loc, panel_id) {
        if (loc == null) return null;
        var box = this.getBoxAtLoc(loc, panel_id);
        if (box == null) return null;
        var core_box_id = box.controller.box_id;

        var va = [];
        var vb = [];
        va.push(box);
        var contaminate_flag = uuid(6);

        var dir_diff_vec = [cc.p(1, 0), cc.p(0, 1), cc.p(-1, 0), cc.p(0, -1)];

        while (va.length > 0) {
            var box0 = va.pop();
            box0.controller.contaminate_flag = contaminate_flag;
            vb.push(box0.controller.loc);

            var loc0 = box0.controller.loc;

            for (var i = 0; i < dir_diff_vec.length; i++) {
                var locn = cc.pAdd(loc0, dir_diff_vec[i]);
                var boxn = this.getBoxAtLoc(locn, panel_id);
                if (boxn) {
                    if (boxn.controller.box_id == core_box_id) {
                        if (boxn.controller.contaminate_flag != contaminate_flag) {
                            va.push(boxn);
                        }
                    }
                }
            }
        }
        return vb;
    },
    show_related_box: function (enabled, panel_id) {
        var related_boxs_loc;
        if (panel_id == 1) {
            related_boxs_loc = this.related_boxs_loc;
        } else if (panel_id == 2) {
            related_boxs_loc = this.related_boxs_loc2;
        }
        if (related_boxs_loc) {
            if (related_boxs_loc.length >= 3) {
                for (var idx in related_boxs_loc) {
                    var loc = related_boxs_loc[idx];
                    var box = this.getBoxAtLoc(loc, panel_id);
                    if (box) {
                        if (enabled) {
                            box.controller.rot_and_big();
                        } else {
                            box.controller.rot_and_big_reset();
                        }
                    }
                }
            }
        }
    },
    remove_related_box: function () {
        if (this.related_boxs_loc) {
            if (this.related_boxs_loc.length >= 3) {
                for (var idx in this.related_boxs_loc) {
                    var loc = this.related_boxs_loc[idx];
                    var box = this.getBoxAtLoc(loc, 1);
                    if (box) {
                        box.controller.remove_gfx();
                        if (box.controller.box_id == 3 ||
                            box.controller.box_id == 0) {
                            box.controller.remove(true);
                        } else {
                            box.controller.remove(null);
                        }
                    }
                }
            }
        }
    },
    remove_related_box2: function () {
        if (this.related_boxs_loc2) {
            if (this.related_boxs_loc2.length >= 3) {
                for (var idx in this.related_boxs_loc2) {
                    var loc = this.related_boxs_loc2[idx];
                    var box = this.getBoxAtLoc(loc, 2);
                    if (box) {
                        box.controller.remove_gfx();
                        if (box.controller.box_id == 3 ||
                            box.controller.box_id == 0) {
                            box.controller.remove(false);
                        } else {
                            box.controller.remove(null);
                        }
                    }
                }
            }
        }
    },

    // 补位
    repair_map: function (panel_id) {
        var column_had_removed;
        if (panel_id == 1) {
            column_had_removed = Core2.column_had_removed;
        } else {
            column_had_removed = Core2.column_had_removed2;
        }
        for (var n = this.cur_n - 1; n >= column_had_removed + 1; n--) {
            for (var m = 0; m < Data.height; m++) {
                var loc = cc.p(n, m);
                var box = this.getBoxAtLoc(loc, panel_id);
                if (box == null) {
                    var box1 = this.get_box_condition_2(loc, panel_id);
                    if (box1) {
                        this.repair_move(box1.controller.loc, loc, panel_id);
                    } else {
                        // todo: 没有了的情况需要生成新的
                    }
                }
            }

        }
    },
    // 补位移动,从loc0移动到loc1: loc0原来非空, loc1原来空
    repair_move: function (loc0, loc1, panel_id) {
        var box0 = this.getBoxAtLoc(loc0, panel_id);
        var box1 = this.getBoxAtLoc(loc1, panel_id);
        if (box0 == null) {
            return;
        }
        if (box1 != null) {
            return;
        }
        // 数据
        if (panel_id == 1) {
            this.box_lists[loc1.x][loc1.y] = box0;
            this.box_lists[loc0.x][loc0.y] = null;
        } else {
            this.box2_lists[loc1.x][loc1.y] = box0;
            this.box2_lists[loc0.x][loc0.y] = null;
        }

        box0.controller.loc = loc1;

        box0.controller.mid_node.setZOrder(110);

        var destination_pos = this.loc2pos(loc1);
        var move_action = cc.EaseExponentialInOut.create(
            cc.MoveTo.create(.4, destination_pos)
        );
        var call_action = cc.CallFunc.create(
            function () {
                this.controller.mid_node.setZOrder(100)
            }, box0
        );
        var action = cc.Sequence.create(move_action, call_action);
        action.setTag(3);
        box0.controller.mid_node.stopActionByTag(3);
        box0.controller.mid_node.runAction(action);
    },
    // 以一个loc往右找,返回第一个不为空的box, 如果没有则返回null
    //get_box_condition_1: function (loc) {
    //    var n = loc.x;
    //    do {
    //        n++;
    //
    //        if (n == this.cur_n) {
    //            this.create_a_box(loc);
    //            return null;
    //        }
    //
    //        if (n == this.cur_n - 1 && this.box_lists[n][loc.y] == null) {
    //            var ccb_node = this.create_a_box(cc.p(n, loc.y));
    //            return ccb_node;
    //        }
    //
    //        var loc1 = cc.p(n, loc.y);
    //        var box = this.getBoxAtLoc(loc1);
    //        if (box) {
    //            return box;
    //        }
    //    } while (n <= this.cur_n - 1);
    //
    //
    //    return ccb_node;
    //},

    // 以一个loc往左找,返回第一个不为空的box, 如果没有则返回null
    get_box_condition_2: function (loc, panel_id) {
        var n = loc.x;
        do {
            n--;

            if (n == (panel_id == 1 ? Core2.column_had_removed : Core2.column_had_removed2) + 1) {
                this.create_a_box(loc, panel_id);
                return null;
            }

            if (n == (panel_id == 1 ? Core2.column_had_removed : Core2.column_had_removed2) && this.box_lists[n][loc.y] == null) {
                var ccb_node = this.create_a_box(cc.p(n, loc.y), panel_id);
                return ccb_node;
            }

            var loc1 = cc.p(n, loc.y);
            var box = this.getBoxAtLoc(loc1, panel_id);
            if (box) {
                return box;
            }
        } while (n >= (panel_id == 1 ? Core2.column_had_removed : Core2.column_had_removed2) + 1);


        return ccb_node;
    },


    combine_related_box: function (loc, panel_id) {

        var box = this.getBoxAtLoc(loc, panel_id);
        if (box == null) return;
        var dest_pos = box.controller.mid_node.getPosition();

        var related_boxs_loc;
        if (panel_id == 1) {
            related_boxs_loc = this.related_boxs_loc;
        } else if (panel_id == 2) {
            related_boxs_loc = this.related_boxs_loc2;
        } else {
            cc.log();
        }

        if (related_boxs_loc) {
            if (related_boxs_loc.length >= 3) {
                var extra_sum = 0;
                for (var idx in related_boxs_loc) {
                    var loc1 = related_boxs_loc[idx];
                    var box1 = this.getBoxAtLoc(loc1, panel_id);
                    if (box1) {
                        if (box1 != box) {
                            extra_sum += box1.controller.number_value - 1;
                            box1.controller.combine_remove(dest_pos);
                        }
                    }
                }

                box.controller.delay_scale_big_then_normal();
                box.controller.remove_gfx();
                box.controller.number_value = Math.pow(related_boxs_loc.length, 2) + extra_sum;
            }
        }
    },

    create_a_box: function (loc, panel_id) {
        var it = Data.getRandomId();
        var mid_node = cc.Node.create();
        var ccbi_name = Data.box[it].ccbi_file;
        var ccb_node = cc.BuilderReader.load(ccbi_name);

        ccb_node.controller.panel_id = panel_id;
        ccb_node.controller.loc = cc.p(loc.x, parseInt(loc.y));
        ccb_node.controller.mid_node = mid_node;
        ccb_node.controller.box_id = it;
        ccb_node.controller.number_value = 1;
        ccb_node.controller.refresh_show();
        ccb_node.controller.is_reward = true;

        mid_node.addChild(ccb_node, 0, 1);
        mid_node.setPosition(this.loc2pos(cc.p(loc.x, parseInt(loc.y))));

        if (panel_id == 1) {
            this.stage.addChild(mid_node, 100);
            this.box_lists[loc.x][loc.y] = ccb_node;
        } else {
            this.stage2.addChild(mid_node, 100);
            this.box2_lists[loc.x][loc.y] = ccb_node;
        }
        return ccb_node;
    }
};