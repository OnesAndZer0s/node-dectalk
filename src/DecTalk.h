#pragma once

// #include "dectalk/dist/include/dtk/ttsapi.h"
// #include "dectalk/src/dapi/src/api/ttsapi.h"
#include "napi.h"

#include <ttsapi.h>

class DecTalk : public Napi::ObjectWrap< DecTalk > {
  public:
    static Napi::Object Init( Napi::Env env, Napi::Object exports );
    DecTalk( const Napi::CallbackInfo& info );

    LPTTS_HANDLE_T ttsHandle = NULL;

  private:
    Napi::Value Startup( const Napi::CallbackInfo& info );
    Napi::Value SpeakSync( const Napi::CallbackInfo& info );
    Napi::Value Speak( const Napi::CallbackInfo& info );

    Napi::Value SyncSync( const Napi::CallbackInfo& info );
    Napi::Value Sync( const Napi::CallbackInfo& info );

    Napi::Value Shutdown( const Napi::CallbackInfo& info );
    Napi::Value Pause( const Napi::CallbackInfo& info );
    Napi::Value Resume( const Napi::CallbackInfo& info );
    Napi::Value Reset( const Napi::CallbackInfo& info );

    Napi::Value GetSampleRate( const Napi::CallbackInfo& info );
    void SetSampleRate( const Napi::CallbackInfo& info, const Napi::Value& value );

    Napi::Value GetVolume( const Napi::CallbackInfo& info );
    void SetVolume( const Napi::CallbackInfo& info, const Napi::Value& value );

    Napi::Value GetAttenuationVolume( const Napi::CallbackInfo& info );
    void SetAttenuationVolume( const Napi::CallbackInfo& info, const Napi::Value& value );

    Napi::Value GetRate( const Napi::CallbackInfo& info );
    void SetRate( const Napi::CallbackInfo& info, const Napi::Value& value );

    Napi::Value GetSpeaker( const Napi::CallbackInfo& info );
    void SetSpeaker( const Napi::CallbackInfo& info, const Napi::Value& value );

    Napi::Value GetLanguage( const Napi::CallbackInfo& info );
    void SetLanguage( const Napi::CallbackInfo& info, const Napi::Value& value );

    Napi::Value GetInputCharacterCount( const Napi::CallbackInfo& info );
    Napi::Value GetIsSpeaking( const Napi::CallbackInfo& info );
    Napi::Value GetWaveOutDeviceID( const Napi::CallbackInfo& info );

    static Napi::Value GetCapabilities( const Napi::CallbackInfo& info );

    Napi::Value OpenWaveFileOut( const Napi::CallbackInfo& info );
    Napi::Value CloseWaveFileOut( const Napi::CallbackInfo& info );

    Napi::Value OpenLogFile( const Napi::CallbackInfo& info );
    Napi::Value CloseLogFile( const Napi::CallbackInfo& info );

    Napi::Value OpenInMemory( const Napi::CallbackInfo& info );
    Napi::Value CloseInMemory( const Napi::CallbackInfo& info );

    Napi::Value AddBuffer( const Napi::CallbackInfo& info );
    Napi::Value ReturnBuffer( const Napi::CallbackInfo& info );

    Napi::Value LoadUserDictionary( const Napi::CallbackInfo& info );
    Napi::Value UnloadUserDictionary( const Napi::CallbackInfo& info );

    // loaduserdictionary
    // unloaduerdictionary

    // void Open( const Napi::CallbackInfo& info );
    // void Close( const Napi::CallbackInfo& info );
    // Napi::Value IsOpen( const Napi::CallbackInfo& info );
    // void Write( Napi::Env env, const struct uhid_event* ev );

    // void Create( const Napi::CallbackInfo& info );
    // void Destroy( const Napi::CallbackInfo& info );
    // void Input( const Napi::CallbackInfo& info );
    // void GetReportReply( const Napi::CallbackInfo& info );
    // void SetReportReply( const Napi::CallbackInfo& info );

    // void On( const Napi::CallbackInfo& info );

    // Napi::Value GetEventEmitter( const Napi::CallbackInfo& info );
    // void SetEventEmitter( const Napi::CallbackInfo& info, const Napi::Value& value );

    // void Poll( const Napi::CallbackInfo& info );

    // Napi::FunctionReference eventEmitter;
};