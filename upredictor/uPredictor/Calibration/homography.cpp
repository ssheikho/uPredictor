#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <eigen3/Eigen/Dense>
#include <eigen3/Eigen/SVD>
#include <eigen3/Eigen/Eigen>
#include <opencv2/opencv.hpp>

#include "CameraModel.h"
#include "KinectInterface.h"

using namespace cv;
using namespace std;
using namespace Eigen;

#define NUM_POINTS 64
#define PRINT 0

/* loadModel loads the relevant image and model information from
   previously created files. */
// For now, just use arrays for modelPoints and imagePoints, with
// maximum size 100. Change it to vector later (But eigen has problems)
int loadModel(Matrix<double, 3, 1> modelPoints[], Matrix<double, 3, 1> imagePoints[][NUM_POINTS])
{
	int i, j, nPoints = 0;
	FILE* fpm  = fopen("model.txt","r");
	FILE* fpi1 = fopen("points1.txt","r");
	FILE* fpi2 = fopen("points2.txt","r");

	if (fpi1==NULL ||fpi2==NULL || fpm==NULL) { 
		printf("File access error: Check if it exists or not\n"); return 1; }

	for (nPoints = 0; !feof(fpm); nPoints++) {
		fscanf(fpm, "%lf %lf ", &modelPoints[i](0,0), &modelPoints[i](1,0));
		modelPoints[i](2,0) = 1;
	}

	fclose(fpm); 

	for (i=0; i<nPoints; i++) {
		fscanf(fpi1, "%lf %lf ", &(imagePoints[0][i])(0,0), &imagePoints[0][i](1,0));
		imagePoints[0][i](2,0) = 1;
		fscanf(fpi2, "%lf %lf ", &imagePoints[1][i](0,0), &imagePoints[1][i](1,0));
		imagePoints[1][i](2,0) = 1;
	}

	fclose(fpi1); fclose(fpi2);

	return nPoints;
}

void computeSVD(int rowSize, MatrixXd &L, MatrixXd &U, MatrixXd &V, VectorXd &S) {
	// Generate random matrices for testing purposes
	VectorXd b = VectorXd::Zero(rowSize);
	// cout << "[L]\n" << L << endl;
	// cout << "[b]\n" << b << endl;

	VectorXd x(rowSize);

	JacobiSVD<MatrixXd> svdOfA(L, ComputeThinU | ComputeThinV);

	U = svdOfA.matrixU();
	V = svdOfA.matrixV();
	S = svdOfA.singularValues();

	if (PRINT) {
		cout << "[U]\n" << U << endl;
		cout << "[V]\n" << V << endl;
		cout << "[S]\n" << S << endl;		
	}
}

void solveAx0(int nPoints, MatrixXd &L, MatrixXd &H)
{
	MatrixXd U;
	MatrixXd V;
	VectorXd S;

	computeSVD((2*nPoints), L, U, V, S);

	for (int i = 0; i < 9; i++)
		H(i, 0) = V(i, 	8);
}

/* Get homography between model and image points. */
int homography(int nPoints, Matrix<double, 3, 1> modelPoints[], Matrix<double, 3, 1> imagePoints[], MatrixXd &H)
{
	// int i, j, k;	
	//double H[9];

	MatrixXd L(2 * nPoints, 9);
	//Matrix<double, (2*(nPoints)), 9> L;

	/* Assembles coefficients matrix L */
	for(int k=0; k < nPoints; k++)
	{
		double X = modelPoints[k](0,0);  /* X coord of model point k */
		double Y = modelPoints[k](1,0);  /* Y coord of model point k */
		double W = modelPoints[k](2,0);  /* W coord of model point k */
		double u = imagePoints[k](0,0);  /* u coord of image point k */
		double v = imagePoints[k](1,0);  /* v coord of image point k */

		int i = k * 2;
		   L(i,0) = X,     L(i,1) = Y,     L(i,2) = W;
		   L(i,3) = 0,     L(i,4) = 0,     L(i,5) = 0;
		L(i,6) = -u*X,  L(i,7) = -u*Y,  L(i,8) = -u*W;
		
		i++;
		   L(i,0) = 0,     L(i,1) = 0,     L(i,2) = 0;
		   L(i,3) = X,     L(i,4) = Y,     L(i,5) = W;
		L(i,6) = -v*X,  L(i,7) = -v*Y,  L(i,8) = -v*W;

	}

	if (PRINT)
		cout << "[L]:\n" << L << endl;

	// cout << "This part not implemented yet\n";

	solveAx0(2 * nPoints, L, H); 
	/* Solve the system [L]{h}={0} */

	if (PRINT)
		cout << "[H]:\n" << H << endl;

	// Solve using the Levenberg Marquardt (Or something else) method

	return 0;
}

