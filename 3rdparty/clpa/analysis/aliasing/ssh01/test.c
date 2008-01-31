typedef struct Key Key;
enum types {
 KEY_RSA1,
 KEY_RSA,
 KEY_DSA,
 KEY_UNSPEC
};
enum fp_type {
 SSH_FP_SHA1,
 SSH_FP_MD5
};
enum fp_rep {
 SSH_FP_HEX,
 SSH_FP_BUBBLEBABBLE
};

struct Key {
 int type;
 int flags;
  // RSA *rsa;
  // DSA *dsa;
};

typedef unsigned char u_char;
typedef unsigned int u_int, u_int32_t, size_t;
typedef unsigned long u_int64_t;
typedef struct Mac Mac;
typedef struct Comp Comp;
typedef struct Enc Enc;
typedef struct Newkeys Newkeys;

typedef struct Buffer {
 u_char *buf;
 u_int alloc;
 u_int offset;
 u_int end;
} Buffer;

typedef struct {
 int fd;
 Buffer identities;
 int howmany;
} AuthenticationConnection;

typedef struct Authctxt Authctxt;
typedef struct Authmethod Authmethod;
typedef struct identity Identity;
typedef struct idlist Idlist;

struct identity {
 struct { struct identity *tqe_next; struct identity **tqe_prev; } next;
 AuthenticationConnection *ac;
 Key *key;
 char *filename;
 int tried;
 int isprivate;
};

struct idlist { struct identity *tqh_first; struct identity **tqh_last; };

struct Authctxt {
 const char *server_user;
 const char *local_user;
 const char *host;
 const char *service;
 Authmethod *method;
 int success;
 char *authlist;

 Idlist keys;
 AuthenticationConnection *agent;

  // Sensitive *sensitive;

 int info_req_seen;

 void *methoddata;
};

struct Authmethod {
 char *name;
 int (*userauth)(Authctxt *authctxt);
 int *enabled;
 int *batch_flag;
};

typedef struct {
 int forward_agent;
 int forward_x11;
 int forward_x11_trusted;
 char *xauth_location;
 int gateway_ports;
 int use_privileged_port;
 int rhosts_rsa_authentication;

 int rsa_authentication;
 int pubkey_authentication;
 int hostbased_authentication;
 int challenge_response_authentication;

 int gss_authentication;
 int gss_deleg_creds;
 int password_authentication;

 int kbd_interactive_authentication;
 char *kbd_interactive_devices;
 int batch_mode;
 int check_host_ip;
 int strict_host_key_checking;
 int compression;
 int compression_level;

 int tcp_keep_alive;
  // LogLevel log_level;

 int port;
 int address_family;
 int connection_attempts;

 int connection_timeout;

 int number_of_password_prompts;

 int cipher;
 char *ciphers;
 char *macs;
 char *hostkeyalgorithms;
 int protocol;
 char *hostname;
 char *host_key_alias;
 char *proxy_command;
 char *user;
 int escape_char;

 char *system_hostfile;
 char *user_hostfile;
 char *system_hostfile2;
 char *user_hostfile2;
 char *preferred_authentications;
 char *bind_address;
 char *smartcard_device;
 int verify_host_key_dns;

 int num_identity_files;
 char *identity_files[100];
 Key *identity_keys[100];


 int num_local_forwards;
  // Forward local_forwards[100];


 int num_remote_forwards;
  // Forward remote_forwards[100];
 int clear_forwardings;

 int enable_ssh_keysign;
 int rekey_limit;
 int no_host_authentication_for_localhost;
 int identities_only;
 int server_alive_interval;
 int server_alive_count_max;

 int num_send_env;
 char *send_env[256];

 char *control_path;
 int control_master;
} Options;
Options options;

void* xmalloc(int);
void* memset(void*,int,int);
char* xstrdup(char*);

AuthenticationConnection *ssh_get_authentication_connection(void);
Key *ssh_get_first_identity(AuthenticationConnection *, char **, int);
Key *ssh_get_next_identity(AuthenticationConnection *, char **, int);

void init()
{
  options.identity_keys[0] = xmalloc(4);
}

void short_pubkey_prepare(Authctxt *authctxt)
{
 Identity *id;
 Idlist agent, files, *preferred;
 Key *key;
 AuthenticationConnection *ac;
 char *comment;
 int i, found;

   for (key = ssh_get_first_identity(ac, &comment, 2);
      key != ((void *)0);
      key = ssh_get_next_identity(ac, &comment, 2)) {
   found = 0;
   (id) = ((&files)->tqh_first);

   if (((id)->next.tqe_next) != ((void *)0))
     (id)->next.tqe_next->next.tqe_prev = (id)->next.tqe_prev;
   else
     (&files)->tqh_last = (id)->next.tqe_prev;
   *(id)->next.tqe_prev = (id)->next.tqe_next;

   (id)->next.tqe_next = ((void *)0);
   (id)->next.tqe_prev = (preferred)->tqh_last;
   *(preferred)->tqh_last = (id);
   (preferred)->tqh_last = &(id)->next.tqe_next;
   }
}

