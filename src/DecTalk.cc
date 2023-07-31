#include "src/DecTalk.h"

// #include "dectalk/src/dapi/src/api/ttsapi.h"
#include "src/LanguageParamsTag.h"
#include "src/TTSBufferTag.h"
#include "src/TTSCapsTag.h"
#include "src/TTSIndexTag.h"
#include "src/TTSPhonemeTag.h"

#include <cstdint>
#include <cstdio>
#include <dtmmedefs.h>
#include <functional>
#include <initializer_list>
#include <iostream>

// #include "AsyncTest.h" // NOLINT(build/include)
// #include "dectalk/dist/include/dtk/dtmmedefs.h"
// #include "dectalk/dist/include/dtk/ttsapi.h"
// #include "dectalk/src/dapi/src/api/ttsapi.h"

#include <napi.h>
#include <string>
#include <ttsapi.h>

std::vector< DecTalk* > DecTalk::ttsList = {};

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

              InstanceMethod( "openInMemory", &DecTalk::OpenInMemory ),
              InstanceMethod( "closeInMemory", &DecTalk::CloseInMemory ),
              InstanceMethod( "addBuffer", &DecTalk::AddBuffer ),
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

              StaticAccessor< &DecTalk::GetVersion >( "version" ),

          } );

  Napi::FunctionReference* constructor = new Napi::FunctionReference();
  *constructor = Napi::Persistent( func );
  env.SetInstanceData( constructor );

  exports.Set( "DecTalk", func );
  return exports;
}

DecTalk::DecTalk( const Napi::CallbackInfo& info ):
    Napi::ObjectWrap< DecTalk >( info ) {
  Napi::HandleScope scope( info.Env() );
}

