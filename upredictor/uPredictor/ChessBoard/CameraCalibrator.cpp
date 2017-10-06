#include "CameraCalibrator.h"

#include <fstream> // Currently needed for unused code

#define PRINT 0
#define DRAW_CORNERS 1

#define _USE_MATH_DEFINES

CameraCalibrator::CameraCalibrator() :
	_imageSize(512, 424)
	, _boardSize(7, 9)
	, _squareSize(22)
{
	MatrixXd modelPoints2DCart = createModel2DCart();
	MatrixXd modelPoints3DCart = addRowOfVal(modelPoints2DCart, 0.0);
	_modelPoints3D = addRowOfVal(modelPoints3DCart, 1.0);
}

CameraCalibrator::~CameraCalibrator() {}

/*
	Create 2D model points for chessboard, then normalize later.
*/
// FUNC_createModel2DCart
MatrixXd CameraCalibrator::createModel2DCart()
{
	MatrixXd retVal(2, _boardSize.height * _boardSize.width);
	int idx = 0;
	for (int i=0; i < _boardSize.height; i++)
	{
		for (int j=0; j < _boardSize.width; j++)
		{
			retVal(0,idx) = i*_squareSize;
			retVal(1,idx) = j*_squareSize;
			idx++;
		}
	}

	return retVal;
}

/*
	Create 2D homogeneous model points for chessboard, then normalize later.
*/
// FUNC_createModel
void CameraCalibrator::createModel(Matrix<double, 3, 1> modelPoints[])
{
	int idx = 0;
	for (int i = 0; i < _boardSize.height; i++)
	{
		for (int j = 0; j < _boardSize.width; j++)
		{
			modelPoints[idx](0,0) = i * _squareSize;
			modelPoints[idx](1,0) = j * _squareSize;
			modelPoints[idx](2,0) = 1;
			idx++;
		}
	}
}

/*
	Add a row of numbers to a matrix.
*/
// FUNC_addRowOfVal
MatrixXd CameraCalibrator::addRowOfVal(MatrixXd &X, double val)
{
	MatrixXd retVal = MatrixXd(X.rows() + 1, X.cols());

	// Copy the original matrix
	for (int i=0; i < X.rows(); i++)
	{
		for (int j=0; j < X.cols(); j++)
		{
			retVal(i,j) = X(i,j);
		}
	}

	// Fill in the last row
	for (int j=0; j < X.cols(); j++)
	{
		retVal(X.rows(),j) = val;
	}

	return retVal;
}

/*
	Gets the corners detected in the image and returns them as 2D homogeneous.
*/
// FUNC_registerCorners
bool CameraCalibrator::registerCorners(Mat image, Matrix<double, 3, 1> imagePoints[])
{
	vector<Point2f> corners;
	bool found = findChessboardCorners(image, _boardSize, corners,
		CALIB_CB_ADAPTIVE_THRESH | CALIB_CB_NORMALIZE_IMAGE);

	if (found)
	{
		// Use the values of points in corners
		// to inititalize the values in imagePoints
		for (int j = 0; j < corners.size(); j++)
		{
			imagePoints[j](0,0) = corners[j].x;
			imagePoints[j](1,0) = corners[j].y;
			imagePoints[j](2,0) = 1;
		}

		if (DRAW_CORNERS)
		{
			drawChessboardCorners(image, _boardSize, Mat(corners), found);
			imshow("registerCorners", image);
		}
	}

	return found;
}

/*
	Singular value decomposition.
*/
// FUNC_computeSVD
void CameraCalibrator::computeSVD(MatrixXd &L, MatrixXd &U, MatrixXd &V, VectorXd &S)
{
	JacobiSVD<MatrixXd> svdOfA(L, ComputeThinU | ComputeThinV);

	// Orthonormal
	U = svdOfA.matrixU();
	V = svdOfA.matrixV();

	// Diagonal matrix in decreasing order
	S = svdOfA.singularValues();

	if (PRINT)
	{
		cout << "[U]:\n" << U << endl;
		cout << "[V]:\n" << V << endl;
		cout << "[S]:\n" << S << endl;		
	}
}

