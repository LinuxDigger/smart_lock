function start_long_polling(id) {
    let error_count = 0;
    function poll() {
        $.ajax({
            type: "GET",
            url: '../msg/get',
            timeout: LONG_POLLING_TIMEOUT,
            data: {
                id: id
            },
            success: function (data) {
                //            console.log(data);
                switch (data.status) {
                    case 0:
                        process_msg(data.from, JSON.parse(data.msg));
                        poll();
                        break;
                    case 1:
                        poll();
                        break;
                }
                error_count = 0;
            },
            error: function (jqXHR, textStatus, errorThrown) {
                console.log('Ajax error!', jqXHR, textStatus, errorThrown);
                if (5 < error_count)
                    return console.log('Fatal error: polling stoped!');
                ++error_count;
                poll();
            }
        });
    }
    poll();
}


function process_msg(from, msg) {
    $(document).trigger('on_msg', [from, msg]);
}



//send_msg(CLIENT_ID,[LOCK_ID],'hello lock!!!!!!',console.log);

function send_msg(from, to, msg, callback) {
    $.ajax({
        type: "POST",
        url: '../msg/send',
        contentType: 'application/json',
        timeout: LONG_POLLING_TIMEOUT,
        data: JSON.stringify({
            from: from,
            to: to,
            msg: JSON.stringify(msg),
        }),
        success: function (data) {
            callback(data);
        },
        error: function (jqXHR, textStatus, errorThrown) {
            callback(errorThrown);
            console.log('Ajax error!', jqXHR, textStatus, errorThrown);
        }
    });
}



