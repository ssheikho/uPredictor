(* ::Package:: *)

(* ::Code::Initialization:: *)
DenavitHartenbergTransform[inA_,inAlpha_, inD_, inTheta_]:=
{
{Cos[inTheta], -Sin[inTheta] * Cos[inAlpha], Sin[inTheta] * Sin[inAlpha], inA * Cos[inTheta]},{Sin[inTheta], Cos[inTheta] * Cos[inAlpha], -Cos[inTheta] * Sin[inAlpha], inA * Sin[inTheta]},{0, Sin[inAlpha] , Cos[inAlpha], inD},
{0, 0, 0, 1}
}


(* ::Code::Initialization:: *)
WAM7DOF[inThetaVect_]:=
DenavitHartenbergTransform[0,-Pi/2, 0, inThetaVect[[1]]].
DenavitHartenbergTransform[0,Pi/2, 0, inThetaVect[[2]]].
DenavitHartenbergTransform[0.045,-Pi/2, 0.55, inThetaVect[[3]]].
DenavitHartenbergTransform[-0.045,Pi/2,0, inThetaVect[[4]]].
DenavitHartenbergTransform[0,-Pi/2,0.3, inThetaVect[[5]]].
DenavitHartenbergTransform[0,Pi/2,0, inThetaVect[[6]]].
DenavitHartenbergTransform[0,0,0.06, inThetaVect[[7]]]



(* ::Code::Initialization:: *)
WAM7DOFToJoint4[inThetaVect_]:=
DenavitHartenbergTransform[0,-Pi/2, 0, inThetaVect[[1]]].
DenavitHartenbergTransform[0,Pi/2, 0, inThetaVect[[2]]].
DenavitHartenbergTransform[0.045,-Pi/2, 0.55, inThetaVect[[3]]].
DenavitHartenbergTransform[-0.045,Pi/2,0, inThetaVect[[4]]]


(* ::Code::Initialization:: *)
WAM7DOFJ0J4J7Pos[inThetas_]:=
{
WAM7DOF[inThetas].{0,0,0,1},
WAM7DOFToJoint4[inThetas].{0,0,0,1},
{0,0,0,1}
}



(* ::Code::Initialization:: *)
ShowWAMPose[inJointAngles_, inMinPlot_, inMaxPlot_]:=
Show[{ListPointPlot3D[Transpose[HomToCart3D[Transpose[WAM7DOFJ0J4J7Pos[inJointAngles]]]], AspectRatio->1, PlotRange->{{inMinPlot, inMaxPlot},{inMinPlot, inMaxPlot},{inMinPlot, inMaxPlot}}],
Graphics3D[Line[Transpose[HomToCart3D[Transpose[WAM7DOFJ0J4J7Pos[inJointAngles]]]]]]}]


(* ::Code::Initialization:: *)
LinearInterp [inFrom_, inTo_, inSlices_]:=(
liSlice = (inTo - inFrom)/inSlices;
liOut = {};
For[liI = 0, liI <= inSlices, liI++, AppendTo[liOut, inFrom + liSlice * liI]];
liOut
)


(* ::Code::Initialization:: *)
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


(* ::Code::Initialization:: *)
WAMEEPtsFromConfigurationsW[inConfigurations_]:=(
	ptCt = Dimensions[inConfigurations][[1]];
	ptCollection = {};
	For[ptI = 1, ptI < ptCt, ptI++, AppendTo[ptCollection, WAM7DOF[inConfigurations[[ptI]]].{0,0,0,1}]];
	ptCollection
)


(* ::Code::Initialization:: *)
WAMEEPtsFromConfigurationsE[inConfigurations_]:=(
	ptCt = Dimensions[inConfigurations][[1]];
	ptCollection = {};
	For[ptI = 1, ptI < ptCt, ptI++, AppendTo[ptCollection, WAM7DOFToJoint4[inConfigurations[[ptI]]].{0,0,0,1}]];
	ptCollection
)


