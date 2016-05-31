% MARC OUTPUT ANALYZER AND MAP PLOTTER
clear all;
close all;
Dh=zeros(11, 5);
Ds=zeros(11, 5);
ex = csvread('AMG6.csv', 1);
% k=35;
% m=4;
% fname = sprintf('plotp3k%03dm%03d',p k, m);
for k=1:11
    for m=1:5    
        % -------------------------- read input file to H, S
        fname = sprintf('plot%02dp%01d',k, m);
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
        if m == 1
            [th, fh] = dist_p2c_v(H, ex(1:10, 2:3));
            [th, fs] = dist_p2c_v(S, ex(1:10, 2:3));
            Dh(k, m) = sum(fh)/10;
            Ds(k, m) = sum(fs)/10;
        elseif m == 2
            [th, fh] = dist_p2c_v(H, ex(11:14, 2:3));
            [th, fs] = dist_p2c_v(S, ex(11:14, 2:3));
            Dh(k, m) = sum(fh)/4;
            Ds(k, m) = sum(fs)/4;
        elseif m == 3
            [th, fh] = dist_p2c_v(H, ex(15:18, 2:3));
            [th, fs] = dist_p2c_v(S, ex(15:18, 2:3));
            Dh(k, m) = sum(fh)/4;
            Ds(k, m) = sum(fs)/4;
        elseif m == 4
            [th, fh] = dist_p2c_v(H, ex(19:22, 2:3));
            [th, fs] = dist_p2c_v(S, ex(19:22, 2:3));
            Dh(k, m) = sum(fh)/4;
            Ds(k, m) = sum(fs)/4;
        elseif m == 5
            [th, fh] = dist_p2c_v(H, ex(23:26, 2:3));
            [th, fs] = dist_p2c_v(S, ex(23:26, 2:3));
            Dh(k, m) = sum(fh)/4;
            Ds(k, m) = sum(fs)/4;
        end
        % -------------------------- end of read input file
%           [th, fh] = dist_p2c_v(H, ex(15:18, 2:3));    
%          [th, fh] = dist_p2c_v(H, ex(27:27, 2:3));
%         [th, fh] = dist_p2c_v(H, ex(1:10, 2:3));%!
%         [th, fh] = dist_p2c_v(H, ex(1:1, 2:3));
%         [th, fh] = dist_p2c_v(H, ex(2:2, 2:3));
%         [th, fh] = dist_p2c_v(H, ex(3:3, 2:3));
%         [th, fh] = dist_p2c_v(H, ex(4:4, 2:3));
%         [th, fh] = dist_p2c_v(H, ex(5:5, 2:3));
%         [th, fh] = dist_p2c_v(H, ex(6:6, 2:3));
%         [th, fh] = dist_p2c_v(H, ex(7:7, 2:3));
%         [th, fh] = dist_p2c_v(H, ex(8:8, 2:3));
%         [th, fh] = dist_p2c_v(H, ex(9:9, 2:3));
%         [th, fh] = dist_p2c_v(H, ex(10:10, 2:3));

%          [ts, fs] = dist_p2c_v(S, ex(15:18, [2 5])) 
%         [ts, fs] = dist_p2c_v(S, ex(27:27, [2 5]));
%          [ts, fs] = dist_p2c_v(S, ex(1:10, [2 5]));
%          [ts, fs] = dist_p2c_v(S, ex(1:1, [2 5]));
%          [ts, fs] = dist_p2c_v(S, ex(2:2, [2 5]));
%          [ts, fs] = dist_p2c_v(S, ex(3:3, [2 5]));
%          [ts, fs] = dist_p2c_v(S, ex(4:4, [2 5]));
%          [ts, fs] = dist_p2c_v(S, ex(5:5, [2 5]));
%          [ts, fs] = dist_p2c_v(S, ex(6:6, [2 5]));
%          [ts, fs] = dist_p2c_v(S, ex(7:7, [2 5]));
%          [ts, fs] = dist_p2c_v(S, ex(8:8, [2 5]));
%          [ts, fs] = dist_p2c_v(S, ex(9:9, [2 5]));
%          [ts, fs] = dist_p2c_v(S, ex(10:10, [2 5]));
            
          
%         Dh(k/100,m)= sum(fh);
%         Ds(k/100,m)= sum(fs);
%         Dhs=Dh+Ds;
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
