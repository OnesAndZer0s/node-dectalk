import bindings from 'bindings';
const addon = bindings( 'node-dectalk.node' );

export type TTSCallback = ( msg: Message, param: any ) => void;

export interface LanguageParams {
  readonly language: number;
  readonly languageAttributes: number;
}

export interface TTSPhoneme {
  readonly phoneme: number;
  readonly duration: number;
  readonly sampleNumber: number;
}

export interface TTSIndex {
  readonly index: number;
  readonly sampleNumber: number;
}

export enum Message {
  Buffer = 9,
  IndexMark = 1,
  Status = 2,
  Visual = 3
}
export interface TTSCaps {
  readonly numberOfLanguages: number;
  readonly languageParams: LanguageParams[];
  readonly sampleRate: number;
  readonly minimumSpeakingRate: number;
  readonly maximumSpeakingRate: number;
  readonly numberOfPredefinedSpeakers: number;
  readonly characterSet: number;
  readonly version: number;
}

export enum LogType {
  /** Log text input. */
  Text = 0x0001,
  /** Log phonemes to host */
  Phonemes = 0x0002,
  /** Log name types to console */
  NameTypes = 0x0004,
  /** Log name form classes to console */
  FormTypes = 0x0008,
  /** Log name syllable structure */
  Syllables = 0x0010,
  /** Log phones out  with dur and f0 */
  OutPhones = 0x0020,
  /** Log debug information in file dbglog.txt */
  DbgLog = 0x0040,
}

export enum MMSysError {
  /** No error */
  NoError = 0,
  /** Unspecified error */
  Error = 1,
  /** Device ID out of range */
  BadDeviceID = 2,
  /** Driver failed enable */
  NotEnabled = 3,
  /** Device already allocated */
  Allocated = 4,
  /** Device handle is invalid */
  InvalHandle = 5,
  /** No device driver present */
  NoDriver = 6,
  /** Memory allocation error */
  NoMem = 7,
  /** Function isn't supported */
  NotSupported = 8,
  /** Error value out of range */
  BadErrNum = 9,
  /** Invalid flag passed */
  InvalFlag = 10,
  /** Invalid parameter passed */
  InvalParam = 11,
  /** Handle being used */
  HandleBusy = 12,
  /** "Specified alias not found in WIN.INI */
  InvalidAlias = 13,
  /** Last error in range */
  LastError = 13,
};

/** Defines for dwFormat field of WAVEINCAPS and WAVEOUTCAPS */
export enum WaveFormat {
  /** Invalid format */
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

/**
 * The DECtalk Text-To-Speech system supports the following predefined speaking voices.
 */
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
  /** Device ID for wave device mapper */
  Mapper = 4294967295,
  /** Open device as shareable */
  OpenShareable = 0x00000004
};

/**
 * The main class for the DECtalk Text-To-Speech system.
 */
export class DecTalk extends addon.DecTalk {

  /**
   * Create a new instance of the DECtalk Text-To-Speech system.
   */
  constructor () {
    super();
  }

  /**
   * Initializes the text-to-speech system; defines the callback routine; and loads the main and user pronunciation dictionaries.  
   * @param {(DeviceID | number)} [deviceID] - Wave out device ID number. `WaveMapper` may be used here if the device ID number is unknown.
   * @param {DeviceManagement} [deviceManagement=DeviceManagement.OwnAudioDevice] - Specifies how the wave output device is managed.
   * @return {MMSysError} This value is zero if initialization was successful. The return value will be one of the following constants:  
   * - {@link MMSysError.NoError | NoError} - Normal successful completion (zero).
   * - {@link MMSysError.NoDriver | NoDriver} - No wave out device driver present.
   * - {@link MMSysError.BadDeviceID | BadDeviceID} - Device ID out of range.
   * - {@link MMSysError.NoMem | NoMem} - Unable to allocate memory.
   * - {@link MMSysError.Error | Error} - Dictionary not found.
   * - {@link MMSysError.InvalParam | InvalParam} - Invalid param for the load dictionary.
   * @comment If the callback procedure is defined, then the calling application will be called via the callback routine when a buffer is filled while in speech-to-memory mode, an error occurs, or an index mark is encountered.  <br/>  
   * The default parameters are:  <br/>  
   * * Language: American English.
   * * Speaking rate: 200 words per minute.
   * * Speaker: Paul.
   * @see {@link shutdown}
   * @see {@link openInMemory}
   * @see {@link openLogFile}
   * @see {@link openWaveFile}
   * @see {@link speak}
   */
  startup ( deviceID?: DeviceID | number, deviceManagement: DeviceManagement = DeviceManagement.OwnAudioDevice, cb?: TTSCallback ): MMSysError {
    return super.startup( deviceID, deviceManagement, cb );
  }
  /**
   * Shuts down the text-to-speech system and frees all system resources used by the text-to-speech system.
   * @returns {MMSysError} This value is zero if shutdown was successful. The return value will be one of the following constants:  
   * - {@link MMSysError.NoError | NoError} - Normal successful completion (zero).
   * - {@link MMSysError.InvalHandle | InvalHandle} - The Text-To-Speech handle is invalid.
   * @comment This call is called when you close an application. Any user-defined dictionaries, which were previously loaded, are automatically unloaded. All previously queued text is discarded and the text-to-speech system will immediately stop speaking.  
   * @see {@link startup}
   */
  shutdown (): MMSysError {
    return super.shutdown();
  }

