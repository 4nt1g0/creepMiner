var logSetting = {};

function update_settings(config) {
    mining_info_url.val(config['miningInfoUrl'] + ':' + config['miningInfoUrlPort']);
    submission_url.val(config['poolUrl'] + ':' + config['poolUrlPort']);
    wallet_url.val(config['walletUrl'] + ':' + config['walletUrlPort']);

    intensity.val(config['miningIntensityRaw']);
    buffer_size.val(config['bufferSizeRaw']);
    plot_readers.val(config['maxPlotReadersRaw']);
    submission_max_retry.val(config['submissionMaxRetry']);
	submit_probability.val(config['submitProbability']);
    target_deadline.val(config['targetDeadlineLocal']);

    timeout.val(config['timeout']);

    log_dir.val(config['logDir']);

    for (var key in config['channelPriorities']) {
        window['cmb_' + key].val(config['channelPriorities'][key].numeric);
    }
}

function connectCallback(msg) {
    data = msg["data"];

    if (data) {
        if (data == "ping") {
            return;
        }

        var response = JSON.parse(data);

        switch (response["type"]) {
            case "config":
                update_settings(response);
                break;
            default:
                break;
        }
    }
}

window.onload = function (evt) {
    $("#btnSettings").addClass('active');
    logSetting = initSettings($("#settingsDlComboboxes"));

    mining_info_url = $("#mining-info-url");
    submission_url = $("#submission-url");
    wallet_url = $("#wallet-url");

    intensity = $("#intensity");
    buffer_size = $("#buffer-size");
    plot_readers = $("#plot-readers");
    submission_max_retry = $("#submission-max-retry");
	submit_probability = $("#submit-probability");
    target_deadline = $("#target-deadline");
    timeout = $("#timeout");

    log_dir = $("#log-dir");

    loggers.forEach(function (element) {
        var id = "cmb_" + element[0];
        window[id] = $("#" + id);
    });

    connect(connectCallback);
}
