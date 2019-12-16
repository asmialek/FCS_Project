%% Create a longitude controller

A_long = A_longitude_hi([2,4,5],[2,4,5]);
B_long = A_longitude_hi([2,4,5],7);
Ci_long = [ 1 0 0 ]; % Tracking of `q cmd` value
A_aug_long = [          0  Ci_long ;
               zeros(3,1)  A_long ];
B_aug_long = [          0; B_long ];

%%%%%%%%%%%%%%%%%%%
%%% TUNE THIS v %%%
%%%%%%%%%%%%%%%%%%%
% Q_long = 10*diag([ 2000 0.5 0.2 200 ]);
% R_long = 100;
Q_long = diag(4);
R_long = 1;
%%%%%%%%%%%%%%%%%%%%

K_long = lqr(A_aug_long, B_aug_long, Q_long, R_long);


% Create a lateral controller 2 outputs

A_lat = A_lateral_hi([1,2,4,5,6],[1,2,4,5,6]);
B_lat = A_lateral_hi([1,2,4,5,6],[8,9]);

Ci_lat = [ 1 0 0 0 0  ;
           0 1 0 0 0 ]; % Tracking of `q cmd` value
       
A_aug_lat = [  zeros(2,2)  Ci_lat ;
               zeros(5,2)  A_lat ];
B_aug_lat = [         0 0; 0 0; B_lat ];

%%%%%%%%%%%%%%%%%%%
%%% TUNE THIS v %%%
%%%%%%%%%%%%%%%%%%%
Q_lat = 10*diag([ 20000 20000 200 200 0.1 0.1 0.1 ]);
R_lat = 100*diag(2);
% Q_lat = diag(7);
% R_lat = diag(2);
%%%%%%%%%%%%%%%%%%%%

K_lat = lqr(A_aug_lat, B_aug_lat, Q_lat, R_lat);
