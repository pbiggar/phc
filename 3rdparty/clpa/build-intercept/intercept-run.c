/* Wrapper script that lets the interception library capture an execution */

#include <stdio.h>
#include <unistd.h>

int 
main(int argc, char *argv[])
{
    char *nargv[argc + 1];
    int i;

    if (argc < 2) {
        fprintf(stderr, "intercept-run: Expected a program to run.\n");
        return -1;
    }

    for (i = 1; i < argc; i++) {
        nargv[i - 1] = argv[i];
    }
    nargv[i - 1] = NULL;

    execvp(nargv[0], nargv);
    perror("execvp");
    return -1;
}
