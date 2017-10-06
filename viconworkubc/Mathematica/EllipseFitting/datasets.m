(* ::Package:: *)

(* ::Code::Initialization:: *)
Import["vicon_input.m"]
currentDataset = Import["../../Datasets/SaraCal06/DATA SaraCal06.mat"];
ballHolderDataset = Import["../../Datasets/BallHolder/DATA Table.mat"];
wristI = 1;
thumbI = 2;
pinkieI = 3;
elbowI = 4;
shoulderI = 5;


(* ::Code::Initialization:: *)
ExtractReach[inDataset_, inAnnotations_, inWhichTrack_]:={
	wrist->ViconTrackSection[inDataset, 8, annotations[[1,2,inWhichTrack,1]], annotations[[1,2,inWhichTrack,2]]],
	thumb->ViconTrackSection[inDataset, 6, annotations[[1,2,inWhichTrack,1]], annotations[[1,2,inWhichTrack,2]]],
	pinkie->ViconTrackSection[inDataset, 4, annotations[[1,2,inWhichTrack,1]], annotations[[1,2,inWhichTrack,2]]],
	elbow->ViconTrackSection[inDataset, 1, annotations[[1,2,inWhichTrack,1]], annotations[[1,2,inWhichTrack,2]]],
	shoulder->ViconTrackSection[inDataset, 5, annotations[[1,2,inWhichTrack,1]], annotations[[1,2,inWhichTrack,2]]]
}


(* ::Code::Initialization:: *)
ExtractReaches[inDataset_, inAnnotations_]:=(	
	nTracks = Dimensions[inAnnotations[[1,2]]][[1]];
	outTracks = {};
	For[trackI = 1, trackI <= nTracks, trackI++, AppendTo[outTracks, ExtractReach[inDataset, inAnnotations,trackI]]];
	outTracks
)


(* ::Code::Initialization:: *)
AnnotationReachAndConic[inDataset_, inAnnotations_, inWhichTrack_, inWhichInterestPt_]:=(	
	aracReach = ExtractReach[inDataset, inAnnotations, inWhichTrack];
	aracPlaneData = ComputeTrackPlaneData[aracReach, inWhichInterestPt];
	aracOutConic = ComputeConic2D[aracPlaneData[[5,2]]];
	aracOutConicParametric = ComputeParametricEllipseFromConic2D[aracOutConic[[1,2]]];
	axisLenA = aracOutConicParametric[[2,2,1]];
	axisLenB = aracOutConicParametric[[2,2,2]];
	axes = SmallerBigger[axisLenB, axisLenA];
	{
		ARACReach->aracReach,
		ARACPlaneData->aracPlaneData,
		ARACOutConic->aracOutConic,
		ARACOutConicParametric->aracOutConicParametric,
		ARACTrack->inWhichTrack,
		ARACAxisMinor->axes[[1]],
		ARACAxisMajor->axes[[2]],
		ARACAxisRatios->axes[[1]]/axes[[2]]
	}
)

AnnotationReachAndConics[inDataset_, inAnnotations_, inWhichInterestPt_]:=(	
	nTracks = Dimensions[inAnnotations[[1,2]]][[1]];
	outTracks = {};
	For[trackI = 1, trackI <= nTracks, trackI++, AppendTo[outTracks, AnnotationReachAndConic[inDataset, inAnnotations,trackI,inWhichInterestPt]]];
	outTracks
)

LoadAnnotations[]:= 
{
	(*Wrist, Thumb, Pinkie, Elbow, Shoulder*)
	trackMapping = {8,6,4,1,5};
	StartStop->{
		{124,209},
		{406,480},
		{719,803},
		{1076,1152},
		{1155,1253} ,
		{1404,1488} 
	},
	TrackMapping->trackMapping
}
