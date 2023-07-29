#pragma once

#include <napi.h>
#include <ttsapi.h>

class TTSBufferTag : public Napi::ObjectWrap< TTSBufferTag > {
  public:
    static Napi::Object Init( Napi::Env env, Napi::Object exports );
    TTSBufferTag( const Napi::CallbackInfo& info );
    static Napi::FunctionReference constructor;

    TTS_BUFFER_T GetStruct();
    // static Napi::Object FromStruct( Napi::Env env, TTS_BUFFER_T caps );

    Napi::Value GetLpData( const Napi::CallbackInfo& info );
    void SetLpData( const Napi::CallbackInfo& info, const Napi::Value& value );
    Napi::Value GetLpPhonemeArray( const Napi::CallbackInfo& info );
    void SetLpPhonemeArray( const Napi::CallbackInfo& info, const Napi::Value& value );
    Napi::Value GetLpIndexArray( const Napi::CallbackInfo& info );
    void SetLpIndexArray( const Napi::CallbackInfo& info, const Napi::Value& value );
    Napi::Value GetDwMaximumBufferLength( const Napi::CallbackInfo& info );
    void SetDwMaximumBufferLength( const Napi::CallbackInfo& info, const Napi::Value& value );
    Napi::Value GetDwMaximumNumberOfPhonemeChanges( const Napi::CallbackInfo& info );
    void SetDwMaximumNumberOfPhonemeChanges( const Napi::CallbackInfo& info, const Napi::Value& value );
    Napi::Value GetDwMaximumNumberOfIndexMarks( const Napi::CallbackInfo& info );
    void SetDwMaximumNumberOfIndexMarks( const Napi::CallbackInfo& info, const Napi::Value& value );
    Napi::Value GetDwBufferLength( const Napi::CallbackInfo& info );
    void SetDwBufferLength( const Napi::CallbackInfo& info, const Napi::Value& value );
    Napi::Value GetDwNumberOfPhonemeChanges( const Napi::CallbackInfo& info );
    void SetDwNumberOfPhonemeChanges( const Napi::CallbackInfo& info, const Napi::Value& value );
    Napi::Value GetDwNumberOfIndexMarks( const Napi::CallbackInfo& info );
    void SetDwNumberOfIndexMarks( const Napi::CallbackInfo& info, const Napi::Value& value );

    TTS_BUFFER_T ttsBufferT;
};
