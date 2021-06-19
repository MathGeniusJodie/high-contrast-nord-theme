#include <math.h>
#include <stdio.h>
typedef struct {unsigned char r,g,b;} srgb8;
typedef struct {float r,g,b;} lrgbf;

srgb8 colors[] = {
    // red
    {0xbf,0x61,0x6a},
    // green
    {0xa3,0xbe,0x8c},
    // yellow
    {0xeb,0xcb,0x8b},
    // blue
    {0x81,0xa1,0xc1},
    // magenta
    {0xb4,0x8e,0xad},
    // cyan
    {0x88,0xc0,0xd0}
};

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

lrgbf brighten(lrgbf l, float max){
    l.r/=max;
    l.g/=max;
    l.b/=max;
    return l;
}

void print_hex(lrgbf l){
    srgb8 c = lrgbf_to_srgb8(l);
    printf("%02x%02x%02x\n",c.r,c.g,c.b);
}

#define MAX(a,b) (((a)>(b))?(a):(b))

int main(){
    int color_count = sizeof(colors)/sizeof(srgb8);
    for(int i=0;i<color_count;i++){
        lrgbf color = srgb8_to_lrgbf(colors[i]);
        float max = MAX(color.r,MAX(color.g*1.2f,color.b));

        printf("*.color%d: #",i+9);
        print_hex(brighten(color,max));
    }
}
