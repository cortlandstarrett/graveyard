Welcome to the ObjectStore examples area!

This directory contains examples of how to use ObjectStore.
Each example is in its own sub-directory.

  hello
     	A simple hello world program that demonstrates
	the very basics of an ObjectStore makefile.

  hello2
        A hello world program that demonstrates how
	to create a database and increment a counter in
	that database.

  empretr
  	An ObjectStore program that demonstrates how
	to store and retrieve objects of your own C++ types
	in an ObjectStore database.

  coll
        An example using ObjectStore collections.

  dict
        An example using the ObjectStore dictionary.

  query
        An example using ObjectStore queries.

  relat
        An example using ObjectStore relationships.

  sevol
        An example using ObjectStore schema evolution.

  notify
        An example using the ObjectStore notification mechanism.

  dllschma
        An example using the ObjectStore DLL schema facility.  Demonstrates
	how to build ObjectStore enabled shared libraries.

  doc_demos\ref4

        These examples illustrate some of the ObjectStore macros.  For
        additional information about these examples, see ObjectStore C++
        API Reference, chapter 4.

  doc_demos\ug2

        This example illustrates commonly used features of ObjectStore
        applications.  The main application is a bookclub program that
        allows the user to select a book for a reader.  The program maintains
        two databases, one for information about readers and the other for
        information about books.  Utility applications are included to
        initialize the databases and list the reader database.  The main
        application assumes that both databases have been initialized.
        For additional information about this example, see ObjectStore C++
        API User Guide, chapter 2.

  doc_demos\ug4

        These two example programs illustrate how to create a database root,
        associate it with an entry-point object, find the root, and retrieve
        the object.  For an example of a program that uses the ObjectStore
        affiliation API for cross-database pointers, see the example doc_ug2.
        For additional information about this examples, see ObjectStore C++
        API User Guide, chapter 4.

  doc_demos\ug5

        These examples illustrate lexical, dynamic, and nested transactions.
        The example of a nested transaction also shows how to construct an
        abort-only transaction.  For additional information about the
        examples, see ObjectStore C++ API User Guide, chapter 5.

  doc_demos\ug6

        These examples illustrate the TIX exception handling facility.  For
        additional information about these examples, see ObjectStore C++
        API User Guide, chapter 6.

  doc_demos\ug7

        These examples illustrate how to use schema keys.  For additional
        information about these examples, see ObjectStore C++ API User
        Guide, chapter 7.

  doc_demos\ug8

        This example illustrates how to send and receive notifications.
        For more information about the example, see ObjectStore C++ API
        User Guide, chapter 8.

  doc_demos\ug9

        These examples illustrate two ways to perform schema evolution:
           * Using the ossevol utility with a post-processing application
           * Using a schema evolution application
        For more information about the examples, see ObjectStore C++ API
        User Guide, chapter 9.

This directory contains ObjectStore souces for VC++.
See ObjectStore C++ documentation, Building ObjectStore
Applications Chapter 4, about using ObjectStore with
VC++ MFC

  ospmfc
    The source code for os_CString which stores CString
    objects persistently.

