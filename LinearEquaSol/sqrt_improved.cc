#include<vector>
#include<iostream>
using std::cin; using std::cout; using std::endl;
using std::vector;

class PositiveDefiniteEqua{
	private:
		vector<double> PositiveDefiniteMatrix;
		vector<double> resVect;
		unsigned long equaNum = 0;

		bool isPositiveDefinite(vector<vector<double>>&);
		void LDLform();
	public:
		PositiveDefiniteEqua(){};
		PositiveDefiniteEqua(vector<vector<double>> &, vector<double> &);
		void SolveEqua();
};

bool PositiveDefiniteEqua::isPositiveDefinite(vector<vector<double>> &coefficientMatrix){
	for(decltype(coefficientMatrix.size()) i = 0; i < coefficientMatrix.size(); ++i){
		if(coefficientMatrix[i][i] <= 0){
			cout << "It is not a Positive Definite Matrix!" << endl;
			return false;
		}

		for(decltype(i) j = 0; j < i; ++j){
			if(coefficientMatrix[i][j] != coefficientMatrix[j][i]){
				return false;
			}
			PositiveDefiniteMatrix.push_back(coefficientMatrix[i][j]);
		}
		PositiveDefiniteMatrix.push_back(coefficientMatrix[i][i]);	
	}
	return true;
};

PositiveDefiniteEqua::PositiveDefiniteEqua(vector<vector<double>> &input_coefficient, vector<double> &input_b){
	if(input_coefficient.size() == 0){
		cout << "Wrong Input! Equations are empty!" << endl;
	}
	if(input_coefficient.size() != input_b.size() || input_coefficient.size() != input_coefficient[0].size()){
		cout << "Wrong Input!"<<endl;
		return;
	}

	if(!isPositiveDefinite(input_coefficient)){
			cout << "It is not a Positive Definite Matrix!" << endl;
			return;	
	}

	resVect = input_b;	
};

void PositiveDefiniteEqua::LDLform(){
	decltype(resVect.size()) it = 0;
	for(auto i = it; i < resVect.size(); ++i){
		auto prevNum = ((i + 1) * i / 2);
		for(decltype(i) j = 0; j < i; ++j, ++it){
			auto prevNum2 = ((j + 1) * j) / 2;
			for(decltype(j) t = 0; t < j; ++t){
				PositiveDefiniteMatrix[it] -= PositiveDefiniteMatrix[prevNum + t] * PositiveDefiniteMatrix[prevNum2 + t];// * PositiveDefiniteMatrix[prevNum2 - 1];
			}
			//PositiveDefiniteMatrix[it] /= PositiveDefiniteMatrix[(j + 2) * (j + 1) / 2 - 1];
		}
		
		for(decltype(i) t = 0; t < i; ++t){
			double l_it = PositiveDefiniteMatrix[prevNum + t] / PositiveDefiniteMatrix[(t + 2) * (t + 1)/2 - 1];
			PositiveDefiniteMatrix[it] -= PositiveDefiniteMatrix[prevNum + t] * l_it;// * PositiveDefiniteMatrix[(t + 2) * (t + 1) / 2 - 1];
			PositiveDefiniteMatrix[it - i + t] = l_it;
		}
		it ++;
	}
}

void PositiveDefiniteEqua::SolveEqua(){
	LDLform();

/*
*	for(auto d : PositiveDefiniteMatrix){
*		cout << d << " ";
*	}
*	cout << endl;
*/
}

int main(){
	vector<vector<double>> coefficient = {{2, 3, 1}, {3, 2, -3}, {1, -3, 5}};
	vector<double> res = {4, -5, 20};
	PositiveDefiniteEqua test(coefficient, res);
	test.SolveEqua();
	return 0;
}