void debug2(const char*,void*,void*);
int key_equal(Key*,Key*);
void key_free(Key*);
void xfree(void*);

void pubkey_prepare(Authctxt *authctxt)
{
 Identity *id;
 Idlist agent, files, *preferred;
 Key *key;
 AuthenticationConnection *ac;
 char *comment;
 int i, found;

 do { (&agent)->tqh_first = ((void *)0); (&agent)->tqh_last = &(&agent)->tqh_first; } while (0);
 do { (&files)->tqh_first = ((void *)0); (&files)->tqh_last = &(&files)->tqh_first; } while (0);
 preferred = &authctxt->keys;
 do { (preferred)->tqh_first = ((void *)0); (preferred)->tqh_last = &(preferred)->tqh_first; } while (0);

 for (i = 0; i < options.num_identity_files; i++) {
  key = options.identity_keys[i];
  if (key && key->type == KEY_RSA1)
   continue;
  options.identity_keys[i] = ((void *)0);
  id = xmalloc(sizeof(*id));
  memset(id, 0, sizeof(*id));
  id->key = key;
  id->filename = xstrdup(options.identity_files[i]);
  do { (id)->next.tqe_next = ((void *)0); (id)->next.tqe_prev = (&files)->tqh_last; *(&files)->tqh_last = (id); (&files)->tqh_last = &(id)->next.tqe_next; } while (0);
 }

 if ((ac = ssh_get_authentication_connection())) {
  for (key = ssh_get_first_identity(ac, &comment, 2);
      key != ((void *)0);
      key = ssh_get_next_identity(ac, &comment, 2)) {
   found = 0;
   for((id) = ((&files)->tqh_first); (id) != ((void *)0); (id) = ((id)->next.tqe_next)) {

    if (key_equal(key, id->key)) {
     key_free(key);
     xfree(comment);
     do { if (((id)->next.tqe_next) != ((void *)0)) (id)->next.tqe_next->next.tqe_prev = (id)->next.tqe_prev; else (&files)->tqh_last = (id)->next.tqe_prev; *(id)->next.tqe_prev = (id)->next.tqe_next; } while (0);
     do { (id)->next.tqe_next = ((void *)0); (id)->next.tqe_prev = (preferred)->tqh_last; *(preferred)->tqh_last = (id); (preferred)->tqh_last = &(id)->next.tqe_next; } while (0);
     id->ac = ac;
     found = 1;
     break;
    }
   }
   if (!found && !options.identities_only) {
    id = xmalloc(sizeof(*id));
    memset(id, 0, sizeof(*id));
    id->key = key;
    id->filename = comment;
    id->ac = ac;
    do { (id)->next.tqe_next = ((void *)0); (id)->next.tqe_prev = (&agent)->tqh_last; *(&agent)->tqh_last = (id); (&agent)->tqh_last = &(id)->next.tqe_next; } while (0);
   }
  }

  for (id = ((&agent)->tqh_first); id; id = ((&agent)->tqh_first)) {
   do {
     if (((id)->next.tqe_next) != ((void *)0))
       (id)->next.tqe_next->next.tqe_prev = (id)->next.tqe_prev;
     else
       (&agent)->tqh_last = (id)->next.tqe_prev;
     *(id)->next.tqe_prev = (id)->next.tqe_next;
   } while (0);
   do {
     (id)->next.tqe_next = ((void *)0);
     (id)->next.tqe_prev = (preferred)->tqh_last;
     *(preferred)->tqh_last = (id);
     (preferred)->tqh_last = &(id)->next.tqe_next;
   } while (0);
  }
  authctxt->agent = ac;
 }

 for (id = ((&files)->tqh_first); id; id = ((&files)->tqh_first)) {
  do { if (((id)->next.tqe_next) != ((void *)0)) (id)->next.tqe_next->next.tqe_prev = (id)->next.tqe_prev; else (&files)->tqh_last = (id)->next.tqe_prev; *(id)->next.tqe_prev = (id)->next.tqe_next; } while (0);
  do { (id)->next.tqe_next = ((void *)0); (id)->next.tqe_prev = (preferred)->tqh_last; *(preferred)->tqh_last = (id); (preferred)->tqh_last = &(id)->next.tqe_next; } while (0);
 }
 for((id) = ((preferred)->tqh_first); (id) != ((void *)0); (id) = ((id)->next.tqe_next)) {
  debug2("key: %s (%p)", id->filename, id->key);
 }
}
