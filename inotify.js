try {
    module.exports = require('./build/Debug/inotify');
} catch(e) {
    module.exports = require('./build/Release/src/inotify');
}
