
#ifdef __cplusplus
extern "C"{
#include<stdlib.h>
#include<stdio.h>
#include<rtl-sdr.h>
#include<math.h>
}
#endif
#define LEN 16384
#define RATE 2000000
#define F1 88e6
#define F2 108e6
#define dF 10000

typedef struct rtlsdr_dev rtlsdr_dev_t;
char manufact[256];
char product[256];
char serial[256];
int ret;
int ret1;
int freq;
int len;
int nread;
int gain;
uint32_t rate;
rtlsdr_dev_t *dptr;
unsigned char buffer[4096];
int main(int argc, char *argv[]){

int ret=rtlsdr_get_device_usb_strings(0,manufact,product,serial);
if (ret==0){
printf("it worked \n");
}

else{
fprintf(stderr, "it did not work \n");
exit(1);
}

ret=rtlsdr_open(&dptr,0);
if (ret==0){
printf("open function completed\n");
}
else {
fprintf(stderr, "open function not completed\n");
exit(1);
}

gain=215;

ret=rtlsdr_set_tuner_gain(dptr,gain);
if (ret==0){
printf("gain set\n");
}
else{
printf("gain not sent\n");
exit(1);
}

ret=rtlsdr_reset_buffer(dptr);
if (ret !=0){
fprintf(stderr, "Failed to reset internal buffer\n");
}
else {
fprintf(stderr, "Buffer Reset\n");
}

rate=RATE;

ret=rtlsdr_set_sample_rate(dptr,rate);

if (ret !=0){
fprintf(stderr, "Failed to set sample rate\n");
}
else {
fprintf(stderr, "Sample Rate Set\n");
}
unsigned char data[16384];
len=LEN;
int i, freq, j, k, g;
int base_freq=F1;
int nsteps=((F2-F1)/dF);
//fprintf(stderr,"nsteps is equal to %d\n",nsteps);
for(i=0;i<=nsteps;i++){
freq=base_freq+(i*dF);

rtlsdr_set_center_freq(dptr,freq);

fprintf(stderr,"freq is equal to %d\n",freq);

ret1=rtlsdr_read_sync(dptr,data,len,&nread);

printf("# read_sync     => %d (%d bytes)\n", ret1, nread);

int num=8192;
float rsum=0.0, rmean, rsd, rvar=0.0;
float isum=0.0, imean, isd, ivar=0.0;
float si, sr;
for(j=0;j<num;j++){
si=data[2*j]-127.5,sr=data[2*j+1]-127.5;
rsum=rsum+sr;
isum=isum+si;
}
rmean=(rsum/num);
imean=(isum/num);
for(k=0;k<num;k++){
rvar=rvar+((sr-rmean)*(sr-rmean));
ivar=ivar+((si-imean)*(si-imean));
}
rvar=rvar/num;
ivar=ivar/num;
rsd=sqrt(rvar);
isd=sqrt(ivar);

fprintf(stderr,"rvar is equal to %f\n",rvar);
fprintf(stderr,"ivar is equal to %f\n",ivar);
//fprintf(stderr,"num is equal to %d\n",num);
fprintf(stderr,"rsum is equal to %f\n",rsum);
fprintf(stderr,"isum is equal to %f\n",isum);
fprintf(stderr,"rmean is equal to %f\n",rmean);
fprintf(stderr,"imean is equal to %f\n",imean);
fprintf(stderr,"rsd is equal to %f\n",rsd);
fprintf(stderr,"isd is equal to %f\n",isd);
}
return rtlsdr_close(dptr);
return 0;
}

