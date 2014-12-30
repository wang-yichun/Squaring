/**
 * Created by leadprogrammer on 12/4/14.
 */

var JSMyTools = {
    isObjectValueEqual: function (a, b) {
        if (a == null && b != null) return false;
        if (a != null && b == null) return false;
        if (a == null && b == null) return true;

        // Of course, we can do it use for in
        // Create arrays of property names
        var aProps = Object.getOwnPropertyNames(a);
        var bProps = Object.getOwnPropertyNames(b);

        // If number of properties is different,
        // objects are not equivalent
        if (aProps.length != bProps.length) {
            return false;
        }

        for (var i = 0; i < aProps.length; i++) {
            var propName = aProps[i];

            // If values of same property are not equal,
            // objects are not equivalent
            if (typeof a[propName] == 'object' && typeof b[propName] == 'object') {
                if (this.isObjectValueEqual(a[propName], b[propName]) == false) {
                    return false;
                }
            } else if (typeof a[propName] != 'object' && typeof b[propName] != 'object') {
                if (a[propName] !== b[propName]) {
                    return false;
                }
            } else {
                return false;
            }
        }

        // If we made it this far, objects
        // are considered equivalent
        return true;
    }
};