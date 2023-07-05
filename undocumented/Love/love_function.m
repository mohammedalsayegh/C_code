nsamp =200;
for k = 1:200
{ 
    t[k] = (float)(k) / (((float)(nsamp) - 1.0)*1000);
    loveX = (sin(2*pi*freq*t[k]))*(sin(2*pi*freq*t[k]))*(sin(2*pi*freq*t[k]));
    loveY = (0.8125*cos(2*pi*freq*t[k]))-(0.3125*cos(4*pi*freq*t[k]))-(0.125*cos(6*pi*freq*t[k])) - (0.0625*cos(8*pi*freq*t[k]));
}