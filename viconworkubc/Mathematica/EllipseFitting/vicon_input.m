(* ::Package:: *)

ViconFrameMat[inViconMats_, inFrame_]:=
Join[
Take[inViconMats,{1,1},{inFrame,inFrame},{1,3}][[1]],
Take[inViconMats,{2,2},{inFrame,inFrame},{1,3}][[1]],
Take[inViconMats,{3,3},{inFrame,inFrame},{1,3}][[1]],
Take[inViconMats,{4,4},{inFrame,inFrame},{1,3}][[1]],
Take[inViconMats,{5,5},{inFrame,inFrame},{1,3}][[1]],
Take[inViconMats,{6,6},{inFrame,inFrame},{1,3}][[1]],
Take[inViconMats,{7,7},{inFrame,inFrame},{1,3}][[1]],
Take[inViconMats,{8, 8},{inFrame,inFrame},{1,3}][[1]]
]


ViconTrackSection[inViconMats_, inJoint_, inStartFrame_, inEndFrame_]:= (
viconTrackSectionOutM = Take[inViconMats,{inJoint,inJoint},{inStartFrame,inStartFrame},{1,3}][[1]];
For[vtsi = inStartFrame + 1, vtsi <= inEndFrame, vtsi++, AppendTo[viconTrackSectionOutM, Take[inViconMats,{inJoint,inJoint},{vtsi,vtsi},{1,3}][[1,1]]];];
viconTrackSectionOutM
)


ConicCenter[inConicSolution_]:=(
	ccBottomTerm = 4 * inConicSolution[[1]] * inConicSolution[[3]] - inConicSolution[[2]] * inConicSolution[[2]];
	{
		((inConicSolution[[2]] * inConicSolution[[5]] - 2 * inConicSolution[[3]] * inConicSolution[[4]]) /ccBottomTerm),
		((inConicSolution[[4]] * inConicSolution[[2]] - 2 * inConicSolution[[1]] * inConicSolution[[5]]) /ccBottomTerm)
	}
)


CartToHom3D[inMat_] := {
Transpose[inMat][[1]],
Transpose[inMat][[2]],
Transpose[inMat][[3]],
ConstantArray[1,Dimensions[Transpose[inMat]][[2]]]
}


CartToHom2D[inMat_] := {
inMat[[1]],
inMat[[2]],
ConstantArray[1,Dimensions[inMat][[2]]]
}


HomToCart2D[inMat_]:=(
htocn = Dimensions[inMat][[2]];
outMat = {};
For[htoci = 1, htoci <= htocn, htoci++, AppendTo[outMat, {inMat[[1,htoci]]/inMat[[3,htoci]],inMat[[2,htoci]]/inMat[[3,htoci]]}]];
Transpose[outMat]
)


HomToCart3D[inMat_]:=(
	htocn = Dimensions[inMat][[2]];
	outMat = {};
	For[htoci = 1, htoci <= htocn, htoci++
		, AppendTo[
			outMat
			, {
				inMat[[1,htoci]]/inMat[[4,htoci]]
				,inMat[[2,htoci]]/inMat[[4,htoci]]
				,inMat[[3,htoci]]/inMat[[4,htoci]]
			}
			]
		];

	Transpose[outMat]
)

Hom2DToCart3DWithOffset[inMat_, inOffset_]:=(
htocn = Dimensions[inMat][[2]];
outMat = {};
For[htoci = 1, htoci <= htocn, htoci++, AppendTo[outMat, {inMat[[1,htoci]]/inMat[[3,htoci]],inMat[[2,htoci]]/inMat[[3,htoci]], inOffset}]];
Transpose[outMat]
)


EllipseK[inConicSolution_]:= - Det[ConicMatFromConicSolution[inConicSolution]]/ Det[AThirtyThreeFromConicSolution[inConicSolution]]


RigidTrans2D[inTheta_, inU0_, inV0_]:={{Cos[inTheta], -Sin[inTheta], inU0},{Sin[inTheta], Cos[inTheta], inV0}, {0,0,1}}


SVDLeastSquares[inA_]:= (
{svdU, svdD, svdV} = SingularValueDecomposition[inA];
Transpose[svdV][[Dimensions[svdD][[2]]]]
)


