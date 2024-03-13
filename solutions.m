%num 1
syms x y
y = sin(x) * cos(x)^2

diff(y,x)
int(y,x)

%%
clc,clear
%% num 2
syms x;
f = sin(x) * cos(x)^2;

x_values = -5:0.1:5;

y_values_derivative = double(subs(diff(f, x), x, x_values));

disp('x values:');
disp(x_values);

disp('Derivative (f''(x)) values:');
disp(y_values_derivative);

%% num 2.2
x = [1, 2, 3, 4, 5];
y = [2, 4, 5, 4, 5];

% Fit a polynomial of degree 8
coef = polyfit(x, y, 8);

% Convert coefficients to a string
coefString = sprintf('%.6f ', coef);

% Display the coefficients
disp(coefString);



%% num 3 
% 1 f(0)'
syms x 
f = sin(x) * cos(x)^2

res = diff(f,x)

subs(res, x, 0)

%% num 3.2

syms x

f = sin(x) * cos(x)^2;

T = taylor(f, x, 'Order', 5);

disp('Fifth order Taylor series expansion at x = 0:');
disp(T);

%% 3.3
syms x
f = sin(x) * cos(x)^2;
T = taylor(f, x, 'Order', 5);

f_prime = diff(T, x);

x_sample = linspace(-0.5, 0.5, 100);  % Choose a range of x values
y_prime_sample = double(subs(f_prime, x, x_sample));  % Evaluate the derivative at sample points

x_value = 0;
y_prime_interp = interp1(x_sample, y_prime_sample, x_value, 'linear');

disp(['Interpolated value of f''(0): ', num2str(y_prime_interp)]);
%% num 4
%(1)
f = [10 15];
A = [5 2;2 3;1 5];
b = [200;100;150];
Lbnd = [0;0];

[x,fval] = linprog(-f,A,b,[],[],Lbnd);

x
fval

%% num 4.2
f = [10 15];
A = [5 2;2 3;1 5];
b = [200;100;150];
intcon = [1 2];
Aeq = [];
beq = [];
ub = [];
lb = [0 0];

[x, sol] = intlinprog(-f,intcon, A, b, Aeq, beq, lb, ub);
sol

x

%% num 5 

x = -1:0.1:1;
[x,y] = meshgrid(-1:0.1:1, -1:0.1:1);
z1 = (2-x.^2-y.^2).^(0.5);
z2 = (x.^2 + y.^2).^(0.5);
mesh(x,y,z1)
hold on
mesh (x,y,z2)
hold off



