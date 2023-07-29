#include "src/DecTalk.h"

#include "dectalk/src/dapi/src/api/ttsapi.h"
#include "src/LanguageParamsTag.h"
#include "src/TTSBufferTag.h"
#include "src/TTSCapsTag.h"
#include "src/TTSIndexTag.h"
#include "src/TTSPhonemeTag.h"

#include <cstdio>
#include <functional>
#include <iostream>

// #include "AsyncTest.h" // NOLINT(build/include)
// #include "dectalk/dist/include/dtk/dtmmedefs.h"
// #include "dectalk/dist/include/dtk/ttsapi.h"
// #include "dectalk/src/dapi/src/api/ttsapi.h"

#include <napi.h>
#include <string>
#include <ttsapi.h>

Napi::Object DecTalk::Init( Napi::Env env, Napi::Object exports ) {
  Napi::Function func =
      DefineClass( env,
          "DecTalk",
          {
              InstanceMethod( "startup", &DecTalk::Startup ),
              InstanceMethod( "speakSync", &DecTalk::SpeakSync ),
              InstanceMethod( "speak", &DecTalk::Speak ),

              InstanceMethod( "syncSync", &DecTalk::SyncSync ),
              InstanceMethod( "sync", &DecTalk::Sync ),
              InstanceMethod( "shutdown", &DecTalk::Shutdown ),
              InstanceMethod( "pause", &DecTalk::Pause ),
              InstanceMethod( "resume", &DecTalk::Resume ),
              InstanceMethod( "reset", &DecTalk::Reset ),
              StaticMethod( "getCapabilities", &DecTalk::GetCapabilities ),

              InstanceMethod( "openWaveFileOut", &DecTalk::OpenWaveFileOut ),
              InstanceMethod( "closeWaveFileOut", &DecTalk::CloseWaveFileOut ),

              InstanceMethod( "openLogFile", &DecTalk::OpenLogFile ),
              InstanceMethod( "closeLogFile", &DecTalk::CloseLogFile ),

              InstanceMethod( "loadUserDictionary", &DecTalk::LoadUserDictionary ),
              InstanceMethod( "unloadUserDictionary", &DecTalk::UnloadUserDictionary ),

              // InstanceMethod( "openInMemory", &DecTalk::OpenInMemory ),
              // InstanceMethod( "closeInMemory", &DecTalk::CloseInMemory ),
              // InstanceMethod( "addBuffer", &DecTalk::AddBuffer ),
              // InstanceMethod( "returnBuffer", &DecTalk::ReturnBuffer ),

              InstanceAccessor< &DecTalk::GetSampleRate, &DecTalk::SetSampleRate >( "sampleRate" ),
              InstanceAccessor< &DecTalk::GetVolume, &DecTalk::SetVolume >( "volume" ),
              InstanceAccessor< &DecTalk::GetAttenuationVolume, &DecTalk::SetAttenuationVolume >( "attenuationVolume" ),
              InstanceAccessor< &DecTalk::GetRate, &DecTalk::SetRate >( "rate" ),
              InstanceAccessor< &DecTalk::GetSpeaker, &DecTalk::SetSpeaker >( "speaker" ),
              InstanceAccessor< &DecTalk::GetLanguage, &DecTalk::SetLanguage >( "language" ),

              InstanceAccessor< &DecTalk::GetInputCharacterCount >( "inputCharacterCount" ),
              InstanceAccessor< &DecTalk::GetIsSpeaking >( "isSpeaking" ),
              InstanceAccessor< &DecTalk::GetWaveOutDeviceID >( "waveOutDeviceID" ),

          } );

  Napi::FunctionReference* constructor = new Napi::FunctionReference();
  *constructor = Napi::Persistent( func );
  env.SetInstanceData( constructor );

  exports.Set( "DecTalk", func );
  return exports;
}

DecTalk::DecTalk( const Napi::CallbackInfo& info ):
    Napi::ObjectWrap< DecTalk >( info ) {}

