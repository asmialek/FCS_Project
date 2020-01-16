% FLYmodel.m 
% Initialization script 
% Pavel Hospodar, CVUT, FEL 2010

clc
close all
% clear

% inputs parameters
plane = input_param;    

% Aerodynamic and mass model initialization 
% Aircraft triming 
x_trim = trimConfig(plane);

% initial states 
H_init = plane.h;
v0 = plane.v0;
V_init = [plane.v0*cos(x_trim(1)) 0 plane.v0*sin(x_trim(1))]';
alpha_init  = 1*x_trim(1);
el_init     = x_trim(2);
pitch_init  = 1*x_trim(3);
eng_init    = x_trim(4);
Ts = 1/50;
Tsim = plane.Tsim;

% longitudinal state-space model
[Ap,Bp,Cp,Dp] = longMotion(plane.v0,plane.h,plane.m,...
    plane.Jzz,plane.x_T,alpha_init,pitch_init);
sysLong = ss(Ap,Bp,Cp,Dp);

% lateral state-space model
[As,Bs,Cs,Ds] = latMotion(plane.v0,plane.h,plane.m,plane.Jxx,...
    plane.Jyy,plane.Jxy,alpha_init,pitch_init);
% sysLat = ss(As, Bs, Cs, Ds);

% sysLongSP = ss(Ap(2:3,2:3), Bp(2:3), eye(2), []);
% impulse(sysLong(2), sysLongSP(1), 100);
% figure
% bodemag(sysLong(3), sysLongSP(2));

% y = [v, \alpha, q, ...]
% rltool(sysLong(2))

% For sensivity analysis
% change the parameter
% sysLong = ss(Ap,...)
% bodemag(sysLong)
