#include "main.h"
 
#define NUMBER_OF_FUCTIONS 4

int main(/*int argc, char const *argv[]*/)
{
	FILE *fp_config=NULL;
	char *line1 = NULL, *line2=NULL;
	size_t line1_size=0, line2_size=0;

	size_t num=0;

	fp_config=fopen("config_tests.txt","r");
	if (fp_config==NULL)
	{
		fprintf(stderr, "cant open config file exiting\n");
		return 1;
	}


	for (volatile int i = 0; i < 100000; ++i)
	{
		__asm__ __volatile__("");
	}

	size_t size=0;

	algoritam_t *alArrr=NULL;

	while(!feof(fp_config))
	{
		getdelim(&line1, &line1_size,' ',fp_config);
		sscanf(line1, "%zu", &num);
		// printf("%zu\n",num);

		size=getline(&line1, &line1_size, fp_config);

		if (size == 0)
		{
			break;
		}
		else
		{
			if (line1[size-1]=='\n')
			{
				line1[size-1]='\0';
			}
			if (line1[0]=='#')
			{
				continue;
			}
		}
		
		size=getline(&line2, &line2_size, fp_config);

		if (size == 0)
		{
			break;
		}
		else
		{
			if (line2[size-1]=='\n')
			{
				line2[size-1]='\0';
			}
			if (line2[0]=='#')
			{
				continue;
			}
		}

		FILE *fp=NULL;
		fp=fopen(line2,"r");
		if (fp==NULL)
		{
			fprintf(stderr, "cant open data file \n");
		}
		else
		{
			data_t *input=NULL;
			input = malloc(sizeof(data_t)*num);
			
			if (input==NULL)
			{
				fprintf(stderr, "cant allocate memory\n");
			}
			else
			{
				memset(input, 0, sizeof(data_t)*num);//valgrind

				if(fread(input, sizeof(data_t), num, fp) != num)
				{
					fprintf(stderr, "wrong size in config file\n skiping sort" );
				}
				else
				{
					alArrr=sort(input,num, line1);
				}	
				free(input);
			}	
			fclose(fp);
		}
	}


	if (line1)
	{
		free(line1);
	}
	
	if (line2)
	{
		free(line2);
	}

	if (alArrr != NULL)
	{
		print_to_file(alArrr);
	}

	sort(NULL, 0, NULL); //free memory
	
	if (fp_config!=NULL)
	{
		fclose(fp_config);
	}
	

	return 0;
}


int test_sort(data_t arr[], size_t num)
{
	uint8_t sorted=0;
	for (size_t i = 0; i < num-1; ++i)
	{
		if (arr[i] > arr[i+1])
		{
			sorted=1;
			// printf("%u  %lu > %lu\n",i ,arr[i] ,arr[i+1] );
		}
	}
	return sorted;
}



// #define ALLOC_MEM_NAME(name) malloc(sizeof(char)* (strlen(name)));
int initAlgoritams(algoritam_t *alArrr[],size_t num)
{

	(*alArrr)=malloc(sizeof(algoritam_t)*num);

	algoritam_t *tempAlArr = (*alArrr);

	if (!tempAlArr)
	{
		fprintf(stderr, "error alocating memory\n" );
		return 1;
	}
	memset(tempAlArr, 0, sizeof(algoritam_t)*num);

	for (size_t i = 0; i < num; ++i)
	{
		tempAlArr[i].numOftest=20;
		// tempAlArr[i].tests=NULL;
		tempAlArr[i].tests=malloc(sizeof(test_t)*tempAlArr[0].numOftest);
		// tempAlArr[i].nameOfalgoritam=NULL;

		if (tempAlArr[i].tests==NULL)
		{
			return 2;
		}
	}


	{
	char name[]="merge_sort_not_rec";
	tempAlArr[0].fuction=merge_sort_not_rec;
	tempAlArr[0].nameOfalgoritam= malloc(sizeof(char)* (strlen(name))+1);
	if (tempAlArr[0].nameOfalgoritam == NULL)
	{
		return 3;
	}
	strcpy(tempAlArr[0].nameOfalgoritam, name);
	}

	{
	char name[]="shellsort";
	tempAlArr[1].fuction=shellsort;
	tempAlArr[1].nameOfalgoritam= malloc(sizeof(char)* (strlen(name))+1);
	strcpy(tempAlArr[1].nameOfalgoritam, name);
	if (tempAlArr[1].nameOfalgoritam == NULL)
	{
		return 3;
	}
	}

	{
	char name[]="buble_sort";
	tempAlArr[2].fuction=buble_sort;
	tempAlArr[2].nameOfalgoritam= malloc(sizeof(char)* (strlen(name))+1);
	if (tempAlArr[2].nameOfalgoritam == NULL)
	{
		return 3;
	}
	strcpy(tempAlArr[2].nameOfalgoritam, name);
	}
	{
	char name[]="quick_sort";
	tempAlArr[3].fuction=quick_sort;
	tempAlArr[3].nameOfalgoritam= malloc(sizeof(char)* (strlen(name))+1);
	strcpy(tempAlArr[3].nameOfalgoritam, name);
	if (tempAlArr[3].nameOfalgoritam == NULL)
	{
		return 3;
	}
	}

	return 0;
}