ConicConstraintMat[inMat_] := (
inMatNRows = Dimensions[inMat][[1]];
inMatA = {};
For[ccmi = 1, ccmi <= inMatNRows, ccmi++,
AppendTo[inMatA,{inMat[[ccmi,1]]*inMat[[ccmi,1]], inMat[[ccmi,1]]*inMat[[ccmi,2]], inMat[[ccmi,2]]*inMat[[ccmi,2]], inMat[[ccmi,1]], inMat[[ccmi,2]], 1}]];
inMatA)


ConicMatFromConicSolution[inSolution_]:={
{inSolution[[1]], inSolution[[2]]/2, inSolution[[4]]/2},
{inSolution[[2]]/2, inSolution[[3]], inSolution[[5]]/2},
{inSolution[[4]] /2,inSolution[[5]]/2, inSolution[[6]]}
};

AThirtyThreeFromConicSolution[inSolution_]:={
	{inSolution[[1]], inSolution[[2]] / 2},
	{inSolution[[2]]/2, inSolution[[3]]}
}

ParametricEllipsePt[inA_, inB_, inTheta_]:={inA * Cos[inTheta], inB * Sin[inTheta]}

ComputeConic2D[inPtsCart2D_]:= (
	ccAMat = ConicConstraintMat[Transpose[inPtsCart2D]];
	ccConicSol = SVDLeastSquares[ccAMat];
	{
		conicSolution->ccConicSol,
		conicMat->ConicMatFromConicSolution[ccConicSol]
	}
)

ComputeParametricEllipseFromConic2D[inConicSolution_]:=(
	cpeA33 = AThirtyThreeFromConicSolution[inConicSolution];
	{cpeEigenVals, cpeEigenVecs} = Eigensystem[cpeA33];
	{
		conicCenter-> ConicCenter[inConicSolution],
		axLens->Sqrt[ EllipseK[inConicSolution] /cpeEigenVals],
		axVecs->cpeEigenVecs,
		axAlpha->ArcTan[cpeEigenVecs[[1,2]],cpeEigenVecs[[1,1]]]
	}
)

EllipseDistanceAtTheta[inParametricEllipse_, inZOffset_, inTheta_, inZPlaneRot_, inInterestPt_]:=
Norm[Transpose[ParametricEllipse3DPt[inParametricEllipse, inZOffset, inTheta, inZPlaneRot]][[1]] - inInterestPt]

LoopTheta[inTheta_]:= (
	a = inTheta;
	While[a > Pi, a = a - (2*Pi)];
	While[a < -Pi, a = a + (2*Pi)];
	a
)

EllipseClosestTheta[inParametric_, inInterestPt_, inRotBack_, inZOffset_, inInitialTheta_]:=(
	minSolution =
		FindMinimum[
		EllipseDistanceAtTheta[inParametric, inZOffset, candidateTheta, inRotBack, inInterestPt]
		, {candidateTheta, inInitialTheta}];
	minTheta = minSolution[[2,1,2]];
	closestPos = Transpose[ParametricEllipse3DPt[inParametric, inZOffset, minTheta, inRotBack]][[1]];
	{
		distance ->minSolution[[1]],
		theta->LoopTheta[minTheta],
		onEllipse->closestPos,
		interestPt->inInterestPt
	}
)

EllipseTestOppositeThetas[inParametric_, inInterestPt_, inRotBack_, inZOffset_, inInitialTheta_]:= (
	outA = EllipseClosestTheta[inParametric, inInterestPt, inRotBack, inZOffset, inInitialTheta];
	outB = EllipseClosestTheta[inParametric, inInterestPt, inRotBack, inZOffset, inInitialTheta + Pi];
	If[outA[[1,2]]<outB[[1,2]], outA, outB]
)

ComputeNearestThetas[inParametric_, inInterestPts_, inRotBack_, inZOffset_]:=(
	ecOut = {};
	ecn = Dimensions[inInterestPts][[1]];
	AppendTo[
		ecOut
		, EllipseTestOppositeThetas[inParametric, inInterestPts[[1]], inRotBack, inZOffset, 0]];
	For[eci = 2, eci <= ecn, eci++
	, AppendTo[
		ecOut
		, EllipseTestOppositeThetas[inParametric, inInterestPts[[eci]], inRotBack, inZOffset, ecOut[[eci - 1, 2,2]]]]];
	ecOut
)

