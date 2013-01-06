/**
 * Disk usage statics using statvfs. 
 */

#include<stdio.h>
#include<sys/statvfs.h>
int main(int argc, char *argv[]){
	struct statvfs data;
	if(statvfs(argv[1],&data)<0){
		printf("Error\n");
		return 0;
	}
	printf("Disk file : %s\n",argv[1]);
	printf("block size: %u\n",data.f_bsize);
	printf("free block: %i\n",data.f_bfree);
	printf("total blocks: %i\n",data.f_blocks);
	return 0;
}