Napi::Value DecTalk::Startup( const Napi::CallbackInfo& info ) {
  Napi::HandleScope scope( info.Env() );

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

  VOID( CALLBACK * callback )
  ( LONG, LONG, DWORD, UINT ) = []( LONG lParam1, LONG lParam2, DWORD cbParam, UINT uiMsg ) {
    auto shitballs = DecTalk::ttsList.at( cbParam );

    Napi::Value other;
    LPTTS_BUFFER_T bufPtr;
    switch( uiMsg ) {
      case TTS_MSG_STATUS:
        fprintf( stderr, ": TTS_MSG_STATUS \n" );
        break;
      case TTS_MSG_BUFFER:
        {
          bufPtr = (LPTTS_BUFFER_T) lParam2;

          // Napi::FunctionReference ref = DecTalk::cbs.at( cbParam );
          // new shit
          // unsigned long hm = (unsigned long) cbParam;
          // uintptr_t teehee = reinterpret_cast< uintptr_t >( hm );
          // HELP* what = reinterpret_cast< HELP* >( teehee );

          // Napi::FunctionReference shit = DecTalk::cbs [ 0 ];
          // shit.Call( {} );
          // shit.Value().Call( {} );
          // fprintf( stderr, "ASSBLASTER\n" );
          // other = TTSBufferTag::FromStruct( shitballs->Env(),bufPtr );
          // TTSBufferTag* bufferTag = Napi::ObjectWrap< TTSBufferTag >::Unwrap( buffer );

          // TextToSpeechAddBuffer( shitballs->ttsHandle, bufPtr );
        }
        break;
      // case TTS_MSG_INDEX_MARK:
      //   fprintf( stderr, PROGRAM_NAME ": TTS_MSG_INDEX_MARK \n" );
      //   break;
      // case TTS_MSG_VISUAL:
      //   fprintf( stderr, PROGRAM_NAME ": TTS_MSG_VISUAL \n" );
      //   break;
      default:
        fprintf( stderr, ": TTS_MSG_UNKNOWN \n" );
        break;
    }

    TTS_BUFFER_T captureMe = *bufPtr;
    auto callback = [ uiMsg, lParam2, captureMe ]( Napi::Env env, Napi::Function jsCallback ) {
      Napi::Value s;
      switch( uiMsg ) {
        case TTS_MSG_STATUS:
          fprintf( stderr, ": TTS_MSG_STATUS \n" );
          break;
        case TTS_MSG_BUFFER:
          {
            // LPTTS_BUFFER_T bufPtr = (LPTTS_BUFFER_T) lParam2;

            // Napi::FunctionReference ref = DecTalk::cbs.at( cbParam );
            // new shit
            // unsigned long hm = (unsigned long) cbParam;
            // uintptr_t teehee = reinterpret_cast< uintptr_t >( hm );
            // HELP* what = reinterpret_cast< HELP* >( teehee );

            // Napi::FunctionReference shit = DecTalk::cbs [ 0 ];
            // shit.Call( {} );
            // shit.Value().Call( {} );
            // fprintf( stderr, "ASSBLASTER\n" );
            // other = TTSBufferTag::FromStruct( shitballs->Env(),bufPtr );
            // TTSBufferTag* bufferTag = Napi::ObjectWrap< TTSBufferTag >::Unwrap( buffer );

            // fprintf( stderr, PROGRAM_NAME ": Callback called \n" );

            s = TTSBufferTag::constructor.New( {} );

            TTSBufferTag* ASD = Napi::ObjectWrap< TTSBufferTag >::Unwrap( s.ToObject() );

            ASD->ttsBufferT = captureMe;

            fprintf( stderr, "L\n" );
          }
          break;
        // case TTS_MSG_INDEX_MARK:
        //   fprintf( stderr, PROGRAM_NAME ": TTS_MSG_INDEX_MARK \n" );
        //   break;
        // case TTS_MSG_VISUAL:
        //   fprintf( stderr, PROGRAM_NAME ": TTS_MSG_VISUAL \n" );
        //   break;
        default:
          fprintf( stderr, ": TTS_MSG_UNKNOWN \n" );
          break;
      }

      jsCallback.Call( { Napi::Number::New( env, uiMsg ), s } );
    };

    shitballs->ttsCb.BlockingCall( callback );
    // shitballs->ttsCb.Release();
  };

  DWORD id = -1;

  if( info.Length() < 3 || !info [ 2 ].IsFunction() ) {
  } else {
    id = 0;
    Napi::Function func = info [ 2 ].As< Napi::Function >();

    ttsCb = Napi::ThreadSafeFunction::New( info.Env(), func, "Callback", 0, 1 );
    DecTalk::ttsList.push_back( this );
  }

  // get new instanceID

  // dtcb = Napi::Persistent( info [ 2 ].As< Napi::Function >() );

  // help.env = dtcb.Env();
  // help.ref = dtcb;

  // // size_t shit =

  // HELP* ret = &help;

  // dtcb.SuppressDestruct();

  // Napi::FunctionReference* hmmmmm = reinterpret_cast< Napi::FunctionReference* >( teehee );

  int retVal = TextToSpeechStartupEx( &ttsHandle, devNo, devOptions, callback, id );

  if( retVal == MMSYSERR_NOERROR ) {
    // set flag
    // retVal = TextToSpeechSetFlag( ttsHandle, flag );
  }

  return Napi::Number::New( info.Env(), retVal );
}

Napi::Value DecTalk::SpeakSync( const Napi::CallbackInfo& info ) {
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

  return Napi::Number::New( info.Env(), TextToSpeechSpeak( ttsHandle, words, force ) );
}

Napi::Value DecTalk::SyncSync( const Napi::CallbackInfo& info ) {
  return Napi::Number::New( info.Env(), TextToSpeechSync( ttsHandle ) );
}

Napi::Value DecTalk::Shutdown( const Napi::CallbackInfo& info ) {
  return Napi::Number::New( info.Env(), TextToSpeechShutdown( ttsHandle ) );
}

Napi::Value DecTalk::Pause( const Napi::CallbackInfo& info ) {
  return Napi::Number::New( info.Env(), TextToSpeechPause( ttsHandle ) );
}

Napi::Value DecTalk::Resume( const Napi::CallbackInfo& info ) {
  return Napi::Number::New( info.Env(), TextToSpeechResume( ttsHandle ) );
}

