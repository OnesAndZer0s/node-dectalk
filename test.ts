import { DecTalk, WaveFormat, TTSBuffer, DeviceID, DeviceManagement, Message } from "./src";
var talk = new DecTalk();
var buf = new TTSBuffer( {
  data: 8192,
  phoneme: 256,
  index: 256
} );

console.log( talk.startup( DeviceID.Mapper, DeviceManagement.DoNotUseAudioDevice, ( msg: Message, other: any ) => {
  switch ( msg ) {
    case Message.Buffer:
      console.log( "Buffer", other );
      talk.addBuffer( other as TTSBuffer );
      break;
    case Message.Status:
      console.log( "Status" );
      break;
    case Message.IndexMark:
      console.log( "IndexMark" );
      break;
    case Message.Visual:
      console.log( "Visual" );
      break;

    default:
      console.log( "Unknown: " + msg );
  }
} ) );

console.log( talk.openInMemory( WaveFormat.Format1M16 ) );

console.log( talk.addBuffer( buf ) );
console.log( talk.speakSync( "a" ) );

// // talk.speak(
// //   [
// //     "[:phoneme on]",
// //     "[sow<150,28>ay<150,28>wwey<300,37>kkih<150,37>nnth<20>uh<150,37>mor<200,33>nnihn<100,33>ae<150,33>nndday<150,33>ssteh<200,28>pp]",
// //     "[aw<300,28>ttssah<150,26>ay<150,25>ddae<200,25>nday<150,25>ttey<150,26>kkuh<150,26>ddiy<150,37>ppbr<20>eh<300,35>thae<300,33>]",
// //     "[ndgeh<300,35>ttrih<300,37>llhxay<300,33>ae<150,33>nnay<150,33>sk<150,33>rEy<150,33>m<150,33>_<150>tuh<150,33>tteh<150,33>ttaw<150,33>ppuh<150,33>]",
// //     "[ffmaa<200,33>lluh<300,33>nngs<150,35>_<150>wah<300,35>ssgow<150,35>ih<300,37>ngaw<450,33>nn<300,33>_<1200>]",
// //     "[ae<150,28>nnday<300,30>ssae<300,28>_<300>hxeh<750,37>ey<200,33>eh<750,33>ey<200,28>eh<750,28>ey<400,26>ey<400,25>_<100>]",
// //     "[hxeh<750,37>ey<200,33>eh<750,33>ey<200,26>eh<750,26>_<750>ay<150,35>sseh<200,37>hxeh<300,33>eh<300,30>_<1800>]",
// //     "[wwah<300,35>ttsgow<300,35>ih<400,37>nnaw<300,33>nn<90>]"
// //   ]
// // );
console.log( talk.syncSync() );