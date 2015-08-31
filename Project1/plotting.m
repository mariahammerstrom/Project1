% Plot data from C++

filename = 'Ex2_2_data_Sup.txt';

% Get N value by reading first line only:
[~,~,N] = textread(filename,'%f %f %f',1);

% Get all values:
[x,y,N] = textread(filename,'%f %f %f',N);

% Log-log plot:
figure
loglog(x,y)
xlabel('log(x)')
ylabel('log(y)')

% Regular plot:
figure
plot(x,y)
xlabel('x')
ylabel('y')