void DecTalk::Startup( const Napi::CallbackInfo& info ) {
  if( ttsHandle != NULL )
    Napi::Error::New( info.Env(), "DecTalk already started.\n" ).ThrowAsJavaScriptException();

  // get device number
  unsigned int devNo;
  if( info.Length() < 1 || !info [ 0 ].IsNumber() )
    devNo = WAVE_MAPPER;
  else
    devNo = info [ 0 ].As< Napi::Number >().Uint32Value();

  // get device options
  DWORD devOptions;
  if( info.Length() < 2 || !info [ 1 ].IsNumber() )
    devOptions = 0;
  else
    devOptions = info [ 1 ].As< Napi::Number >().Uint32Value();

  LONG flag;
  if( info.Length() < 3 || !info [ 2 ].IsNumber() )
    flag = 0;
  else
    flag = info [ 2 ].As< Napi::Number >().Int32Value();

  int status = TextToSpeechStartup( &ttsHandle, devNo, devOptions, NULL, flag );
  if( status != MMSYSERR_NOERROR )
    Napi::Error::New( info.Env(), "Startup failed with code " + std::to_string( status ) + "\n" ).ThrowAsJavaScriptException();
}

void DecTalk::SpeakSync( const Napi::CallbackInfo& info ) {
  if( ttsHandle == NULL )
    Napi::Error::New( info.Env(), "DecTalk not started.\n" ).ThrowAsJavaScriptException();

  // get string
  if( info.Length() < 1 || !info [ 0 ].IsString() )
    Napi::Error::New( info.Env(), "Speak requires a string.\n" ).ThrowAsJavaScriptException();

  int force;
  if( info.Length() < 2 || !info [ 1 ].IsBoolean() )
    force = TTS_NORMAL;
  else
    force = info [ 1 ].As< Napi::Boolean >().Value();

  std::string fullwords = info [ 0 ].As< Napi::String >().Utf8Value();
  char* words = strdup( fullwords.c_str() );

  int status = TextToSpeechSpeak( ttsHandle, words, force );

  if( status != MMSYSERR_NOERROR )
    Napi::Error::New( info.Env(), "Speak failed with code " + std::to_string( status ) + "\n" ).ThrowAsJavaScriptException();
}

void DecTalk::SyncSync( const Napi::CallbackInfo& info ) {
  if( ttsHandle == NULL )
    Napi::Error::New( info.Env(), "DecTalk not started.\n" ).ThrowAsJavaScriptException();

  int status = TextToSpeechSync( ttsHandle );

  if( status != MMSYSERR_NOERROR )
    Napi::Error::New( info.Env(), "Sync failed with code " + std::to_string( status ) + "\n" ).ThrowAsJavaScriptException();
}

void DecTalk::Shutdown( const Napi::CallbackInfo& info ) {
  if( ttsHandle == NULL )
    Napi::Error::New( info.Env(), "DecTalk not started.\n" ).ThrowAsJavaScriptException();

  int status = TextToSpeechShutdown( ttsHandle );

  if( status != MMSYSERR_NOERROR )
    Napi::Error::New( info.Env(), "Shutdown failed with code " + std::to_string( status ) + "\n" ).ThrowAsJavaScriptException();
}

void DecTalk::Pause( const Napi::CallbackInfo& info ) {
  if( ttsHandle == NULL )
    Napi::Error::New( info.Env(), "DecTalk not started.\n" ).ThrowAsJavaScriptException();

  int status = TextToSpeechPause( ttsHandle );

  if( status != MMSYSERR_NOERROR )
    Napi::Error::New( info.Env(), "Pause failed with code " + std::to_string( status ) + "\n" ).ThrowAsJavaScriptException();
}

void DecTalk::Resume( const Napi::CallbackInfo& info ) {
  if( ttsHandle == NULL )
    Napi::Error::New( info.Env(), "DecTalk not started.\n" ).ThrowAsJavaScriptException();

  int status = TextToSpeechResume( ttsHandle );

  if( status != MMSYSERR_NOERROR )
    Napi::Error::New( info.Env(), "Resume failed with code " + std::to_string( status ) + "\n" ).ThrowAsJavaScriptException();
}

void DecTalk::Reset( const Napi::CallbackInfo& info ) {
  if( ttsHandle == NULL )
    Napi::Error::New( info.Env(), "DecTalk not started.\n" ).ThrowAsJavaScriptException();

  // get bool
  bool res = false;
  if( info.Length() < 1 || !info [ 0 ].IsBoolean() )
    res = false;
  else
    res = info [ 0 ].As< Napi::Boolean >().Value();

  int status = TextToSpeechReset( ttsHandle, res );

  if( status != MMSYSERR_NOERROR )
    Napi::Error::New( info.Env(), "Reset failed with code " + std::to_string( status ) + "\n" ).ThrowAsJavaScriptException();
}

