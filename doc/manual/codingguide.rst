Coding Guide
============

There are a number of unusual coding features, which developers working on
|phc| should know about.

Debugging
---------

.. |gdb| replace:: :program:`gdb`

|phc| uses :program:`libtool`, which can make debugging tricky
[#libtool_link]_. When you want to call |gdb| on |phc|, you must use
:program:`libtool`. Instead of

.. sourcecode:: bash

   gdb --args src/phc --help

you must use

.. sourcecode:: bash

   libtool --mode=execute gdb --args src/phc --help

This may be abbreviated:

.. sourcecode:: bash

   libtool e gdb --args src/phc --help

If you are working on, or debugging, compilation with |phc|, we have created a
`convenience wrapper
<http://code.google.com/p/phc/source/browse/trunk/misc/comp>`_ wrapper to
simplfiy this.



In |gdb|, tab-completion (for example for breakpoints) will not be
available immediately. This is because |phc| is structured as a library, which
is only loaded once the program starts. Tab-completion will begin to work once
|phc|'s execution starts.

We have found that |gdb| can be tempermental when working with |phc|. If you
rebuild |phc| while working in |gdb|, you will need to restart |gdb|. |gdb|
also has problems reading C++ values containing |phc|'s objects. This can
sometimes be worked around by finding the same value in a different context
(perhaps after it has been casted, or passed to another function).
Occasionally, dereferencing a pointer using `->` can fail --- try using `.`
instead.


phc idoms 
---------

Garbage collection
******************

We use garbage collection in |phc|. That is, the compiler itself is linked to a
garbage collection library, and we do not free any memory manually. As a
result, any objects which store objects allocated by |phc| (such as objects
representing AST classes), must be registered with the garbage collector.

This is very straightforward for classes. Simply inherit from `GC_obj`:

.. sourcecode:: c++

   class MyClass: virtual public GC_obj
   {
      // Class implementation
      ...
   }


STL containers are handled differently, as they provide a parameter for the
allocator. If allocating an std::list, you may use

.. sourcecode:: c++

   std::list<AST::Node*, phc_allocator<AST::Node*> > mylist.

However, we provide a number of convenience classes, which can be used without `phc_allocator`:

   * List (in :file:`src/lib/List.h`)
   * Map (in :file:`src/lib/Map.h`)
   * Set (in :file:`src/lib/Set.h`)
   * Stack (in :file:`src/lib/Stack.h`)
   * Vector (in :file:`src/lib/Vector.h`)

If you wish to override another STL container to use garbage collection, use this template:

.. sourcecode:: c++

   template<typename _Tp, typename _Alloc = phc_allocator<_Tp> >
   class List : public std::list<_Tp, _Alloc>, virtual public GC_obj
   {
      ...
   }


foreach-loop
************

Since we use lists so frequently, `foreach` is used throughout the |phc|
codebase. This is a macro for `BOOST_FOREACH
<http://www.boost.org/doc/libs/1_39_0/doc/html/foreach.html>`_.

It is often combined with boost::tie, which splits an `std::pair` or tuple into
their requisite fields, so it goes well with `std::map`\s.

.. sourcecode:: c++

   int key, value;
   Map<int, int> mymap = some_function ();
   foreach (tie(key, value), mymap)
   {
      ...
   }


`List`\s work very well with `foreach`, but can lead to long error messages if
a `List*` is used instead of a List. If you come across error like this:

.. sourcecode:: text

   /usr/include/boost/range/mutable_iterator.hpp: In instantiation of ‘boost::range_mutable_iterator<MIR::Signature_list*>’:
   /usr/include/boost/mpl/eval_if.hpp:38:   instantiated from ‘boost::mpl::eval_if<mpl_::bool_<false>, boost::range_const_iterator<MIR::Signature_list*>, boost::range_mutable_iterator<MIR::Signature_list*> >’
   /usr/include/boost/foreach.hpp:368:   instantiated from ‘boost::foreach_detail_::foreach_iterator<MIR::Signature_list*, mpl_::bool_<false> >’
   src/codegen/Generate_C.cpp:514:   instantiated from here
   /usr/include/boost/range/mutable_iterator.hpp:37: error: ‘MIR::Signature_list*’ is not a class, struct, or union type
   src/codegen/Generate_C.cpp: In function ‘void function_declaration_block(std::ostream&, MIR::Signature_list*, String*)’:
   src/codegen/Generate_C.cpp:514: error: no matching function for call to ‘deref(const boost::foreach_detail_::auto_any_base&, boost::foreach_detail_::type2type<MIR::Signature_list*, mpl_::bool_<false> >*)’
   /usr/include/boost/foreach.hpp: In function ‘bool boost::foreach_detail_::done(const boost::foreach_detail_::auto_any_base&, const boost::foreach_detail_::auto_any_base&, boost::foreach_detail_::type2type<T*, C>*) [with T = MIR::Signature_list, C = mpl_::bool_<false>]’:
   src/codegen/Generate_C.cpp:514:   instantiated from here
   /usr/include/boost/foreach.hpp:695: error: no match for ‘operator!’ in ‘!* boost::foreach_detail_::auto_any_cast [with T = MIR::Signature_list*, C = mpl_::bool_<false>](((const boost::foreach_detail_::auto_any_base&)((const boost::foreach_detail_::auto_any_base*)cur)))’
   /usr/include/boost/foreach.hpp:695: note: candidates are: operator!(bool) <built-in>


it is likely that a `List*` was used in a foreach, instead of a `List`.


.. [#libtool_link]

   The `libtool documentation
   <http://www.gnu.org/software/libtool/manual/html_node/Debugging-executables.html>`_
   has more details.



