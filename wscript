srcdir = "."
blddir = "build"
APPNAME = "node-inotify"
VERSION = "0.1.4"

def set_options(ctx):
  ctx.add_option('--exe', action='store_true', default=False)
  ctx.recurse('src')

def configure(ctx):
  ctx.recurse('src')

def spec(spec):
    import Options, Utils
    if Options.options.exe:
            Utils.exec_command('${NODE} specs.js')

def build(ctx):
  ctx.recurse('src')
  ctx.add_post_fun(spec)

