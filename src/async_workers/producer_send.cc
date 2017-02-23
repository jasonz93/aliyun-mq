#ifndef _PRODUCER_SEND_WORKER
#define _PRODUCER_SEND_WORKER

#include <nan.h>
#include <Producer.h>
#include "../utils.h"

using Nan::AsyncWorker;
using Nan::Callback;
using v8::Local;
using v8::Value;
using v8::Object;
using v8::String;
using ons::Producer;

class ProducerSendWorker : public AsyncWorker {
    public:
        ProducerSendWorker(Callback *callback, Producer*& producer, ons::Message*& msg, bool oneWay)
            : AsyncWorker(callback), producer(producer), msg(msg), oneWay(oneWay) {}
        ~ProducerSendWorker() {

        }

        void Execute() {
            try {
                if (oneWay) {
                    producer->sendOneway(*msg);
                } else {
                    sendResult = producer->send(*msg);
                }
                delete msg;
                msg = NULL;
            } catch (ons::ONSClientException& e) {
                SetErrorMessage(e.GetMsg());
            }
        }

        void HandleOKCallback() {
            Nan::HandleScope scope;

            if (oneWay) {
                Local<Value> argv[] = {Nan::Null()};
                callback->Call(1, argv);
            } else {
                Local<Object> result = Nan::New<Object>();
                result->Set(NEW_STRING("msgId"), NEW_STRING(sendResult.getMessageId()));

                Local<Value> argv[] = {Nan::Null(), result};

                callback->Call(2, argv);
            }
        }

    private:
        bool oneWay;
        Producer* producer;
        ons::Message* msg;
        ons::SendResultONS sendResult;
};

#endif