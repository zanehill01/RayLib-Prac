
#include "raylib.h"

int main(void)
{

	const int s_width = 800;
	const int s_height = 450;

	InitWindow(s_width, s_height, "RayLib Practice Window");
	Vector2 ballPosition = { (float)s_width / 2, (float)s_height / 2 };

	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		if (IsKeyDown(KEY_RIGHT)) ballPosition.x += 2.0f;
		if (IsKeyDown(KEY_LEFT)) ballPosition.x -= 2.0f;

		if (IsKeyDown(KEY_UP)) ballPosition.y -= 2.0f;
		if (IsKeyDown(KEY_DOWN)) ballPosition.y += 2.0f;

		BeginDrawing();

			ClearBackground(RAYWHITE);
			DrawText("Move the Ball with the Arrow Keys", 10, 10, 20, DARKGRAY);
			DrawCircleV(ballPosition, 50, MAROON);

		EndDrawing();
	}

	CloseWindow();
	return 0;
}