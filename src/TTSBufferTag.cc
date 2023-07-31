#include "./TTSBufferTag.h"

#include "src/TTSIndexTag.h"
#include "src/TTSPhonemeTag.h"

#include <napi.h>
#include <ttsapi.h>

Napi::FunctionReference TTSBufferTag::constructor;

Napi::Object TTSBufferTag::Init( Napi::Env env, Napi::Object exports ) {
  Napi::HandleScope scope( env );

  Napi::Function func =
      DefineClass( env,
          "TTSBuffer",
          {
              InstanceAccessor< &TTSBufferTag::GetLpData >( "data" ),
              InstanceAccessor< &TTSBufferTag::GetLpPhonemeArray >( "phonemes" ),
              InstanceAccessor< &TTSBufferTag::GetLpIndexArray >( "indexes" ),
              InstanceAccessor< &TTSBufferTag::GetDwMaximumBufferLength >( "maxBufferLength" ),
              InstanceAccessor< &TTSBufferTag::GetDwMaximumNumberOfPhonemeChanges >( "maxPhonemeChanges" ),
              InstanceAccessor< &TTSBufferTag::GetDwMaximumNumberOfIndexMarks >( "maxIndexMarks" ),
          } );

  constructor = Napi::Persistent( func );
  constructor.SuppressDestruct();

  exports.Set( "TTSBuffer", func );
  return exports;
}

TTSBufferTag::TTSBufferTag( const Napi::CallbackInfo& info ):
    Napi::ObjectWrap< TTSBufferTag >( info ) {
  // check if there was object passed int constructor

  int dataLength = 256;
  int phonemeLength = 1;
  int indexLength = 256;
  if( info.Length() >= 1 ) {
    Napi::Object obj = info [ 0 ].As< Napi::Object >();

    if( obj.Has( "data" ) )
      dataLength = obj.Get( "data" ).As< Napi::Number >().Uint32Value();

    if( obj.Has( "phoneme" ) )
      phonemeLength = obj.Get( "phoneme" ).As< Napi::Number >().Uint32Value();

    if( obj.Has( "index" ) )
      indexLength = obj.Get( "index" ).As< Napi::Number >().Uint32Value();
  }
  TTS_BUFFER_T bs = *(LPTTS_BUFFER_T) malloc( sizeof( TTS_BUFFER_T ) );

  bs.lpData = (LPSTR) malloc( sizeof( LPSTR ) * dataLength );

  // create phoneme array
  bs.lpPhonemeArray = (LPTTS_PHONEME_T) malloc( sizeof( TTS_PHONEME_T ) * phonemeLength );

  // create index array
  bs.lpIndexArray = (LPTTS_INDEX_T) malloc( sizeof( TTS_INDEX_T ) * indexLength );

  bs.dwMaximumBufferLength = dataLength;
  bs.dwMaximumNumberOfIndexMarks = phonemeLength;
  bs.dwMaximumNumberOfPhonemeChanges = indexLength;
  ttsBufferT = bs;
}

Napi::Object TTSBufferTag::FromStruct( Napi::Env env, TTS_BUFFER_T bufs ) {
  Napi::Object from = TTSBufferTag::constructor.New( {} );
  TTSBufferTag* buf = Napi::ObjectWrap< TTSBufferTag >::Unwrap( from );
  buf->ttsBufferT = bufs;

  return from;
}

Napi::Value TTSBufferTag::GetLpData( const Napi::CallbackInfo& info ) {
  return Napi::Buffer< char >::New( info.Env(), ttsBufferT.lpData, ttsBufferT.dwBufferLength );
}

Napi::Value TTSBufferTag::GetLpPhonemeArray( const Napi::CallbackInfo& info ) {
  Napi::Array array = Napi::Array::New( info.Env(), ttsBufferT.dwNumberOfPhonemeChanges );
  for( int i = 0; i < ttsBufferT.dwNumberOfPhonemeChanges; i++ )
    array.Set( i, TTSPhonemeTag::FromStruct( info.Env(), ttsBufferT.lpPhonemeArray [ i ] ) );
  return array;
}

Napi::Value TTSBufferTag::GetLpIndexArray( const Napi::CallbackInfo& info ) {
  Napi::Array array = Napi::Array::New( info.Env(), ttsBufferT.dwNumberOfIndexMarks );
  for( int i = 0; i < ttsBufferT.dwNumberOfIndexMarks; i++ )
    array.Set( i, TTSIndexTag::FromStruct( info.Env(), ttsBufferT.lpIndexArray [ i ] ) );
  return array;
}

Napi::Value TTSBufferTag::GetDwMaximumBufferLength( const Napi::CallbackInfo& info ) {
  return Napi::Number::New( info.Env(), ttsBufferT.dwMaximumBufferLength );
}

Napi::Value TTSBufferTag::GetDwMaximumNumberOfPhonemeChanges( const Napi::CallbackInfo& info ) {
  return Napi::Number::New( info.Env(), ttsBufferT.dwMaximumNumberOfPhonemeChanges );
}

Napi::Value TTSBufferTag::GetDwMaximumNumberOfIndexMarks( const Napi::CallbackInfo& info ) {
  return Napi::Number::New( info.Env(), ttsBufferT.dwMaximumNumberOfIndexMarks );
}
