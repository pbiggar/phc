/*
 * Authors:
 *   Ted Kremenek   <kremenek@cs.stanford.edu>
 *   Peter Hawkins  <hawkinsp@cs.stanford.edu>
 *
 * Copyright (c) 2004-2006,
 *   The Board of Trustees of The Leland Stanford Junior University
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * 3. The names of the contributors may not be used to endorse or promote
 * products derived from this software without specific prior written
 * permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <fcntl.h>
#include <caml/mlvalues.h>
#include <caml/alloc.h>
#include <caml/memory.h>
#include <caml/fail.h>
#include <caml/callback.h>

/* Berkeley DB C interface */

#include <db.h>

#ifndef DBVER
#define DBVER (DB_VERSION_MAJOR * 10 + DB_VERSION_MINOR)
#endif

#if (DBVER >= 43)
#else
#include <errno.h>
#endif

/* Macros */

#define DBENV_val(v) (*((DB_ENV **)&Field(v,0)))

#define BDB_val( v ) *((DB **) &Field(v,0))

#define BDB_buf_key( v ) *((void **) &Field(v,1))
#define BDB_buf_key_ptr( v ) ((void **) &Field(v,1))
#define BDB_buf_key_size_ptr( v ) ((size_t *) &Field(v,2))

#define BDB_buf_data( v ) *((void **) &Field(v,3))
#define BDB_buf_data_ptr( v ) ((void **) &Field(v,3))
#define BDB_buf_data_size_ptr( v ) ((size_t *) &Field(v,4))

#define BDB_active_cursor( v ) *((DBC **) &Field(v,5))
#define BDB_active_cursor_ptr( v ) ((DBC **)&Field(v,5))

/* Exception code */

static void raise_bdb_exception( char * errmsg ) Noreturn;

static void raise_bdb_exception( char * errmsg )
{
   static value * bdb_exn = NULL;
   if( bdb_exn == NULL )
      bdb_exn = caml_named_value("dbmbderror");
   raise_with_string(*bdb_exn, errmsg );
}

static void raise_bdb_exception_with_code( char * errmsg, int code )
{
  printf("DBM ERROR: %d, VERSION %d\n",code,DBVER);
  raise_bdb_exception(errmsg);
}

/* Create a database environment handle */
value caml_dbenv_create(value unit) 
{
    int ret;
    CAMLparam1(unit); 
    CAMLlocal1(v);
    DB_ENV *dbenv = NULL;

    if ((ret = db_env_create(&dbenv, 0)) != 0)
      raise_bdb_exception_with_code("Cannot create bdb environment handle",
            ret); 

    v = caml_alloc_small(1, Abstract_tag);
    DBENV_val(v) = dbenv;

    CAMLreturn(v);
}

/* Open a database environment */
value caml_dbenv_open(value vdbenv, value vhome, value vmode)
{
    CAMLparam3(vdbenv, vhome, vmode);
    char *home = String_val(vhome);
    int mode = Int_val(vmode);
    int ret;
    value v;
    DB_ENV *dbenv = DBENV_val(vdbenv);

    if (dbenv == NULL) 
      raise_bdb_exception("Database environment handle has been closed");

    if ((ret = dbenv->open(dbenv, home, DB_CREATE | DB_INIT_MPOOL | DB_PRIVATE,
                           0)) != 0)
      raise_bdb_exception_with_code("Could not open bdb environment ", ret);

    CAMLreturn(Val_unit);
}

/* Set the cache size */
value caml_dbenv_set_cachesize(value venv, value vgb, value vb)
{
    CAMLparam3(venv, vgb, vb);
    DB_ENV *dbenv = DBENV_val(venv);
    int gbytes = Int_val(vgb), bytes = Int_val(vb);
    int ret;

    if (dbenv == NULL) 
      raise_bdb_exception("Database environment handle has been closed");

    if ((ret = dbenv->set_cachesize(dbenv, gbytes, bytes, 1)) != 0)
      raise_bdb_exception_with_code("Could not set dbenv cache size", ret);

    CAMLreturn(Val_unit);
}

