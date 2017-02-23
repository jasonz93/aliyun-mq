#include "ProducerWrap.h"
#include "MessageWrap.h"
#include "MessageUtils.h"
#include "async_workers/producer_send.cc"

using namespace v8;

Nan::Persistent<Function> ProducerWrap::constructor;

ProducerWrap::ProducerWrap() {}

ProducerWrap::~ProducerWrap() {
    delete this->_producer;
}

void ProducerWrap::Init(Local<Object> exports) {
    Nan::HandleScope scope;

    Local<FunctionTemplate> tpl = Nan::New<FunctionTemplate>(New);
    tpl->SetClassName(Nan::New<String>("Producer").ToLocalChecked());
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    Nan::SetPrototypeMethod(tpl, "start", Start);
    Nan::SetPrototypeMethod(tpl, "shutdown", Shutdown);
    Nan::SetPrototypeMethod(tpl, "send", Send);
    Nan::SetPrototypeMethod(tpl, "sendOneway", SendOneway);

    constructor.Reset(tpl->GetFunction());
}

NAN_METHOD(ProducerWrap::New) {
    if (info.IsConstructCall()) {
        ProducerWrap* producerWrap = new ProducerWrap();
        producerWrap->Wrap(info.This());
        info.GetReturnValue().Set(info.This());
    } else {
        Local<Function> cons = Nan::New<Function>(constructor);
        Local<Object> result = Nan::NewInstance(cons).ToLocalChecked();
        info.GetReturnValue().Set(result);
    }
}

NAN_METHOD(ProducerWrap::Start) {
    ProducerWrap* obj = Nan::ObjectWrap::Unwrap<ProducerWrap>(info.Holder());
    obj->_producer->start();
}

NAN_METHOD(ProducerWrap::Shutdown) {
    ProducerWrap* obj = Nan::ObjectWrap::Unwrap<ProducerWrap>(info.Holder());
    obj->_producer->shutdown();
}

NAN_METHOD(ProducerWrap::Send) {
    ProducerWrap* wrap = Nan::ObjectWrap::Unwrap<ProducerWrap>(info.Holder());

    ons::Message* msg = MessageUtils::FromV8Object(Nan::To<Object>(info[0]).ToLocalChecked());
    Nan::Callback* callback = new Nan::Callback(info[1].As<Function>());
    Nan::AsyncQueueWorker(new ProducerSendWorker(callback, wrap->_producer, msg, false));
}

NAN_METHOD(ProducerWrap::SendOneway) {
    ProducerWrap* wrap = Nan::ObjectWrap::Unwrap<ProducerWrap>(info.Holder());

    ons::Message* msg = MessageUtils::FromV8Object(Nan::To<Object>(info[0]).ToLocalChecked());
    Nan::Callback* callback = new Nan::Callback(info[1].As<Function>());
    Nan::AsyncQueueWorker(new ProducerSendWorker(callback, wrap->_producer, msg, true));
}