#include<stdio.h>

main()
{
FILE *fp;
fp=fopen("/dev/memory","w");
fprintf(fp,"abc");
fclose(fp);
}
