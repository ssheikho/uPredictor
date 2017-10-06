clc;
close all;

% clear all;
%%
a = 9;
b = 5;
x_c = 10;
y_c =2;
T = 0;

A = a^2*(sin(T))^2 + b^2*(cos(T))^2;
B = 2*(b^2 - a^2)*sin(T)*cos(T);
C = a^2*(cos(T))^2 + b^2*(sin(T))^2;
D = -2*A*x_c - B*y_c;
E = -B*x_c - 2*C*y_c;
F = A*x_c^2 + B*x_c*y_c + C*y_c^2 - a^2*b^2;

syms x y
imp_ellip = A*x^2 + B*x*y + C*y^2 + D*x + E*y + F == 0;

fp = fimplicit(imp_ellip, [x_c-a x_c+a y_c-b y_c+b]);
X = fp.XData;
Y = fp.YData;

%%
%t = linspace(0, 2*pi, 100);
%X = x_c + a*cos(t)*cos(T) - b*sin(t)*sin(T);
%Y = y_c + a*cos(t)*sin(T) + b*sin(t)*cos(T);


% plot(X,Y);



%% Rotation

l = length(X);

z = 0*ones(1,l);
figure()
hold on
grid on
plot3(X,Y,z,'b')

thetaZ = pi/4;
thetaX = pi/2;
% thetaY = 

to_origin = [1 0 0 -x_c;0 1 0 -y_c; 0 0 1 0; 0 0 0 1];
from_origin = [1 0 0 x_c;0 1 0 y_c; 0 0 1 0; 0 0 0 1];


RotZ = [cos(thetaZ) -sin(thetaZ) 0 0;sin(thetaZ) cos(thetaZ) 0 0; 0 0 1 0; 0 0 0 1];

RotX = [1 0 0 0; 0 cos(thetaX) -sin(thetaX) 0 ;0 sin(thetaX) cos(thetaX) 0 ; 0 0 0 1];

RotY = [ cos(thetaZ) 0 sin(thetaZ) 0 ;0 1 0 0;-sin(thetaZ) 0 cos(thetaZ) 0 ; 0 0 0 1];

p = [X; Y; z; ones(1,l)];

p_primeX = RotX*to_origin*p;
p_prime = from_origin*RotZ*RotX*to_origin*p;


plot3(p_prime(1,:),p_prime(2,:),p_prime(3,:),'r')
plot3(p_primeX(1,:),p_primeX(2,:),p_primeX(3,:),'m')

%% Translation

trans = [1 0 0 4;0 1 0 4; 0 0 1 4; 0 0 0 1];

p = trans*p_prime;

figure()
plot3(p_prime(1,:),p_prime(2,:),p_prime(3,:),'r')
hold on
grid on
plot3(p(1,:),p(2,:),p(3,:))

