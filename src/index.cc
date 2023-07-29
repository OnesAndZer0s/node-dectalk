// #include <dtk/ttsapi.h>
// #include "build/headers/dtk/dtmmedefs.h"
// #include "build/headers/dtk/ttsapi.h"
// #include "dectalk/src/dapi/src/api/epsonapi.h"
// #include "dectalk/src/dapi/src/api/ttsapi.h"
// #include "dectalk/src/dapi/src/cmd/c.h"
// #include "lib/dectalk/dapi/src/api/epsonapi.h"

// #include "build/headers/dtk/dtmmedefs.h"
// #include "dectalk/dist/include/dtk/ttsapi.h"
// #include "dectalk/src/dapi/src/api/ttsapi.h"
#include "src/DecTalk.h"
#include "src/LanguageParamsTag.h"
#include "src/TTSBufferTag.h"
#include "src/TTSCapsTag.h"
#include "src/TTSIndexTag.h"
#include "src/TTSPhonemeTag.h"

#include <napi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <ttsapi.h>

DWORD devEncoding [ 3 ] = {
    WAVE_FORMAT_1M16,
    WAVE_FORMAT_1M08,
    WAVE_FORMAT_08M08 };

LPTTS_HANDLE_T ttsHandle;

#define PROGRAM_NAME "WebSpeak"

class DecTalkAddon : public Napi::Addon< DecTalkAddon > {
  public:
    DecTalkAddon( Napi::Env env, Napi::Object exports ) {
      DefineAddon( exports,
          {
              // InstanceMethod( "hello", &DecTalkAddon::Hello, napi_enumerable ),
          } );

      DecTalk::Init( env, exports );
      LanguageParamsTag::Init( env, exports );
      TTSCapsTag::Init( env, exports );

      // literally cannot do anything with these yet
      // TTSPhonemeTag::Init( env, exports );
      // TTSIndexTag::Init( env, exports );
      // TTSBufferTag::Init( env, exports );
    }

