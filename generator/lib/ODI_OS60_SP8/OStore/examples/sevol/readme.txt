Simple Schema Evolution Examples
================================
These examples progressively move from simple examples through
to more complex examples as they progress. The purpose is to
show various aspects of schema evolution programming.

Files in this directory are:

    README.TXT        - this file

    doall.bat         - batch file which runs the whole example

    makefile          - makefile

    schm1pre.cc	      - application database schema source file, unevolved
			example 1
    schm1new.cc	      - application database schema source file, evolved
			example 1
    schm2pre.cc	      - application database schema source file, unevolved
			example 2
    schm2new.cc	      - application database schema source file, evolved
			example 2
    schm3pre.cc	      - application database schema source file, unevolved
			example 3
    schm3new.cc	      - application database schema source file, evolved
		        example 3
    schm4pre.cc	      - application database schema source file, unevolved
		        example 4
    schm4new.cc	      - application database schema source file, evolved
		        example 4
    schm5pre.cc	      - application database schema source file, unevolved
		        example 5
    schm5new.cc	      - application database schema source file, evolved
		        example 5

    db_pop1.cc        - database population program for example 1
    part1pre.hh       - class definition for original database
    db_read1.cc       - database reader program, assuming an evolved database
    part1new.hh       - class definition for new database

Note that this first example does not have any associated evolution program to
move the definition of the "part" class from part1pre.hh to part1new.hh. The
purpose of this example is to show you what the error from mismatched schemata
would be.

    db_pop2.cc        - database population program for example 2
    part2pre.hh       - class definition for evolved database, example 2
    evolve2.cc        - evolution program to evolve db from part2pre.hh to
			part2new.hh
    db_read2.cc       - database reader program, assuming an evolved database,
			example 2
    part2new.hh       - class definition for new database, example 2

    db_pop3.cc        - database population program for example 3
    part3pre.hh       - class definition for original database, example 3
    evolve3.cc        - evolution program to evolve db from part3pre.hh to
			part3new.hh
    db_read3.cc       - database reader program, assuming an evolved database,
			example 3
    part3new.hh       - class definition for new database, example 3

    db_pop4.cc        - database population program for example 4
    part4pre.hh       - class definition for original database, example 4
    evolve4.cc        - evolution program to evolve db from part4pre.hh to
			part4new.hh
    db_read4.cc       - database reader program, assuming an evolved database,
			example 4
    part4new.hh       - class definition for new database, example 4

    db_pop5.cc        - database population program for example 5
    part5pre.hh       - class definition for original database, example 5
    evolve5.cc        - evolution program to evolve db from part5pre.hh to
			part5new.hh
    db_read5.cc       - database reader program, assuming an evolved database,
			example 5
    part5new.hh       - class definition for new database, example 5

To build and run this example, first make sure that your environment
variable OS_ROOTDIR is set to the path of your ObjectStore installation.

Then you can either

1. Type 'doall' to run all the steps of this example.

or, to do each step of this example separately, do:

1. Type 'nmake' to make the various db_popn, db_readn and evolven executables.

2. Type 'db_pop1' to run the db_pop1 executable. This creates the
   db1.db database, and populates it.

3. Type 'db_read1' to run the db_read1 executable. This will display an
   error message saying that there is a type incompatibility. The purpose of
   this example is to demonstrate the error message.

4. For each of <n> = 2, 3, 4, 5, perform steps 5 through to 8

5. Type 'db_pop<n>' to run the db_pop<n> executable to create and
   populate the db<n>.db database.

6. Type 'db_read<n>' to run the db_read<n> executable; note the error message.

7. Invoke schema evolution on the database by typing 'evolve<n>'.

8. Type 'db_read<n>' to run the db_read<n> executable. Note that when you
   run it after schema evolution has been performed it completes successfully.

When you are done with this example, you may type
'nmake clean' to clean up.

