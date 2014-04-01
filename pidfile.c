#include <stdio.h>

#include <stdlib.h>

#include <unistd.h>

#include <string.h>

#include <fcntl.h>



static char *saved_pidfile;



static void pidfile_delete(void)

{

        if (saved_pidfile) unlink(saved_pidfile);

}



int pidfile_acquire(const char *pidfile)

{

        int pid_fd;

        if (!pidfile) return -1;



       pid_fd = open(pidfile, O_CREAT | O_WRONLY, 0644);

        if (pid_fd < 0) {

                printf("Unable to open pidfile %s: %m\n", pidfile);

        } else {

                lockf(pid_fd, F_LOCK, 0);

                if (!saved_pidfile)

                       atexit(pidfile_delete);

                saved_pidfile = (char *) pidfile;

        }

        return pid_fd;

}



void pidfile_write_release(int pid_fd)

{

       FILE *out;


       if (pid_fd < 0) return;



       if ((out = fdopen(pid_fd, "w")) != NULL) {

                fprintf(out, "%d\n", getpid());

                fclose(out);

        }

        lockf(pid_fd, F_UNLCK, 0);

        close(pid_fd);

}



void create_pidfile(const char *filename)

{

        int fd;

        fd = pidfile_acquire(filename);

        pidfile_write_release(fd);

}



int main(int argc, char *argv[])

{

        create_pidfile(argv[1]?argv[1]:"/var/run/test.pid");

        return 0;

}
