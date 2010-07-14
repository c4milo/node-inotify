# Node-inotify - monitoring file system events in Gnu/Linux with [NodeJS][nodejs_home]
The inotify API provides a mechanism for monitoring file system events.
Inotify can be used to monitor individual files, or to monitor directories.
When a directory is monitored, inotify will return events for the directory
itself, and for files inside the directory. [(ref: GNU/Linux Manual)][inotify.7]

## Building
You must have [NodeJS][nodejs_dev] already installed to be able to build node-inotify

    git clone git://github.com/c4milo/node-inotify.git

    $ node-waf configure build install

## Example of use
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
 * inotify.IN_ACCESS: File was accessed (read)
 * inotify.IN_ATTRIB: Metadata changed, e.g., permissions, timestamps, extended attributes, link count (since Linux 2.6.25), UID, GID, etc.
 * inotify.IN_CLOSE_WRITE: File opened for writing was closed
 * inotify.IN_CLOSE_NOWRITE: File not opened for writing was closed
        NODE_DEFINE_CONSTANT(object_tmpl, IN_CREATE); //File/directory created in watched directory
        NODE_DEFINE_CONSTANT(object_tmpl, IN_DELETE); //File/directory deleted from watched directory
        NODE_DEFINE_CONSTANT(object_tmpl, IN_DELETE_SELF); //Watched file/directory was itself deleted
        NODE_DEFINE_CONSTANT(object_tmpl, IN_MODIFY); //File was modified
        NODE_DEFINE_CONSTANT(object_tmpl, IN_MOVE_SELF); //Watched file/directory was itself moved
        NODE_DEFINE_CONSTANT(object_tmpl, IN_MOVED_FROM); //File moved out of watched directory
        NODE_DEFINE_CONSTANT(object_tmpl, IN_MOVED_TO); //File moved into watched directory
        NODE_DEFINE_CONSTANT(object_tmpl, IN_OPEN); //File was opened
        NODE_DEFINE_CONSTANT(object_tmpl, IN_IGNORED); // Watch was removed explicitly (inotify.watch.rm) or
                                                       //automatically (file was deleted, or file system was
                                                        //unmounted)
        NODE_DEFINE_CONSTANT(object_tmpl, IN_ISDIR); //Subject of this event is a directory
        NODE_DEFINE_CONSTANT(object_tmpl, IN_Q_OVERFLOW); //Event queue overflowed (wd is -1 for this event)
        NODE_DEFINE_CONSTANT(object_tmpl, IN_UNMOUNT); //File system containing watched object was unmounted
        NODE_DEFINE_CONSTANT(object_tmpl, IN_ALL_EVENTS);

        NODE_DEFINE_CONSTANT(object_tmpl, IN_ONLYDIR); // Only watch the path if it is a directory.
        NODE_DEFINE_CONSTANT(object_tmpl, IN_DONT_FOLLOW); // Do not follow a sym link
        NODE_DEFINE_CONSTANT(object_tmpl, IN_ONESHOT); // Only send event once
        NODE_DEFINE_CONSTANT(object_tmpl, IN_MASK_ADD); //Add (OR) events to watch mask for this pathname if it
                                                        //already exists (instead of replacing mask).

        NODE_DEFINE_CONSTANT(object_tmpl, IN_CLOSE); // (IN_CLOSE_WRITE | IN_CLOSE_NOWRITE)  Close
        NODE_DEFINE_CONSTANT(object_tmpl, IN_MOVE);  //  (IN_MOVED_FROM | IN_MOVED_TO)  Moves

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

