#include "dungeon_loop.h"

#include <cassert>
#include <iostream>
#include <time.h>

#define RLIGHTS_IMPLEMENTATION
#include <rlights.h>

#include "keybindings.h"
#include "dungeon_maze.h"

dungeon_loop::dungeon_loop()
noexcept
  :  m_type_volume(), m_fracta_cube(), m_int_vectors()
/// Set up the loop
{
  assert(m_directions.size() == 3);

  // acid_trip(m_cam_angle_average, m_cam_angle_deviation, m_cam_angle, m_dark_opacity);

  dungeon_init(m_type_volume, m_max_dungeon_radius);
}

void dungeon_loop::camera_position(Camera &camera)
noexcept
/// Hang the camera in the right position.
{ camera.position = vector2vector3(vector_subtract(m_position, vector_scale(m_directions[0], 0.25f))); }

void dungeon_loop::camera_init(Camera &camera)
noexcept
/// Initialize the camera.
{
  camera_position(camera); // Camera position
  camera.target = vector2vector3(vector_add(m_position, m_directions[0])); // std::vector <float>Add(camera.position, forward);      // Camera looking at point
  camera.up = vector2vector3(m_directions[2]);          // Camera up vector (rotation towards target)
  camera.fovy = m_cam_angle;                                // Camera field-of-view Y
  camera.type = CAMERA_PERSPECTIVE; // Camera mode type

  SetCameraMode(camera, CAMERA_FIRST_PERSON);

  SetTargetFPS(fps);
}

void dungeon_loop::player_init()
noexcept
/// Initialize all things pertaining to the player.
{
  if (m_level <= 2)
  { m_start_posit = (std::vector <float>){ 2.0f, 0.0f, 0.0f }; }

  if (m_level >= 3)
  { m_start_posit = (std::vector <float>){ 1.0f - (float)m_dungeon_radius, 0.0f, 0.0f }; }

  m_directions = m_start_directs;

  m_position = m_start_posit;
}

void dungeon_loop::level_init()
noexcept
/// Level initialization.
{  
  m_loop = true;

  if (!m_reset)
  { ++m_level; }

  if (m_level >= 3)
  {
    m_dungeon_radius = 6 + 2*m_level;
    m_wall_perc = 40 + m_level;
  }

  m_reset = false;

  if (m_level > m_end_level)
  {
    m_loop = false;
    m_game = false;
  }

  m_dungeon_span = 2*m_dungeon_radius + 1;
  m_wrap = m_dungeon_radius + 0.5f;

  m_dungeon_middle = { m_dungeon_radius, m_dungeon_radius, m_dungeon_radius };

  player_init();
}

void dungeon_loop::perform_action()
noexcept
/// Choose what to based on the current action.
{
  m_position = vector_add(m_position, vector_scale(m_movement, m_velocity));

  switch (m_act)
  {
    case action::forward:
      m_hale_scale -= GetFrameTime()/m_period;
      break;
    case action::backward:
      m_hale_scale -= GetFrameTime()/m_period;
      break;
    case action::right:
      m_hale_scale -= GetFrameTime()/m_period;
      break;
    case action::left:
      m_hale_scale -= GetFrameTime()/m_period;
      break;
    case action::up:
      m_hale_scale -= GetFrameTime()/m_period;
      break;
    case action::down:
      m_hale_scale -= GetFrameTime()/m_period;
      break;

    case action::rotate_right:
      rotate_first_second(m_directions[0], m_directions[1], m_theta);
      break;
    case action::rotate_left:
      rotate_first_second(m_directions[1], m_directions[0], m_theta);
      break;
    case action::rotate_up:
      rotate_first_second(m_directions[0], m_directions[2], m_theta);
      break;
    case action::rotate_down:
      rotate_first_second(m_directions[2], m_directions[0], m_theta);
      break;
    case action::roll_right:
      rotate_first_second(m_directions[2], m_directions[1], m_theta);
      break;
    case action::roll_left:
      rotate_first_second(m_directions[1], m_directions[2], m_theta);
      break;

    case action::inhale:
      m_hale_scale -= GetFrameTime()/m_period;
      break;

    case action::exhale:
      m_hale_scale += GetFrameTime()/m_period;
      break;

    case action::none:
      m_hale_scale = 1.0f;
      break;

    case action::catalyze:
      break;
  }
}

