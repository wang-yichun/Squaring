/**
 * Created by leadprogrammer on 9/24/14.
 */
var HpShow = {
    refresh_enemy_item_hp: function (enemy_list_item) {
        if (enemy_list_item.need_destroy) return;
        enemy_list_item.hp_node.setVisible(true);
        enemy_list_item.hp_node.unschedule(enemy_list_item.hp_node.delay_call);
        enemy_list_item.hp_node.scheduleOnce(enemy_list_item.hp_node.delay_call, 2);
        HpShow.set_hp_node(enemy_list_item.hp_node, enemy_list_item.hp, enemy_list_item.remain_hp);
    },

    refresh_hero_item_hp: function (hero_node) {
        hero_node.hp_node.setVisible(true);
        hero_node.hp_node.unschedule(hero_node.hp_node.delay_call);
        hero_node.hp_node.scheduleOnce(hero_node.hp_node.delay_call, 2);
        if (hero_node.para.hero_super_mode_status == HeroSuperModeStatus.Disabled) {
            HpShow.set_hero_hp_node(hero_node.hp_node, hero_node.para.hp, hero_node.para.remain_hp);
        } else {
            HpShow.set_hero_hp_node(hero_node.hp_node, hero_node.para.super_hp, hero_node.para.remain_hp);
        }
    },

    refresh_hero_item_charge: function (hero_node) {
        HpShow.set_hero_charge_node(hero_node.charge_node, hero_node.para.charge_need_time, hero_node.para.remain_charge_need_time);
    },

    refresh_barrier_item_hp: function (barrier_item) {
        barrier_item.hp_node.setVisible(true);
        barrier_item.hp_node.unschedule(barrier_item.hp_node.delay_call);
        barrier_item.hp_node.scheduleOnce(barrier_item.hp_node.delay_call, 3);
        HpShow.set_barrier_hp_node(barrier_item.hp_node, barrier_item.hp, barrier_item.remain_hp, barrier_item.node.controller['scope_box'].getContentSize().width);
    },

    set_hp_node: function (node, hp, remain_hp) {
        var hp_bar_length = 10; // 血条显示长度
        node.clear();
        var hp_point = remain_hp * hp_bar_length / hp - hp_bar_length / 2;
        node.drawSegment(cc.p(-hp_bar_length / 2, 0), cc.p(hp_point, 0), 1, cc.c4f(0, 1, 0, .5));
        if (remain_hp > 0) {
            if (remain_hp < hp) {
                node.drawSegment(cc.p(hp_point, 0), cc.p(hp_bar_length / 2, 0), 1, cc.c4f(1, 0, 0, .5));
            }
        }
    },

    set_hero_hp_node: function (node, hp, remain_hp) {
        var hp_bar_length = 30; // 血条显示长度
        node.clear();
        if (remain_hp > 0) {
            var hp_point = remain_hp * hp_bar_length / hp - hp_bar_length / 2;
            node.drawSegment(cc.p(-hp_bar_length / 2, 0), cc.p(hp_point, 0), 1, cc.c4f(0, 0.5, 1, .5));
            if (remain_hp < hp) {
                node.drawSegment(cc.p(hp_point, 0), cc.p(hp_bar_length / 2, 0), 1, cc.c4f(1, 0, 0, .5));
            }
        }
    },

    set_hero_charge_node: function (node, max, cur) {
        var bar_length = 30; // 血条显示长度
        node.clear();
        if (cur > 0) {
            var hp_point = (max - cur) * bar_length / max - bar_length / 2;
            node.drawSegment(cc.p(-bar_length / 2, 0), cc.p(hp_point, 0), 1, cc.c4f(0.5, 0.5, 0, .5));
            if (cur < max) {
                node.drawSegment(cc.p(hp_point, 0), cc.p(bar_length / 2, 0), 1, cc.c4f(1, 1, 0, .5));
            }
        }
    },

    set_barrier_hp_node: function (node, hp, remain_hp, bar_length) {
        node.clear();
        if (remain_hp > 0) {
            var hp_point = remain_hp * bar_length / hp - bar_length / 2;
            node.drawSegment(cc.p(-bar_length / 2, 0), cc.p(hp_point, 0), 1, cc.c4f(0, 0.5, 1, .5));
            if (remain_hp < hp) {
                node.drawSegment(cc.p(hp_point, 0), cc.p(bar_length / 2, 0), 1, cc.c4f(1, 0, 0, .5));
            }
        }
    }
};