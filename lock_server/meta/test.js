"encrypt?" + new URLSearchParams({
	ID: "3CD679DBC30DA695C321E2D55EFDD695",
	data: "aGVsbG8gd29ybGQh",
	timestamp: 1000,
}).toString();


"decrypt?" + new URLSearchParams({
	type: "data",
	timestamp: "1000",
	hash: "ANDKLVOf0PcCZl3YzQYZEJbiie4s/Rq90Gx9GukIxrg=",
	ID: "3CD679DBC30DA695C321E2D55EFDD695",
	data: "IF+urRwjwgaOOAVLGwyEHw=="
}).toString();



function _loop() {
	$.get('https://39.107.123.167:8083/lock/test/get_id', function(id) {
		let data = '' + Math.random() + Math.random() + Math.random() + Math.random() + Math.random() + Math.random() + Math.random() + Math.random() + Math.random();
		let timestamp = +new Date();
		$.get('https://39.107.123.167:8083/lock/test/' + "encrypt?" + new URLSearchParams({
			ID: id,
			data: btoa(data),
			timestamp: timestamp,
		}).toString(), function(data0) {
			console.log(data0.encryptedData);
			$.get('https://39.107.123.167:8083/lock/test/' + "decrypt?" + new URLSearchParams({
				type: "data",
				timestamp: timestamp,
				hash: data0.calculatedHash,
				ID: id,
				data: data0.encryptedData
			}).toString(), function(data1) {
				if (data !== data1.decryptedData)
					console.log('Error: ', data0, data1);
				return _loop();
			});
		});
	});
}
_loop();






