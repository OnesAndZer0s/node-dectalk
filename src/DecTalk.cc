#include "src/DecTalk.h"

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
              InstanceMethod( "returnBuffer", &DecTalk::ReturnBuffer ),

              InstanceAccessor< &DecTalk::GetVolume, &DecTalk::SetVolume >( "volume" ),
              InstanceAccessor< &DecTalk::GetAttenuationVolume, &DecTalk::SetAttenuationVolume >( "attenuationVolume" ),
              InstanceAccessor< &DecTalk::GetSpeaker, &DecTalk::SetSpeaker >( "speaker" ),
              // InstanceAccessor< &DecTalk::GetLanguage, &DecTalk::SetLanguage >( "language" ),

              InstanceAccessor< &DecTalk::GetInputCharacterCount >( "inputCharacterCount" ),
              InstanceAccessor< &DecTalk::GetIsSpeaking >( "isSpeaking" ),
              InstanceAccessor< &DecTalk::GetWaveOutDeviceID >( "waveOutDeviceID" ),

              StaticAccessor< &DecTalk::GetVersion >( "version" ),

              InstanceMethod< &DecTalk::Typing >( "typing" ),
              // InstanceMethod< &DecTalk::GetPhVdefParams >( "getPhVdfParams" ),
              StaticMethod( "startLang", &DecTalk::StartLang ),
              StaticMethod( "selectLang", &DecTalk::SelectLang ),
              StaticMethod( "closeLang", &DecTalk::CloseLang ),
              StaticMethod( "enumLangs", &DecTalk::EnumLang ),

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
    auto ttsInstance = DecTalk::ttsList.at( cbParam );

    LPTTS_BUFFER_T bufPtr;
    TTS_BUFFER_T copiedBuf;

    switch( uiMsg ) {
      case TTS_MSG_STATUS:
        fprintf( stderr, "TTS_MSG_STATUS \n" );
        break;
      case TTS_MSG_BUFFER:
        {
          bufPtr = (LPTTS_BUFFER_T) lParam2;
          TextToSpeechAddBuffer( ttsInstance->ttsHandle, bufPtr );

          memcpy( &copiedBuf, bufPtr, sizeof( TTS_BUFFER_T ) );

          copiedBuf.lpData = (char*) malloc( copiedBuf.dwBufferLength );
          memcpy( copiedBuf.lpData, bufPtr->lpData, copiedBuf.dwBufferLength );

          copiedBuf.lpIndexArray = (LPTTS_INDEX_T) malloc( copiedBuf.dwMaximumNumberOfIndexMarks * sizeof( TTS_INDEX_T ) );
          memcpy( copiedBuf.lpIndexArray, bufPtr->lpIndexArray, copiedBuf.dwMaximumNumberOfIndexMarks * sizeof( TTS_INDEX_T ) );

          copiedBuf.lpPhonemeArray = (LPTTS_PHONEME_T) malloc( copiedBuf.dwMaximumNumberOfPhonemeChanges * sizeof( TTS_PHONEME_T ) );
          memcpy( copiedBuf.lpPhonemeArray, bufPtr->lpPhonemeArray, copiedBuf.dwMaximumNumberOfPhonemeChanges * sizeof( TTS_PHONEME_T ) );
        }
        break;
      case TTS_MSG_INDEX_MARK:
        fprintf( stderr, "TTS_MSG_INDEX_MARK \n" );
        break;
      case TTS_MSG_VISUAL:
        fprintf( stderr, "TTS_MSG_VISUAL \n" );
        break;
      default:
        fprintf( stderr, "TTS_MSG_UNKNOWN \n" );
        break;
    }

    if( uiMsg == TTS_MSG_BUFFER )
      return;
    // if the buffer is not copied, the callback will just call the pointers to nothing :)

    auto callback = [ uiMsg, copiedBuf ]( Napi::Env env, Napi::Function jsCallback ) {
      Napi::Value retVal;
      switch( uiMsg ) {
        case TTS_MSG_STATUS:
          fprintf( stderr, ": TTS_MSG_STATUS \n" );
          break;
        case TTS_MSG_BUFFER:
          {
            retVal = TTSBufferTag::constructor.New( {} );

            TTSBufferTag* newBuf = Napi::ObjectWrap< TTSBufferTag >::Unwrap( retVal.ToObject() );

            newBuf->ttsBufferT = copiedBuf;
          }
          break;
        case TTS_MSG_INDEX_MARK:
          fprintf( stderr, "TTS_MSG_INDEX_MARK \n" );
          break;
        case TTS_MSG_VISUAL:
          fprintf( stderr, "TTS_MSG_VISUAL \n" );
          break;
        default:
          fprintf( stderr, ": TTS_MSG_UNKNOWN \n" );
          break;
      }

      jsCallback.Call( { Napi::Number::New( env, uiMsg ), retVal } );
    };

    ttsInstance->ttsCb.BlockingCall( callback );
    ttsInstance->ttsCb.Release();
  };

  DWORD id = -1;

  if( info.Length() >= 3 && info [ 2 ].IsFunction() ) {
    id = 0; // TODO make this not hardcoded
    Napi::Function func = info [ 2 ].As< Napi::Function >();

    ttsCb = Napi::ThreadSafeFunction::New( info.Env(), func, "Callback", 0, 1 );
    DecTalk::ttsList.push_back( this );
  } else callback = NULL;

  return Napi::Number::New( info.Env(), TextToSpeechStartupEx( &ttsHandle, devNo, devOptions, callback, id ) );
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

