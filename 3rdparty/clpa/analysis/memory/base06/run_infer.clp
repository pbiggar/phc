import "../scalar.clp".

analyze session_name("cil_body").

+add_memory_cache().
+split_loops().
+ignore_int_casts().
