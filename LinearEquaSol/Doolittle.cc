#include<iostream>
#include<vector>
#include<math.h>
using std::cin; using std::cout; using std::endl;
using std::vector;

class LinearEqua{
private:
	vector<double> resVector;
	vector<std::vector<double>> coefficientMatrix;
	vector<int> equaSeq;
	
	int equaNum, unknownNum;
	
	int GetMaxInLine(unsigned);
	void SwapRow(int, int);
	void SwapB();
	void LUDoolittle();
public:
	LinearEqua(void);
	LinearEqua(vector<vector<double>>&, vector<double>&);

	void SetCoefficient(vector<vector<double>>&);
	void SetB(vector<double>&);
	void DoolittleSolveEqua();
	void PrintRes();
	void PrintCoefficient();
};

LinearEqua::LinearEqua(void){};
LinearEqua::LinearEqua(vector<vector<double>> &input_coefficient, vector<double> &input_b){
	if(input_b.size() != input_coefficient.size()){
		cout << "Wrong Input!" << endl;
		return;
	}

	resVector = input_b;
	coefficientMatrix = input_coefficient;

	for(int i = 0; i < resVector.size(); ++i){
		equaSeq.push_back(i);
	}
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
	for(++curRow;curRow < equaNum; ++curRow){
		int val = abs(coefficientMatrix[curRow][colID]);
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
	
	int tmpEquaID = equaSeq[row1];
	equaSeq[row1] = equaSeq[row2];
	equaSeq[row2] = tmpEquaID;

	/*double btmp = resVector[row1];
	resVector[row1] = resVector[row2];
	resVector[row2] = btmp;*/
}

void LinearEqua::SwapB(){
	vector<double> tmpB = resVector;
	for(int i = 0 ; i < equaNum; ++i){
		if(equaSeq[i] != i){
			resVector[i] = tmpB[equaSeq[i]];
		}
	}
}

void LinearEqua::LUDoolittle(){
	if((equaNum = resVector.size()) != coefficientMatrix.size()){
		std::cout << "Wrong Input!" << std::endl;
	}
	unknownNum = coefficientMatrix[0].size();
	if(equaNum < unknownNum){
		std::cout << "Input Linear System Of Equations Has No Answer!" << std::endl;
		return;
	}

	for(int layer = 0; layer < unknownNum; ++layer){
		for(int colInLayer = layer; colInLayer < unknownNum; ++colInLayer){
			for(int colBeforeLayer = 0; colBeforeLayer < layer; ++colBeforeLayer){
				coefficientMatrix[layer][colInLayer] -= coefficientMatrix[layer][colBeforeLayer] * coefficientMatrix[colBeforeLayer][colInLayer];
			}
		}

		for(int rowInLayer = layer + 1; rowInLayer < equaNum; ++rowInLayer){
			for(int rowAboveLayer = 0; rowAboveLayer < layer; ++rowAboveLayer){
				coefficientMatrix[rowInLayer][layer] -= coefficientMatrix[rowInLayer][rowAboveLayer] * coefficientMatrix[rowAboveLayer][layer];
			}
			coefficientMatrix[rowInLayer][layer] /= coefficientMatrix[layer][layer];
		}

		int curMaxRow = GetMaxInLine(layer);
		if(curMaxRow != layer){
			SwapRow(curMaxRow, layer);
		}
	};

}

void LinearEqua::DoolittleSolveEqua(){
	LUDoolittle();
	PrintCoefficient();
	SwapB();

	for(int i = 0; i < unknownNum; ++i){
		for(int j = 0; j < i; ++j){
			resVector[i] -= coefficientMatrix[i][j] * resVector[j];
		}
	}

	for(int solvingUnknownID = unknownNum - 1; solvingUnknownID >= 0; --solvingUnknownID){
		for(int t = solvingUnknownID + 1; t < unknownNum; ++t){
			resVector[solvingUnknownID] -= coefficientMatrix[solvingUnknownID][t] * resVector[t];
		}
		resVector[solvingUnknownID] /= coefficientMatrix[solvingUnknownID][solvingUnknownID];
	}
}

void LinearEqua::PrintCoefficient(){
	int equaNum = coefficientMatrix.size();
	int unknownNum = coefficientMatrix[0].size();
	for(int i = 0; i < equaNum; ++i){
		for(int j = 0; j < unknownNum; ++j){
			cout << coefficientMatrix[i][j] << " ";
		}
		cout << endl;
	}
}

void LinearEqua::PrintRes(){
	int resNum = coefficientMatrix[0].size();
	cout << "The Answer Vector Is:" << endl;
	for(int i = 0; i < resNum; ++i){
		cout << resVector[i] << endl;
	}
}

int main(){
	vector<vector<double>> coMatrix {{10, -7, 0, 1}, {-3, 2.099999, 6, 2}, {5 ,-1, 5, -1}, {2, 1, 0, 2}};
	vector<double> equaB {8, 5.900001, 5, 1};
	LinearEqua curTest(coMatrix, equaB);
	curTest.DoolittleSolveEqua();
	curTest.PrintRes();
	return 0;	
}