  /**
   * Qqueues to the text-to-speech system. While in startup state, speech samples are routed to the audio device or ignored, depending on whether the {@link DeviceManagement.DoNotUseAudioDevice | DoNotUseAudioDevice} flag is set in the `deviceOptions` parameter of the startup function. If the text-to-speech system is in one of its special modes (wave-file, log-file, or speech-to-memory modes), the speech samples are handled accordingly.  
   * @async
   * @param { ( string | string[] ) } text - The text to be spoken.
   * @param { boolean } [ force = false ] - Specifies if the text is to be pushed through the Text-To-Speech system even if it is not on a clause boundary.
   * @return  {Promise<MMSysError>} The value will be zero if the function is successful. The return value will be one of the following constants: 
   * - {@link MMSysError.NoError | NoError} - Normal successful completion (zero).  <br/>  
   * - {@link MMSysError.NoMem | NoMem} - Unable to allocate memory.  <br/>  
   * - {@link MMSysError.InvalHandle | InvalHandle} - The Text-To-Speech handle is invalid.  <br/>  
   * @comment The speaker, speaking rate, and volume can also be changed in the text string by inserting in-line commands as shown in the following example:  <br/>  
   * `[:name paul] I am Paul. [:nb] I am Betty. [:volume set 50] The volume has been set to 50% of the maximum level. [:ra 120] I am speaking at 120 words per minute.`  
   * @see {@link openInMemory}
   * @see {@link openLogFile}
   * @see {@link openWaveFile}
   * @see {@link startup}
   */
  async speak ( text: string | string[], force: boolean = false ): Promise<MMSysError> {
    if ( typeof text !== "string" ) {
      text = text.join( " " );
    }
    return await super.speak( text, force );
  }

  /**
   * Qqueues to the text-to-speech system. While in startup state, speech samples are routed to the audio device or ignored, depending on whether the {@link DeviceManagement.DoNotUseAudioDevice | DoNotUseAudioDevice} flag is set in the `deviceOptions` parameter of the startup function. If the text-to-speech system is in one of its special modes (wave-file, log-file, or speech-to-memory modes), the speech samples are handled accordingly.  
   * @param { ( string | string[] ) } text - The text to be spoken.
   * @param { boolean } [ force = false ] - Specifies if the text is to be pushed through the Text-To-Speech system even if it is not on a clause boundary.
   * @return  {MMSysError} The value will be zero if the function is successful. The return value will be one of the following constants: 
   * - {@link MMSysError.NoError | NoError} - Normal successful completion (zero).  <br/>  
   * - {@link MMSysError.NoMem | NoMem} - Unable to allocate memory.  <br/>  
   * - {@link MMSysError.InvalHandle | InvalHandle} - The Text-To-Speech handle is invalid.  <br/>  
   * @comment The speaker, speaking rate, and volume can also be changed in the text string by inserting in-line commands as shown in the following example:  <br/>  
   * `[:name paul] I am Paul. [:nb] I am Betty. [:volume set 50] The volume has been set to 50% of the maximum level. [:ra 120] I am speaking at 120 words per minute.`  
   * @see {@link openInMemory}
   * @see {@link openLogFile}
   * @see {@link openWaveFile}
   * @see {@link startup}
   */
  speakSync ( text: string | string[], force: boolean = false ): MMSysError {
    if ( typeof text !== "string" ) {
      text = text.join( " " );
    }
    return super.speakSync( text, force );
  }

