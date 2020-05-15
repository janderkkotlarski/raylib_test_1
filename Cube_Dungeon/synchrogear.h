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
  bass_a_5
};

std::string sync2string(const synchrogear sg)
noexcept;

#endif // SYNCHROGEAR_H