/*
	Solve [A]{x}={0}
*/
// FUNC_solveAx0
void CameraCalibrator::solveAx0(MatrixXd &L, MatrixXd &H)
{
	MatrixXd U, V;
	VectorXd S;

	computeSVD(L, U, V, S);

	for (int i = 0; i < 9; i++)
		H(i, 0) = V(i, 	8);
}

/* 
	Get homography between model and image points.
*/
// FUNC_homography
int CameraCalibrator::homography(Matrix<double, 3, 1> modelPoints[]
							   , Matrix<double, 3, 1> imagePoints[]
							   , MatrixXd &H)
{
	MatrixXd L(2 * NUM_POINTS, 9);

	/* Assembles coefficients matrix L */
	for(int k = 0; k < NUM_POINTS; k++)
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

	// Solve the system [L]{H}={0}
	solveAx0(L, H); 

	if (PRINT)
		cout << "[H]:\n" << H << endl;

	return 0;
}

/*
	True if the determinant < 0.
*/
// FUNC_trueRotSol
int CameraCalibrator::trueRotSol(Vector3d &r1, Vector3d &r2)
{
	Vector3d r3 = r1.cross(r2);
	MatrixXd R(3, 3);
	R << r1, r2, r3;

	if (PRINT)
		cout << "Determinant of R: " << R.determinant() << endl;

	if (R.determinant() > 0)
		// Basically meaning if determinant is 1
		return 0;
	else
		return 1;
}

/*
	Use SVD to get the optimized orthogonal rotation matrix.
*/
// FUNC_fixRotation
void CameraCalibrator::fixRotation(Vector3d &r1, Vector3d &r2, Vector3d &r3)
{
	MatrixXd R(3, 3);
	R << r1, r2, r3;

	if (PRINT)
		getMatParams(R);

	MatrixXd U, V;
	VectorXd S;

	computeSVD(R, U, V, S);

	if (PRINT)
		cout << R - (U * V.transpose()) << endl;

	R = U * V.transpose();

	if (PRINT)
		getMatParams(R);

	r1 = R.col(0);
	r2 = R.col(1);
	r3 = R.col(2);
}

/*
	Normalizes points in a matrix.
*/
// FUNC_divByLastRowInPlace
void CameraCalibrator::divByLastRowInPlace(MatrixXd &X)
{
	int rowsMinusOne = X.rows() - 1;
	for(int i = 0; i < X.cols(); i++)
	{
		for(int j = 0; j < X.rows(); j++)
		{
			X(j, i) = X(j, i) / X(rowsMinusOne, i);
		}
	}
}

/*
	Computes the mean rotation and translation vectors.
*/
// FUNC_computeRTMean
Matrix4d CameraCalibrator::computeRTMean(MatrixXd &rotVecs, MatrixXd &transVecs)
{
	// Calculate the mean of the Rodrigues-rotation and translation vectors
	Matrix<double, 3, 1> meanRotVec;
	meanRotVec << rotVecs.row(0).sum(), rotVecs.row(1).sum(), rotVecs.row(2).sum();
	meanRotVec /= rotVecs.cols();

	Matrix<double, 3, 1> meanTransVec;
	meanTransVec << transVecs.row(0).sum(), transVecs.row(1).sum(), transVecs.row(2).sum();
	meanTransVec /= transVecs.cols();

	// Convert the mean Rodrigues-rotation vector back into a 3x3 rotation matrix
	double eigMeanRotVec[3] = { meanRotVec(0,0), meanRotVec(1,0), meanRotVec(2,0) };
	Mat cvMeanRotMat;
	Mat cvMeanRotVec = Mat(3, 1, CV_64FC1, eigMeanRotVec);
	Rodrigues(cvMeanRotVec, cvMeanRotMat);
	Matrix3d meanRotMat;
	meanRotMat << cvMeanRotMat.at<double>(0,0), cvMeanRotMat.at<double>(0,1), cvMeanRotMat.at<double>(0,2),
				  cvMeanRotMat.at<double>(1,0), cvMeanRotMat.at<double>(1,1), cvMeanRotMat.at<double>(1,2),
				  cvMeanRotMat.at<double>(2,0), cvMeanRotMat.at<double>(2,1), cvMeanRotMat.at<double>(2,2);

	// Construct the new averaged 4x4 RT matrix
	Matrix4d RT;
	RT << meanRotMat, meanTransVec, 0, 0, 0, 1;

	cout << "RTMean:\n" << RT << endl;

	return RT;
}