/* Normalize image points that belong to calibration pattern. */
void normalizeImagePoints(double w, double h, int n, int numViews, Matrix<double, 3, 1> imagePoints[][NUM_POINTS], Matrix3d &N)
{
	// s_ = pixel scaling
	// _0 = camera origin(?)
	double sx = 2.0/w, sy = 2.0/h, x0 = w/2.0, y0 = h/2.0;

	//int i, j, k;

	N << sx,   0,  -sx*x0, 
	      0,  sy,  -sy*y0,
	      0,   0,       1;

	// k = index of view
	for (int k = 0; k < numViews; k++) {
		for (int i = 0; i < n; i++) {
			imagePoints[k][i] = N * imagePoints[k][i];
			// cout <<"k, i: "<< k << " " << i <<endl; 
			// cout << imagePoints[k][i] << endl;
		}
	}
}

/*
   Gets the camera intrinsic matrix.
*/
void getIntrinsicParams(CameraModel &camModel, Matrix3d &A, Matrix3d &AInv)
{
	A << camModel._alpha, camModel._gamma, camModel._uZero,
	                   0,  camModel._beta, camModel._vZero,
	                   0,               0,               1;

	AInv = A.inverse();

	if (PRINT + 21)
	{
		cout << "[A]:\n" << A << endl;
		cout << "[AInv]:\n" << AInv << endl;
	}
}

/*
	Computes the camera extrinsic matrix.
*/
void getExtrinsicParams(CameraModel &camModel, MatrixXd &H, Matrix3d &K)
{
	Matrix3d A;
	Matrix3d AInv;
	getIntrinsicParams(camModel, A, AInv);

	double tmpNorm1 = 1/((AInv * H.col(0)).norm());
	K.col(0) = (AInv * H.col(0) * tmpNorm1);
	double tmpNorm2 = 1/((AInv * H.col(1)).norm());
	K.col(1) = (AInv * H.col(1) * tmpNorm2);
	K.col(2) = (AInv * H.col(2) * ((tmpNorm1 + tmpNorm2)/2.0));
	
	if (PRINT + 21)
		cout << "[K]:\n" << K << endl;
}

/* createModel points for chessboar, then normalize later */
void createModel(Matrix<double, 3, 1> modelPoints[], Size boardSize) {
	int idx = 0;
	double squareSize = 10;
	for (int i=0; i < boardSize.height; i++) {
		for (int j=0; j < boardSize.width; j++) {
			modelPoints[idx](0,0) = i*squareSize;
			modelPoints[idx](1,0) = j*squareSize;
			modelPoints[idx](2,0) = 1;
			idx++;
		}
	}

	// Normalize the model Points

	double h = squareSize*boardSize.height, w = squareSize*boardSize.width; 
	double sx = 2.0/w, sy = 2.0/h, x0 = w/2.0, y0 = h/2.0;

	Matrix3d N;
	N << sx,   0,  -sx*x0, 
	      0,  sy,  -sy*y0,
	      0,   0,       1;

	for (int i = 0; i < idx; i++) {
		modelPoints[i] = N * modelPoints[i];
	}
}

