#pragma once

#include "napi.h"

#include <ttsapi.h>

class TTSPhonemeTag : public Napi::ObjectWrap< TTSPhonemeTag > {
  public:
    static Napi::Object Init( Napi::Env env, Napi::Object exports );
    TTSPhonemeTag( const Napi::CallbackInfo& info );
    static Napi::FunctionReference constructor;

    static Napi::Object FromStruct( Napi::Env env, TTS_PHONEME_T caps );

    Napi::Value GetDwPhoneme( const Napi::CallbackInfo& info );
    Napi::Value GetDwPhonemeSampleNumber( const Napi::CallbackInfo& info );
    Napi::Value GetDwPhonemeDuration( const Napi::CallbackInfo& info );

    TTS_PHONEME_T ttsPhonemeT;
};
