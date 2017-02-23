//
// Created by nicholas on 17-2-23.
//

#include "MessageUtils.h"
#include "utils.h"

using v8::Local;
using v8::Object;
using v8::Value;

inline const char* CStringOrNull(Local<Value> val) {
    if (val->IsUndefined() || val->IsNull()) {
        return NULL;
    } else if (val->IsString()) {
        return V8_CSTRING(val);
    } else {
        return NULL;
    }
}

inline long long LongLongOrZero(Local<Value> val) {
    if (val->IsUndefined() || val->IsNull()) {
        return 0;
    } else if (val->IsNumber() || val->IsInt32()) {
        return Nan::To<int64_t>(val).FromJust();
    } else {
        return 0;
    }
}

ons::Message* MessageUtils::FromV8Object(v8::Local<v8::Object> obj) {
    Nan::HandleScope scope;

    ons::Message* msg = new ons::Message();
    msg->setTopic(V8_CSTRING(obj->Get(NEW_STRING("topic"))));
    msg->setKey(V8_CSTRING(obj->Get(NEW_STRING("key"))));
    msg->setTag(V8_CSTRING(obj->Get(NEW_STRING("tag"))));
    msg->setBody(V8_CSTRING(obj->Get(NEW_STRING("body"))));
    msg->setStartDeliverTime(LongLongOrZero(obj->Get(NEW_STRING("startDeliverTime"))));

    return msg;
}

v8::Local<v8::Object> MessageUtils::ToV8Object(ons::Message *msg) {
    Local<Object> msgObj = Nan::New<Object>();
    Nan::Set(msgObj, NEW_STRING("topic"), NEW_STRING(msg->getTopic()));
    Nan::Set(msgObj, NEW_STRING("tag"), NEW_STRING(msg->getTag()));
    Nan::Set(msgObj, NEW_STRING("key"), NEW_STRING(msg->getKey()));
    Nan::Set(msgObj, NEW_STRING("msgId"), NEW_STRING(msg->getMsgID()));
    Nan::Set(msgObj, NEW_STRING("body"), NEW_STRING(msg->getBody()));
    Nan::Set(msgObj, NEW_STRING("startDeliverTime"), NEW_LOCAL(v8::Number, msg->getStartDeliverTime()));
    Nan::Set(msgObj, NEW_STRING("storeTimestamp"), NEW_LOCAL(v8::Number, msg->getStoreTimestamp()));
    Nan::Set(msgObj, NEW_STRING("reconsumeTimes"), NEW_LOCAL(v8::Integer, msg->getReconsumeTimes()));

    return msgObj;
}