  private:
    Napi::Value Hello( const Napi::CallbackInfo& info ) {
      ttsHandle = NULL;
      unsigned int devNo = WAVE_MAPPER;
      //   int status;
      DWORD devOptions = 0;
      // DWORD encoding = 0;
      // TextToSpeechSetLanguage( ttsHandle, );

      // setup callback

      VOID( CALLBACK * callback )
      ( LONG, LONG, DWORD, UINT ) = []( LONG lParam1, LONG lParam2, DWORD cbParam, UINT uiMsg ) {
        switch( uiMsg ) {
          case TTS_MSG_STATUS:
            fprintf( stderr, PROGRAM_NAME ": TTS_MSG_STATUS \n" );
            break;
          case TTS_MSG_BUFFER:
            {
              // fprintf( stderr, PROGRAM_NAME ": TTS_MSG_BUFFER \n" );
              // cast to pointer
              LPTTS_BUFFER_T bufPtr = (LPTTS_BUFFER_T) lParam2;
              // fprintf( stderr, PROGRAM_NAME ": Callback called \n" );
              TextToSpeechAddBuffer( ttsHandle, bufPtr );
            }
            break;
          case TTS_MSG_INDEX_MARK:
            fprintf( stderr, PROGRAM_NAME ": TTS_MSG_INDEX_MARK \n" );
            break;
          case TTS_MSG_VISUAL:
            fprintf( stderr, PROGRAM_NAME ": TTS_MSG_VISUAL \n" );
            break;
          default:
            fprintf( stderr, PROGRAM_NAME ": TTS_MSG_UNKNOWN \n" );
            break;
        }
        // fprintf( stderr, PROGRAM_NAME ": ERROR \n" );
        // cast to pointer
        // LPTTS_HANDLE_T bufPtr = (LPTTS_HANDLE_T) lparam;
        // fprintf( stderr, PROGRAM_NAME ": Callback called \n" );
      };

      int status = TextToSpeechStartup( &ttsHandle, devNo, devOptions, callback, DO_NOT_USE_AUDIO_DEVICE );
      if( status != MMSYSERR_NOERROR ) {
        fprintf( stderr, PROGRAM_NAME ": TextToSpeechStartup failed with code %d, exiting.\n", status );
        exit( -1 );
      }

      TTS_BUFFER_T bs = *(LPTTS_BUFFER_T) malloc( sizeof( TTS_BUFFER_T ) );

      // bs.dwBufferLength = 2048;
      // bs.dwMaximumBufferLength = 2048;

      // create buffer
      bs.lpData = (LPSTR) malloc( sizeof( LPSTR ) * 256 );

      // create phoneme array
      bs.lpPhonemeArray = (LPTTS_PHONEME_T) malloc( sizeof( TTS_PHONEME_T ) * 256 );

      // create index array
      bs.lpIndexArray = (LPTTS_INDEX_T) malloc( sizeof( TTS_INDEX_T ) * 256 );

      // set up buffer
      // bs.dwBufferLength = 0;
      bs.dwMaximumBufferLength = 256;
      // bs.dwNumberOfIndexMarks = 0;
      // bs.dwNumberOfPhonemeChanges = 0;
      bs.dwMaximumNumberOfIndexMarks = 1;
      bs.dwMaximumNumberOfPhonemeChanges = 256;

      // bs.lpData = NULL;
      // bs.lpPhonemeArray = NULL;
      // bs.lpIndexArray = NULL;
      // bs.dwReserved = 0;
      // bs.dwNumberOfPhonemeChanges = 2;
      // bs.dwMaximumNumberOfIndexMarks = 0;
      // bs.dwMaximumNumberOfPhonemeChanges = 0;
      // bs.dwNumberOfIndexMarks = 0;

      TextToSpeechOpenInMemory( ttsHandle, WAVE_FORMAT_1M16 );
      TextToSpeechAddBuffer( ttsHandle, &bs );

      LPSTR spk = const_cast< char* >( "macro hard" );

      TextToSpeechSpeak( ttsHandle, spk, TTS_NORMAL );

      TextToSpeechCloseInMemory( ttsHandle );
      // TextToSpeechSync( ttsHandle );

      return Napi::String::New( info.Env(), "Hello World!" );

      //   switch( status ) {
      //     case MMSYSERR_NODRIVER:
      //       fprintf( stderr, PROGRAM_NAME ": Could not find any wave devices\n" );
      //       fprintf( stderr, PROGRAM_NAME ": Is the MM server ready? \n" );
      //       fprintf( stderr, PROGRAM_NAME ": Exiting\n" );
      //       exit( 1 );

      //     case MMSYSERR_NOTENABLED:
      //       fprintf( stderr, PROGRAM_NAME ": DECtalk licence not found.\n" );
      //       fprintf( stderr, PROGRAM_NAME ": Exiting\n" );
      //       exit( 1 );

      //     case MMSYSERR_ALLOCATED:
      //       fprintf( stderr, PROGRAM_NAME ": DECtalk has exceeded licence quota.\n" );
      //       fprintf( stderr, PROGRAM_NAME ": Exiting\n" );
      //       exit( 1 );

      //     case MMSYSERR_NOMEM:
      //       fprintf( stderr, PROGRAM_NAME ": DECtalk has ran out of memory.\n" );
      //       exit( 1 );

      //     case MMSYSERR_NOERROR:
      //       break;

      //     default:
      //       fprintf( stderr, PROGRAM_NAME ": TextToSpeechStartup failed with code %d, exiting.\n", status );
      //       exit( -1 );
      //   }

      //   char* device = const_cast< char* >( info [ 0 ].As< Napi::String >().Utf8Value().c_str() );

      //   // fprintf( stderr, PROGRAM_NAME ": Opening up '%s' for writing...\n", device );
      //   // TextToSpeechOpenWaveOutFile( ttsHandle, device, devEncoding [ encoding ] );
      //   // TextToSpeechSetSpeaker( ttsHandle );
      //   std::string fullwords = info [ 1 ].As< Napi::String >().Utf8Value();

      //   fprintf( stderr, PROGRAM_NAME ": About to speak... %s\n", fullwords.c_str() );

      //   MMRESULT res = TextToSpeechSpeak( ttsHandle, const_cast< char* >( fullwords.c_str() ), TTS_FORCE );
      //   if( res != MMSYSERR_NOERROR ) {
      //     fprintf( stderr, PROGRAM_NAME ": TextToSpeechSpeak failed with code %d, exiting.\n", res );
      //     exit( -1 );
      //   }

      //   fprintf( stderr, PROGRAM_NAME ": Waiting for synchronisation...\n" );
      //   TextToSpeechSync( ttsHandle );

      //   // fprintf( stderr, PROGRAM_NAME ": Closing file.\n" );
      //   // TextToSpeechCloseWaveOutFile( ttsHandle );

      //   // fprintf( stderr, PROGRAM_NAME ": TextToSpeechShutdown failed.\n" );

      //   fprintf( stderr, PROGRAM_NAME ": Thanks for using DECtalk!\n" );

      //   return Napi::String::New( info.Env(), std::to_string( ERROR_IN_AUDIO_WRITE ) );
    }
};

NODE_API_ADDON( DecTalkAddon )