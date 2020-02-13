
#ifdef __cplusplus
extern "C"{
#include<stdint.h>
#include<rtl-sdr_export.h>
#include<stdlib.h>
#include<stdio.h>
#include<rtl-sdr.h>
#include<rtl-sdr_export.h>
#include<math.h>
}
#endif

typedef struct rtlsdr_dev rtlsdr_dev_t;
char *manufact[64];
char *product[64];
char *serial[64];
int ret;
uint32_t freq;
int len;
uint32_t rate;
rtlsdr_dev_t *dptr;
void *buffer[256];
int n_read[256];
int main(){

int ret=rtlsdr_get_device_usb_strings(0,NULL,NULL,NULL);
if (ret==0){
printf("it worked \n");
}

else{
printf("it did not work \n");
exit(1);
}

rtlsdr_open(&dptr,0);
printf("open function completed\n");

freq=991000000;
rtlsdr_set_center_freq(dptr,freq);
printf("freq set \n");

rate=2000000;
rtlsdr_set_sample_rate(dptr,rate);

rtlsdr_reset_buffer(dptr);
len=16384;
rtlsdr_read_sync(dptr,buffer,len,n_read);

printf("complete\n");
}


