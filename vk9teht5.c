#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>

#define MAXPATH 256

void print_stat_info(struct stat st,struct dirent *direntp, int rec){
	

	//stat(direntp->d_name,&st);
	char *day, *month, *date, *hour, *minute, *second, * year; //to get the same format as ls -l
	
	//padding
	for (int i = 1;i<rec;i++){
		printf("\t");
	
	}
	//check if directory
	if (direntp->d_type == DT_DIR){
		printf("d");
	}else{
		printf("-");
	}
	//source stat: https://linuxhint.com/stat-system-call-linux/
	//printf((S_ISDIR(st.st_mode))? "d":"-" ); // did not work for subdirectories
	//different permissions
	printf((st.st_mode & S_IRUSR)? "r":"-");
	printf((st.st_mode & S_IWUSR)? "w":"-");
	printf((st.st_mode & S_IXUSR)? "x":"-");
	printf((st.st_mode & S_IRGRP)? "r":"-");
	printf((st.st_mode & S_IWGRP)? "w":"-");
	printf((st.st_mode & S_IXGRP)? "x":"-");
	printf((st.st_mode & S_IROTH)? "r":"-");
	printf((st.st_mode & S_IWOTH)? "w":"-");
	printf((st.st_mode & S_IXOTH)? "x":"-");
	printf("\t");
	
	//links
	printf("%ld\t",st.st_nlink);
	
	//sourc: https://stackoverflow.com/questions/7624127/finding-the-owner-and-group-of-a-file-as-a-string 
	//owner and group name
	printf("%s\t",getpwuid(st.st_uid)->pw_name);
	printf("%s\t",getgrgid(st.st_gid)->gr_name);
	
	//size of the file
	printf("%ld\t",st.st_size);
	
	day = strtok(ctime(&st.st_ctime)," "); //not used
	//only these 4 are in the ls -l
	month = strtok(NULL, " ");
	date = strtok(NULL, " ");
	hour = strtok(NULL,":");
	minute = strtok(NULL,":");
	
	second = strtok(NULL," ");//not used
	year = strtok(NULL,"\n");//not used
	
	//print the same format as ls- l
	printf("\t%s %2s %s:%s\t",month,date,hour,minute);
	//printf("\t%s\t",strtok(ctime(&st.st_ctime),"\n")); //for printingh all time info
	
	//print name
	printf("%s\n",direntp->d_name);
	


}

int list_dir(char * dir, int rec)
{
	DIR * dirp;
	char path[MAXPATH];
	struct dirent * direntp;
	struct stat st;
	
	/* Here you should open the directory indicated by the given path */
	/* check functions opendir */

	//opening the directory
	//source: https://pubs.opengroup.org/onlinepubs/009695399/functions/opendir.html 
	dirp = opendir(dir);
	if (dirp == NULL){
		printf ("Failed to open directory: %s\n", dir);
		return -1;
	
	}
	
	/* Then you should write a loop that reads the directory and prints the 
	   information about the included files */
	/* check function readdir and stat */
	
	//padding of the recursion
	for (int i = 1;i<rec;i++){
		printf("\t");
	
	}
	//priting the current directory 
	printf("Current dir: %s\n",dir);
	
	//padding for the recursion
	for (int i = 1;i<rec;i++){
		printf("\t");
	
	}
	printf("Permissions\tLinks\tOwner\tGroup\tFile size\tLast Change\tName\n");
	int count = 0; // jus tif there is empty dir so there wil be empty line
	//going through the directory
	//source how readdir works: https://pubs.opengroup.org/onlinepubs/7908799/xsh/readdir.html 
	while((direntp = readdir(dirp)) != NULL){
	
		
		//source: https://stackoverflow.com/questions/46694350/cant-compare-dirent-d-type-to-dt-dir
		//cheking if directory
		if (direntp->d_type == DT_DIR){
			
			//check if '.' current or '..' parent directory
			if (strcmp(direntp->d_name,".") == 0 || strcmp(direntp->d_name,"..") == 0){
				continue;
			}else{
				//if recursive to see subdirectories
				if (rec > 0){
					//copy the path of directory
					strcpy(path,dir);
					strcat(path,"/");
					strcat(path,direntp->d_name);
					
					//padding
					for (int i = 1;i<rec;i++){
							printf("\t");
						
					}
					
					//printing recursion level and path
					printf("Recursion: %d\n",rec);
					printf("\t<%s>\n",path);
					
					//recursion
					rec++;
					list_dir(path,rec);
					rec--;
				}else{ //if not recursive --> pritn directory values
					count++;
					strcpy(path,dir);
					strcat(path,"/");
					strcat(path,direntp->d_name);
					
					stat(path,&st);
					print_stat_info(st,direntp,rec);
					}
				
			}
		}else{
			count++;
			//source to get the rigth path when going into subdirectories:
			//https://stackoverflow.com/questions/60488124/stat-giving-wrong-information 
			//copy the path of directory
			strcpy(path,dir);
			strcat(path,"/");
			strcat(path,direntp->d_name);
			stat(path,&st); //add to stat
			
			//print values
			print_stat_info(st,direntp,rec);

			
		}
	
	}
	//if empty dir to help readability
	if (count == 0){
		printf("\n");
	}

	
	/* closing is already given here, but remember to do it yourself in the future :) */
	if (closedir(dirp) == -1) {
		perror(dir);
		return -1;
	}
	
	return 0;
}

int main(int argc, char * * argv)
{
	int i = 1, rec = 0;
	
	if (argc > 1) {
		if (strcmp(argv[i], "-r") == 0) {
			rec = 1;
			i++;
		}
	}
		
	while (i < argc) {
		if (list_dir(argv[i], rec) == -1) exit(1);
		i++;
	}
		
	return 0;
}

