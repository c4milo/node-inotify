// Copyright 2015, Camilo Aguilar.
#include "bindings.h"

namespace NodeInotify {
    void InitializeInotify(Handle<Object> exports) {
        NanScope();

        Inotify::Initialize(exports);

        exports->Set(NanNew<String>("version"),
                    NanNew<String>(NODE_INOTIFY_VERSION));

        Handle<ObjectTemplate> global = ObjectTemplate::New();
        Handle<Context> context = NanNew<Context>(reinterpret_cast<ExtensionConfiguration *>(NULL), global);
        Context::Scope context_scope(context);

        context->Global()->Set(NanNew<String>("Inotify"), exports);
    }

    extern "C" void init (Handle<Object> exports) {
        NanScope();
        InitializeInotify(exports);
    }
} //namespace NodeInotify

NODE_MODULE(inotify, NodeInotify::init)