class SpeakWorker : public Napi::AsyncWorker {
  public:
    SpeakWorker( const Napi::Env& env, LPTTS_HANDLE_T ttsHandle, char* text, int force ):
        Napi::AsyncWorker { env, "SpeakWorker" },
        m_deferred { env },
        ttsHandle { ttsHandle },
        text { text },
        force { force } {}

    ~SpeakWorker() {}

    Napi::Promise GetPromise() { return m_deferred.Promise(); }

    void Execute() {
      int status = TextToSpeechSpeak( ttsHandle, text, force );

      if( status != MMSYSERR_NOERROR ) {
        SetError( "Speak failed with code " + std::to_string( status ) );
        return;
      }
    }

    void OnOK() {
      m_deferred.Resolve( Napi::String::New( Env(), text ) );
    }

    void OnError( const Napi::Error& err ) { m_deferred.Reject( err.Value() ); }

  private:
    LPTTS_HANDLE_T ttsHandle;
    char* text;
    Napi::Promise::Deferred m_deferred;
    int force;
};

class SyncWorker : public Napi::AsyncWorker {
  public:
    SyncWorker( const Napi::Env& env, LPTTS_HANDLE_T ttsHandle ):
        Napi::AsyncWorker { env, "SyncWorker" },
        m_deferred { env },
        ttsHandle { ttsHandle } {}

    ~SyncWorker() {}

    Napi::Promise GetPromise() { return m_deferred.Promise(); }

    void Execute() {
      int status = TextToSpeechSync( ttsHandle );

      if( status != MMSYSERR_NOERROR ) {
        SetError( "Sync failed with code " + std::to_string( status ) );
        return;
      }
    }

    void OnOK() {
      m_deferred.Resolve( Env().Null() );
    }

    void OnError( const Napi::Error& err ) { m_deferred.Reject( err.Value() ); }

  private:
    LPTTS_HANDLE_T ttsHandle;
    char* text;
    Napi::Promise::Deferred m_deferred;
    int force;
};

Napi::Value DecTalk::Speak( const Napi::CallbackInfo& info ) {
  if( ttsHandle == NULL )
    Napi::Error::New( info.Env(), "DecTalk not started.\n" ).ThrowAsJavaScriptException();

  if( info.Length() < 1 || !info [ 0 ].IsString() )
    Napi::Error::New( info.Env(), "Speak requires a string.\n" ).ThrowAsJavaScriptException();

  std::string fullwords = info [ 0 ].As< Napi::String >().Utf8Value();
  char* words = strdup( fullwords.c_str() );

  int force;
  if( info.Length() < 2 || !info [ 1 ].IsBoolean() )
    force = TTS_NORMAL;
  else
    force = info [ 1 ].As< Napi::Boolean >().Value();

  SpeakWorker* SpeakWorker = new class SpeakWorker( info.Env(), ttsHandle, words, force );
  SpeakWorker->Queue();
  return SpeakWorker->GetPromise();
}

Napi::Value DecTalk::Sync( const Napi::CallbackInfo& info ) {
  if( ttsHandle == NULL )
    Napi::Error::New( info.Env(), "DecTalk not started.\n" ).ThrowAsJavaScriptException();

  SyncWorker* SyncWorker = new class SyncWorker( info.Env(), ttsHandle );
  SyncWorker->Queue();
  return SyncWorker->GetPromise();
}

Napi::Value DecTalk::GetSampleRate( const Napi::CallbackInfo& info ) {
  if( ttsHandle == NULL )
    Napi::Error::New( info.Env(), "DecTalk not started.\n" ).ThrowAsJavaScriptException();

  DWORD sampleRate;
  int status = TextToSpeechGetRate( ttsHandle, &sampleRate );

  if( status != MMSYSERR_NOERROR )
    Napi::Error::New( info.Env(), "GetSampleRate failed with code " + std::to_string( status ) + "\n" ).ThrowAsJavaScriptException();

  return Napi::Number::New( info.Env(), sampleRate );
}

