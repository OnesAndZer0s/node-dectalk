#include "src/TTSIndexTag.h"

#include <napi.h>
#include <ttsapi.h>

Napi::FunctionReference TTSIndexTag::constructor;

Napi::Object TTSIndexTag::Init( Napi::Env env, Napi::Object exports ) {
  Napi::Function func =
      DefineClass( env,
          "TTSIndex",
          {
              InstanceAccessor< &TTSIndexTag::GetDwIndexValue, &TTSIndexTag::SetDwIndexValue >( "index" ),
              InstanceAccessor< &TTSIndexTag::GetDwIndexSampleNumber, &TTSIndexTag::SetDwIndexSampleNumber >( "sampleNumber" ),

          } );

  constructor = Napi::Persistent( func );
  constructor.SuppressDestruct();
  // env.SetInstanceData( constructor );

  // exports.Set( "TTSIndexTag", func );
  return exports;
}

TTSIndexTag::TTSIndexTag( const Napi::CallbackInfo& info ):
    Napi::ObjectWrap< TTSIndexTag >( info ) {
}

TTS_INDEX_T TTSIndexTag::ToStruct() {
  TTS_INDEX_T index;
  index.dwIndexValue = dwIndexValue;
  index.dwIndexSampleNumber = dwIndexSampleNumber;
  return index;
}

Napi::Object TTSIndexTag::FromStruct( Napi::Env env, TTS_INDEX_T index ) {
  Napi::Object from = TTSIndexTag::constructor.New( {} );
  TTSIndexTag ttsindex = *Napi::ObjectWrap< TTSIndexTag >::Unwrap( from );
  ttsindex.dwIndexValue = index.dwIndexValue;
  ttsindex.dwIndexSampleNumber = index.dwIndexSampleNumber;
  ttsindex.dwReserved = index.dwReserved;

  return from;
}

Napi::Value TTSIndexTag::GetDwIndexValue( const Napi::CallbackInfo& info ) {
  return Napi::Number::New( info.Env(), dwIndexValue );
}

void TTSIndexTag::SetDwIndexValue( const Napi::CallbackInfo& info, const Napi::Value& value ) {
  dwIndexValue = value.As< Napi::Number >().Uint32Value();
}

Napi::Value TTSIndexTag::GetDwIndexSampleNumber( const Napi::CallbackInfo& info ) {
  return Napi::Number::New( info.Env(), dwIndexSampleNumber );
}

void TTSIndexTag::SetDwIndexSampleNumber( const Napi::CallbackInfo& info, const Napi::Value& value ) {
  dwIndexSampleNumber = value.As< Napi::Number >().Uint32Value();
}
