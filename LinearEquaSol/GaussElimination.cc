#include<iostream>
#include<vector>
#include<math.h>
using std::cin; using std::cout; using std::endl;
using std::vector;

class LinearEqua{
private:
	vector<double> resVector;
	vector<std::vector<double>> coefficientMatrix;
	int GetMaxInLine(unsigned);
	void SwapRow(int, int);
public:
	LinearEqua(void);
	LinearEqua(std::vector<std::vector<double>>&, std::vector<double>&);

	void SetCoefficient(std::vector<std::vector<double>>&);
	void SetB(std::vector<double>&);
	void GaussSolveEqua();
	void PrintCoefficient();
	void PrintRes();
};

LinearEqua::LinearEqua(void){};
LinearEqua::LinearEqua(vector<vector<double>> &input_coefficient, vector<double> &input_b){
	if(input_b.size() != input_coefficient.size()){
		cout << "Wrong Input!" << endl;
		return;
	}
	resVector = input_b;
	coefficientMatrix = input_coefficient;
};
	
void LinearEqua::SetCoefficient(vector<vector<double>> &input_coefficient){
	coefficientMatrix = input_coefficient;
};
void LinearEqua::SetB(vector<double> &input_b){
	resVector = input_b;
};

int LinearEqua::GetMaxInLine(unsigned colID){
	unsigned curRow = colID;
	double max = abs(coefficientMatrix[curRow][colID]);
	unsigned maxRow = colID;
	for(++curRow;curRow < resVector.size(); ++curRow){
		double val = abs(coefficientMatrix[curRow][colID]);
		
		if(val > max){
			max = val;
			maxRow = curRow;
		}
	}
	return maxRow;
};

void LinearEqua::SwapRow(int row1, int row2){
	std::vector<double> tmp = coefficientMatrix[row1];
	coefficientMatrix[row1] = coefficientMatrix[row2];
	coefficientMatrix[row2] = tmp;
	double btmp = resVector[row1];
	resVector[row1] = resVector[row2];
	resVector[row2] = btmp;
}

void LinearEqua::PrintCoefficient(){
	for(auto col : coefficientMatrix){
		for(auto element : col){
			cout << element << " ";
		}
		cout << endl;
	}
}

void LinearEqua::GaussSolveEqua(){
	decltype(resVector.size()) equaNum, unknownNum = 0;
	if((equaNum = resVector.size()) != coefficientMatrix.size()){
		cout << "Wrong Input!" << endl;
	}	
	unknownNum = coefficientMatrix[0].size();
	if(equaNum < unknownNum){
		cout << "Input Linear System Of Equations Has No Answer!" << endl;
		return;
	}

	for(int eliminatedColNum = 0; eliminatedColNum < unknownNum; ++eliminatedColNum){
		/*int swapCol = GetMaxInLine(eliminatedColNum);
		if(swapCol != eliminatedColNum){
			SwapRow(eliminatedColNum, swapCol);
		}*/
		if(coefficientMatrix[eliminatedColNum][eliminatedColNum] == 0){
			cout << "Input Linear System Of Equations Has No Answer!" << endl;
			return;
		}
		
		for(int eliminatedEquaID = eliminatedColNum + 1; eliminatedEquaID < equaNum; ++eliminatedEquaID){
			double m = coefficientMatrix[eliminatedEquaID][eliminatedColNum]/coefficientMatrix[eliminatedColNum][eliminatedColNum];
			for(int colInEqua = eliminatedColNum + 1; colInEqua < unknownNum; ++colInEqua){
				coefficientMatrix[eliminatedEquaID][colInEqua] -= (m * coefficientMatrix[eliminatedColNum][colInEqua]);
			}
			resVector[eliminatedEquaID] -= (m * resVector[eliminatedColNum]);
			coefficientMatrix[eliminatedEquaID][eliminatedColNum] = m;
		}
	//	PrintCoefficient();
	//	PrintRes();
	}

	for(int i = unknownNum; i < equaNum; ++i){
		if(resVector[i] != 0){
			cout << "Input Linear System Of Equations Has No Answer!" << endl;
			return;
		}
	}

	for(int solvingUnknownID = unknownNum - 1; solvingUnknownID >= 0; --solvingUnknownID){
		for(int t = solvingUnknownID + 1; t < unknownNum; ++t){
			resVector[solvingUnknownID] -= coefficientMatrix[solvingUnknownID][t] * resVector[t];
		}	
		resVector[solvingUnknownID] /= coefficientMatrix[solvingUnknownID][solvingUnknownID];
	}	
};

void LinearEqua::PrintRes(){
	int resNum = coefficientMatrix[0].size();
	for(int i = 0; i < resNum; ++i){
		cout << resVector[i] << " ";
	}
	cout << endl;
}

int main(){
	vector<vector<double>> coMatrix {{2, 1, -3, -1}, {3, 1, 0, 7}, {-1, 2, 4, -2}, {1, 0, -1, 5}};
	vector<vector<double>> equaB {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};
	for(auto equa : equaB){
		LinearEqua curTest(coMatrix, equa);
		curTest.GaussSolveEqua();
		curTest.PrintRes();
	}
	return 0;	
}
