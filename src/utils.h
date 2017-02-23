#ifndef _ALIMQ_UTILS
#define _ALIMQ_UTILS

#include <inttypes.h>
#include <node.h>
#include <v8.h>

#define NEW_LOCAL(type, val) Nan::New<type>(val)
#define NEW_STRING(str) NEW_LOCAL(v8::String, str).ToLocalChecked()
#define V8_CSTRING(str) *Nan::Utf8String(str)

typedef uint64_t hash_t;

constexpr hash_t prime = 0x100000001B3ull;
constexpr hash_t basis = 0xCBF29CE484222325ull;

hash_t hash_(char const* str);

constexpr hash_t hash_compile_time(char const* str, hash_t last_value = basis)
{
    return *str ? hash_compile_time(str+1, (*str ^ last_value) * prime) : last_value;
}

v8::Local<v8::Value> NullOrString(const char* value);

#endif