  /**
   * Will block until all previously queued text has been spoken. This function will automatically resume audio if the Text - To - Speech system has been paused by the {@link pause()} function.  
   * @async
   * @return {Promise<MMSysError>} The value will be zero if the function is successful. The return value will be one of the following constants:
   * - {@link MMSysError.NoError | NoError} - Normal successful completion (zero).  <br/>  
   * - {@link MMSysError.Error | Error} - Unable to complete queued text.  <br/>  
   * - {@link MMSysError.InvalHandle | InvalHandle} - The Text-To-Speech handle is invalid.  <br/>  
   * @comment This call automatically resumes audio output if the text-to-speech system is in a paused state by a previously issued {@link pause()} call.  
   * @see {@link pause}
   */
  async sync (): Promise<MMSysError> {
    return await super.sync();
  }
  /**
   * Will block until all previously queued text has been spoken. This function will automatically resume audio if the Text-To-Speech system has been paused by the {@link pause()} function.  
   * @return {MMSysError} The value will be zero if the function is successful. The return value will be one of the following constants:
   * - {@link MMSysError.NoError | NoError} - Normal successful completion (zero).  <br/>  
   * - {@link MMSysError.Error | Error} - Unable to complete queued text.  <br/>  
   * - {@link MMSysError.InvalHandle | InvalHandle} - The Text-To-Speech handle is invalid.  <br/>  
   * @comment This call automatically resumes audio output if the text-to-speech system is in a paused state by a previously issued {@link pause()} call.  
   * @see {@link pause}
   */
  syncSync (): MMSysError {
    return super.syncSync();
  }

  /**
   * Causes the specified wave file to be opened and the text-to-speech system to enter into wave-file mode. This mode indicates that the speech samples are to be written in wave format into the wave file each time {@link speak()} is called. The text-to-speech system remains in the wave-file mode until {@link closeWaveFile()} is called.  
   * @param {string} filename - The name of the wave file to be created.
   * @param {WaveFormat} format - Determines one or more of the wave file audio sample format.
   * @return {MMSysError} The value will be zero if the function is successful. The return value will be one of the following constants:
   * - {@link MMSysError.NoError | NoError} - Normal successful completion (zero).  <br/>  
   * - {@link MMSysError.InvalParam | InvalParam} - An invalid parameter or an illegal wave output format was passed.  <br/>  
   * - {@link MMSysError.NoMem | NoMem} - Memory allocation error.  <br/>  
   * - {@link MMSysError.Allocated | Allocated} - A wave file is already open.  <br/>  
   * - {@link MMSysError.Error | Error} - Unable to open the wave file or unable to write to the wave file.  <br/>  
   * - {@link MMSysError.InvalHandle | InvalHandle} - The Text-To-Speech handle is invalid.  <br/>  
   * @comment This call automatically resumes audio output if the text-to-speech system is in a paused state by a previously issued {@link pause()} call. <br/>  
   * The startup function must be called to start the text-to-speech system before calling {@link openWaveFile()}.
   * @see {@link closeWaveFile}
   * @see {@link pause}
   * @see {@link reset}
   * @see {@link speak}
   * @see {@link startup}
   */
  openWaveFile ( filename: string, format: WaveFormat ): MMSysError {
    return super.openWaveFileOut( filename, format );
  }

  /**
   * Close the Text-To-Speech Wave File.  
   * @return {MMSysError} The value will be zero if the function is successful. The return value will be one of the following constants:
   * - {@link MMSysError.NoError | NoError} - Normal successful completion (zero).  <br/>  
   * - {@link MMSysError.Error | Error} - Failure to wait for pending speech, unable to update wave file header, or unable to close the wave file.  <br/>  
   * - {@link MMSysError.InvalHandle | InvalHandle} - The Text-To-Speech handle is invalid.  <br/>  
   * @comment The application must call {@link openWaveFile()} before calling {@link closeWaveFile()}.
   * @see {@link openWaveFile}
   */
  closeWaveFile (): MMSysError {
    return super.closeWaveFileOut();
  }