int dungeon_loop::dungeon_wrap(const int coord)
noexcept
/// When a coordinate falls outside the scope, bring it back on the other side.
{
  int index = coord;

  while (index < -m_dungeon_radius)
  {
    // index += m_dungeon_span;
    index = 0;
  }

  while (index > m_dungeon_radius)
  {
    // index -= m_dungeon_span;
    index = 0;
  }

  return index;
}

unsigned dungeon_loop::dungeon_warp(const int coord)
noexcept
/// When a coordinate falls outside the scope, bring it back on the other side.
{
  unsigned index = coord;

  while (index < 0)
  { index += m_dungeon_span; }

  while (index >= m_dungeon_span)
  { index -= m_dungeon_span; }

  return index;
}

int dungeon_loop::coordinator(const float pos)
noexcept
/// Determine the int coordinate from the float position
{ return int(round(pos)) + m_dungeon_radius; }

std::vector <std::vector <int>> dungeon_loop::director()
noexcept
/// Returns the initial directions of movement.
{
  std::vector <std::vector <int>> directs;

  for (const std::vector <float> &direction: m_directions)
  {
    std::vector <int> direct;

    for (const float num: direction)
    { direct.push_back(int(round(num))); }

    directs.push_back(direct);
  }

  assert(directs.size() == m_directions.size());

  return directs;
}

void dungeon_loop::play_actions(std::vector <Sound> &track_samples)
noexcept
{
  
  m_cube_dungeon_pos = vector_float2int(m_position);

  if (m_act == action::none)
  {
    m_act = key_bind_actions();
    gamepad_actions(m_act);

    if (m_act != action::none)
    {
      m_movement = action2direction(m_directions, m_act);


      m_destination = vector_add(m_position, m_movement);

      for (float &part: m_destination)
      { part = dungeon_wrap(part); }

      m_destint = vector_float2int(m_destination);

      if (type_collision(m_type_volume[m_destint[0]]
                                      [m_destint[1]]
                                      [m_destint[2]]))
      {
        m_act = action::none;

        m_movement = { 0.0f, 0.0f, 0.0f };
      }

      m_movemint = vector_float2int(m_movement);

      m_destination = vector_add(m_position, m_movement);

      for (float &part: m_destination)
      { part = dungeon_wrap(part); }

      m_destint = vector_float2int(m_destination);

      unsigned count
      { 0 };

      std::vector <int> dungeon_index;

      for (const float num: m_position)
      {
        dungeon_index.push_back(int(round(num + m_directions[0][count])) + m_dungeon_radius);
        ++count;
      }

      if (m_act == action::inhale &&
          (m_internal_type != cube_type::none ||
           m_type_volume[dungeon_index[0]]
                        [dungeon_index[1]]
                        [dungeon_index[2]] == cube_type::concrete ||
           m_type_volume[dungeon_index[0]]
                        [dungeon_index[1]]
                        [dungeon_index[2]] == cube_type::invisible))
         { m_act = action::none; }

      if (m_act == action::exhale)
      {
        if (m_internal_type != cube_type::none &&
            m_type_volume[dungeon_index[0]]
                         [dungeon_index[1]]
                         [dungeon_index[2]] == cube_type::none)
        {
          m_hale_scale = 0.0f;

          m_type_volume[dungeon_index[0]]
                       [dungeon_index[1]]
                       [dungeon_index[2]] = m_internal_type;

          m_internal_type = cube_type::none;
        }
        else
        { m_act = action::none; }
      }
    }

    if (m_synchro)
    {
      if (m_act == action::forward ||
          m_act == action::backward ||
          m_act == action::right ||
          m_act == action::left ||
          m_act == action::up ||
          m_act == action::down)
      { play_tracks(track_samples, m_music_tracks, m_track_index, 0); }

      if (m_act == action::rotate_right ||
          m_act == action::rotate_left ||
          m_act == action::rotate_up ||
          m_act == action::rotate_down ||
          m_act == action::roll_right ||
          m_act == action::roll_left)
      { play_tracks(track_samples, m_music_tracks, m_track_index, 1); }
    }

    m_time = 0.0f;
  }

  m_delta_time = GetFrameTime();

  if (m_act != action::none)
  {
    m_time += m_delta_time;

    if (m_time >= m_period)
    {      
      for (float &num: m_position)
      { num = round(num); }

      for (std::vector <float> &direction: m_directions)
      {        
        for (float &num: direction)
        { num = round(num); }
      }

      if (m_act == action::inhale &&
          m_internal_type == cube_type::none)
      {
        unsigned count
        { 0 };

        std::vector <int> dungeon_index;

        for (const int num: m_position)
        {
          dungeon_index.push_back(int(round(num + m_directions[0][count])) + m_dungeon_radius);
          ++count;
        }

        m_internal_type =  m_type_volume[dungeon_index[0]]
                                        [dungeon_index[1]]
                                        [dungeon_index[2]];

        m_type_volume[dungeon_index[0]]
                     [dungeon_index[1]]
                     [dungeon_index[2]] = cube_type::none;
      }

      if (m_movement != std::vector <float> { 0.0f, 0.0f, 0.0f })
      {
        std::vector <int> moved_to
        { vector_float2int(m_position) };

        for (int &num: moved_to)
        { num += m_dungeon_radius; }

        if (m_type_volume[moved_to[0]]
                         [moved_to[1]]
                         [moved_to[2]] == cube_type::next)
        { m_loop = false; }

        m_type_volume[moved_to[0]]
                     [moved_to[1]]
                     [moved_to[2]] = cube_type::none;
      }

      m_act = action::none;

      m_collide_type = cube_type::none;

      m_movement = { 0.0f, 0.0f, 0.0f };

      m_movemint = vector_float2int(m_movement);

      m_destination = vector_add(m_position, m_movement);

      for (float &part: m_destination)
      { part = dungeon_wrap(part); }

      m_destint = vector_float2int(m_destination);
    }
  }
}

