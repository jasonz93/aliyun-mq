#ifndef __V8_MESSAGE_LISTENER
#define __V8_MESSAGE_LISTENER

#include <nan.h>
#include <uv.h>
#include <pthread.h>
#include <unordered_map>
#include <Message.h>
#include <Action.h>
#include "MessageAck.h"
#include "utils.h"

typedef struct {
    MessageAck* ack;
    Nan::Callback* callback;
    ons::Message* msg;
    void* context;
} msg_listen_t;

class BaseMessageListener {
    public:
        explicit BaseMessageListener(Nan::Callback* callback);
        ~BaseMessageListener();

        CommonAction handleMessage(ons::Message& message);

    private:
        std::unordered_map<pthread_t, uv_async_t*> asyncMap;
        Nan::Callback* callback;
};

inline void notifyInLoop(uv_async_t* handle);

#endif