/*
   Gets the camera intrinsic matrix. Camera parameters are currently
   hardcoded for convenience.
*/
// FUNC_getIntrinsicParams
Matrix3d CameraCalibrator::getIntrinsicParams(string serial)
{
	Matrix3d A;
	
	if (serial == "051860134447")
	{
		A << 367.629, 		0, 253.773,
	     	       0, 367.629,  200.89,
     		       0, 		0, 	   1.0;
	}
	else
	{
		A << 365.683,       0, 260.452,
		           0, 365.683, 208.018,
		           0,       0,     1.0;
	}
	
	if (PRINT)
	{
		cout << "[A]:\n" << A << endl;
	}

	return A;
}

/*
	Computes the homography (3x3, 2D homogeneous->2D homogeneous)
	from the given image.
*/
// FUNC_computeHomographyForImage
Matrix4d CameraCalibrator::computeHomographyForImage(Mat image, string serial)
{
	Size imgSize(512, 424);
	// Size imgSize(1920, 1080);
	double h = imgSize.height, w = imgSize.width;

	// Corners of model board (2D homogeneous)
	Matrix<double, 3, 1> modelPoints[NUM_POINTS];

	// Corners found in image
	Matrix<double, 3, 1> imagePoints[1][NUM_POINTS];

	// Reconstructed image points
	Matrix<double, 3, 1> imagePointsComp[1][NUM_POINTS];

	createModel(modelPoints);
	
	// Get the corners in the image
	bool valid = registerCorners(image, imagePoints[0]);

	Matrix4d RT;
	Matrix<double, 3, 4> tmpRT;

	if (!valid)
		return RT;

	// Compute homography for the pairs of points
	MatrixXd H(9,1);
	homography(modelPoints, imagePoints[0], H);
	
	if (PRINT)
		cout << "[H]:\n" << H << endl;

	// Resize the homography vector into a 3x3 matrix, but need to
	// transpose after because resize() orders the entries in the
	// wrong position
	H.resize(3,3);
	H.transposeInPlace();

	if (PRINT)
		cout << "After resizing [H]:\n" << H << endl;

	// Intrinsic matrix (3x3)
	Matrix3d A = getIntrinsicParams(serial);
	Matrix3d hIdeal = A.inverse() * H;

	// Build the rotation matrix
	Vector3d r1 = hIdeal.col(0);
	Vector3d r2 = hIdeal.col(1);
	double r1Norm = r1.norm();
	double r2Norm = r2.norm();
	r1 /= r1Norm;
	r2 /= r2Norm;
	
	// Find the correct Z-rotation by checking if determinant > 0
	Vector3d r3;
	int trueSol = trueRotSol(r1, r2);
	if (trueSol)
		r3 = r2.cross(r1);
	else
		r3 = r1.cross(r2);
	
	// Translation vector
	Vector3d t = hIdeal.col(2);
	t *= ((1.0/r1Norm) + (1.0/r2Norm)) / 2.0;

	if (PRINT)
		cout << "T is : " << t << endl;

	// Fix the orthogonality issue of R using SVD
	fixRotation(r1, r2, r3);

	Matrix<double, 1, 4> lastRow;
	lastRow << 0, 0, 0, 1;

	// Extrinsic matrix (4x4)
	tmpRT.col(0) = r1;
	tmpRT.col(1) = r2;
	tmpRT.col(2) = r3;
	tmpRT.col(3) = t;

	RT << tmpRT, lastRow;

	if (DRAW_CORNERS)
		reconstructChessboard(image, imagePoints[0], imagePointsComp[0]);

	return RT;
}

