clear

curr_path = cd;
curr_folder = split(curr_path, '/');
if ~strcmp(curr_folder{end}, 'F16Sim')
    addpath('.');
    cd F16Sim;
    mex nlplant.c
end

disp(' ')
disp(' ')
disp(' ')
disp(' ')
disp(' ')
disp(' ')
disp(' ')
disp(' ')
disp('At what flight condition would you like to trim the F-16?');
disp('1.  Steady Wings-Level Flight.');
disp('2.  Steady Turning Flight.');
disp('3.  Steady Pull-Up Flight.');
disp('4.  Steady Roll Flight.');
global FC_flag
FC_flag = input('Your Selection:  ');

my_FindF16Dynamics
lqr_gains

my_runLINF16sim

A = A_hi;
B = B_hi;
C = eye(18);
D = zeros(18,4);

my_runF16Sim

%% Step input variables
% "_time" variables are in seconds
% "_value" are in mph and degrees
% These are example values and need to be explored
% to find what brakes the simulation
velocity_time  = 0;
velocity_value = 500;
theta_time     = 5;
theta_value    = 5;
phi_time       = 20;
phi_value      = 10;
psi_time       = 50;
psi_value      = 2;