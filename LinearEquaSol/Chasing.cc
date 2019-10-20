#include<iostream>
#include<vector>
using std::cin; using std::cout; using std::endl;
using std::vector;

#define ISZERO(x, i, j)\
{\
if(x != 0){ \
cout << "Coefficient is not valid!" << endl;\
cout << "Matrix[" << i << "][" << j << "] is not zero!" << endl;\
return false;\
}\
}

class LinearEqua{
	private:
		vector<double> resVector;
		vector<vector<double>> coefficientMatrix;
	public:
		LinearEqua(void){};
		LinearEqua(vector<vector<double>>&, vector<double>&);
		bool CheckValid();
		void Solve();
		void PrintRes();
};

LinearEqua::LinearEqua(vector<vector<double>>& input_coefficient, vector<double>& input_b){
	resVector = input_b;
	coefficientMatrix = input_coefficient;
}

bool LinearEqua::CheckValid(){
    if(coefficientMatrix.size() != coefficientMatrix[0].size()){
        cout << "It is not a squa!" << endl;
    	return false;
    }   
	auto size = coefficientMatrix.size();
             
	for(decltype(size) i = 1; i < size - 1; ++i){
        for(decltype(i) j = 0; j < i - 1; ++j){
	    	ISZERO(coefficientMatrix[i][j], i, j);
		}         
    	for(decltype(i) j = i + 2; j < size; ++j){
	    	ISZERO(coefficientMatrix[i][j], i, j);
	    }         
    }   
    for(decltype(size) i = 2; i < size; ++i){
        ISZERO(coefficientMatrix[0][i], 0, i);
    }         
    for(decltype(size) i = 0; i < size - 2; ++i){
    	ISZERO(coefficientMatrix[size - 1][i], size - 1, i);
	}                           
    return true;         
} 

void LinearEqua::Solve(){
	if(!CheckValid()){
		cout << "error!" << endl;
		return;
	}
	auto size = coefficientMatrix.size();

	coefficientMatrix[0][1] /= coefficientMatrix[0][0];
	for(decltype(size) i = 1; i < size - 1; ++i){
		coefficientMatrix[i][i] -= coefficientMatrix[i - 1][i] * coefficientMatrix[i][i - 1];
		coefficientMatrix[i][i + 1] /= coefficientMatrix[i][i];
	}
	coefficientMatrix[size - 1][size - 1] -= coefficientMatrix[size - 2][size - 1] * coefficientMatrix[size - 1][size - 2];

	for(decltype(size) i = 0; i < size - 1; ++i){
		resVector[i] /= coefficientMatrix[i][i];
		resVector[i + 1] -= coefficientMatrix[i + 1][i] * resVector[i];
	}
	resVector[size - 1] /= coefficientMatrix[size - 1][size - 1];

	for(int i = size - 2; i >= 0; --i){
		resVector[i] -= coefficientMatrix[i][i + 1] * resVector[i + 1];
	}
}

void LinearEqua::PrintRes(){
	for(auto res : resVector){
		cout << res << " ";
	}
	cout << endl;
}

int main(){
	vector<vector<double>> coe = {{2, -1 ,0, 0}, {-1, 3, -2, 0}, {0, -1, 2, -1}, {0, 0, -3, 5}};
	vector<double> b = {6, 1, 0, 1};
	LinearEqua test(coe, b);
	test.Solve();
	test.PrintRes();
	return 0;
}
