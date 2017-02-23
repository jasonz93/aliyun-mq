//
// Created by nicholas on 17-2-23.
//

#ifndef ALIMQ_MESSAGEUTILS_H
#define ALIMQ_MESSAGEUTILS_H

#include <nan.h>
#include <Message.h>

class MessageUtils {
public:
    static ons::Message* FromV8Object(v8::Local<v8::Object> obj);
    static v8::Local<v8::Object> ToV8Object(ons::Message* msg);
};


#endif //ALIMQ_MESSAGEUTILS_H
