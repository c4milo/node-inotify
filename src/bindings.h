// Copyright 2015, Camilo Aguilar.
#ifndef SRC_BINDINGS_H_
#define SRC_BINDINGS_H_
#include "node_inotify.h"

namespace NodeInotify {

	class Inotify : public Nan::ObjectWrap {
		public:
			static void Initialize(Handle<Object> target);

			Inotify();
			Inotify(bool nonpersistent);
			virtual ~Inotify();
		protected:
			static NAN_METHOD(New);
			static NAN_METHOD(AddWatch);
			static NAN_METHOD(RemoveWatch);
			static NAN_METHOD(Close);
			static NAN_GETTER(GetPersistent);

		private:
			int fd;
			uv_poll_t* read_watcher;
			bool persistent;
			char poll_stopped;
			void StopPolling();
			static void Callback(uv_poll_t* watcher, int status, int revents);
			static void on_handle_close(uv_handle_t* handle);
	};

}  //namespace NodeInotify

#endif  // SRC_BINDINGS_H

