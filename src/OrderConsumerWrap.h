//
// Created by nicholas on 17-2-23.
//

#ifndef ALIMQ_ORDERCONSUMERWRAP_H
#define ALIMQ_ORDERCONSUMERWRAP_H

#include <nan.h>
#include <OrderConsumer.h>
#include "ONSFactoryWrap.h"

class OrderConsumerWrap : public Nan::ObjectWrap {
public:
    static void Init(v8::Local<v8::Object> exports);

private:
    explicit OrderConsumerWrap();
    ~OrderConsumerWrap();

    static NAN_METHOD(New);

    static NAN_METHOD(Start);
    static NAN_METHOD(Shutdown);
    static NAN_METHOD(Subscribe);

    static Nan::Persistent<v8::Function> constructor;
    ons::OrderConsumer* consumer;

    friend class ONSFactoryWrap;
};


#endif //ALIMQ_ORDERCONSUMERWRAP_H