/*
	Bundle adjustment.
*/
// FUNC_bundleAdjustment
Matrix4d CameraCalibrator::bundleAdjustment(
	string serial1, vector<Point2d> image1Points, vector<Matrix4d> ext1,
	string serial2, vector<Point2d> image2Points, vector<Matrix4d> ext2)
{
	// Save the extrinsic matrices in a single array
	//
	// These parameters will be modified after ceres::Solve
	double camera[NUM_VIEWS * 12];

	// Each matrix occupies 6 elements, ordered as
	// R1, R2, R3, T1, T2, T3
	// where R* are the entries in the Rodrigues-equivalent vector
	for (int i = 0; i < NUM_VIEWS; i++)
	{
		// RT for camera 1 image
		Matrix4d RT1 = ext1[i];
		double tempRT1[9] = { RT1(0,0), RT1(0,1), RT1(0,2), RT1(1,0), RT1(1,1), RT1(1,2), RT1(2,0), RT1(2,1), RT1(2,2) };
		Mat cvRotVec1;
		Mat cvRotMat1 = Mat(3, 3, CV_64FC1, tempRT1);
		Rodrigues(cvRotMat1, cvRotVec1);
		camera[12 * i] = cvRotVec1.at<double>(0,0);
		camera[12 * i + 1] = cvRotVec1.at<double>(1,0);
		camera[12 * i + 2] = cvRotVec1.at<double>(2,0);
		camera[12 * i + 3] = RT1(0,3);
		camera[12 * i + 4] = RT1(1,3);
		camera[12 * i + 5] = RT1(2,3);

		// RT for camera 2 image
		Matrix4d RT2 = ext2[i];
		double tempRT2[9] = { RT2(0,0), RT2(0,1), RT2(0,2), RT2(1,0), RT2(1,1), RT2(1,2), RT2(2,0), RT2(2,1), RT2(2,2) };
		Mat cvRotVec2;
		Mat cvRotMat2 = Mat(3, 3, CV_64FC1, tempRT2);
		Rodrigues(cvRotMat2, cvRotVec2);
		camera[12 * i + 6] = cvRotVec2.at<double>(0,0);
		camera[12 * i + 7] = cvRotVec2.at<double>(1,0);
		camera[12 * i + 8] = cvRotVec2.at<double>(2,0);
		camera[12 * i + 9] = RT2(0,3);
		camera[12 * i + 10] = RT2(1,3);
		camera[12 * i + 11] = RT2(2,3);
	}

	if (PRINT)
	{
		cout << "Extrinsic matrices pre-optimization: " << endl;
		for (int i = 0; i < NUM_VIEWS * 2; i++)
		{
			for (int j = j; j < 6; j++)
			{
				cout << camera[i * 6 + j] << ", ";
			}
			cout << endl;
		}
	}

	// Get the intrinsic matrix of each camera
	double intrinsics[4];
	Matrix3d A1 = getIntrinsicParams(serial1);
	intrinsics[0] = A1(0,0);
	intrinsics[1] = A1(1,1);
	intrinsics[2] = A1(0,2);
	intrinsics[3] = A1(1,2);

	double intrinsics2[4];
	Matrix3d A2 = getIntrinsicParams(serial2);
	intrinsics2[0] = A2(0,0);
	intrinsics2[1] = A2(1,1);
	intrinsics2[2] = A2(0,2);
	intrinsics2[3] = A2(1,2);

	if (PRINT)
	{
		cout << "Intrinsics 1: " << A1 << endl;
		cout << "Intrinsics 2: " << A2 << endl;
	}

	// Model board points
	//
	// These points will be modified after ceres::Solve
	double pointProj[NUM_VIEWS * NUM_POINTS][3];

	// Optimize the extrinsic matrices and the model board points
	ceres::Problem problem;
	for (int i = 0; i < NUM_VIEWS; i++)
	{
		for (int j = 0; j < NUM_POINTS; j++)
		{
			// Each pair of images gets their own model board
			pointProj[i * NUM_POINTS + j][0] = _modelPoints3D(0, j);
			pointProj[i * NUM_POINTS + j][1] = _modelPoints3D(1, j);
			pointProj[i * NUM_POINTS + j][2] = _modelPoints3D(2, j);

	  		ceres::CostFunction* cost_function =
	  					new ceres::AutoDiffCostFunction<ReprojectionError, 4, 12 * NUM_VIEWS, 3>(
	                 		new ReprojectionError(image1Points[i * NUM_POINTS + j]
	                 							, image2Points[i * NUM_POINTS + j]
	                 							, intrinsics
	                 							, intrinsics2
	                 							, i));
	  		problem.AddResidualBlock(cost_function,
	        	                   	 NULL, //squared loss,
	            	               	 camera,
	            	               	 pointProj[i * NUM_POINTS + j]);
  		}
	}
	ceres::Solver::Options options;
	options.linear_solver_type = ceres::DENSE_SCHUR;
	options.minimizer_progress_to_stdout = true;
	ceres::Solver::Summary summary;
	ceres::Solve(options, &problem, &summary);
	cout << summary.FullReport() << endl;

	if (PRINT)
	{
		cout << "Extrinsic matrices post-optimization: " << endl;
		for (int i = 0; i < NUM_VIEWS * 2; i++)
		{
			for (int j = j; j < 6; j++)
			{
				cout << camera[i * 6 + j] << ", ";
			}
			cout << endl;
		}
	}

	if (DRAW_CORNERS)
	{
		// Draw corners to test new RT matrix
	    double camRot[3] = {camera[0], camera[1], camera[2]};
	    Mat rotVec = Mat(3, 1, CV_64FC1, camRot);
		Mat rotMat;
		Rodrigues(rotVec, rotMat);
		Matrix<double, 3, 4> rtMat;
		rtMat << rotMat.at<double>(0,0), rotMat.at<double>(0,1), rotMat.at<double>(0,2), camera[3],
				 rotMat.at<double>(1,0), rotMat.at<double>(1,1), rotMat.at<double>(1,2), camera[4],
				 rotMat.at<double>(2,0), rotMat.at<double>(2,1), rotMat.at<double>(2,2), camera[5];
		MatrixXd points(4, 63);
		for (int i = 0; i < 63; i++)
		{
			points(0,i) = pointProj[i][0];
			points(1,i) = pointProj[i][1];
			points(2,i) = pointProj[i][2];
			points(3,i) = 1;
		}
		points = A1 * rtMat * points;
		divByLastRowInPlace(points);
		Mat img = imread("imagefolder/kinect10.jpg");
		int step = 255/126;
		int col = step * 63;
		for (int i = 0; i < 63; i++)
		{
			Point2d pt(points(0,i), points(1,i));
			circle(img, pt, 3, (0,0,col), 2);
			col += step;
		}
		imshow("Reproj", img);

		double camRot2[3] = {camera[6], camera[7], camera[8]};
	    Mat rotVec2 = Mat(3, 1, CV_64FC1, camRot2);
		Mat rotMat2;
		Rodrigues(rotVec2, rotMat2);
		Matrix<double, 3, 4> rtMat2;
		rtMat2 << rotMat2.at<double>(0,0), rotMat2.at<double>(0,1), rotMat2.at<double>(0,2), camera[9],
				  rotMat2.at<double>(1,0), rotMat2.at<double>(1,1), rotMat2.at<double>(1,2), camera[10],
				  rotMat2.at<double>(2,0), rotMat2.at<double>(2,1), rotMat2.at<double>(2,2), camera[11];
		MatrixXd points2(4, 63);
		for (int i = 0; i < 63; i++)
		{
			points2(0,i) = pointProj[i][0];
			points2(1,i) = pointProj[i][1];
			points2(2,i) = pointProj[i][2];
			points2(3,i) = 1;
		}
		points2 = A2 * rtMat2 * points2;
		divByLastRowInPlace(points2);
		Mat img2 = imread("imagefolder/kinect20.jpg");
		int step2 = 255/126;
		int col2 = step2 * 63;
		for (int i = 0; i < 63; i++)
		{
			Point2d pt(points2(0,i), points2(1,i));
			circle(img2, pt, 3, (0,0,col2), 2);
			col2 += step2;
		}
		imshow("Reproj2", img2);
	}

	Matrix<double, 1, 4> lastRow;
	lastRow << 0, 0, 0, 1;

	// Compute the camera transformation matrix for each pair of images
	// and find the mean camera transformation matrix for this set
	MatrixXd rotVecs(3, NUM_VIEWS);
	MatrixXd transVecs(3, NUM_VIEWS);

    for (int i = 0; i < NUM_VIEWS; i++)
    {
    	// RT1
    	double camRot1[3] = {camera[12 * i], camera[12 * i + 1], camera[12 * i + 2]};
	    Mat rotVec1 = Mat(3, 1, CV_64FC1, camRot1);
		Mat rotMat1;
		Rodrigues(rotVec1, rotMat1);
		Matrix<double, 3, 4> rtMat1;
		rtMat1 << rotMat1.at<double>(0,0), rotMat1.at<double>(0,1), rotMat1.at<double>(0,2), camera[12 * i + 3],
				  rotMat1.at<double>(1,0), rotMat1.at<double>(1,1), rotMat1.at<double>(1,2), camera[12 * i + 4],
				  rotMat1.at<double>(2,0), rotMat1.at<double>(2,1), rotMat1.at<double>(2,2), camera[12 * i + 5];

		// RT2
		double camRot2[3] = {camera[12 * i + 6], camera[12 * i + 7], camera[12 * i + 8]};
    	Mat rotVec2 = Mat(3, 1, CV_64FC1, camRot2);
		Mat rotMat2;
		Rodrigues(rotVec2, rotMat2);
		Matrix<double, 3, 4> rtMat2;
		rtMat2 << rotMat2.at<double>(0,0), rotMat2.at<double>(0,1), rotMat2.at<double>(0,2), camera[12 * i + 9],
				  rotMat2.at<double>(1,0), rotMat2.at<double>(1,1), rotMat2.at<double>(1,2), camera[12 * i + 10],
				  rotMat2.at<double>(2,0), rotMat2.at<double>(2,1), rotMat2.at<double>(2,2), camera[12 * i + 11];  

		Matrix4d tempRT1, tempRT2;
		tempRT1 << rtMat1, lastRow;
		tempRT2 << rtMat2, lastRow;

		// RT1 * RT2.inverse()
		Matrix4d RT = tempRT1 * tempRT2.inverse();

		if (PRINT)
		{
			cout << "RT" << i << ":\n" << RT << endl;
		}

		// Convert the rotation matrix into angle-axis
		double rot[9] = { RT(0,0), RT(0,1), RT(0,2), RT(1,0), RT(1,1), RT(1,2), RT(2,0), RT(2,1), RT(2,2) };
		Mat cvRotMat = Mat(3, 3, CV_64FC1, rot);
		Mat cvRotVec;
		Rodrigues(cvRotMat, cvRotVec);

		Matrix<double, 1, 3> rotVec, transVec;
		rotVec << cvRotVec.at<double>(0,0), cvRotVec.at<double>(1,0), cvRotVec.at<double>(2,0);
		transVec << RT(0,3), RT(1,3), RT(2,3);

		rotVecs.col(i) = rotVec;
		transVecs.col(i) = transVec;
    }

	return computeRTMean(rotVecs, transVecs);
}

