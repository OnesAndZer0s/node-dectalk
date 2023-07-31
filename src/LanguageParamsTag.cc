#include "src/LanguageParamsTag.h"

#include <napi.h>
#include <ttsapi.h>

Napi::FunctionReference LanguageParamsTag::constructor;

Napi::Object LanguageParamsTag::Init( Napi::Env env, Napi::Object exports ) {
  Napi::Function func =
      DefineClass( env,
          "LanguageParams",
          { InstanceAccessor( "language", &LanguageParamsTag::GetDwLanguage, &LanguageParamsTag::SetDwLanguage ),
              InstanceAccessor( "languageAttributes", &LanguageParamsTag::GetDwLanguageAttributes, &LanguageParamsTag::SetDwLanguageAttributes ) } );

  constructor = Napi::Persistent( func );
  constructor.SuppressDestruct();
  return exports;
}

LanguageParamsTag::LanguageParamsTag( const Napi::CallbackInfo& info ):
    Napi::ObjectWrap< LanguageParamsTag >( info ) {
}

Napi::Object LanguageParamsTag::FromStruct( Napi::Env env, LANGUAGE_PARAMS_T params ) {
  Napi::Object from = LanguageParamsTag::constructor.New( {} );
  LanguageParamsTag* langParamTag = Napi::ObjectWrap< LanguageParamsTag >::Unwrap( from );
  langParamTag->languageParamsT = params;

  return from;
}

Napi::Value LanguageParamsTag::GetDwLanguage( const Napi::CallbackInfo& info ) {
  return Napi::Number::New( info.Env(), languageParamsT.dwLanguage );
}

void LanguageParamsTag::SetDwLanguage( const Napi::CallbackInfo& info, const Napi::Value& value ) {
  languageParamsT.dwLanguage = value.As< Napi::Number >().Uint32Value();
}

Napi::Value LanguageParamsTag::GetDwLanguageAttributes( const Napi::CallbackInfo& info ) {
  return Napi::Number::New( info.Env(), languageParamsT.dwLanguageAttributes );
}

void LanguageParamsTag::SetDwLanguageAttributes( const Napi::CallbackInfo& info, const Napi::Value& value ) {
  languageParamsT.dwLanguageAttributes = value.As< Napi::Number >().Uint32Value();
}