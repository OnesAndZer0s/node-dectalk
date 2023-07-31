#include "./TTSBufferTag.h"

#include <napi.h>
#include <ttsapi.h>

Napi::FunctionReference TTSBufferTag::constructor;

Napi::Object TTSBufferTag::Init( Napi::Env env, Napi::Object exports ) {
  Napi::HandleScope scope( env );

  Napi::Function func =
      DefineClass( env,
          "TTSBuffer",
          {
              InstanceAccessor< &TTSBufferTag::GetLpData, &TTSBufferTag::SetLpData >( "data" ),
              InstanceAccessor< &TTSBufferTag::GetLpPhonemeArray, &TTSBufferTag::SetLpPhonemeArray >( "phonemes" ),
              InstanceAccessor< &TTSBufferTag::GetLpIndexArray, &TTSBufferTag::SetLpIndexArray >( "indexes" ),
              InstanceAccessor< &TTSBufferTag::GetDwMaximumBufferLength, &TTSBufferTag::SetDwMaximumBufferLength >( "maxBufferLength" ),
              InstanceAccessor< &TTSBufferTag::GetDwMaximumNumberOfPhonemeChanges, &TTSBufferTag::SetDwMaximumNumberOfPhonemeChanges >( "maxPhonemeChanges" ),
              InstanceAccessor< &TTSBufferTag::GetDwMaximumNumberOfIndexMarks, &TTSBufferTag::SetDwMaximumNumberOfIndexMarks >( "maxIndexMarks" ),
              InstanceAccessor< &TTSBufferTag::GetDwBufferLength, &TTSBufferTag::SetDwBufferLength >( "bufferLength" ),
              InstanceAccessor< &TTSBufferTag::GetDwNumberOfPhonemeChanges, &TTSBufferTag::SetDwNumberOfPhonemeChanges >( "phonemeChanges" ),
              InstanceAccessor< &TTSBufferTag::GetDwNumberOfIndexMarks, &TTSBufferTag::SetDwNumberOfIndexMarks >( "indexMarks" ),
          } );

  constructor = Napi::Persistent( func );
  constructor.SuppressDestruct();
  // env.SetInstanceData( constructor );

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
  // bs.dwBufferLength = 0;
  // bs.dwMaximumNumberOfIndexMarks = 0;
  // bs.dwMaximumNumberOfPhonemeChanges = 0;
  // bs.dwNumberOfIndexMarks = 0;
  // bs.dwNumberOfPhonemeChanges = 0;
  // bs.dwReserved = 0;

  // bs.lpIndexArray = NULL;
  // bs.lpPhonemeArray = NULL;
  // bs.lpData = NULL;

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
  // return Napi::Buffer< char >::New( info.Env(), lpData, dwBufferLength );
}

void TTSBufferTag::SetLpData( const Napi::CallbackInfo& info, const Napi::Value& value ) {
  ttsBufferT.lpData = value.As< Napi::Buffer< char > >().Data();
  // lpData = value.As< Napi::Buffer< char > >().Data();
}

Napi::Value TTSBufferTag::GetLpPhonemeArray( const Napi::CallbackInfo& info ) {
  return Napi::Buffer< TTS_PHONEME_T >::New( info.Env(), ttsBufferT.lpPhonemeArray, ttsBufferT.dwNumberOfPhonemeChanges );
  // return Napi::Buffer< TTS_PHONEME_T >::New( info.Env(), lpPhonemeArray, dwNumberOfPhonemeChanges );
}

void TTSBufferTag::SetLpPhonemeArray( const Napi::CallbackInfo& info, const Napi::Value& value ) {
  ttsBufferT.lpPhonemeArray = value.As< Napi::Buffer< TTS_PHONEME_T > >().Data();
  // lpPhonemeArray = value.As< Napi::Buffer< TTS_PHONEME_T > >().Data();
}

Napi::Value TTSBufferTag::GetLpIndexArray( const Napi::CallbackInfo& info ) {
  return Napi::Buffer< TTS_INDEX_T >::New( info.Env(), ttsBufferT.lpIndexArray, ttsBufferT.dwNumberOfIndexMarks );
  // return Napi::Buffer< TTS_INDEX_T >::New( info.Env(), lpIndexArray, dwNumberOfIndexMarks );
}

