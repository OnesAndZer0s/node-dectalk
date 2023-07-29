import { DecTalk } from "./src";

var talk = new DecTalk();
talk.startup();
talk.speak(
  [
    "[:phoneme on]",
    // "[sow<150,28>ay<150,28>kkray<300,37>ssuh<300,37>mmttay<300,33>mms<50>wweh<150,33>nnay<150,33>mm<50>llay<150,28>ihnn<150,28>]",
    // "[ih<150,28>nnbeh<150,27>eh<300,25>dd<50>_<100>guh<100,26>sstuw<150,26>geh<150,37>teht<100,37>ah<200,37>ll<50,37>luh<150,37>tt<100,37>_<100>wah<150,33>tts<50>ih<150,35>]",
    // "[mah<300,37>hxae<300,33>dd<50>ae<150,33>dd<50>ay<300,33>mm<10>ffiy<150,33>llih<150,35>nnPeh<150,28>kkuw<300,26>llyur<300,25>_<2000>]",
    "[sow<150,28>ay<150,28>wwey<300,37>kkih<150,37>nnth<20>uh<150,37>mor<200,33>nnihn<100,33>ae<150,33>nndday<150,33>ssteh<200,28>pp]",
    "[aw<300,28>ttssah<150,26>ay<150,25>ddae<200,25>nday<150,25>ttey<150,26>kkuh<150,26>ddiy<150,37>ppbr<20>eh<300,35>thae<300,33>]",
    "[ndgeh<300,35>ttrih<300,37>llhxay<300,33>ae<150,33>nnay<150,33>sk<150,33>rEy<150,33>m<150,33>_<150>tuh<150,33>tteh<150,33>ttaw<150,33>ppuh<150,33>]",
    "[ffmaa<200,33>lluh<300,33>nngs<150,35>_<150>wah<300,35>ssgow<150,35>ih<300,37>ngaw<450,33>nn<300,33>_<1200>]",
    "[ae<150,28>nnday<300,30>ssae<300,28>_<300>hxeh<750,37>ey<200,33>eh<750,33>ey<200,28>eh<750,28>ey<400,26>ey<400,25>_<100>]",
    "[hxeh<750,37>ey<200,33>eh<750,33>ey<200,26>eh<750,26>_<750>ay<150,35>sseh<200,37>hxeh<300,33>eh<300,30>_<1800>]",
    "[wwah<300,35>ttsgow<300,35>ih<400,37>nnaw<300,33>nn<90>]"



  ]
);
talk.sync();