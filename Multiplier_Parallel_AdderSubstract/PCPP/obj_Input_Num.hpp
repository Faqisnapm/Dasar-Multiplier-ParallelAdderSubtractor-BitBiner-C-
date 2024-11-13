#pragma once
#include "raylib.h"
#include <iostream>
#include <string>

class obj_Input_Num {
public:
	int ID;
	Vector2 Pos, InitialLine, TargetLine;
	Vector2 InitLineUp, InitLineLeft, InitLineRight, InitLineDown;
	float RatioX, RatioY;
	Vector2 BaseSize;
	Color BaseColor = BLACK;
	Color DefaultInputBoxCol = WHITE;
	Color PointColor = DARKGRAY;
	float LineThick = 10;
	bool OnFocus = false;;
	Rectangle RecBase;
	int InputLength = 0;
	int NumInput[200];
	int NumInputI = 0;
	int MaxInputLength = 4;
	int LocPoint = -1;
	int UseLocPoint = -1;
	bool DisableInput = false;
	std::string str, LabelPinggir, Tulisan_Atas_Str;
	bool WithIdOnLabel = false;
	int MultiplierSpace = 40;
	Vector2 LineMiddle;
	bool Tulisan_Atas = false;
	float Tulisan_Atas_Geser_Kiri = 0;
	Color FocusBoxColor = DefaultInputBoxCol;

	//RecPoint
	Rectangle RLUp, RLDown, RLRight, RLLeft;

	//Other Function
	float GetRatio() {
		return RatioX <= RatioY ? RatioX : RatioY;
	}
	Vector2 GetRatioV2() {
		return { GetRatio(), GetRatio() };
	}

	//Line Function
	void This_DrawLine() {
		if (TargetLine.x < InitialLine.x) {
			DrawLineEx({ InitialLine.x, InitialLine.y }, { (InitialLine.x - (TargetLine.x / 4 * GetRatio())), InitialLine.y}, LineThick * GetRatio(), BaseColor);
			DrawLineEx({ (InitialLine.x - (TargetLine.x / 4 * GetRatio())), InitialLine.y }, { (InitialLine.x - (TargetLine.x / 4 * GetRatio())), TargetLine.y }, LineThick * GetRatio(), BaseColor);
			DrawLineEx({ InitialLine.x - (TargetLine.x / 4 * GetRatio()), TargetLine.y }, { TargetLine.x , TargetLine.y }, LineThick * GetRatio(), BaseColor);
			LineMiddle = { (InitialLine.x - (TargetLine.x / 4 * GetRatio())), InitialLine.y };
		}
		else {
			DrawLineEx({ InitialLine.x, InitialLine.y }, { TargetLine.x / 2, InitialLine.y }, LineThick * GetRatio(), BaseColor);
			DrawLineEx({ TargetLine.x / 2, InitialLine.y }, { TargetLine.x / 2, TargetLine.y }, LineThick * GetRatio(), BaseColor);
			DrawLineEx({ TargetLine.x / 2, TargetLine.y }, { TargetLine.x , TargetLine.y }, LineThick * GetRatio(), BaseColor);
			LineMiddle = { TargetLine.x / 2, InitialLine.y };
		}
	}
	void SetInitialLine(Vector2 _Vec2) {
		InitialLine = _Vec2;
	}
	void SetTargetLine(Vector2 _Vec2) {
		TargetLine = _Vec2;
	}

	//Draw Object

	void DrawObject() {
		FocusBoxColor = DefaultInputBoxCol;
		DrawRectangleRec(RecBase, BLACK);
		//DrawRectangle((Pos.x - (BaseSize.x / 2)) * GetRatio(), (Pos.y - BaseSize.y / 2) * GetRatio(), BaseSize.x * GetRatio(), BaseSize.y * GetRatio(), BLACK);
		DrawRectangle((Pos.x - ((BaseSize.x - 10) / 2)) * GetRatio(), (Pos.y - ((BaseSize.y - 10) / 2)) * GetRatio(), (BaseSize.x - 10) * GetRatio(), (BaseSize.y - 10) * GetRatio(), FocusBoxColor);
		std::string Str = std::to_string(NumInputI);
		if (str.length() > 0) {
			DrawText(str.c_str(), (Pos.x - (BaseSize.x / 2) + 15) * GetRatio(), (Pos.y - (BaseSize.y / 4)) * GetRatio(), 50 * GetRatio(), BLACK);
		}
		else {
			DrawText(Str.c_str(), (Pos.x - (BaseSize.x / 2) + 15) * GetRatio(), (Pos.y - (BaseSize.y / 4)) * GetRatio(), 50 * GetRatio(), BLACK);
		}
		if (WithIdOnLabel) {
			DrawText(LabelPinggir.c_str(), (Pos.x - (BaseSize.x / 2) - (LabelPinggir.length() * 60)) * GetRatio(), (Pos.y - (BaseSize.y / 4)) * GetRatio(), 50 * GetRatio(), BLACK);
			DrawText(std::to_string(ID).c_str(), (Pos.x - (BaseSize.x / 2) - (LabelPinggir.length() * 25)) * GetRatio(), (Pos.y * GetRatio()), 30 * GetRatio(), BLACK);
		}
		else {
			DrawText(LabelPinggir.c_str(), (Pos.x - (BaseSize.x / 2) - (LabelPinggir.length() * MultiplierSpace)) * GetRatio(), (Pos.y - (BaseSize.y / 4)) * GetRatio(), 50 * GetRatio(), BLACK);
		}
		if (Tulisan_Atas) {
			DrawText(Tulisan_Atas_Str.c_str(), (Pos.x - (BaseSize.x / 4) + 20 - Tulisan_Atas_Geser_Kiri) * GetRatio(), (Pos.y - (BaseSize.y) - 10) * GetRatio(), 50 * GetRatio(), BLACK);
	
		}

		//Point Rec
		if (UseLocPoint == 0) DrawRectangleRec(RLUp, PointColor);
		if (UseLocPoint == 1) DrawRectangleRec(RLDown, PointColor);
		if (UseLocPoint == 2) DrawRectangleRec(RLLeft, PointColor);
		if (UseLocPoint == 3) DrawRectangleRec(RLRight, PointColor);

		This_DrawLine();
	}

