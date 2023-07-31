#include "src/TTSPhonemeTag.h"

#include <napi.h>
#include <ttsapi.h>

Napi::FunctionReference TTSPhonemeTag::constructor;

Napi::Object TTSPhonemeTag::Init( Napi::Env env, Napi::Object exports ) {
  Napi::Function func =
      DefineClass( env,
          "TTSPhoneme",
          {
              InstanceAccessor< &TTSPhonemeTag::GetDwPhoneme >( "phoneme" ),
              InstanceAccessor< &TTSPhonemeTag::GetDwPhonemeSampleNumber >( "sampleNumber" ),
              InstanceAccessor< &TTSPhonemeTag::GetDwPhonemeDuration >( "duration" ),
          } );

  constructor = Napi::Persistent( func );
  constructor.SuppressDestruct();

  // exports.Set( "TTSPhonemeTag", func );
  return exports;
}

TTSPhonemeTag::TTSPhonemeTag( const Napi::CallbackInfo& info ):
    Napi::ObjectWrap< TTSPhonemeTag >( info ) {
  TTS_PHONEME_T ph = *(LPTTS_PHONEME_T) malloc( sizeof( TTS_PHONEME_T ) );
  ttsPhonemeT = ph;
}

Napi::Object TTSPhonemeTag::FromStruct( Napi::Env env, TTS_PHONEME_T phoneme ) {
  Napi::Object from = TTSPhonemeTag::constructor.New( {} );
  TTSPhonemeTag* ttsphoneme = Napi::ObjectWrap< TTSPhonemeTag >::Unwrap( from );
  ttsphoneme->ttsPhonemeT = phoneme;

  return from;
}

Napi::Value TTSPhonemeTag::GetDwPhoneme( const Napi::CallbackInfo& info ) {
  return Napi::Number::New( info.Env(), ttsPhonemeT.dwPhoneme );
}

Napi::Value TTSPhonemeTag::GetDwPhonemeSampleNumber( const Napi::CallbackInfo& info ) {
  return Napi::Number::New( info.Env(), ttsPhonemeT.dwPhonemeSampleNumber );
}

Napi::Value TTSPhonemeTag::GetDwPhonemeDuration( const Napi::CallbackInfo& info ) {
  return Napi::Number::New( info.Env(), ttsPhonemeT.dwPhonemeDuration );
}
