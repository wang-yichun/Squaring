/**
 * Created by leadprogrammer on 10/8/14.
 */

var GeometryTools = {
    barrierContainsPoint: function (barrier, point) {
        var rect = barrier.node.controller['scope_box'].getBoundingBox();
        rect.x += barrier.node.getPosition().x;
        rect.y += barrier.node.getPosition().y;
//        var rect = barrier.node.getBoundingBox();
        if (rect.x < point.x && point.x < rect.x + rect.width) {
            if (rect.y < point.y && point.y < rect.y + rect.height) {
                return true;
            }
        }
        return false;
    },
    tingContainsPoint: function (ting, point) {
        var rect = cc.rect(ting.node.getPosition().x - 20, ting.node.getPosition().y, 40, 60);
        if (rect.x < point.x && point.x < rect.x + rect.width) {
            if (rect.y < point.y && point.y < rect.y + rect.height) {
                return true;
            }
        }
        return false;
    },
    barrierContainsPosition: function (barrier_item, position) {
        var distance = cc.pDistance(barrier_item.node.getPosition(), position);
        if (distance < 40) {
            return true;
        }
        return false;
    },
    getPointListCenter: function (point_list) {
        var x_sum = 0;
        var y_sum = 0;
        for (var i in point_list) {
            var p = point_list[i];
            x_sum += p.x;
            y_sum += p.y;
        }
        var center_point = cc.p(x_sum / point_list.length, y_sum / point_list.length);
        return center_point;
    },
    getLocDistance: function (loc1, loc2) {
        return Math.floor((Math.abs(loc1.x - loc2.x) + Math.abs(loc1.y - loc2.y)) * 10);
    }
};