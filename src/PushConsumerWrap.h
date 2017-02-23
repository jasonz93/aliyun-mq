#ifndef __PUSH_CONSUMER_WRAP
#define __PUSH_CONSUMER_WRAP

#include <nan.h>
#include <PushConsumer.h>
#include "ONSFactoryWrap.h"

class PushConsumerWrap : public Nan::ObjectWrap {
    public:
        static void Init(v8::Local<v8::Object> exports);

    private:
        explicit PushConsumerWrap();
        ~PushConsumerWrap();

        static NAN_METHOD(New);
        static NAN_METHOD(Start);
        static NAN_METHOD(Shutdown);
        static NAN_METHOD(Subscribe);

        static Nan::Persistent<v8::Function> constructor;
        ons::PushConsumer* _consumer;

        friend class ONSFactoryWrap;
};



#endif