value caml_dbenv_close(value venv) {
    CAMLparam1(venv);
    DB_ENV *dbenv = DBENV_val(venv);
    int ret;

    if (dbenv == NULL) 
      raise_bdb_exception("Database environment handle has been closed");
    
    if ((ret = dbenv->close(dbenv, 0)) != 0) 
      raise_bdb_exception_with_code("Error closing DB environment", ret);

    DBENV_val(venv) = NULL;
    CAMLreturn(Val_unit);
}

value caml_dbenv_memp_stat_print(value venv) {
    CAMLparam1(venv);
    DB_ENV *dbenv = DBENV_val(venv);
    FILE *mf;

#if (DBVER >= 43)
    if (dbenv == NULL) 
      raise_bdb_exception("Database environment handle has been closed");
    
    dbenv->get_msgfile(dbenv, &mf);
    dbenv->set_msgfile(dbenv, stdout);
    dbenv->memp_stat_print(dbenv, 0); // print main overall and per-.db stats
    dbenv->set_msgfile(dbenv, mf);
#endif

    CAMLreturn(Val_unit);
}

/* Fetching keys and data requires memory.  This function is
   responsible for allocating memory for such uses */

static size_t bdb_allocate_buffer( void ** buf_ptr, size_t * size_ptr, size_t desired )
{
   void * buf = *buf_ptr;
   size_t size = *size_ptr;

   if( desired < size ) return size;

   desired *= 2 ;

   if( buf == NULL )
   {
      size = ( desired > 2048 ) ? desired : 2048;
      buf = malloc( size );
   }
   else {
      size = desired;
      buf = realloc( buf, size );
   }

   if( !buf ) raise_bdb_exception("cannot allocate db buffer");

   /* Update buffer and size */

   *buf_ptr = buf;
   *size_ptr = size;

   return size;
}

/* Code to allocate an O'Caml object to store the pointer */

static value alloc_bdb( DB * db )
{
   value res = alloc_small( 6, Abstract_tag );

   BDB_val( res ) = db; /* Set DB handle */

   BDB_buf_key( res ) = NULL; /* memory will be allocated lazily */
   *BDB_buf_key_size_ptr(res) = 0;
 
   BDB_buf_data( res ) = NULL; /* memory will be allocated lazily */
   *BDB_buf_data_size_ptr(res) = 0;

   BDB_active_cursor( res ) = NULL;

   return res;
}

static void free_bdb( value vdb )
{
   BDB_val( vdb ) = NULL;

   if( BDB_buf_key(vdb) )
   {
      free( BDB_buf_key(vdb) );
      BDB_buf_key(vdb) = NULL;
   }

   if( BDB_buf_data(vdb) )
   {
      free( BDB_buf_data(vdb) );
      BDB_buf_data(vdb) = NULL;
   }
}


/* DBP extraction */

DB * extract_dbp( value vdb )
{
   if( BDB_val( vdb ) == NULL ) raise_bdb_exception("BDB has been closed");
   else return BDB_val(vdb);
}

/* 
   We are mapping these types:

   type Dbm.open_flag =
      Dbm_rdonly | Dbm_wronly | Dbm_rdwr | Dbm_create
*/

static int bdb_open_flags[] = {
   DB_RDONLY,			/* Dbm_rdonly */
   0,				/* Dbm_wronly == NOP */
   0,				/* Dbm_rdwr == NOP */
   DB_CREATE,			/* Dbm_create */

   /* extended flags */
   DB_AUTO_COMMIT,		/* Dbm_auto_commit */
   DB_DIRTY_READ,		/* Dbm_dirty_read */
   DB_EXCL,			/* Dbm_excl       */
   DB_NOMMAP,			/* Dbm_nommap     */
   DB_THREAD,			/* Dbm_thread     */
   DB_TRUNCATE,			/* Dbm_truncate   */
};

/* open : string -> Sys.open_flag list -> int -> t */

