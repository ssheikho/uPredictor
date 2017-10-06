#ifndef VICON_DEFS_H
#define VICON_DEFS_H

enum ViconUnits {
	mm
};

struct ViconTrajEntry {
	double _pos[3];
	bool _present;
};

#endif
