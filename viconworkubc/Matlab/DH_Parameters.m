clc;
% close all;
clear all;
%% WAM parameters
a = [0 0 0.045 -0.045 0 0 0];

alpha = [-pi/2 pi/2 -pi/2 pi/2 -pi/2 pi/2 0];

d = [0 0 0.55 0 0.3 0 0.060];
%% WAM angles test1:
SP = [-0.00555155	-1.8016	0.029511	2.70739	0.0265679	-0.265047	0.102334];
Ball_1 = [0.268227	-1.88044	-0.376619	0.228989	0.0876109	-0.10643	-0.134596];
Ball_2 = [0.183932	-1.89668	-0.154853	0.270322	-0.271847	-0.31502	0.0977104];
Ball_3 = [0.0494161	-1.89434	-0.151113	0.302024	-0.179571	-0.413779	-0.223162];
Ball_4 = [-0.193501	-1.89443	-0.151067	0.280804	0.486999	-0.320317	-0.121444];

O = [SP; Ball_1; Ball_2; Ball_3; Ball_4];

%% Create WAM struct and saving DH parameters

WAM = struct;
for j=1:5
    WAM(j).A1 = [cos(O(j,1)) sin(O(j,1))*cos(alpha(1)) sin(O(j,1))*sin(alpha(1)) a(1)*cos(O(j,1)); sin(O(j,1)) cos(O(j,1))*cos(alpha(1)) -cos(O(j,1))*sin(alpha(1)) a(1)*sin(O(j,1)); 0 sin(alpha(1)) cos(alpha(1)) d(1); 0 0 0 1];
    WAM(j).A2 = [cos(O(j,2)) sin(O(j,2))*cos(alpha(2)) sin(O(j,2))*sin(alpha(2)) a(2)*cos(O(j,2)); sin(O(j,2)) cos(O(j,2))*cos(alpha(2)) -cos(O(j,2))*sin(alpha(2)) a(2)*sin(O(j,2)); 0 sin(alpha(2)) cos(alpha(2)) d(2); 0 0 0 1];
    WAM(j).A3 = [cos(O(j,3)) sin(O(j,3))*cos(alpha(3)) sin(O(j,3))*sin(alpha(3)) a(3)*cos(O(j,3)); sin(O(j,3)) cos(O(j,3))*cos(alpha(3)) -cos(O(j,3))*sin(alpha(3)) a(3)*sin(O(j,3)); 0 sin(alpha(3)) cos(alpha(3)) d(3); 0 0 0 1];
    WAM(j).A4 = [cos(O(j,4)) sin(O(j,4))*cos(alpha(4)) sin(O(j,4))*sin(alpha(4)) a(4)*cos(O(j,4)); sin(O(j,4)) cos(O(j,4))*cos(alpha(4)) -cos(O(j,4))*sin(alpha(4)) a(4)*sin(O(j,4)); 0 sin(alpha(4)) cos(alpha(4)) d(4); 0 0 0 1];
    WAM(j).A5 = [cos(O(j,5)) sin(O(j,5))*cos(alpha(5)) sin(O(j,5))*sin(alpha(5)) a(5)*cos(O(j,5)); sin(O(j,5)) cos(O(j,5))*cos(alpha(5)) -cos(O(j,5))*sin(alpha(5)) a(5)*sin(O(j,5)); 0 sin(alpha(5)) cos(alpha(5)) d(5); 0 0 0 1];
    WAM(j).A6 = [cos(O(j,6)) sin(O(j,6))*cos(alpha(6)) sin(O(j,6))*sin(alpha(6)) a(6)*cos(O(j,6)); sin(O(j,6)) cos(O(j,6))*cos(alpha(6)) -cos(O(j,6))*sin(alpha(6)) a(6)*sin(O(j,6)); 0 sin(alpha(6)) cos(alpha(6)) d(6); 0 0 0 1];
    WAM(j).A7 = [cos(O(j,7)) sin(O(j,7))*cos(alpha(7)) sin(O(j,7))*sin(alpha(7)) a(7)*cos(O(j,7)); sin(O(j,7)) cos(O(j,7))*cos(alpha(7)) -cos(O(j,7))*sin(alpha(7)) a(7)*sin(O(j,7)); 0 sin(alpha(7)) cos(alpha(7)) d(7); 0 0 0 1];
end

for j=1:5
   WAM(j).DH4 = WAM(j).A1*WAM(j).A2*WAM(j).A3*WAM(j).A4;
   WAM(j).DH7 = WAM(j).A1*WAM(j).A2*WAM(j).A3*WAM(j).A4*WAM(j).A5*WAM(j).A6*WAM(j).A7;
end

figure (1)
plot3([WAM(1).DH4(1,4) WAM(1).DH7(1,4)],[WAM(1).DH4(2,4) WAM(1).DH7(2,4)],[WAM(1).DH4(3,4) WAM(1).DH7(3,4)],'mo-','LineWidth',2),xlabel('x'),ylabel('y'),zlabel('z')
hold on
grid on
plot3([WAM(2).DH4(1,4) WAM(2).DH7(1,4)],[WAM(2).DH4(2,4) WAM(2).DH7(2,4)],[WAM(2).DH4(3,4) WAM(2).DH7(3,4)],'ro-','LineWidth',2)
plot3([WAM(3).DH4(1,4) WAM(3).DH7(1,4)],[WAM(3).DH4(2,4) WAM(3).DH7(2,4)],[WAM(3).DH4(3,4) WAM(3).DH7(3,4)],'bo-','LineWidth',2)
plot3([WAM(4).DH4(1,4) WAM(4).DH7(1,4)],[WAM(4).DH4(2,4) WAM(4).DH7(2,4)],[WAM(4).DH4(3,4) WAM(4).DH7(3,4)],'go-','LineWidth',2)
plot3([WAM(5).DH4(1,4) WAM(5).DH7(1,4)],[WAM(5).DH4(2,4) WAM(5).DH7(2,4)],[WAM(5).DH4(3,4) WAM(5).DH7(3,4)],'yo-','LineWidth',2)

