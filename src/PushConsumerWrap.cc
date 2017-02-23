#include "PushConsumerWrap.h"
#include "MessageWrap.h"
#include "PushMessageListener.h"

using v8::Function;
using v8::Local;
using v8::Object;
using v8::Value;
using v8::FunctionTemplate;
using v8::String;

Nan::Persistent<Function> PushConsumerWrap::constructor;

PushConsumerWrap::PushConsumerWrap() {}

PushConsumerWrap::~PushConsumerWrap() {}

void PushConsumerWrap::Init(Local<Object> exports) {
    Nan::HandleScope scope;

    Local<FunctionTemplate> tpl = Nan::New<FunctionTemplate>(New);
    tpl->SetClassName(Nan::New<String>("PushConsumer").ToLocalChecked());
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    Nan::SetPrototypeMethod(tpl, "start", Start);
    Nan::SetPrototypeMethod(tpl, "shutdown", Shutdown);
    Nan::SetPrototypeMethod(tpl, "subscribe", Subscribe);

    constructor.Reset(tpl->GetFunction());
}

NAN_METHOD(PushConsumerWrap::New) {
    if (info.IsConstructCall()) {
        PushConsumerWrap* consumerWrap = new PushConsumerWrap();
        consumerWrap->Wrap(info.This());
        info.GetReturnValue().Set(info.This());
    } else {
        Local<Function> cons = Nan::New<Function>(constructor);
        info.GetReturnValue().Set(Nan::NewInstance(cons).ToLocalChecked());
    }
}

NAN_METHOD(PushConsumerWrap::Start) {
    PushConsumerWrap* wrap = Nan::ObjectWrap::Unwrap<PushConsumerWrap>(info.Holder());
    wrap->_consumer->start();
}

NAN_METHOD(PushConsumerWrap::Shutdown) {
    PushConsumerWrap* wrap = Nan::ObjectWrap::Unwrap<PushConsumerWrap>(info.Holder());
    wrap->_consumer->shutdown();
}

NAN_METHOD(PushConsumerWrap::Subscribe) {
    PushConsumerWrap* consumerWrap = Nan::ObjectWrap::Unwrap<PushConsumerWrap>(info.Holder());

    const char* expr;
    const char* topic = *Nan::Utf8String(info[0]);
    Local<Function> cb;
    if (info[1]->IsFunction()) {
        cb = info[1].As<Function>();
        expr = "*";
    } else {
        cb = info[2].As<Function>();
        expr = *Nan::Utf8String(info[1]);
    }

    PushMessageListener* listener = new PushMessageListener(new Nan::Callback(cb));
    consumerWrap->_consumer->subscribe(topic, expr, listener);
}