#include "main.h"

int uint64_cmp(const void *a, const void *b) 
{ 
    if (*( data_t*)a >  *( data_t*)b)
    {
    	return 1;
 	}
    return -1;
}

double quick_sort(data_t arr[], size_t num)
{
	START_RECORDING_TIME;

	qsort(arr, num, sizeof(data_t) ,uint64_cmp );

	STOP_RECORDING_TIME;
	return CALCULATE_TIME;
}

double buble_sort(data_t arr[], size_t num)
{
	START_RECORDING_TIME;

	uint8_t swaped=1;
	for (size_t i = 0; i < num && swaped ; ++i)
	{
		swaped=0;
		for (size_t k = 0; k < num -1; ++k)
		{
			if (arr[k] > arr[k+1])
			{
				SWAP(arr[k] , arr[k+1]);
				swaped=1;
			}
		}
		
	}

	STOP_RECORDING_TIME;
	return CALCULATE_TIME;
}

double shellsort(data_t arr[], size_t num)
{
	START_RECORDING_TIME;

    int k;
    size_t  j,i;
    for (i = num / 2; i > 0; i = i / 2)
    {
        for (j = i; j < num; j++)
        {
            for(k = j - i; k >= 0; k = k - i)
            {
                if (arr[k+i] >= arr[k])
                {
                    break;
                }
                else
                {
                	SWAP(arr[k], arr[k+i]);
                }
            }
        }
    }
	
	STOP_RECORDING_TIME;
	return CALCULATE_TIME;
}

double merge_sort_not_rec(data_t arr[], size_t num)
{
	START_RECORDING_TIME;

	size_t size=0, i =0, j=0, h1=0,l1=0,l2=0,h2=0,k=0;
	data_t *temp=NULL;
	temp=malloc(sizeof(data_t)*num);
	if (temp == NULL)
	{
		return 0.0;
	}

	for(size=1; size < num; size=size*2 )
	{
		l1=0;
		k=0;  /*Index for temp array*/
		while( l1+size < num)
		{
			h1=l1+size-1;
			l2=h1+1;
			h2=l2+size-1;
			/* h2 exceeds the limlt of arr */
			if( h2>=num ) 
				h2=num-1;
			
			/*Merge the two pairs with lower limits l1 and l2*/
			i=l1;
			j=l2;
			
			while(i<=h1 && j<=h2 )
			{
				if( arr[i] <= arr[j] )
					temp[k++]=arr[i++];
				else
					temp[k++]=arr[j++];
			}
			
			while(i<=h1)
				temp[k++]=arr[i++];
			while(j<=h2)
				temp[k++]=arr[j++];
			/**Merging completed**/
			/*Take the next two pairs for merging */
			l1=h2+1; 
		}/*End of while*/

		/*any pair left */
		for(i=l1; k<num; i++) 
			temp[k++]=arr[i];

		for(i=0;i<num;i++)
			arr[i]=temp[i];

		}
	free(temp);

	STOP_RECORDING_TIME;
	return CALCULATE_TIME;
}
