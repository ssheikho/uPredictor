clc;
% close all;
% clear all;
%% Script to get the position of the markers on the Chest

c=xlsread('Data2Trajectories2.xls',1,'AY:BG');

MChest= [mean(c(:,1),'omitnan') mean(c(:,2),'omitnan') mean(c(:,3),'omitnan')]; % [X Y Z] mm
LChest=[mean(c(:,4),'omitnan') mean(c(:,5),'omitnan') mean(c(:,6),'omitnan')];
RChest =[mean(c(:,7),'omitnan') mean(c(:,8),'omitnan') mean(c(:,9),'omitnan')];

Cst=mean([MChest(1) LChest(1) RChest(1)]); % Averange between markers.