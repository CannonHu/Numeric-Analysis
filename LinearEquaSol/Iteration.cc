#include<iostream>
#include<vector>
#include<math.h>
using std::cin; using std::cout; using std::endl;
using std::vector;

class LinearEqua{
	private:
		vector<double> bVector;
		vector<vector<double>> coefficientMatrix;
		vector<double> resVector;
		double iterationDelta = 0;
		int iterationTimes = -1;
		int iterationCnt = 0;
		
		double JacobiIteration();
		double GSIteration();
	public:
		LinearEqua(void){};
		LinearEqua(vector<vector<double>>&, vector<double>&);
		void SetIteration(double);
		void SetInitialRes(vector<double>&);
		double JacobiSolve();
		double GSSolve();
		
};

LinearEqua::LinearEqua(vector<vector<double>> &input_coefficient, vector<double> &input_b){
    if(input_b.size() != input_coefficient.size()){
        cout << "Wrong Input!" << endl;
        return;
    }

	for(auto &v: input_coefficient){
		if(v.size() != input_coefficient[0].size()){
			cout << "Wrong Input!"  << endl;
			return;
		}
	}
    bVector = input_b;
    coefficientMatrix = input_coefficient;
	
	for(decltype(input_coefficient.size()) i = 0; i < input_coefficient.size(); ++i){
		double t = input_coefficient[i][i];
		for(decltype(i) j = 0; j < input_coefficient.size(); ++j){
			if(i == j){
				input_coefficient[i][j] = 0;
			}
			else{
				input_coefficient[i][j] /= t;
			}
		}
		bVector[i] /= t;
	}
};

void LinearEqua::SetIteration(double delta){
	iterationDelta = delta;
};

void LinearEqua::SetInitialRes(vector<double>& initialRes){
	if(initialRes.size() != coefficientMatrix[0].size()){
		cout << "Invalid Initial Result!" << endl;
		return;
	}
	resVector = initialRes;
}

double LinearEqua::JacobiIteration(){
	vector<double> newResVector(resVector.size(), 0);
	for(decltype(coefficientMatrix.size()) i = 0; i < coefficientMatrix.size(); ++i){
		for(decltype(i) j = 0; j < resVector.size(); ++j){
			newResVector[j] += coefficientMatrix[i][j] * resVector[j];
		}
	}
	
	double maxDelta = 0;
	for(decltype(resVector.size()) i = 0; i < resVector.size(); ++i){
		double eleDelta = abs(resVector[i] - newResVector[i]);
		if(eleDelta > maxDelta){
			maxDelta = eleDelta;
		}
	}
	
	return maxDelta;
}

double LinearEqua::JacobiSolve(){
	double resDelta = 0;
	if(iterationTimes <= 0){
		auto i = iterationTimes;
		
		while(i--){
			resDelta = JacobiIteration();
		}
	}
	else if(iterationDelta != 0){
		resDelta = JacobiIteration();
		
		while(resDelta > iterationDelta){
			auto tempDelta = JacobiIteration();
			if(tempDelta > resDelta){
				cout << "Bad Iteration!" << endl;
				return -1;	
			}
			else{
				resDelta = tempDelta;
			}
		}
	}

	return resDelta;
}

double LinearEqua::GSIteration(){
    vector<double> prevResVector = resVector;
	for(decltype(coefficientMatrix.size()) i = 0; i < coefficientMatrix.size(); ++i){
      	resVector[i] = 0;
		for(decltype(i) j = 0; j < resVector.size(); ++j){
            resVector[i] += coefficientMatrix[i][j] * resVector[j];
        }
    }
    
    double maxDelta = 0;
	for(decltype(resVector.size()) i = 0; i < resVector.size(); ++i){
        double eleDelta = abs(resVector[i] - prevResVector[i]);
        if(eleDelta > maxDelta){
            maxDelta = eleDelta;
        }
    }       
        
    return maxDelta;
}

double LinearEqua::GSSolve(){
    double resDelta = 0;
	if(iterationTimes <= 0){
		auto i = iterationTimes;
	    while(i--){
			resDelta = JacobiIteration();
		}
	}
	else if(iterationDelta != 0){
		resDelta = JacobiIteration();
		
	    while(resDelta > iterationDelta){
		     auto tempDelta = JacobiIteration();
		     if(tempDelta > resDelta){
			     cout << "Bad Iteration!" << endl;
			     return -1;
			 }
			 else{
				 resDelta = tempDelta;
			 }
		}
	}
	 
	return resDelta;
}

int main(){

}
