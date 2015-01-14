/**
 * Created by leadprogrammer on 14-7-28.
 * might be ignored local
 */

var SwitcherConfig = {
    sceneInfo: undefined,
    init: function () {
        this.sceneInfo = {
            'SceneA': { // scene_info
                'class': 'SceneA',
                'object': gSceneA,
                'layers': {
                    'core_group': {
                        //'LCore': {
                        //    ccbi: RES_CCBI_LCore,
                        //    in_timeline: {name: null, time: 0.1},
                        //    out_timeline: {name: null, time: 0.1},
                        //    zorder: 50
                        //    //mutex_layers: [
                        //    //    {group_id: 'group_editer'},
                        //    //    {group_id: 'top_panel'},
                        //    //    {group_id: 'left_panel'},
                        //    //    {group_id: 'popup_panel'}
                        //    //]
                        //},

                        'LCore2': {
                            ccbi: RES_CCBI_LCore2,
                            in_timeline: {name: null, time: 0.1},
                            out_timeline: {name: null, time: 0.1},
                            zorder: 50
                            //mutex_layers: [
                            //    {group_id: 'group_editer'},
                            //    {group_id: 'top_panel'},
                            //    {group_id: 'left_panel'},
                            //    {group_id: 'popup_panel'}
                            //]
                        }
                    },
                    'popup_group': {
                        'LMenuInGame': {
                            ccbi: RES_CCBI_LMenuInGame,
                            in_timeline: {name: null, time: 0.1},
                            out_timeline: {name: null, time: 0.1},
                            zorder: 60,
                            mutex_layers: [
                                {group_id: 'core_group'}
                            ]
                        }
                    }
                }

            },

            'MyScene': {
                'class': 'MyScene',
                'object': gMyScene,
                'layers': {}
            }
        }
    }
};
