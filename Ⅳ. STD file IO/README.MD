# Ⅳ standard file I/O

function(3)

* success -> return 0
* fail -> return EOF => [ERROR](#ERROR)

(except from [OPEN](#OPEN) and [setbuf](#BUFFER))

## function(3) : <stdio.h>

### BUFFER

#### void setbuf(FILE *fp, char* buf); 

##### int setvbuf(FILE *fp, char* buf, int mode, size_t size); 

set buffer of fppowe

#### int fflush(FILE *fp); 

flush a buffer of fp and print it immediately to fp

``` 
setbuf(stdout, buf); // buffer of stdout = buf -> by line (_IOLBF)
setbuf(stdout, NULL); // release buf (_IONBF)
setvbuf(fp, buf, size);
```

<hr/>

### OFFSET

``` 
fseek(fp, 0, SEEK_END);
fsize = ftell(fp);
```

<hr/>

### I/O

#### FILE* fopen(const char* pathname, mode_t mode); 

##### FILE* fdopen(int fd, mode_t mode); 

#### FILE* freopen(const char* pathname, mode_t mode, FILE* fp); 

#### FILE* fclose(FILE* fp); 

``` 
fp = fopen(fname, "w+"); // O_RDWR | O_CREAT | O_TRUNC
freopen(fname, "a+", fp); // O_RDWR | O_CREAT | O_APPEND
fclose(fp);
```

<hr/>

### ERROR

#### int ferror(FILE* fp); 

#### int feof(FILE* fp); 

<hr/><hr/>

### char I/O 

#### int fgetc(FILE *fp); 

(= getc) get character from fp

#### int getchar(); 

get character from stdin

#### int ungetc(int c, FILE *fp); 

push c back to stream

<hr/><hr/>

#### int fputc(int c, FILE *fp); 

(= putc) print c to fp

#### int putchar(int c); 

print c to stdout

``` 
while(!feof(fp)){

    fputc(c, stdout);

    if(ferror(fp)){
        clearerr(fp);
    }

    c = fgetc(fp);
}
```

<hr/>

### char* IO 

#### int fgets(char* buf, int n, FILE *fp); 

get at most n-1 char* from fp and stores them into buf until '\n'<br/>
(include \n)

#### int gets(char* buf); 

get char* from stdin and stores them into buf until '\n'<br/>
(exclude \n)

<hr/><hr/>

#### int fputs(const char* str, FILE *fp); 

print char* to fp until '\n'<br/>
(exclude \n)

#### int puts(const char* str); 

print char* to stdout until '\n'<br/>
(include \n)

``` 
while(!fgets(buf, BUF_SIZE, stdin) != NULL) // get \n
    if(fputs(buf, stdout) == EOF) // \n would be print 
        exit(1);
```

<hr/>

### binaray I/O

#### size_t fread(&emsp; &emsp; void* ptr, size_t, size_t nmemb, FILE* fp); 

#### size_t fwrite(const void* ptr, size_t, size_t nmemb, FILE* fp); 

```
fwrite(&mystruct, sizeof(struct mystruct), 1, fp); 
fread(&twostructs, sizeof(struct mystruct), 2, fp); // get 2*sizeof(mystruct) bytes and store the two items at ptr 
``` 