  /**
   * Causes the specified log file to be opened and the text-to-speech sytem to enter into the log-file mode. This mode indicates that the speech samples are to be written as text, phonemes, or syllables into the log file each time {@link speak()} is called. The phonemes and syllables are written using the arpabet alphabet. The text-to-speech system remains in the log-file mode until {@link closeLogFile()} is called.  
   * @param {string} filename - The name of the log file to be created.  
   * @param {LogType=} [logType] - Specifies one or more of the type of output.  
   * @return {MMSysError} The value will be zero if the function is successful. The return value will be one of the following constants:
   * - {@link MMSysError.NoError | NoError} - Normal successful completion (zero).  <br/>  
   * - {@link MMSysError.InvalParam | InvalParam} - An invalid parameter was passed.  <br/>  
   * - {@link MMSysError.NoMem | NoMem} - Unable to allocate memory.  <br/>  
   * - {@link MMSysError.Allocated | Allocated} - A log file is already open.  <br/>  
   * - {@link MMSysError.Error | Error} - Unable to open the output file.  <br/>  
   * - {@link MMSysError.InvalHandle | InvalHandle} - The Text-To-Speech handle is invalid.  <br/>  
   * @comment If more than one of the dwFlags are passed, then the logged output is mixed in an unpredictable fashion. If there is already a log file open, this call returns an error. The Log command has no effect when a log file is already open. <br/>  
   * The startup function must be called to start the text-to-speech system before calling this function. <br/>  
   * {@link openLogFile()} automatically resumes audio output if the text-to-speech system is in a paused state by a previously issued {@link pause()} call.
   * @see {@link closeLogFile}
   * @see {@link pause}
   * @see {@link reset}
   * @see {@link speak}
   * @see {@link startup}
   */
  openLogFile ( filename: string, logType?: LogType ): MMSysError {
    return super.openLogFile( filename, logType );
  }

  /**
   * Closes the log file opened by the {@link openLogFile()} function.  
   * @return {MMSysError} The value will be zero if the function is successful. The return value will be one of the following constants:
   * - {@link MMSysError.NoError | NoError} - Normal successful completion (zero).  <br/>  
   * - {@link MMSysError.Error | Error} - Failure to wait for pending speech, unable to close the output file, or no output file is open.  <br/>  
   * - {@link MMSysError.InvalHandle | InvalHandle} - The Text-To-Speech handle is invalid.  <br/>  
   * @comment This call closes an open log file, even if it was opened with the Log in-line command. <br/>  
   * The application must call {@link openLogFile()} before calling {@link closeLogFile()}.  
   * @see {@link openLogFile}
   */
  closeLogFile (): MMSysError {
    return super.closeLogFile();
  }

  /**
   * Pauses text-to-speech audio output.  
   * @return {MMSysError} The value will be zero if the function is successful. The return value will be one of the following constants:
   * - {@link MMSysError.NoError | NoError} - Normal successful completion (zero).  <br/>  
   * - {@link MMSysError.InvalHandle | InvalHandle} - The specified device handle is invalid. The system is not speaking or the text-to-speech handle is invalid.  <br/>  
   * @comment This call only affects the audio output and has no effect when writing log files, wave files, or when using the speech-to-memory capability of the text-to-speech system.   <br/>  
   * If the text-to-speech system owns the audio device (i.e. {@link DeviceManagement.OwnAudioDevice | OwnAudioDevice} was specified in the startup function), then it remains paused until one of the following is called:  <br/>  
   * * openInMemory
   * * openLogFile
   * * ppenWaveFile
   * * resume
   * * sync
    * If the text-to-speech system does not own the audio device (i.e.  {@link DeviceManagement.OwnAudioDevice | OwnAudioDevice} was NOT specified in the startup function) and {@link pause()} is called while the system is speaking, it will remain paused until the system has completed speaking.  <br/>  
    * In this case, the wave output device is released when {@link reset()} is called. It will also be released if {@link sync()}, {@link openInMemory()}, {@link openLogFile()}, or {@link openWaveFile()} is called AND the system has completed speaking.  <br/>  
    * Note that the {@link pause()} call will NOT resume audio output if the text-to-speech system has been paused by the {@link pause()} call.
   * @see {@link resume}
   * @see {@link reset}
   * @see {@link speak}
   * @see {@link sync}
   */
  pause (): MMSysError {
    return super.pause();
  }

