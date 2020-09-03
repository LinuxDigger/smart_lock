(function () {
    Vue.mixin({
        methods: {
            capitalizeFirstLetter: str => str.charAt(0).toUpperCase() + str.slice(1)
        }
    })



    var app = new Vue({
        el: '#app',
        data: {
            logs: [],
            passwords: [{
                create_date: '2020年07月16日',
                create_time: '07:32',
                type: '临时密码',
                content: '123456',
                urgent: '非紧急',
                infos: [
            ['创建者', '系统'],
            ['有效期', '无限制'],
        ],
    }],
            notices: [],
            new_log_count: 2,
            is_locked: true,
            image_info: null,
        },
        methods: {
            $: $,
            lock_button_click($event) {
                lock_button_click(app);
            },
            open_notice(index) {
                let notice = app.notices.splice(index, 1)[0];
                if (notice.action)
                    notice.action(notice);
            },
        },
    });


    window.app = app;
})();
