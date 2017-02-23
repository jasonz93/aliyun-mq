#ifndef _ONSFactory
#define _ONSFactory

#include <nan.h>
#include <ONSFactory.h>

class ONSFactoryWrap : public Nan::ObjectWrap {
    public:
        static void Init(v8::Local<v8::Object> exports);

    private:
        explicit ONSFactoryWrap(v8::Local<v8::Object> props);
        ~ONSFactoryWrap();

        static void SetPropertyIfExists(ons::ONSFactoryProperty* factoryInfo, const char* key, v8::Local<v8::Object> props, const char* propsKey);

        static NAN_METHOD(New);
        static NAN_METHOD(CreateProducer);
        static NAN_METHOD(CreatePushConsumer);
        static NAN_METHOD(CreateOrderConsumer);
        static NAN_METHOD(CreateOrderProducer);

        static Nan::Persistent<v8::Function> constructor;
        ons::ONSFactoryProperty _factoryInfo;
};


#endif