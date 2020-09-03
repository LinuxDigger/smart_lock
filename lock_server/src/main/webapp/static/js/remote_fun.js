const lock = {
    lock: function (callback) {
        send_msg(CLIENT_ID, [LOCK_ID], {
            type: 'lock',
            data: []
        }, callback);
    },
    unlock: function (callback) {
        send_msg(CLIENT_ID, [LOCK_ID], {
            type: 'unlock',
            data: []
        }, callback);
    },
    open_door: function (callback) {
        send_msg(CLIENT_ID, [LOCK_ID], {
            type: 'open_door',
            data: []
        }, callback);
    },
    close_door: function (callback) {
        send_msg(CLIENT_ID, [LOCK_ID], {
            type: 'close_door',
            data: []
        }, callback);
    },
    list_log: function (callback) {
        send_msg(CLIENT_ID, [LOCK_ID], {
            type: 'list_log',
            data: []
        }, callback);
    },
    list_password: function (callback) {
        send_msg(CLIENT_ID, [LOCK_ID], {
            type: 'list_password',
            data: []
        }, callback);
    },
    get_image: function (mark_image, callback) {
        send_msg(CLIENT_ID, [LOCK_ID], {
            type: 'get_image',
            data: [mark_image]
        }, callback);
    },
}
