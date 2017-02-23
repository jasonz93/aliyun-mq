#include <node.h>
#include "ONSFactoryWrap.h"
#include "MessageWrap.h"
#include "MessageAck.h"
#include "ProducerWrap.h"
#include "PushConsumerWrap.h"
#include "OrderConsumerWrap.h"
#include "OrderProducerWrap.h"

using namespace v8;

void Init(Local<Object> exports) {
    ONSFactoryWrap::Init(exports);
    MessageWrap::Init(exports);
    MessageAckWrap::Init(exports);
    ProducerWrap::Init(exports);
    PushConsumerWrap::Init(exports);
    OrderConsumerWrap::Init(exports);
    OrderProducerWrap::Init(exports);
}

NODE_MODULE(alimq, Init);