#pragma once

#include "napi.h"

#include <ttsapi.h>

class TTSCapsTag : public Napi::ObjectWrap< TTSCapsTag > {
  public:
    static Napi::Object Init( Napi::Env env, Napi::Object exports );
    TTSCapsTag( const Napi::CallbackInfo& info );
    static Napi::FunctionReference constructor;

    static Napi::Object FromStruct( Napi::Env env, TTS_CAPS_T caps );

    Napi::Value GetDwNumberOfLanguages( const Napi::CallbackInfo& info );
    Napi::Value GetLpLanguageParamsArray( const Napi::CallbackInfo& info );
    Napi::Value GetDwSampleRate( const Napi::CallbackInfo& info );
    Napi::Value GetDwMinimumSpeakingRate( const Napi::CallbackInfo& info );
    Napi::Value GetDwMaximumSpeakingRate( const Napi::CallbackInfo& info );
    Napi::Value GetDwNumberOfPredefinedSpeakers( const Napi::CallbackInfo& info );
    Napi::Value GetDwCharacterSet( const Napi::CallbackInfo& info );
    Napi::Value GetVersion( const Napi::CallbackInfo& info );

    TTS_CAPS_T ttsCapsT;
};