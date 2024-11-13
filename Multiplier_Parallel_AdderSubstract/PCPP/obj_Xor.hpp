#pragma once
#include "raylib.h"
#include <iostream>
#include <string>

using namespace std;
class obj_Xor {
public:
	Vector2 Pos;
	float Scale = .8;
	Image Img;
	Texture2D texture;

	void LoadImg(string _Path) {
		Img = LoadImage(_Path.c_str());
	}
	void Draw() {
		DrawTextureEx(texture, Pos, 0, Scale, WHITE);
	}
	void SetPos(Vector2 _V2) {
		Pos = _V2;
	}
	void Update() {

	}
	void Initialize() {
		Pos = { 1280, 720 };
		LoadImg("Res/XorGate.png");
		texture = LoadTextureFromImage(Img);
	}
	void Deinitialize() {
		UnloadTexture(texture);
	}
};