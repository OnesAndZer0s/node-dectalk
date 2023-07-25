// #include <dtk/ttsapi.h>
// #include "build/headers/dtk/dtmmedefs.h"
// #include "build/headers/dtk/ttsapi.h"
// #include "dectalk/src/dapi/src/api/epsonapi.h"
// #include "dectalk/src/dapi/src/api/ttsapi.h"
// #include "dectalk/src/dapi/src/cmd/c.h"
// #include "lib/dectalk/dapi/src/api/epsonapi.h"

#include "dectalk/dist/include/dtk/ttsapi.h"

#include <napi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>

DWORD devEncoding [ 3 ] = {
    WAVE_FORMAT_1M16,
    WAVE_FORMAT_1M08,
    WAVE_FORMAT_08M08 };

LPTTS_HANDLE_T ttsHandle;

#define PROGRAM_NAME "WebSpeak"

class HelloAddon : public Napi::Addon< HelloAddon > {
  public:
    HelloAddon( Napi::Env env, Napi::Object exports ) {
      DefineAddon( exports, { InstanceMethod( "hello", &HelloAddon::Hello, napi_enumerable ) } );
    }

  private:
    Napi::Value Hello( const Napi::CallbackInfo& info ) {
      ttsHandle = NULL;
      unsigned int devNo = WAVE_MAPPER;
      int status;
      DWORD devOptions = DO_NOT_USE_AUDIO_DEVICE;
      DWORD encoding = 0;
      status = TextToSpeechStartup( &ttsHandle, devNo, devOptions, NULL, (long) NULL );

      switch( status ) {
        case MMSYSERR_NODRIVER:
          fprintf( stderr, PROGRAM_NAME ": Could not find any wave devices\n" );
          fprintf( stderr, PROGRAM_NAME ": Is the MM server ready? \n" );
          fprintf( stderr, PROGRAM_NAME ": Exiting\n" );
          exit( 1 );

        case MMSYSERR_NOTENABLED:
          fprintf( stderr, PROGRAM_NAME ": DECtalk licence not found.\n" );
          fprintf( stderr, PROGRAM_NAME ": Exiting\n" );
          exit( 1 );

        case MMSYSERR_ALLOCATED:
          fprintf( stderr, PROGRAM_NAME ": DECtalk has exceeded licence quota.\n" );
          fprintf( stderr, PROGRAM_NAME ": Exiting\n" );
          exit( 1 );

        case MMSYSERR_NOMEM:
          fprintf( stderr, PROGRAM_NAME ": DECtalk has ran out of memory.\n" );
          exit( 1 );

        case MMSYSERR_NOERROR:
          break;

        default:
          fprintf( stderr, PROGRAM_NAME ": TextToSpeechStartup failed with code %d, exiting.\n", status );
          exit( -1 );
      }

      char* device = const_cast< char* >( info [ 0 ].As< Napi::String >().Utf8Value().c_str() );

      fprintf( stderr, PROGRAM_NAME ": Opening up '%s' for writing...\n", device );
      TextToSpeechOpenWaveOutFile( ttsHandle, device, devEncoding [ encoding ] );

      char* words = const_cast< char* >( info [ 1 ].As< Napi::String >().Utf8Value().c_str() );
      fprintf( stderr, PROGRAM_NAME ": About to speak...\n" );
      TextToSpeechSpeak( ttsHandle, words, TTS_FORCE );

      fprintf( stderr, PROGRAM_NAME ": Waiting for synchronisation...\n" );
      TextToSpeechSync( ttsHandle );

      fprintf( stderr, PROGRAM_NAME ": Closing file.\n" );
      TextToSpeechCloseWaveOutFile( ttsHandle );

      fprintf( stderr, PROGRAM_NAME ": TextToSpeechShutdown failed.\n" );

      fprintf( stderr, PROGRAM_NAME ": Thanks for using DECtalk!\n" );

      return Napi::String::New( info.Env(), std::to_string( ERROR_IN_AUDIO_WRITE ) );
    }
};

NODE_API_ADDON( HelloAddon )