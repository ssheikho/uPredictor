clc;
close all;

% clear all;
%%
a = 9;
b = 5;
x_c = 5;
y_c =4;
T = 2;

A = a^2*(sin(T))^2 + b^2*(cos(T))^2;
B = 2*(b^2 - a^2)*sin(T)*cos(T);
C = a^2*(cos(T))^2 + b^2*(sin(T))^2;
D = -2*A*x_c - B*y_c;
E = -B*x_c - 2*y_c;
F = A*x_c^2 + B*x_c*y_c + C*y_c^2 - a^2*b^2;

syms x y
imp_ellip = A*x^2 + B*x*y + C*y^2 + D*x + E*y + F == 0;

fimplicit(imp_ellip, [-10 15 -10 10]);

%%
t = linspace(0, 2*pi, 100);
X = x_c + a*cos(t)*cos(T) - b*sin(t)*sin(T);
Y = y_c + a*cos(t)*sin(T) + b*sin(t)*cos(T);

plot(X,Y);