/* Build interceptor
 * This file contains a library of functions that is to be loaded using 
 * LD_PRELOAD. The code overrides calls to exec() in order to intercept
 * executions matching the specifications given in the interceptor configuration
 * file.
 * 
 * Author: Peter Hawkins <hawkinsp@cs.stanford.edu>
 */

#define _GNU_SOURCE 1

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <assert.h>
#include <dlfcn.h>
#include <unistd.h>
#include <regex.h>

#define MAX_ENV_STRINGS 1024
#define PATH_MAX 1024
#define BUFFER_SIZE 2048
#define MAX_MAPPINGS 1024

/* NB. We need to be careful in this file to mark non-exported symbols as
 * static to avoid pollution of the application's namespace. */

static const int debug = 0;

/* Environment variables we should inspect */

/* Where do we find the configuration file? */
static const char *BI_CONFIG_FILE_VAR = "BUILD_INTERCEPTOR_CONFIG";

/* Were we invoked by the build interceptor library (me!) or by something else?
 */
static const char *BI_FROMLIBRARY_VAR = "BUILD_INTERCEPTOR_FROM_LIBRARY";


/* Pointers to the libc versions of the functions we are overriding. */
static int (*real_execve)(const char *, char *const [], char * const []) = NULL;

/* Path name of the build interceptor library (me!) as determined by
 * the configuration file*/
static char config_path[PATH_MAX];
static char lib_path[PATH_MAX];
static char scripts_path[PATH_MAX];

/* Environment variable strings */

/* The original configuration environment string */
static char config_evar[PATH_MAX];
static char fromlibrary_evar[PATH_MAX];

/* The ld_preload given to the victim */
static char ld_preload_var[BUFFER_SIZE];

typedef struct {
    regex_t src;
    char *dst;
} mapping_t;

static mapping_t mappings[MAX_MAPPINGS];
static int num_mappings = 0;


/* Print an error message and abort execution */
static void
die(const char *fmt, ...)
{
    va_list args;

    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    abort();
}

/* Set *fptr to the address of libc symbol name, aborting the program if
 * the symbol cannot be found */
static void 
load_symbol(void **fptr, const char *name)
{
    assert(fptr != NULL && name != NULL);
    *fptr = dlsym(RTLD_NEXT, name);
    if (*fptr == NULL) {
        die("libintercept: Couldn't locate symbol \"%s\" (%s).\n",
            name, dlerror());
    }
}

/* Load the file name mappings */
static void
load_config(const char *filename)
{
    FILE *f;
    char buffer[BUFFER_SIZE];
    char buffer2[BUFFER_SIZE];
    char *p, *src, *dst;
    int section = -1;
    const int PATHS_SECTION = 0;
    const int REDIRS_SECTION = 1;
    int len, ret;
    struct stat s;

    lib_path[0] = scripts_path[0] = 0;

    f = fopen(filename, "r");
    if (f == NULL)
        die("libintercept: Could not open configuration file '%s': %s\n", 
                filename, strerror(errno));
        
    while (1) {
        if (fgets(buffer, BUFFER_SIZE, f) == NULL) {
            if (feof(f)) break;
            die("libintercept: Error reading from mapping file: %s\n",
                strerror(errno));
        }

        /* Strip leading spaces */
        src = &buffer[0];
        while (*src && isspace(*src)) src++;

        /* Skip comments */
        if (src[0] == '#') continue;

        /* Strip any trailing spaces or newlines */
        p = src + strlen(src) - 1;
        while (p >= src && isspace(*p)) p--;
        *(p+1) = '\0';

        /* Skip blank lines */
        if (src[0] == 0) continue;
        
        len = strlen(src);

        /* Parse section headers */
        if (!strcasecmp("[paths]", src)) {
            section = PATHS_SECTION; 
        } else if (!strcasecmp("[redirections]", src)) {
            section = REDIRS_SECTION; 
        } else {
            dst = p = strrchr(src, '=');
            if (p == NULL)
                die("libintercept: Missing '=' separator in config file entry."
                        "\n");

            /* Strip trailing and leading whitespace */
            while (*p == ' ' && p > src) p--;
            *p = '\0';
            dst++;
            while (*dst == ' ') dst++;

            if (section == REDIRS_SECTION) {
                if (debug) 
                    fprintf(stderr, "intercept: regex %s -> %s\n", src, dst);

                ret = regcomp(&mappings[num_mappings].src, src, REG_EXTENDED);
                if (ret != 0) 
                    die("Invalid regular expression in mapping: %s", src);

                /* NB. We are lazy and never free the mapping regular 
                 * expression structures. They will be freed for us by the
                 * OS on exit/exec. */

                if (!strchr(dst, '/')) {
                    snprintf(buffer2, BUFFER_SIZE, "%s%s", scripts_path, dst);
                    buffer2[BUFFER_SIZE - 1] = 0;
                    dst = buffer2;
                }
                mappings[num_mappings].dst = canonicalize_file_name(dst);
                if (mappings[num_mappings].dst == NULL)
                    die("libintercept: %s does not exist\n", dst);
            
                num_mappings++;
            } else if (section == PATHS_SECTION) {
                if (!strcmp(src, "intercept_scripts")) {
                    strncpy(scripts_path, dst, PATH_MAX);
                    scripts_path[PATH_MAX - 2] = 0;
                    len = strlen(scripts_path);
                    if (len > 0 && scripts_path[len - 1] != '/') {
                        scripts_path[len++] = '/';
                        scripts_path[len] = 0;
                    }
                } else if (!strcmp(src, "intercept_library")) {
                    strncpy(lib_path, dst, PATH_MAX);
                    lib_path[PATH_MAX - 1] = 0;
                }
            } else {
                die("libintercept: Expected section header in config file.\n");
            }
        }
    }
    fclose(f);
    
    /* Check we have valid library and scripts paths */
    ret = stat(lib_path, &s);
    if (ret < 0 || !S_ISREG(s.st_mode)) 
            die("Invalid or missing library path in configuration file\n");

    ret = stat(scripts_path, &s);
    if (ret < 0 || !S_ISDIR(s.st_mode)) 
            die("Invalid or missing script path in configuration file\n");
}


