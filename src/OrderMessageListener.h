//
// Created by nicholas on 17-2-23.
//

#ifndef ALIMQ_ORDERMESSAGELISTENER_H
#define ALIMQ_ORDERMESSAGELISTENER_H

#include <MessageOrderListener.h>
#include "BaseMessageListener.h"

class OrderMessageListener : public BaseMessageListener, public ons::MessageOrderListener {
public:
    explicit OrderMessageListener(Nan::Callback* callback);
    ~OrderMessageListener();
    OrderAction consume(ons::Message& message, ons::ConsumeOrderContext& context);
};


#endif //ALIMQ_ORDERMESSAGELISTENER_H
