#include <math.h>
#include <stdio.h>
typedef struct {unsigned char r,g,b;} srgb8;
typedef struct {float r,g,b;} lrgbf;

// red
srgb8 c09 = {0xbf,0x61,0x6a};
// green
srgb8 c10 = {0xa3,0xbe,0x8c};
// yellow
srgb8 c11 = {0xeb,0xcb,0x8b};
// blue
srgb8 c12 = {0x81,0xa1,0xc1};
// magenta
srgb8 c13 = {0xb4,0x8e,0xad};
// cyan
srgb8 c14 = {0x88,0xc0,0xd0};

float to_gamma(float a){
	return 0.0031308f >= a ? 12.92f * a : 1.055f * powf(a, 1.f / 2.4f) - 0.055f;
};
float to_linear(float a){
	return 0.04045f < a ? powf((a + 0.055f) / 1.055f, 2.4f) : a / 12.92f;
};

lrgbf srgb8_to_lrgbf(srgb8 c){
    return (lrgbf){
        to_linear(((float)c.r)/255.f),
        to_linear(((float)c.g)/255.f),
        to_linear(((float)c.b)/255.f)
    };
}

srgb8 lrgbf_to_srgb8(lrgbf l){
    return (srgb8){
        (unsigned char)(to_gamma(l.r)*255.f+0.5f),
        (unsigned char)(to_gamma(l.g)*255.f+0.5f),
        (unsigned char)(to_gamma(l.b)*255.f+0.5f)
    };
}

srgb8 brighten(srgb8 c, float max){
    lrgbf l = srgb8_to_lrgbf(c);
    l.r/=max;
    l.g/=max;
    l.b/=max;
    return lrgbf_to_srgb8(l);
}

void print_srgb8(srgb8 c){
    printf("%x%x%x\n",c.r,c.g,c.b);
}

int main(){
    float max = to_linear(((float)0xeb)/255.f);
    print_srgb8(brighten(c09,max));
    print_srgb8(brighten(c10,max));
    print_srgb8(brighten(c11,max));
    print_srgb8(brighten(c12,max));
    print_srgb8(brighten(c13,max));
    print_srgb8(brighten(c14,max));
}
