#ifndef _PRODUCER_WRAP
#define _PRODUCER_WRAP

#include <v8.h>
#include <nan.h>
#include <Producer.h>
#include "ONSFactoryWrap.h"


class ProducerWrap : public Nan::ObjectWrap {
    public:
        static void Init(v8::Local<v8::Object> exports);

    private:
        ProducerWrap();
        ~ProducerWrap();

        static NAN_METHOD(New);
        static NAN_METHOD(Start);
        static NAN_METHOD(Shutdown);
        static NAN_METHOD(Send);
        static NAN_METHOD(SendOneway);


        static Nan::Persistent<v8::Function> constructor;
        ons::Producer* _producer;

        friend class ONSFactoryWrap;
};

#endif