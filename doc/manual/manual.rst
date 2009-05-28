..
   Top-level structure of the phc manuals
   See README for details

   TODO: mention license

<<<<<<<<<<<<<<<<<<<<<<<<<<<<
phc manual
<<<<<<<<<<<<<<<<<<<<<<<<<<<<

.. important::

   If you cannot find information on some aspect of |phc|, please `get in touch
   <http://phpcompiler.org/mailinglist.html>`_, and we will try to fix it.


.. _usermanual:

&&&&&&&&&&&&&&&&&&&&&&&&&&&&
Users' manual
&&&&&&&&&&&&&&&&&&&&&&&&&&&&

.. toctree::
   
   userintro
   install
   runningphc



.. _devmanual:

&&&&&&&&&&&&&&&&&&&&&&&&&&&&
Developers' manual
&&&&&&&&&&&&&&&&&&&&&&&&&&&&

.. toctree::

   devintro
   demo



.. _treetutorials:

############################
Tree Traversal API Tutorials
############################

.. toctree::

   traversalintro
   gettingstarted
   treetutorial1
   treetutorial2
   treetutorial3
   treetutorial4
   treetutorial5
   treetutorial6



.. _reference:

############################
Reference
############################

.. toctree::

   refintro
   grammar
   representingphp
   limitations
   apioverview
   maketeatheory




.. _guide:

############################
Developers' Guide
############################

.. toctree::

   othersources
   testing
   porting



&&&&&&&&&&&&&&&&&&&&&&&&&&&&
Indices and tables
&&&&&&&&&&&&&&&&&&&&&&&&&&&&

* :ref:`search`

.. * :ref:`genindex`
.. * :ref:`modindex`
.. * :ref:`glossary`

.. todo::
   things which should be discussed:

   *  developing phc:

      +  Other IRs

   *  folds
   *  describe compilation and generate-c
   *  pass_manager
   *  maketea_user_defined
   *  common errors in phc

      +   boost foreach bug

   *   common idioms in phc

      +   Map, List, etc, garbage collection

   *   analyses in other languages:

      +   ie PHP

.. todolist::

