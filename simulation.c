#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

#define MAX_STATE 10
#define MAX_LOOP 10000000

struct state {
	int num;
	int id;
	int valid;
};

double average;
long arrivals;
long count;
struct state state;
double p[MAX_STATE*2+2];
long arrivals_arr[MAX_STATE*2+2];
int valid[MAX_STATE*2+2];
int type[MAX_STATE*2+2];
double average_old[MAX_LOOP];
int e;

void output(void) {
	int i;
	printf("=============================================================== \n");
	printf("=            *** Results from M/M/2/10 simulation ***         = \n");
	printf("=============================================================== \n");
	printf("=    Total number of arrivals 	= %ld\n", arrivals);
	printf("=    Total arrivals and posibility in each state\n");
	for (i=0; i<=MAX_STATE*2+1; i++) {
		if (valid[i])
			printf("=    total[%d] 		= %ld			posibility[%d]		 = %lf\n",i,arrivals_arr[i],i,p[i]);
	}
	printf("=    Number of transitions	= %ld\n", count);
	printf("=    Current State 		= %d-%d\n", state.num, state.id);
	printf("=    Average number of customers  	= %lf\n", average);
	printf("=============================================================== \n");
}

void arrival(void) {
	arrivals++;
	arrivals_arr[state.num*2+state.id]++;
	count++;
	if (state.num == MAX_STATE)
		return;
	state.num++;
}

void departure() {
	int i;
	count++;	
	for (i=0; i<=MAX_STATE*2+1; i++)
		if (type[i] != -1)
			p[i] =	 (float)arrivals_arr[i] / arrivals;
	average = 0.0;
	for (i=0; i<=MAX_STATE*2+1; i++) {
		if (type[i] != -1)
			average += i/2*p[i];
	}
}

int main(int argc, char *argv[])
{
	double random;
	int k,l,ma,mb;
	int i,j,ii=0;
	if (argc < 3) {
		printf("./sim <k> <l>\n");
		exit(0);
	}
	k = atoi(argv[1]);
	l = atoi(argv[2]);
	ma = 4; mb = 1; e = 5;
	srand(time(NULL));
	for (i=0; i<=MAX_STATE*2+1; i+=2) {
		arrivals_arr[i] = 0;
		p[i] = 0.0;
		if (i<=2*k+1) {
			valid[i] = valid[i+1] = 1;
			type[i] = 0;
			type[i+1] = 1;
		}
		else {
			valid[i] = 1;
			valid[i+1] = 0;
			type[i] = 2;
			type[i+1] = -1;
		}
	}
	valid[0] = 1; valid[1] = 0; 
	type[0] = 0; type[1] = -1;
	type[2*(k+1)] = 1;
	count = arrivals = 0;
	state.num = 0;
	state.id = 0;
	average = 0.0;

	for (j=0; j<=MAX_LOOP; j++) {
		random = (float)rand() / RAND_MAX;
		if (state.num == 0) {
			state.id=0;
			arrival();
		}
		else if (state.num*2+state.id == 3) {
			if (random < (float)l / (l+mb)) {
				arrival();
				if (state.num == k+1)
					state.id = 0;
			}
			else {
				state.num--;
				state.id = 0;
				departure(j);
			}
		}
		else if (type[state.num*2+state.id] == 0) {
			if (random < (float)l / (l+ma)) {
				arrival();
			}
			else {
				state.num--;
				departure(j);
			}
		}
		else if (type[state.num*2+state.id] == 1)
		{
			if (random < (float)l / (l+ma+mb)) {
				arrival();
				if (state.num == k+1)
					state.id = 0;
			}
			else if (random < ((float)l+ma) / (l+ma+mb)) {
				state.num--;
				state.id=1;
				departure(j);
			}
			else {
				state.num--;
				state.id=0;
				departure(j);
			}
		}
		else if (type[state.num*2+state.id] == 2) {
			if (random < (float)l / (l+ma+mb)) {
				arrival();
			}
			else {
				state.num--;
				departure(j);
			}	
		}
		else {
			printf("error\n");
			exit(1);
		}
		if (j % 1000 == 0 && j>0) {
			//uncomment to print average number of customers through time
			//printf("%lf\n",average);
			average_old[ii++] = average;
			if (fabs(average_old[ii-1] - average_old[ii-2]) < pow(10,-e)) {
				output();
				exit(0);
			}	
		}
	}
	output();
	return 0;
}