"use strict";
var __importDefault = (this && this.__importDefault) || function (mod) {
    return (mod && mod.__esModule) ? mod : { "default": mod };
};
Object.defineProperty(exports, "__esModule", { value: true });
exports.App = void 0;
const react_1 = __importDefault(require("react"));
const react_bootstrap_1 = require("react-bootstrap");
const react_bootstrap_2 = require("react-bootstrap");
const SpeakNavbar_1 = require("./components/SpeakNavbar");
const SpeakWindow_1 = require("./components/SpeakWindow");
const App = () => {
    return (<react_bootstrap_2.ThemeProvider>
      <SpeakNavbar_1.SpeakNavbar />
      <react_bootstrap_1.Container>
        <react_bootstrap_2.Row>
          <react_bootstrap_2.Col>
            <SpeakWindow_1.SpeakWindow />
          </react_bootstrap_2.Col>
        </react_bootstrap_2.Row>
      </react_bootstrap_1.Container>
    </react_bootstrap_2.ThemeProvider>);
};
exports.App = App;