  /**
   * Resumes text-to-speech output after it was paused by calling {@link pause()}.
   * @return {MMSysError} The value will be zero if the function is successful. The return value will be one of the following constants:
   * - {@link MMSysError.NoError | NoError} - Normal successful completion (zero).  <br/>  
   * - {@link MMSysError.InvalHandle | InvalHandle} - The system was not paused or the text-to-speech handle was invalid.  <br/>  
   * @comment This call only affects the audio output and has no effect when writing log files, writing wave files, or when writing speech samples to memory.  
   * @see {@link pause}
   */
  resume (): MMSysError {
    return super.resume();
  }

  /**
   * Cancels all audio output and deletes any text from the Text-To-Speech systems text queue. All pending index marks are discarded.  
   * @return {MMSysError} The value will be zero if the function is successful. The return value will be one of the following constants:
   * - {@link MMSysError.NoError | NoError} - Normal successful completion (zero).  <br/>  
   * - {@link MMSysError.NoMem | NoMem} - Unable to allocate memory.  <br/>  
   * - {@link MMSysError.Error | Error} - Unable to flush the system.  <br/>  
   * - {@link MMSysError.InvalHandle | InvalHandle} - The Text-To-Speech handle is invalid.  <br/>  
   * @comment The {@link reset()} call flushes all previously queued text and stops all audio output. If the {@link openInMemory()} call has enabled outputting the speech samples to memory, then all queued memory buffers will be returned to the calling application. If the `reset` flag is on and the text-to-speech system is in one of its special modes (log-file, wave-file or speech-to-memory mode), then all files will be closed and the text-to-speech system is returned to the startup state.  <br/>  
   * {@link reset()} should be called before {@link closeInMemory()}. Failing to do this in a situation where the synthesizer is busy may result in a deadlock.
   * @see {@link pause}
   * @see {@link openInMemory}
   * @see {@link openLogFile}
   * @see {@link openWaveFile}
   */
  reset (): MMSysError {
    return super.reset();
  }

  /**
   * Returns the current setting of the volume.  
   * @type {number} The current setting of the volume. Valid values range from 0 to 100.  
   * @comment The current setting of the volume is returned even if the volume change has not yet occurred. This may occur while setting {@link volume} without the {@link sync()} call. The volume change occurs on clause boundaries.  
   */
  get volume (): number {
    return super.volume;
  }

  /**
   * Sets the volume of the text-to-speech system.  
   * @comment The volume change is not effective until the next phrase boundary. All the queued audio encountered before the phrase boundary is unaffected.  
   */
  set volume ( value: number ) {
    super.volume = value;
  }

  /**
   * Returns the current setting of the attenuation volume.
   * @type {number} The current setting of the attenuation volume. Valid values range from 0 to 100.  
   * @comment The current setting of the attenuation volume is returned even if the attenuation volume change has not yet occurred. This may occur while setting {@link attenuationVolume} without the {@link sync()} call. The attenuation volume change occurs on clause boundaries.  
   */
  get attenuationVolume (): number {
    return super.attenuationVolume;
  }

  /**
   * Sets the attenuation volume of the text-to-speech system.
   * @comment The attenuation volume change is not effective until the next phrase boundary. All the queued audio encountered before the phrase boundary is unaffected.
   */
  set attenuationVolume ( value: number ) {
    super.attenuationVolume = value;
  }

  /**
   * Returns the current setting of the speaking rate.  
   * @type {number} The current setting of the speaking rate. Valid values range from 75 to 600 words per minute.  
   * @comment The current setting of the speaking rate is returned even if the speaking rate change has not yet occurred. This may occur while setting {@link rate} without the {@link sync()} call. The speaking-rate change occurs on clause boundaries.  
   */
  get rate (): number {
    return super.rate;
  }

  /**
   * Sets the text-to-speech speaking rate.  
   * @comment The speaking rate change is not effective until the next phrase boundary. All the queued audio encountered before the phrase boundary is unaffected.  
   */
  set rate ( value: number ) {
    super.rate = value;
  }

