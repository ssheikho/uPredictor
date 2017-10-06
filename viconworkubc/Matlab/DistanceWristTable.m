%% DISTANCE BETWEEN HAND AND TABLE
clc;
close all;
% clear all;
%% IMPORT DATA
% RUN TableCoordinates.m before run this script
W=xlsread('Data2Trajectories2.xls',1,'BK:BM');  % Import trajectory of the Wrist

T=xlsread('Data2Trajectories2.xls',1,'BN:BP');  % Import trajectory of the Thumb

Pk=xlsread('Data2Trajectories2.xls',1,'BQ:BS'); % Import trajectory of the Pinkie

%% Wrist
m = length(W(:,1));

W_RB = zeros(1,1);
W_LB = zeros(1,1);
W_M = zeros(1,1);
W_MR = zeros(1,1);
W_ML = zeros(1,1);
W_RF = zeros(1,1);
W_LF = zeros(1,1);

for n=1:m
    W_RB(1,n)=sqrt((RB(1)-W(n,1))^2 + (RB(2)-W(n,2))^2 +(RB(3)-W(n,3))^2);
end

for n=1:m
    W_RF(1,n)=sqrt((RF(1)-W(n,1))^2 + (RF(2)-W(n,2))^2 +(RF(3)-W(n,3))^2);
end

for n=1:m
    W_MR(1,n)=sqrt((MR(1)-W(n,1))^2 + (MR(2)-W(n,2))^2 +(MR(3)-W(n,3))^2);
end

for n=1:m
    W_M(1,n)=sqrt((M(1)-W(n,1))^2 + (M(2)-W(n,2))^2 +(M(3)-W(n,3))^2);
end

for n=1:m
    W_ML(1,n)=sqrt((ML(1)-W(n,1))^2 + (ML(2)-W(n,2))^2 +(ML(3)-W(n,3))^2);
end

for n=1:m
    W_LF(1,n)=sqrt((LF(1)-W(n,1))^2 + (LF(2)-W(n,2))^2 +(LF(3)-W(n,3))^2);
end

for n=1:m
    W_LB(1,n)=sqrt((LB(1)-W(n,1))^2 + (LB(2)-W(n,2))^2 +(LB(3)-W(n,3))^2);
end

figure()
subplot(2,1,1)
plot(W_RB),grid on,grid minor,title('Distance Wrist-RB'), xlabel('frame'), ylabel('Distance [mm]')

subplot(2,1,2)
plot(W_RF),grid on,grid minor,title('Distance Wrist-RF'), xlabel('frame'), ylabel('Distance [mm]')

figure()
subplot(3,1,1)
plot(W_MR),grid on,grid minor,title('Distance Wrist-MR'), xlabel('frame'), ylabel('Distance [mm]')

subplot(3,1,2)
plot(W_M),grid on,grid minor,title('Distance Wrist-M'), xlabel('frame'), ylabel('Distance [mm]')

subplot(3,1,3)
plot(W_ML),grid on,grid minor,title('Distance Wrist-ML'), xlabel('frame'), ylabel('Distance [mm]')

figure()
subplot(2,1,1)
plot(W_LF),grid on,grid minor,title('Distance Wrist-LF'), xlabel('frame'), ylabel('Distance [mm]')

subplot(2,1,2)
plot(W_LB),grid on,grid minor,title('Distance Wrist-LB'), xlabel('frame'), ylabel('Distance [mm]')

%% Thumb
m = length(T(:,1));

T_RB = zeros(1,1);
T_LB = zeros(1,1);
T_M  = zeros(1,1);
T_MR = zeros(1,1);
T_ML = zeros(1,1);
T_RF = zeros(1,1);
T_LF = zeros(1,1);

for n=1:m
    T_RB(1,n)=sqrt((RB(1)-T(n,1))^2 + (RB(2)-T(n,2))^2 +(RB(3)-T(n,3))^2);
end

for n=1:m
    T_RF(1,n)=sqrt((RF(1)-T(n,1))^2 + (RF(2)-T(n,2))^2 +(RF(3)-T(n,3))^2);
end

for n=1:m
    T_MR(1,n)=sqrt((MR(1)-T(n,1))^2 + (MR(2)-T(n,2))^2 +(MR(3)-T(n,3))^2);
end

for n=1:m
    T_M(1,n)=sqrt((M(1)-T(n,1))^2 + (M(2)-T(n,2))^2 +(M(3)-T(n,3))^2);
end

for n=1:m
    T_ML(1,n)=sqrt((ML(1)-T(n,1))^2 + (ML(2)-T(n,2))^2 +(ML(3)-T(n,3))^2);
