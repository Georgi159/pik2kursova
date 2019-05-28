#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>



int uint64_cmp(const void *a, const void *b) 
{ 
   // return -(int64_t)(*( data_t*)a) +(int64_t)(*( data_t*)b); 
    if (*( uint64_t*)a <  *( uint64_t*)b)
    {
    	return 1;
 	}
    return -1;
}

int main()
{
	FILE *fp=fopen("/dev/urandom","r");
	FILE *fw=fopen("testsored_re.dat","w");

	uint32_t *arr=NULL;
	uint32_t num=60000;

	arr=malloc(sizeof(uint64_t)*num);

	fread(arr,sizeof(uint64_t),num,fp);

	qsort(arr, num, sizeof(uint64_t) ,uint64_cmp );

	fwrite(arr, sizeof(uint64_t),num,fw);

	fclose(fp);
	fclose(fw);
	free(arr);
	return 0;
}

