#ifndef __MESSAGE_ACK
#define __MESSAGE_ACK

#include <uv.h>
#include <Action.h>
#include <nan.h>
#include "CommonAction.h"

class MessageAck : public Nan::ObjectWrap {
    public:
        explicit MessageAck();
        ~MessageAck();

        void Block();
        void Ack(CommonAction action);
        CommonAction action = CommonAction::SUCCESS;

    private:
        uv_mutex_t* mutex;
        uv_cond_t* cond;
};

class MessageAckWrap : public Nan::ObjectWrap {
    public:
        explicit MessageAckWrap();
        ~MessageAckWrap();

        void SetAck(MessageAck* ack);
        MessageAck* GetAck();

        static void Init(v8::Local<v8::Object> exports);
        static Nan::Persistent<v8::Function> constructor;

    private:
        static NAN_METHOD(New);
        static NAN_METHOD(Ack);

        MessageAck* ack;
};

#endif