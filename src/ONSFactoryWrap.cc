#include "ONSFactoryWrap.h"
#include "ProducerWrap.h"
#include "PushConsumerWrap.h"
#include "OrderProducerWrap.h"
#include "OrderConsumerWrap.h"

using v8::Local;
using v8::Function;
using v8::Value;
using v8::String;
using v8::Object;
using v8::FunctionTemplate;
using ons::ONSFactoryProperty;
using ons::ONSFactory;
using ons::Producer;

Nan::Persistent<Function> ONSFactoryWrap::constructor;

ONSFactoryWrap::ONSFactoryWrap(Local<Object> props) {
    SetPropertyIfExists(&_factoryInfo, ONSFactoryProperty::AccessKey, props, "accessKey");
    SetPropertyIfExists(&_factoryInfo, ONSFactoryProperty::SecretKey, props, "secretKey");
    SetPropertyIfExists(&_factoryInfo, ONSFactoryProperty::LogPath, props, "logPath");
}

ONSFactoryWrap::~ONSFactoryWrap() {
}

void ONSFactoryWrap::SetPropertyIfExists(ons::ONSFactoryProperty* factoryInfo, const char* key, Local<Object> props, const char* propKey) {
    Nan::HandleScope scope;

    Local<String> v8PropKey = Nan::New<String>(propKey).ToLocalChecked();
    if (Nan::HasOwnProperty(props, v8PropKey).FromJust()) {
        factoryInfo->setFactoryProperty(key, *String::Utf8Value(Nan::Get(props, v8PropKey).ToLocalChecked()));
    }
}

void ONSFactoryWrap::Init(Local<Object> exports) {
    Nan::HandleScope scope;

    Local<FunctionTemplate> tpl = Nan::New<FunctionTemplate>(New);
    tpl->SetClassName(Nan::New<String>("ONSFactory").ToLocalChecked());
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    Nan::SetPrototypeMethod(tpl, "createProducer", CreateProducer);
    Nan::SetPrototypeMethod(tpl, "createPushConsumer", CreatePushConsumer);
    Nan::SetPrototypeMethod(tpl, "createOrderConsumer", CreateOrderConsumer);
    Nan::SetPrototypeMethod(tpl, "createOrderProducer", CreateOrderProducer);

    constructor.Reset(tpl->GetFunction());
    exports->Set(Nan::New("ONSFactory").ToLocalChecked(), tpl->GetFunction());
}

NAN_METHOD(ONSFactoryWrap::New) {
    if (info.IsConstructCall()) {
        if (!info[0]->IsObject()) {
            Nan::ThrowError("ONSFactoryWrap::New: Wrong type of argument.");
            return;
        }
        Nan::MaybeLocal<Object> props = Nan::To<Object>(info[0]);
        ONSFactoryWrap* factory = new ONSFactoryWrap(props.ToLocalChecked());
        factory->Wrap(info.This());
        info.GetReturnValue().Set(info.This());
    } else {
        const int argc = 1;
        Local<Value> argv[argc] = {info[0]};
        Local<Function> cons = Nan::New<Function>(constructor);
        info.GetReturnValue().Set(Nan::NewInstance(cons, argc, argv).ToLocalChecked());
    }
}

NAN_METHOD(ONSFactoryWrap::CreateProducer) {
    if (!info[0]->IsObject()) {
        Nan::ThrowError("CreateProducer: Wrong type of argument.");
        return;
    }
    ONSFactoryWrap* factoryWrap = Nan::ObjectWrap::Unwrap<ONSFactoryWrap>(info.Holder());
    ons::ONSFactoryProperty factoryInfo(factoryWrap->_factoryInfo);

    Local<Object> props = Nan::To<Object>(info[0]).ToLocalChecked();

    SetPropertyIfExists(&factoryInfo, ONSFactoryProperty::ProducerId, props, "producerId");
    Producer* producer = ONSFactory::getInstance()->createProducer(factoryInfo);
    Local<Function> cons = Nan::New<Function>(ProducerWrap::constructor);
    Local<Object> result = cons->NewInstance();
    ProducerWrap* producerWrap = Nan::ObjectWrap::Unwrap<ProducerWrap>(result);
    producerWrap->_producer = producer;
    info.GetReturnValue().Set(result);
}

NAN_METHOD(ONSFactoryWrap::CreatePushConsumer) {
    if (!info[0]->IsObject()) {
        Nan::ThrowError("CreateProducer: Wrong type of argument.");
        return;
    }
    ONSFactoryWrap* factoryWrap = Nan::ObjectWrap::Unwrap<ONSFactoryWrap>(info.Holder());
    ons::ONSFactoryProperty factoryInfo(factoryWrap->_factoryInfo);

    Local<Object> props = Nan::To<Object>(info[0]).ToLocalChecked();

    SetPropertyIfExists(&factoryInfo, ONSFactoryProperty::ConsumerId, props, "consumerId");

    ons::PushConsumer* consumer = ONSFactory::getInstance()->createPushConsumer(factoryInfo);
    Local<Function> cons = Nan::New<Function>(PushConsumerWrap::constructor);
    Local<Object> result = Nan::NewInstance(cons).ToLocalChecked();
    PushConsumerWrap* consumerWrap = Nan::ObjectWrap::Unwrap<PushConsumerWrap>(result);
    consumerWrap->_consumer = consumer;
    info.GetReturnValue().Set(result);
}

NAN_METHOD(ONSFactoryWrap::CreateOrderConsumer) {
    if (!info[0]->IsObject()) {
        Nan::ThrowError("CreateProducer: Wrong type of argument.");
        return;
    }
    ONSFactoryWrap* factoryWrap = Nan::ObjectWrap::Unwrap<ONSFactoryWrap>(info.Holder());
    ons::ONSFactoryProperty factoryInfo(factoryWrap->_factoryInfo);

    Local<Object> props = Nan::To<Object>(info[0]).ToLocalChecked();

    SetPropertyIfExists(&factoryInfo, ONSFactoryProperty::ConsumerId, props, "consumerId");

    ons::OrderConsumer* consumer = ons::ONSFactory::getInstance()->createOrderConsumer(factoryInfo);
    Local<Function> cons = Nan::New<Function>(OrderConsumerWrap::constructor);
    Local<Object> obj = Nan::NewInstance(cons).ToLocalChecked();
    OrderConsumerWrap* wrap = Nan::ObjectWrap::Unwrap<OrderConsumerWrap>(obj);
    wrap->consumer = consumer;
    info.GetReturnValue().Set(obj);
}

NAN_METHOD(ONSFactoryWrap::CreateOrderProducer) {
    if (!info[0]->IsObject()) {
        Nan::ThrowError("CreateProducer: Wrong type of argument.");
        return;
    }
    ONSFactoryWrap* factoryWrap = Nan::ObjectWrap::Unwrap<ONSFactoryWrap>(info.Holder());
    ons::ONSFactoryProperty factoryInfo(factoryWrap->_factoryInfo);

    Local<Object> props = Nan::To<Object>(info[0]).ToLocalChecked();

    SetPropertyIfExists(&factoryInfo, ONSFactoryProperty::ProducerId, props, "producerId");

    ons::OrderProducer* producer = ONSFactory::getInstance()->createOrderProducer(factoryInfo);
    Local<Function> cons = Nan::New<Function>(OrderProducerWrap::constructor);
    Local<Object> obj = Nan::NewInstance(cons).ToLocalChecked();
    OrderProducerWrap* wrap = Nan::ObjectWrap::Unwrap<OrderProducerWrap>(obj);
    wrap->producer = producer;
    info.GetReturnValue().Set(obj);
}