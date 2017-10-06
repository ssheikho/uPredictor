#ifndef LEV_MAR_DIF_H
#define LEV_MAR_DIF_H

#include <libmin.h>

//JWH If you do this, the number of parameters shouldn't change.
class LevMarDif {
	public:
		LevMarDif(Minimizable *m, string name,
			int maxIters = -1, bool print = false, double thresh = 0.0001);
		~LevMarDif();

		void update();

	protected:
		Minimizable *_m;
		int _maxIters;
		bool _print;
		double _thresh;
		double _info[10], _opts[5];
		double *_work;
		
};

#endif
