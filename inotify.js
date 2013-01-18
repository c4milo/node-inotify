try {
    module.exports = require('./build/Release/inotify');
} catch(e) {
    module.exports = require('./build/Debug/inotify');
}
