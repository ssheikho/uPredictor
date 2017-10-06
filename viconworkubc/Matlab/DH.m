clc;
close all;
clear all;
%% WAM parameters
a = [0 0 0.045 -0.045 0 0 0];

alpha = [-pi/2 pi/2 -pi/2 pi/2 -pi/2 pi/2 0];

d = [0 0 0.55 0 0.3 0 0.060];

O = sym('O',[1 7]);
%% Create DH matrix

% A = [cos(O(1)) sin(O(1))*cos(alpha(1)) a(1)*cos(O(1)); sin(O(1)) cos(O(1))*cos(alpha(1)) -cos(O(1))*sin(alpha(1)) a(1)*sin(O(1)); 0 sin(alpha(1)) cos(alpha(1)) d(1); 0 0 0 1];

% Cell-array
for i=1:7
    A{i} = [cos(O(i)) sin(O(i))*cos(alpha(i)) sin(O(i))*sin(alpha(i)) a(i)*cos(O(i)); sin(O(i)) cos(O(i))*cos(alpha(i)) -cos(O(i))*sin(alpha(i)) a(i)*sin(O(i)); 0 sin(alpha(i)) cos(alpha(i)) d(i); 0 0 0 1];
end


dh = struct('DH',A); %struct with the all values in one field
