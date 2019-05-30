#include "main.h"

int print_to_file(algoritam_t alArrr[])
{
	FILE *fp=NULL;
	int error=1;
	if (alArrr == NULL)
	{
		return 4;
	}

	fp=fopen("results.csv","w");
	if ( fp == NULL )
	{
		fprintf(stderr, "error openig file\n");
		return 1;
	}

	do
	{
		error=fprintf(fp,"\"Name of test/Name of algoritam\""); 
		if (error < 0) break;

		for (size_t i = 0; i < NUMBER_OF_FUCTIONS; ++i)
		{
			error=fprintf(fp,",\"%s\"" ,alArrr[i].nameOfalgoritam); 
			if (error < 0) break;
		}
		error=fprintf(fp,"\n"); 
		if (error < 0) break;

		for (size_t k = 0; k < alArrr[0].numOfmadeTest; ++k)
		{
			error=fprintf(fp,"\"%s\"" ,alArrr[0].tests[k].nameOftest); 
			if (error < 0) break;

			for (size_t i = 0; i < NUMBER_OF_FUCTIONS; ++i)
			{
				error=fprintf(fp,",%.9lf" ,alArrr[i].tests[k].time); 
				if (error < 0) break;
			}
			error=fprintf(fp,"\n"); 
			if (error < 0) break;
		}
	}while(0);
	
	fclose(fp);
	if (error < 0) return 2;
	return 0;
}


int print_best(algoritam_t alArrr[])
{
	uint32_t numberOfbest[NUMBER_OF_FUCTIONS]={0};
	uint32_t beast=0;

	for (size_t k = 0; k < alArrr[0].numOfmadeTest; ++k)
	{
		for (size_t i = 0; i < NUMBER_OF_FUCTIONS - 1 ; ++i)
		{
			
			if (alArrr[beast].tests[k].time > alArrr[i+1].tests[k].time)
			{
				beast=i+1;
			}
		}
		numberOfbest[beast]++;
		beast=0;
	}	

	beast=0;
	for (size_t i = 0; i < NUMBER_OF_FUCTIONS-1; ++i)
	{
		if (numberOfbest[beast] < numberOfbest[i+1])
		{
			beast = i+1;
		}
	}

	printf("This is the best : %s\nWith %u wins\n", alArrr[beast].nameOfalgoritam,numberOfbest[beast]);

	return 0;
}
