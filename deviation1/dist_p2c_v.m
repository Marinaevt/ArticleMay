function [ x0, fval ] = dist_p2c_v( F, X )
%DIST_P2C_V calculate relative distance from X to curve F(:,:)
% this is vectorized version of DIST_P2C
% 
%  s1 =  max(abs(F(:,1)));
%  s2 =  max(abs(F(:,2)));
rdfunc = @(x, idx)sum((([x interp1(F(:,1),F(:,2),x)] - X(idx, :))./X(idx, :)).^2);
% rdfunc = @(x, idx)sum((([x interp1(F(:,1),F(:,2),x)] - X(idx, :))./[s1 s2]).^2);
[x0, fval] = arrayfun(@(idx)fminbnd(@(x)rdfunc(x, idx),...
                      F(1, 1), F(end, 1), optimset('TolX',1e-20)), 1:size(X, 1));
end