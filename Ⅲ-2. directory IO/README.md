# Ⅲ-2. directory I/O

## key

### DIR

### dirent

d_name, d_ino

## function(3)

##### <sys/types.h>

##### <dirent.h>

### DIR* opendir(const char* name); 

### struct dirent* readdir(DIR *dp); 

### int closedir(DIR *dp); 

``` 
DIR* dirp = opendir(dname);
struct dirent *dentry = readdir(dp);
// dentry->d_name == dname
closedir(dp);
```

``` 
while((dentry = readdir(dirp)) != NULL){
	if(dentry->d_ino == 0)
		continue;
	memcpy(filename, dentry->d_name, DIRECTORY_SIZE);
```

<hr/>

## function(2)

##### <sys/stat.h>

##### <sys/types.h>

### int mkdir(const char* pathname, mode_t mode); 

<hr/>

##### <unistd.h>

### int rmdir(const char* pathname); 

### int chdir(const char* pathname); 

### char* getcwd(char* buf, size_t size); 

``` 
chdir("/etc"); // change directory
getcwd(cwd, PATH_MAX); // cwd == "/etc"
```