  /**
   * Returns the value of the identifier for the last voice that has spoken.  
   * @type {Speaker} The current speaker.  
   * @comment Note that even after a setting {@link speaker}, {@link speaker} returns the value for the previous speaking voice until the new voice actually has spoken.  
   */
  get speaker (): Speaker {
    return super.speaker;
  }

  /**
   * Sets the voice of the speaker the text-to-speech system will use.  
   * @comment The change in speaking voice is not effective until the next phrase boundary. All queued audio encountered before the phrase boundary is unaffected.  
   */
  set speaker ( value: Speaker ) {
    super.speaker = value;
  }

  /**
   * Returns if the Text-To-Speech system is currently speaking.  
   * @type {boolean} value is `true` if audio samples are playing and `false` if no audio sample is playing.  
   * @comment Has no meaning if the application is sending speech to a wave file or sending speech to memory.  
   */
  get isSpeaking (): boolean {
    return super.isSpeaking;
  }

  /**
   * Returns a count of characters that the text-to-speech system is currently processing.  
   * @type {number} The number of characters that the text-to-speech system is currently processing.  
   */
  get inputCharacterCount (): number {
    return super.inputCharacterCount;
  }

  /**
   * Returns the current wave output device ID.  
   * @type {number} The current wave output device ID.  
   */
  get waveOutDeviceID (): number {
    return super.waveOutDeviceID;
  }

  // get language () {
  //   return super.language;
  // }

  // set language ( value: number ) {
  //   super.language = value;
  // }

  /**
   * Lists the current capabilities of the DECtalk Software by returning the class {@link TTSCaps}.  
   * @static
   * @returns {TTSCaps} The capabilities of the DECtalk Software.  
   * @comment Information returned in the {@link TTSCaps} class includes languages and proper-name pronunciation support, sample rate, minimum and maximum speaking rate, number of predefined speaking voices, character-set supported, and version number.  
   */
  static getCapabilities (): TTSCaps {
    return super.getCapabilities();
  }

  /**
   * Loads a user-defined pronunciation dictionary into the text-to-speech system.
   * @param {string} filename - The name of the user dictionary file to be loaded.  
   * @returns {MMSysError} The value will be zero if the function is successful. The return value will be one of the following constants:  
   * - {@link MMSysError.NoError | NoError} - Normal successful completion (zero).  <br/>  
   * - {@link MMSysError.NoMem | NoMem} - Unable to allocate memory for dictionary.  <br/>  
   * - {@link MMSysError.InvalParam | InvalParam} - Dictionary file not found or an invalid dictionary file name.  <br/>  
   * - {@link MMSysError.Error | Error} - Illegal dictionary format or a dictionary is already loaded.  <br/>  
   * - {@link MMSysError.InvalHandle | InvalHandle} - The Text-To-Speech handle is invalid.  <br/>  
   * @comment This call loads a dictionary created by the windict or userdict applet. Any previously loaded user dictionary must be unloaded before loading a new user dictionary. Note that the text-to-speech system will automatically load a user dictionary, user.dic, at startup if it exists in the home directory.  
   * @see {@link unloadUserDictionary}
   */
  loadUserDictionary ( filename: string ): MMSysError {
    return super.loadUserDictionary( filename );
  }

  /**
   * Unloads the currently loaded user dictionary.  
   * @returns {MMSysError} The value will be zero if the function is successful. The return value will be one of the following constants:
   * - {@link MMSysError.NoError | NoError} - Normal successful completion (zero).  <br/>  
   * - {@link MMSysError.InvalHandle | InvalHandle} - The Text-To-Speech handle is invalid.  <br/>  
   * @comment A user dictionary is created using the User Dictionary Build tool.  
   * @see {@link loadUserDictionary}
   */
  unloadUserDictionary (): MMSysError {
    return super.unloadUserDictionary();
  }

  /**
   * Returns information about the currently running version of DECtalk Software.
   * @readonly
   * @static
   */
  static get version (): {
    readonly dllVersion: number,
    readonly dTalkVersion: number,
    readonly structVersion: number,
    readonly language: string,
    readonly version: string,
    readonly versionString: string,
    readonly dtMajor: number,
    readonly dtMinor: number,
    readonly dapiMajor: number,
    readonly dapiMinor: number,
  } {

    return super.version;
  }