Napi::Value DecTalk::Reset( const Napi::CallbackInfo& info ) {
  // get bool
  bool res = false;
  if( info.Length() < 1 || !info [ 0 ].IsBoolean() )
    res = false;
  else
    res = info [ 0 ].As< Napi::Boolean >().Value();

  return Napi::Number::New( info.Env(), TextToSpeechReset( ttsHandle, res ) );
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
      status = TextToSpeechSpeak( ttsHandle, text, force );
    }

    void OnOK() {
      m_deferred.Resolve( Napi::Number::New( Env(), status ) );
    }

    void OnError( const Napi::Error& err ) { m_deferred.Reject( err.Value() ); }

  private:
    LPTTS_HANDLE_T ttsHandle;
    char* text;
    int status;
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
      status = TextToSpeechSync( ttsHandle );
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
    int status;
};

Napi::Value DecTalk::Speak( const Napi::CallbackInfo& info ) {
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
  SyncWorker* SyncWorker = new class SyncWorker( info.Env(), ttsHandle );
  SyncWorker->Queue();
  return SyncWorker->GetPromise();
}

Napi::Value DecTalk::GetSampleRate( const Napi::CallbackInfo& info ) {
  DWORD sampleRate;
  int status = TextToSpeechGetRate( ttsHandle, &sampleRate );

  if( status != MMSYSERR_NOERROR )
    Napi::Error::New( info.Env(), "GetSampleRate failed with code " + std::to_string( status ) + "\n" ).ThrowAsJavaScriptException();

  return Napi::Number::New( info.Env(), sampleRate );
}

void DecTalk::SetSampleRate( const Napi::CallbackInfo& info, const Napi::Value& value ) {
  if( !value.IsNumber() )
    Napi::Error::New( info.Env(), "SetSampleRate requires a number.\n" ).ThrowAsJavaScriptException();

  DWORD sampleRate = value.As< Napi::Number >().Uint32Value();
  int status = TextToSpeechSetRate( ttsHandle, sampleRate );

  if( status != MMSYSERR_NOERROR )
    Napi::Error::New( info.Env(), "SetSampleRate failed with code " + std::to_string( status ) + "\n" ).ThrowAsJavaScriptException();
}

Napi::Value DecTalk::GetVolume( const Napi::CallbackInfo& info ) {
  int volume;
  int status = TextToSpeechGetVolume( ttsHandle, VOLUME_MAIN, &volume );

  if( status != MMSYSERR_NOERROR )
    Napi::Error::New( info.Env(), "GetVolume failed with code " + std::to_string( status ) + "\n" ).ThrowAsJavaScriptException();

  return Napi::Number::New( info.Env(), volume );
}

void DecTalk::SetVolume( const Napi::CallbackInfo& info, const Napi::Value& value ) {
  if( !value.IsNumber() )
    Napi::Error::New( info.Env(), "SetVolume requires a number.\n" ).ThrowAsJavaScriptException();

  DWORD volume = value.As< Napi::Number >().Uint32Value();
  int status = TextToSpeechSetVolume( ttsHandle, VOLUME_MAIN, volume );

  if( status != MMSYSERR_NOERROR )
    Napi::Error::New( info.Env(), "SetVolume failed with code " + std::to_string( status ) + "\n" ).ThrowAsJavaScriptException();
}

Napi::Value DecTalk::GetAttenuationVolume( const Napi::CallbackInfo& info ) {
  int volume;
  int status = TextToSpeechGetVolume( ttsHandle, VOLUME_ATTENUATION, &volume );

  if( status != MMSYSERR_NOERROR )
    Napi::Error::New( info.Env(), "GetAttenuationVolume failed with code " + std::to_string( status ) + "\n" ).ThrowAsJavaScriptException();

  return Napi::Number::New( info.Env(), volume );
}

void DecTalk::SetAttenuationVolume( const Napi::CallbackInfo& info, const Napi::Value& value ) {
  if( !value.IsNumber() )
    Napi::Error::New( info.Env(), "SetAttenuationVolume requires a number.\n" ).ThrowAsJavaScriptException();

  DWORD volume = value.As< Napi::Number >().Uint32Value();
  int status = TextToSpeechSetVolume( ttsHandle, VOLUME_ATTENUATION, volume );

  if( status != MMSYSERR_NOERROR )
    Napi::Error::New( info.Env(), "SetAttenuationVolume failed with code " + std::to_string( status ) + "\n" ).ThrowAsJavaScriptException();
}

