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
  // env.SetInstanceData( constructor );

  // exports.Set( "LanguageParamsTag", func );
  return exports;
}

LanguageParamsTag::LanguageParamsTag( const Napi::CallbackInfo& info ):
    Napi::ObjectWrap< LanguageParamsTag >( info ) {
}

LANGUAGE_PARAMS_T LanguageParamsTag::ToStruct() {
  LANGUAGE_PARAMS_T params;
  params.dwLanguage = dwLanguage;
  params.dwLanguageAttributes = dwLanguageAttributes;
  return params;
}

Napi::Object LanguageParamsTag::FromStruct( Napi::Env env, LANGUAGE_PARAMS_T params ) {
  Napi::Object from = LanguageParamsTag::constructor.New( {} );
  LanguageParamsTag* langParamTag = Napi::ObjectWrap< LanguageParamsTag >::Unwrap( from );
  langParamTag->dwLanguage = params.dwLanguage;
  langParamTag->dwLanguageAttributes = params.dwLanguageAttributes;

  return from;
}

Napi::Value LanguageParamsTag::GetDwLanguage( const Napi::CallbackInfo& info ) {
  return Napi::Number::New( info.Env(), dwLanguage );
}

void LanguageParamsTag::SetDwLanguage( const Napi::CallbackInfo& info, const Napi::Value& value ) {
  dwLanguage = value.As< Napi::Number >().Uint32Value();
}

Napi::Value LanguageParamsTag::GetDwLanguageAttributes( const Napi::CallbackInfo& info ) {
  return Napi::Number::New( info.Env(), dwLanguageAttributes );
}

void LanguageParamsTag::SetDwLanguageAttributes( const Napi::CallbackInfo& info, const Napi::Value& value ) {
  dwLanguageAttributes = value.As< Napi::Number >().Uint32Value();
}