var JSBHelper = JSBHelper || {};
JSBHelper.selectorArray = {};

JSBHelper.SendMessageToAll = function (func_name, func_params) {
    if (sys.platform == 'browser') {
        //html5 浏览器
    } else { // sys.platform == “mobile”
        SendMessageToNative(func_name, func_params);
    }
};

JSBHelper.SendMessageToOC = function (func_name, func_params) {
    if (sys.platform == 'browser') {
        //html5 浏览器
    } else { // sys.platform == “mobile”
        if (sys.os == "windows") {
        } else if (sys.os == "android") {
        } else if (sys.os == "ios") {
            SendMessageToNative(func_name, func_params);
        }
    }
};

JSBHelper.SendMessageToJAVA = function (func_name, func_params) {
    if (sys.platform == 'browser') {
        //html5 浏览器
    } else { // sys.platform == “mobile”
        if (sys.os == "windows") {
        } else if (sys.os == "android") {
            SendMessageToNative(func_name, func_params);
        } else if (sys.os == "ios") {
        }
    }
};

JSBHelper.SendMessageToCPP = function (func_name, func_params) {
    if (sys.platform == 'browser') {
        //html5 浏览器
    } else { // sys.platform == “mobile”
        SendMessageToCpp(func_name, func_params);
    }
};

/**
 *
 * Before you want to call JS function on Cpp side,
 * you need to addSelector function to JSBHelper.
 *
 * @param func_name What function name you will plan to be called from Cpp side.
 * @param selector What function you will plan to be called from Cpp side.
 */
JSBHelper.AddSelector = function (func_name, selector) {
    if (sys.platform == 'browser')return;
//    cc.log("into JS: AddSelector");

    JSBHelper.selectorArray[func_name] = selector;
};

/**
 * This is callback from Cpp,
 * you don't need to understand it.
 *
 * @param func_name
 * @param returnValue
 * @constructor
 */
JSBHelper.GetMessageFromCpp = function (func_name, returnValue) {
    if (sys.platform == 'browser')return;

    if (JSBHelper.selectorArray[func_name] == null) {
        cc.log("[Error!!] Can't find function: " + func_name + ". Please ensure it has been addSelector in Javascript side.");
        return;
    }

    var returnValueMap = returnValue ? JSON.parse(returnValue) : null;

    JSBHelper.selectorArray[func_name](returnValueMap);

    delete JSBHelper.selectorArray[func_name];
};