void DecTalk::SetSampleRate( const Napi::CallbackInfo& info, const Napi::Value& value ) {
  if( ttsHandle == NULL )
    Napi::Error::New( info.Env(), "DecTalk not started.\n" ).ThrowAsJavaScriptException();

  if( !value.IsNumber() )
    Napi::Error::New( info.Env(), "SetSampleRate requires a number.\n" ).ThrowAsJavaScriptException();

  DWORD sampleRate = value.As< Napi::Number >().Uint32Value();
  int status = TextToSpeechSetRate( ttsHandle, sampleRate );

  if( status != MMSYSERR_NOERROR )
    Napi::Error::New( info.Env(), "SetSampleRate failed with code " + std::to_string( status ) + "\n" ).ThrowAsJavaScriptException();
}

Napi::Value DecTalk::GetVolume( const Napi::CallbackInfo& info ) {
  if( ttsHandle == NULL )
    Napi::Error::New( info.Env(), "DecTalk not started.\n" ).ThrowAsJavaScriptException();

  int volume;
  int status = TextToSpeechGetVolume( ttsHandle, VOLUME_MAIN, &volume );

  if( status != MMSYSERR_NOERROR )
    Napi::Error::New( info.Env(), "GetVolume failed with code " + std::to_string( status ) + "\n" ).ThrowAsJavaScriptException();

  return Napi::Number::New( info.Env(), volume );
}

void DecTalk::SetVolume( const Napi::CallbackInfo& info, const Napi::Value& value ) {
  if( ttsHandle == NULL )
    Napi::Error::New( info.Env(), "DecTalk not started.\n" ).ThrowAsJavaScriptException();

  if( !value.IsNumber() )
    Napi::Error::New( info.Env(), "SetVolume requires a number.\n" ).ThrowAsJavaScriptException();

  DWORD volume = value.As< Napi::Number >().Uint32Value();
  int status = TextToSpeechSetVolume( ttsHandle, VOLUME_MAIN, volume );

  if( status != MMSYSERR_NOERROR )
    Napi::Error::New( info.Env(), "SetVolume failed with code " + std::to_string( status ) + "\n" ).ThrowAsJavaScriptException();
}

Napi::Value DecTalk::GetAttenuationVolume( const Napi::CallbackInfo& info ) {
  if( ttsHandle == NULL )
    Napi::Error::New( info.Env(), "DecTalk not started.\n" ).ThrowAsJavaScriptException();

  int volume;
  int status = TextToSpeechGetVolume( ttsHandle, VOLUME_ATTENUATION, &volume );

  if( status != MMSYSERR_NOERROR )
    Napi::Error::New( info.Env(), "GetAttenuationVolume failed with code " + std::to_string( status ) + "\n" ).ThrowAsJavaScriptException();

  return Napi::Number::New( info.Env(), volume );
}

void DecTalk::SetAttenuationVolume( const Napi::CallbackInfo& info, const Napi::Value& value ) {
  if( ttsHandle == NULL )
    Napi::Error::New( info.Env(), "DecTalk not started.\n" ).ThrowAsJavaScriptException();

  if( !value.IsNumber() )
    Napi::Error::New( info.Env(), "SetAttenuationVolume requires a number.\n" ).ThrowAsJavaScriptException();

  DWORD volume = value.As< Napi::Number >().Uint32Value();
  int status = TextToSpeechSetVolume( ttsHandle, VOLUME_ATTENUATION, volume );

  if( status != MMSYSERR_NOERROR )
    Napi::Error::New( info.Env(), "SetAttenuationVolume failed with code " + std::to_string( status ) + "\n" ).ThrowAsJavaScriptException();
}

Napi::Value DecTalk::GetRate( const Napi::CallbackInfo& info ) {
  if( ttsHandle == NULL )
    Napi::Error::New( info.Env(), "DecTalk not started.\n" ).ThrowAsJavaScriptException();
  DWORD rate;
  int status = TextToSpeechGetRate( ttsHandle, &rate );

  if( status != MMSYSERR_NOERROR )
    Napi::Error::New( info.Env(), "GetRate failed with code " + std::to_string( status ) + "\n" ).ThrowAsJavaScriptException();

  return Napi::Number::New( info.Env(), rate );
}

void DecTalk::SetRate( const Napi::CallbackInfo& info, const Napi::Value& value ) {
  if( ttsHandle == NULL )
    Napi::Error::New( info.Env(), "DecTalk not started.\n" ).ThrowAsJavaScriptException();
  if( !value.IsNumber() )
    Napi::Error::New( info.Env(), "SetRate requires a number.\n" ).ThrowAsJavaScriptException();

  DWORD rate = value.As< Napi::Number >().Uint32Value();
  int status = TextToSpeechSetRate( ttsHandle, rate );

  if( status != MMSYSERR_NOERROR )
    Napi::Error::New( info.Env(), "SetRate failed with code " + std::to_string( status ) + "\n" ).ThrowAsJavaScriptException();
}

