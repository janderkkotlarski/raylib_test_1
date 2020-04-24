#include "raylib.h"

#include "raymath.h"

#define RLIGHTS_IMPLEMENTATION
#include "rlights.h"

#if defined(PLATFORM_DESKTOP)
    #define GLSL_VERSION            330
#else   // PLATFORM_RPI, PLATFORM_ANDROID, PLATFORM_WEB
    #define GLSL_VERSION            100
#endif

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    SetConfigFlags(FLAG_MSAA_4X_HINT);  // Enable Multi Sampling Anti Aliasing 4x (if available)
    InitWindow(screenWidth, screenHeight, "raylib [shaders] example - fog");

    // Define the camera to look into our 3d world
    Camera camera = {
        (Vector3){ 0.0f, 0.0f, 0.0f },      // position
        (Vector3){ 1.0f, 0.0f, 0.0f },      // target
        (Vector3){ 0.0f, 1.0f, 0.0f },      // up
        45.0f, CAMERA_PERSPECTIVE };        // fov, type

    // Load models and texture
    Model modelA = LoadModelFromMesh(GenMeshTorus(0.4f, 1.0f, 16, 32));
    Model modelB = LoadModelFromMesh(GenMeshCube(1.0f, 1.0f, 1.0f));
    Model modelC = LoadModelFromMesh(GenMeshSphere(0.5f, 32, 32));

    Model model_1 = LoadModelFromMesh(GenMeshCube(1.0f, 1.0f, 1.0f));

    Texture texture = LoadTexture("C:/raylib/raylib/examples/shaders/resources/texel_checker.png");

    // Assign texture to default model material
    modelA.materials[0].maps[MAP_DIFFUSE].texture = texture;
    modelB.materials[0].maps[MAP_DIFFUSE].texture = texture;
    modelC.materials[0].maps[MAP_DIFFUSE].texture = texture;

    // Load shader and set up some uniforms
    Shader shader = LoadShader(FormatText("C:/raylib/raylib/examples/shaders/resources/shaders/glsl330/base_lighting.vs", GLSL_VERSION),
                               FormatText("C:/raylib/raylib/examples/shaders/resources/shaders/glsl330/dark_fog.fs", GLSL_VERSION));
    shader.locs[LOC_MATRIX_MODEL] = GetShaderLocation(shader, "matModel");
    shader.locs[LOC_VECTOR_VIEW] = GetShaderLocation(shader, "viewPos");

    // Ambient light level
    const float array4[4]
    { 10.0f, 10.0f, 10.0f, 1.0f };

    int ambientLoc = GetShaderLocation(shader, "ambient");
    SetShaderValue(shader, float(ambientLoc), array4, UNIFORM_VEC4); //(float[4]){ 0.2f, 0.2f, 0.2f, 1.0f }

    float fogDensity = 0.15f;
    int fogDensityLoc = GetShaderLocation(shader, "fogDensity");
    SetShaderValue(shader, fogDensityLoc, &fogDensity, UNIFORM_FLOAT);

    // NOTE: All models share the same shader
    modelA.materials[0].shader = shader;
    modelB.materials[0].shader = shader;
    modelC.materials[0].shader = shader;

    model_1.materials[0].shader = shader;

    // Using just 1 point lights
    CreateLight(LIGHT_POINT, camera.position, Vector3Zero(), BLACK, shader);

    SetCameraMode(camera, CAMERA_THIRD_PERSON);  // Set an orbital camera mode

    SetTargetFPS(60);                       // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())            // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        UpdateCamera(&camera);              // Update camera

        if (IsKeyDown(KEY_UP))
        {
            fogDensity += 0.001;
            if (fogDensity > 1.0) fogDensity = 1.0;
        }

        if (IsKeyDown(KEY_DOWN))
        {
            fogDensity -= 0.001;
            if (fogDensity < 0.0) fogDensity = 0.0;
        }

        SetShaderValue(shader, fogDensityLoc, &fogDensity, UNIFORM_FLOAT);

        // Rotate the torus
        modelA.transform = MatrixMultiply(modelA.transform, MatrixRotateX(-0.025));
        modelA.transform = MatrixMultiply(modelA.transform, MatrixRotateZ(0.012));

        // Update the light shader with the camera view position
        SetShaderValue(shader, shader.locs[LOC_VECTOR_VIEW], &camera.position.x, UNIFORM_VEC3);
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(BLACK);

            BeginMode3D(camera);

            // DrawCube((Vector3){ 3.0f, 0.0f, 0.0f }, 1.0f, 1.0f, 1.0f, WHITE);

            DrawModel(model_1, (Vector3){ 3.0f, 2.0f, 0.0f }, 1.0f, RED);

                // Draw the three models
                // DrawModel(modelA, Vector3Zero(), 1.0f, WHITE);
                // DrawModel(modelB, (Vector3){ 2.6, 0, 0 }, 1.0f, WHITE);
                // DrawModel(modelC, (Vector3){ 2.6, 0, 0 }, 1.0f, WHITE);

                // for (int i = 20; i <= 40; i += 2)
                // { DrawModel(modelA,(Vector3){ float(i), 0, 2 }, 1.0f, WHITE); }

            EndMode3D();

            DrawText(TextFormat("Use KEY_UP/KEY_DOWN to change fog density [%.2f]", fogDensity), 10, 10, 20, RAYWHITE);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadModel(modelA);        // Unload the model A
    UnloadModel(modelB);        // Unload the model B
    UnloadModel(modelC);        // Unload the model C
    UnloadTexture(texture);     // Unload the texture
    UnloadShader(shader);       // Unload shader

    CloseWindow();              // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
