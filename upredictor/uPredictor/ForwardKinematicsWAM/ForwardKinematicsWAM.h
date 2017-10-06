#include <Eigen/Dense>
#include <list>
#include "DH.h"

using namespace std;


class ForwardKinematics {
private:
	std::list<DH> matrixList;
	VectorXd a, d, alpha, theta;
	void constructAll(void);
	
public:
	ForwardKinematics(VectorXd a, VectorXd d, VectorXd alpha, VectorXd theta);
	Matrix4d getDH4(void);
	Matrix4d getDH7(void);
	Matrix4d getA1(void);
	
	void setTheta(VectorXd theta);

	
};
