function show_toast(msg, timeout) {
    var $toast = $('#toast');
    $toast.find('.weui-toast>p').text(msg);
    $toast.fadeIn(100);
    setTimeout(function () {
        $toast.fadeOut(100);
    }, timeout);
}

function show_loading(msg) {
    var $loadingToast = $('#loadingToast');
    $loadingToast.find('.weui-toast>p').text(msg);
    $loadingToast.fadeIn(100);
    return function () {
        $loadingToast.fadeOut(100);
    };
}


function lock_button_click(app) {
    if (app.is_locked) {
        let close = show_loading('正在开锁');
        lock.unlock(console.log);
        setTimeout(function () {
            lock.open_door(console.log);
            setTimeout(function () {
                close();
                show_toast('开锁成功', 1000);
                app.is_locked = false;
            }, 1000);
        }, 1000);
    } else {
        let close = show_loading('正在关锁');
        lock.close_door(console.log);
        setTimeout(function () {
            lock.lock(console.log);
            close();
            app.is_locked = true;
        }, 6000);
    }
}






function padding_zeros(str, length) {
    return ('' + str).padStart(length, 0);
}

function object2array(object) {
    let array = [];
    for (let prop in object) {
        array.push([prop, object[prop]]);
    }
    return array;
}

function play_notice_sound() {
    new_notice_sound.currentTime = 0;
    new_notice_sound.play();
}



function start_monitor() {
    let info = null;
    let is_stop = false;

    function _loop(mark_image) {
        lock.get_image(mark_image, function (data) {

        });
    }
    set_on_get_image_handler(function (image) {
        if (image.info)
            info = image.info;
        app.image_info = info;
        monitor_image.src = 'data:image/png;base64, ' + image.base64_img;
        console.log(image);
        if (!is_stop)
            _loop(true);
    })
    _loop(true);

    function stop_monitor() {
        is_stop = true;
    }
    return stop_monitor;
}
