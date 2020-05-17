#include "synchrogear.h"

std::string sync2string(const synchrogear sg)
noexcept
{
  switch (sg)
  {
    case synchrogear::silence:
      return "silence.wav";
      break;
    case synchrogear::drum:
      return "drum.wav";
      break;
    case synchrogear::bass_e_5:
      return "bass_e_5.wav";
      break;
    case synchrogear::bass_f_5:
      return "bass_f_5.wav";
      break;
    case synchrogear::bass_g_5:
      return "bass_g_5.wav";
      break;
    case synchrogear::bass_a_5:
      return "bass_a_5.wav";
      break;
    case synchrogear::stick_1a:
      return "stick_1a.wav";
      break;
    case synchrogear::stick_1b:
      return "stick_1b.wav";
      break;
    case synchrogear::synth_1_e_5_:
      return "synth_1_e_5_.wav";
      break;
    case synchrogear::synth_1_f_5:
      return "synth_1_f_5.wav";
      break;
    case synchrogear::synth_1_g_5:
      return "synth_1_g_5.wav";
      break;
    case synchrogear::synth_1_a_5:
      return "synth_1_a_5.wav";
      break;
    case synchrogear::synth_1_c_6:
      return "synth_1_c_6.wav";
      break;
  }

  return "silence.wav";
}
