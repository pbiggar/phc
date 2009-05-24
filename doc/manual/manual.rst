.. phc documentation master file, created by sphinx-quickstart on Sun May 17 17:10:44 2009.
   You can adapt this file completely to your liking, but it should at least
   contain the root `toctree` directive.

..
	Top-level structure of the phc manuals
	
	See README for details

	TODO: mention license

<<<<<<<<<<<<<<<<<<<<<<<<<<<<
|phc| manual
<<<<<<<<<<<<<<<<<<<<<<<<<<<<


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



.. _treetutorials:

############################
Tree Traversal API Tutorials
############################

.. toctree::

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

	grammar
	representingphp
	limitations
	apioverview
	maketeatheory




.. _guide:

############################
Developers Guide
############################

.. toctree::

	porting




Indices and tables
==================

* :ref:`genindex`
* :ref:`search`

.. * :ref:`modindex`
.. * :ref:`glossary`

..
	TODO: things which should be discussed:
		developing phc:
			- Other IRs
			- testing
			- project page
			- prominent link to contribute
		folds
		describe compilation and generate-c
      pass_manager
      maketea_user_defined
      common errors in phc
         - boost foreach bug
      common idioms in phc
         - Map, List, etc, garbage collection
      analyses in other languages:
         ie PHP


