//
// Created by nicholas on 17-2-23.
//

#ifndef ALIMQ_ORDERPRODUCERSEND_H
#define ALIMQ_ORDERPRODUCERSEND_H

#include <nan.h>
#include <OrderProducer.h>
#include <ONSClientException.h>
#include "../utils.h"

class OrderProducerSend : public Nan::AsyncWorker {
public:
    explicit OrderProducerSend(ons::OrderProducer* producer, ons::Message* message, const char* shardingKey, Nan::Callback* callback)
        : AsyncWorker(callback), producer(producer), message(message), shardingKey(shardingKey) {}
    ~OrderProducerSend() {}

    void Execute() {
        try {
            result = producer->send(*message, shardingKey);
            delete message;
            message = NULL;
        } catch (ons::ONSClientException& e) {
            SetErrorMessage(e.GetMsg());
        }
    }

    void HandleOKCallback() {
        Nan::HandleScope scope;

        v8::Local<v8::Object> obj = Nan::New<v8::Object>();
        Nan::Set(obj, NEW_STRING("msgId"), NEW_STRING(result.getMessageId()));
        v8::Local<v8::Value> argv[] = {Nan::Null(), obj};
        callback->Call(2, argv);
    }

private:
    ons::OrderProducer* producer;
    ons::Message* message;
    std::string shardingKey;
    ons::SendResultONS result;
};


#endif //ALIMQ_ORDERPRODUCERSEND_H
