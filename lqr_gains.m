%% Create a pitch rate controller
A_pr = [       0         0    1.0000 ;
         -0.0000   -0.6721    0.9392 ;
               0   -0.4775   -0.8741 ];
B_pr = [       0   -0.0018   -0.1254 ]';

C_pr = eye(3);
D_pr = zeros(3,1);

Ci_pr = [ 0 0 1 ]; % Tracking of `q cmd` value
A_aug_pr = [          0  Ci_pr ;
             zeros(3,1)  A_pr ];
B_aug_pr = [          0; B_pr ];

Q_pr = 1*diag([ 1 0.1 1 0.1 ]);
R_pr = 1;
K_pr = lqr(A_aug_pr, B_aug_pr, Q_pr, R_pr);

%% Create a longitude controller
Ci_long = [ 1 0 0 ]; % Tracking of `q cmd` value
A_aug_long = [          0  Ci_pr ;
               zeros(3,1)  A_pr ];
B_aug_long = [          0; B_pr ];

Q_long = 10*diag([ 2000 0.5 0.2 200 ]);
R_long = 100;
K_long = lqr(A_aug_long, B_aug_long, Q_long, R_long);
