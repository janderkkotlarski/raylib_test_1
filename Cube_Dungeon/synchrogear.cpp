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

std::vector <synchrogear> silence_loop()
noexcept
{
  return std::vector <synchrogear>
  {
    synchrogear::silence, synchrogear::silence, synchrogear::silence, synchrogear::silence,
    synchrogear::silence, synchrogear::silence, synchrogear::silence, synchrogear::silence,
    synchrogear::silence, synchrogear::silence, synchrogear::silence, synchrogear::silence,
    synchrogear::silence, synchrogear::silence, synchrogear::silence, synchrogear::silence
  };
}

std::vector <synchrogear> drum_loop_1()
noexcept
{
  return std::vector <synchrogear>
  {
    synchrogear::drum, synchrogear::drum, synchrogear::drum, synchrogear::drum,
    synchrogear::drum, synchrogear::drum, synchrogear::drum, synchrogear::drum,
    synchrogear::drum, synchrogear::drum, synchrogear::drum, synchrogear::drum,
    synchrogear::drum, synchrogear::drum, synchrogear::drum, synchrogear::drum
  };
}

std::vector <synchrogear> drum_track()
noexcept
{
  std::vector <synchrogear> track
  { drum_loop_1() };

  for (const synchrogear note: drum_loop_1())
  { track.push_back(note); }

  return track;
}

std::vector <synchrogear> bass_loop_1()
noexcept
{
  return std::vector <synchrogear>
  {
    synchrogear::bass_g_5, synchrogear::bass_g_5, synchrogear::bass_g_5, synchrogear::bass_g_5,
    synchrogear::bass_g_5, synchrogear::bass_g_5, synchrogear::bass_g_5, synchrogear::bass_g_5,
    synchrogear::bass_a_5, synchrogear::bass_a_5, synchrogear::bass_a_5, synchrogear::bass_a_5,
    synchrogear::bass_f_5, synchrogear::bass_f_5, synchrogear::bass_e_5, synchrogear::bass_e_5
  };
}

std::vector <synchrogear> bass_track()
noexcept
{
  std::vector <synchrogear> track
  { bass_loop_1() };

  for (const synchrogear note: bass_loop_1())
  { track.push_back(note); }

  return track;
}

std::vector <synchrogear> stick_loop_1()
noexcept
{
  return std::vector <synchrogear>
  {
    synchrogear::stick_1a, synchrogear::stick_1a, synchrogear::stick_1a, synchrogear::stick_1b,
    synchrogear::stick_1a, synchrogear::stick_1a, synchrogear::stick_1a, synchrogear::stick_1b,
    synchrogear::stick_1a, synchrogear::stick_1a, synchrogear::stick_1a, synchrogear::stick_1b,
    synchrogear::stick_1a, synchrogear::stick_1a, synchrogear::stick_1a, synchrogear::stick_1b
  };
}

std::vector <synchrogear> stick_track()
noexcept
{
  std::vector <synchrogear> track
  { stick_loop_1() };

  for (const synchrogear note: stick_loop_1())
  { track.push_back(note); }

  return track;
}

std::vector <synchrogear> synth_1_loop_1()
noexcept
{
  return std::vector <synchrogear>
  {
    synchrogear::synth_1_a_5, synchrogear::silence, synchrogear::silence, synchrogear::silence,
    synchrogear::synth_1_c_6, synchrogear::silence, synchrogear::silence, synchrogear::silence,
    synchrogear::synth_1_g_5, synchrogear::silence, synchrogear::silence, synchrogear::silence,
    synchrogear::synth_1_f_5, synchrogear::synth_1_e_5_, synchrogear::silence, synchrogear::silence
  };
}

std::vector <synchrogear> synth_1_track()
noexcept
{
  std::vector <synchrogear> track
  { synth_1_loop_1() };

  for (const synchrogear note: synth_1_loop_1())
  { track.push_back(note); }

  return track;
}

std::vector <std::vector <synchrogear>> music_tracks_generator()
noexcept
{
  return std::vector <std::vector <synchrogear>>
  { drum_track(), bass_track(), stick_track(), synth_1_track() };
}

void play_tracks(std::vector <Sound> &track_samples,
                 const std::vector <std::vector <synchrogear>> &music_tracks,
                 unsigned &track_index,
                 const unsigned begin_index)
noexcept
{
  for (unsigned sample_index{ begin_index }; sample_index < track_samples.size(); ++sample_index)
  {
    if (music_tracks[sample_index][track_index] != synchrogear::silence)
    { PlaySoundMulti(track_samples[sample_index]); }
  }

  ++track_index;

  if (track_index >= music_tracks[0].size())
  { track_index = 0; }

  for (unsigned sample_index{ 0 }; sample_index < track_samples.size(); ++sample_index)
  { track_samples[sample_index] = LoadSound(sync2string(music_tracks[sample_index][track_index]).c_str()); }
}
