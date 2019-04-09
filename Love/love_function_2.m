freq=1000;
Amp=1;
ts=1/200000;
T=1e-3;
t=0:ts:T;

tempX = (sin(2*pi*freq*t)).*(sin(2 .* pi .* freq .* t)).*(sin(2 .* pi .* freq .* t));
tempY = (0.8125 .* cos(2 .* pi .* freq .* t))-(0.3125 .* cos(4 .* pi .* freq .* t))-(0.125 .* cos(6 .* pi .* freq .* t)) - (0.0625 .* cos(8 .* pi .* freq .* t));

figure(1)
plot(tempX,tempY);

figure(2)
plot(tempX);

figure(3)
plot(tempY);