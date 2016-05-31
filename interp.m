clear all;
prop = csvread('prop.csv');
p = prop(1, 1);
k = 2;
j = 1;
for i = 1:size(prop, 1)
    
    if p(k-1) ~= prop(i, 1)
        p(k) = prop(i, 1);
        k = k + 1;
        j = 1;
    end
    h(k-1, j) = prop(i, 3);

    t(k-1, j) = prop(i, 2);
    j = j + 1;
end

% h1 = [24.15, 30.65, 38.6, 45.3];
% t1 = [90, 180, 270, 305];
% p1 = 6;
% h2 = [26, 35.4, 40.5, 47.7];
% t2 = [500, 1000, 1250, 1534];
% p2 = 4;
% for i = 1:size(h, 2)
%     for j = 1:size(h, 1)
%         if h(j, i) < 0
%             h(j, i) = 0;
%         end
%     end
% end
k = 1;
mf = [];
R0 = 50;
s0 = 0.93;
Kf = [];
for i = 1:numel(p)
    for j = i+1:numel(p)
        [m, hf] = StrainRateSens1(p(i), t(i, :), h(i, :), p(j), t(j, :), h(j, :));
        %mf = [mf; m]
        %figure
        %plot(hf, m)
        %filename = sprintf('%d_%d', p(i)*10, p(j)*10);
        %print(filename, '-djpeg')
        %plot(hf, mean(m), '.')
        p(i)
        p(j)
        mean(m)
        mf = [mf; mean(m), p(i), p(j)];
        I = IntegralSIMPS(0, pi/2, mean(m));
        pf = min(p(i), p(j))*0.101325;
        ind = 1;
        for l = 1:numel(p)
            if pf == p(l)
                ind = l;
            end
        end
        tf = t(ind, :);
        tf = tf(tf ~=0);
        tf = max(tf);
        K = (pf*R0/(2*s0))*(tf/(2*I))^mean(m);
        Kf = [Kf; K];
        %hold on
        %axis([40 50 0 0.5])
        k = k + 1;
    end
end

% plot(h, m)