"use strict";
var __awaiter = (this && this.__awaiter) || function (thisArg, _arguments, P, generator) {
    function adopt(value) { return value instanceof P ? value : new P(function (resolve) { resolve(value); }); }
    return new (P || (P = Promise))(function (resolve, reject) {
        function fulfilled(value) { try { step(generator.next(value)); } catch (e) { reject(e); } }
        function rejected(value) { try { step(generator["throw"](value)); } catch (e) { reject(e); } }
        function step(result) { result.done ? resolve(result.value) : adopt(result.value).then(fulfilled, rejected); }
        step((generator = generator.apply(thisArg, _arguments || [])).next());
    });
};
var __importDefault = (this && this.__importDefault) || function (mod) {
    return (mod && mod.__esModule) ? mod : { "default": mod };
};
Object.defineProperty(exports, "__esModule", { value: true });
exports.TTSBuffer = exports.DecTalk = exports.DeviceID = exports.DeviceManagement = exports.Speaker = exports.WaveFormat = exports.MMSysError = exports.LogType = exports.Message = void 0;
const bindings_1 = __importDefault(require("bindings"));
const addon = (0, bindings_1.default)('node-dectalk.node');
var Message;
(function (Message) {
    Message[Message["Buffer"] = 9] = "Buffer";
    Message[Message["IndexMark"] = 1] = "IndexMark";
    Message[Message["Status"] = 2] = "Status";
    Message[Message["Visual"] = 3] = "Visual";
})(Message = exports.Message || (exports.Message = {}));
var LogType;
(function (LogType) {
    /** Log text input. */
    LogType[LogType["Text"] = 1] = "Text";
    /** Log phonemes to host */
    LogType[LogType["Phonemes"] = 2] = "Phonemes";
    /** Log name types to console */
    LogType[LogType["NameTypes"] = 4] = "NameTypes";
    /** Log name form classes to console */
    LogType[LogType["FormTypes"] = 8] = "FormTypes";
    /** Log name syllable structure */
    LogType[LogType["Syllables"] = 16] = "Syllables";
    /** Log phones out  with dur and f0 */
    LogType[LogType["OutPhones"] = 32] = "OutPhones";
    /** Log debug information in file dbglog.txt */
    LogType[LogType["DbgLog"] = 64] = "DbgLog";
})(LogType = exports.LogType || (exports.LogType = {}));
var MMSysError;
(function (MMSysError) {
    /** no error */
    MMSysError[MMSysError["NoError"] = 0] = "NoError";
    /** unspecified error */
    MMSysError[MMSysError["Error"] = 1] = "Error";
    /** device ID out of range */
    MMSysError[MMSysError["BadDeviceID"] = 2] = "BadDeviceID";
    /** driver failed enable */
    MMSysError[MMSysError["NotEnabled"] = 3] = "NotEnabled";
    /** device already allocated */
    MMSysError[MMSysError["Allocated"] = 4] = "Allocated";
    /** device handle is invalid */
    MMSysError[MMSysError["InvalHandle"] = 5] = "InvalHandle";
    /** no device driver present */
    MMSysError[MMSysError["NoDriver"] = 6] = "NoDriver";
    /** memory allocation error */
    MMSysError[MMSysError["NoMem"] = 7] = "NoMem";
    /** function isn't supported */
    MMSysError[MMSysError["NotSupported"] = 8] = "NotSupported";
    /** error value out of range */
    MMSysError[MMSysError["BadErrNum"] = 9] = "BadErrNum";
    /** invalid flag passed */
    MMSysError[MMSysError["InvalFlag"] = 10] = "InvalFlag";
    /** invalid parameter passed */
    MMSysError[MMSysError["InvalParam"] = 11] = "InvalParam";
    /** handle being used */
    MMSysError[MMSysError["HandleBusy"] = 12] = "HandleBusy";
    /** "Specified alias not found in WIN.INI */
    MMSysError[MMSysError["InvalidAlias"] = 13] = "InvalidAlias";
    /** last error in range */
    MMSysError[MMSysError["LastError"] = 13] = "LastError";
})(MMSysError = exports.MMSysError || (exports.MMSysError = {}));
;
/** defines for dwFormat field of WAVEINCAPS and WAVEOUTCAPS */
var WaveFormat;
(function (WaveFormat) {
    /** invalid format */
    WaveFormat[WaveFormat["InvalidFormat"] = 0] = "InvalidFormat";
    /** 11.025 kHz, Mono,   8-bit */
    WaveFormat[WaveFormat["Format1M08"] = 1] = "Format1M08";
    /** 11.025 kHz, Stereo, 8-bit */
    WaveFormat[WaveFormat["Format1S08"] = 2] = "Format1S08";
    /** 11.025 kHz, Mono,   16-bit */
    WaveFormat[WaveFormat["Format1M16"] = 4] = "Format1M16";
    /** 11.025 kHz, Stereo, 16-bit */
    WaveFormat[WaveFormat["Format1S16"] = 8] = "Format1S16";
    /** 22.05  kHz, Mono,   8-bit */
    WaveFormat[WaveFormat["Format2M08"] = 16] = "Format2M08";
    /** 22.05  kHz, Stereo, 8-bit */
    WaveFormat[WaveFormat["Format2S08"] = 32] = "Format2S08";
    /** 22.05  kHz, Mono,   16-bit */
    WaveFormat[WaveFormat["Format2M16"] = 64] = "Format2M16";
    /** 22.05  kHz, Stereo, 16-bit */
    WaveFormat[WaveFormat["Format2S16"] = 128] = "Format2S16";
    /** 44.1   kHz, Mono,   8-bit */
    WaveFormat[WaveFormat["Format4M08"] = 256] = "Format4M08";
    /** 44.1   kHz, Stereo, 8-bit */
    WaveFormat[WaveFormat["Format4S08"] = 512] = "Format4S08";
    /** 44.1   kHz, Mono,   16-bit */
    WaveFormat[WaveFormat["Format4M16"] = 1024] = "Format4M16";
    /** 44.1   kHz, Stereo, 16-bit */
    WaveFormat[WaveFormat["Format4S16"] = 2048] = "Format4S16";
    /** 8      kHz, Mono,   8-bit */
    WaveFormat[WaveFormat["Format08M08"] = 4096] = "Format08M08";
    /** 8      kHz, Mono,   16-bit */
    WaveFormat[WaveFormat["Format08M16"] = 8192] = "Format08M16";
    /** 8      kHz, Mono,   Mu-law */
    WaveFormat[WaveFormat["FormatMuLaw"] = 7] = "FormatMuLaw";
})(WaveFormat = exports.WaveFormat || (exports.WaveFormat = {}));
var Speaker;
(function (Speaker) {
    Speaker[Speaker["Paul"] = 0] = "Paul";
    Speaker[Speaker["Betty"] = 1] = "Betty";
    Speaker[Speaker["Harry"] = 2] = "Harry";
    Speaker[Speaker["Frank"] = 3] = "Frank";
    Speaker[Speaker["Dennis"] = 4] = "Dennis";
    Speaker[Speaker["Kit"] = 5] = "Kit";
    Speaker[Speaker["Ursula"] = 6] = "Ursula";
    Speaker[Speaker["Rita"] = 7] = "Rita";
    Speaker[Speaker["Wendy"] = 8] = "Wendy";
})(Speaker = exports.Speaker || (exports.Speaker = {}));
var DeviceManagement;
(function (DeviceManagement) {
    DeviceManagement[DeviceManagement["OwnAudioDevice"] = 1] = "OwnAudioDevice";
    DeviceManagement[DeviceManagement["ReportOpenError"] = 2] = "ReportOpenError";
    // UseSAPI5AudioDevice = 0x40000000,
    DeviceManagement[DeviceManagement["DoNotUseAudioDevice"] = 2147483648] = "DoNotUseAudioDevice";
})(DeviceManagement = exports.DeviceManagement || (exports.DeviceManagement = {}));
var DeviceID;
(function (DeviceID) {
    /** device ID for wave device mapper */
    DeviceID[DeviceID["Mapper"] = 4294967295] = "Mapper";
    /** Open device as shareable */
    DeviceID[DeviceID["OpenShareable"] = 4] = "OpenShareable";
})(DeviceID = exports.DeviceID || (exports.DeviceID = {}));
;
class DecTalk extends addon.DecTalk {
    constructor() {
        super();
    }
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
    startup(deviceID, deviceManagement = DeviceManagement.OwnAudioDevice, cb) {
        return super.startup(deviceID, deviceManagement, cb);
    }
    /**
     * DECtalk shutdown function.
     * @returns {MMSysError} This value is zero if shutdown was successful.
     *   The return value will be one of the following constants:
     *
     *  `NoError` = 0 - Normal successful completion  <br/>
     *  `InvalHandle` - The Text-To-Speech handle is invalid  <br/>
     */
    shutdown() {
        return super.shutdown();
    }
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
    speak(text, force = false) {
        const _super = Object.create(null, {
            speak: { get: () => super.speak }
        });
        return __awaiter(this, void 0, void 0, function* () {
            if (typeof text !== "string") {
                text = text.join(" ");
            }
            return yield _super.speak.call(this, text, force);
        });
    }
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
    speakSync(text, force = false) {
        if (typeof text !== "string") {
            text = text.join(" ");
        }
        return super.speakSync(text, force);
    }
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
    sync() {
        const _super = Object.create(null, {
            sync: { get: () => super.sync }
        });
        return __awaiter(this, void 0, void 0, function* () {
            return yield _super.sync.call(this);
        });
    }
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
    syncSync() {
        return super.syncSync();
    }
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
    openWaveFile(filename, format) {
        return super.openWaveFileOut(filename, format);
    }
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
    closeWaveFile() {
        return super.closeWaveFileOut();
    }
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
    openLogFile(filename, logType) {
        return super.openLogFile(filename, logType);
    }
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
    closeLogFile() {
        return super.closeLogFile();
    }
    /**
     * Pauses the Text-To-Speech system.
     * @return {MMSysError} The value will be zero if the function is successful.
     * The return value will be one of the following constants:
     *
     * `NoError` = 0 - Normal successful completion  <br/>
     * `InvalHandle` - The specified device handle is invalid (The system is NOT speaking), or the Text-To-Speech handle is invalid  <br/>
     * @memberof DecTalk
     */
    pause() {
        return super.pause();
    }
    /**
     * Resumes the Text-To-Speech system.
     * @return {MMSysError} The value will be zero if the function is successful.
     * The return value will be one of the following constants:
     *
     * `NoError` = 0 - Normal successful completion  <br/>
     * `InvalHandle` - The specified device handle is invalid (The system is NOT speaking), or the Text-To-Speech handle is invalid  <br/>
     * @memberof DecTalk
     */
    resume() {
        return super.resume();
    }
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
    reset() {
        return super.reset();
    }
    get sampleRate() {
        return super.getSampleRate();
    }
    set sampleRate(value) {
        super.setSampleRate(value);
    }
    get volume() {
        return super.getVolume();
    }
    set volume(value) {
        super.setVolume(value);
    }
    get attenuationVolume() {
        return super.getAttenuationVolume();
    }
    set attenuationVolume(value) {
        super.setAttenuationVolume(value);
    }
    get rate() {
        return super.getRate();
    }
    set rate(value) {
        super.setRate(value);
    }
    get speaker() {
        return super.getSpeaker();
    }
    set speaker(value) {
        super.setSpeaker(value);
    }
    get isSpeaking() {
        return super.isSpeaking;
    }
    get inputCharacterCount() {
        return super.inputCharacterCount;
    }
    get waveOutDeviceID() {
        return super.waveOutDeviceID;
    }
    get language() {
        return super.getLanguage();
    }
    set language(value) {
        super.setLanguage(value);
    }
    static getCapabilities() {
        return super.getCapabilities();
    }
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
    loadUserDictionary(filename) {
        return super.loadUserDictionary(filename);
    }
    /**
     * Unloads the currently loaded user dictionary
     * @returns {MMSysError} The value will be zero if the function is successful.
     * The return value will be one of the following constants:
     *
     * `NoError` = 0 - Normal successful completion  <br/>
     * `InvalHandle` - The Text-To-Speech handle is invalid  <br/>
     * @memberof DecTalk
     */
    unloadUserDictionary() {
        return super.unloadUserDictionary();
    }
    /**
     * Returns the current version of the Text-To-Speech system.
     * @readonly
     * @static
     * @memberof DecTalk
     */
    static get version() {
        return super.version;
    }
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
    openInMemory(format) {
        return super.openInMemory(format);
    }
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
    closeInMemory() {
        return super.closeInMemory();
    }
    addBuffer(buf) {
        return super.addBuffer(buf);
    }
}
exports.DecTalk = DecTalk;
class TTSBuffer extends addon.TTSBuffer {
    constructor(options) {
        super(options);
    }
}
exports.TTSBuffer = TTSBuffer;
