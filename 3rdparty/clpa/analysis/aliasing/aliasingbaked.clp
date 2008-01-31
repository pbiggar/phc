%%
% Authors:
%   Brian Hackett  <bhackett@stanford.edu>
%
% Copyright (c) 2006,
%   The Board of Trustees of The Leland Stanford Junior University
% All rights reserved.
%
% Redistribution and use in source and binary forms, with or without
% modification, are permitted provided that the following conditions are met:
% 
% 1. Redistributions of source code must retain the above copyright notice,
% this list of conditions and the following disclaimer.
% 
% 2. Redistributions in binary form must reproduce the above copyright notice,
% this list of conditions and the following disclaimer in the documentation
% and/or other materials provided with the distribution.
% 
% 3. The names of the contributors may not be used to endorse or promote
% products derived from this software without specific prior written
% permission.
% 
% THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
% AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
% IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
% ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
% LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
% CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
% SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
% INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
% CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
% ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
% POSSIBILITY OF SUCH DAMAGE.
%%

% baked-in information about aliasing invariants etc.
% imported directly by aliasing.clp

% pointer type invariants. all pointers to composites of type COMP are cursors
% into some gigantic global structure. don't use other spoints for these
predicate pointer_inv(COMP:string).
?drop_spoints(SUM,POS,S,T), trace_type(SUM,T,y_comp{COMP}),
    pointer_inv(COMP), +drop_spoints(SUM,POS,S,T).

% utility composite types. do not infer invariants on these
predicate non_invariant_comp(COMP:string).
non_invariant_comp(COMP), +omit_comp_spoints(COMP,_,_,_,_).

% ignore all spoints if we are in the given function
predicate ignore_fn(FN:string).
cil_curfn(FN), ignore_fn(FN), +drop_spoints(_,_,_,_).

% ignore all spoints involving the given global
predicate ignore_glob(in G:string).
?drop_spoints(SUM,POS,S,T), trace_root(S,glob{G}), ignore_glob(G),
    +drop_spoints(SUM,POS,S,T).
?drop_spoints(SUM,POS,S,T), trace_root(T,glob{G}), ignore_glob(G),
    +drop_spoints(SUM,POS,S,T).

% ignore all spoints involving the given field of the given type
predicate ignore_field(in C:string,in F:string).
?drop_spoints(SUM,POS,S,T),
    trace_sub(S,fld{_,F,C},_),
    ignore_field(C,F), +drop_spoints(SUM,POS,S,T).
?drop_spoints(SUM,POS,S,T),
    trace_sub(T,fld{_,F,C},_),
    ignore_field(C,F), +drop_spoints(SUM,POS,S,T).

% TODO: remove me
predicate ignore_trace(in SUM:sum,in T:t_trace).
?drop_spoints(SUM,POS,S,T), trace_sub(S,SS,_), ignore_trace(SUM,SS),
    +drop_spoints(SUM,POS,S,T).
?drop_spoints(SUM,POS,S,T), trace_sub(T,ST,_), ignore_trace(SUM,ST),
    +drop_spoints(SUM,POS,S,T).

predicate usemod_ignore_fn(in G:string).
cil_curfn(FN), usemod_ignore_fn(FN),
    +omit_usemod(_,_), +omit_soft(_,_,omit_dropped).

predicate usemod_ignore_glob(in G:string).
omit_usemod(T,_) :- trace_root(T,glob{G}), usemod_ignore_glob(G).

% openssh

% mmapped allocation structs/functions
+pointer_inv("mm_master").
+ignore_fn("mm_malloc"), +ignore_fn("mm_free"), +ignore_fn("mm_create").

% openssl

% these (almost) always point into a big global nid_objs array
+pointer_inv("asn1_object_st").

% array-based allocator
+ignore_fn("BN_CTX_get").

% httpd

% pool allocation structures
+pointer_inv("apr_pool_t"), +pointer_inv("apr_allocator_t").
+pointer_inv("apr_memnode_t"), +pointer_inv("apr_bucket_alloc_t").
+ignore_glob("srclib/apr/memory/unix/apr_pools.c:global_pool").
+ignore_glob("memory/unix/apr_pools.c:global_pool").

% ignore fields used for pool allocation or freelists
+ignore_field("apr_memnode_t","first_avail").
+ignore_field("apr_bucket_alloc_t","freelist").
+ignore_field("apr_pool_t","cleanups").

% const char*'s that are never written through yet leak out pervasively
+ignore_glob("server/mpm_common.c:dash_k_arg").
+ignore_glob("apr_hook_debug_current").
+ignore_field("request_rec","headers_out").
+ignore_field("request_rec","err_headers_out").
+ignore_field("request_rec","subprocess_env").

% postgresql

% pool allocation or other state in some global tree
+pointer_inv("MemoryContextData"), +pointer_inv("ResourceOwnerData").
+pointer_inv("TransactionStateData").

+ignore_glob("newNodeMacroHolder").
+ignore_glob("src/backend/utils/hash/dynahash.c:saveState").
+ignore_glob("psqlscan.l:cur_state").
+ignore_glob("BufferBlockPointers").
+ignore_glob("LocalBufferBlockPointers").
+ignore_glob("src/backend/storage/ipc/shmem.c:ShmemIndexAlloc").

