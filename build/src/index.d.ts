/// <reference types="node" />
declare const addon: any;
export declare type TTSCallback = (msg: Message, buffer: Buffer) => void;
export interface LanguageParams {
    readonly language: number;
    readonly languageAttributes: number;
}
export declare enum Message {
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
export declare enum LogType {
    /** Log text input. */
    Text = 1,
    /** Log phonemes to host */
    Phonemes = 2,
    /** Log name types to console */
    NameTypes = 4,
    /** Log name form classes to console */
    FormTypes = 8,
    /** Log name syllable structure */
    Syllables = 16,
    /** Log phones out  with dur and f0 */
    OutPhones = 32,
    /** Log debug information in file dbglog.txt */
    DbgLog = 64
}
export declare enum MMSysError {
    /** no error */
    NoError = 0,
    /** unspecified error */
    Error = 1,
    /** device ID out of range */
    BadDeviceID = 2,
    /** driver failed enable */
    NotEnabled = 3,
    /** device already allocated */
    Allocated = 4,
    /** device handle is invalid */
    InvalHandle = 5,
    /** no device driver present */
    NoDriver = 6,
    /** memory allocation error */
    NoMem = 7,
    /** function isn't supported */
    NotSupported = 8,
    /** error value out of range */
    BadErrNum = 9,
    /** invalid flag passed */
    InvalFlag = 10,
    /** invalid parameter passed */
    InvalParam = 11,
    /** handle being used */
    HandleBusy = 12,
    /** "Specified alias not found in WIN.INI */
    InvalidAlias = 13,
    /** last error in range */
    LastError = 13
}
/** defines for dwFormat field of WAVEINCAPS and WAVEOUTCAPS */
export declare enum WaveFormat {
    /** invalid format */
    InvalidFormat = 0,
    /** 11.025 kHz, Mono,   8-bit */
    Format1M08 = 1,
    /** 11.025 kHz, Stereo, 8-bit */
    Format1S08 = 2,
    /** 11.025 kHz, Mono,   16-bit */
    Format1M16 = 4,
    /** 11.025 kHz, Stereo, 16-bit */
    Format1S16 = 8,
    /** 22.05  kHz, Mono,   8-bit */
    Format2M08 = 16,
    /** 22.05  kHz, Stereo, 8-bit */
    Format2S08 = 32,
    /** 22.05  kHz, Mono,   16-bit */
    Format2M16 = 64,
    /** 22.05  kHz, Stereo, 16-bit */
    Format2S16 = 128,
    /** 44.1   kHz, Mono,   8-bit */
    Format4M08 = 256,
    /** 44.1   kHz, Stereo, 8-bit */
    Format4S08 = 512,
    /** 44.1   kHz, Mono,   16-bit */
    Format4M16 = 1024,
    /** 44.1   kHz, Stereo, 16-bit */
    Format4S16 = 2048,
    /** 8      kHz, Mono,   8-bit */
    Format08M08 = 4096,
    /** 8      kHz, Mono,   16-bit */
    Format08M16 = 8192,
    /** 8      kHz, Mono,   Mu-law */
    FormatMuLaw = 7
}
export declare enum Speaker {
    Paul = 0,
    Betty = 1,
    Harry = 2,
    Frank = 3,
    Dennis = 4,
    Kit = 5,
    Ursula = 6,
    Rita = 7,
    Wendy = 8
}
export declare enum DeviceManagement {
    OwnAudioDevice = 1,
    ReportOpenError = 2,
    DoNotUseAudioDevice = 2147483648
}
export declare enum DeviceID {
    /** device ID for wave device mapper */
    Mapper = 4294967295,
    /** Open device as shareable */
    OpenShareable = 4
}
export declare class DecTalk extends addon.DecTalk {
    constructor();
    /**
     * DECtalk initialization function.
     * @param {(DeviceID | number)} [deviceID] - Wave out device ID number. `WaveMapper` may be used here if the device ID number is unknown.
     * @param {DeviceManagement} [deviceManagement=DeviceManagement.OwnAudioDevice] - Specifies how the wave output device is managed.
     * @return {MMSysError} This value is zero if initialization was successful.
     *    The return value will be one of the following constants:
     *
     *    `NoError` = 0 - Normal successful completion  <br/>
     *    `NoDriver` - No wave out device driver present  <br/>
     *    `BadDeviceID` - Device ID out of range  <br/>
     *    `NoMem` - Unable to allocate memory  <br/>
     *    `Error` - Dictionary not found  <br/>
     *    `InvalParam` - Invalid param for th eload dictionary  <br/>
     * @memberof DecTalk
     */
    startup(deviceID?: DeviceID | number, deviceManagement?: DeviceManagement, cb?: TTSCallback): MMSysError;
    /**
     * DECtalk shutdown function.
     * @returns {MMSysError} This value is zero if shutdown was successful.
     *   The return value will be one of the following constants:
     *
     *  `NoError` = 0 - Normal successful completion  <br/>
     *  `InvalHandle` - The Text-To-Speech handle is invalid  <br/>
     */
    shutdown(): MMSysError;
    /**
     * This function queues to the Text-To-Speech system.
     * @async
     * @param { ( string | string[] ) } text - The text to be spoken.
     * @param { boolean } [ force = false ] - Specifies if the text is to be pushed through the Text-To-Speech system even if it is not on a clause boundary.
     * @return  {Promise<MMSysError>} The value will be zero if the function is successful.
     *  The return value will be one of the following constants:
     *
     *  `NoError` = 0 - Normal successful completion  <br/>
     *  `NoMem` - Unable to allocate memory  <br/>
     *  `InvalHandle` - The Text-To-Speech handle is invalid  <br/>
     * @memberof DecTalk
     */
    speak(text: string | string[], force?: boolean): Promise<MMSysError>;
    /**
     * This function queues to the Text-To-Speech system.
     * @param { ( string | string[] ) } text - The text to be spoken.
     * @param { boolean } [ force = false ] - Specifies if the text is to be pushed through the Text-To-Speech system even if it is not on a clause boundary.
     * @return  {MMSysError} The value will be zero if the function is successful.
     *  The return value will be one of the following constants:
     *
     *  `NoError` = 0 - Normal successful completion  <br/>
     *  `NoMem` - Unable to allocate memory  <br/>
     *  `InvalHandle` - The Text-To-Speech handle is invalid  <br/>
     * @memberof DecTalk
     */
    speakSync(text: string | string[], force?: boolean): MMSysError;
    /**
     * Will block until all previously queued text has been spoken. This function will automatically resume audio if the Text - To - Speech system has been paused by the `pause()` function.
     * @async
     * @return {Promise<MMSysError>} The value will be zero if the function is successful.
     * The return value will be one of the following constants:
     *
     * `NoError` = 0 - Normal successful completion  <br/>
     * `Error` - Unable to complete queued text  <br/>
     * `InvalHandle` - The Text-To-Speech handle is invalid  <br/>
     * @memberof DecTalk
     */
    sync(): Promise<MMSysError>;
    /**
     * Will block until all previously queued text has been spoken. This function will automatically resume audio if the Text - To - Speech system has been paused by the `pause()` function.
     * @return {MMSysError} The value will be zero if the function is successful.
     * The return value will be one of the following constants:
     *
     * `NoError` = 0 - Normal successful completion  <br/>
     * `Error` - Unable to complete queued text  <br/>
     * `InvalHandle` - The Text-To-Speech handle is invalid  <br/>
     * @memberof DecTalk
     */
    syncSync(): MMSysError;
    /**
     * Creates a wave file. All subsequent calls to the `speak()` function cause the audio to be written to the specified file until the `closeWaveFile()` function is called.
     *
     * @param {string} filename - The name of the wave file to be created.
     * @param {WaveFormat} format - Ddetermines the wave file audio sample format.
     * @return {MMSysError} The value will be zero if the function is successful.
     * The return value will be one of the following constants:
     *
     * `NoError` = 0 - Normal successful completion  <br/>
     * `InvalParam` - An invalid parameter was passed (An illegal wave output format value.)  <br/>
     * `NoMem` - Unable to allocate memory  <br/>
     * `Allocated` - A wave output file is already open  <br/>
     * `Error` - Unable to open the wave output file or unable to write to the wave output file  <br/>
     * `InvalHandle` - The Text-To-Speech handle is invalid  <br/>
     * @memberof DecTalk
     */
    openWaveFile(filename: string, format: WaveFormat): MMSysError;
    /**
     * Close the Text-To-Speech Wave File.
     * @return {MMSysError} The value will be zero if the function is successful.
     * The return value will be one of the following constants:
     *
     * `NoError` = 0 - Normal successful completion  <br/>
     * `Error` - Failure to wait for pending speech.  <br/>
     * OR Unable to update the wave output file header  <br/>
     * OR Unable to close the wave output file.  <br/>
     * OR No wave output file is open  <br/>
     * `InvalHandle` - The Text-To-Speech handle is invalid  <br/>
     * @memberof DecTalk
     */
    closeWaveFile(): MMSysError;
    /**
     *  Creates a file which contains either text, phonemes, or syllables. The phonemes and syllables are written using the arpabet alphabet. After calling this function, all subsequent calls to the `speak()` function cause the log data to be written to specified file until the `closeLogFile()` function is called.
     * @param {string} filename - The name of the log file to be created.
     * @param {LogType=} [logType] - Specifies the type of log file to be created.
     * @return {MMSysError} The value will be zero if the function is successful.
     * The return value will be one of the following constants:
     *
     * `NoError` = 0 - Normal successful completion  <br/>
     * `InvalParam` - An invalid parameter was passed  <br/>
     * `NoMem` - Unable to allocate memory  <br/>
     * `Allocated` - A log file is already open  <br/>
     * `Error` - Unable to open the log file.  <br/>
     * `InvalHandle` - The Text-To-Speech handle is invalid  <br/>
     * @memberof DecTalk
     */
    openLogFile(filename: string, logType?: LogType): MMSysError;
    /**
     * Closes the log file opened by the `openLogFile()` function.
     * @return {MMSysError} The value will be zero if the function is successful.
     * The return value will be one of the following constants:
     *
     * `NoError` = 0 - Normal successful completion  <br/>
     * `Error` - Failure to wait for pending speech  <br/>
     * OR Unable to close the output file  <br/>
     * OR No output file is open  <br/>
     * `InvalHandle` - The Text-To-Speech handle is invalid  <br/>
     * @memberof DecTalk
     */
    closeLogFile(): MMSysError;
    /**
     * Pauses the Text-To-Speech system.
     * @return {MMSysError} The value will be zero if the function is successful.
     * The return value will be one of the following constants:
     *
     * `NoError` = 0 - Normal successful completion  <br/>
     * `InvalHandle` - The specified device handle is invalid (The system is NOT speaking), or the Text-To-Speech handle is invalid  <br/>
     * @memberof DecTalk
     */
    pause(): MMSysError;
    /**
     * Resumes the Text-To-Speech system.
     * @return {MMSysError} The value will be zero if the function is successful.
     * The return value will be one of the following constants:
     *
     * `NoError` = 0 - Normal successful completion  <br/>
     * `InvalHandle` - The specified device handle is invalid (The system is NOT speaking), or the Text-To-Speech handle is invalid  <br/>
     * @memberof DecTalk
     */
    resume(): MMSysError;
    /**
     * cancels all audio output and deletes any text from the Text-To-Speech systems text queue. All pending index marks are discarded.
     * @return {MMSysError} The value will be zero if the function is successful.
     * The return value will be one of the following constants:
     *
     * `NoError` = 0 - Normal successful completion  <br/>
     * `NoMem` - Unable to allocate memory  <br/>
     * `Error` - Unable to flush the system  <br/>
     * `InvalHandle` - The Text-To-Speech handle is invalid  <br/>
     * @memberof DecTalk
     */
    reset(): MMSysError;
    get sampleRate(): number;
    set sampleRate(value: number);
    get volume(): number;
    set volume(value: number);
    get attenuationVolume(): number;
    set attenuationVolume(value: number);
    get rate(): number;
    set rate(value: number);
    get speaker(): Speaker;
    set speaker(value: Speaker);
    get isSpeaking(): boolean;
    get inputCharacterCount(): number;
    get waveOutDeviceID(): number;
    get language(): number;
    set language(value: number);
    static getCapabilities(): TTSCaps;
    /**
     * Load a user dictionary. If a user dictionary is already loaded then it must be unloaded by the `unloadUserDictionary()` function before the new dictionary can be loaded.
     * @param {string} filename - The name of the user dictionary file to be loaded.
     * @returns {MMSysError} The value will be zero if the function is successful.
     * The return value will be one of the following constants:
     *
     * `NoError` = 0 - Normal successful completion  <br/>
     * `NoMem` - Unable to allocate memory  <br/>
     * `InvalParam` - Dictory file not found. (invalid dictionary file name)  <br/>
     * `Error` - Illegal dictionary format, or a dictionary is already loaded  <br/>
     * `InvalHandle` - The Text-To-Speech handle is invalid  <br/>
     * @memberof DecTalk
     */
    loadUserDictionary(filename: string): MMSysError;
    /**
     * Unloads the currently loaded user dictionary
     * @returns {MMSysError} The value will be zero if the function is successful.
     * The return value will be one of the following constants:
     *
     * `NoError` = 0 - Normal successful completion  <br/>
     * `InvalHandle` - The Text-To-Speech handle is invalid  <br/>
     * @memberof DecTalk
     */
    unloadUserDictionary(): MMSysError;
    /**
     * Returns the current version of the Text-To-Speech system.
     * @readonly
     * @static
     * @memberof DecTalk
     */
    static get version(): string;
    /**
     * Causes all speech samples created by the Text-To-Speech system to be places in user supplied shared memory buffers. These buffers are supplied to the system by the `addBuffer()` function.
     * @param {WaveFormat} format - Determines the wave file audio sample format
     * @return {MMSysError} The value will be zero if the function is successful.
     * The return value will be one of the following constants:
     *
     * `NoError` = 0 - Normal successful completion <br/>
     * `InvalParam` - An invalid parameter was passed (An illegal wave output format value.) <br/>
     * `NoMem` - Unable to allocate memory <br/>
     * `Error` - Illegal output state <br/>
     * `InvalHandle` - The Text-To-Speech handle is invalid <br/>
     * @memberof DecTalk
     */
    openInMemory(format: WaveFormat): MMSysError;
    /**
     * Return the Text-To-Speech system to it's normal state. Speech samples will be routed to the audio device (if audio output was enabled at startup).
     * @return {MMSysError} The value will be zero if the function is successful.
     * The return value will be one of the following constants:
     *
     * `NoError` = 0 - Normal successful completion <br/>
     * `Error` - Output to memory not enabled, or unable to create a system object <br/>
     * `InvalHandle` - The Text-To-Speech handle is invalid <br/>
     * @memberof DecTalk
     */
    closeInMemory(): MMSysError;
    addBuffer(buf: any): MMSysError;
}
export declare class TTSBuffer extends addon.TTSBuffer {
    constructor(options: {
        data?: number;
        phoneme?: number;
        index?: number;
    });
}
export {};
