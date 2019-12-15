%================================================
%     Matlab Script File used to linearize the 
%     non-linear F-16 model. The program will 
%     also run the linearized F-16 Simulation,
%     save the LTI state-space matrices to a file,
%     save and plot the simulation results.
%
% Author: Richard S. Russell
% 
%================================================

% clear;
clc;

global fi_flag_Simulink;
global ElevatorDis AileronDis RudderDis;

disp('This is an F-16 Simulation.');

%% Trim aircraft to desired altitude and velocity
altitude = 15000;
velocity = 500;

%% Initial guess for trim
thrust = 5000;          % thrust, lbs
elevator = -0.09;       % elevator, degrees
alpha = 8.49;              % AOA, degrees
rudder = -0.01;             % rudder angle, degrees
aileron = 0.01;            % aileron, degrees

%% Find trim for Hifi model at desired altitude and velocity
disp('Trimming High Fidelity Model.');
fi_flag_Simulink = 1;

global phi psi p q r phi_weight theta_weight psi_weight

alpha = alpha*pi/180;  %convert to radians

% Initial Guess for free parameters
UX0 = [thrust; elevator; alpha; aileron; rudder];  % free parameters: two control values & angle of attack

% Initialize some varibles
%
phi = 0; psi = 0;
p = 0; q = 0; r = 0;
phi_weight = 10; theta_weight = 10; psi_weight = 10;

% disp('At what flight condition would you like to trim the F-16?');
% disp('1.  Steady Wings-Level Flight.');
% disp('2.  Steady Turning Flight.');
% disp('3.  Steady Pull-Up Flight.');
% disp('4.  Steady Roll Flight.');
FC_flag = 1;

% Initializing optimization options and running optimization:
OPTIONS = optimset('TolFun',1e-10,'TolX',1e-10,'MaxFunEvals',5e+04,'MaxIter',1e+04);

for iter = 1:4:1
    [UX,FVAL,EXITFLAG,OUTPUT] = fminsearch('trimfun',UX0,OPTIONS);
    [cost, Xdot, xu] = trimfun(UX);
    UX0 = UX;
end

% For simulink:
trim_state_hi=xu(1:12);
trim_thrust_hi=xu(13);
trim_ele_hi=xu(14);
trim_ail_hi=xu(15);
trim_rud=xu(16);
trim_control_hi=[xu(2);xu(4);xu(5)];
dLEF = xu(17);

trim_state_lin = trim_state_hi; trim_thrust_lin = trim_thrust_hi; trim_control_lin = trim_control_hi;
xu_hi = xu;


%% Find the state space model for the hifi model at the desired alt and vel.
[A_hi,B_hi,C_hi,D_hi] = linmod('LIN_F16Block', [trim_state_lin; trim_thrust_lin; trim_control_lin(1); trim_control_lin(2); trim_control_lin(3); dLEF; -trim_state_lin(8)*180/pi], [trim_thrust_lin; trim_control_lin(1); trim_control_lin(2); trim_control_lin(3)]);


%% Save State Space and eigenvalues to file
trim_file = sprintf('StateSpace_alt%.0f_vel%.0f.txt', altitude, velocity);
fid_trim = fopen(trim_file, 'w');


%% For Hifi
%% Print A
fprintf(fid_trim,'A_hi = \n');
for i = 1:1:length(A_hi(:,1))
    for j = 1:1:length(A_hi(1,:))
        fprintf(fid_trim, '%8.5f,', A_hi(i,j));
    end
    fprintf(fid_trim, '\n');
end
fprintf(fid_trim, '\n\n');

%% Print B
fprintf(fid_trim,'B_hi = \n');
for i = 1:1:length(B_hi(:,1))
    for j = 1:1:length(B_hi(1,:))
        fprintf(fid_trim, '%8.5f,', B_hi(i,j));
    end
    fprintf(fid_trim, '\n');
end
fprintf(fid_trim, '\n\n');

