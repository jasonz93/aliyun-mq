#ifndef _MESSAGE_WRAP
#define _MESSAGE_WRAP

#include <node.h>
#include <node_object_wrap.h>
#include <v8.h>
#include <nan.h>
#include <Message.h>
#include "utils.h"
#include "BaseMessageListener.h"

using namespace v8;

class MessageWrap : public Nan::ObjectWrap {
    public:
        static void Init(v8::Local<v8::Object> exports);
        ons::Message* getMessage();
        void setMessage(ons::Message* message);
        static Nan::Persistent<Function> constructor;

    private:
        MessageWrap(ons::Message* message);
        MessageWrap();
        ~MessageWrap();
        static NAN_METHOD(New);
        static NAN_METHOD(PutUserProperty);
        static NAN_METHOD(GetUserProperty);
        static NAN_SETTER(SetProperties);
        static NAN_GETTER(GetProperties);
        static NAN_METHOD(PutSystemProperty);
        static NAN_METHOD(GetSystemProperty);

        static NAN_SETTER(Setter);
        static NAN_GETTER(Getter);

        static NAN_METHOD(ToString);
        static NAN_METHOD(ToSystemString);
        static NAN_METHOD(ToUserString);

        ons::Message* _message;

        friend class BaseMessageListener;
};

#endif