#pragma once

#include "napi.h"

#include <ttsapi.h>

class TTSIndexTag : public Napi::ObjectWrap< TTSIndexTag > {
  public:
    static Napi::Object Init( Napi::Env env, Napi::Object exports );
    TTSIndexTag( const Napi::CallbackInfo& info );
    static Napi::FunctionReference constructor;

    TTS_INDEX_T ToStruct();
    static Napi::Object FromStruct( Napi::Env env, TTS_INDEX_T caps );

    DWORD dwIndexValue;
    void SetDwIndexValue( const Napi::CallbackInfo& info, const Napi::Value& value );
    Napi::Value GetDwIndexValue( const Napi::CallbackInfo& info );
    DWORD dwIndexSampleNumber;
    void SetDwIndexSampleNumber( const Napi::CallbackInfo& info, const Napi::Value& value );
    Napi::Value GetDwIndexSampleNumber( const Napi::CallbackInfo& info );
    DWORD dwReserved;
};
