clc;
close all;
%%
p=xlsread('Data2Trajectories2.xls',1,'BK:BS');

% figure ()
% grid on
% hold on
% plot(p(:,1)),title('RWristM X coordinate'), xlabel('frame'), ylabel('Position [mm]')
% plot(ones(3500)*LB(1),'r')
% plot(ones(3500)*RB(1),'b')
% plot(ones(3500)*LF(1),'g')
% plot(ones(3500)*RF(1),'y')
% plot(ones(3500)*M(1),'m')
% plot(ones(3500)*MR(1),'k')
% plot(ones(3500)*ML(1),'c')
% plot(ones(3500)*Cst,'m-.')

%% Calculate Velocity

f= 1:3417; % Number of frames
h=0.01; % Step of derivation

dxdf=diff([eps p(:,1)'])./diff([eps f]); % Velocity with default step of derivation h=1
dxdf2=diff([eps p(:,1)'])/h;

% figure (7)
% plot(f,dxdf),title('Velocity using h=1'), xlabel('frame'), ylabel('Velocity [mm/s]')
% grid on
% figure (8)
% plot(f,dxdf2),title('Velocity using h=0.01'), xlabel('frame'), ylabel('Velocity [mm/s]')
% grid on

%% Calculate Acceleration

% dvdf=diff([eps dxdf])./diff([eps f]);
% dvdf2=diff([eps dxdf])/h;
% 
% figure()
% plot(f,dvdf),title('Aceleration using h=1'), xlabel('frame'), ylabel('Velocity [mm/s2]')
% grid on
% figure()
% plot(f,dvdf2),title('Aceleration using h=0.01'), xlabel('frame'), ylabel('Velocity [mm/s2]')
% grid on

%% FINDING START/END OF THE REACHING MOTION
clc;

Frame1=zeros(1,1); % frames when Reach start
Frame2=zeros(1,1); % frames when Reach ends
Pos1=zeros(1,1); % Position when Reach start
Pos2=zeros(1,1); % Position when Reach ends
Data = p(:,1); % Trajec. x axis
DataInv = 1.01*max(Data) - Data;      % Adapting Data to use findpeaks command
[Minima,MinIdx] = findpeaks(DataInv);          
NewData = 1.01*max(Data) - Minima;          % Returning Data to the original position

% FIRST FILTER: Position close to chest o markers on the table.

for i = 1:length(NewData)
    if abs(NewData(i)-Cst)<=30
        Pos1(1,i)=NewData(i);
        Frame1(1,i)=MinIdx(i);
    elseif abs(NewData(i)-LB(1))<=50
        Pos2(1,i)=NewData(i);
        Frame2(1,i)=MinIdx(i);
    elseif abs(NewData(i)-LF(1))<=50
        Pos2(1,i)=NewData(i);
        Frame2(1,i)=MinIdx(i);
    elseif abs(NewData(i)-RF(1))<=50
        Pos2(1,i)=NewData(i);
        Frame2(1,i)=MinIdx(i);
    elseif abs(NewData(i)-RB(1))<=70
        Pos2(1,i)=NewData(i);
        Frame2(1,i)=MinIdx(i);
    elseif abs(NewData(i)-MR(1))<=50
        Pos2(1,i)=NewData(i);
        Frame2(1,i)=MinIdx(i);
    elseif abs(NewData(i)-M(1))<=50
        Pos2(1,i)=NewData(i);
        Frame2(1,i)=MinIdx(i);
    elseif abs(NewData(i)-ML(1))<=50
        Pos2(1,i)=NewData(i);
        Frame2(1,i)=MinIdx(i);
    end
end

% SECOND FILTER: save positions when the velocity is close to 0.

tol=0.14;
Frame3=zeros(1,1);
Pos3=zeros(1,1);
Frame4=zeros(1,1);
Pos4=zeros(1,1);

for i=1:length(Frame1)
    if Frame1(i) ~= 0
    if abs(dxdf(Frame1(i)))<=tol
        Frame3(1,i)=Frame1(i);
        Pos3(1,i)=Pos1(i);
    end
    end
end

for i=1:length(Frame2)
    if Frame2(i) ~= 0
    if abs(dxdf(Frame2(i)))<=tol
        Frame4(1,i)=Frame2(i);
        Pos4(1,i)=Pos2(i);
    end
    end
end

figure()
grid on
hold on
plot(p(:,1))
plot(MinIdx,NewData,'ob'),title('Reaching Motion Start/End'), xlabel('frame'), ylabel('Position [mm]')
plot(Frame3,Pos3,'r*')
plot(Frame4,Pos4,'m*')
legend('RWristM X','X Pos. Peaks&Trough','Reach Start','Reach Ends')
