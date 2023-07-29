#include "src/TTSPhonemeTag.h"

#include <napi.h>
#include <ttsapi.h>

Napi::FunctionReference TTSPhonemeTag::constructor;

Napi::Object TTSPhonemeTag::Init( Napi::Env env, Napi::Object exports ) {
  Napi::Function func =
      DefineClass( env,
          "TTSPhoneme",
          {
              InstanceAccessor< &TTSPhonemeTag::GetDwPhoneme, &TTSPhonemeTag::SetDwPhoneme >( "phoneme" ),
              InstanceAccessor< &TTSPhonemeTag::GetDwPhonemeSampleNumber, &TTSPhonemeTag::SetDwPhonemeSampleNumber >( "sampleNumber" ),
              InstanceAccessor< &TTSPhonemeTag::GetDwPhonemeDuration, &TTSPhonemeTag::SetDwPhonemeDuration >( "duration" ),
          } );

  constructor = Napi::Persistent( func );
  constructor.SuppressDestruct();

  exports.Set( "TTSPhonemeTag", func );
  return exports;
}

TTSPhonemeTag::TTSPhonemeTag( const Napi::CallbackInfo& info ):
    Napi::ObjectWrap< TTSPhonemeTag >( info ) {
}

TTS_PHONEME_T TTSPhonemeTag::ToStruct() {
  TTS_PHONEME_T phoneme;
  phoneme.dwPhoneme = dwPhoneme;
  phoneme.dwPhonemeSampleNumber = dwPhonemeSampleNumber;
  phoneme.dwPhonemeDuration = dwPhonemeDuration;
  phoneme.dwReserved = dwReserved;
  return phoneme;
}

Napi::Object TTSPhonemeTag::FromStruct( Napi::Env env, TTS_PHONEME_T phoneme ) {
  Napi::Object from = TTSPhonemeTag::constructor.New( {} );
  TTSPhonemeTag ttsphoneme = *Napi::ObjectWrap< TTSPhonemeTag >::Unwrap( from );
  ttsphoneme.dwPhoneme = phoneme.dwPhoneme;
  ttsphoneme.dwPhonemeSampleNumber = phoneme.dwPhonemeSampleNumber;
  ttsphoneme.dwPhonemeDuration = phoneme.dwPhonemeDuration;
  ttsphoneme.dwReserved = phoneme.dwReserved;

  return from;
}

Napi::Value TTSPhonemeTag::GetDwPhoneme( const Napi::CallbackInfo& info ) {
  return Napi::Number::New( info.Env(), dwPhoneme );
}

void TTSPhonemeTag::SetDwPhoneme( const Napi::CallbackInfo& info, const Napi::Value& value ) {
  dwPhoneme = value.As< Napi::Number >().Uint32Value();
}

Napi::Value TTSPhonemeTag::GetDwPhonemeSampleNumber( const Napi::CallbackInfo& info ) {
  return Napi::Number::New( info.Env(), dwPhonemeSampleNumber );
}

void TTSPhonemeTag::SetDwPhonemeSampleNumber( const Napi::CallbackInfo& info, const Napi::Value& value ) {
  dwPhonemeSampleNumber = value.As< Napi::Number >().Uint32Value();
}

Napi::Value TTSPhonemeTag::GetDwPhonemeDuration( const Napi::CallbackInfo& info ) {
  return Napi::Number::New( info.Env(), dwPhonemeDuration );
}

void TTSPhonemeTag::SetDwPhonemeDuration( const Napi::CallbackInfo& info, const Napi::Value& value ) {
  dwPhonemeDuration = value.As< Napi::Number >().Uint32Value();
}
