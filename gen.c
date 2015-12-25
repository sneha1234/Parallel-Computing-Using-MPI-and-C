#include<stdio.h>
#include<stdlib.h>
static int ste = 31;
/*
* randint() function is called to generate random capacities for different arcs
*/
int randint(int max,int min)
{
srand(time(NULL) - ste );
ste *= 313;
return min+(int)((int)(max-min+1)*(rand()/(RAND_MAX+1.0)));
}
int main(int argc, char* argv[] )
{
/*
* Checking whether the user has passed correct number of arguments
*/
if(argc != 5)
{
printf(" Format Error : exit(0)\n Usage: ./gen -v <vertices> -f <file name> \n ");
printf(" number of vertices should be of the form v={(st-2)*(st-3)+2}*n+2 where n=1,2,3.......\n");
exit(0);
}
FILE *f = fopen(argv[4],"w");
int i,j;
int v = atoi(argv[2]);
int st = 5;
int c = 10;
int s = 1;
int **graph;
int limit = v + 1;
//logic for forming initial edges
int rst,n;
rst=st-2;
n=rst*(rst-1)+2;//no. of nodes in a single cluster of nodes

graph = (int **) calloc(limit, sizeof(int *));
for (i = s; i < limit; ++i)
{
graph[i] = (int *) calloc(limit, sizeof(int));
}
/*
*Counter variable to count the total number of arcs
*/
int counter = 0;
if (n - 2 < rst || rst == 0)
{
printf("\nInvalid number of stages\nEXIT[0]\n");
exit(0);
}
int start=0,w=0;
//logic for forming cluster
for(start=2;start<v;start=start+n)//for 1
{

graph[1][start]=randint(c,2);
counter++;
for (i = 1; i <= rst; ++i)//for 2
{
graph[start][start + i] = randint(c,2);
counter ++;
for (j = i + start; j < (n+start); j = j + rst)//for 3
{
if (j +rst < (n+start))
{

graph[j][j + rst] = randint(c,2);
//printf("graph[%d][%d]\n",j,j + rst);
counter ++;
}//end of if
//graph[j - rst][n+start-1] = randint(c,2);
//counter ++;
}//end of for 3
}//enf of for 2

for(w=(n+start-rst);w<(n+start-1);w++)
graph[w][n+start-1]=randint(c,2);

graph[n+start-1][v]=randint(c,2);

}//end of cluster building



//adding random arcs in the graph
int ran_arc_num = n / 4;
int a, b, from, to;

for (start=2;start<v;start=start+n)//for1
{

for (i = 0; i < ran_arc_num; ++i)//for 2
{
do
{
a = randint(start+n - 1,start);
b = randint(start+n - 1,start);
}
while(a == b);

if (a < b)
{
from = a;
to=b;
}
else
{
from = b;
to = a;
}

if (graph[from][to] == 0)
{
graph[from][to] = randint(c,2);
counter ++;
}

}//end of for 2
}//end of for 1

//adding first line in the output file
fprintf(f,"%d\n",v);
//generating the graph files with respect the source vertex
for (i = 1; i < limit; ++i){
for (j = 1; j < limit; ++j){
if (graph[i][j] != 0){
if (s == 1)
{
fprintf(f,"%d %d %d\n", i, j, graph[i][j]);
}else{
fprintf(f,"%d %d %d\n", i - 1, j - 1, graph[i][j]);
}
}
}
}
printf("\n File created : %s \t[ OK ]\n ARC COUNT : %d \t[ OK ]\n\n",argv[10],counter);
fclose(f);
return 0;
}


