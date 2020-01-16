disp('%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%')
disp('%                      Feedback Example                          %')
disp('%               F-16 PAH Control System Design                   %')
disp('%                    Author: Daniel Wagner                       %')
disp('%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%')

%% options
clear all; close all; clc;
tf = 10; % final time


disp('%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%')
disp('%                       Frequency Method                         %')
disp('%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%')


%% open-loop dynamics
Ap = [0       0        1; 
      0 -1.0189,  0.9051; 
      0  0.8223, -1.0774];

Bp = [      0;
      -0.0022; 
      -0.1756];
  
Cp = eye(3);

Dp = 0;

%% state-space representation
xpdot = ss(Ap,Bp,Cp,Dp);

% labels for system
xpdot.StateName  = {'\theta', '\alpha', 'q'};
xpdot.InputName  = '\delta_e';
xpdot.OutputName = {'\theta', '\alpha', 'q'};

% open-loop responses
figure(1); step(xpdot,tf); 
figure(2); impulse(xpdot,tf);

%% build pitch damper using feedback command
help feedback; kq = 1; xcl = feedback(xpdot,-kq,1,3);

%% build PAH using feedback command
kp = 10; ki = 0.1; C = pid(kp,ki); xcl = feedback(-C*xcl,1,1,1);

%% closed-loop responses
figure(3); step(xcl,tf); 
figure(4); impulse(xcl,tf);

%% use sisotool 
clear xcl % reset variables

% pitch damper
sisotool(xpdot(3,:)); 
kq = 1; xcl = feedback(xpdot,-kq,1,3); 

% pitch attitude hold
sisotool(xcl(1,:)); 
C = pid(34.7,6.03); xcl = feedback(-C*xcl,1,1,1); % PAH

%% closed-loop responses
figure(5); step(xcl,tf); 
figure(6); impulse(xcl,tf);


disp('%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%')
disp('%                     State-Space Method                         %')
disp('%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%')

%% integrated open-loop dynamics
A = [0 0       0        1; 
     1 0       0        0;
     0 0 -1.0189,  0.9051; 
     0 0  0.8223, -1.0774];

B = [       0;
            0;
      -0.0022; 
      -0.1756];
  
G = [  0; 
      -1;
       0;
       0];
   
C = eye(4);

D = 0;

%% eigenvalues of integrated open-loop 
eig(A)

%% integrated state-space representation
xdot = ss(A,B,C,D);

% labels for system
xdot.StateName  = {'\omgeta','\theta', '\alpha', 'q'};
xdot.InputName  = '\delta_e';
xdot.OutputName = {'\omgeta','\theta', '\alpha', 'q'};

%% desired-closed loop
p1 = -4+1i;
p2 = -16;
p3 = -8;
p4 = -4-1i;

K  = place(A,B,[p1,p2,p3,p4]);

%% eigenvalues of closed-loop 
eig(A-B*K)

%% integrated closed-loop representation
xcldot = ss(A-B*K, G, C, D);

%% closed-loop responses
figure(7); step(xcldot,tf); 
figure(8); impulse(xcldot,tf);


