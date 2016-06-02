MapF = csvread('mapF.csv');
MapF = MapF(:, 2:end);
%MapK = csvread('mapkM.csv');
min(min(MapF))
[K, M]=meshgrid(200:1:500,0.2:0.001:0.499);
figure
surf(K, M, MapF())
figure
contourf(K, M, MapF, 200)
colorbar;
title('');
xlabel('');
ylabel('');