// Copyright 2015, Camilo Aguilar.
#include "bindings.h"

namespace NodeInotify {
    void InitializeInotify(Local<Object> exports) {
        Nan::HandleScope scope;
        v8::Isolate* isolate = v8::Isolate::GetCurrent();
        Local<ObjectTemplate> global = ObjectTemplate::New(isolate);
        Local<Context> context = Nan::New<Context>(reinterpret_cast<ExtensionConfiguration *>(NULL), global);
        Inotify::Initialize(exports);

        auto i = v8::Isolate::GetCurrent();
        // auto ctx = i->GetCurrentContext();
        // FIXME: The maybe version fails here
        exports->Set(context, Nan::New<String>("version").ToLocalChecked(),
                    Nan::New<String>(NODE_INOTIFY_VERSION).ToLocalChecked());
        Context::Scope context_scope(context);
        context->Global()->Set(context,Nan::New<String>("Inotify").ToLocalChecked(), exports);
    }

    extern "C" void init (Local<Object> exports) {
        Nan::HandleScope scope;
        InitializeInotify(exports);
    }
} //namespace NodeInotify

NODE_MODULE(inotify, NodeInotify::init)
