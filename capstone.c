
#ifdef __cplusplus
extern "C"{
#include<stdlib.h>
#include<stdio.h>
#include<rtl-sdr.h>
#include<math.h>
}
#endif

typedef struct rtlsdr_dev rtlsdr_dev_t;
char manufact[64];
char product[64];
char serial[64];
int ret;
uint32_t freq;
int len;
int nread;
uint32_t rate;
rtlsdr_dev_t *dptr;
char buffer[256];
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

freq=991000000;

ret=rtlsdr_set_center_freq(dptr,freq);
if (ret==0){
printf("freq set \n");
}
else{
fprintf(stderr, "freq set failed\n");
exit(1);
}

rate=2000000;

ret=rtlsdr_set_sample_rate(dptr,rate);
if (ret==0){
fprintf(stderr, "Failed to set sample rate\n");
}

ret=rtlsdr_reset_buffer(dptr);
if (ret==0){
fprintf(stderr, "Failed to reset internal buffer\n");
exit(1);
}
unsigned char data[16384];
len=sizeof(data);

ret=rtlsdr_read_sync(dptr,buffer,len,&nread);
if (ret==0){
printf("complete\n");
}
else {
printf("READ FAILED\n");
}
return 0;
}

