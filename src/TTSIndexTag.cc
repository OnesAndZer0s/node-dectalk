#include "src/TTSIndexTag.h"

#include <napi.h>
#include <ttsapi.h>

Napi::FunctionReference TTSIndexTag::constructor;

Napi::Object TTSIndexTag::Init( Napi::Env env, Napi::Object exports ) {
  Napi::Function func =
      DefineClass( env,
          "TTSIndex",
          {
              InstanceAccessor< &TTSIndexTag::GetDwIndexValue >( "index" ),
              InstanceAccessor< &TTSIndexTag::GetDwIndexSampleNumber >( "sampleNumber" ),

          } );

  constructor = Napi::Persistent( func );
  constructor.SuppressDestruct();

  return exports;
}

TTSIndexTag::TTSIndexTag( const Napi::CallbackInfo& info ):
    Napi::ObjectWrap< TTSIndexTag >( info ) {
  TTS_INDEX_T ind = *(LPTTS_INDEX_T) malloc( sizeof( TTS_INDEX_T ) );

  ttsIndexT = ind;
}

Napi::Object TTSIndexTag::FromStruct( Napi::Env env, TTS_INDEX_T index ) {
  Napi::Object from = TTSIndexTag::constructor.New( {} );
  TTSIndexTag* buf = Napi::ObjectWrap< TTSIndexTag >::Unwrap( from );
  buf->ttsIndexT = index;

  return from;
}

Napi::Value TTSIndexTag::GetDwIndexValue( const Napi::CallbackInfo& info ) {
  return Napi::Number::New( info.Env(), ttsIndexT.dwIndexValue );
}

Napi::Value TTSIndexTag::GetDwIndexSampleNumber( const Napi::CallbackInfo& info ) {
  return Napi::Number::New( info.Env(), ttsIndexT.dwIndexSampleNumber );
}