void free_algoritams_t(algoritam_t *alg, size_t num)
{
	static uint8_t count = 1;


	for (size_t k = 0; k < num ; ++k)
	{
		free(alg[k].nameOfalgoritam);
		for (size_t i = 0; i < alg[k].numOfmadeTest && count; ++i)
		{
			free(alg[k].tests[i].nameOftest);
		}
		count=0;
		free(alg[k].tests);
	}
	free(alg);

}


algoritam_t *sort(data_t input[],size_t num, char name[])
{
	static algoritam_t *alArrr=NULL;
	static uint8_t runed = 0; // marker if the fuction has runed

	if (alArrr == NULL && runed == 0)
	{
		if(initAlgoritams(&alArrr,NUMBER_OF_FUCTIONS))
		{
			// *error=1;
		}
	}


	if ((!input && !num && !name && runed)) //|| *error == 1)
	{
		free_algoritams_t(alArrr,NUMBER_OF_FUCTIONS);
		return NULL;
	}
	runed =1;

	char *dName=NULL;
	if (!name)
	{
		fprintf(stderr, "no name of test\n" );
	}
	else
	{
		dName = malloc(sizeof(char)*strlen(name)+1);
		if (!dName)
		{
			fprintf(stderr, "error alocating memory dName\n" );
		}else
		{
			strcpy(dName,name);
		}
	}

	data_t *data=NULL;
	data=malloc(sizeof(data_t)*num);
	if (!data)
	{
		fprintf(stderr, "error alocating memory for tests \n" );
		return alArrr;
	}
	memcpy(data,input,num*sizeof(data_t));

 	for (size_t i = 0; i < NUMBER_OF_FUCTIONS; ++i)
 	{
 		puts("--------------------------------");
 		if (alArrr[i].numOfmadeTest > alArrr[i].numOftest)
 		{
 			alArrr[i].numOftest*=2;

 			test_t *temp =NULL;
			 temp=realloc(alArrr[i].tests, sizeof(test_t)*alArrr[i].numOftest );
			 if (temp != NULL)
			 {
			 	alArrr[i].tests=temp;
			 }

 			if (!alArrr[i].tests)
 			{
 				fprintf(stderr, "error expanding array\n" );
 			}
 		}

 		alArrr[i].tests[alArrr[i].numOfmadeTest].time= alArrr[i].fuction(data,num);

 		if (alArrr[i].tests[alArrr[i].numOfmadeTest].time == 0.0)
 		{
 			fprintf(stderr, "To fast or error\n");
 		}

 		alArrr[i].tests[alArrr[i].numOfmadeTest].nameOftest=dName;
		alArrr[i].numOfmadeTest++;

		printf("Име на алгоритам %s\n",alArrr[i].nameOfalgoritam );
 		printf("Име на test %s\n",alArrr[i].tests[alArrr[i].numOfmadeTest-1].nameOftest );
		printf("\t%.10lf\n",alArrr[i].tests[alArrr[i].numOfmadeTest-1].time);

 		if (test_sort(data, num))
		{
			fprintf(stderr, "not:() sorted\n");
		}

		// for (size_t l = 0; l < num; ++l)		{printf("%lu\n", data[l]);}

		memcpy(data,input,num*sizeof(data_t));
 	}

 	// printf("\t%.10lf\n",alArrr[0].tests[0].time);
	free(data);
	return alArrr;
}



int print_to_file(algoritam_t alArrr[])
{
	FILE *fp=NULL;

	fp=fopen("results.csv","w");

	fprintf(fp,"\"Name of test/Name of algoritam\""); 

	for (size_t i = 0; i < NUMBER_OF_FUCTIONS; ++i)
	{
		fprintf(fp,",\"%s\"" ,alArrr[i].nameOfalgoritam); 
	}
	fprintf(fp,"\n"); 

	for (size_t k = 0; k < alArrr[0].numOfmadeTest; ++k)
	{
		fprintf(fp,"\"%s\"" ,alArrr[0].tests[k].nameOftest); 
		for (size_t i = 0; i < NUMBER_OF_FUCTIONS; ++i)
		{
			fprintf(fp,",%.9lf" ,alArrr[i].tests[k].time); 
		}
		fprintf(fp,"\n"); 
	}
	
	fprintf(fp,"\n"); 
	fclose(fp);
	return 0;
}