value caml_bdb_open(value venv, value vfile, value vflags, value vmode ) 
{
   CAMLparam4(venv, vfile, vflags, vmode);
   CAMLlocal1(vdbenv);
   char * file = String_val( vfile );
   unsigned int flags = caml_convert_flag_list( vflags, bdb_open_flags );
   int mode = Int_val( vmode );
   
   DB *dbp;           /* DB structure handle */
   DB_ENV *dbenv;     /* Database environment pointer */
   unsigned int ret;  /* function return value */ 

   dbenv = NULL;

   if (Int_val(venv) != 0) {
       dbenv = DBENV_val(Field(venv, 0));
   }

   /* Initialize the database handle */

   ret = db_create( &dbp, dbenv, 0 );
   if ( ret != 0) { raise_bdb_exception_with_code("cannot create db handler",ret); }

   /* open the database */ 

   ret = dbp->open(dbp,        /* DB structure pointer */        
		   NULL,       /* Transaction pointer */
		   file,       /* On-disk file that holds the database. */
		   NULL,       /* Optional logical database name */
		   DB_BTREE,   /* Database access method */
		   flags,      /* Open flags */
		   mode );     /* file mode */

   if( ret != 0 ) { 
      dbp->close( dbp, 0 ); /* Free resource */
      raise_bdb_exception_with_code("cannot open bdb file",ret); 
   }
   
   CAMLreturn(alloc_bdb( dbp ));
}

/* open_advanced : string -> Sys.open_flag list -> int -> t */

#if 0
static unsigned int bdb_specific_open_flags[] = {
   DB_AUTO_COMMIT,
   DB_CREATE,
   DB_DIRTY_READ,
   DB_EXCL,
   DB_NOMMAP,
   DB_RDONLY,
   DB_THREAD,
   DB_TRUNCATE
};
#endif

static unsigned int bdb_type[] = {
   DB_BTREE,
   DB_HASH,
   DB_UNKNOWN
};

value caml_bdb_open_advanced( value vdatabase, value vfile, value vtype,
				 value vflags, value vmode ) /* ML */
{
   char * database = String_val( vdatabase );
   char * file = String_val( vfile );
   //unsigned int flags = caml_convert_flag_list( vflags, bdb_specific_open_flags );
   unsigned int flags = caml_convert_flag_list( vflags, bdb_open_flags );
   int mode = Int_val( vmode );
   unsigned int db_type = bdb_type[ Int_val( vtype ) ];
   
   /* Get the dabase handler */

   DB *dbp;           /* DB structure handle */
   unsigned int ret;  /* function return value */ 

   /* Initialize the structure. This database is not opened in an
    * environment, so the environment pointer is NULL. */

   ret = db_create( &dbp, NULL, 0 );
   if ( ret != 0) { raise_bdb_exception_with_code("cannot create db handler",ret); }

   /* open the database */ 

   ret = dbp->open(dbp,        /* DB structure pointer */        
		   NULL,       /* Transaction pointer */
		   file,       /* On-disk file that holds the database. */
		   database,   /* Optional logical database name */
		   db_type,   /* Database access method */
		   flags,      /* Open flags */
		   mode );     /* file mode */

   if( ret != 0 ) { 
      dbp->close( dbp, 0 ); /* Free resource */
      raise_bdb_exception_with_code("cannot open bdb file",ret); 
   }

   return alloc_bdb( dbp );
}

/* close: t -> unit */

value caml_bdb_close( value vdb ) /* ML */
{
   DB * dbp = extract_dbp( vdb );
   if( dbp != NULL )
   {
      DBC * cursorp = BDB_active_cursor( vdb );
      if( cursorp )
      {
	 cursorp->c_close( cursorp );
	 BDB_active_cursor( vdb ) = NULL;
      }
      dbp->close( dbp, 0 );
      free_bdb( vdb );
   }
   return Val_unit;
}

