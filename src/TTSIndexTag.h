#pragma once

#include "napi.h"

#include <ttsapi.h>

class TTSIndexTag : public Napi::ObjectWrap< TTSIndexTag > {
  public:
    static Napi::Object Init( Napi::Env env, Napi::Object exports );
    TTSIndexTag( const Napi::CallbackInfo& info );
    static Napi::FunctionReference constructor;

    static Napi::Object FromStruct( Napi::Env env, TTS_INDEX_T caps );

    Napi::Value GetDwIndexValue( const Napi::CallbackInfo& info );
    Napi::Value GetDwIndexSampleNumber( const Napi::CallbackInfo& info );

    TTS_INDEX_T ttsIndexT;
};
