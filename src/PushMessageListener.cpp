//
// Created by nicholas on 17-2-23.
//

#include "PushMessageListener.h"

PushMessageListener::PushMessageListener(Nan::Callback *callback) : BaseMessageListener(callback) {}

PushMessageListener::~PushMessageListener() {}

Action PushMessageListener::consume(ons::Message &message, ons::ConsumeContext &context) {
    return handleMessage(message) == CommonAction::SUCCESS ? Action::CommitMessage : Action::ReconsumeLater;
}