void dungeon_loop::other_actions()
noexcept
{
  if (IsKeyReleased(KEY_BACKSPACE) ||
      IsGamepadButtonReleased(GAMEPAD_PLAYER1, GAMEPAD_BUTTON_MIDDLE_RIGHT))
  {
    m_loop = false;
    m_reset = true;
    m_act = action::none;
  }

  if (WindowShouldClose() ||
      IsGamepadButtonDown(GAMEPAD_PLAYER1, GAMEPAD_BUTTON_MIDDLE_LEFT))
  {
    m_loop = false;
    m_game = false;
    m_act = action::none;
  }

  if (m_act == action::none &&
      m_type_volume[m_cube_dungeon_pos[0]]
                   [m_cube_dungeon_pos[1]]
                   [m_cube_dungeon_pos[2]] == cube_type::next)
  { m_loop = false; }

  if (m_act == action::none &&
      m_type_volume[m_cube_dungeon_pos[0]]
                   [m_cube_dungeon_pos[1]]
                   [m_cube_dungeon_pos[2]] == cube_type::setback)
  {
    m_type_volume[m_cube_dungeon_pos[0]]
                 [m_cube_dungeon_pos[1]]
                 [m_cube_dungeon_pos[2]] = cube_type::none;

    player_init();
  }  
}

void dungeon_loop::test_cheats()
noexcept
{
  if (IsKeyReleased(KEY_RIGHT_BRACKET))
  { m_loop = false; }

  if (IsKeyReleased(KEY_LEFT_BRACKET))
  {
    m_loop = false;

    m_level -= 2;

    if (m_level < 0)
    { m_level = 0; }
  }
}

void dungeon_loop::player_move(Camera &camera)
noexcept
{
  m_velocity = m_delta_time*m_speed;
  m_theta = m_delta_time*m_angle;

  spectral_shift(m_spectral_profile, m_delta_time);

  chromatic_shift(m_chromatic_profile, m_delta_time);

  perform_action();
  wrapping(m_position, m_wrap);

  camera_position(camera);
  camera.target = vector2vector3(vector_add(m_position, m_directions[0]));
  camera.up = vector2vector3(m_directions[2]);
  camera.fovy = m_cam_angle;
}