/* sync : t -> unit */
value caml_bdb_sync( value vdb )
{
    DB *dbp = extract_dbp(vdb);
    if (dbp)
	dbp->sync(dbp, 0);
    return Val_unit;
}

/* fetch: t -> string -> string */
value caml_bdb_fetch( value vdb, value vkey ) /* ML */
{
   DBT key, data;

   /* zero out DBTs before using them */

   memset( &key, 0, sizeof( key ) );
   memset( &data, 0, sizeof( data ) );

   /* retrieve the key */

   key.data = String_val( vkey );
   key.size = string_length( vkey );

   /* set the data buffer */

   data.data = BDB_buf_data( vdb );
   data.ulen = *(BDB_buf_data_size_ptr( vdb ));
   data.flags = DB_DBT_USERMEM;

   /* Get the handle */

   DB * dbp = extract_dbp( vdb );

   /* Now attempt the retrieve the data.  If the buffer is
      too small we will increase the buffer size */

   int result = dbp->get( dbp, NULL, &key, &data, 0 );

#if (DBVER >= 43)
   if( result == DB_BUFFER_SMALL )
#else
   if (result == ENOMEM)
#endif
   {
      /* Enlarge our data buffer to accomodate the amount requested by
	 Berkeley DB */

      data.ulen = bdb_allocate_buffer( BDB_buf_data_ptr(vdb), 
				       BDB_buf_data_size_ptr(vdb),
				       data.size );

      /* Don't forget to set the new buffer */

      data.data = BDB_buf_data( vdb );

      /* try again */

      result = dbp->get( dbp, NULL, &key, &data, 0 );
   }

   switch( result )
   {
      case 0: /* SUCCESS!!! */
      {
	 value return_res = alloc_string( data.size );
	 memmove ( String_val (return_res), data.data, data.size );
	 return return_res;
      }
      case DB_NOTFOUND: /* No such item.  Raise an exception. */
	 raise_not_found();

	 /* The rest of these shouldn't happen because in this simple
	    interface there shouldn't be locks, etc. */

      case DB_LOCK_DEADLOCK:
	 raise_bdb_exception("DB_LOCK_DEADLOCK: A transactional database environment operation was selected to resolve a deadlock.");

      case DB_LOCK_NOTGRANTED:
	 raise_bdb_exception("DB_LOCK_NOTGRANTED: A Berkeley DB Concurrent Data Store database environment configured for lock timeouts was unable to grant a lock in the allowed time.");

      case DB_REP_HANDLE_DEAD:
	 raise_bdb_exception("DB_REP_HANDLE_DEAD: The database handle has been invalidated because a replication election unrolled a committed transaction.");

      case DB_SECONDARY_BAD:
	 raise_bdb_exception("A secondary index references a nonexistent primary key.");

      default:
         raise_bdb_exception_with_code("An error occured in retrieving the data from the database.",result);
   }
}

/* insert: t -> string -> string */
value caml_bdb_insert( value vdb, value vkey, value vcontent ) /* ML */
{
   int ret;
   DBT key, data;

   /* zero out DBTs before using them */

   memset( &key, 0, sizeof( key ) );
   memset( &data, 0, sizeof( data ) );

   /* retrieve the key */

   key.data = String_val( vkey );
   key.size = string_length( vkey );

   /* set the data */

   data.data = String_val( vcontent );
   data.size = string_length( vcontent );

   /* get the handle */

   DB * dbp = extract_dbp( vdb );

   /* insert */

   switch( ret = dbp->put( dbp, NULL, &key, &data, DB_NOOVERWRITE ) )
   {
      case 0 :
	 return Val_unit;

      case DB_KEYEXIST:
	 raise_bdb_exception("Entry already exists");

      default:
         raise_bdb_exception_with_code("DB_INSERT: Berkeley DB store failed",ret);
   }
}


