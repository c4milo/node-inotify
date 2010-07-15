# Node-inotify - monitoring file system events in Gnu/Linux with [NodeJS][nodejs_home]
The inotify API provides a mechanism for monitoring file system events.
Inotify can be used to monitor individual files, or to monitor directories.
When a directory is monitored, inotify will return events for the directory
itself, and for files inside the directory. [(ref: GNU/Linux Manual)][inotify.7]

## Building
You must have [NodeJS][nodejs_dev] already installed to be able to build node-inotify

    git clone git://github.com/c4milo/node-inotify.git

    $ cd node-inotify
    $ node-waf configure build

### NPM
    $npm install inotifyjs

## API
  * **`var inotify = new Inotify(persistent)`** TODO
  * **inotify.addWatch(arg):**  TODO
  * **inotify.removeWatch(watch_descriptor):** TODO
  * **inotify.close():** TODO

## Example of use
This code
    sys     = require('sys');
    fs      = require('fs');
    Inotify = require('node-inotify').Inotify;

    //You can use new Inotify(false) for non persistent fashion. Maybe to be used
    // with Connect, ExpressJs, etc.
    var inotify = new Inotify(); //persistent by default

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
    var home_dir = { path:      '/home/camilo',
                     watch_for: inotify.IN_ALL_EVENTS,
                     callback:  callback
                  };

    var home_watch_descriptor = inotify.addWatch(home_dir);

    var home2_dir = { path:      '/home/bob',
                      watch_for: inotify.IN_ALL_EVENTS,
                      callback:  callback
                  };

    var home2_wd = inotify.addWatch(home2_dir);


## Inotify Events

### Watch for:
 * **inotify.IN_ACCESS:** File was accessed (read)
 * **inotify.IN_ATTRIB:** Metadata changed, e.g., permissions, timestamps, extended attributes, link count (since Linux 2.6.25), UID, GID, etc.
 * **inotify.IN_CLOSE_WRITE:** File opened for writing was closed
 * **inotify.IN_CLOSE_NOWRITE:** File not opened for writing was closed
 * **inotify.IN_CREATE:** File/directory created in the watched directory
 * **inotify.IN_DELETE:** File/directory deleted from the watched directory
 * **inotify.IN_DELETE_SELF:** Watched file/directory was itself deleted
 * **inotify.IN_MODIFY:** File was modified
 * **inotify.IN_MOVE_SELF:** Watched file/directory was itself moved
 * **inotify.IN_MOVED_FROM:** File moved out of the watched directory
 * **inotify.IN_MOVED_TO:** File moved into watched directory
 * **inotify.IN_OPEN:** File was opened
 * **inotify.IN_ALL_EVENTS:** watch for all kind of events
 * **inotify.IN_CLOSE:**  (IN_CLOSE_WRITE | IN_CLOSE_NOWRITE)  Close
 * **inotify.IN_MOVE:**  (IN_MOVED_FROM | IN_MOVED_TO)  Moves

### Additional Flags:
 * **inotify.IN_ONLYDIR:** Only watch the path if it is a directory.
 * **inotify.IN_DONT_FOLLOW:** Do not follow symbolics links
 * **inotify.IN_ONESHOT:** Only send event once
 * **inotify.IN_MASK_ADD:** Add (OR) events to watch mask for this pathname if it already exists (instead of replacing mask).

### The following bits may be set in the mask field returned in the callback
 * **inotify.IN_IGNORED:** Watch was removed explicitly with inotify.removeWatch(watch_descriptor) or automatically (the file was deleted, or the file system was unmounted)
 * **inotify.IN_ISDIR:** Subject of this event is a directory
 * **inotify.IN_Q_OVERFLOW:** Event queue overflowed (wd is -1 for this event)
 * **inotify.IN_UNMOUNT:** File system containing the watched object was unmounted



## License
(The MIT License)

Copyright 2010 Camilo Aguilar. All rights reserved.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to
deal in the Software without restriction, including without limitation the
rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
sell copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
IN THE SOFTWARE.


[inotify.7]: http://www.kernel.org/doc/man-pages/online/pages/man7/inotify.7.html "http://www.kernel.org/doc/man-pages/online/pages/man7/inotify.7.html"
[nodejs_home]: http://www.nodejs.org
[nodejs_dev]: http://github.com/ry/node
[code_example]: http://gist.github.com/476119

