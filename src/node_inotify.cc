// Copyright 2015, Camilo Aguilar.
#include "bindings.h"

namespace NodeInotify {
    void InitializeInotify(Handle<Object> exports) {
        Nan::HandleScope scope;

        Inotify::Initialize(exports);

        exports->Set(Nan::New<String>("version").ToLocalChecked(),
                    Nan::New<String>(NODE_INOTIFY_VERSION).ToLocalChecked());

        v8::Isolate* isolate = v8::Isolate::GetCurrent();
        Local<ObjectTemplate> global = ObjectTemplate::New(isolate);
        Handle<Context> context = Nan::New<Context>(reinterpret_cast<ExtensionConfiguration *>(NULL), global);
        Context::Scope context_scope(context);

        context->Global()->Set(Nan::New<String>("Inotify").ToLocalChecked(), exports);
    }

    extern "C" void init (Handle<Object> exports) {
        Nan::HandleScope scope;
        InitializeInotify(exports);
    }
} //namespace NodeInotify

NODE_MODULE(inotify, NodeInotify::init)
