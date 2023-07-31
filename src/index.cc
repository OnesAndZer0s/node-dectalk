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

class DecTalkAddon : public Napi::Addon< DecTalkAddon > {
  public:
    DecTalkAddon( Napi::Env env, Napi::Object exports ) {
      DefineAddon( exports,
          {} );

      DecTalk::Init( env, exports );
      LanguageParamsTag::Init( env, exports );
      TTSCapsTag::Init( env, exports );
      TTSPhonemeTag::Init( env, exports );
      TTSIndexTag::Init( env, exports );
      TTSBufferTag::Init( env, exports );
    }
};

NODE_API_ADDON( DecTalkAddon )