void dungeon_loop::infos()
noexcept
{
  const int x
  { 20 };
  int y
  { 20 };
  const int size
  { 20 };

  display_string("Level ", std::to_string(m_level), x, y, size);

  y += 30;

  display_string("FPS: ", std::to_string(GetFPS()), x, y, size);

  y += 30;

  display_string("Pos: ", vector2string(m_position), x, y, size);

  y += 30;

  const std::string collide_pos
  {
    "[" + std::to_string(m_direction_shift[0]) +
    "][" + std::to_string(m_direction_shift[1]) +
    "][" + std::to_string(m_direction_shift[2]) + "]"
  };

  display_string("Col: ", collide_pos, x, y, size);

  y += 30;

  display_string("Action: ", action2string(m_act), x, y, size);

  y += 30;

  display_string("Scale: ", std::to_string(m_hale_scale), x, y, size);

  y += 30;

  std::vector <float> direction
  { action2direction(m_directions, m_act) };

  const std::string direction_string
  { vector2string(direction) };

  display_string("Direction: ", direction_string, x, y, size);

  y += 30;

  display_string("Collide type: ",type2string(m_collide_type), x, y, size);
}

void dungeon_loop::coord_transform(const std::vector <int> &counters,
                                   const int index)
noexcept
{
  m_coord_int[index] = m_pos_int[index] + counters[index];
  m_index_int[index] = dungeon_wrap(m_coord_int[index]);
}

void dungeon_loop::frame_update(std::vector <Model> &cube_models)
noexcept
{
  ++m_frame;

  if (m_frame >= m_frames)
  {
    m_frame = 0;

    ++m_cube_index;

    if (m_cube_index >= cube_models.size())
    { m_cube_index = 0; }
  }
}

void dungeon_loop::cube_drawing(std::vector <Model> &cube_models,
                                std::vector <Model> &dark_models,
                                Model &model)
noexcept
{
  m_pos_int = vector_float2int(m_position);

  unsigned index
  { 0 };

  std::vector <int> counters
  { -m_horizon,  -m_horizon,  -m_horizon};

  for (; counters[index] <= m_horizon; ++counters[index])
  {
    coord_transform(counters, index);

    ++index;

    for (; counters[index] <= m_horizon; ++counters[index])
    {
      coord_transform(counters, index);

      ++index;

      for (; counters[index] <= m_horizon; ++counters[index])
      {
        coord_transform(counters, index);

        const std::vector <int> dungeon_pos;

        std::vector <int> dungeon_index;

        for (const int num: m_index_int)
        { dungeon_index.push_back(num + m_dungeon_radius); }

        const cube_type c_type
        { m_type_volume[dungeon_index[0]]
                       [dungeon_index[1]]
                       [dungeon_index[2]] };

        if (c_type != cube_type::none &&
            c_type != cube_type::invisible &&
            c_type != cube_type::transparent)
        {
          m_fracta_cube.set_pos_type(m_coord_int[0], m_coord_int[1], m_coord_int[2], c_type);

          const unsigned c_index
          { type2index(c_type) };

          if (display_selector(m_position,
                               m_fracta_cube.get_position(),
                               m_directions[0], m_cam_field))
          {
            if (index != 42)
            {    
              if (((m_act == action::inhale ||
                   m_act == action::exhale) &&
                  counters[0] == (int)m_directions[0][0] &&
                  counters[1] == (int)m_directions[0][1] &&
                  counters[2] == (int)m_directions[0][2]) ||
                  (m_collide_type == cube_type::ruby &&
                   dungeon_index == m_destint))
              { m_fracta_cube.display(cube_models[c_index], dark_models[c_index], m_hale_scale); }
              else
              { m_fracta_cube.display(cube_models[c_index], dark_models[c_index], 1.0f); }
            }
          }
        }
      }

      counters[index] = -m_horizon;
      --index;
    }

    counters[index] = -m_horizon;
    --index;
  }
}

void dungeon_loop::transition()
noexcept
{
  m_screen_opacity = 0.0f;

  if (transit(m_collide_type))
  {
    m_screen_opacity = m_time/m_period;

    Color screen_color
    { profile2color(m_chromatic_profile) };

    scale_color(screen_color, m_light_intensity);
    scale_color(screen_color, 1.5f);

    change_opacity(screen_color, 4.0f*m_screen_opacity);

    for (int count{ 0 }; count < 3; ++count)
    { DrawRectangle(0, 0, m_screen_width, m_screen_height, screen_color); }
  }

  candy_blink(m_candy_factor, m_delta_time, m_candy_up);

  dark_shift(m_cube_vein_profile, m_delta_time, m_dark_opacity, m_dark_up);

  // acid_trip(m_cam_angle_average, m_cam_angle_deviation, m_cam_angle, m_dark_opacity);

  // DrawRectangle(0, 0, m_screen_width, m_screen_height, m_dark_color);
}

