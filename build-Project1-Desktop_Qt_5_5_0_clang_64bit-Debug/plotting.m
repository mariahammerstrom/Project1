% Plot data from C++

n = 10;

% ANALYTIC SOLUTION
filename = sprintf('Project1_analytic_solution_n%d.txt',n);
[x,y] = textread(filename,'%f %f',n);


% SIMPLE ALGORITHM
filename = sprintf('Project1_simple_algorithm_n%d.txt',n);
[x2,y2] = textread(filename,'%f %f',n);


% LU DECOMPOSITION
filename = sprintf('Project1_LU_decomp_n%d.txt',n);
[x3,y3] = textread(filename,'%f %f',n);


% PLOTTING:
figure;
plot(x,y,fliplr(x2),fliplr(y2),x3,y3);
xlabel('x');
ylabel('u(x)');
title(sprintf('Solution to 1D Poisson equation, n = %d',n));
legend('Analytic solution','Numerical solution','LU decomposition');
print(sprintf('Plot_n%d',n),'-dpng');


% Log-log plot:
%figure
%loglog(x,y)
%xlabel('log(x)')
%ylabel('log(y)')