(* ::Code::Initialization:: *)
WAM7DOFCartW[inVect_]:=Transpose[{{0.045` Cos[inVect[[1]]] Cos[inVect[[2]]] Cos[inVect[[3]]]+0.55` Cos[inVect[[1]]] Sin[inVect[[2]]]-0.045` Sin[inVect[[1]]] Sin[inVect[[3]]]-0.045` Cos[inVect[[4]]] (Cos[inVect[[1]]] Cos[inVect[[2]]] Cos[inVect[[3]]]-Sin[inVect[[1]]] Sin[inVect[[3]]])+0.045` Cos[inVect[[1]]] Sin[inVect[[2]]] Sin[inVect[[4]]]+0.3` (Cos[inVect[[1]]] Cos[inVect[[4]]] Sin[inVect[[2]]]+(Cos[inVect[[1]]] Cos[inVect[[2]]] Cos[inVect[[3]]]-Sin[inVect[[1]]] Sin[inVect[[3]]]) Sin[inVect[[4]]])+0.06` (-Cos[inVect[[6]]] (-Cos[inVect[[1]]] Cos[inVect[[4]]] Sin[inVect[[2]]]-(Cos[inVect[[1]]] Cos[inVect[[2]]] Cos[inVect[[3]]]-Sin[inVect[[1]]] Sin[inVect[[3]]]) Sin[inVect[[4]]])+(Cos[inVect[[5]]] (Cos[inVect[[4]]] (Cos[inVect[[1]]] Cos[inVect[[2]]] Cos[inVect[[3]]]-Sin[inVect[[1]]] Sin[inVect[[3]]])-Cos[inVect[[1]]] Sin[inVect[[2]]] Sin[inVect[[4]]])+(-Cos[inVect[[3]]] Sin[inVect[[1]]]-Cos[inVect[[1]]] Cos[inVect[[2]]] Sin[inVect[[3]]]) Sin[inVect[[5]]]) Sin[inVect[[6]]]),0.045` Cos[inVect[[2]]] Cos[inVect[[3]]] Sin[inVect[[1]]]+0.55` Sin[inVect[[1]]] Sin[inVect[[2]]]+0.045` Cos[inVect[[1]]] Sin[inVect[[3]]]-0.045` Cos[inVect[[4]]] (Cos[inVect[[2]]] Cos[inVect[[3]]] Sin[inVect[[1]]]+Cos[inVect[[1]]] Sin[inVect[[3]]])+0.045` Sin[inVect[[1]]] Sin[inVect[[2]]] Sin[inVect[[4]]]+0.3` (Cos[inVect[[4]]] Sin[inVect[[1]]] Sin[inVect[[2]]]+(Cos[inVect[[2]]] Cos[inVect[[3]]] Sin[inVect[[1]]]+Cos[inVect[[1]]] Sin[inVect[[3]]]) Sin[inVect[[4]]])+0.06` (-Cos[inVect[[6]]] (-Cos[inVect[[4]]] Sin[inVect[[1]]] Sin[inVect[[2]]]-(Cos[inVect[[2]]] Cos[inVect[[3]]] Sin[inVect[[1]]]+Cos[inVect[[1]]] Sin[inVect[[3]]]) Sin[inVect[[4]]])+(Cos[inVect[[5]]] (Cos[inVect[[4]]] (Cos[inVect[[2]]] Cos[inVect[[3]]] Sin[inVect[[1]]]+Cos[inVect[[1]]] Sin[inVect[[3]]])-Sin[inVect[[1]]] Sin[inVect[[2]]] Sin[inVect[[4]]])+(Cos[inVect[[1]]] Cos[inVect[[3]]]-Cos[inVect[[2]]] Sin[inVect[[1]]] Sin[inVect[[3]]]) Sin[inVect[[5]]]) Sin[inVect[[6]]]),0.` +0.55` Cos[inVect[[2]]]-0.045` Cos[inVect[[3]]] Sin[inVect[[2]]]+0.045` Cos[inVect[[3]]] Cos[inVect[[4]]] Sin[inVect[[2]]]+0.045` Cos[inVect[[2]]] Sin[inVect[[4]]]+0.3` (Cos[inVect[[2]]] Cos[inVect[[4]]]-Cos[inVect[[3]]] Sin[inVect[[2]]] Sin[inVect[[4]]])+0.06` (-Cos[inVect[[6]]] (-Cos[inVect[[2]]] Cos[inVect[[4]]]+Cos[inVect[[3]]] Sin[inVect[[2]]] Sin[inVect[[4]]])+(Cos[inVect[[5]]] (-Cos[inVect[[3]]] Cos[inVect[[4]]] Sin[inVect[[2]]]-Cos[inVect[[2]]] Sin[inVect[[4]]])+Sin[inVect[[2]]] Sin[inVect[[3]]] Sin[inVect[[5]]]) Sin[inVect[[6]]])}}]


(* ::Code::Initialization:: *)
SimpleThirdOrder[inConstVar_, inVar1_, inVar2_, inVar3_, inMultiplier_]:= inConstVar + inMultiplier * inVar1 + inMultiplier^2 * inVar2+ inMultiplier^3 * inVar3


(* ::Code::Initialization:: *)
SillyIK[inPt_]:=(
sillyIKSol = NMinimize[Norm[Transpose[WAM7DOFCartW[{testTheta1, testTheta2, testTheta3, testTheta4, testTheta5, testTheta6}]][[1]]-inPt],{testTheta1, testTheta2, testTheta3, testTheta4, testTheta5, testTheta6}];
sillyIKVect = {
sillyIKSol[[2,1,2]],
sillyIKSol[[2,2,2]],
sillyIKSol[[2,3,2]],
sillyIKSol[[2,4,2]],
sillyIKSol[[2,5,2]],
sillyIKSol[[2,6,2]],
0};
{sillyIKSol, sillyIKVect}
)


(* ::Code::Initialization:: *)
SimpleThirdOrder7Vect[
	in1Z_, in1A_, in1B_, in1C_,
	in2Z_, in2A_, in2B_, in2C_,
	in3Z_, in3A_, in3B_, in3C_,
	in4Z_, in4A_, in4B_, in4C_,
	in5Z_, in5A_, in5B_, in5C_,
	in6Z_, in6A_, in6B_, in6C_,
	in7Z_, in7A_, in7B_, in7C_,
	inSliderVal_
]:=
	{
		SimpleThirdOrder[in1Z, in1A, in1B, in1C, inSliderVal],
		SimpleThirdOrder[in2Z, in2A, in2B, in2C, inSliderVal],
		SimpleThirdOrder[in3Z, in3A, in3B, in3C, inSliderVal],
		SimpleThirdOrder[in4Z, in4A, in4B, in4C, inSliderVal],
		SimpleThirdOrder[in5Z, in5A, in5B, in5C, inSliderVal],
		SimpleThirdOrder[in6Z, in6A, in6B, in6C, inSliderVal],
		SimpleThirdOrder[in7Z, in7A, in7B, in7C, inSliderVal]
	}


(* ::Code::Initialization:: *)
PathMinFormulaToW[inPts_]:=(
	pmftwNPts = Dimensions[linearPts][[1]];
	pmftwMinForm  = Norm[Transpose[
	WAM7DOFCartW[
		SimpleThirdOrder7Vect[
			testTheta1Z, testTheta1A, testTheta1B, testTheta1C,
			testTheta2Z, testTheta2A, testTheta2B, testTheta2C,
			testTheta3Z, testTheta3A, testTheta3B, testTheta3C,
			testTheta4Z, testTheta4A, testTheta4B, testTheta4C,
			testTheta5Z, testTheta5A, testTheta5B, testTheta5C,
			testTheta6Z, testTheta6A, testTheta6B, testTheta6C,
			testTheta7Z, testTheta7A, testTheta7B, testTheta7C,
			0]
		]
	][[1]]-inPts[[1]]];
	
	sliceSize = 1 / (pmftwNPts-1);

	For[pmftwI = 2, pmftwI<= pmftwNPts, pmftwI++,
		pmftwMinForm = pmftwMinForm +
			Norm[Transpose[
			WAM7DOFCartW[
				SimpleThirdOrder7Vect[
					testTheta1Z, testTheta1A, testTheta1B, testTheta1C,
					testTheta2Z, testTheta2A, testTheta2B, testTheta2C,
					testTheta3Z, testTheta3A, testTheta3B, testTheta3C,
					testTheta4Z, testTheta4A, testTheta4B, testTheta4C,
					testTheta5Z, testTheta5A, testTheta5B, testTheta5C,
					testTheta6Z, testTheta6A, testTheta6B, testTheta6C,
					testTheta7Z, testTheta7A, testTheta7B, testTheta7C,
					(pmftwI - 1) * sliceSize]
					]
				][[1]]-inPts[[pmftwI]]
			]
		];
	pmftwMinForm
)
