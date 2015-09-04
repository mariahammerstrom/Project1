% Plot data from C++

filename = 'Project1_analytic_solution.txt';

% Get N value by reading first line only:
[~,~,N] = textread(filename,'%f %f %f',1);

% Get all values:
[x,y,N] = textread(filename,'%f %f %f',N);





filename = 'Project1_simple_algorithm.txt';

% Get N value by reading first line only:
[~,~,N] = textread(filename,'%f %f %f',1);

% Get all values:
[x2,y2,N] = textread(filename,'%f %f %f',N);

% Regular plot:
figure
plot(x,y,fliplr(x2),fliplr(y2))
xlabel('x')
ylabel('u(x)')
title('Solution to 1D Poisson equation')
legend('Analytic solution','Numerical solution')



% Log-log plot:
%figure
%loglog(x,y)
%xlabel('log(x)')
%ylabel('log(y)')