/*
	Bundle adjustment interface.
*/
// FUNC_doBundleAdjustment
Matrix4d CameraCalibrator::doBundleAdjustment(string serial1, string *file1, string serial2, string *file2)
{
	// Collect all the corner positions from each image
	vector<Point2d> corners1, corners2;

	// Collect each extrinsic matrix
	vector<Matrix4d> ext1, ext2;

	for (int i = 0; i < NUM_VIEWS; i++)
	{
		// Compute RT for camera 1 image
		Mat image1 = imread(file1[i]);
		Matrix4d RT1 = computeHomographyForImage(image1, serial1);
		ext1.push_back(RT1);

		// Compute RT for camera 2 image
		Mat image2 = imread(file2[i]);
		Matrix4d RT2 = computeHomographyForImage(image2, serial2);
		ext2.push_back(RT2);

		// Need to read images again in order to save the corners
		image1 = imread(file1[i]);
		vector<Point2d> temp1;
		findChessboardCorners(image1, _boardSize, temp1,
			CALIB_CB_ADAPTIVE_THRESH | CALIB_CB_NORMALIZE_IMAGE);

		image2 = imread(file2[i]);
		vector<Point2d> temp2;
		findChessboardCorners(image2, _boardSize, temp2,
			CALIB_CB_ADAPTIVE_THRESH | CALIB_CB_NORMALIZE_IMAGE);

		for (int j = 0; j < NUM_POINTS; j++)
		{
			corners1.push_back(temp1[j]);
			corners2.push_back(temp2[j]);
		}
	}

	return bundleAdjustment(serial1, corners1, ext1, serial2, corners2, ext2);
}


