let log_type = ['lock', 'unlock', 'open_door', 'close_door', 'abnormal', 'danger', 'info', 'error', ]
log_type = (function () {
    let _log_type = {};
    for (let i in log_type)
        _log_type[log_type[i]] = +i;
    return _log_type;
})();
