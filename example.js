'use strict';
sys     = require('sys');
fs      = require('fs');
http = require('http');
Inotify = require('inotify').Inotify;

var inotify = new Inotify(); //persistent by default, new Inotify(false) //no persistent

var data = {}; //used to correlate two events

var callback = function(event) {
    var mask = event.mask;
    var type = mask & Inotify.IN_ISDIR ? 'directory ' : 'file ';
    event.name ? type += ' ' + event.name + ' ': ' ';

    //the porpuse of this hell of 'if'
    //statements is only illustrative.

    if(mask & Inotify.IN_ACCESS) {
        sys.puts(type + 'was accessed ');
    } else if(mask & Inotify.IN_MODIFY) {
        sys.puts(type + 'was modified ');
    } else if(mask & Inotify.IN_OPEN) {
        sys.puts(type + 'was opened ');
    } else if(mask & Inotify.IN_CLOSE_NOWRITE) {
        sys.puts(type + ' opened for reading was closed ');
    } else if(mask & Inotify.IN_CLOSE_WRITE) {
        sys.puts(type + ' opened for writing was closed ');
    } else if(mask & Inotify.IN_ATTRIB) {
        sys.puts(type + 'metadata changed ');
    } else if(mask & Inotify.IN_CREATE) {
        sys.puts(type + 'created');
    } else if(mask & Inotify.IN_DELETE) {
        sys.puts(type + 'deleted');
    } else if(mask & Inotify.IN_DELETE_SELF) {
        sys.puts(type + 'watched deleted ');
    } else if(mask & Inotify.IN_MOVE_SELF) {
        sys.puts(type + 'watched moved');
    } else if(mask & Inotify.IN_IGNORED) {
        sys.puts(type + 'watch was removed');
    } else if(mask & Inotify.IN_MOVED_FROM) {
        data = event;
        data.type = type;
    } else if(mask & Inotify.IN_MOVED_TO) {
        if( Object.keys(data).length &&
            data.cookie === event.cookie) {
            sys.puts(type + ' moved to ' + data.type);
            data = {};
        }
    }
}

var dir = { path: './',
            watch_for: Inotify.IN_ALL_EVENTS,
            callback: callback
          };

var watch = inotify.addWatch(dir);

http.createServer(function (request, response) {
    response.writeHead(200, {'Content-Type': 'text/plain'});
    response.end('Hello World\n');
}).listen(8124);
console.log('Http server started');