/* replace: t -> string -> string */
value caml_bdb_replace( value vdb, value vkey, value vcontent ) /* ML */
{
    int ret;
    DBT key, data;

    /* zero out DBTs before using them */

    memset( &key, 0, sizeof( key ) );
    memset( &data, 0, sizeof( data ) );

    /* retrieve the key */

    key.data = String_val( vkey );
    key.size = string_length( vkey );

    /* set the data */

    data.data = String_val( vcontent );
    data.size = string_length( vcontent );

    /* get the handle */

    DB * dbp = extract_dbp( vdb );

    /* insert */

    if (ret = dbp->put( dbp, NULL, &key, &data, 0 )) {
	dbp->err(dbp, ret, "DB->put");
	raise_bdb_exception_with_code("Berkeley DB store failed",ret);
    }
    else return Val_unit;

}

/* delete */
value caml_bdb_delete( value vdb, value vkey ) /* ML */
{
   int ret;
   DBT key;

   /* zero out DBT */

   memset( &key, 0, sizeof( key ) );

   /* retrieve the key */

   key.data = String_val( vkey );
   key.size = string_length( vkey );

   /* get the handle */

   DB * dbp = extract_dbp( vdb );

   /* blow away the entry */

   switch( ret = dbp->del( dbp, NULL, &key, 0 ) )
   {
      case 0 :
	 return Val_unit;
      default:
         raise_bdb_exception_with_code("Berkeley DB delete failed",ret);
   }
}

/* Dbmbd.firstkey */

value caml_bdb_firstkey( value vdb ) /* ML */
{
   DBT key, data;

/*
   FILE * fp;

   fp = fopen("log","w");
   fprintf(fp,"in firstkey\n");
   fflush(fp);
*/ 



   /* zero out DBTs before using them */

   memset( &key, 0, sizeof( key ) );
   memset( &data, 0, sizeof( data ) );

   /* set the key */

   key.data = BDB_buf_key( vdb );
   key.ulen = *BDB_buf_key_size_ptr( vdb );
   key.flags = DB_DBT_USERMEM;

   /* set the data */

   data.data = BDB_buf_data( vdb );
   data.ulen = *BDB_buf_data_size_ptr( vdb );
   data.flags = DB_DBT_USERMEM;

   /* get the handle */

   DB * dbp = extract_dbp( vdb );

   /* create a cursor */

   DBC *cursorp = BDB_active_cursor( vdb );

   if( cursorp ) /* remove old cursor */
      cursorp->c_close( cursorp );

   dbp->cursor( dbp, NULL, &cursorp, 0);
   BDB_active_cursor( vdb ) = cursorp;

/*
   fprintf(fp,"cursor created\n");
   fflush(fp);
*/
   /* get first entry */

   unsigned int result = cursorp->c_get( cursorp, &key, &data, DB_FIRST );

#if (DBVER >= 43)
   while( result == DB_BUFFER_SMALL )
#else
   while( result == ENOMEM )
#endif
   {
      /* Enlarge our data buffer to accomodate the amount requested by
	 Berkeley DB */

      /*    fprintf(fp,"data.ulen = %d, data.size = %d\n", data.ulen, data.size ); */

      if( data.ulen < data.size )
      {
	 data.ulen = bdb_allocate_buffer( BDB_buf_data_ptr(vdb), 
					  BDB_buf_data_size_ptr(vdb),
					  data.size );
	 
	 data.size = 0;

	 /* Don't forget to set the new buffer */

/*
	 fprintf(fp,"firskey: resizing data buffer\n");
	 fflush(fp);
*/

	 data.data = BDB_buf_data( vdb );
      }

      if( key.ulen < key.size )
      {
	 key.ulen = bdb_allocate_buffer( BDB_buf_key_ptr(vdb),
					 BDB_buf_key_size_ptr(vdb),
					 key.size );

	 key.size = 0;

	 /* Don't forget to set the new buffer */
/*
	 fprintf(fp,"firskey: resizing key buffer to %d\n", key.ulen );
	 fflush(fp);
*/
	 key.data = BDB_buf_key( vdb );
      }

      /* try again */

      result = cursorp->c_get( cursorp, &key, &data, DB_FIRST );

/*
      fprintf(fp,"result = %X data.size = %d key.size = %d data.ulen = %d key.ulen = %d",result,data.size,key.size,data.ulen,key.ulen);
      fflush(fp);
*/
   }
    
   if( result )
      raise_not_found();

   /* All we do is return the key value. */
   
   value res = alloc_string( key.size );
   memmove( String_val(res), key.data, key.size );
   return res;   
}

