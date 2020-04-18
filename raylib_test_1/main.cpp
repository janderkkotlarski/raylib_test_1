#include <iostream>
#include <string>
#include <vector>
#include <random>

#include <raylib.h>

#include "misc_functions.h"
#include "fractacube.h"
#include "dungeon_loop.h"

#if defined(PLATFORM_DESKTOP)
    #define GLSL_VERSION            330
#else   // PLATFORM_RPI, PLATFORM_ANDROID, PLATFORM_WEB
    #define GLSL_VERSION            100
#endif


int main()
{
  // Initialization
  //--------------------------------------------------------------------------------------
  const int screenWidth = 1200;
  const int screenHeight = 600;

  // Init VR simulator (Oculus Rift CV1 parameters)


  SetConfigFlags(FLAG_MSAA_4X_HINT);// VR device parameters (head-mounted-device)

  InitWindow(screenWidth, screenHeight, "Test 1 for raylib");

  InitVrSimulator();

  VrDeviceInfo hmd = { 0 };

  // Oculus Rift CV1 parameters for simulator
  hmd.hResolution = 2000;                 // HMD horizontal resolution in pixels
  hmd.vResolution = 1200;  // 1200               // HMD vertical resolution in pixels
  hmd.hScreenSize = 0.133793f;  // 0.133793f;            // HMD horizontal size in meters
  hmd.vScreenSize = 0.0669f;              // HMD vertical size in meters
  hmd.vScreenCenter = 0.04678f;           // HMD screen center in meters
  hmd.eyeToScreenDistance = 0.041f;       // HMD distance between eye and display in meters
  hmd.lensSeparationDistance = 0.07f;     // HMD lens separation distance in meters
  hmd.interpupillaryDistance = 0.07f;     // HMD IPD (distance between pupils) in meters

  // NOTE: CV1 uses a Fresnel-hybrid-asymmetric lenses with specific distortion compute shaders.
  // Following parameters are an approximation to distortion stereo rendering but results differ from actual device.
  hmd.lensDistortionValues[0] = 1.0f;     // HMD lens distortion constant parameter 0
  hmd.lensDistortionValues[1] = 0.22f;    // HMD lens distortion constant parameter 1
  hmd.lensDistortionValues[2] = 0.24f;    // HMD lens distortion constant parameter 2
  hmd.lensDistortionValues[3] = 0.0f;     // HMD lens distortion constant parameter 3
  hmd.chromaAbCorrection[0] = 0.996f;     // HMD chromatic aberration correction parameter 0
  hmd.chromaAbCorrection[1] = -0.004f;    // HMD chromatic aberration correction parameter 1
  hmd.chromaAbCorrection[2] = 1.014f;     // HMD chromatic aberration correction parameter 2
  hmd.chromaAbCorrection[3] = 0.0f;       // HMD chromatic aberration correction parameter 3

  // Distortion shader (uses device lens distortion and chroma)
  Shader distortion = LoadShader(0, FormatText("resources/distortion%i.fs", GLSL_VERSION));

  SetVrConfiguration(hmd, distortion);    // Set Vr device parameters for stereo rendering

  SetTargetFPS(fps);  // Set our game to run at fps frames-per-second
  //--------------------------------------------------------------------------------------

  dungeon_loop d_loop;

  d_loop.run();

  UnloadShader(distortion);   // Unload distortion shader

  CloseVrSimulator();         // Close VR simulator

  CloseWindow();

  return 0;
}