void TTSBufferTag::SetLpIndexArray( const Napi::CallbackInfo& info, const Napi::Value& value ) {
  ttsBufferT.lpIndexArray = value.As< Napi::Buffer< TTS_INDEX_T > >().Data();
  // lpIndexArray = value.As< Napi::Buffer< TTS_INDEX_T > >().Data();
}

Napi::Value TTSBufferTag::GetDwMaximumBufferLength( const Napi::CallbackInfo& info ) {
  return Napi::Number::New( info.Env(), ttsBufferT.dwMaximumBufferLength );
  // return Napi::Number::New( info.Env(), dwMaximumBufferLength );
}

void TTSBufferTag::SetDwMaximumBufferLength( const Napi::CallbackInfo& info, const Napi::Value& value ) {
  ttsBufferT.dwMaximumBufferLength = value.As< Napi::Number >().Uint32Value();
  // dwMaximumBufferLength = value.As< Napi::Number >().Uint32Value();
}

Napi::Value TTSBufferTag::GetDwMaximumNumberOfPhonemeChanges( const Napi::CallbackInfo& info ) {
  return Napi::Number::New( info.Env(), ttsBufferT.dwMaximumNumberOfPhonemeChanges );
  // return Napi::Number::New( info.Env(), dwMaximumNumberOfPhonemeChanges );
}

void TTSBufferTag::SetDwMaximumNumberOfPhonemeChanges( const Napi::CallbackInfo& info, const Napi::Value& value ) {
  ttsBufferT.dwMaximumNumberOfPhonemeChanges = value.As< Napi::Number >().Uint32Value();
  // dwMaximumNumberOfPhonemeChanges = value.As< Napi::Number >().Uint32Value();
}

Napi::Value TTSBufferTag::GetDwMaximumNumberOfIndexMarks( const Napi::CallbackInfo& info ) {
  return Napi::Number::New( info.Env(), ttsBufferT.dwMaximumNumberOfIndexMarks );
  // return Napi::Number::New( info.Env(), dwMaximumNumberOfIndexMarks );
}

void TTSBufferTag::SetDwMaximumNumberOfIndexMarks( const Napi::CallbackInfo& info, const Napi::Value& value ) {
  ttsBufferT.dwMaximumNumberOfIndexMarks = value.As< Napi::Number >().Uint32Value();
  // dwMaximumNumberOfIndexMarks = value.As< Napi::Number >().Uint32Value();
}

Napi::Value TTSBufferTag::GetDwBufferLength( const Napi::CallbackInfo& info ) {
  return Napi::Number::New( info.Env(), ttsBufferT.dwBufferLength );
  // return Napi::Number::New( info.Env(), dwBufferLength );
}

void TTSBufferTag::SetDwBufferLength( const Napi::CallbackInfo& info, const Napi::Value& value ) {
  ttsBufferT.dwBufferLength = value.As< Napi::Number >().Uint32Value();
  // dwBufferLength = value.As< Napi::Number >().Uint32Value();
}

Napi::Value TTSBufferTag::GetDwNumberOfPhonemeChanges( const Napi::CallbackInfo& info ) {
  return Napi::Number::New( info.Env(), ttsBufferT.dwNumberOfPhonemeChanges );
  // return Napi::Number::New( info.Env(), dwNumberOfPhonemeChanges );
}

void TTSBufferTag::SetDwNumberOfPhonemeChanges( const Napi::CallbackInfo& info, const Napi::Value& value ) {
  ttsBufferT.dwNumberOfPhonemeChanges = value.As< Napi::Number >().Uint32Value();
  // dwNumberOfPhonemeChanges = value.As< Napi::Number >().Uint32Value();
}

Napi::Value TTSBufferTag::GetDwNumberOfIndexMarks( const Napi::CallbackInfo& info ) {
  return Napi::Number::New( info.Env(), ttsBufferT.dwNumberOfIndexMarks );
  // return Napi::Number::New( info.Env(), dwNumberOfIndexMarks );
}

void TTSBufferTag::SetDwNumberOfIndexMarks( const Napi::CallbackInfo& info, const Napi::Value& value ) {
  ttsBufferT.dwNumberOfIndexMarks = value.As< Napi::Number >().Uint32Value();
  // dwNumberOfIndexMarks = value.As< Napi::Number >().Uint32Value();
}
