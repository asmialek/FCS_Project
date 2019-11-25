r2d = 180/pi;
d2r = pi/180;

A = [  -0.1645   0.0603 -0.9982 0.0442;
      -16.5500  -2.5900  0.9970 0     ;
        6.7790  -0.1023 -0.0673 0     ;
        0        1       0.0604 0     ];
   
B = [-0.0006  0.0007;
      1.3470  0.2365;
      0.0919 -0.0706;
      0       0    ];
  
C = eye(4);

%% state-space representation
xpdot = ss(A,B,C,[]);

% labels for system
xpdot.StateName  = {'p', 'r', '\beta', '\phi'};
xpdot.InputName  = {'\delta_a', '\delta_r'};
xpdot.StateName  = {'p', 'r', '\beta', '\phi'};

Ci = [zeros(2,2) eye(2)]; % tracking (integration) matrix

D = zeros(4,2);

A_aug = [zeros(2,2), Ci  ;
         zeros(4,2),  A ];

B_aug = [zeros(2,2);  B ];

Br     = [-eye(2); zeros(4,2)];

% Q = 10*diag([2000 2000 2000 4000 0.5 0.1]);
% R = 5*diag([0.01 0.5]);

% K = lqr(A_aug, B_aug, Q, R,[]);

Q = 10*diag([2000 2000 2000 4000 0.5 0.1]);
R = 100*diag([0.5 0.5]);
K = lqr(A_aug, B_aug, Q, R,[]);