// Napi::Value DecTalk::GetLanguage( const Napi::CallbackInfo& info ) {
//   DWORD language;
//   int status = TextToSpeechGetLanguage( ttsHandle, &language );

//   if( status != MMSYSERR_NOERROR )
//     Napi::Error::New( info.Env(), "GetLanguage failed with code " + std::to_string( status ) + "\n" ).ThrowAsJavaScriptException();

//   return Napi::Number::New( info.Env(), language );
// }

// void DecTalk::SetLanguage( const Napi::CallbackInfo& info, const Napi::Value& value ) {
//   if( !value.IsNumber() )
//     Napi::Error::New( info.Env(), "SetLanguage requires a number.\n" ).ThrowAsJavaScriptException();

//   unsigned int language = value.As< Napi::Number >().Uint32Value();
//   int status = TextToSpeechSetLanguage( ttsHandle, language );

//   if( status != MMSYSERR_NOERROR )
//     Napi::Error::New( info.Env(), "SetLanguage failed with code " + std::to_string( status ) + "\n" ).ThrowAsJavaScriptException();
// }

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

  return Napi::Number::New( info.Env(), TextToSpeechAddBuffer( ttsHandle, &bufferTag->ttsBufferT ) );
}

Napi::Value DecTalk::ReturnBuffer( const Napi::CallbackInfo& info ) {
  LPTTS_BUFFER_T wordsPtr;

  int thing = TextToSpeechReturnBuffer( ttsHandle, &wordsPtr );

  if( thing != MMSYSERR_NOERROR )
    Napi::Error::New( info.Env(), "ReturnBuffer failed with code " + std::to_string( thing ) + "\n" ).ThrowAsJavaScriptException();

  Napi::Value retVal = TTSBufferTag::constructor.New( {} );
  TTSBufferTag* ttsBuf = Napi::ObjectWrap< TTSBufferTag >::Unwrap( retVal.ToObject() );
  ttsBuf->ttsBufferT = *wordsPtr;
  return retVal;
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

  return Napi::Number::New( info.Env(), TextToSpeechLoadUserDictionary( ttsHandle, words ) );
}

Napi::Value DecTalk::UnloadUserDictionary( const Napi::CallbackInfo& info ) {
  return Napi::Number::New( info.Env(), TextToSpeechUnloadUserDictionary( ttsHandle ) );
}

Napi::Value DecTalk::GetVersion( const Napi::CallbackInfo& info ) {
  LPVERSION_INFO v;
  LPSTR vS;
  DWORD ver = TextToSpeechVersion( &vS );

  TextToSpeechVersionEx( &v );
  // get bits 31-24 of ver
  int DecTalkMajor = ( ver & 0xFF000000 ) >> 24;
  // get bits 23-16 of ver
  int DecTalkMinor = ( ver & 0x00FF0000 ) >> 16;

  int DAPIMajor = ( ver & 0x0000FF00 ) >> 8;

  int DAPIMinor = ( ver & 0x000000FF );

  Napi::Object retVal = Napi::Object::New( info.Env() );
  retVal.Set( "dllVersion", v->DLLVersion );
  retVal.Set( "dTalkVersion", v->DTalkVersion );
  retVal.Set( "structVersion", v->StructVersion );
  retVal.Set( "language", v->Language );
  retVal.Set( "version", v->VerString );
  retVal.Set( "versionString", Napi::String::New( info.Env(), vS ) );
  retVal.Set( "dtMajor", Napi::Number::New( info.Env(), DecTalkMajor ) );
  retVal.Set( "dtMinor", Napi::Number::New( info.Env(), DecTalkMinor ) );
  retVal.Set( "dapiMajor", Napi::Number::New( info.Env(), DAPIMajor ) );
  retVal.Set( "dapiMinor", Napi::Number::New( info.Env(), DAPIMinor ) );

  return retVal;
}