Napi::Value DecTalk::GetRate( const Napi::CallbackInfo& info ) {
  DWORD rate;
  int status = TextToSpeechGetRate( ttsHandle, &rate );

  if( status != MMSYSERR_NOERROR )
    Napi::Error::New( info.Env(), "GetRate failed with code " + std::to_string( status ) + "\n" ).ThrowAsJavaScriptException();

  return Napi::Number::New( info.Env(), rate );
}

void DecTalk::SetRate( const Napi::CallbackInfo& info, const Napi::Value& value ) {
  if( !value.IsNumber() )
    Napi::Error::New( info.Env(), "SetRate requires a number.\n" ).ThrowAsJavaScriptException();

  DWORD rate = value.As< Napi::Number >().Uint32Value();
  int status = TextToSpeechSetRate( ttsHandle, rate );

  if( status != MMSYSERR_NOERROR )
    Napi::Error::New( info.Env(), "SetRate failed with code " + std::to_string( status ) + "\n" ).ThrowAsJavaScriptException();
}

Napi::Value DecTalk::GetSpeaker( const Napi::CallbackInfo& info ) {
  DWORD speaker;
  int status = TextToSpeechGetSpeaker( ttsHandle, &speaker );

  if( status != MMSYSERR_NOERROR )
    Napi::Error::New( info.Env(), "GetSpeaker failed with code " + std::to_string( status ) + "\n" ).ThrowAsJavaScriptException();

  return Napi::Number::New( info.Env(), speaker );
}

void DecTalk::SetSpeaker( const Napi::CallbackInfo& info, const Napi::Value& value ) {
  if( !value.IsNumber() )
    Napi::Error::New( info.Env(), "SetSpeaker requires a number.\n" ).ThrowAsJavaScriptException();

  unsigned int speaker = value.As< Napi::Number >().Uint32Value();
  int status = TextToSpeechSetSpeaker( ttsHandle, speaker );

  if( status != MMSYSERR_NOERROR )
    Napi::Error::New( info.Env(), "SetSpeaker failed with code " + std::to_string( status ) + "\n" ).ThrowAsJavaScriptException();
}

Napi::Value DecTalk::GetLanguage( const Napi::CallbackInfo& info ) {
  DWORD language;
  int status = TextToSpeechGetLanguage( ttsHandle, &language );

  if( status != MMSYSERR_NOERROR )
    Napi::Error::New( info.Env(), "GetLanguage failed with code " + std::to_string( status ) + "\n" ).ThrowAsJavaScriptException();

  return Napi::Number::New( info.Env(), language );
}