GetThetas[inCNT_]:=(
nThetas = Dimensions[cnt][[1]];
outThetas = {};
For[thetaI = 1, thetaI< nThetas, thetaI++, AppendTo[outThetas,cnt[[thetaI,2,2]]]];
outThetas
)

FlipToClosestTheta[inLastTheta_, inCurTheta_]:=(
	twoPiMore = inCurTheta + (2 * Pi);
	twoPiLess = inCurTheta - (2 * Pi);
	a = If[Abs[inLastTheta - inCurTheta] < Abs[inLastTheta - twoPiMore], inCurTheta, twoPiMore];
	If[Abs[inLastTheta - a] < Abs[inLastTheta - twoPiLess], a, twoPiLess]
)

FlipToClosestThetas[inThetas_]:= (
	nThetas = Dimensions[inThetas][[1]];
	outThetas = {inThetas[[1]]};
	For[thetaI = 2, thetaI < nThetas, thetaI++
		, AppendTo[
			outThetas, FlipToClosestTheta[outThetas[[thetaI - 1]], inThetas[[thetaI]]]]];
	outThetas
)

GetEllipsePositions[inCNT_]:=(
nThetas = Dimensions[cnt][[1]];
outThetas = {};
For[thetaI = 1, thetaI< nThetas, thetaI++, AppendTo[outThetas,cnt[[thetaI,3,2]]]];
outThetas
)

GetOriginalPositions[inCNT_]:=(
nThetas = Dimensions[cnt][[1]];
outThetas = {};
For[thetaI = 1, thetaI< nThetas, thetaI++, AppendTo[outThetas,cnt[[thetaI,4,2]]]];
outThetas
)

ComputeNorms[inVects_]:=(
	nThetas = Dimensions[inVects][[1]];
	outThetas = {};
	For[thetaI = 1, thetaI< nThetas, thetaI++, AppendTo[outThetas,Norm[inVects[[thetaI]]]]];
	outThetas
)

DisceteD[inVect_]:=(
n = Dimensions[inVect][[1]];
out = {};
For[i = 2, i < n, i++, AppendTo[out, inVect[[i]]-inVect[[i-1]]]];
out
)

LinesAlong[inVect_]:=(
	n = Dimensions[inVect][[1]];
	outGraphics = {};
	For[i = 2, i < n, i++,
		AppendTo[outGraphics, Line[{inVect[[i-1]], inVect[[i]]}]
		]
	];
	Graphics3D[outGraphics]
)

(*
RShoM - 5
RElbM - 1
RUArmUM - 7
RWristM - 8
RLArmLM - 2
RLArmUM - 3
RThumbM - 6
RPinkieM - 4
*)


ParametricEllipse3DPt[inParametric_, inZOffset_, inTheta_, inZPlaneRot_]:= inZPlaneRot.Hom2DToCart3DWithOffset[
RigidTrans2D[inParametric[[4,2]],inParametric[[1,2,1]], inParametric[[1,2,2]]].
CartToHom2D[Transpose[{{inParametric[[2,2,1]] * Cos[inTheta], inParametric[[2,2,2]] * Sin[inTheta]}}]],inZOffset]


