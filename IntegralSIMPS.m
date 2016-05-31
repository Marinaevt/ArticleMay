function [I] = IntegralSIMPS(bot, up, m)
    intg = @(x)(((sin(x)).^3./x.^2).^(1./m).*(1./x - 1./tan(x)));
    I = integral(intg, bot, up);
end

