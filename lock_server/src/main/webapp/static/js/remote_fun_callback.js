function on_list_log(logs) {
    app.logs = [];
    for (let log of logs.reverse()) {
        let type = log.content;
        let remark = {};
        if (log.remark)
            remark = JSON.parse(log.remark);

        let time = new Date(log.create_time);
        let year = padding_zeros(time.getFullYear(), 4),
            month = padding_zeros(time.getMonth() + 1, 2),
            day = padding_zeros(time.getDate(), 2),
            hour = time.getHours(),
            minute = padding_zeros(time.getMinutes(), 2),
            second = padding_zeros(time.getSeconds(), 2);

        let infos = object2array(remark);
        infos.unshift(['时间', `${hour}:${minute}:${second}`]);
        switch (log.type) {
            case log_type.lock:
            case log_type.unlock:
            case log_type.open_door:
            case log_type.close_door:
                app.logs.push({
                    create_time: `${year}年${month}月${day}日`,
                    type: type,
                    infos: infos,
                    buttons: [['primary', '删除记录'], ]
                });
                break;
            case log_type.abnormal:
            case log_type.danger:
                app.logs.push({
                    create_time: `${year}年${month}月${day}日`,
                    type: type,
                    infos: infos,
                    buttons: [['default', '删除记录'], ['primary', '查看视频记录'], ]
                });
                break;
            default:
                app.logs.push({
                    create_time: `${year}年${month}月${day}日`,
                    type: type,
                    infos: infos,
                    buttons: []
                });
        }
    }
}

function on_list_password(passwords) {

}

function on_notice(_notice) {
    notice = {
        icon_class: 'fa-info-circle',
        icon_color: '#07c160',
        content: null,
        badge_class: '',
        badge_content: '',
        action: function (notice) {
            console.log(notice);
        },
    };
    switch (_notice.type) {
        case 'guest':
            notice.icon_class = 'fa-info-circle';
            notice.icon_color = '#07c160';
            notice.content = _notice.title;
            notice.badge_content = 'New';
            notice.action = function (notice) {
                weui.dialog({
                    title: _notice.title,
                    content: _notice.content,
                    className: 'custom-classname',
                    buttons: [{
                        label: '开门',
                        type: 'default',
                        onClick: function () {}
                                }, {
                        label: '查看监控',
                        type: 'primary',
                        onClick: function () {
                            $('.weui-tabbar__item').eq(3).click();
                        }
                            }],
                });
            };
            break;
        case 'log':
            notice.icon_class = 'fa-book';
            notice.icon_color = '#365aff';
            notice.content = _notice.title;
            notice.badge_class = 'weui-badge_dot';
            notice.action = function (notice) {
                $('.weui-tabbar__item').eq(1).click();
            };
            break;
        case 'abnormal':
            notice.icon_class = 'fa-user-secret';
            notice.icon_color = '#7e00ff';
            notice.content = _notice.title;
            notice.badge_class = 'weui-badge_dot';
            notice.action = function (notice) {
                weui.dialog({
                    title: _notice.title,
                    content: _notice.content,
                    className: 'custom-classname',
                    buttons: [{
                        label: '忽略',
                        type: 'default',
                        onClick: function () {}
                                }, {
                        label: '查看监控',
                        type: 'primary',
                        onClick: function () {
                            $('.weui-tabbar__item').eq(3).click();
                        }
                            }],
                });
            };
            break;
        case 'danger':
            notice.icon_class = 'fa-bell';
            notice.icon_color = 'red';
            notice.content = _notice.title;
            notice.badge_class = 'weui-badge_dot';
            notice.action = function (notice) {
                weui.dialog({
                    title: _notice.title,
                    content: _notice.content,
                    className: 'custom-classname',
                    buttons: [{
                        label: '忽略',
                        type: 'default',
                        onClick: function () {}
                                }, {
                        label: '查看监控',
                        type: 'primary',
                        onClick: function () {
                            $('.weui-tabbar__item').eq(3).click();
                        }
                            }],
                });
            };
            break;
        default:
            break;
    }
    play_notice_sound();
    app.notices.unshift(notice);
}

let get_image_handler = function (image) {
    console.log(image);
};

function set_on_get_image_handler(handler) {
    get_image_handler = handler;
}

function on_get_image(image) {
    get_image_handler(image);
}

(function () {
    $(document).on("on_msg", function (event, from, msg) {
        switch (msg.type) {
            case 'on_list_log':
                on_list_log.apply(null, msg.data);
                break;
            case 'on_list_password':
                on_list_password.apply(null, msg.data);
                break;
            case 'on_notice':
                on_notice.apply(null, msg.data);
                break;
            case 'on_get_image':
                on_get_image.apply(null, msg.data);
                break;
            default:
                console.log(event, from, msg);
        }
    });
})();
