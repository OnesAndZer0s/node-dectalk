#pragma once

#include "napi.h"

#include <ttsapi.h>

class TTSCapsTag : public Napi::ObjectWrap< TTSCapsTag > {
  public:
    static Napi::Object Init( Napi::Env env, Napi::Object exports );
    TTSCapsTag( const Napi::CallbackInfo& info );
    static Napi::FunctionReference constructor;

    TTS_CAPS_T ToStruct();
    static Napi::Object FromStruct( Napi::Env env, TTS_CAPS_T caps );

    DWORD dwNumberOfLanguages;
    Napi::Value GetDwNumberOfLanguages( const Napi::CallbackInfo& info );
    LPLANGUAGE_PARAMS_T lpLanguageParamsArray;
    Napi::Value GetLpLanguageParamsArray( const Napi::CallbackInfo& info );
    DWORD dwSampleRate;
    Napi::Value GetDwSampleRate( const Napi::CallbackInfo& info );
    DWORD dwMinimumSpeakingRate;
    Napi::Value GetDwMinimumSpeakingRate( const Napi::CallbackInfo& info );
    DWORD dwMaximumSpeakingRate;
    Napi::Value GetDwMaximumSpeakingRate( const Napi::CallbackInfo& info );
    DWORD dwNumberOfPredefinedSpeakers;
    Napi::Value GetDwNumberOfPredefinedSpeakers( const Napi::CallbackInfo& info );
    DWORD dwCharacterSet;
    Napi::Value GetDwCharacterSet( const Napi::CallbackInfo& info );
    DWORD version;
    Napi::Value GetVersion( const Napi::CallbackInfo& info );
};