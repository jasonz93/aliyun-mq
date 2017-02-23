//
// Created by nicholas on 17-2-23.
//

#include "OrderMessageListener.h"

OrderMessageListener::OrderMessageListener(Nan::Callback *callback) : BaseMessageListener(callback) {}

OrderMessageListener::~OrderMessageListener() {}

OrderAction OrderMessageListener::consume(ons::Message &message, ons::ConsumeOrderContext &context) {
    return handleMessage(message) == CommonAction::SUCCESS ? OrderAction::Success : OrderAction::Suspend;
}