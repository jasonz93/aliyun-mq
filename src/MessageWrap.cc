#include "MessageWrap.h"

inline void SET_IF_EXIST(v8::Local<v8::Object>& src, v8::Local<v8::Object>& target, const char* key) {
    Nan::HandleScope scope;

    v8::Local<v8::String> keyStr = Nan::New<v8::String>(key).ToLocalChecked();
    if (Nan::Has(src, keyStr).FromJust()) {
        Nan::Set(target, keyStr, Nan::Get(src, keyStr).ToLocalChecked());
    }
}

using namespace v8;

Nan::Persistent<Function> MessageWrap::constructor;

MessageWrap::MessageWrap(ons::Message* message) {
    this->_message = message;
}

MessageWrap::MessageWrap() {}

MessageWrap::~MessageWrap() {

}

void MessageWrap::Init(Local<Object> exports) {
    Nan::HandleScope scope;

    Local<FunctionTemplate> tpl = Nan::New<FunctionTemplate>(New);
    tpl->SetClassName(Nan::New<String>("Message").ToLocalChecked());
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    Nan::SetPrototypeMethod(tpl, "putUserProperty", PutUserProperty);
    Nan::SetPrototypeMethod(tpl, "getUserProperty", GetUserProperty);
    Nan::SetPrototypeMethod(tpl, "putSystemProperty", PutSystemProperty);
    Nan::SetPrototypeMethod(tpl, "getSystemProperty", GetSystemProperty);

    Local<ObjectTemplate> objTpl = tpl->InstanceTemplate();

    Nan::SetAccessor(objTpl, Nan::New<String>("userProperties").ToLocalChecked(), GetProperties, SetProperties);
    Nan::SetAccessor(objTpl, Nan::New<String>("systemProperties").ToLocalChecked(), GetProperties, SetProperties);

    Nan::SetAccessor(objTpl, Nan::New<String>("topic").ToLocalChecked(), Getter, Setter);
    Nan::SetAccessor(objTpl, Nan::New<String>("tag").ToLocalChecked(), Getter, Setter);
    Nan::SetAccessor(objTpl, Nan::New<String>("key").ToLocalChecked(), Getter, Setter);
    Nan::SetAccessor(objTpl, Nan::New<String>("msgId").ToLocalChecked(), Getter, Setter);
    Nan::SetAccessor(objTpl, Nan::New<String>("startDeliverTime").ToLocalChecked(), Getter, Setter);
    Nan::SetAccessor(objTpl, Nan::New<String>("body").ToLocalChecked(), Getter, Setter);
    Nan::SetAccessor(objTpl, Nan::New<String>("reconsumeTimes").ToLocalChecked(), Getter, Setter);
    Nan::SetAccessor(objTpl, Nan::New<String>("storeTimestamp").ToLocalChecked(), Getter, Setter);

    constructor.Reset(tpl->GetFunction());
    Nan::Set(exports, Nan::New<String>("Message").ToLocalChecked(), tpl->GetFunction());
}

NAN_METHOD(MessageWrap::New) {
    if (info.IsConstructCall()) {
        MessageWrap* messageWrap;
        if (info.Length() > 0 && info[0]->IsObject()) {
            ons::Message* msg = new ons::Message();
            messageWrap = new MessageWrap(msg);
            messageWrap->Wrap(info.This());
            Local<Object> obj = info[0].As<Object>();
            Local<Object> target = info.This();
            SET_IF_EXIST(obj, target, "topic");
            SET_IF_EXIST(obj, target, "tag");
            SET_IF_EXIST(obj, target, "key");
            SET_IF_EXIST(obj, target, "msgId");
            SET_IF_EXIST(obj, target, "startDeliverTime");
            SET_IF_EXIST(obj, target, "body");
            SET_IF_EXIST(obj, target, "reconsumeTimes");
            SET_IF_EXIST(obj, target, "storeTimestamp");
        } else {
            messageWrap = new MessageWrap();
            messageWrap->Wrap(info.This());
        }
        info.GetReturnValue().Set(info.This());
    } else {
        const int argc = 1;
        Local<Value> argv[argc] = {info[0]};
        Local<Function> cons = Nan::New<Function>(constructor);
        Local<Object> result = Nan::NewInstance(cons, argc, argv).ToLocalChecked();
        info.GetReturnValue().Set(result);
    }
}

