/**
 * Created by leadprogrammer on 12/30/14.
 */

var Data = {

    data: [],

    height: 9,
    width: 200,

    init: function () {
        for (var n = 0; n < this.width; n++) {
            var row = [];
            for (var m = 0; m < this.height; m++) {
                row.push(Math.floor(Math.random() * 2));
            }
            this.data.push(row);
        }
    }
};
