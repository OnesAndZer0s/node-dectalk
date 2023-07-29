"use strict";
var __createBinding = (this && this.__createBinding) || (Object.create ? (function(o, m, k, k2) {
    if (k2 === undefined) k2 = k;
    var desc = Object.getOwnPropertyDescriptor(m, k);
    if (!desc || ("get" in desc ? !m.__esModule : desc.writable || desc.configurable)) {
      desc = { enumerable: true, get: function() { return m[k]; } };
    }
    Object.defineProperty(o, k2, desc);
}) : (function(o, m, k, k2) {
    if (k2 === undefined) k2 = k;
    o[k2] = m[k];
}));
var __setModuleDefault = (this && this.__setModuleDefault) || (Object.create ? (function(o, v) {
    Object.defineProperty(o, "default", { enumerable: true, value: v });
}) : function(o, v) {
    o["default"] = v;
});
var __importStar = (this && this.__importStar) || function (mod) {
    if (mod && mod.__esModule) return mod;
    var result = {};
    if (mod != null) for (var k in mod) if (k !== "default" && Object.prototype.hasOwnProperty.call(mod, k)) __createBinding(result, mod, k);
    __setModuleDefault(result, mod);
    return result;
};
var __awaiter = (this && this.__awaiter) || function (thisArg, _arguments, P, generator) {
    function adopt(value) { return value instanceof P ? value : new P(function (resolve) { resolve(value); }); }
    return new (P || (P = Promise))(function (resolve, reject) {
        function fulfilled(value) { try { step(generator.next(value)); } catch (e) { reject(e); } }
        function rejected(value) { try { step(generator["throw"](value)); } catch (e) { reject(e); } }
        function step(result) { result.done ? resolve(result.value) : adopt(result.value).then(fulfilled, rejected); }
        step((generator = generator.apply(thisArg, _arguments || [])).next());
    });
};
Object.defineProperty(exports, "__esModule", { value: true });
exports.SpeakWindow = void 0;
const react_1 = __importStar(require("react"));
const react_bootstrap_1 = require("react-bootstrap");
const SpeakWindow = () => {
    const audioPlayer = (0, react_1.useRef)(null);
    const [value, setValue] = (0, react_1.useState)("");
    const [phonemeEnable, setPhonemeEnable] = (0, react_1.useState)(true);
    const [audioFile, setAudioFile] = (0, react_1.useState)("");
    const [isLoading, setIsLoading] = (0, react_1.useState)(false);
    const [emscripten, setEmscriptenEnvironment] = (0, react_1.useState)(null);
    const getSay = () => __awaiter(void 0, void 0, void 0, function* () {
        if (emscripten)
            return emscripten;
        const env = yield say();
        setEmscriptenEnvironment(env);
        return env;
    });
    const commit = () => __awaiter(void 0, void 0, void 0, function* () {
        var _a, _b, _c;
        setIsLoading(true);
        const dectalk = yield getSay();
        const outputFileName = Date.now() + ".wav";
        let input = "";
        if (phonemeEnable) {
            input += "[:phone on]\n";
        }
        input += value;
        dectalk.callMain([outputFileName, input]);
        const buffer = dectalk.FS.readFile(outputFileName);
        const blob = new Blob([buffer], { type: "audio/x-wav" });
        // Pause the audio player if it is playing...
        (_a = audioPlayer.current) === null || _a === void 0 ? void 0 : _a.pause();
        // Create a blob URL and reload it if
        setAudioFile(URL.createObjectURL(blob));
        (_b = audioPlayer.current) === null || _b === void 0 ? void 0 : _b.load();
        (_c = audioPlayer.current) === null || _c === void 0 ? void 0 : _c.play();
        setIsLoading(false);
    });
    return (<react_bootstrap_1.Form as="div" className="py-4">
      <react_bootstrap_1.Form.Group className="mb-3" controlId="SpeakWindow.Phoneme">
        <react_bootstrap_1.Form.Label>Enable Phonemes</react_bootstrap_1.Form.Label>
        <react_bootstrap_1.Form.Check checked={phonemeEnable} onChange={(e) => setPhonemeEnable(e.target.checked)} disabled={isLoading}/>
        <react_bootstrap_1.Form.Text muted>
          This option configures whether <code>[:phone on]</code> is prefixed to your input, for singing.
        </react_bootstrap_1.Form.Text>
      </react_bootstrap_1.Form.Group>
      <react_bootstrap_1.Form.Group className="mb-3" controlId="SpeakWindow.Text">
        <react_bootstrap_1.Form.Label>DECtalk Input</react_bootstrap_1.Form.Label>
        <react_bootstrap_1.Form.Control as="textarea" rows={12} value={value} onChange={(e) => setValue(e.target.value)} disabled={isLoading}/>
      </react_bootstrap_1.Form.Group>
      <react_bootstrap_1.Button variant="primary" type="submit" disabled={isLoading} onClick={commit}>
        Submit
      </react_bootstrap_1.Button>

      <react_bootstrap_1.Form.Group className="py-4" style={audioFile ? {} : { visibility: "hidden" }}>
        <audio ref={audioPlayer} controls>
          {audioFile && <source src={audioFile} type="audio/x-wav"/>}
        </audio>
      </react_bootstrap_1.Form.Group>
    </react_bootstrap_1.Form>);
    // <main>
    //     <textarea
    //       value={value}
    //       onChange={(e) => setValue(e.target.value)}
    //     ></textarea>
    //     <button onClick={commit}>Commit</button>
    // <audio ref={audioPlayer} controls>
    //   {audioFile && <source src={audioFile} type="audio/x-wav" />}
    // </audio>
    //   </main>
};
exports.SpeakWindow = SpeakWindow;
