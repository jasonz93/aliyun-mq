//
// Created by nicholas on 17-2-23.
//

#ifndef ALIMQ_PUSHMESSAGELISTENER_H
#define ALIMQ_PUSHMESSAGELISTENER_H

#include <nan.h>
#include <MessageListener.h>
#include "BaseMessageListener.h"

class PushMessageListener : public BaseMessageListener, public ons::MessageListener {
public:
    explicit PushMessageListener(Nan::Callback* callback);
    ~PushMessageListener();
    Action consume(ons::Message& message, ons::ConsumeContext& context);
};


#endif //ALIMQ_PUSHMESSAGELISTENER_H
