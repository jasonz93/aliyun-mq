//
// Created by nicholas on 17-2-23.
//

#include "OrderProducerWrap.h"
#include "utils.h"
#include "async_workers/OrderProducerSend.h"
#include "MessageUtils.h"

using v8::Function;
using v8::FunctionTemplate;
using v8::Local;
using v8::Object;
using v8::String;
using v8::Value;

Nan::Persistent<Function> OrderProducerWrap::constructor;

OrderProducerWrap::OrderProducerWrap() {}

OrderProducerWrap::~OrderProducerWrap() {}

void OrderProducerWrap::Init(v8::Local<v8::Object> exports) {
    Nan::HandleScope scope;

    Local<FunctionTemplate> tpl = Nan::New<FunctionTemplate>(New);
    tpl->SetClassName(NEW_STRING("OrderProducer"));
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    Nan::SetPrototypeMethod(tpl, "start", Start);
    Nan::SetPrototypeMethod(tpl, "shutdown", Shutdown);
    Nan::SetPrototypeMethod(tpl, "send", Send);

    constructor.Reset(tpl->GetFunction());
}

NAN_METHOD(OrderProducerWrap::New) {
    if (info.IsConstructCall()) {
        OrderProducerWrap* wrap = new OrderProducerWrap();
        wrap->Wrap(info.This());
        info.GetReturnValue().Set(info.This());
    } else {
        Local<Function> cons = Nan::New<Function>(constructor);
        Local<Object> obj = Nan::NewInstance(cons).ToLocalChecked();
        info.GetReturnValue().Set(obj);
    }
}

NAN_METHOD(OrderProducerWrap::Start) {
    OrderProducerWrap* wrap = Nan::ObjectWrap::Unwrap<OrderProducerWrap>(info.Holder());
    wrap->producer->start();
}

NAN_METHOD(OrderProducerWrap::Shutdown) {
    OrderProducerWrap* wrap = Nan::ObjectWrap::Unwrap<OrderProducerWrap>(info.Holder());
    wrap->producer->shutdown();
}

NAN_METHOD(OrderProducerWrap::Send) {
    OrderProducerWrap* wrap = Nan::ObjectWrap::Unwrap<OrderProducerWrap>(info.Holder());

    ons::Message* message = MessageUtils::FromV8Object(info[0].As<Object>());

    OrderProducerSend* worker = new OrderProducerSend(wrap->producer, message, V8_CSTRING(info[1]), new Nan::Callback(info[2].As<Function>()));
    Nan::AsyncQueueWorker(worker);
}