NAN_METHOD(MessageWrap::PutUserProperty) {
    MessageWrap* message = Nan::ObjectWrap::Unwrap<MessageWrap>(info.Holder());
    message->_message->putUserProperties(*String::Utf8Value(info[0]), *String::Utf8Value(info[1]));
}

NAN_METHOD(MessageWrap::GetUserProperty) {
    MessageWrap* message = Nan::ObjectWrap::Unwrap<MessageWrap>(info.Holder());

    const char* property = message->_message->getUserProperties(*String::Utf8Value(info[0]));
    info.GetReturnValue().Set(Nan::New<String>(property).ToLocalChecked());
}

NAN_METHOD(MessageWrap::PutSystemProperty) {
    MessageWrap* message = Nan::ObjectWrap::Unwrap<MessageWrap>(info.Holder());
    message->_message->putSystemProperties(*String::Utf8Value(info[0]), *String::Utf8Value(info[1]));
}

NAN_METHOD(MessageWrap::GetSystemProperty) {
    MessageWrap* message = Nan::ObjectWrap::Unwrap<MessageWrap>(info.Holder());
    const char* property = message->_message->getSystemProperties(*String::Utf8Value(info[0]));
    info.GetReturnValue().Set(Nan::New<String>(property).ToLocalChecked());
}

NAN_GETTER(MessageWrap::GetProperties) {

}

NAN_SETTER(MessageWrap::SetProperties) {

}

NAN_GETTER(MessageWrap::Getter) {
    MessageWrap* message = Nan::ObjectWrap::Unwrap<MessageWrap>(info.Holder());
    Nan::ReturnValue<Value> returnValue = info.GetReturnValue();
    switch (hash_(*String::Utf8Value(property))) {
        case hash_compile_time("topic"):
            returnValue.Set(NullOrString(message->_message->getTopic()));
            break;
        case hash_compile_time("tag"):
            returnValue.Set(NullOrString(message->_message->getTag()));
            break;
        case hash_compile_time("key"):
            returnValue.Set(NullOrString(message->_message->getKey()));
            break;
        case hash_compile_time("msgId"):
            returnValue.Set(NullOrString(message->_message->getMsgID()));
            break;
        case hash_compile_time("startDeliverTime"):
            returnValue.Set(Nan::New<Number>(message->_message->getStartDeliverTime()));
            break;
        case hash_compile_time("body"):
            returnValue.Set(NullOrString(message->_message->getBody()));
            break;
        case hash_compile_time("reconsumeTimes"):
            returnValue.Set(Nan::New<Integer>(message->_message->getReconsumeTimes()));
            break;
        case hash_compile_time("storeTimestamp"):
            returnValue.Set(Nan::New<Number>(message->_message->getStoreTimestamp()));
            break;
    }
}

NAN_SETTER(MessageWrap::Setter) {
    MessageWrap* message = Nan::ObjectWrap::Unwrap<MessageWrap>(info.Holder());
    switch (hash_(*String::Utf8Value(property))) {
        case hash_compile_time("topic"):
            message->_message->setTopic(*String::Utf8Value(value->ToString()));
            break;
        case hash_compile_time("tag"):
            message->_message->setTag(*String::Utf8Value(value->ToString()));
            break;
        case hash_compile_time("key"):
            message->_message->setKey(*String::Utf8Value(value->ToString()));
            break;
        case hash_compile_time("msgId"):
            message->_message->setMsgID(*String::Utf8Value(value->ToString()));
            break;
        case hash_compile_time("startDeliverTime"):
            message->_message->setStartDeliverTime(value->NumberValue());
            break;
        case hash_compile_time("body"):
            message->_message->setBody(*String::Utf8Value(value->ToString()));
            break;
        case hash_compile_time("reconsumeTimes"):
            message->_message->setReconsumeTimes(value->Int32Value());
            break;
        case hash_compile_time("storeTimestamp"):
            message->_message->setStoreTimestamp(value->NumberValue());
            break;
    }
}

ons::Message* MessageWrap::getMessage() {
    return this->_message;
}

void MessageWrap::setMessage(ons::Message* message) {
    _message = message;
}