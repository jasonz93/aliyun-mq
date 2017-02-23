#include "MessageAck.h"

using v8::Function;
using v8::Local;
using v8::String;
using v8::Object;
using v8::Value;
using v8::FunctionTemplate;

MessageAck::MessageAck() : cond(new uv_cond_t), mutex(new uv_mutex_t) {
    uv_cond_init(cond);
    uv_mutex_init(mutex);
}

MessageAck::~MessageAck() {
    uv_cond_destroy(cond);
    delete cond;
    cond = NULL;

    uv_mutex_destroy(mutex);
    delete mutex;
    mutex = NULL;
}

void MessageAck::Block() {
    uv_cond_wait(cond, mutex);
}

void MessageAck::Ack(CommonAction action = CommonAction ::SUCCESS) {
    this->action = action;
    uv_cond_signal(cond);
}



Nan::Persistent<Function> MessageAckWrap::constructor;

MessageAckWrap::MessageAckWrap() {}

MessageAckWrap::~MessageAckWrap() {}

void MessageAckWrap::Init(Local<Object> exports) {
    Nan::HandleScope scope;

    Local<FunctionTemplate> tpl = Nan::New<FunctionTemplate>(New);
    tpl->SetClassName(Nan::New<String>("MessageAck").ToLocalChecked());
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    Nan::SetCallAsFunctionHandler(tpl->InstanceTemplate(), Ack);

    constructor.Reset(tpl->GetFunction());
}

NAN_METHOD(MessageAckWrap::New) {
    if (info.IsConstructCall()) {
        MessageAckWrap* wrap = new MessageAckWrap();
        wrap->Wrap(info.This());
        info.GetReturnValue().Set(info.This());
    } else {
        Local<Function> cons = Nan::New<Function>(constructor);
        Local<Object> result = Nan::NewInstance(cons).ToLocalChecked();
        info.GetReturnValue().Set(result);
    }
}

NAN_METHOD(MessageAckWrap::Ack) {
    CommonAction action;
    if (info[0]->IsUndefined() || info[0]->IsNull() || info[0]->IsTrue()) {
        action = CommonAction::SUCCESS;
    } else {
        action = CommonAction::FAILED;
    }

    MessageAckWrap* ackWrap = Nan::ObjectWrap::Unwrap<MessageAckWrap>(info.Holder());
    ackWrap->ack->Ack(action);
}

void MessageAckWrap::SetAck(MessageAck* ack) {
    this->ack = ack;
}

MessageAck* MessageAckWrap::GetAck() {
    return this->ack;
}