%% Print C
fprintf(fid_trim,'C_hi = \n');
for i = 1:1:length(C_hi(:,1))
    for j = 1:1:length(C_hi(1,:))
        fprintf(fid_trim, '%8.5f,', C_hi(i,j));
    end
    fprintf(fid_trim, '\n');
end
fprintf(fid_trim, '\n\n');

%% Print D
fprintf(fid_trim,'D_hi = \n');
for i = 1:1:length(D_hi(:,1))
    for j = 1:1:length(D_hi(1,:))
        fprintf(fid_trim, '%8.5f,', D_hi(i,j));
    end
    fprintf(fid_trim, '\n');
end
fprintf(fid_trim, '\n\n');


%% Initialize some varibles used to create disturbances. %

DisEle_1 = 0;    DisEle_2 = 0;    DisEle_3 = 0;
DisAil_1 = 0;    DisAil_2 = 0;    DisAil_3 = 0;
DisRud_1 = 0;    DisRud_2 = 0;    DisRud_3 = 0;
ElevatorDis = 0; AileronDis = 0;  RudderDis = 0;


%% Find out which surface to creat a disturbance.

dis_flag = input('Would you like to create a disturbance on a surface (y/n):  ', 's');

if dis_flag == 'y'
    ElevatorDis = 0.2;
    DisEle_1 = ElevatorDis;    DisEle_2 = -2*ElevatorDis;    DisEle_3 = ElevatorDis;
    
    AileronDis = 0.01;
    DisAil_1 = AileronDis;    DisAil_2 = -2*AileronDis;    DisAil_3 = AileronDis;
    
    RudderDis = 0.01;
    DisRud_1 = RudderDis;    DisRud_2 = -2*RudderDis;    DisRud_3 = RudderDis;
elseif dis_flag == 'n'
    %do nothing
else
    error('Invalid Selection');
end


%% Create a pitch rate controller
A_pr = [       0         0    1.0000 ;
         -0.0000   -0.6721    0.9392 ;
               0   -0.4775   -0.8741 ];
B_pr = [       0   -0.0018   -0.1254 ]';
% A_pr = [ A_hi(5,5),  A_hi(5,8),  A_hi(5,11)   ;
%          A_hi(8,5),  A_hi(8,8),  A_hi(8,11)   ;
%          A_hi(11,5), A_hi(11,8), A_hi(11,11) ];
% B_pr = [ A_hi(5,14), A_hi(8,14), A_hi(11,14)]';
C_pr = eye(3);
D_pr = zeros(3,1);

Ci_pr = [ 0 0 1 ]; % Tracking of `q cmd` value
A_aug_pr = [          0  Ci_pr ;
             zeros(3,1)  A_pr ];
B_aug_pr = [          0; B_pr ];

Q_pr = 10*diag([ 2000 0.5 0.2 200 ]);
R_pr = 100;
K_pr = lqr(A_aug_pr, B_aug_pr, Q_pr, R_pr);

%% Create a longitude controller
Ci_long = [ 1 0 0 ]; % Tracking of `q cmd` value
A_aug_long = [          0  Ci_pr ;
               zeros(3,1)  A_pr ];
B_aug_long = [          0; B_pr ];

Q_long = 10*diag([ 2000 0.5 0.2 200 ]);
R_long = 100;
K_long = lqr(A_aug_long, B_aug_long, Q_long, R_long);

%% Create a mach controller
% A_mach = [      0    0.0000
%            0.0001   -0.0129]
% A_mach = [A_hi(3,3) A_hi(3,7) A_hi(3,9) A_hi(3,10) A_hi(3,12);
%           A_hi(7,3) A_hi(7,7) A_hi(7,9) A_hi(7,10) A_hi(7,12);
%           A_hi(9,3) A_hi(9,7) A_hi(9,9) A_hi(9,10) A_hi(9,12);
%           A_hi(10,3) A_hi(10,7) A_hi(10,9) A_hi(10,10) A_hi(10,12);
%           A_hi(12,3) A_hi(12,7) A_hi(12,9) A_hi(12,10) A_hi(12,12)];
% B_mach = [A_hi(3,16) A_hi(7,16) A_hi(96) A_hi(10,16) A_hi(12,16)]';

