#pragma once

#include <napi.h>
#include <ttsapi.h>

class TTSBufferTag : public Napi::ObjectWrap< TTSBufferTag > {
  public:
    static Napi::Object Init( Napi::Env env, Napi::Object exports );
    TTSBufferTag( const Napi::CallbackInfo& info );
    static Napi::FunctionReference constructor;

    static Napi::Object FromStruct( Napi::Env env, TTS_BUFFER_T caps );

    Napi::Value GetLpData( const Napi::CallbackInfo& info );
    Napi::Value GetLpPhonemeArray( const Napi::CallbackInfo& info );
    Napi::Value GetLpIndexArray( const Napi::CallbackInfo& info );
    Napi::Value GetDwMaximumBufferLength( const Napi::CallbackInfo& info );
    Napi::Value GetDwMaximumNumberOfPhonemeChanges( const Napi::CallbackInfo& info );
    Napi::Value GetDwMaximumNumberOfIndexMarks( const Napi::CallbackInfo& info );
    TTS_BUFFER_T ttsBufferT;
};