/* XXX: Something weird happens when we are linked against bash -- we seem
 * to get another copy of unsetenv from somewhere which doesn't work.
 * This one is copied out of the C library
 */
extern char ** __environ;
static int 
my_unsetenv(const char *name)
{
  size_t len;
  char **ep;

  if (name == NULL || *name == '\0' || strchr (name, '=') != NULL)
    {
      errno = (EINVAL);
      return -1;
    }

  len = strlen (name);

  ep = __environ;
  while (*ep != NULL)
    if (!strncmp (*ep, name, len) && (*ep)[len] == '=')
      {
    /* Found it.  Remove this pointer by moving later ones back.  */
    char **dp = ep;

    do
      dp[0] = dp[1];
    while (*dp++);
    /* Continue the loop in case NAME appears again.  */
      }
    else
      ++ep;

  return 0;
}

/* Library initialization function. Called automatically when the library
 * is loaded */
static void __attribute__((constructor))
initialize(void)
{
    char *config_filename;
    char *ld_preload, *p;

    /* Find the addresses of the real copies of the symbols we are faking */
    load_symbol((void **)&real_execve, "execve");

    config_filename = getenv(BI_CONFIG_FILE_VAR);
    if (!config_filename)
            die("Missing configuration file environment variable %s\n", 
                    BI_CONFIG_FILE_VAR);
    strncpy(config_path, config_filename, sizeof(config_path));
    config_path[sizeof(config_path)-1] = 0;
    load_config(config_filename);

    /* Hide our environment variables from the victim */
    my_unsetenv(BI_CONFIG_FILE_VAR);
    my_unsetenv(BI_FROMLIBRARY_VAR);

    snprintf(config_evar, sizeof(config_evar), "%s=%s", BI_CONFIG_FILE_VAR, 
            config_filename);
    config_evar[sizeof(config_evar) - 1] = 0;
    snprintf(fromlibrary_evar, sizeof(fromlibrary_evar), "%s=1", 
            BI_FROMLIBRARY_VAR);
    fromlibrary_evar[sizeof(fromlibrary_evar) - 1] = 0;

    ld_preload = getenv("LD_PRELOAD");
    if (ld_preload) {
        /* Strip the first element of the LD_PRELOAD list, assuming that
         * it must be us. */
        p = strchr(ld_preload, ' ');
        if (p != NULL) {
            strncpy(ld_preload_var, p+1, 
                sizeof(ld_preload_var));
            ld_preload_var[sizeof(ld_preload_var) - 1] = 0;
            setenv("LD_PRELOAD", ld_preload_var, 1);
        } else {
            my_unsetenv("LD_PRELOAD");
        }
    }
}

/* Map an absolute filename via the mapping table. Returns either the 
 * original string or a pointer into the mapping table (which should not be
 * freed). */
static const char * 
map_file(const char *oldfile)
{
    int i;
    const char *ret;
    char *canon;

    canon = canonicalize_file_name(oldfile);
    /* Use the old filename if canonicalization fails */
    if (!canon) canon = strdup(oldfile);
    
    if (debug) 
        fprintf(stderr, "intercept: mapping input %s\n", canon);
    ret = oldfile;
    for (i = 0; i < num_mappings; i++) {
        if (regexec(&mappings[i].src, canon, 0, NULL, 0) == 0) {
            ret = mappings[i].dst;
            break;
        }
    }
    free((void *)canon);
    return ret;
}

