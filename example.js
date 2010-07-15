//require.paths.unshift('build/default/src');
sys     = require('sys');
fs      = require('fs');
http = require('http');
Inotify = require('node-inotify').Inotify;

var inotify = new Inotify(); //persistent by default, new Inotify(false) //no persistent

var callback = function(event) {
    var mask = event.mask;
    var type = mask & inotify.IN_ISDIR ? 'Directory ' : 'File ';
    event.name ? type += ' ' + event.name + ' ': ' ';

    if(mask & inotify.IN_ACCESS) {
        sys.puts(type + 'was accessed ');
    } else if(mask & inotify.IN_MODIFY) {
        sys.puts(type + 'was modified ');
    } else if(mask & inotify.IN_OPEN) {
        sys.puts(type + 'was opened ');
    } else if(mask & inotify.IN_CLOSE_NOWRITE) {
        sys.puts(type + ' opened for reading was closed ');
    } else if(mask & inotify.IN_CLOSE_WRITE) {
        sys.puts(type + ' opened for writing was closed ');
    } else if(mask & inotify.IN_MOVE) {
        sys.puts(type + 'was moved ');
    } else if(mask & inotify.IN_ATTRIB) {
        sys.puts(type + 'metadata changed ');
    } else if(mask & inotify.IN_CREATE) {
        sys.puts(type + 'created');
    } else if(mask & inotify.IN_DELETE) {
        sys.puts(type + 'deleted');
    } else if(mask & inotify.IN_DELETE_SELF) {
        sys.puts(type + 'watched deleted ');
    } else if(mask & inotify.IN_MOVE_SELF) {
        sys.puts(type + 'watched moved');
    } else if(mask & inotify.IN_IGNORED) {
        sys.puts(type + 'watch was removed');
    }
    //sys.puts(sys.inspect(event));
}

var tmp_dir = { path: '/home/camilo',
                watch_for: inotify.IN_ALL_EVENTS,
                callback: callback
               };

var watch = inotify.addWatch(tmp_dir);

http.createServer(function (request, response) {
    response.writeHead(200, {'Content-Type': 'text/plain'});
    response.end('Hello World\n');
}).listen(8124);
console.log('Http server started');

