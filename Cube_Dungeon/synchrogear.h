#ifndef SYNCHROGEAR_H
#define SYNCHROGEAR_H

#include <string>

enum class synchrogear
{
  silence,
  drum,
  bass_e_5,
  bass_f_5,
  bass_g_5,
  bass_a_5,
  stick_1a,
  stick_1b,
  synth_1_e_5_,
  synth_1_f_5,
  synth_1_g_5,
  synth_1_a_5,
  synth_1_c_6
};

std::string sync2string(const synchrogear sg)
noexcept;

#endif // SYNCHROGEAR_H
