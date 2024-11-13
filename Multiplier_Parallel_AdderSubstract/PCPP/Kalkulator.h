#pragma once

//Fungsi Kalkulator Full

void Kalkulator_Full_Adder(int _A[], int _B[], int _Sum[], int& _Cout, int _Max_Bits) {
	_Cout = 0;
	for (int i = _Max_Bits - 1; i >= 0; i--) {
		int tempSum = _A[i] + _B[i] + _Cout;
		_Sum[i] = tempSum % (_Max_Bits / 2);
		_Cout = tempSum / (_Max_Bits / 2);
	}
}

void Kalkulator_Full_Substractor(int _A[], int _B[], int _Sum[], int& _Cout, int _Max_Bits) {
	const int Bits = 200;
	int NumA[Bits];
	int NumB[Bits];
	int NumAns[Bits];
	int Co1[Bits];
	int NumBSementaraAdd1[Bits];
	int NumBSementara[Bits];
	int _temp;

	for (int i = 0; i < _Max_Bits; i++) {
		if (i < _Max_Bits - 1) {
			Co1[i] = 0;
		}
		else {
			Co1[_Max_Bits - 1] = 1;
		}
	}
	for (int i = 0; i < Bits; i++) {
		NumA[i] = NumB[i] = NumAns[i] = NumBSementaraAdd1[i] = Co1[i] = NumBSementara[i] = 0;
	}
	for (int i = 0; i < _Max_Bits; i++) {
		if (_B[i] == 1) {
			NumB[i] = 0;
		}
		else {
			NumB[i] = 1;
		}
	}

	//Tambah 1
	/*Kalkulator_Full_Adder(NumB, Co1, NumAns, _temp, _Max_Bits);*/
	bool AdaNol = false;
	for (int j = 0; j < _Max_Bits; j++) {
		if (NumB[j] == 0) AdaNol = true;
	}
	if (!AdaNol) {
		for (int j = 0; j < _Max_Bits; j++) {
			NumB[j] = 0;
		}
	}
	if (AdaNol) {
		for (int i = _Max_Bits - 1; i >= 0; i--) {
			bool DoubleTambah = false;
			if (i > 0) {
				if (NumB[i] == 0) {
					NumB[i] = 1;
					break;
				}
				else if (NumB[i] == 1 && NumB[i - 1] == 0) {
					NumB[i] = 0;
					NumB[i - 1] = 1;
					break;
				}
				else if(NumB[i] == 1 && NumB[i - 1] == 1){
					NumB[i] = 0;
					NumB[i - 1] = 0;
					i = i - 1;
				}
			}
		}
	}
	Kalkulator_Full_Adder(_A, NumB, _Sum, _Cout, _Max_Bits);
}

//Multiplier
void DecToBin(int _In, int& _Out0, int& _Out1) {
	if (_In == 0) {
		_Out0 = _Out1 = 0;
	}
	else if (_In == 1) {
		_Out0 = 1;
		_Out1 = 0;
	}
	else if (_In == 2) {
		_Out0 = 0;
		_Out1 = 1;
	}
	else if (_In == 3) {
		_Out0 = _Out1 = 1;
	}
}
void BinToDec(int& Out, int In0, int In1) {
	if (!In0 && !In1) {
		Out = 0;
	}
	else if (!In0 && In1) {
		Out = 1;
	}
	else if (In0 && !In1) {
		Out = 2;
	}
	else if (In0 && In1) {
		Out = 3;
	}
}
bool Kal_O0(bool A0, bool B0, bool A1, bool B1) {
	return A0 && B0;
}
bool Kal_O1(bool A0, bool B0, bool A1, bool B1) {
	return (!A1 && A0 && B1) || (A0 && B1 && !B0) || (A1 && !B1 && B0) || (A1 && !A0 && B0);
}
bool Kal_O2(bool A0, bool B0, bool A1, bool B1) {
	if (A0 && A1 && B0 && B1) {
		return 0;
	}
	else {
		return (A1 && B1 && B0) || (A1 && A0 && B1);
	}
};
bool Kal_O3(bool A0, bool B0, bool A1, bool B1) {
	return A1 && A0 && B1 && B0;
};

int BinToDecMulti(int _A[], int _Max_Bit) {
	int Hasil = 0;
	for (int i = 0; i < _Max_Bit; i++) {
		Hasil += _A[i] * std::pow(2, (_Max_Bit - 1) - i);
	}
	return Hasil;
}