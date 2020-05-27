# LINUX SYSTEM PROGRAMMING

each folder has its own README.md

open(fname, o_creat|o_truc|o_exec, 0644); 
close(fd); 
fd = creat(fname, 0644); 
lseek(1, (off_t)0, seek_cur); 

ftell(fp) == lseek(fd, 0, seek_end); 
read_size = read(fd, &int, buf_len); 
write(fd, ~~); 
fd2 = dup(fd1)
dup2(fd1, fd2); // but diff? fd2->fd1
stat(2modes)

* if((mode & S_IFMT) == S_IFREG)
* if(S_ISDIR)

umask(066); 
utime(time_buf); /actime, mtime
chmod(fd, 0644); 
chown(fd, uid, git); 
access(fp, F_ok); 
link(fname1, hardlinkname1); 
unlink(name); 
symlink(fname, symlinkname); 
remove(name); 
renameae(1, 2); 
readdir(dirname, 0666); 
closedir(fp)
mkdir(dirname)
rmdir(dirnmae)
chdir(dirname)
getcwd(buf); 
setbuf(stdin, null); 
setvbuf(fp, buf, size); 
fseek(fp, 0, seek_cur); 
ftell(fp); 
fopen(name, mode )
fdopen(fd, mode)
freopen(name, mode, fp)
fclose(fp)
ferrorfp
feoffp

getcwd()

getc(fp, c)
getchar(c);
ungetc(fp)
putc(fp, c)
putchar(fp)
fgets(fp, str)
gets(str)
fputs(fp, buf)
puts(buf)
exit(0)
_exit(0)
setjmp(env)
longjmp(env, 1)
fork()
