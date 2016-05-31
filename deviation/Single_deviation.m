% MARC OUTPUT ANALYZER AND MAP PLOTTER
clear all;
close all;
Dh=zeros(10, 9);
Ds=zeros(10, 9);
ex = csvread('Experiment.csv', 1);
% k=35;
% m=4;
% fname = sprintf('plotp3k%03dm%03d',p k, m);
for k=100:100:1000
    for m=1:9    
%         -------------------------- read input file to H, S
        fname = sprintf('0_16_aks',k, m);
        in = fopen(fname);
        formatSpec = '%f %f';

         for i=1:9 
            fgets(in);
        end
        C1 = textscan(in,formatSpec, 'Delimiter', '\n', 'CollectOutput', true);
        C1{1}(end, :) = [];
        H = abs(C1{1});
        clear C1;

        for i=1:6
            fgets(in);
        end
        C2 = textscan(in,formatSpec, 'Delimiter', '\n', 'CollectOutput', true);
        %C2{1}(end, :) = [];
        S = C2{1};
        S(:,2)=S(:,2)./S(1,2);
        clear C2;
        fclose(in);
        % -------------------------- end of read input file

%          [th, fh] = dist_p2c_v(H, ex(1:10, 2:3));%      ¿Ã„6    3    ‡ÚÏ
%          [th, fh] = dist_p2c_v(H, ex(11:14, 2:3));%     ¿Ã„6    3.5  ‡ÚÏ
%          [th, fh] = dist_p2c_v(H, ex(15:18, 2:3));%     ¿Ã„6    4    ‡ÚÏ
%          [th, fh] = dist_p2c_v(H, ex(19:22, 2:3));%     ¿Ã„6    5    ‡ÚÏ      
%          [th, fh] = dist_p2c_v(H, ex(23:26, 2:3));%     ¿Ã„6    6    ‡ÚÏ     
%          [th, fh] = dist_p2c_v(H, ex(27:36, 2:3));%     AA5083  0.29 Ãœ¿  
%          [th, fh] = dist_p2c_v(H, ex(37:44, 2:3));%     AA5083  0.56 Ãœ¿
%          [th, fh] = dist_p2c_v(H, ex(45:63, 2:3));%     AZ31    0.29 Ãœ¿
         [th, fh] = dist_p2c_v(H, ex(64:99, 2:3));%     AZ31    0.16 Ãœ¿
         
%          [ts, fs] = dist_p2c_v(S, ex(1:10, [2 5]));%    ¿Ã„6    3    ‡ÚÏ
%          [ts, fs] = dist_p2c_v(S, ex(11:14, [2 5]));%   ¿Ã„6    3.5  ‡ÚÏ
%          [ts, fs] = dist_p2c_v(S, ex(15:18, [2 5]));%   ¿Ã„6    4    ‡ÚÏ
%          [ts, fs] = dist_p2c_v(S, ex(19:22, [2 5]));%   ¿Ã„6    5    ‡ÚÏ  
%          [ts, fs] = dist_p2c_v(S, ex(23:26, [2 5]));%   ¿Ã„6    6    ‡ÚÏ 
%          [ts, fs] = dist_p2c_v(S, ex(27:36, [2 5]));%   AA5083  0.29 Ãœ¿
%          [ts, fs] = dist_p2c_v(S, ex(37:44, [2 5]));%   AA5083  0.56 Ãœ¿
%          [ts, fs] = dist_p2c_v(S, ex(45:63, [2 5]));%   AZ31    0.29 Ãœ¿
         [ts, fs] = dist_p2c_v(S, ex(64:99, [2 5]));%   AZ31    0.16 Ãœ¿
%          [ts, fs] = dist_p2c_v(S, S(109,:));



        Dh(k/100,m)= sum(fh);
        Ds(k/100,m)= sum(fs);
        Dhs=(Dh+Ds);
        fname
    end
end




%--------------- old 
% r1 = [x' interp1(H(:,1),abs(H(:,2)),x)'];
% 
% r2 = ex(ones(size(x,2),1),2:3);
% s = abs(max(r1(:,2))/max(r1(:,1)));
% 
% r31 = (r1(:,1) - r2(:,1))./ abs(ex(1, 2));
% r32 = (r1(:,2) - r2(:,2))./ abs(ex(1, 3));
% r3 = [r31 r32];
% r4 = arrayfun(@(idx) norm(r3(idx,:)), 1:size(r3,1));
% 
% % dx = gradient(r1(:,1));
% % dy = gradient(r1(:,2));
% % dxdy = [dx dy];
% % dn = 1 ./ arrayfun(@(idx) norm(dxdy(idx,:)), 1:size(dxdy,1))';
% % dxdy = dxdy .* [dn dn];
% % qn = 5000;
% % quiver(x(qn), y(qn), dx(qn)/dn, dy(qn)/dn, 100);
% % r = r1 - r2;
% % rn = 1 ./ arrayfun(@(idx) norm(r(idx,:)), 1:size(r,1))';
% % r = r .* [rn rn];
% 
% % cr = arrayfun(@(idx)cross([dxdy(idx,:) 0], [r(idx, :) 0]), 1:size(dxdy,1), 'UniformOutput', false)';
% % cr1 = arrayfun(@(idx)norm(cr{idx}), 1:size(dxdy,1));
% 
% % figure;
% % hold on;
% % plot(x, 1-cr1);
% 
% % plot(x, r31, 'r');
% % plot(x, r32, 'b');
% % plot(x, r4, 'k');
% % t = (H(1,1)+0.01):0.1:H(end,1);
% % h = interp1(H(:,1), H(:,2), t);
% % s = interp1(S(:,1), S(:,2), t);
% 
% %plot(t, h, 'g');