  /**
   * Causes the text-to-speech system to enter into the speech-to-memory mode. This mode indicates that the speech samples are to be written into memory buffers rather than sent to an audio device each time {@link speak()} is called. The {@link addBuffer()} call supplies the text-to-speech system with the memory buffers that it needs. The text-to-speech system remains in the speech-to-memory mode until {@link closeInMemory()} is called.  
   * @param {WaveFormat} format - Determines the wave file audio sample format
   * @return {MMSysError} The value will be zero if the function is successful. return value will be one of the following constants:
   * - {@link MMSysError.NoError | NoError} - Normal successful completion (zero).  <br/>
   * - {@link MMSysError.InvalParam | InvalParam} - An invalid parameter or illegal wave output format was passed.  <br/>
   * - {@link MMSysError.NoMem | NoMem} - Unable to allocate memory.  <br/>
   * - {@link MMSysError.Error | Error} - Illegal output state.  <br/>
   * - {@link MMSysError.InvalHandle | InvalHandle} - The Text-To-Speech handle is invalid.  <br/>
   * @comment The text-to-speech system is in the speech-to-memory mode after successfully invoking this call. The memory buffer is passed using the class {@link TTSBuffer}. <br/>  
   * The text-to-speech system returns the buffer to the application when the memory buffer, phoneme array, or index mark array is full or when force was used in the {@link speak()} call. <br/>  
   * The startup function must be called to start the text-to-speech system before calling this function. <br/>  
   * {@link openInMemory()} automatically resumes audio output if the text-to-speech system is in a paused state by a previously issued {@link pause()} call.
   * @see {@link closeInMemory}
   * @see {@link addBuffer}
   * @see {@link startup}
   * @see {@link TTSBuffer}
   * @see {@link speak}
   * @see {@link pause}
   * @see {@link reset}
   * @see {@link returnBuffer}
   */
  openInMemory ( format: WaveFormat ): MMSysError {
    return super.openInMemory( format );
  }

  /**
   * Return the Text-To-Speech system to it's normal state. Speech samples will be routed to the audio device (if audio output was enabled at startup).
   * @return {MMSysError} The value will be zero if the function is successful. The return value will be one of the following constants:
   * - {@link MMSysError.NoError | NoError} - Normal successful completion (zero).  <br/>  
   * - {@link MMSysError.Error | Error} - Output to memory not enabled or unable to create a system object.  <br/>  
   * - {@link MMSysError.InvalHandle | InvalHandle} - The Text-To-Speech handle is invalid.  <br/>  
   * @comment {@link openInMemory()} must be called before calling {@link closeInMemory()}.
   * @see {@link openInMemory}
   */
  closeInMemory (): MMSysError {
    return super.closeInMemory();
  }

  /**
   * Add a buffer to the memory list.  
   * @param {TTSBuffer} buf - The buffer to be added to the memory list.
   * @returns {MMSysError} The value will be zero if the function is successful. The return value will be one of the following constants:
   * - {@link MMSysError.NoError | NoError} - Normal successful completion (zero).  <br/>  
   * - {@link MMSysError.InvalParam | InvalParam} - Invalid parameter.  <br/>  
   * - {@link MMSysError.Error | Error} - Output to memory not enabled or unable to create a system object.  <br/>  
   * - {@link MMSysError.InvalHandle | InvalHandle} - The Text-To-Speech handle is invalid.  <br/>  
   * @comment The application must call {@link openInMemory()} before calling {@link addBuffer()}. The memory buffer is passed using the {@link TTSBuffer} class. <br/>  
   * The text-to-speech system returns the buffer to the application when the memory buffer, phoneme array, or index mark array is full or when force was used in the {@link speak()} call.
   * @see {@link openInMemory}
   * @see {@link returnBuffer}
   * @see {@link startup}
   * @see {@link TTSBuffer}
   */
  addBuffer ( buf: TTSBuffer ): MMSysError {
    return super.addBuffer( buf );
  }

  /**
   * Cause the current buffer to be returned even if it not yet full. The buffer may in fact be empty.  
   * @returns {TTSBuffer} The buffer returned by the Text-To-Speech system.  
   */
  returnBuffer (): TTSBuffer {
    return super.returnBuffer();
  }

