#define _GNU_SOURCE
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>


void listdir(const char *name, int indent)
{
    DIR *dir;
    struct dirent *entry;
	struct stat st;
    if (!(dir = opendir(name)))
        return;

    while ((entry = readdir(dir)) != NULL) {
    	
    	
        if (entry->d_type == DT_DIR) {
            char path[1024];
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;
            snprintf(path, sizeof(path), "%s/%s", name, entry->d_name);
            printf("%*s[%s]\n", indent, "", entry->d_name);
            listdir(path, indent + 2);
        } else {
        	stat(entry->d_name,&st);
        	printf((S_ISDIR(st.st_mode))? "d":"-" );
            	printf("%*s- %s\n", indent, "", entry->d_name);
        }
    }
    closedir(dir);
}

int main(void) {
    listdir(".", 0);
    return 0;
}