void registerCorners(Mat image, Size boardSize, Matrix<double, 3, 1> imagePoints[]) {

	vector<Point2f> corners;
	bool found = findChessboardCorners(image, boardSize, corners,
		CALIB_CB_ADAPTIVE_THRESH | CALIB_CB_NORMALIZE_IMAGE);

	if (found) {
		cornerSubPix(image, corners, Size(11,11), Size(-1, -1),
					TermCriteria(TermCriteria::EPS + TermCriteria::COUNT, 30, 0.1));

		// Use the values of points in corners
		// to inititalize the values in imagePoints
		for (int j = 0; j < corners.size(); j++)
		{
			imagePoints[j](0,0) = corners[j].x;
			imagePoints[j](1,0) = corners[j].y;
			imagePoints[j](2,0) = 1;
			// cout <<"I, J: "<< i << " " << j <<endl; 
			// cout << imagePoints[i][j] << endl;
		}

		drawChessboardCorners(image, boardSize, Mat(corners), found);

		// imshow("something", image);
		// waitKey(0);
	}
}


void getCorners(int numFiles, Size boardSize, Matrix<double, 3, 1> imagePoints[][NUM_POINTS])
{
	Mat image;
	for (int i = 0; i < numFiles; i++) {
		image = imread("imagefolder/image" + to_string(i) + ".jpg", CV_LOAD_IMAGE_GRAYSCALE);
		// Read the next image in the folder
		registerCorners(image, boardSize, imagePoints[i]);
	}
}


void reconstructChessboard(Mat image, int nPoints, Matrix<double, 3, 1> imagePoints[], Matrix<double, 3, 1> imagePointsComp[])
{

	for (int i=0; i<nPoints; i++) {
		Point2f tmpCentre(imagePoints[i](0,0), imagePoints[i](1,0));
		circle(image, tmpCentre, 10, (0,0,255), 2);
	}

	for (int i=0; i<nPoints; i++) {
		Point2f tmpCentre(imagePointsComp[i](0,0), imagePointsComp[i](1,0));
		circle(image, tmpCentre, 7.5, (255,0,0), 2);
	}

	imshow("something", image);
	waitKey(0);
}

void getMatParams(MatrixXd X) {
	cout << "[X]" << endl;
	cout << "det(X) : " << X.determinant() << endl;
	cout << "[XX'] : " << endl;
	cout << X * X.transpose() << endl;
}

void fixRotation(int rowSize, Vector3d &r1, Vector3d &r2, Vector3d &r3) {

	MatrixXd R(3, 3);
	R << r1, r2, r3;

	cout << "[R]" << endl;
	cout << R << endl;

	MatrixXd U;
	MatrixXd V;
	VectorXd S;

	computeSVD(rowSize, R, U, V, S);

	R = U * V;

	cout << "After fixing [R]" << endl;
	cout << R << endl;

	getMatParams(R);

	r1 = R.col(0);
	r2 = R.col(1);
	r3 = R.col(2);

}

