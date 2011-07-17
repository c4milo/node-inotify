srcdir = "."
blddir = "build"
APPNAME = "node-inotify"
VERSION = "0.1.7"

def set_options(ctx):
  ctx.add_option('--exe', action='store_true', default=False)
  ctx.recurse('src')

def configure(ctx):
  ctx.recurse('src')

def build(ctx):
  ctx.recurse('src')