/** ********** FUNCTIONS FOR TESTING ********** */

/*
	Draws circles on an image given the points.
*/
// FUNC_reconstructChessboard
void CameraCalibrator::reconstructChessboard(Mat image
						 				   , Matrix<double, 3, 1> imagePoints[]
						 				   , Matrix<double, 3, 1> imagePointsComp[])
{
	for (int i = 0; i < NUM_POINTS; i++)
	{
		Point2f tmpCentre(imagePoints[i](0,0), imagePoints[i](1,0));
		circle(image, tmpCentre, 10, (0,0,255), 2);
	}

	for (int i = 0; i < NUM_POINTS; i++)
	{
		Point2f tmpCentre(imagePointsComp[i](0,0), imagePointsComp[i](1,0));
		circle(image, tmpCentre, 7.5, (255,0,0), 2);
	}

	// Somehow adding this makes the code run faster!
	imshow("reconstructChessboard", image);
}

/*
	Print the properties of the given matrix.
*/
// FUNC_getMatParams
void CameraCalibrator::getMatParams(MatrixXd X)
{
	cout << "[X]:\n" << X << endl;
	cout << "det(X): " << X.determinant() << endl;
	cout << "[XX']:\n" << X*X.transpose() << endl;
}


/** ********** TYPERECIPIENT ********** **/

