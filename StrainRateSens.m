function [m, h] = StrainRateSens(p1, t1, h1, p2, t2, h2)
    h1 = h1(h1~=0);
    h2 = h2(h2~=0);
    t1 = t1(t1~=0);
    t2 = t2(t2~=0);
    hi = h1(1):0.05:h1(end);
    ti = interp1(h1, t1, hi, 'spline');
    hj = h2(1):0.05:h2(end);
    tj = interp1(h2, t2, hj, 'spline');
    k = 1;  
    for i = 1:numel(hi)
        for j = 1:numel(hj)
            if hi(i) == hj(j)
                m(k) = log(p1/p2)/log(tj(j)/ti(i));
                h(k) = hi(i);
                k = k + 1;
            end
        end
    end
end

