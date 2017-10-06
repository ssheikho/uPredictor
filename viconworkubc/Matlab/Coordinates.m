%% Read the following intructions BEFORE run this script
% Step1: Check your Internet Conection, you needed to use the Nexus Matlab Interaction.
% Step2: Open Vicon Nexus Software
% Step3: Go to START menu and find "Set Matlab path". Click on it. Then Matlab is going to ask for your user and password.
% Step4: Run this script. If doesn't work close matlab and open it from Nexus. Look for the option "Launch Matlab"

%% IMPORTANT: 
% Also is possible run this script directly from Nexus, but in this case is not very useful becouse is only for import trayectories. 
% However, can be applicable for another situations.
%% This script was develop using the "Sara Cal 06"
% After establish conection use vicon.DisplayCommandList to get the entire
% command list and vicon.DisplayCommandHelp(‘COMMANDNAME’) to know how
% these commands works. 
%%
vicon = ViconNexus; % Establish conection Matlab-Nexus

Subject = vicon.GetSubjectNames; % Subject is a string with the Subject's names inside. Subject{2} is "ActuallySara"

% Import markers trayectories
% Output: X,Y,Z Coordinates and E(existence)
% [RShoM(:,1),RShoM(:,2),RShoM(:,3),RShoM(:,4)] = vicon.GetTrajectory(Subject{2},'RShoM');
% [RElbM(:,1),RElbM(:,2),RElbM(:,3),RElbM(:,4)] = vicon.GetTrajectory(Subject{2},'RElbM');
% [RUArmUM(:,1),RUArmUM(:,2),RUArmUM(:,3),RUArmUM(:,4)] = vicon.GetTrajectory(Subject{2},'RUArmUM');
% [RWristM(:,1),RWristM(:,2),RWristM(:,3),RWristM(:,4)] = vicon.GetTrajectory(Subject{2},'RWristM');
% [RLArmUM(:,1),RLArmUM(:,2),RLArmUM(:,3),RLArmUM(:,4)] = vicon.GetTrajectory(Subject{2},'RLArmUM');
% [RLArmLM(:,1),RLArmLM(:,2),RLArmLM(:,3),RLArmLM(:,4)] = vicon.GetTrajectory(Subject{2},'RLArmLM');
% [RThumbM(:,1),RThumbM(:,2),RThumbM(:,3),RThumbM(:,4)] = vicon.GetTrajectory(Subject{2},'RThumbM');
% [RPinkieM(:,1),RPinkieM(:,2),RPinkieM(:,3),RPinkieM(:,4)] = vicon.GetTrajectory(Subject{2},'RPinkieM');

% To get the names of the markers use vicon.GetMarkerNames('SubjectName')