int computeHomographyForImage(Mat image)
{
	Size imgSize(1920, 1080);
	double h = 100, w = 100;
	h = imgSize.height, w = imgSize.width;

	Matrix<double, 3, 1> modelPoints[NUM_POINTS];
	// modelPoints contains num sqare number of points (In 3d, probably 0/1 appended at the end)
	Matrix<double, 3, 1> imagePoints[1][NUM_POINTS];
	// Normalize all sets of images	
	Matrix<double, 3, 1> imagePointsComp[1][NUM_POINTS];
	// Stores the reconstructed images
	Size boardSize(6, 7);
	int nPoints = boardSize.height*boardSize.width;
	int numViews = 1;

	createModel(modelPoints, boardSize);
	
	registerCorners(image, boardSize, imagePoints[0]);

	cout << "We're here!" << endl;

	// Normalize the points using the camera parameters
	Matrix3d N;
	normalizeImagePoints(w, h, nPoints, numViews, imagePoints, N);

	cout << "N is:\n";
	cout << N << endl;

	// Compute homography for the pairs of points

	MatrixXd H(9,1);

	homography(nPoints, modelPoints, imagePoints[0], H);
	
	H.resize(3,3);
	H.transposeInPlace();

	// Extrinsic matrix
	Matrix3d K;

	// Assume that we initialize K as part of the class
	// getExtrinsicParams(ki.getDepthCM(), H, K);

	Vector3d r1 = K.col(0);
	Vector3d r2 = K.col(1);
	Vector3d r3 = r1.cross(r2);
	//Vector3d r3 = r2.cross(r1);

	// Fix the orthogonality issue of R using SVD
	fixRotation(3, r1, r2, r3);

	Vector3d t = K.col(2);
	Matrix <double, 1, 4> lastRow;
	lastRow << 0, 0, 0, 1;

	Matrix <double, 4, 4> RT;
	Matrix <double, 3, 4> tmpRT;
	tmpRT.col(0) = r1;
	tmpRT.col(1) = r2;
	tmpRT.col(2) = r3;
	tmpRT.col(3) = t;

	RT << tmpRT,
		  lastRow;

	cout << "[RT]:\n" << RT << endl;

	cout << "[H]:\n" << H << endl;

	if (H(2,2) != 0) {
		double scale = H(2,2);
		H = (H/scale);
	}
	else {
		cout << "Error during scaling\n";
	}

	cout << "After resizing [H]:\n" << H << endl;

	for (int j=0; j < nPoints; j++) {
		imagePointsComp[0][j] = ((H*modelPoints[j]*imagePoints[0][j](2,0))/((H*modelPoints[j])(2,0)));
	}

	MatrixXd invN = N.inverse();

	Matrix<double, 3, 1> tmpImgPoints[NUM_POINTS];
	Matrix<double, 3, 1> tmpImgPointsComp[NUM_POINTS];

	for (int j=0; j < nPoints; j++) {
		tmpImgPoints[j] = invN * imagePoints[0][j];
		tmpImgPointsComp[j] = invN * imagePointsComp[0][j];
	}

	reconstructChessboard(image, nPoints, tmpImgPoints, tmpImgPointsComp);

	return 0;
}

