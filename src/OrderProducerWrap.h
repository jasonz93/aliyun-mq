//
// Created by nicholas on 17-2-23.
//

#ifndef ALIMQ_ORDERPRODUCERWRAP_H
#define ALIMQ_ORDERPRODUCERWRAP_H

#include <nan.h>
#include <OrderProducer.h>
#include "ONSFactoryWrap.h"

class OrderProducerWrap : public Nan::ObjectWrap {
public:
    static void Init(v8::Local<v8::Object> exports);

private:
    explicit OrderProducerWrap();
    ~OrderProducerWrap();

    static NAN_METHOD(New);
    static NAN_METHOD(Start);
    static NAN_METHOD(Shutdown);
    static NAN_METHOD(Send);

    static Nan::Persistent<v8::Function> constructor;
    ons::OrderProducer* producer;

    friend class ONSFactoryWrap;
};


#endif //ALIMQ_ORDERPRODUCERWRAP_H
