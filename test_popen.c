#if  0
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>

   int main(int argc, char *argv[])
   {
       if (argc != 2) {
           printf("usage: %s <dir>\n", argv[0]);
           exit(0);
       }

       char dirname[NAME_MAX];
       strncpy(dirname, argv[1], sizeof(dirname));
       if (dirname[strlen(dirname) - 1] == '/')
           dirname[strlen(dirname) - 1] = '\0';

       char cmd[1024];
       snprintf(cmd, sizeof(cmd), "/bin/tar -cvf %s.tar %s", dirname, dirname);
       FILE *exec = popen(cmd, "r");
       if (exec == NULL) {
           perror("popen");
           exit(1);
       }
       char buf[1024];
       while (fgets(buf, sizeof(buf), exec) != NULL)
           printf("%s\n", buf);
       int ret = fclose(exec);
       printf("ret is %d\n", ret);

       return 0;
   }

#else
   #include <stdlib.h>
   #include <unistd.h>
   #include <sys/types.h>
   #include <stdio.h>
   #include <limits.h>
   #include <string.h>
#include <errno.h>

   int main(int argc, char *argv[])
   {
       if (argc != 2) {
           printf("usage: %s <dir>\n", argv[0]);
           exit(0);
       }

       char dirname[NAME_MAX];
       strncpy(dirname, argv[1], sizeof(dirname));
       if (dirname[strlen(dirname) - 1] == '/')
           dirname[strlen(dirname) - 1] = '\0';

       char cmd[1024];
       snprintf(cmd, sizeof(cmd), "/bin/tar -cvf %s.tar %s", dirname, dirname);
       FILE *exec = popen(cmd, "r");
       if (exec == NULL) {
           perror("popen");
           exit(1);
       }

	   int ret = pclose(exec);
       //int ret = fclose(exec);
       printf("ret is %d %s\n", ret, strerror(ret));

       return 0;
   }
#endif