end

for n=1:m
    T_LF(1,n)=sqrt((LF(1)-T(n,1))^2 + (LF(2)-T(n,2))^2 +(LF(3)-T(n,3))^2);
end

for n=1:m
    T_LB(1,n)=sqrt((LB(1)-T(n,1))^2 + (LB(2)-T(n,2))^2 +(LB(3)-T(n,3))^2);
end

figure()
subplot(2,1,1)
plot(T_RB),grid on,grid minor,title('Distance Thumb-RB'), xlabel('frame'), ylabel('Distance [mm]')

subplot(2,1,2)
plot(T_RF),grid on,grid minor,title('Distance Thumb-RF'), xlabel('frame'), ylabel('Distance [mm]')

figure()
subplot(3,1,1)
plot(T_MR),grid on,grid minor,title('Distance Thumb-MR'), xlabel('frame'), ylabel('Distance [mm]')

subplot(3,1,2)
plot(T_M),grid on,grid minor,title('Distance Thumb-M'), xlabel('frame'), ylabel('Distance [mm]')

subplot(3,1,3)
plot(T_ML),grid on,grid minor,title('Distance Thumb-ML'), xlabel('frame'), ylabel('Distance [mm]')

figure()
subplot(2,1,1)
plot(T_LF),grid on,grid minor,title('Distance Thumb-LF'), xlabel('frame'), ylabel('Distance [mm]')

subplot(2,1,2)
plot(T_LB),grid on,grid minor,title('Distance Thumb-LB'), xlabel('frame'), ylabel('Distance [mm]')
%% Pinkie

m = length(Pk(:,1));

Pk_RB = zeros(1,1);
Pk_LB = zeros(1,1);
Pk_M = zeros(1,1);
Pk_MR = zeros(1,1);
Pk_ML = zeros(1,1);
Pk_RF = zeros(1,1);
Pk_LF = zeros(1,1);

for n=1:m
    Pk_RB(1,n)=sqrt((RB(1)-Pk(n,1))^2 + (RB(2)-Pk(n,2))^2 +(RB(3)-Pk(n,3))^2);
end

for n=1:m
    Pk_RF(1,n)=sqrt((RF(1)-Pk(n,1))^2 + (RF(2)-Pk(n,2))^2 +(RF(3)-Pk(n,3))^2);
end

for n=1:m
    Pk_MR(1,n)=sqrt((MR(1)-Pk(n,1))^2 + (MR(2)-Pk(n,2))^2 +(MR(3)-Pk(n,3))^2);
end

for n=1:m
    Pk_M(1,n)=sqrt((M(1)-Pk(n,1))^2 + (M(2)-Pk(n,2))^2 +(M(3)-Pk(n,3))^2);
end

for n=1:m
    Pk_ML(1,n)=sqrt((ML(1)-Pk(n,1))^2 + (ML(2)-Pk(n,2))^2 +(ML(3)-Pk(n,3))^2);
end

for n=1:m
    Pk_LF(1,n)=sqrt((LF(1)-Pk(n,1))^2 + (LF(2)-Pk(n,2))^2 +(LF(3)-Pk(n,3))^2);
end

for n=1:m
    Pk_LB(1,n)=sqrt((LB(1)-Pk(n,1))^2 + (LB(2)-Pk(n,2))^2 +(LB(3)-Pk(n,3))^2);
end

figure()
subplot(2,1,1)
plot(Pk_RB),grid on,grid minor,title('Distance Pinkie-RB'), xlabel('frame'), ylabel('Distance [mm]')

subplot(2,1,2)
plot(Pk_RF),grid on,grid minor,title('Distance Pinkie-RF'), xlabel('frame'), ylabel('Distance [mm]')

figure()
subplot(3,1,1)
plot(Pk_MR),grid on,grid minor,title('Distance Pinkie-MR'), xlabel('frame'), ylabel('Distance [mm]')

subplot(3,1,2)
plot(Pk_M),grid on,grid minor,title('Distance Pinkie-M'), xlabel('frame'), ylabel('Distance [mm]')

subplot(3,1,3)
plot(Pk_ML),grid on,grid minor,title('Distance Pinkie-ML'), xlabel('frame'), ylabel('Distance [mm]')

figure()
subplot(2,1,1)
plot(Pk_LF),grid on,grid minor,title('Distance Pinkie-LF'), xlabel('frame'), ylabel('Distance [mm]')

subplot(2,1,2)
plot(Pk_LB),grid on,grid minor,title('Distance Pinkie-LB'), xlabel('frame'), ylabel('Distance [mm]')