value caml_bdb_nextkey( value vdb ) /* ML */
{
   DBT key, data;

   /* zero out DBTs before using them */

   memset( &key, 0, sizeof( key ) );
   memset( &data, 0, sizeof( data ) );

   /* set the key */

   key.data = BDB_buf_key( vdb );
   key.ulen = *BDB_buf_key_size_ptr( vdb );
   key.flags = DB_DBT_USERMEM;

   /* set the data */

   data.data = BDB_buf_data( vdb );
   data.ulen = *BDB_buf_data_size_ptr( vdb );
   data.flags = DB_DBT_USERMEM;

   /* create a cursor */

   DBC *cursorp = BDB_active_cursor( vdb );

   if( !cursorp ) 
   {
      printf("ERROR IN CAML_DBMBDB_NEXTKEY\n");
      fflush(stdout);

      raise_not_found();
   }

   /* get next entry */

/*
   printf("IN CAML_DBMBDB_NEXTKEY before cursor:\n");
   printf("KEY.DATA = %x\nKEY.ULEN = %d\nKEY.FLAGS = %x\n",
	  key.data, key.ulen, key.flags );
   printf("DATA.DATA = %x\nDATA.ULEN = %d\nDATA.FLAGS = %x\n",
	  data.data, data.ulen, data.flags );
   printf("CURSORP: %x\n",cursorp);

   fflush(stdout);
*/
   unsigned int result = cursorp->c_get( cursorp, &key, &data, DB_NEXT );

/*
   printf("IN CAML_DBMBDB_NEXTKEY\n");
   fflush(stdout);
*/
#if (DBVER >= 43)
   while( result == DB_BUFFER_SMALL )
#else
   while( result == ENOMEM )
#endif     
   {

      /* Enlarge our data buffer to accomodate the amount requested by
	 Berkeley DB */

      if( data.ulen < data.size )
      {
	 data.ulen = bdb_allocate_buffer( BDB_buf_data_ptr(vdb), 
					  BDB_buf_data_size_ptr(vdb),
					  data.size );
	 
	 /* Don't forget to set the new buffer */

	 data.data = BDB_buf_data( vdb );
      }

      if( key.ulen < key.size )
      {
	 key.ulen = bdb_allocate_buffer( BDB_buf_key_ptr(vdb),
					 BDB_buf_key_size_ptr(vdb),
					 key.size );

	 /* Don't forget to set the new buffer */

	 key.data = BDB_buf_key( vdb );
      }

      /* try again */

      result = cursorp->c_get( cursorp, &key, &data, DB_NEXT );
   }

/*
   printf("IN CAML_DBMBDB_NEXTKEY [ 2 ]\n");
   fflush(stdout);
*/  
   if( result )
   {
      /*
	printf("RAISING NOT FOUND\n");
      fflush(stdout);
      */
      raise_not_found();
   }
/*
   printf("IN CAML_DBMBDB_NEXTKEY after cursor:\n");
   printf("KEY.DATA = %x\nKEY.ULEN = %d\nKEY.FLAGS = %x\n",
	  key.data, key.ulen, key.flags );
   printf("DATA.DATA = %x\nDATA.ULEN = %d\nDATA.FLAGS = %x\n",
	  data.data, data.ulen, data.flags );
   printf("CURSORP: %x\n",cursorp);
   fflush(stdout);
*/
   /* All we do is return the key value. */
   
   value res = alloc_string( key.size );
   memmove( String_val(res), key.data, key.size );

/*
   printf("LEAVING CAML_DBMBDB_NEXTKEY\n");
   fflush(stdout);
*/
   return res;
}