void DecTalk::SetLanguage( const Napi::CallbackInfo& info, const Napi::Value& value ) {
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

Napi::Value DecTalk::OpenWaveFileOut( const Napi::CallbackInfo& info ) {
  if( info.Length() < 1 || !info [ 0 ].IsString() )
    Napi::Error::New( info.Env(), "OpenWaveFileOut requires a string.\n" ).ThrowAsJavaScriptException();

  int encoding;
  if( info.Length() < 2 || !info [ 1 ].IsNumber() )
    encoding = 0;
  else
    encoding = info [ 1 ].As< Napi::Number >().Uint32Value();

  std::string fullwords = info [ 0 ].As< Napi::String >().Utf8Value();
  char* words = strdup( fullwords.c_str() );

  return Napi::Number::New( info.Env(), TextToSpeechOpenWaveOutFile( ttsHandle, words, encoding ) );
}

Napi::Value DecTalk::CloseWaveFileOut( const Napi::CallbackInfo& info ) {
  return Napi::Number::New( info.Env(), TextToSpeechCloseWaveOutFile( ttsHandle ) );
}

Napi::Value DecTalk::OpenLogFile( const Napi::CallbackInfo& info ) {
  if( info.Length() < 1 || !info [ 0 ].IsString() )
    Napi::Error::New( info.Env(), "OpenLogFile requires a string.\n" ).ThrowAsJavaScriptException();

  std::string fullwords = info [ 0 ].As< Napi::String >().Utf8Value();
  char* words = strdup( fullwords.c_str() );

  int flags;
  if( info.Length() < 2 || !info [ 1 ].IsNumber() )
    flags = 0;
  else
    flags = info [ 1 ].As< Napi::Number >().Uint32Value();

  return Napi::Number::New( info.Env(), TextToSpeechOpenLogFile( ttsHandle, words, flags ) );
}

Napi::Value DecTalk::CloseLogFile( const Napi::CallbackInfo& info ) {
  return Napi::Number::New( info.Env(), TextToSpeechCloseLogFile( ttsHandle ) );
}

Napi::Value DecTalk::OpenInMemory( const Napi::CallbackInfo& info ) {
  if( info.Length() < 1 || !info [ 0 ].IsNumber() )
    Napi::Error::New( info.Env(), "OpenInMemory requires a number.\n" ).ThrowAsJavaScriptException();

  DWORD dwFormat;
  if( info.Length() < 2 || !info [ 1 ].IsNumber() )
    dwFormat = WAVE_FORMAT_1M16;
  else
    dwFormat = info [ 1 ].As< Napi::Number >().Uint32Value();
  return Napi::Number::New( info.Env(), TextToSpeechOpenInMemory( ttsHandle, dwFormat ) );
}

Napi::Value DecTalk::CloseInMemory( const Napi::CallbackInfo& info ) {
  return Napi::Number::New( info.Env(), TextToSpeechCloseInMemory( ttsHandle ) );
}

Napi::Value DecTalk::AddBuffer( const Napi::CallbackInfo& info ) {
  if( info.Length() < 1 || !info [ 0 ].IsObject() )
    Napi::Error::New( info.Env(), "AddBuffer requires a buffer.\n" ).ThrowAsJavaScriptException();

  Napi::Object buffer = info [ 0 ].As< Napi::Object >();
  TTSBufferTag* bufferTag = Napi::ObjectWrap< TTSBufferTag >::Unwrap( buffer );

  // LPTTS_BUFFER_T bs = (LPTTS_BUFFER_T) malloc( sizeof( TTS_BUFFER_T ) );

  // bs.dwBufferLength = 2048;
  // bs.dwMaximumBufferLength = 2048;

  // create buffer
  // bs->lpData = (LPSTR) malloc( sizeof( LPSTR ) * 8192 );
  // create phoneme array
  // bs->lpPhonemeArray = (LPTTS_PHONEME_T) malloc( sizeof( TTS_PHONEME_T ) * 256 );

  // create index array
  // bs->lpIndexArray = (LPTTS_INDEX_T) malloc( sizeof( TTS_INDEX_T ) * 256 );

  // set up buffer
  // bs.dwBufferLength = 0;
  // bs->dwMaximumBufferLength = 8192;
  // bs.dwNumberOfIndexMarks = 0;
  // bs.dwNumberOfPhonemeChanges = 0;
  // bs->dwMaximumNumberOfIndexMarks = 1;
  // bs->dwMaximumNumberOfPhonemeChanges = 256;

  // return Napi::Number::New( info.Env(), TextToSpeechAddBuffer( ttsHandle, &bufferTag->ttsBufferT ) );
  return Napi::Number::New( info.Env(), TextToSpeechAddBuffer( ttsHandle, &bufferTag->ttsBufferT ) );
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

Napi::Value DecTalk::LoadUserDictionary( const Napi::CallbackInfo& info ) {
  if( info.Length() < 1 || !info [ 0 ].IsString() )
    Napi::Error::New( info.Env(), "LoadUserDictionary requires a string.\n" ).ThrowAsJavaScriptException();

  std::string fullwords = info [ 0 ].As< Napi::String >().Utf8Value();
  char* words = strdup( fullwords.c_str() );

  return Napi::Number::New( info.Env(), TextToSpeechLoadUserDictionary( &ttsHandle, words ) );
}

Napi::Value DecTalk::UnloadUserDictionary( const Napi::CallbackInfo& info ) {
  return Napi::Number::New( info.Env(), TextToSpeechUnloadUserDictionary( ttsHandle ) );
}

Napi::Value DecTalk::GetVersion( const Napi::CallbackInfo& info ) {
  LPSTR v;
  TextToSpeechVersion( &v );
  return Napi::String::New( info.Env(), v );
}

// get PvdfParams
// typing
// control panel
// get last error
// tuning
// enumLangs
// setLang