void CameraCalibrator::processType(SimplePool<KinectFrame>::PooledPtr t)
{
	// ArrayPt3DCollection pts = t->getRegisteredPts();

	// for (int i = 0; i < pts.getNPts(); i++)
	// {
	// 	CameraSpacePoint *temp = pts.getCameraPt(i);
	// 	if (!isnan(temp->X))
	// 	cout << temp->X << "," << temp->Y << "," << temp->Z << endl;
	// }
	// Mat image = t->_rgb;
	Mat image = t->_depthBGRA;
	// cout << image.rows << ", " << image.cols << ", " << image.channels() << endl;
	// cvtColor(image, image, COLOR_BGR2RGB);
	// imshow("Frame to save", image);//)image);

	// computeHomographyForImage(image);

	// fireUpdate(image);
}


/** ********** UNUSED CODE ********** **/

CameraCalibrator::CameraCalibrator(string settingsFile)
{
	ifstream input;
	input.open(settingsFile);
	
	if (!input.is_open())
	{
		return;
	}

	string line, flag;
	while (1)
	{
		getline(input, line);
		if (input.eof())
			break;	

		flag = "image_size";
		if (!line.compare(0, flag.size(), flag))
		{
			string width = line.substr(flag.size() + 1, line.find(",") - flag.size() - 1);
			string height = line.substr(line.find(",") + 1);
			_imageSize = Size(stod(width), stod(height));
			cout << "got the imagesize: " << _imageSize.width << "," << _imageSize.height << endl;
			continue;
		}

		flag = "board_size";
		if (!line.compare(0, flag.size(), flag))
		{
			string width = line.substr(flag.size() + 1, line.find(",") - flag.size() - 1);
			string height = line.substr(line.find(",") + 1);
			_boardSize = Size(stod(width), stod(height));
			continue;
		}

		flag = "square_size";
		if (!line.compare(0, flag.size(), flag))
		{
			string size = line.substr(flag.size() + 1);
			_squareSize = stof(size);
			continue;
		}
	}
}

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

void CameraCalibrator::calcBoardCornerPositions(vector<Point3f> &corners)
{
	corners.clear();
	for( int i = 0; i < _boardSize.height; ++i )
	{
            for( int j = 0; j < _boardSize.width; ++j )
                corners.push_back(Point3f(j*_squareSize, i*_squareSize, 0));
	}
}


double CameraCalibrator::computeReprojectionErrors(
	const vector<vector<Point3f> >& objectPoints)
{
	vector<Point2f> imagePoints2;
	size_t totalPoints = 0;
	double totalErr = 0, err;
	_reprojErrors.resize(objectPoints.size());

	for(size_t i = 0; i < objectPoints.size(); ++i )
	{
		projectPoints(objectPoints[i], _rvecs[i], _tvecs[i],
			_camMatrix, _distCoeffs, imagePoints2);
		err = norm(_imagePoints[i], imagePoints2, NORM_L2);

		size_t n = objectPoints[i].size();
		_reprojErrors[i] = (float) std::sqrt(err*err/n);
		totalErr        += err*err;
		totalPoints     += n;
	}

	return std::sqrt(totalErr/totalPoints);
}

