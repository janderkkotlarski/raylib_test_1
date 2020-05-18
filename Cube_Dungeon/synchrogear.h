#ifndef SYNCHROGEAR_H
#define SYNCHROGEAR_H

#include <string>
#include <vector>

#include <raylib.h>

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

std::vector <synchrogear> silence_loop()
noexcept;

std::vector <synchrogear> drum_loop_1()
noexcept;

std::vector <synchrogear> drum_track()
noexcept;

std::vector <synchrogear> bass_loop_1()
noexcept;

std::vector <synchrogear> bass_track()
noexcept;

std::vector <synchrogear> stick_loop_1()
noexcept;

std::vector <synchrogear> stick_track()
noexcept;

std::vector <synchrogear> synth_1_loop_1()
noexcept;

std::vector <synchrogear> synth_1_track()
noexcept;

std::vector <std::vector <synchrogear>> music_tracks_generator()
noexcept;

void play_tracks(std::vector <Sound> &track_samples,
                 const std::vector <std::vector <synchrogear>> &music_tracks,
                 unsigned &track_index,
                 const unsigned begin_index)
noexcept;

#endif // SYNCHROGEAR_H