A_mach = [A_hi(3,3) A_hi(3,7) A_hi(3,8) ;
          A_hi(7,3) A_hi(7,7) A_hi(7,8) ;
          A_hi(8,3) A_hi(8,7) A_hi(8,8) ];
B_mach = [A_hi(3,13) A_hi(7,13) A_hi(8,13)]';

Ci_mach = [ 1 0 0 ]; % Tracking of `alt cmd` value
A_aug_mach = [          0  Ci_pr ;
               zeros(3,1)  A_pr ];
B_aug_mach = [          0; B_pr ];

Q_mach = 10*diag([ 2000 0.5 0.2 200 ]);
R_mach = 100;
K_mach = lqr(A_aug_mach, B_aug_mach, Q_mach, R_mach);

% %% Create a control matrix K
% size_A = size(A_hi);
% size_B = size(B_hi);
% Q = eye(size_A(2));
% R = eye(size_B(2));
% K = lqr(A_hi, B_hi, Q, R);


% %% Create a control matrix K from augumnented matrixes
% Ci = [zeros(1,4) 1 zeros(1,13)];
% A_aug = [ 0 Ci ; zeros(18,1) A_hi ];
% B_aug = [ zeros(1,4) ; B_hi ];
% size_A = size(A_aug);
% size_B = size(B_aug);
% Q = eye(size_A(2));
% R = eye(size_B(2));
% K_aug = lqr(A_aug, B_aug, Q, R);


%% Conditions for model
thrust = 0;  % Since this a linear model
deltaT = 0.001;
TStart = 0;
TFinal = 20;


%% Run and save hifi then lofi linearized simulation
fi_model = 'hifi';
A = A_hi; B = B_hi; C = C_hi; D = D_hi;
C = eye(18);
trim_state = xu_hi;
trim_thrust = trim_thrust_hi;
trim_control = trim_control_hi;

disp('Simulation in progress.');
sim( 'augumented_SS_F16_Block' ,[TStart TFinal]);
% sim( 'SS_F16_Block' ,[TStart TFinal]);

trim_file = sprintf('%s%.3f%s%.3f%s%.3f_%smodel_alt%0.f_vel%.0f_LTI.txt', 'ele_', ElevatorDis, 'ail_', AileronDis, 'rud_', RudderDis, fi_model, altitude, velocity);
fid_trim = fopen(trim_file, 'w');

% 1 time,             
% 3 npos,epos,alt,     \
% 3 phi,theta,psi,     |
% 3 vel,alpha,beta,    \_ A
% 3 p,q,r,             /
% 3 nx,ny,nz,          |
% 3 mach,qbar,ps,      /
% 4 thrust,ele,ail,rud }- B
% 23 SUM
heading = sprintf('\ntime,npos,epos,alt,phi,theta,psi,vel,alpha,beta,p,q,r,nx,ny,nz,mach,qbar,ps,thrust,ele,ail,rud\n\n');

fprintf(fid_trim,heading);

fid_trim = fopen(trim_file, 'a');

for row = 1:1:length(simout(:,1))
    fprintf(fid_trim,'%8.5f,',T(row,:));
    for column = 1:1:length(simout(1,:))
        fprintf(fid_trim,'%8.5f,',simout(row,column));
    end
    for column = 1:1:length(controls(1,:))
%             fprintf(fid_trim,'%8.5f,',controls(row,column));
        fprintf(fid_trim, '0,');
    end
    fprintf(fid_trim,'\n');
end

fclose(fid_trim);


%% Plotting
plot_flag = input('Plot results (y/n):  ', 's');

if plot_flag == 'y'
    graphF16_all;
end
