// nodejs, this is the shortest http server I ever seem so far...
var http = require('http');

http.createServer(
    function (req, res) {
        res.write('Hello World!');
        res.end();
    }).listen(8888);
