function [m, h] = StrainRateSens1(p1, t1, h1, p2, t2, h2)
    h1 = h1(h1~=0);
    h2 = h2(h2~=0);
    t1 = t1(t1~=0);
    t2 = t2(t2~=0);
    %h = max(h1(1), h2(1)):0.5:min(h1(end), h2(end));
    h = 42:0.5:min(h1(end), h2(end));
    ti = interp1(h1, t1, h, 'spline');
    tj = interp1(h2, t2, h, 'spline'); 
    for i = 1:numel(h)
        m(i) = log(p1/p2)/log(tj(i)/ti(i));
    end
end

