
#include "raylib.h"
#include "rcamera.h"

#define MAX_COLUMNS 20

int main(void)
{
	const int s_width = 1200;
	const int s_height = 850;

	InitWindow(s_width, s_height, "RayLib Practice Window");

	// create camera window

	Camera camera = { 0 };
	camera.position = (Vector3){ 0.0f, 2.0f, 4.0f };  // Camera position 
	camera.target = (Vector3){ 0.0f, 2.0f, 0.0f };      // Camera looking at point 
	camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target) 
	camera.fovy = 60.0f;                                // Camera field-of-view Y 
	camera.projection = CAMERA_PERSPECTIVE;             // Camera mode type

	int cameraMode = CAMERA_FIRST_PERSON;

	// generate random columns for the world generation

	float heights[MAX_COLUMNS] = { 0 };
	Vector3 positions[MAX_COLUMNS] = { 0 };
	Color colors[MAX_COLUMNS] = { 0 };

	for (int i = 0; i < MAX_COLUMNS; i++)
	{
		heights[i] = (float)GetRandomValue(1, 12);
		positions[i] = (Vector3){ (float)GetRandomValue(-15, 15), heights[i] / 2.0f, (float)GetRandomValue(-15, 15) };
		colors[i] = (Color){ GetRandomValue(20, 255), GetRandomValue(10,55), 30, 255 };
	}

	SetTargetFPS(60);

	while (!WindowShouldClose())
	{

		if (IsKeyPressed(KEY_ONE))
		{
			cameraMode = CAMERA_FREE;
			camera.up = (Vector3){ 0.0f, 1.0f, 0.0f }; // Reset roll
		}

		if (IsKeyPressed(KEY_TWO))
		{
			cameraMode = CAMERA_FIRST_PERSON;
			camera.up = (Vector3){ 0.0f, 1.0f, 0.0f }; // Reset roll
		}

		if (IsKeyPressed(KEY_THREE))
		{
			cameraMode = CAMERA_THIRD_PERSON;
			camera.up = (Vector3){ 0.0f, 1.0f, 0.0f }; // Reset roll
		}

		UpdateCamera(&camera, cameraMode);

		//

		BeginDrawing();

			ClearBackground(RAYWHITE);

			BeginMode3D(camera);

				// Draw Ground

				DrawPlane((Vector3) { 0.0f, 0.0f, 0.0f }, (Vector2) { 32.0f, 32.0f }, LIGHTGRAY);

				// Draw Walls

				DrawCube((Vector3) { -16.0f, 2.5f, 0.0f }, 1.0f, 5.0f, 32.0f, BLUE);
				DrawCube((Vector3) { 16.0f, 2.5f, 0.0f }, 1.0f, 5.0f, 32.0f, LIME);
				DrawCube((Vector3) { 0.0f, 2.5f, 16.0f }, 32.0f, 5.0f, 1.0f, GOLD);

				// Draw Random Cubes

				for (int i = 0; i < MAX_COLUMNS; i++)
				{
					DrawCube(positions[i], 2.0f, heights[i], 2.0f, colors[i]);
					DrawCubeWires(positions[i], 2.0f, heights[i], 2.0f, MAROON);
				}

				// Draw Player Cube

				if (cameraMode == CAMERA_THIRD_PERSON)
				{
					DrawCube(camera.target, 0.5f, 0.5f, 0.5f, PURPLE);
					DrawCubeWires(camera.target, 0.5f, 0.5f, 0.5f, DARKPURPLE);
				}

			EndMode3D();

		EndDrawing();

	}

	CloseWindow();
	return 0;
}