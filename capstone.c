
#ifdef __cplusplus
extern "C"{
#include<stdlib.h>
#include<stdio.h>
#include<rtl-sdr.h>
#include<math.h>
}
#endif

typedef struct rtlsdr_dev rtlsdr_dev_t;
char manufact[256];
char product[256];
char serial[256];
int ret;
int ret1;
int freq;
int len;
int nread;
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

freq=1079000000;

ret=rtlsdr_set_center_freq(dptr,freq);
if (ret==0){
printf("freq set \n");
}
else{
fprintf(stderr, "freq set failed\n");
exit(1);
}

ret=rtlsdr_reset_buffer(dptr);
if (ret !=0){
fprintf(stderr, "Failed to reset internal buffer\n");
}
else {
fprintf(stderr, "Buffer Reset\n");
}

rate=2000000;

ret=rtlsdr_set_sample_rate(dptr,rate);

if (ret !=0){
fprintf(stderr, "Failed to set sample rate\n");
}
else {
fprintf(stderr, "Sample Rate Set\n");
}
unsigned char data[16384];
len=16384;

ret1=rtlsdr_read_sync(dptr,data,len,&nread);

printf("# read_sync	=> %d (%d bytes)\n", ret1, nread);
fprintf(stderr,"ret1 is equal to %d\n",ret1);
fprintf(stderr,"nread is equal to %d\n",nread);
fprintf(stderr,"len is equal to %d\n",len);
fprintf(stderr,"data is equal to %d\n",data);
fprintf(stderr,"dptr is equal to %d\n",dptr);

int num=2129691224;
fprintf(stderr,"num is equal to %d\n",num);
int i;
float sum, mean, sd, var;
for(i=0;i<16384;i++){
sum=ret1;
mean=sum/num;
sum=0.0;
}
for(i=0;i<16384;i++){
var=(num-mean)*(num-mean);
sd=sqrt(var/num);
}
fprintf(stderr,"sum is equal to %d\n",var);
fprintf(stderr,"mean is equal to %d\n",mean);
fprintf(stderr,"var is equal to %d\n",var);
fprintf(stderr,"sd is equal to %d\n",sd);
return rtlsdr_close(dptr);
return 0;
}

