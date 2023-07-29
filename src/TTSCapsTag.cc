#include "./TTSCapsTag.h"

#include "./LanguageParamsTag.h"

#include <napi.h>
#include <ttsapi.h>

Napi::FunctionReference TTSCapsTag::constructor;

Napi::Object TTSCapsTag::Init( Napi::Env env, Napi::Object exports ) {
  Napi::HandleScope scope( env );

  Napi::Function func =
      DefineClass( env,
          "TTSCaps",
          { InstanceAccessor< &TTSCapsTag::GetDwNumberOfLanguages >( "numberOfLanguages" ),
              InstanceAccessor< &TTSCapsTag::GetLpLanguageParamsArray >( "languageParams" ),
              InstanceAccessor< &TTSCapsTag::GetDwSampleRate >( "sampleRate" ),
              InstanceAccessor< &TTSCapsTag::GetDwMinimumSpeakingRate >( "minimumSpeakingRate" ),
              InstanceAccessor< &TTSCapsTag::GetDwMaximumSpeakingRate >( "maximumSpeakingRate" ),
              InstanceAccessor< &TTSCapsTag::GetDwNumberOfPredefinedSpeakers >( "numberOfPredefinedSpeakers" ),
              InstanceAccessor< &TTSCapsTag::GetDwCharacterSet >( "characterSet" ),
              InstanceAccessor< &TTSCapsTag::GetVersion >( "version" ) } );

  constructor = Napi::Persistent( func );
  constructor.SuppressDestruct();
  // env.SetInstanceData( constructor );

  // exports.Set( "TTSCapsTag", func );
  return exports;
}

TTSCapsTag::TTSCapsTag( const Napi::CallbackInfo& info ):
    Napi::ObjectWrap< TTSCapsTag >( info ) {
}

TTS_CAPS_T TTSCapsTag::ToStruct() {
  TTS_CAPS_T caps;
  caps.dwNumberOfLanguages = dwNumberOfLanguages;
  caps.lpLanguageParamsArray = lpLanguageParamsArray;
  caps.dwSampleRate = dwSampleRate;
  caps.dwMinimumSpeakingRate = dwMinimumSpeakingRate;
  caps.dwMaximumSpeakingRate = dwMaximumSpeakingRate;
  caps.dwNumberOfPredefinedSpeakers = dwNumberOfPredefinedSpeakers;
  caps.dwCharacterSet = dwCharacterSet;
  caps.Version = version;
  return caps;
}

Napi::Object TTSCapsTag::FromStruct( Napi::Env env, TTS_CAPS_T caps ) {
  Napi::Object from = TTSCapsTag::constructor.New( {} );
  TTSCapsTag* ttscapsTag = Napi::ObjectWrap< TTSCapsTag >::Unwrap( from );
  ttscapsTag->dwNumberOfLanguages = caps.dwNumberOfLanguages;
  ttscapsTag->lpLanguageParamsArray = caps.lpLanguageParamsArray;
  ttscapsTag->dwSampleRate = caps.dwSampleRate;
  ttscapsTag->dwMinimumSpeakingRate = caps.dwMinimumSpeakingRate;
  ttscapsTag->dwMaximumSpeakingRate = caps.dwMaximumSpeakingRate;
  ttscapsTag->dwNumberOfPredefinedSpeakers = caps.dwNumberOfPredefinedSpeakers;
  ttscapsTag->dwCharacterSet = caps.dwCharacterSet;
  ttscapsTag->version = caps.Version;

  return from;
}

Napi::Value TTSCapsTag::GetDwNumberOfLanguages( const Napi::CallbackInfo& info ) {
  return Napi::Number::New( info.Env(), dwNumberOfLanguages );
}

Napi::Value TTSCapsTag::GetLpLanguageParamsArray( const Napi::CallbackInfo& info ) {
  Napi::Array array = Napi::Array::New( info.Env(), dwNumberOfLanguages );
  for( int i = 0; i < dwNumberOfLanguages; i++ )
    array.Set( i, LanguageParamsTag::FromStruct( info.Env(), lpLanguageParamsArray [ i ] ) );
  return array;
}

Napi::Value TTSCapsTag::GetDwSampleRate( const Napi::CallbackInfo& info ) {
  return Napi::Number::New( info.Env(), dwSampleRate );
}

Napi::Value TTSCapsTag::GetDwMinimumSpeakingRate( const Napi::CallbackInfo& info ) {
  return Napi::Number::New( info.Env(), dwMinimumSpeakingRate );
}

Napi::Value TTSCapsTag::GetDwMaximumSpeakingRate( const Napi::CallbackInfo& info ) {
  return Napi::Number::New( info.Env(), dwMaximumSpeakingRate );
}

Napi::Value TTSCapsTag::GetDwNumberOfPredefinedSpeakers( const Napi::CallbackInfo& info ) {
  return Napi::Number::New( info.Env(), dwNumberOfPredefinedSpeakers );
}

Napi::Value TTSCapsTag::GetDwCharacterSet( const Napi::CallbackInfo& info ) {
  return Napi::Number::New( info.Env(), dwCharacterSet );
}

Napi::Value TTSCapsTag::GetVersion( const Napi::CallbackInfo& info ) {
  return Napi::Number::New( info.Env(), version );
}