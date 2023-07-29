import bindings from 'bindings';
const addon = bindings( 'node-dectalk.node' );


export interface LanguageParams {
  language: number;
  languageAttributes: number;
}

export interface TTSCaps {
  numberOfLanguages: number;
  languageParams: LanguageParams[];
  sampleRate: number;
  minimumSpeakingRate: number;
  maximumSpeakingRate: number;
  numberOfPredefinedSpeakers: number;
  characterSet: number;
  /** The version of the DecTalk software. */
  version: number;
}
export enum MMSysError {
  /** no error */
  NOERROR = 0,
  /** unspecified error */
  ERROR = 1,
  /** device ID out of range */
  BADDEVICEID = 2,
  /** driver failed enable */
  NOTENABLED = 3,
  /** device already allocated */
  ALLOCATED = 4,
  /** device handle is invalid */
  INVALHANDLE = 5,
  /** no device driver present */
  NODRIVER = 6,
  /** memory allocation error */
  NOMEM = 7,
  /** function isn't supported */
  NOTSUPPORTED = 8,
  /** error value out of range */
  BADERRNUM = 9,
  /** invalid flag passed */
  INVALFLAG = 10,
  /** invalid parameter passed */
  INVALPARAM = 11,
  /** handle being used */
  HANDLEBUSY = 12,
  /** "Specified alias not found in WIN.INI */
  INVALIDALIAS = 13,
  /** last error in range */
  LASTERROR = 13,
};

/** defines for dwFormat field of WAVEINCAPS and WAVEOUTCAPS */
export enum WaveFormat {
  /** invalid format */
  InvalidFormat = 0x00000000,
  /** 11.025 kHz, Mono,   8-bit */
  Format1M08 = 0x00000001,
  /** 11.025 kHz, Stereo, 8-bit */
  Format1S08 = 0x00000002,
  /** 11.025 kHz, Mono,   16-bit */
  Format1M16 = 0x00000004,
  /** 11.025 kHz, Stereo, 16-bit */
  Format1S16 = 0x00000008,
  /** 22.05  kHz, Mono,   8-bit */
  Format2M08 = 0x00000010,
  /** 22.05  kHz, Stereo, 8-bit */
  Format2S08 = 0x00000020,
  /** 22.05  kHz, Mono,   16-bit */
  Format2M16 = 0x00000040,
  /** 22.05  kHz, Stereo, 16-bit */
  Format2S16 = 0x00000080,
  /** 44.1   kHz, Mono,   8-bit */
  Format4M08 = 0x00000100,
  /** 44.1   kHz, Stereo, 8-bit */
  Format4S08 = 0x00000200,
  /** 44.1   kHz, Mono,   16-bit */
  Format4M16 = 0x00000400,
  /** 44.1   kHz, Stereo, 16-bit */
  Format4S16 = 0x00000800,
  /** 8      kHz, Mono,   8-bit */
  Format08M08 = 0x00001000,
  /** 8      kHz, Mono,   16-bit */
  Format08M16 = 0x00002000,
  /** 8      kHz, Mono,   Mu-law */
  FormatMuLaw = 0x00000007,

}

export enum Speaker {
  Paul,
  Betty,
  Harry,
  Frank,
  Dennis,
  Kit,
  Ursula,
  Rita,
  Wendy
}

export enum DeviceManagement {
  OwnAudioDevice = 0x00000001,
  ReportOpenError = 0x00000002,
  // UseSAPI5AudioDevice = 0x40000000,
  DoNotUseAudioDevice = 0x80000000
}
export enum DeviceID {
  /** device ID for wave device mapper */
  Mapper = 4294967295,
  /** Open device as shareable */
  OpenShareable = 0x00000004
};

export class DecTalk extends addon.DecTalk {

  constructor () {
    super();
  }

  startup ( deviceID?: DeviceID | number, deviceManagement: DeviceManagement = DeviceManagement.OwnAudioDevice ): MMSysError {
    return super.startup( deviceID, deviceManagement );
  }

  shutdown (): MMSysError {
    return super.shutdown();
  }

  async speak ( text: string | string[], force: boolean = false ): Promise<MMSysError> {
    if ( typeof text !== "string" ) {
      text = text.join( " " );
    }
    return await super.speak( text, force );
  }

  speakSync ( text: string | string[], force: boolean = false ): MMSysError {
    if ( typeof text !== "string" ) {
      text = text.join( " " );
    }
    return super.speakSync( text, force );
  }

  async sync (): Promise<MMSysError> {
    return await super.sync();
  }

  syncSync (): MMSysError {
    return super.syncSync();
  }

  openWaveFileOut ( filename: string, format: WaveFormat ): MMSysError {
    return super.openWaveFileOut( filename, format );
  }

  closeWaveFileOut (): MMSysError {
    return super.closeWaveFileOut();
  }

  openLogFile ( filename: string ): MMSysError {
    return super.openLogFile( filename );
  }

  closeLogFile (): MMSysError {
    return super.closeLogFile();
  }

  pause (): MMSysError {
    return super.pause();
  }

  resume (): MMSysError {
    return super.resume();
  }

  reset (): MMSysError {
    return super.reset();
  }

  get sampleRate (): number {
    return super.getSampleRate();
  }

  set sampleRate ( value: number ) {
    super.setSampleRate( value );
  }

  get volume (): number {
    return super.getVolume();
  }

  set volume ( value: number ) {
    super.setVolume( value );
  }

  get attenuationVolume (): number {
    return super.getAttenuationVolume();
  }

  set attenuationVolume ( value: number ) {
    super.setAttenuationVolume( value );
  }

  get rate (): number {
    return super.getRate();
  }

  set rate ( value: number ) {
    super.setRate( value );
  }

  get speaker (): Speaker {
    return super.getSpeaker();
  }

  set speaker ( value: Speaker ) {
    super.setSpeaker( value );
  }

  get isSpeaking (): boolean {
    return super.isSpeaking;
  }

  get inputCharacterCount (): number {
    return super.inputCharacterCount;
  }

  get waveOutDeviceID (): number {
    return super.waveOutDeviceID;
  }

  get language () {
    return super.getLanguage();
  }

  set language ( value: number ) {
    super.setLanguage( value );
  }

  static getCapabilities (): TTSCaps {
    return super.getCapabilities();
  }

  loadUserDictionary ( filename: string ): MMSysError {
    return super.loadUserDictionary( filename );
  }

  unloadUserDictionary (): MMSysError {
    return super.unloadUserDictionary();
  }

}