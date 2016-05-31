MapF = csvread('mapF.csv');
MapF = MapF(:, 2:end);
%MapK = csvread('mapkM.csv');
[K, M]=meshgrid(100:10:500,0.4:0.01:0.59);
figure
surf(K, M, MapF())
figure
contourf(K, M, MapF, 30)
colorbar;
title('');
xlabel('');
ylabel('');