PlotTracksArmAndPlane[inDataSet_, inPlotRange_, inAnnotationRanges_, inTrackSelection_, inVTSWrist_, inVTSThumb_, inVTSPinkie_, inVTSElbow_, inVTSShoulder_, inWristPlane_]:=
Manipulate[
Show[
{
ListPointPlot3D[
ViconFrameMat[inDataSet, u]
, PlotRange->{{-inPlotRange, inPlotRange},{-inPlotRange, inPlotRange},{-inPlotRange, inPlotRange}}, BoxRatios-> {1,1,1}],
ListPointPlot3D[
inVTSWrist
, PlotRange->{{-inPlotRange, inPlotRange},{-inPlotRange, inPlotRange},{-inPlotRange, inPlotRange}}],
ListPointPlot3D[
inVTSThumb
, PlotRange->{{-inPlotRange, inPlotRange},{-inPlotRange, inPlotRange},{-inPlotRange, inPlotRange}}],
ListPointPlot3D[
inVTSPinkie
, PlotRange->{{-inPlotRange, inPlotRange},{-inPlotRange, inPlotRange},{-inPlotRange, inPlotRange}}],
ListPointPlot3D[
inVTSElbow
, PlotRange->{{-inPlotRange, inPlotRange},{-inPlotRange, inPlotRange},{-inPlotRange, inPlotRange}}],
ListPointPlot3D[
inVTSShoulder
, PlotRange->{{-inPlotRange, inPlotRange},{-inPlotRange, inPlotRange},{-inPlotRange, inPlotRange}}],
Graphics3D[
Line[{ViconFrameMat[inDataSet, u][[5]],ViconFrameMat[inDataSet, u][[1]],ViconFrameMat[inDataSet, u][[7]],ViconFrameMat[inDataSet, u][[5]]}]
],
Graphics3D[
Line[{ViconFrameMat[inDataSet, u][[1]],ViconFrameMat[inDataSet, u][[8]],ViconFrameMat[inDataSet, u][[2]],ViconFrameMat[inDataSet, u][[3]],ViconFrameMat[inDataSet, u][[1]]}]
],
Graphics3D[
Line[{ViconFrameMat[inDataSet, u][[8]],ViconFrameMat[inDataSet, u][[6]],ViconFrameMat[inDataSet, u][[4]],ViconFrameMat[inDataSet, u][[8]]}]
],
ContourPlot3D[inWristPlane[[1,2]].{Px,Py,Pz,1} == 0, {Px,-inPlotRange,inPlotRange}, {Py,-inPlotRange,inPlotRange}, {Pz,-inPlotRange,inPlotRange}]
}
]
, {u, inAnnotationRanges[[inTrackSelection,1]],inAnnotationRanges[[inTrackSelection,2]], 1}
]



ComputePlane[inMat_]:=(
	cpPlane = SVDLeastSquares[Transpose[CartToHom3D[inMat]]];
	cpPlaneNV = {cpPlane[[1]],cpPlane[[2]],cpPlane[[3]]};
	cpPlaneN = Norm[cpPlaneNV];
	cpPlaneNV = cpPlaneNV / cpPlaneN;
	cpPlaneNormalized = cpPlane / cpPlaneN;
	{
		Plane->cpPlane,
		PlaneNormal->cpPlaneNV,
		PlaneNorm->cpPlaneN,
		PlaneNormalized->cpPlaneNormalized
	}
)


SimpleAnnotator[inDataset_]:=Manipulate[
Show[{
ListPointPlot3D[ViconTrackSection[currentDataset, 8,scanStartPt,scanEndPt], PlotStyle->{Blue}],
ListPointPlot3D[ViconTrackSection[currentDataset, 8,reachStartPt,reachEndPt], PlotStyle->{Red}]
}]
,{scanStartPt,1,Dimensions[currentDataset][[2]],1},{scanEndPt,1,Dimensions[currentDataset][[2]],1}
,{reachStartPt,1,Dimensions[currentDataset][[2]],1},{reachEndPt,1,Dimensions[currentDataset][[2]],1}]


ComputeTrackPlane[inTracks_, inTrackIndex_]:= ComputePlane[inTracks[[inTrackIndex,2]]];


ComputeTrackPlaneData[inTracks_, inTrackIndex_]:= (
	ctpdPlane =  ComputeTrackPlane[inTracks, inTrackIndex];
	ctpdRotationMatrix = RotationMatrix[{ctpdPlane[[2,2]], {0,0,1}}];
	offsetPts2D = ctpdRotationMatrix.Transpose[inTracks[[inTrackIndex,2]]];
	meanOffset = Mean[offsetPts2D[[3]]];
	ctpdPts2D = {offsetPts2D[[1]], offsetPts2D[[2]]};
	{
		CTPPlaneData->ctpdPlane,
		CTPRotationMatrix->ctpdRotationMatrix,
		CTPOffsetPts2D->offsetPts2D,
		CTPMeanOffset->meanOffset,
		CTPPts2D->ctpdPts2D
	}
)


SmallerBigger[inA_, inB_]:=If[inA < inB, {inA, inB}, {inB,inA}]


PlaneAndDist[inTrack_, inEndPtHom_]:=(
	plane = ComputePlane[inTrack];
	({plane[[4,2]]}.inEndPtHom)[[1,1]]
)
