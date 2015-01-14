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

                row.push(Data.getRandomId());
            }
            this.data.push(row);
        }
    },

    getRandomId: function () {
        var r = Math.random();
        var id;
        if (r < .04) {
            id = 4;
        } else if (r < .35) {
            id = 1;
        } else if (r < .60) {
            id = 0;
        } else if (r < .80) {
            id = 2;
        } else {
            id = 3;
        }
        return id;
    },

    box: [
        {'ccbi_file': 'Assets/CCBI/Common/NBox_01.ccbi'}, // attack
        {'ccbi_file': 'Assets/CCBI/Common/NBox_02.ccbi'}, // exp
        {'ccbi_file': 'Assets/CCBI/Common/NBox_03.ccbi'}, // gold
        {'ccbi_file': 'Assets/CCBI/Common/NBox_04.ccbi'}, // hp
        {'ccbi_file': 'Assets/CCBI/Common/NBox_05.ccbi'} // empty
    ],

    core: undefined,
    gLCore: undefined
};
