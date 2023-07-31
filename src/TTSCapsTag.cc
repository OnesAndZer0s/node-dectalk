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

  return exports;
}

TTSCapsTag::TTSCapsTag( const Napi::CallbackInfo& info ):
    Napi::ObjectWrap< TTSCapsTag >( info ) {
}

Napi::Object TTSCapsTag::FromStruct( Napi::Env env, TTS_CAPS_T caps ) {
  Napi::Object from = TTSCapsTag::constructor.New( {} );
  TTSCapsTag* ttscapsTag = Napi::ObjectWrap< TTSCapsTag >::Unwrap( from );
  ttscapsTag->ttsCapsT = caps;

  return from;
}

Napi::Value TTSCapsTag::GetDwNumberOfLanguages( const Napi::CallbackInfo& info ) {
  return Napi::Number::New( info.Env(), ttsCapsT.dwNumberOfLanguages );
}

Napi::Value TTSCapsTag::GetLpLanguageParamsArray( const Napi::CallbackInfo& info ) {
  Napi::Array array = Napi::Array::New( info.Env(), ttsCapsT.dwNumberOfLanguages );
  for( int i = 0; i < ttsCapsT.dwNumberOfLanguages; i++ )
    array.Set( i, LanguageParamsTag::FromStruct( info.Env(), ttsCapsT.lpLanguageParamsArray [ i ] ) );
  return array;
}

Napi::Value TTSCapsTag::GetDwSampleRate( const Napi::CallbackInfo& info ) {
  return Napi::Number::New( info.Env(), ttsCapsT.dwSampleRate );
}

Napi::Value TTSCapsTag::GetDwMinimumSpeakingRate( const Napi::CallbackInfo& info ) {
  return Napi::Number::New( info.Env(), ttsCapsT.dwMinimumSpeakingRate );
}

Napi::Value TTSCapsTag::GetDwMaximumSpeakingRate( const Napi::CallbackInfo& info ) {
  return Napi::Number::New( info.Env(), ttsCapsT.dwMaximumSpeakingRate );
}

Napi::Value TTSCapsTag::GetDwNumberOfPredefinedSpeakers( const Napi::CallbackInfo& info ) {
  return Napi::Number::New( info.Env(), ttsCapsT.dwNumberOfPredefinedSpeakers );
}

Napi::Value TTSCapsTag::GetDwCharacterSet( const Napi::CallbackInfo& info ) {
  return Napi::Number::New( info.Env(), ttsCapsT.dwCharacterSet );
}

Napi::Value TTSCapsTag::GetVersion( const Napi::CallbackInfo& info ) {
  return Napi::Number::New( info.Env(), ttsCapsT.Version );
}