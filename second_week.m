clear; close all; clc;

%% open loop dynamics fro "short-period" approximation of F-16
Ap = [ 0       0       1  ;
       0  -1.019  0.9051  ;
       0  0.8223  -1.077 ];
   
Bp = [       0  ;
       -0.0022  ;
       -0.1756 ];
   
Cp = eye(3);

Dp = 0;

%% we want the state-space representation of the open-loop dynamics
xpdot = ss(Ap, Bp, Cp, Dp);
xpdot.StateName  = {'\theta','\alpha','q'};
xpdot.InputName  = '\delta_e';
xpdot.OutputName = {'\theta','\alpha','q'};

%% plot open-loop responses
figure(1); step(xpdot);
figure(2); impulse(xpdot);

%%  find eigenvalues of "relaxed stability" system
eigenvalues = eig(Ap);

%% how do we build a feedback loop to "stabilize" the system
kq = 100; xcldot = feedback(xpdot,-kq,1,3);                          % pitch damper
kp = 10; ki = 1; C = pid(kp,ki); xcldot = feedback(-C*xcldot,1,1,1); % pitch attitude hold

%% what do the step and impulse responses of the "new" closed-loop system look like
figure(3); step(xcldot);
figure(4); impulse(xcldot);

%% we know what the controller is and how to build it, but how do we "tune" it?
clear xcldot; xcldot = feedback(xpdot,-5.2,1,3);
% sisotool(xpdot(1,:)); 
C = pid(-2.29,-1.15);
xcldot = feedback(C*xcldot,1,1,1);

%% what does the final response of the system looks like
figure(5); step(xcldot)
figure(6); impulse(xcldot)