bool CameraCalibrator::runCalibration(double &totalAvgErr)
{
	vector<vector<Point3f> > objectPoints(1);
	calcBoardCornerPositions(objectPoints[0]);
	objectPoints.resize(_imagePoints.size(), objectPoints[0]);

	double rms = calibrateCamera(objectPoints, _imagePoints,
			_imageSize, _camMatrix, _distCoeffs, _rvecs, _tvecs);
	
	cout << "Re-projection error reported by calibrateCamera: "<< rms << endl;
	bool ok = checkRange(_camMatrix) && checkRange(_distCoeffs);

	totalAvgErr = computeReprojectionErrors(objectPoints);
	return ok;
}

bool CameraCalibrator::runCalibrationAndSave()
{
	double totalAvgErr = 0;

	if (runCalibration(totalAvgErr))
	{
		// Save the settings in a text file
		ofstream output;
		output.open("settings.txt");

		if (output.is_open())
		{
			output << "image_size " << _imageSize.width << ","
					<< _imageSize.height << endl;

			output << "board_size " << _boardSize.width << ","
					<< _boardSize.height << endl;

			output << "square_size " << _squareSize << endl;

			output << "camera_matrix " << _camMatrix << endl;
			output << "distortion_coeffs " << _distCoeffs << endl;

			output << "avg_reproj_error " << totalAvgErr << endl;
			output << "img_reproj_error " << Mat(_reprojErrors) << endl;
			

    			if (!_rvecs.empty() && !_tvecs.empty())
			{
        			Mat bigmat((int)_rvecs.size(), 6,
					_rvecs[0].type());
        			for (size_t i = 0; i < _rvecs.size(); i++)
				{
					Mat r = bigmat(Range(int(i), int(i+1)),
							Range(0,3));
					Mat t = bigmat(Range(int(i), int(i+1)),
							Range(3,6));

					r = _rvecs[i].t();
					t = _tvecs[i].t();
				}
        			output << "extrinsic_parameters " << bigmat;
			}

			if (!_imagePoints.empty())
			{
				Mat imagePtMat((int) _imagePoints.size(),
					(int) _imagePoints[0].size(), CV_32FC2);
				for (size_t i = 0; i < _imagePoints.size(); i++)
				{
					Mat r = imagePtMat.row(int(i)).reshape(
							2, imagePtMat.cols);
					Mat imgpti(_imagePoints[i]);
					imgpti.copyTo(r);
				}
				output << "image_points " << imagePtMat;
			}

			output.close();
		}
	}
}

void CameraCalibrator::calibrate(
	int numFiles,
	Size &imageSize, Size &boardSize, float squareSize)
{
	_imageSize = imageSize;
	_boardSize = boardSize;
	_squareSize = squareSize;

	Mat image;
	for (size_t i = 0; i < NUM_VIEWS; i++)
	{
		// Read the next image in the folder
		image = imread("imagefolder/image" + to_string(i) + ".jpg", CV_LOAD_IMAGE_GRAYSCALE);

		// See if we can detect the corners
		vector<Point2f> corners;
		bool found = findChessboardCorners(image, _boardSize, corners,
			CALIB_CB_ADAPTIVE_THRESH | CALIB_CB_NORMALIZE_IMAGE);

		if (found)
		{
			// Save and draw the corners
			cornerSubPix(image, corners, Size(11,11), Size(-1, -1),
			TermCriteria(TermCriteria::EPS + TermCriteria::COUNT, 30, 0.1));
			
			_imagePoints.push_back(corners);			

	        drawChessboardCorners(image, _boardSize, Mat(corners), found);
	
			imshow("something", image);
			//waitKey(0);
		}
	}

	// Calibrate only if we've found corners in at least one image
	if (_imagePoints.size())
	{
		runCalibrationAndSave();
	}
	else
	{
		cout << "No corners found." << endl;
	}
}