Napi::Value DecTalk::GetSpeaker( const Napi::CallbackInfo& info ) {
  if( ttsHandle == NULL )
    Napi::Error::New( info.Env(), "DecTalk not started.\n" ).ThrowAsJavaScriptException();
  DWORD speaker;
  int status = TextToSpeechGetSpeaker( ttsHandle, &speaker );

  if( status != MMSYSERR_NOERROR )
    Napi::Error::New( info.Env(), "GetSpeaker failed with code " + std::to_string( status ) + "\n" ).ThrowAsJavaScriptException();

  return Napi::Number::New( info.Env(), speaker );
}

void DecTalk::SetSpeaker( const Napi::CallbackInfo& info, const Napi::Value& value ) {
  if( ttsHandle == NULL )
    Napi::Error::New( info.Env(), "DecTalk not started.\n" ).ThrowAsJavaScriptException();
  if( !value.IsNumber() )
    Napi::Error::New( info.Env(), "SetSpeaker requires a number.\n" ).ThrowAsJavaScriptException();

  unsigned int speaker = value.As< Napi::Number >().Uint32Value();
  int status = TextToSpeechSetSpeaker( ttsHandle, speaker );

  if( status != MMSYSERR_NOERROR )
    Napi::Error::New( info.Env(), "SetSpeaker failed with code " + std::to_string( status ) + "\n" ).ThrowAsJavaScriptException();
}

Napi::Value DecTalk::GetLanguage( const Napi::CallbackInfo& info ) {
  if( ttsHandle == NULL )
    Napi::Error::New( info.Env(), "DecTalk not started.\n" ).ThrowAsJavaScriptException();
  DWORD language;
  int status = TextToSpeechGetLanguage( ttsHandle, &language );

  if( status != MMSYSERR_NOERROR )
    Napi::Error::New( info.Env(), "GetLanguage failed with code " + std::to_string( status ) + "\n" ).ThrowAsJavaScriptException();

  return Napi::Number::New( info.Env(), language );
}

void DecTalk::SetLanguage( const Napi::CallbackInfo& info, const Napi::Value& value ) {
  if( ttsHandle == NULL )
    Napi::Error::New( info.Env(), "DecTalk not started.\n" ).ThrowAsJavaScriptException();
  if( !value.IsNumber() )
    Napi::Error::New( info.Env(), "SetLanguage requires a number.\n" ).ThrowAsJavaScriptException();

  unsigned int language = value.As< Napi::Number >().Uint32Value();
  int status = TextToSpeechSetLanguage( ttsHandle, language );

  if( status != MMSYSERR_NOERROR )
    Napi::Error::New( info.Env(), "SetLanguage failed with code " + std::to_string( status ) + "\n" ).ThrowAsJavaScriptException();
}

Napi::Value DecTalk::GetInputCharacterCount( const Napi::CallbackInfo& info ) {
  if( ttsHandle == NULL )
    return Napi::Number::New( info.Env(), -1 );

  DWORD dwIdentifierArray [ 1 ] = { INPUT_CHARACTER_COUNT };
  DWORD dwStatusArray [ 1 ];
  int thing = TextToSpeechGetStatus( ttsHandle, dwIdentifierArray, dwStatusArray, 1 );

  if( thing != MMSYSERR_NOERROR )
    Napi::Error::New( info.Env(), "GetInputCharacterCount failed with code " + std::to_string( thing ) + "\n" ).ThrowAsJavaScriptException();

  return Napi::Number::New( info.Env(), dwStatusArray [ 0 ] );
}

Napi::Value DecTalk::GetIsSpeaking( const Napi::CallbackInfo& info ) {
  if( ttsHandle == NULL )
    return Napi::Number::New( info.Env(), -1 );

  DWORD dwIdentifierArray [ 1 ] = { STATUS_SPEAKING };
  DWORD dwStatusArray [ 1 ];
  int thing = TextToSpeechGetStatus( ttsHandle, dwIdentifierArray, dwStatusArray, 1 );

  if( thing != MMSYSERR_NOERROR )
    Napi::Error::New( info.Env(), "GetIsSpeaking failed with code " + std::to_string( thing ) + "\n" ).ThrowAsJavaScriptException();

  return Napi::Boolean::New( info.Env(), dwStatusArray [ 0 ] );
}

