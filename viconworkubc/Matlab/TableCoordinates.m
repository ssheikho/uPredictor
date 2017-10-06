clc;
% close all;
% clear all;
%% Script to get the position of the markers

v=xlsread('Data2Trajectories2.xls',1,'C:W');

RB= [mean(v(:,1),'omitnan') mean(v(:,2),'omitnan') mean(v(:,3),'omitnan')]; % [X Y Z] mm
LB=[mean(v(:,4),'omitnan') mean(v(:,5),'omitnan') mean(v(:,6),'omitnan')];
M =[mean(v(:,7),'omitnan') mean(v(:,8),'omitnan') mean(v(:,9),'omitnan')];
RF=[mean(v(:,10),'omitnan') mean(v(:,11),'omitnan') mean(v(:,12),'omitnan')];
MR=[mean(v(:,13),'omitnan') mean(v(:,14),'omitnan') mean(v(:,15),'omitnan')];
ML =[mean(v(:,16),'omitnan') mean(v(:,17),'omitnan') mean(v(:,18),'omitnan')];
LF =[mean(v(:,19),'omitnan') mean(v(:,20),'omitnan') mean(v(:,21),'omitnan')]; 