void dungeon_loop::game_loop(Camera &camera, std::vector <Model> &cube_models, std::vector <Model> &dark_models,
                             Model &model,
                             std::vector <Shader> &fog_shaders, std::vector <Shader> &dark_shaders,
                             Shader &shader,
                             const int fog_density_loc,
                             std::vector <Sound> &track_samples)
noexcept
{
  while (m_game)
  {
    level_init();
    dungeon_filler(m_type_volume, m_level, m_dungeon_radius);
    single_placements(m_type_volume, m_level, m_dungeon_radius);

    while (m_loop)
    {
      player_move(camera);
      play_actions(track_samples);

      refresh_fogs(cube_models, fog_shaders, m_position,
                   m_spectral_profile, m_chromatic_profile, m_candy_factor,
                   m_fog_density_loc, m_fog_density);

      refresh_darks(dark_models, dark_shaders, m_position,
                   m_cube_vein_profile, m_fog_density_loc, m_fog_density);

      std::vector <float> ambient_profile
      { m_spectral_profile };

      fog_refresh(shader, m_position, ambient_profile, m_fog_density_loc, m_fog_density);

      BeginDrawing();
      {
        ClearBackground(BLACK);

        BeginMode3D(camera);        
        { cube_drawing(cube_models, dark_models, model); }

        EndMode3D();

        if (m_test)
        { infos(); }

        transition();

        infos();
      }

      EndDrawing();

      other_actions();
      test_cheats();
    }
  }
}

void dungeon_loop::run_window()
{
  InitWindow(m_screen_width, m_screen_height, "Cube Dungeon");

  InitAudioDevice();

  std::string temp
  { "" };

  std::vector <Sound> track_samples;

  for (const std::vector <synchrogear> &music_track: m_music_tracks)
  { track_samples.push_back(LoadSound(sync2string(music_track[m_track_index]).c_str())); }

  const std::string file_name
  { "cube_face_" };

  std::string file_type
  { ".png" };

  std::vector <Model> cube_models;

  std::vector <Image> face_images;

  std::vector <Shader> fog_shaders;

  init_cubes_images_fogs(cube_models, face_images, fog_shaders, m_position, m_ambient_profile,
                         m_fracta_cube, file_name, file_type, m_fog_density_loc, m_fog_density, false);

  file_type = "_.png";

  std::vector <Model> dark_models;

  std::vector <Image> dark_images;

  std::vector <Shader> dark_shaders;

  init_cubes_images_fogs(dark_models, dark_images, dark_shaders, m_position, m_ambient_profile,
                         m_fracta_cube, file_name, file_type, m_dark_density_loc, m_fog_density, true);

  Model c_model
  { LoadModelFromMesh(GenMeshCube(m_fracta_cube.get_cube_dims()[0],
                                  m_fracta_cube.get_cube_dims()[1],
                                  m_fracta_cube.get_cube_dims()[2])) };

  c_model.materials[0].maps[MAP_DIFFUSE].texture = LoadTexture("cube_face_0.png");

  Shader f_shader
  { LoadShader(FormatText("base_lighting.vs", GLSL_VERSION),
               FormatText("dark_fog.fs", GLSL_VERSION)) };

  f_shader.locs[LOC_MATRIX_MODEL] = GetShaderLocation(f_shader, "matModel");
  f_shader.locs[LOC_VECTOR_VIEW] = GetShaderLocation(f_shader, "viewPos");


  const std::vector <float> ambi_profile
  { 1.0f, 1.0f, 1.0f, 1.0f };

  float ambient_profile[4]
  { 0.0f, 1.0f, 1.0f, 1.0f };

  vector2array_float(ambi_profile, ambient_profile);

  const int ambientLoc = GetShaderLocation(f_shader, "ambient");
  SetShaderValue(f_shader, ambientLoc, ambient_profile, UNIFORM_VEC4);

  const int fog_density_loc
  { GetShaderLocation(f_shader, "fogDensity") };
  SetShaderValue(f_shader, fog_density_loc, &m_fog_density, UNIFORM_FLOAT);

  c_model.materials[0].shader = f_shader;


  Camera3D camera;
  camera_init(camera);

  game_loop(camera, cube_models, dark_models, c_model,
            fog_shaders, dark_shaders, f_shader, fog_density_loc,
            track_samples);

  // UnloadShader(distortion);

  CloseVrSimulator();         // Close VR simulator

  CloseWindow();
}
