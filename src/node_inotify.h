// Copyright 2010, Camilo Aguilar. Cloudescape, LLC.
#ifndef SRC_NODE_INOTIFY_H_
#define SRC_NODE_INOTIFY_H_

// Silence incompatible cast warning from Nan::AsyncQueueWorker(Nan::AsyncWorker*)
// https://github.com/nodejs/nan/issues/807
#if defined(__GNUC__) && __GNUC__ >= 8
#define DISABLE_WCAST_FUNCTION_TYPE _Pragma("GCC diagnostic push") _Pragma("GCC diagnostic ignored \"-Wcast-function-type\"")
#define DISABLE_WCAST_FUNCTION_TYPE_END _Pragma("GCC diagnostic pop")
#else
#define DISABLE_WCAST_FUNCTION_TYPE
#define DISABLE_WCAST_FUNCTION_TYPE_END
#endif

#include <node.h>
#include <node_version.h>
#include <node_object_wrap.h>
#include <sys/inotify.h>
#include <sys/select.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
DISABLE_WCAST_FUNCTION_TYPE
#include <nan.h>
DISABLE_WCAST_FUNCTION_TYPE_END

#define NODE_INOTIFY_VERSION "1.3.0"

using namespace v8;
using namespace node;

namespace NodeInotify {

}

#endif  // SRC_NODE_INOTIFY_H_