	//RunCode
	void CheckClickFocus() {
		if (CheckCollisionPointRec(GetMousePosition(), RecBase) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
			OnFocus = true;
			FocusBoxColor = GRAY;
			//std::cout << "ImFocus\n";
		}
		else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !CheckCollisionPointRec(GetMousePosition(), RecBase)) {
			OnFocus = false;
			FocusBoxColor = DefaultInputBoxCol;
		}
	}
	void FillNum() {
		int CurrentKey = GetKeyPressed();
		
		if (OnFocus && CurrentKey >= 48 && CurrentKey <= 57 && std::to_string(NumInputI).length() < MaxInputLength) {
			NumInput[InputLength] = (int)(CurrentKey - 48);
			for (int i = 0; i <= InputLength; i++) {
				std::cout << NumInput[i];
			}
			//std::cout << "\n";
			InputLength++;
		}
		else if (OnFocus && IsKeyPressed(KEY_BACKSPACE)) {
			if (InputLength > 0) {
				NumInput[InputLength] = 0;
				InputLength--;
			}
		} 
		if (OnFocus && (CurrentKey >= 48 && CurrentKey <= 57 || IsKeyPressed(KEY_BACKSPACE))) {
			NumInputI = 0;
			for (int i = 0; i < InputLength; i++)
				NumInputI = 10 * NumInputI + NumInput[i];
		}
	}
	void SetPointRecPosition() {
		RLUp.x = (Pos.x - 10) * GetRatio();
		RLUp.y = (Pos.y - (BaseSize.y / 2) - 10) * GetRatio();
		RLUp.height = 20 * GetRatio();
		RLUp.width = 20 * GetRatio();
		InitLineUp = { Pos.x * GetRatio(), (Pos.y - (BaseSize.y / 2)) * GetRatio() };

		RLDown.x = (Pos.x - 10) * GetRatio();
		RLDown.y = (Pos.y + (BaseSize.y / 2) - 10) * GetRatio();
		RLDown.height = 20 * GetRatio();
		RLDown.width = 20 * GetRatio();
		InitLineDown = { Pos.x * GetRatio(), (Pos.y + (BaseSize.y / 2)) * GetRatio() };

		RLLeft.x = (Pos.x - 10 - (BaseSize.x / 2)) * GetRatio();
		RLLeft.y = (Pos.y - 10) * GetRatio();
		RLLeft.height = 20 * GetRatio();
		RLLeft.width = 20 * GetRatio();
		InitLineLeft = { (Pos.x - 10 - (BaseSize.x / 2)) * GetRatio(), Pos.y * GetRatio() };

		RLRight.x = (Pos.x - 10 + (BaseSize.x / 2)) * GetRatio();
		RLRight.y = (Pos.y - 10) * GetRatio();
		RLRight.height = 20 * GetRatio();
		RLRight.width = 20 * GetRatio();
		InitLineRight = { (Pos.x - 10 + (BaseSize.x / 2)) * GetRatio(), Pos.y * GetRatio() };
	}
	void SetLocPointPosition() {
		if (CheckCollisionPointRec(GetMousePosition(), RLUp)) {
			LocPoint = 0;
		}
		else if (CheckCollisionPointRec(GetMousePosition(), RLDown)) {
			LocPoint = 1;
		}
		else if (CheckCollisionPointRec(GetMousePosition(), RLLeft)) {
			LocPoint = 2;
		}
		else if (CheckCollisionPointRec(GetMousePosition(), RLRight)) {
			LocPoint = 3;
		}
	}

	void Main() {
		//Default
		LineThick = 10;
		Pos.x = 1920 / 2.0f;
		Pos.y = 1080 / 2.0f;
		BaseSize = { 150, 80 };
		OnFocus = false;
	}
	void SetOBJPos(float _x, float _y) {
		Pos = { _x, _y };
	}
	void Initialize(Vector2 _Pos, Vector2 _BaseSize, float _LineThick, int _UseLocPoint) {
		Main();
		Update();
		Pos = _Pos;
		BaseSize = _BaseSize;
		LineThick = _LineThick;
		UseLocPoint = _UseLocPoint;
	}
	void Update() {
		//Set RecBase Attr
		RecBase.x = (Pos.x - (BaseSize.x / 2)) * GetRatio();
		RecBase.y = (Pos.y - BaseSize.y / 2) * GetRatio();
		RecBase.width = BaseSize.x * GetRatio();
		RecBase.height = BaseSize.y * GetRatio();
		if(TargetLine.x > 0 && TargetLine.y > 0 && UseLocPoint == 0){
			InitialLine = InitLineUp;
		}
		if (TargetLine.x > 0 && TargetLine.y > 0 && UseLocPoint == 1) {
			InitialLine = InitLineDown;
		}
		if (TargetLine.x > 0 && TargetLine.y > 0 && UseLocPoint == 2) {
			InitialLine = InitLineLeft;
		}
		if (TargetLine.x > 0 && TargetLine.y > 0 && UseLocPoint == 3) {
			InitialLine = InitLineRight;
		}

		if (!DisableInput)CheckClickFocus();
		if (OnFocus) {
			FillNum();
		}
		SetPointRecPosition();
	}
	int GetVal() {
		return NumInputI;
	}
};