  /**
   * Speaks a single letter as quickly as possible, aborting any previously queued speech. This will be somewhat slower if {@link speak()} has been called since the last {@link typing()} or {@link reset()} call.  
   * @param {string} text - The character to be spoken.  
   * @comment This function should only be called only when the application is synthesizing directly to an audio device (not to memory or to a file).  
`  */
  typing ( text: string ): void {
    super.typing( text );
  }


  /**
   * Checks for an installed language and loads it into the DecTalk Multi-Language (ML) engine.  
   * @static
   * @param {string} lang - The language to be loaded. 
   * @returns {number} A handle to the loaded language on success or sets the bit `TTSLangError` on failure. If the `TTSLangError` bit is set, the return can equal one of two values: `TTSNotSupported` for the application is not running DECtalk ML and `TTSNotAvailable` for the language selected is not installed.
   * @comments This call must be called before a language may be selected and opened in a multi-language application.
   */
  static startLang ( lang: string ): number {
    return super.startLang( lang );
  }

  /**
   * Selects a loaded language for a program thread.  
   * @static
   * @param {number} lang - The language header to be selected.
   * @returns {boolean} True if the language was selected successfully.
   */
  static selectLang ( lang: number ): boolean {
    return super.selectLang( lang );
  }

  /**
   * Closes an instance for an installed language and attempts to unload it from the DecTalk Multi-Language (ML) engine.  
   * @static
   * @param {string} lang - The language to be closed.
   * @returns {boolean} True if the language was closed successfully.
   * @comments Call this application per thread using the selected language. When a thread returns `true`, the language is freed and can be uninstalled or upgraded. A return of `true` may be a bad pass of the lang variable or more instances. If there are more instances, the call frees the current instance and returns a `false` flag. After calling {@link closeLang()}, assume the language handle is no longer valid.
   * @see {@link enumLangs}
   * @see {@link startLang}
   * @see {@link selectLang}
   */
  static closeLang ( lang: string ): boolean {
    return super.closeLang( lang );
  }

  /**
   * Retrieves information about what languages are available.  
   * @static
   * @returns {{ multiLang: boolean, languages: { code: string, name: string }[] }} An object contains language data, and zero on error  
   * @comment {@link enumLangs()} returns the default language in the registry as the first language of the array of entries returned by langs.
   * @see {@link startLang}
   * @see {@link selectLang}
   * @see {@link closeLang}
   */
  static enumLangs (): { multiLang: boolean, languages: { code: string, name: string }[] } | 0 {
    return super.enumLangs();
  }


}

/**
 * Contains information about the current state of the Text-To-Speech system.
 * @comment When the memory buffer is completed, the memory buffer is returned to the calling application. A memory buffer is considered completed when any one of the following occur:  <br/>
 * * The memory buffer ( the data field ) is filled.
 * * The phoneme array is filled.
 * * The index mark array is filled.
 * * A `TTSForce` argument is used in the call to {@link DecTalk.speak | speak()}.
 * @see {@link DecTalk.addBuffer}
 * @see {@link DecTalk.returnBuffer}
 */
export class TTSBuffer extends addon.TTSBuffer {
  /**
   * Creates an instance of TTSBuffer.  
   * @param { { data?: number, phoneme?: number, index?: number } } options - The maximum lengths of each list.  
   */
  constructor ( options: { data?: number, phoneme?: number, index?: number } ) {
    super( options );
  }

  /**
   * The audio sample data buffer.
   * @readonly
   * @type {Buffer}
   */
  readonly data!: Buffer;
  /**
   * The list of phonemes in the buffer.
   * @readonly
   * @type {TTSPhoneme[]}
   */
  readonly phoneme!: TTSPhoneme[];
  /**
   * The list of index marks in the buffer.
   * @readonly
   * @type {TTSIndex[]}
   */
  readonly index!: TTSIndex[];

  /**
   * The maximum number of bytes in the data buffer.  
   * @readonly
   * @type {number}
   */
  readonly maxBufferLength!: number;
  /**
   * The maximum number of classes in the phoneme array.  
   * @readonly
   * @type {number}
   */
  readonly maxPhonemeLength!: number;
  /**
   * The maximum number of classes in the index array.  
   * @readonly
   * @type {number}
   */
  readonly maxIndexLength!: number;

}