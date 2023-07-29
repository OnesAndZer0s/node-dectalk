#pragma once

#include "napi.h"

#include <ttsapi.h>

class TTSPhonemeTag : public Napi::ObjectWrap< TTSPhonemeTag > {
  public:
    static Napi::Object Init( Napi::Env env, Napi::Object exports );
    TTSPhonemeTag( const Napi::CallbackInfo& info );
    static Napi::FunctionReference constructor;

    TTS_PHONEME_T ToStruct();
    static Napi::Object FromStruct( Napi::Env env, TTS_PHONEME_T caps );

    DWORD dwPhoneme;
    Napi::Value GetDwPhoneme( const Napi::CallbackInfo& info );
    void SetDwPhoneme( const Napi::CallbackInfo& info, const Napi::Value& value );
    DWORD dwPhonemeSampleNumber;
    Napi::Value GetDwPhonemeSampleNumber( const Napi::CallbackInfo& info );
    void SetDwPhonemeSampleNumber( const Napi::CallbackInfo& info, const Napi::Value& value );
    DWORD dwPhonemeDuration;
    Napi::Value GetDwPhonemeDuration( const Napi::CallbackInfo& info );
    void SetDwPhonemeDuration( const Napi::CallbackInfo& info, const Napi::Value& value );
    DWORD dwReserved;
};