Napi::Value DecTalk::GetWaveOutDeviceID( const Napi::CallbackInfo& info ) {
  if( ttsHandle == NULL )
    return Napi::Number::New( info.Env(), -1 );

  DWORD dwIdentifierArray [ 1 ] = { WAVE_OUT_DEVICE_ID };
  DWORD dwStatusArray [ 1 ];
  int thing = TextToSpeechGetStatus( ttsHandle, dwIdentifierArray, dwStatusArray, 1 );

  if( thing != MMSYSERR_NOERROR )
    Napi::Error::New( info.Env(), "GetWaveOutDeviceID failed with code " + std::to_string( thing ) + "\n" ).ThrowAsJavaScriptException();

  return Napi::Number::New( info.Env(), dwStatusArray [ 0 ] );
}

void DecTalk::OpenWaveFileOut( const Napi::CallbackInfo& info ) {
  if( ttsHandle == NULL )
    Napi::Error::New( info.Env(), "DecTalk not started.\n" ).ThrowAsJavaScriptException();
  if( info.Length() < 1 || !info [ 0 ].IsString() )
    Napi::Error::New( info.Env(), "OpenWaveFileOut requires a string.\n" ).ThrowAsJavaScriptException();

  int encoding;
  if( info.Length() < 2 || !info [ 1 ].IsNumber() )
    encoding = 0;
  else
    encoding = info [ 1 ].As< Napi::Number >().Uint32Value();

  std::string fullwords = info [ 0 ].As< Napi::String >().Utf8Value();
  char* words = strdup( fullwords.c_str() );

  int status = TextToSpeechOpenWaveOutFile( ttsHandle, words, encoding );

  if( status != MMSYSERR_NOERROR )
    Napi::Error::New( info.Env(), "OpenWaveFileOut failed with code " + std::to_string( status ) + "\n" ).ThrowAsJavaScriptException();
}

void DecTalk::CloseWaveFileOut( const Napi::CallbackInfo& info ) {
  if( ttsHandle == NULL )
    Napi::Error::New( info.Env(), "DecTalk not started.\n" ).ThrowAsJavaScriptException();

  int status = TextToSpeechCloseWaveOutFile( ttsHandle );

  if( status != MMSYSERR_NOERROR )
    Napi::Error::New( info.Env(), "CloseWaveFileOut failed with code " + std::to_string( status ) + "\n" ).ThrowAsJavaScriptException();
}

void DecTalk::OpenLogFile( const Napi::CallbackInfo& info ) {
  if( ttsHandle == NULL )
    Napi::Error::New( info.Env(), "DecTalk not started.\n" ).ThrowAsJavaScriptException();
  if( info.Length() < 1 || !info [ 0 ].IsString() )
    Napi::Error::New( info.Env(), "OpenLogFile requires a string.\n" ).ThrowAsJavaScriptException();

  std::string fullwords = info [ 0 ].As< Napi::String >().Utf8Value();
  char* words = strdup( fullwords.c_str() );

  int flags;
  if( info.Length() < 2 || !info [ 1 ].IsNumber() )
    flags = 0;
  else
    flags = info [ 1 ].As< Napi::Number >().Uint32Value();

  int status = TextToSpeechOpenLogFile( ttsHandle, words, flags );

  if( status != MMSYSERR_NOERROR )
    Napi::Error::New( info.Env(), "OpenLogFile failed with code " + std::to_string( status ) + "\n" ).ThrowAsJavaScriptException();
}

void DecTalk::CloseLogFile( const Napi::CallbackInfo& info ) {
  if( ttsHandle == NULL )
    Napi::Error::New( info.Env(), "DecTalk not started.\n" ).ThrowAsJavaScriptException();
  int status = TextToSpeechCloseLogFile( ttsHandle );

  if( status != MMSYSERR_NOERROR )
    Napi::Error::New( info.Env(), "CloseLogFile failed with code " + std::to_string( status ) + "\n" ).ThrowAsJavaScriptException();
}

