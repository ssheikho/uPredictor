clc;
close all;
%% Center of the ball

p=xlsread('Data2Trajectories2.xls',1,'BK:BS');          % Import Data of the Markers 

d = sqrt(45^2+60^2);
Tx=[RB(1) RF(1) MR(1) M(1) ML(1) LF(1) LB(1)];
Ty=[RB(2) RF(2) MR(2) M(2) ML(2) LF(2) LB(2)];
Tz=[RB(3) RF(3) MR(3) M(3) ML(3) LF(3) LB(3)];


figure()        % Ploting Markers and Trajectories
plot3(p(:,1),p(:,2),p(:,3)), xlabel('x'),ylabel('y'),zlabel('z'), grid on
hold on
plot3(Tx,Ty,Tz,'o-')

%% Define Line between RB & LB

v = [RB(1)-LB(1) RB(2)-LB(2) RB(3)-LB(3)]; 

t=0:0.1:1;
Lx = LB(1)+ t*v(1);
Ly = LB(2)+ t*v(2);
Lz = LB(3)+ t*v(3);


%% FINDING RACK COORDINATES
clc;
% Eq. of the plane

Mx = [RF(1) MR(1) M(1) ML(1) LF(1)];
My = [RF(2) MR(2) M(2) ML(2) LF(2)];
Mz = [RF(3) MR(3) M(3) ML(3) LF(3)];

syms g
Normal = v;
R = zeros(5,3);


for i=1:length(Mx)
    
C = dot([Mx(i) My(i) Mz(i)],Normal);
Y=eval(solve(v(1)*(LB(1)+ g*v(1)) + v(2)*(LB(2)+ g*v(2)) + v(3)*(LB(3)+ g*v(3)) == C, g));

R(i,1) = LB(1)+ Y*v(1);
R(i,2) = LB(2)+ Y*v(2);
R(i,3) = LB(3)+ Y*v(3);
end


%% Finding Centers

d=45;
Center=zeros(5,3);
for i=1:length(Mx)

v1 = RB-R(i,:);

v2= [Mx(i) My(i) Mz(i)]-R(i,:);

N = cross(v1,v2)/norm(cross(v1,v2));

Center(i,:) = R(i,:) + N*d;
end

figure()
plot3(Lx,Ly,Lz), xlabel('x'),ylabel('y'),zlabel('z'), grid on
hold on
plot3(Tx,Ty,Tz,'o-')
plot3(R(:,1), R(:,2), R(:,3), 'mo')
plot3(Center(:,1),Center(:,2),Center(:,3),'ko')
plot3(N(1),N(2),N(3))
% plot3(p(:,1),p(:,2),p(:,3)), xlabel('x'),ylabel('y'),zlabel('z'), grid on
% plot3(Tx,Ty,Tz,'o-')






