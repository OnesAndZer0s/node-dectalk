#pragma once

#include "napi.h"

#include <ttsapi.h>

class LanguageParamsTag : public Napi::ObjectWrap< LanguageParamsTag > {
  public:
    static Napi::Object Init( Napi::Env env, Napi::Object exports );
    LanguageParamsTag( const Napi::CallbackInfo& info );
    static Napi::FunctionReference constructor;

    LANGUAGE_PARAMS_T ToStruct();
    static Napi::Object FromStruct( Napi::Env env, LANGUAGE_PARAMS_T caps );
    Napi::Value GetDwLanguage( const Napi::CallbackInfo& info );
    void SetDwLanguage( const Napi::CallbackInfo& info, const Napi::Value& value );
    Napi::Value GetDwLanguageAttributes( const Napi::CallbackInfo& info );
    void SetDwLanguageAttributes( const Napi::CallbackInfo& info, const Napi::Value& value );

    LANGUAGE_PARAMS_T languageParamsT;
};
