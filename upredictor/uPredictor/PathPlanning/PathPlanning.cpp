#include <iostream>
#include <UBCUtil.h>
#include "BasicFormulas.h"
#include "ForwardKin.h"
#include "NaiveIK.h"
#include "ParseMathematica.h"
 
#include <Eigen/SVD>

#include <fstream>
#include <iostream>
#include <string>

using namespace ceres;
using namespace Eigen;
using namespace std;

int main(int argc, char **argv) {
	size_t nJoints = 7;
	size_t polynomialOrder = 3;

	Problem problem;

	std::vector<double> jointMinAngles, jointMaxAngles;
	jointMinAngles.push_back(-2.6);
	jointMinAngles.push_back(-2.0);
	jointMinAngles.push_back(-2.8);
	jointMinAngles.push_back(-0.9);
	jointMinAngles.push_back(-4.76);
	jointMinAngles.push_back(-1.6);
	jointMinAngles.push_back(-3.0);

	jointMaxAngles.push_back(2.6);
	jointMaxAngles.push_back(2.0);
	jointMaxAngles.push_back(2.8);
	jointMaxAngles.push_back(3.1);
	jointMaxAngles.push_back(1.24);
	jointMaxAngles.push_back(1.6);
	jointMaxAngles.push_back(3.0);

	MatrixXd inPositions = parseMathematica(getWholeFile(argv[1])).transpose();
	MatrixXd inAngles = parseMathematica(getWholeFile(argv[2]));
	MatrixXd startAngles = inAngles.block(0,0,1,nJoints).transpose();
	MatrixXd endAngles = inAngles.block(1,0,1,nJoints).transpose();
	

	//generate linear path in joint space 
	//Eigen::Matrix<double, Dynamic, Dynamic> outJointAngles = 		linearInterp<double>(startAngles, endAngles, 20);


	//generate linear path
	Eigen::Matrix<double, Dynamic, Dynamic> outPathPts = 		linearInterp<double>(
		inPositions.block(0,0,3,1), inPositions.block(0,1,3,1)
		, 20);

	//generate Elliptical path
	//Eigen::Matrix<double, Dynamic, Dynamic> outPathPtsEll = 		EllipticalInterp<double>(
	//	inPositions.block(0,0,3,1), inPositions.block(0,1,3,1)
	//	, 20);

	// number of optimization parameters 
	size_t nParams = nJoints * (polynomialOrder + 1);

	double startConfig[nParams];
	size_t ctr = 0;

	// theta = a0 + a1*t ...
	// at time zero theta(0) = a0
	for(size_t joint = 0; joint < nJoints; joint++) {
		startConfig[ctr] = startAngles(joint);
		ctr++;
		for(size_t term = 0; term < polynomialOrder; term++) {
			startConfig[ctr] = 0.0;
			ctr++;
		}
	}

	
	//generates the DH T matrix for all the joints	     
	ForwardKin<double> wam =
		ForwardKin<double>::generateBarrettWAM();

	//NaiveIK nik(wam);
	size_t nSlices = 20;

	
	for(size_t i = 0; i <= nSlices; i++) {
		double sliceSize = 1.0 / (double)nSlices;
		//from 0 to 1
		double multiplier = i * sliceSize;
		
		//cf for every outPathPts, i.e. every slice
		CostFunction *cf =
			NaiveIK<double>::CreateThirdOrderSevenParam(
				wam, outPathPts.block(0,i,3,1) 					, multiplier
				, jointMinAngles, jointMaxAngles);

		problem.AddResidualBlock(cf, NULL, startConfig);
	}

	ctr = 0;
	for(size_t joint = 0; joint < nJoints; joint++) {
		problem.SetParameterLowerBound(startConfig, ctr, jointMinAngles[joint]);
		problem.SetParameterUpperBound(startConfig, ctr, jointMaxAngles[joint]);
		ctr++;
		for(size_t term = 0; term < polynomialOrder; term++) {
			problem.SetParameterLowerBound(
				startConfig, ctr, jointMinAngles[joint]);
			problem.SetParameterUpperBound(
				startConfig, ctr, jointMaxAngles[joint]);
			ctr++;
		}
	}

	Solver::Options options;
	Solver::Summary summary;

	//options.use_nonmonotonic_steps = true;
	options.max_num_iterations = 1000;
	//options.function_tolerance = 0.00000000001;
	//options.gradient_tolerance = 0.000000000000000000001;
	ceres::Solve(options, &problem, &summary);

	cout << summary.FullReport() << endl;
	
	//printEigenMathematica(outJointAngles, cout, "interpolated joint angles");

	printEigenMathematica(inPositions.block(0,0,3,1), cout, "startPosW");
	printEigenMathematica(inPositions.block(0,1,3,1), cout, "endPosW");
	printEigenMathematica(outPathPts, cout, "pathPts");


	
	//printEigenMathematica(outPathPtsEll, cout, "pathPts2");

	cout << "{{";
	for(size_t i = 0; i < nParams; i++) {
		cout << fixed << startConfig[i];
		if(i < (nParams - 1)) cout << ",";
	}
	cout << "}}" << endl;
	Eigen::Matrix<double, 21 , 7> J0; 

	
	// Fit nth order polynomial in joint spacelx
	for (size_t j = 0; j < wam.getNJoints(); j++){
		size_t jTimesFour = j * 4;

		for(size_t i = 0; i <= nSlices; i++) {

			J0(i,j) = simpleThirdOrder(
					startConfig[jTimesFour]
					, startConfig[jTimesFour + 1]
					, startConfig[jTimesFour + 2]
					, startConfig[jTimesFour + 3]
					, double(i*(3.0/nSlices)));

		}

	}	

	cout<<J0<<endl;
/*
	cout << "{{";
	for(size_t i = 0; i < nSlices; i++) {
		cout << fixed << startConfig[i];
		if(i < (nSlices - 1)) cout << ",";
	}
	cout << "}}" << endl;
*/
	return 0;
}




