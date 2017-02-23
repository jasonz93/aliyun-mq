//
// Created by nicholas on 17-2-23.
//

#include "OrderConsumerWrap.h"
#include "MessageUtils.h"
#include "utils.h"
#include "OrderMessageListener.h"

using v8::Function;
using v8::FunctionTemplate;
using v8::Local;
using v8::Object;
using v8::Value;
using v8::String;

Nan::Persistent<Function> OrderConsumerWrap::constructor;

OrderConsumerWrap::OrderConsumerWrap() {}

OrderConsumerWrap::~OrderConsumerWrap() {
    delete consumer;
    consumer = NULL;
}

void OrderConsumerWrap::Init(v8::Local<v8::Object> exports) {
    Nan::HandleScope scope;

    Local<FunctionTemplate> tpl = Nan::New<FunctionTemplate>(New);
    tpl->SetClassName(NEW_STRING("OrderConsumer"));
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    Nan::SetPrototypeMethod(tpl, "start", Start);
    Nan::SetPrototypeMethod(tpl, "shutdown", Shutdown);
    Nan::SetPrototypeMethod(tpl, "subscribe", Subscribe);

    constructor.Reset(tpl->GetFunction());
}

NAN_METHOD(OrderConsumerWrap::New) {
    if (info.IsConstructCall()) {
        OrderConsumerWrap* consumerWrap = new OrderConsumerWrap();
        consumerWrap->Wrap(info.This());
        info.GetReturnValue().Set(info.This());
    } else {
        Local<Function> cons = Nan::New<Function>(constructor);
        Local<Object> obj = Nan::NewInstance(cons).ToLocalChecked();
        info.GetReturnValue().Set(obj);
    }
}

NAN_METHOD(OrderConsumerWrap::Start) {
    OrderConsumerWrap* wrap = Nan::ObjectWrap::Unwrap<OrderConsumerWrap>(info.Holder());
    wrap->consumer->start();
}

NAN_METHOD(OrderConsumerWrap::Shutdown) {
    OrderConsumerWrap* wrap = Nan::ObjectWrap::Unwrap<OrderConsumerWrap>(info.Holder());
    wrap->consumer->shutdown();
}

NAN_METHOD(OrderConsumerWrap::Subscribe) {
    OrderConsumerWrap* wrap = Nan::ObjectWrap::Unwrap<OrderConsumerWrap>(info.Holder());

    Nan::Callback* callback;
    const char* topic = *Nan::Utf8String(info[0]);
    const char* expr;
    if (info[1]->IsFunction()) {
        callback = new Nan::Callback(info[1].As<Function>());
        expr = "*";
    } else {
        callback = new Nan::Callback(info[2].As<Function>());
        expr = *Nan::Utf8String(info[1]);
    }
    wrap->consumer->subscribe(topic, expr, new OrderMessageListener(callback));
}