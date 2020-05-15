#include "synchrogear.h"

std::string sync2string(const synchrogear sg)
noexcept
{
  switch (sg)
  {
    case synchrogear::silence:
      return "";
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
  }

  return "";
}
