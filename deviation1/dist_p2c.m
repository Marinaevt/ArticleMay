function [ x0, fval ] = dist_p2c( F, X )
%DIST_P2C calculate relative distance from X to curve F(:,:)
%d = [x' interp1(F(:,1),F(:,2),x)'] - X(ones(size(x,2),1) + 1,2:3);
%r = arrayfun(@(idx) norm(d(idx,:)), 1:size(d,1))

rdfunc = @(x)norm([x interp1(F(:,1),F(:,2),x)] - X)./abs(X);
[x0, fval] = fminbnd(rdfunc, F(1, 1), F(end, 1));
end

