#include "utils.h"
#include <nan.h>

hash_t hash_(char const* str)
{
    hash_t ret{basis};

    while(*str){
        ret ^= *str;
        ret *= prime;
        str++;
    }

    return ret;
}

v8::Local<v8::Value> NullOrString(const char* value) {
    if (value == 0) {
        return Nan::Null();
    } else {
        return Nan::New<v8::String>(value).ToLocalChecked();
    }
}