#include "BaseMessageListener.h"
#include "MessageUtils.h"

using v8::Local;
using v8::Function;
using v8::Object;
using v8::Value;

BaseMessageListener::BaseMessageListener(Nan::Callback* callback) : callback(callback) {

}

BaseMessageListener::~BaseMessageListener() {
    for (auto ite = asyncMap.begin(); ite != asyncMap.end(); ++ ite) {
        uv_close((uv_handle_t*)ite->second, NULL);
        delete ite->second;
    }
    delete callback;
    callback = NULL;
}

CommonAction BaseMessageListener::handleMessage(ons::Message& message) {
    MessageAck* ack = new MessageAck();
    //Initialize async info
    msg_listen_t* result = new msg_listen_t;
    result->ack = ack;
    result->callback = callback;
    result->msg = &message;

    pthread_t tid = pthread_self();
    auto search = asyncMap.find(tid);
    uv_async_t* async;
    if (search != asyncMap.end()) {
        async = search->second;
    } else {
        async = new uv_async_t;
        uv_async_init(uv_default_loop(), async, notifyInLoop);
        asyncMap.insert({tid, async});
    }

    async->data = result;
    uv_async_send(async);
//    printf("Try blocking consumer thread.\n");
    ack->Block();
//    printf("Message ack received.\n");

    CommonAction action = result->ack->action;
    delete result;
    result = NULL;

    delete ack;
    ack = NULL;

    return action;
}

inline void notifyInLoop(uv_async_t* handle) {
    Nan::HandleScope scope;

    msg_listen_t* result = (msg_listen_t*)handle->data;
//    printf("Got msg listen data.\n");
    //Build ack wrap
    Local<Function> ackWrapCons = Nan::New<Function>(MessageAckWrap::constructor);
    Local<Object> ackWrapObj = Nan::NewInstance(ackWrapCons).ToLocalChecked();
    MessageAckWrap* ackWrap = Nan::ObjectWrap::Unwrap<MessageAckWrap>(ackWrapObj);
    ackWrap->SetAck(result->ack);

    Local<Object> msgObj = MessageUtils::ToV8Object(result->msg);
    //Call callback
    Local<Value> argv[] = {msgObj, ackWrapObj};
//    printf("Building callback done.\n");
    result->callback->Call(2, argv);
}