/* --------------------------------------------------------------------------*/
/* Intercepted symbols */
int 
execve(const char *filename, char *const argv[], char *const env[])
{
    char *newenv[MAX_ENV_STRINGS];
    char *newargs[MAX_ENV_STRINGS];
    const char *ld_preload;
    char buffer[BUFFER_SIZE];
    const char *new_file;
    char * const *oldenv = env;
    char * const *a;
    int i, mapped, j;
    int ret;

    buffer[0] = 0;
    new_file = map_file(filename);
    /* If we're diverting, don't trace the diverted file */
    mapped = strcmp(new_file, filename);
    if (debug)
        fprintf(stderr, "intercept: running %s instead of %s\n", new_file, 
                filename);
    
    i = mapped ? 0 : 1;
    newenv[i++] = config_evar;
    newenv[i++] = fromlibrary_evar;
    ld_preload = NULL;
    while (*oldenv && i < MAX_ENV_STRINGS - 1) {
        if (!mapped && !strncmp("LD_PRELOAD=", *oldenv, 11)) {
            ld_preload = strchr(*oldenv, '=') + 1;
        } else {
            newenv[i] = *oldenv;
            i++;
        }
        oldenv++;
    }

    j = 0;
    if (mapped) {
        newargs[j++] = (char *)new_file;
    } else {
        /* We need to make sure that we appear at the front of LD_PRELOAD */
        snprintf(buffer, BUFFER_SIZE, "LD_PRELOAD=%s%s%s", lib_path,
                (ld_preload ? " " : ""), (ld_preload ? ld_preload : ""));
        buffer[BUFFER_SIZE - 1] = 0;

        newenv[0] = buffer;
    }
    newenv[i] = NULL;

    a = argv;
    while (*a && j < MAX_ENV_STRINGS - 1) {
        newargs[j++] = *a;
        a++;
    }
    newargs[j] = NULL;

    ret = real_execve(new_file, newargs, newenv);
    return ret;
}

int 
execv(const char *filename, char *const argv[])
{
    return execve(filename, argv, environ);
}

int 
execvp(const char *filename, char *const argv[])
{
    char newfile[PATH_MAX];
    int len;
    const char *path;
    const char *next;

    /* If the specified filename contains a slash character, execvp does
     * not seach the PATH. */
    if (strchr(filename, '/') != NULL)
        return execve(filename, argv, environ);


    /* Seach the directories specified in the PATH environment for the
     * file filename. We have to do this ourselves since we do our mapping
     * on the absolute filename. */

    /* Fetch the PATH environment variable, using the libc default if
     * it doesn't exist */
    path = getenv("PATH");
    if (path == NULL)
        path = ":/bin:/usr/bin";
         
    while (path[0] != 0) {
        next = strchr(path, ':');
        if (next == NULL)
            next = path + strlen(path);

        len = (int)(next - path);
        if (len > PATH_MAX)
            len = PATH_MAX;

        if (len == 0) {
            /* Empty path segment means current working directory */
            getcwd(newfile, PATH_MAX);
            len = strlen(newfile);
        } else {
            memcpy(newfile, path, len);
        }
        /* Add a trailing slash, if necessary */
        if (len > 0 && newfile[len - 1] != '/')
            newfile[len++] = '/';
        newfile[len] = 0;

        strncat(newfile, filename, PATH_MAX - len - 1);

        /* Try to execute this file. If this works, execve will not
         * return */
        execve(newfile, argv, environ);
        
        path = next;
        if (*path == ':') path++;
    }

    errno = ENOENT;
    return -1;

}

int
execl(const char *filename, const char *arg0, ...)
{
    va_list arg_list;
    char *args[MAX_ENV_STRINGS], *a;
    int i;

    va_start(arg_list, arg0);
    
    args[0] = (char *)arg0;
    a = va_arg(arg_list, char *const);
    i = 1;
    while (a != NULL && i < MAX_ENV_STRINGS) {
        args[i] = a;
        i++;
        a = va_arg(arg_list, char *const);
    }
    args[i] = NULL;

    va_end(arg_list);
    return execve(filename, args, environ);
}

int
execle(const char *filename, const char *arg0, ...)
{
    va_list arg_list;
    char *args[MAX_ENV_STRINGS], *a;
    char * const * env;
    int i;

    va_start(arg_list, arg0);
    args[0] = (char *)arg0;
    a = va_arg(arg_list, char *const);
    i = 1;
    while (a != NULL && i < MAX_ENV_STRINGS) {
        args[i] = a;
        i++;
        a = va_arg(arg_list, char *const);
    }
    args[i] = NULL;
    env = va_arg(arg_list, char * const *);

    va_end(arg_list);
    return execve(filename, args, env);
}

int
execlp(const char *filename, const char *arg0, ...)
{
    va_list arg_list;
    char *args[MAX_ENV_STRINGS], *a;
    int i;

    va_start(arg_list, arg0);
    args[0] = (char *)arg0;
    a = va_arg(arg_list, char *const);
    i = 1;
    while (a != NULL && i < MAX_ENV_STRINGS) {
        args[i] = a;
        i++;
        a = va_arg(arg_list, char *const);
    }
    args[i] = NULL;

    va_end(arg_list);
    return execvp(filename, args);
}

