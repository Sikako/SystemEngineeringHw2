#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[]){
	int fd;
	int ret;
	char opt;
	off_t begin, end;

	if(argc == 1){
		printf("lockf [file] [type(l/u)] [begin] [end]\n");
		exit(1);
	} 

	fd = open(argv[1], O_WRONLY);
	printf("fd = %d is opened\n", fd);

	sscanf(argv[2], "%c", &opt);
	sscanf(argv[3], "%ld", &begin);
	sscanf(argv[4], "%ld", &end);

	do{
		switch(opt){
			case 'l':
				lseek(fd, begin, SEEK_SET);
				ret = lockf(fd, F_LOCK, end - begin + 1);
				break;
			case 'u':
				lseek(fd, begin, SEEK_SET);
				ret = lockf(fd, F_UNLCK, end - begin + 1);
				break;
			default:
				printf("input error\n");
				exit(1);
		}
		printf("[type(l/u)] [begin] [end]\n");
		printf("|\n");
		printf("-->");
	
	}while(scanf("%c %ld %ld", &opt, &begin, &end));
	if(ret != 0)	perror("flock\n");
	printf("end\n");
	getchar();
	return 0;

}
