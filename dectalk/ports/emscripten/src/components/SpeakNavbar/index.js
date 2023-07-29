"use strict";
var __importDefault = (this && this.__importDefault) || function (mod) {
    return (mod && mod.__esModule) ? mod : { "default": mod };
};
Object.defineProperty(exports, "__esModule", { value: true });
exports.SpeakNavbar = void 0;
const react_1 = __importDefault(require("react"));
const Container_1 = __importDefault(require("react-bootstrap/Container"));
const Nav_1 = __importDefault(require("react-bootstrap/Nav"));
const Navbar_1 = __importDefault(require("react-bootstrap/Navbar"));
const SpeakNavbar = () => {
    return (<Navbar_1.default bg="light" expand="lg">
      <Container_1.default>
        <Navbar_1.default.Brand href="#home">DECtalk for Web</Navbar_1.default.Brand>
        <Navbar_1.default.Toggle aria-controls="basic-navbar-nav"/>
        <Navbar_1.default.Collapse id="basic-navbar-nav">
          <Nav_1.default className="me-auto">
            <Nav_1.default.Link href="https://github.com/dectalk/dectalk/">GitHub</Nav_1.default.Link>
            <Nav_1.default.Link href="https://discordapp.com/invite/wHgdmf4">Discord</Nav_1.default.Link>
          </Nav_1.default>
        </Navbar_1.default.Collapse>
      </Container_1.default>
    </Navbar_1.default>);
};
exports.SpeakNavbar = SpeakNavbar;
