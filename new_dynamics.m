% Took A_longitude_hi form FindF16Dynamics.m and exctated terms responsible
% for Theta, alpha, q and delta_e.
%
% Method:
B = [A_longitude_hi(2, end), A_longitude_hi(4, end), A_longitude_hi(5, end) ]'
A = [A_longitude_hi(2,2), A_longitude_hi(2,4), A_longitude_hi(2,5);
     A_longitude_hi(4,2), A_longitude_hi(4,4), A_longitude_hi(4,5); 
     A_longitude_hi(5,2), A_longitude_hi(5,4), A_longitude_hi(5,5),]

% clear

% A = [       0         0    1.0000 ;
%       -0.0000   -0.6721    0.9392 ;
%             0   -0.4775   -0.8741 ];
%             
% B = [       0   -0.0018   -0.1254 ]';

C = eye(3);

D = zeros(3,1);

Ci = [ 0 0 1 ]; % Tracking of `q cmd` value

A_aug = [ 0          Ci ;
          zeros(3,1)  A ];
      
B_aug = [ 0; B ];

Q = 10*diag([2000 0.5 0.1 100 ]);
R = 100*0.5;
K = lqr(A_aug, B_aug, Q, R);