void DecTalk::OpenInMemory( const Napi::CallbackInfo& info ) {
  if( ttsHandle == NULL )
    Napi::Error::New( info.Env(), "DecTalk not started.\n" ).ThrowAsJavaScriptException();
  if( info.Length() < 1 || !info [ 0 ].IsNumber() )
    Napi::Error::New( info.Env(), "OpenInMemory requires a number.\n" ).ThrowAsJavaScriptException();

  // DWORD dwSize = info [ 0 ].As< Napi::Number >().Uint32Value();
  DWORD dwSize = WAVE_FORMAT_1M16;
  int status = TextToSpeechOpenInMemory( ttsHandle, dwSize );

  if( status != MMSYSERR_NOERROR )
    Napi::Error::New( info.Env(), "OpenInMemory failed with code " + std::to_string( status ) + "\n" ).ThrowAsJavaScriptException();
}

void DecTalk::CloseInMemory( const Napi::CallbackInfo& info ) {
  if( ttsHandle == NULL )
    return;

  int status = TextToSpeechCloseInMemory( ttsHandle );

  if( status != MMSYSERR_NOERROR )
    Napi::Error::New( info.Env(), "CloseInMemory failed with code " + std::to_string( status ) + "\n" ).ThrowAsJavaScriptException();
}

void DecTalk::AddBuffer( const Napi::CallbackInfo& info ) {
  if( ttsHandle == NULL )
    return;

  if( info.Length() < 1 || !info [ 0 ].IsObject() )
    Napi::Error::New( info.Env(), "AddBuffer requires a buffer.\n" ).ThrowAsJavaScriptException();

  Napi::Object buffer = info [ 0 ].As< Napi::Object >();
  TTSBufferTag* bufferTag = Napi::ObjectWrap< TTSBufferTag >::Unwrap( buffer );

  // int status = TextToSpeechAddBuffer( ttsHandle, &bufferTag->ttsBufferT );

  // if( status != MMSYSERR_NOERROR )
  // Napi::Error::New( info.Env(), "AddBuffer failed with code " + std::to_string( status ) + "\n" ).ThrowAsJavaScriptException();
}

Napi::Value DecTalk::ReturnBuffer( const Napi::CallbackInfo& info ) {
  if( ttsHandle == NULL )
    return Napi::Number::New( info.Env(), -1 );

  // if( info.Length() < 1 || !info [ 0 ].IsObject() )
  //   Napi::Error::New( info.Env(), "AddBuffer requires a buffer.\n" ).ThrowAsJavaScriptException();

  LPTTS_BUFFER_T wordsPtr;

  int thing = TextToSpeechReturnBuffer( ttsHandle, &wordsPtr );

  if( thing != MMSYSERR_NOERROR )
    Napi::Error::New( info.Env(), "ReturnBuffer failed with code " + std::to_string( thing ) + "\n" ).ThrowAsJavaScriptException();

  // return Napi::Number::New( info.Env(), dwStatusArray [ 0 ] );
  // return TTSBufferTag::FromStruct( info.Env(), *wordsPtr );
  return info.Env().Null();
}

Napi::Value DecTalk::GetCapabilities( const Napi::CallbackInfo& info ) {
  TTS_CAPS_T caps;
  int thing = TextToSpeechGetCaps( &caps );

  if( thing != MMSYSERR_NOERROR )
    Napi::Error::New( info.Env(), "GetCapabilities failed with code " + std::to_string( thing ) + "\n" ).ThrowAsJavaScriptException();

  return TTSCapsTag::FromStruct( info.Env(), caps );
}

void DecTalk::LoadUserDictionary( const Napi::CallbackInfo& info ) {
  if( info.Length() < 1 || !info [ 0 ].IsString() )
    Napi::Error::New( info.Env(), "LoadUserDictionary requires a string.\n" ).ThrowAsJavaScriptException();

  std::string fullwords = info [ 0 ].As< Napi::String >().Utf8Value();
  char* words = strdup( fullwords.c_str() );

  int status = TextToSpeechLoadUserDictionary( &ttsHandle, words );

  if( status != MMSYSERR_NOERROR )
    Napi::Error::New( info.Env(), "LoadUserDictionary failed with code " + std::to_string( status ) + "\n" ).ThrowAsJavaScriptException();
}

void DecTalk::UnloadUserDictionary( const Napi::CallbackInfo& info ) {
  int status = TextToSpeechUnloadUserDictionary( ttsHandle );

  if( status != MMSYSERR_NOERROR )
    Napi::Error::New( info.Env(), "UnloadUserDictionary failed with code " + std::to_string( status ) + "\n" ).ThrowAsJavaScriptException();
}