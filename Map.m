MapF = csvread('mapF.csv');
MapF = MapF(:, 2:end);
%MapK = csvread('mapkM.csv');
min(min(MapF))
[K, M]=meshgrid(100:10:1000,0.1:0.01:0.89);
figure
surf(K, M, MapF())
figure
contourf(K, M, MapF, 30)
colorbar;
title('');
xlabel('');
ylabel('');