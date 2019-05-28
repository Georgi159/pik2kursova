#define _GNU_SOURCE
#include <stdio.h>
#include <inttypes.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <setjmp.h> 

#ifndef MAIN_LIB_1
#define MAIN_LIB_1

	// #ifdef _MSC_VER
	//     #define forceinline __forceinline
	// #elif defined(__GNUC__)
	//     #define forceinline inline __attribute__((__always_inline__))
	// #elif defined(__CLANG__)
	//     #if __has_attribute(__always_inline__)
	//         #define forceinline inline __attribute__((__always_inline__))
	//     #else
	//         #define forceinline inline
	//     #endif
	// #else
	//     #define forceinline inline
	// #endif
// #undef forceinline

// #define forceinline 

#include <stdio.h>
#include <inttypes.h>
#include <time.h>


#define SWAP(a,b)	do{ (a)=(a)^(b); (b)=(a)^(b); (a)=(a)^(b); }while(0)


#define START_RECORDING_TIME timeStat_t stTime ;\
	clock_gettime( CLOCK_REALTIME,&(stTime.begin))


#define STOP_RECORDING_TIME do\
{\
	clock_gettime( CLOCK_REALTIME,&(stTime.end));\
	stTime.elapsed.tv_sec= stTime.end.tv_sec - stTime.begin.tv_sec;\
	stTime.elapsed.tv_nsec= stTime.end.tv_nsec - stTime.begin.tv_nsec;\
	if ((stTime.end.tv_nsec < stTime.begin.tv_nsec) )\
	{\
		stTime.elapsed.tv_sec--;\
		stTime.elapsed.tv_nsec+=1E9;		\
	}\
} while (0)

#define CALCULATE_TIME ((double)stTime.elapsed.tv_sec+((double)stTime.elapsed.tv_nsec)/1E9)

typedef struct time_stat
{
	struct timespec begin;
	struct timespec end;
	struct timespec elapsed;
} timeStat_t;

typedef uint64_t data_t;


typedef struct test 
{
	double time;
	char *nameOftest;

}test_t;

typedef struct algoritam
{
	double (*fuction) (data_t arr[], size_t num);
	char *nameOfalgoritam;
	size_t numOftest;
	size_t numOfmadeTest;
	test_t *tests;
}algoritam_t;



 
double buble_sort(data_t arr[], size_t num);
double shellsort (data_t arr[], size_t num);
double quick_sort(data_t arr[], size_t num);
double merge_sort_not_rec(data_t arr[], size_t num);


int test_sort(data_t arr[], size_t num);

algoritam_t *sort(data_t input[],size_t num, char name[]);

int initAlgoritams(algoritam_t *alArrr[],size_t num);



#endif