int computeHomography()
{
	/*
	Steps to perform:
		- Read data from file 	(DONE)
		- Read images from folders	(Need to integrate, already implemented)	(DONE)
		- Find chessboard corners in images 	(Need to integrate, already implemented)	(DONE)
		- Write data to file 	(Not performed right now)
		- Setup model Points and image Points once detected		(DONE)
		- Normalize matrices	(DONE)
		- Setup matrix for homography computation	(DONE)
		- Use SVD to identify non trivial solution	(DONE)
	*/

	Size imgSize(1920, 1080);
	double h = 100, w = 100;
	h = imgSize.height, w = imgSize.width;

	Matrix<double, 3, 1> modelPoints[NUM_POINTS];
	// modelPoints contains num sqare number of points (In 3d, probably 0/1 appended at the end)
	Matrix<double, 3, 1> imagePoints[100][NUM_POINTS];
	// Normalize all sets of images	
	Matrix<double, 3, 1> imagePointsComp[100][NUM_POINTS];
	// Stores the reconstructed images

	Matrix<double, 3, 1> modelPointsOrig[NUM_POINTS];
	Matrix<double, 3, 1> imagePointsOrig[100][NUM_POINTS];

	// int nPoints = loadModel(modelPoints, imagePoints);

	Size boardSize(6, 7);
	int nPoints = boardSize.height*boardSize.width;
	int numViews = 1;

	createModel(modelPoints, boardSize);
	
	getCorners(numViews, boardSize, imagePoints);

	// for (int k = 0; k < 1; k++) {
	// 	for (int i = 0; i < 42; i++) {
	// 		cout <<"k, i: "<< k << " " << i <<endl; 
	// 		cout << modelPoints[i] << endl;
	// 	}
	// }

	cout << "We're here!" << endl;

	// i is index of image
	// j is index of point (in an image)
	for (int i=0; i < numViews; i++)	{
		for (int j=0; j < nPoints; j++)	{
			imagePointsOrig[i][j] = imagePoints[i][j];
		}
	}

	for (int j=0; j < nPoints; j++)	{
		modelPointsOrig[j] = modelPoints[j];
	}

	// Normalize the points using the camera parameters
	Matrix3d N;
	normalizeImagePoints(w, h, nPoints, numViews, imagePoints, N);

	cout << "N is:\n";
	cout << N << endl;

	// For extrinsic matrix
	TrackIDManager tidm;
	KinectInterface ki(tidm);

	// Compute homography for the pairs of points
	 
	for (int i=0; i < numViews; i++) {
		MatrixXd H(9,1);

		homography(nPoints, modelPoints, imagePoints[i], H);
		
		H.resize(3,3);
		H.transposeInPlace();

		// Extrinsic matrix
		Matrix3d K;
		getExtrinsicParams(ki.getDepthCM(), H, K);

		Vector3d r1 = K.col(0);
		Vector3d r2 = K.col(1);
		Vector3d r3 = r1.cross(r2);
		//Vector3d r3 = r2.cross(r1);

		// Fix the orthogonality issue of R using SVD
		fixRotation(3, r1, r2, r3);

		Vector3d t = K.col(2);
		Matrix <double, 1, 4> lastRow;
		lastRow << 0, 0, 0, 1;

		Matrix <double, 4, 4> RT;
		Matrix <double, 3, 4> tmpRT;
		tmpRT.col(0) = r1;
		tmpRT.col(1) = r2;
		tmpRT.col(2) = r3;
		tmpRT.col(3) = t;

		RT << tmpRT,
 			  lastRow;

		cout << "[RT]:\n" << RT << endl;

		cout << "[H]:\n" << H << endl;

		if (H(2,2) != 0) {
			double scale = H(2,2);
			H = (H/scale);
		}
		else {
			cout << "Error during scaling\n";
		}

		cout << "After resizing [H]:\n" << H << endl;

		for (int j=0; j < nPoints; j++) {
			// cout << "Currently for j: " << j << endl; 
			// cout << (imagePoints[i][j]/imagePoints[i][j](2,0)) << endl;
			// cout << "The other value\n";	
			// cout << ((H*modelPoints[j]*imagePoints[i][j](2,0))/((H*modelPoints[j])(2,0))) << endl;
			imagePointsComp[i][j] = ((H*modelPoints[j]*imagePoints[i][j](2,0))/((H*modelPoints[j])(2,0)));
		}

		// for (int j=0; j < nPoints; j++) {
		// 	cout << "Currently for j: " << j << endl; 
		// 	cout << (imagePoints[i][j]/imagePoints[i][j](2,0)) - (H*modelPoints[j]/((H*modelPoints[j])(2,0))) << endl;
		// }

	}

	MatrixXd invN = N.inverse();

	for (int i=0; i < numViews; i++) {
		Matrix<double, 3, 1> tmpImgPoints[NUM_POINTS];
		Matrix<double, 3, 1> tmpImgPointsComp[NUM_POINTS];

		for (int j=0; j < nPoints; j++) {
			tmpImgPoints[j] = invN * imagePoints[i][j];
			tmpImgPointsComp[j] = invN * imagePointsComp[i][j];
		}

		Mat image;
		image = imread("imagefolder/image" + to_string(i) + ".jpg" /*, CV_LOAD_IMAGE_GRAYSCALE*/);

		reconstructChessboard(image, nPoints, tmpImgPoints, tmpImgPointsComp);
	}


	
	return 0;
}

int main() {
	// int nPoints = 12;
	// MatrixXd L = MatrixXd::Ones(nPoints, 10);
	// Matrix<double, 9, 1> H;
	// solveAx0(nPoints, L, H);

	//computeSVD();

	computeHomography();
	
	/*
	TrackIDManager tidm;
	KinectInterface ki(tidm);

	Matrix3d K;
	getExtrinsicParams(ki.getDepthCM(), K);	
	*/
	
	return 0;
}
