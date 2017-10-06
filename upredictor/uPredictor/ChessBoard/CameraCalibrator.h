#include "ceres/ceres.h"
#include "ceres/rotation.h"
#include "KinectFrame.h"
#include "SimplePool.h"
#include "TypeRecipient.h"

#include <cmath>
#include <eigen3/Eigen/Dense>
#include <eigen3/Eigen/SVD>
#include <eigen3/Eigen/Eigen>
#include <math.h>
#include <opencv2/opencv.hpp>
#include <string>

using namespace std;
using namespace cv;
using namespace Eigen;

#define NUM_POINTS 63 // Number of points per image
#define NUM_VIEWS 10 // Number of pairs of images

class CameraCalibrator
	: public TypeRecipient<SimplePool<KinectFrame>::PooledPtr>
	, public TypeBroadcaster<Mat>
{
public:
	CameraCalibrator();
	~CameraCalibrator();

	Matrix4d computeHomographyForImage(Mat image, string serial);
	Matrix4d bundleAdjustment(string serial1, vector<Point2d> image1Points, vector<Matrix4d> ext1
                          , string serial2, vector<Point2d> image2Points, vector<Matrix4d> ext2);
	Matrix4d doBundleAdjustment(string serial1, string *file1, string serial2, string *file2);

  // TypeRecipient
  void processType(SimplePool<KinectFrame>::PooledPtr t);
  void onStartup() {};

  /** UNUSED **/
  CameraCalibrator(string settingsFile);
  void calibrate(int numFiles,
    Size &imageSize, Size &boardSize, float squareSize);
  bool runCalibration(double &totalAvgErr);
  bool runCalibrationAndSave();

protected:
  void createModel(Matrix<double, 3, 1> modelPoints[]);
  MatrixXd createModel2DCart();
  MatrixXd addRowOfVal(MatrixXd &X, double val);

  bool registerCorners(Mat image, Matrix<double, 3, 1> imagePoints[]);
  void computeSVD(MatrixXd &L, MatrixXd &U, MatrixXd &V, VectorXd &S);
  void solveAx0(MatrixXd &L, MatrixXd &H);
  int homography(Matrix<double, 3, 1> modelPoints[]
               , Matrix<double, 3, 1> imagePoints[]
               , MatrixXd &H);
  int trueRotSol(Vector3d &r1, Vector3d &r2);
  void fixRotation(Vector3d &r1, Vector3d &r2, Vector3d &r3);
  void divByLastRowInPlace(MatrixXd &X);
  Matrix4d computeRTMean(MatrixXd &rowVecs, MatrixXd &transVecs);

  Matrix3d getIntrinsicParams(string serial);

  Size _imageSize, _boardSize;
  float _squareSize;
  MatrixXd _modelPoints3D;

  /** FUNCTIONS FOR TESTING **/
  void reconstructChessboard(Mat image
                           , Matrix<double, 3, 1> imagePoints[]
                           , Matrix<double, 3, 1> imagePointsComp[]);
  void getMatParams(MatrixXd X);

  /** COST FUNCTION FOR BUNDLE ADJUSTMENT **/
  struct ReprojectionError
  {
    ReprojectionError(Point2d pt1, Point2d pt2
                    , double *intrinsics1, double *intrinsics2
                    , int viewNum) :
    _alpha1(intrinsics1[0]), _beta1(intrinsics1[1]), _u1(intrinsics1[2]), _v1(intrinsics1[3])
    , _alpha2(intrinsics2[0]), _beta2(intrinsics2[1]), _u2(intrinsics2[2]), _v2(intrinsics2[3])
    {
      _pt1 = pt1;
      _pt2 = pt2;
      _view = viewNum;
    }

    template <typename T>
    bool operator()(const T* const camera,
                    const T* const point,
                    T* residuals) const
    {
      // Transform the model board for each image
      T pt1[3];
      ceres::AngleAxisRotatePoint(&camera[12 * _view], point, pt1);
      pt1[0] += camera[12 * _view + 3];
      pt1[1] += camera[12 * _view + 4];
      pt1[2] += camera[12 * _view + 5];

      T pt2[3];
      ceres::AngleAxisRotatePoint(&camera[12 * _view + 6], point, pt2);
      pt2[0] += camera[12 * _view + 9];
      pt2[1] += camera[12 * _view + 10];
      pt2[2] += camera[12 * _view + 11];

      // Peproject the transformed model board
      T x = (pt1[0] / pt1[2] * T(_alpha1)) + T(_u1);
      T y = (pt1[1] / pt1[2] * T(_beta1)) + T(_v1);

      T x2 = (pt2[0] / pt2[2] * T(_alpha2)) + T(_u2);
      T y2 = (pt2[1] / pt2[2] * T(_beta2)) + T(_v2);

      // Compute the residual
      // Multi-dimensional residuals seem to result in more accurate optimizations
      residuals[0] = x - T(_pt1.x);
      residuals[1] = y - T(_pt1.y);
      residuals[2] = x2 - T(_pt2.x);
      residuals[3] = y2 - T(_pt2.y);

      return true;
    }

    Point2d _pt1, _pt2;
    int _view;
    double _alpha1, _beta1, _u1, _v1
         , _alpha2, _beta2, _u2, _v2;
  };

  /** UNUSED **/
  void calcBoardCornerPositions(vector<Point3f> &corners);
  double computeReprojectionErrors(
    const vector<vector<Point3f> >& objectPoints);

  vector<vector<Point2f>> _imagePoints;
	Mat _camMatrix		// INTRINSIC MATRIX
	    , _distCoeffs;	// DISTORTION COEFFS
	vector<Mat> _rvecs	// ROTATION VECTORS
		    , _tvecs;	// TRANSLATION VECTORS
	vector<float> _reprojErrors;
};
