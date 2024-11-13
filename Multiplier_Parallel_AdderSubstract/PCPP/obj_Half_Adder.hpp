#pragma once
#include "raylib.h"
#include <iostream>
#include <string>

class obj_Half_Adder {
public:
	obj_Input_Num Connected_To_A, Connected_To_B, Connected_To_C;
	Vector2 Size;
	Vector2 Pos, Pos_PointA, Pos_PointB, Pos_PointC, Pos_Output, Pos_CarryOut;
	Vector2 Pos_TargetCarryIn;

	Rectangle RecBase;
	Rectangle PointARec, PointBRec, PointCRec, PointOutRec, PointCOutRec;

	int InputA[200];
	int InputB[200];
	int InputC[200];
	int Output, CarryOut;
	int CarryIn[200];
	Color PointColor = GRAY;
	float LineThick = 10;
	float RatioX, RatioY;
	std::string Label = "";

	float GetRatio() {
		return RatioX <= RatioY ? RatioX : RatioY;
	}
	void ConnectTo_A(obj_Input_Num& _A) {
		_A.TargetLine = Pos_PointA;
		for (int i = 0; i < 200; i++) {
			InputA[i] = _A.NumInput[i];
		}
	}
	void ConnectTo_B(obj_Input_Num& _B) {
		_B.TargetLine = Pos_PointB;
		for (int i = 0; i < 200; i++) {
			InputB[i] = _B.NumInput[i];
		}
	}
	void ConnectTo_C(obj_Input_Num& _C) {
		_C.TargetLine = Pos_PointC;
		for (int i = 0; i < 200; i++) {
			InputC[i] = _C.NumInput[i];
		}
	}
	void ConnectTo_CO(obj_Half_Adder _CO) {
		Pos_TargetCarryIn = _CO.Pos_PointC;
	}
	void ConnectTo_CO_Vector(Vector2 _V2) {
		Pos_TargetCarryIn = _V2;
	}
	void Initialize(Vector2 _Pos, Vector2 _Size) {
		Pos = _Pos;
		Size = _Size;

		Pos_PointA.x = Pos.x - (_Size.x / 2);
		Pos_PointA.y = Pos.y - (_Size.y / 2) + (_Size.y / 3);

		Pos_PointB.x = Pos.x - (_Size.x / 2);
		Pos_PointB.y = Pos.y + (_Size.y / 2) - (_Size.y / 3);

		Pos_PointC.x = Pos.x;
		Pos_PointC.y = Pos.y - (_Size.y / 2);

		Pos_Output.x = Pos.x + (_Size.x / 2);
		Pos_Output.y = Pos.y - (_Size.y / 2) + (_Size.y / 3);

		Pos_CarryOut.x = Pos.x + (_Size.x / 2);
		Pos_CarryOut.y = Pos.y + (_Size.y / 2) - (_Size.y / 3);
	}
	void Update() {
		SetRecBase();
		SetRecPoint();
		SetPointsPos();
	}
	void SetPointsPos() {
		Pos_PointA.x = (Pos.x - (Size.x / 2)) * GetRatio();
		Pos_PointA.y = (Pos.y - (Size.y / 2) + (Size.y / 3)) * GetRatio();

		Pos_PointB.x = (Pos.x - (Size.x / 2)) * GetRatio();
		Pos_PointB.y = (Pos.y + (Size.y / 2) - (Size.y / 3)) * GetRatio();

		Pos_PointC.x = (Pos.x) * GetRatio();
		Pos_PointC.y = (Pos.y - (Size.y / 2)) * GetRatio();

		Pos_Output.x = (Pos.x + (Size.x / 2)) * GetRatio();
		Pos_Output.y = (Pos.y - (Size.y / 2) + (Size.y / 3)) * GetRatio();

		Pos_CarryOut.x = (Pos.x + (Size.x / 2)) * GetRatio();
		Pos_CarryOut.y = (Pos.y + (Size.y / 2) - (Size.y / 3)) * GetRatio();
	}
	void SetRecBase() {
		RecBase.x = (Pos.x - (Size.x / 2)) * GetRatio();
		RecBase.y = (Pos.y - (Size.y / 2)) * GetRatio();
		RecBase.width = (Size.x) * GetRatio();
		RecBase.height = (Size.y) * GetRatio();
	}
	void SetRecPoint() {
		PointARec.x = Pos_PointA.x - (10 * GetRatio());
		PointARec.y = Pos_PointA.y - (10 * GetRatio());
		PointARec.width = 20 * GetRatio();
		PointARec.height = 20 * GetRatio();

		PointBRec.x = Pos_PointB.x - (10 * GetRatio());
		PointBRec.y = Pos_PointB.y - (10 * GetRatio());
		PointBRec.width = 20 * GetRatio();
		PointBRec.height = 20 * GetRatio();

		PointCRec.x = Pos_PointC.x - (10 * GetRatio());
		PointCRec.y = Pos_PointC.y - (10 * GetRatio());
		PointCRec.width = 20 * GetRatio();
		PointCRec.height = 20 * GetRatio();

		PointOutRec.x = Pos_Output.x - (10 * GetRatio());
		PointOutRec.y = Pos_Output.y - (10 * GetRatio());
		PointOutRec.width = 20 * GetRatio();
		PointOutRec.height = 20 * GetRatio();

		PointCOutRec.x = Pos_CarryOut.x - (10 * GetRatio());
		PointCOutRec.y = Pos_CarryOut.y - (10 * GetRatio());
		PointCOutRec.width = 20 * GetRatio();
		PointCOutRec.height = 20 * GetRatio();
	}
	void DrawLine() {
		DrawLineEx({ Pos_CarryOut.x, Pos_CarryOut.y }, { (Pos_CarryOut.x + (Size.x * GetRatio())), Pos_CarryOut.y }, LineThick * GetRatio(), BLACK);
		DrawLineEx({ (Pos_CarryOut.x + (Size.x * GetRatio())), Pos_CarryOut.y }, { (Pos_CarryOut.x + (Size.x * GetRatio())), ((Pos_CarryOut.y + Pos_TargetCarryIn.y) / 2) + (10 * GetRatio()) }, LineThick * GetRatio(), BLACK);
		DrawLineEx({ (Pos_CarryOut.x + (Size.x * GetRatio())), ((Pos_CarryOut.y + Pos_TargetCarryIn.y) / 2) + (10 * GetRatio()) }, { (Pos_TargetCarryIn.x), ((Pos_CarryOut.y + Pos_TargetCarryIn.y) / 2) + (10 * GetRatio()) }, LineThick * GetRatio(), BLACK);
		DrawLineEx({ (Pos_TargetCarryIn.x), ((Pos_CarryOut.y + Pos_TargetCarryIn.y) / 2) + (10 * GetRatio()) }, { (Pos_TargetCarryIn.x), Pos_TargetCarryIn.y }, LineThick * GetRatio(), BLACK);
	}
	void Draw() {
		DrawRectangleRec(RecBase, BLACK);
		DrawText(Label.c_str(), (Pos.x - (Label.length() * 5)) * GetRatio(), (Pos.y - 7) * GetRatio(), 20 * GetRatio(), WHITE);

		DrawRectangleRec(PointARec, PointColor);
		DrawRectangleRec(PointBRec, PointColor);
		DrawRectangleRec(PointCRec, PointColor);
		DrawRectangleRec(PointOutRec, PointColor);
		DrawRectangleRec(PointCOutRec, PointColor);

		if (Pos_TargetCarryIn.x > 0 || Pos_TargetCarryIn.y > 0) {
			DrawLine();
		}
	}
};