void DecTalk::Typing( const Napi::CallbackInfo& info ) {
  if( info.Length() < 1 || !info [ 0 ].IsString() )
    Napi::Error::New( info.Env(), "Typing requires a string.\n" ).ThrowAsJavaScriptException();

  std::string fullwords = info [ 0 ].As< Napi::String >().Utf8Value();
  unsigned char word = fullwords.c_str() [ 0 ];
  TextToSpeechTyping( ttsHandle, word );
}

Napi::Value DecTalk::GetPhVdefParams( const Napi::CallbackInfo& info ) {
  if( info.Length() < 1 || !info [ 0 ].IsNumber() )
    Napi::Error::New( info.Env(), "GetPvdfParams requires a number.\n" ).ThrowAsJavaScriptException();

  UINT voice = info [ 0 ].As< Napi::Number >().Uint32Value();
  short* thing = TextToSpeechGetPhVdefParams( ttsHandle, voice );

  if( thing != MMSYSERR_NOERROR )
    Napi::Error::New( info.Env(), "GetPvdfParams failed with code " + std::to_string( *thing ) + "\n" ).ThrowAsJavaScriptException();
  return Napi::Number::New( info.Env(), *thing );
}

Napi::Value DecTalk::StartLang( const Napi::CallbackInfo& info ) {
  if( info.Length() < 1 || !info [ 0 ].IsString() )
    Napi::Error::New( info.Env(), "StartLang requires a string.\n" ).ThrowAsJavaScriptException();

  std::string language = info [ 0 ].As< Napi::String >().Utf8Value();
  char* unconst = strdup( language.c_str() );
  unsigned int thing = TextToSpeechStartLang( unconst );

  return Napi::Number::New( info.Env(), thing );
}

Napi::Value DecTalk::SelectLang( const Napi::CallbackInfo& info ) {
  if( info.Length() < 1 || !info [ 0 ].IsNumber() )
    Napi::Error::New( info.Env(), "SelectLang requires a number.\n" ).ThrowAsJavaScriptException();

  unsigned int language = info [ 0 ].As< Napi::Number >().Uint32Value();

  BOOL active = TextToSpeechSelectLang( NULL, language );

  return Napi::Boolean::New( info.Env(), active );
}

Napi::Value DecTalk::CloseLang( const Napi::CallbackInfo& info ) {
  if( info.Length() < 1 || !info [ 0 ].IsString() )
    Napi::Error::New( info.Env(), "CloseLang requires a string.\n" ).ThrowAsJavaScriptException();

  std::string language = info [ 0 ].As< Napi::String >().Utf8Value();
  char* unconst = strdup( language.c_str() );
  BOOL active = TextToSpeechCloseLang( unconst );

  return Napi::Boolean::New( info.Env(), active );
}

Napi::Value DecTalk::EnumLang( const Napi::CallbackInfo& info ) {
  LPLANG_ENUM language = (LPLANG_ENUM) malloc( sizeof( LANG_ENUM ) );
  DWORD sz = TextToSpeechEnumLangs( &language );

  if( sz == 0 ) return Napi::Number::New( info.Env(), 0 );

  Napi::Object retVal = Napi::Object::New( info.Env() );
  retVal.Set( "multiLang", Napi::Boolean::New( info.Env(), language->MultiLang ) );
  Napi::Array langArray = Napi::Array::New( info.Env(), language->Languages );
  for( int i = 0; i < language->Languages; i++ ) {
    Napi::Object langObj = Napi::Object::New( info.Env() );
    langObj.Set( "code", language->Entries [ i ].lang_code );
    langObj.Set( "name", language->Entries [ i ].lang_name );
    langArray.Set( i, langObj );
  }
  retVal.Set( "languages", langArray );
  return retVal;
}