% some system-wide cache structures
+ignore_glob("src/backend/utils/cache/syscache.c:SysCache").
+ignore_glob("src/backend/utils/cache/catcache.c:CacheHdr").
+ignore_glob("src/backend/utils/cache/relcache.c:RelationSysNameCache").
+ignore_glob("src/backend/utils/cache/relcache.c:RelationIdCache").
+ignore_glob("src/backend/commands/tablecmds.c:on_commits").
+ignore_glob("src/backend/utils/misc/guc.c:guc_variables").

+ignore_trace(_,fld{_,"freeList",_}).
+ignore_trace(_,fld{_,"null_field",_}), +ignore_trace(_,rfld{_,"null_field",_}).
+ignore_trace(_,fld{_,"relrefs",_}).
+ignore_trace(_,fld{_,"curBlock",_}).

% more home baked freelists
+ignore_glob("src/pl/plpgsql/src/pl_exec.c:active_simple_exprs").
+ignore_glob("src/interfaces/ecpg/ecpglib/memory.c:auto_allocs").

% don't infer composite invariants directly on these utility structs
+non_invariant_comp("Dllist"), +non_invariant_comp("Dlelem").
+non_invariant_comp("List"), +non_invariant_comp("ListCell").
+non_invariant_comp("__anonunion_data_53"). % internal union to List

+non_invariant_comp("__anonstruct_HASH_SEQ_STATUS_161").
+non_invariant_comp("HTAB").

% these are struct types that are always entries in a cache or global struct
+pointer_inv("RelationData").
+pointer_inv("SMgrRelationData").
+pointer_inv("connection").

% there is a bogus ret->*arg0 here due to an unreachable path.
% TODO: exit.clp should make this unnecessary
+ignore_fn("copyObject").

% samba

% core samba memory allocation function
+ignore_fn("_talloc").

+ignore_glob("kern/arch/amd64/page.c:page_free_list").

% linux

% low-level freelists and memory manipulation functions that we're ignoring
+ignore_fn("mm/slab.c:__cache_alloc"), +ignore_fn("mm/slab.c:__cache_free").
+ignore_fn("include/linux/mm.h:page_zone").
+ignore_fn("__alloc_pages").

+ignore_fn("vmap"), +ignore_fn("__vmalloc_area").
+ignore_fn("mempool_alloc"), +ignore_fn("mempool_free").

+ignore_fn("drivers/acpi/utilities/utalloc.c:acpi_ut_find_allocation").
+ignore_fn("drivers/acpi/utilities/utalloc.c:acpi_ut_remove_allocation").
+ignore_fn("drivers/acpi/utilities/utalloc.c:acpi_ut_track_allocation").

+ignore_fn("dput").
+ignore_fn("shrink_dcache_sb"), +ignore_fn("shrink_dcache_anon").
+ignore_fn("fs/dcache.c:select_parent").
+ignore_fn("fs/dcache.c:prune_dcache").

+ignore_fn("bio_alloc_bioset").
+ignore_fn("__xfrm_state_destroy").

+ignore_field(_,"virt_base").

+ignore_field("kernel_symbol",_).
+ignore_field("kernel_param",_).
+ignore_field("kparam_string",_).
+ignore_field("kparam_array",_).

% list_head etc. are utility structs used everywhere in linux
+non_invariant_comp("list_head").
+non_invariant_comp("hlist_head"), +non_invariant_comp("hlist_node").
+non_invariant_comp("__wait_queue").

+trace_one_simplify(_,fld{T,"prev","list_head"},fld{T,"next","list_head"}).
+trace_one_simplify(_,drf{fld{T,"le_prev",C}},fld{T,"le_next",C}).

+pointer_inv("net_device").
+pointer_inv("file").
+pointer_inv("inode").
+pointer_inv("dentry").

+ignore_glob("debug_mutex_held_locks").

% ok to cast between these two
+check_cast(y_comp{"sk_buff"},y_comp{"sk_buff_head"}).
+check_cast(y_comp{"sk_buff_head"},y_comp{"sk_buff"}).

% omitted usemod information
+usemod_ignore_fn("kfree").
+usemod_ignore_glob("mm/slab.c:cache_chain").
+usemod_ignore_glob("mm/hugetlb.c:hugepage_freelists").
+usemod_ignore_glob("mm/swapfile.c:swap_info").
+usemod_ignore_glob("mm/swap_state.c:swap_cache_info").
+usemod_ignore_glob("mm/shmem.c:shmem_swaplist").
+usemod_ignore_glob("mm/vmscan.c:shrinker_list").
+usemod_ignore_glob("mem_map").
+usemod_ignore_glob("debug_mutex_lock"), +usemod_ignore_glob("debug_mutex_held_locks").
+usemod_ignore_glob("debug_mutex_on").

+usemod_ignore_fn("kref_get").
+usemod_ignore_fn("kref_put").
+usemod_ignore_fn("kref_init").

+usemod_ignore_fn("include/linux/module.h:try_module_get").
+usemod_ignore_fn("include/linux/module.h:module_put").

% Histar
+ignore_glob("ko_list").
+ignore_glob("kern/kern/kobj.c:ko_gc_list").
+ignore_glob("kern/kern/kobj.c:ko_hash").
+ignore_fn("pagetree_get_page").
+ignore_fn("pagetree_put_page").

% Threads appear _everywhere_ and kill our scalability
+pointer_inv("Thread").
