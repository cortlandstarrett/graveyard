

                        ObjectStore 6.0 Service Pack 8
                                   May 2002

                 Copyright (c) eXcelon Corporation, 1989-2002.
                     All Rights Reserved.  Patent Pending.

This document includes release information for all the modules of ObjectStore
Release 6.0 Service Pack 8. The modules include some or all of the following, 
depending on platform architecture:

        ObjectStore C++ Interface (OSCI)
        ObjectStore Java Interface (OSJI)
        Dynamic Data Modeling Library (DDML)
        Java Middle-Tier Library (JMTL)
        ObjectStore ActiveX Interface (OSAX)
        Rapid Database Development tool (RDD)


Additional release module details are available in README files and Release
Notes available once layered software modules are installed.

ObjectStore installation instructions for your platform can be found in the
docs directory on the CD as described in the following list.  Open the
index.htm file in your Web browser.

   AIX     :  docs/install_guide/inst_aix/index.htm
   HP-UX   :  docs/install_guide/inst_hp/index.htm
   Linux   :  docs/install_guide/inst_lnx/index.htm
   SGI     :  docs/install_guide/inst_sgi/index.htm
   Solaris :  docs/install_guide/inst_sol/index.htm
   Tru64   :  docs/install_guide/inst_t64/index.htm
   Windows :  docs/install_guide/inst_nt/index.htm

You can also find a full set of product documentation as well as
information about previous Release 6.0 Service Packs on the Technical
Support Web site at docs.exln.com.  Service Pack 8 documentation
becomes available on the Support Web site shortly after the software
is released, not before.

Service Pack 8 documentation does not support full-text search of the
documentation set on the CD. During the documentation installation, an
error message such as the following is likely to appear:

     chmod: WARNING: can't access <install_pathname>/search
     Can't open <install_pathname>/search/search.ini
     mv:cannot rename /tmp/search.tmp: No such file or directory

This error message relates to obsolete files and is of no consequence.


CONTENTS
========

 - Supported Platforms
 - Operating System Patches
 - Release 6.0 Service Pack 8 Highlights
 - Restrictions and Known Problems

Supported Platforms
===================

The Support Matrix available on the Internet at http://support.exln.com
provides a complete listing of all supported and maintained products on
all platforms.

ObjectStore Release 6.0 Service Pack 8 supports the following
platforms and compilers:  

 - Windows NT 4.0 SP3, SP4, SP5, SP6a; and Windows 98/2000/XP

   C++: Visual C++ 6.0 SP3
   Java Virtual Machines:

        Sun Java 2 SDK Version 1.4.0 for Windows
        Sun Java 2 SDK Version 1.3.0 for Windows
        Sun Java 2 SDK Version 1.2.2 for Windows
        IBM Java Development Kit Version 1.3.0
        IBM Java Development Kit Version 1.2.2 

   NOTES:  
      1. Windows ME requires steps to work around installation 
         problems with that platform. ObjectStore Support provides an FAQ
         describing the procedure. The FAQ is named
         install_osserver_oscmgr_on_win_me.
      2. NT 4.0 SP3 is supported with y2k patch that is available at
         http://www.microsoft.com/technet/year2k/product/user_view68488EN.htm
      3. Windows 95 has moved from supported status to maintained status.

 - Sun Platform (three separate packages):

   Solaris/SPARC 2.6, 2.7, 2.8 (32-bit)
   C++:   SunPro C++ 4.2; Solaris Forte 6.1 C++ version 5.2 (in
   compatibility mode)
   Java:  Sun Java 2 SDK 1.2.2

   Solaris/SPARC 2.6, 2.7, 2.8 (32-bit)
   C++:   Solaris Forte 6.1 C++ version 5.2 (native mode);  Solaris Forte 6.2
          C++ version 5.3 (native mode)
   Java:  Sun Java 2 SDK 1.3 and 1.4

   Solaris/SPARC 2.8 (64-bit)
   C++:   Solaris Forte 6.1 C++ version 5.2 and 6.2 C++ version 5.3 (native
          mode); the -xarxch=v9 compiler option for 64-bit applications
   Java:  No JDK available

   While you can develop and run 32-bit applications using the 32-bit
   ObjectStore packages on 32-bit or 64-bit Solaris platforms, you can only
   develop and run 64-bit applications using the 64-bit ObjectStore packages
   on 64-bit hardware-capable platform.

   Also, note that ObjectStore using the Solaris Forte 6.1 C++ version 5.2
   compiler requires the Sun Microsystems patch number 106327-08.

 - AIX 4.3.3

   C++: xlC 3.6.6 compiler
   Java: IBM Java Development Kit Version 1.2.2, 1.3

 - Compaq Tru64 -- We provide two packages of ObjectStore -- one for Tru64
   version 4.0D/4.0F and another for version 5.1.

   C++: 6.1 (Tru64 version 4.0) and 6.3 (Tru64 version 5.1) -- both 64-bit

 - HP-UX 11.0 and 11i -- both 64-bit

   C++: aCC 3.15 compiler and later (3.27 in compatibility mode)
   Java: No JDK available

   NOTE: The 3.27 compiler for HP 64-bit platforms is supported with the 
       use of the backward-compatibility flags described under 
       Restrictions and Known Problems.

 - HP-UX 11.00 and 11i -- both 32-bit

   C++: aCC 3.27 compiler and later
   Java: JDK  1.2.2.08 or 1.3

 - Linux 2.2.14 Red Hat 7.2

    C++: gcc, version 2.95.2
    Java: Blackdown JDK 1.2.2, 1.3; Sun Java SDK 1.3; Sun Java SDK 1.4

       Use of Sun JDK 1.3 on Red Hat Linux 7.2:

       Sun's JVM was built with Redhat 6.1 using the gcc/egcs-2.91
       compiler and has an explicit dependency on libstdc++-libc6.1-1.so.2.
       ObjectStore's JNI libraries are built using the C++ compiler version
       2.95.2, and have an explicit dependency on a newer
       libstdc++-libc6.2-2.so.3.  These two libraries are not compatible and
       can cause problems if loaded at the same time.  To ensure that both
       Sun's JVM and ObjectStore's JNI libraries use the same libstdc++
       library, create a symbolic link so that libstdc++-libc6.1-1.so.2
       points to libstdc++-libc6.2-2.so.3. Also, make sure that the link
       libstdc++-libc6.2-2.so.3 is pointing to the right version of the
       glibc library.  In Red Hat 7.2, both the glibc 2 and glibc 3 version
       of the libraries are bundled.

       To create the correct links, execute the following commands as root:

         cd /usr/lib
         mv libstdc++-libc6.1-1.so.2 libstdc++-libc6.1-1.so.2.orig
         ln -sf  libstdc++-libc6.2-2.so.3 libstdc++-libc6.1-1.so.2
         ln -sf libstdc++-2-libc6.1-1-2.9.0.so libstdc++-libc6.2-2.so.3

 - SGI IRIX 6.5.5

   C++ 7.2.1 compiler
   Java: JDK 1.2

Operating System Patches
========================

  - HP-UX:

    The HP-UX kernel patch PHKL_20995 and any dependent
    patches are required. If this patch is not installed,
    ObjectStore can cause the operating system to crash (a UNIX
    kernel panic).

    The HP-UX kernel patches(PHNE_23456 and PHNE_23249) and
    all dependent patches must also be installed for ObjectStore
    to operate correctly. PHCO_23770 is a dependent patch that
    must be installed to enable correct pthread operation.

  - Solaris:

    ObjectStore using the Solaris Forte 6.1 C++ version 5.2 compiler
    requires the Sun Microsystems patch number 106327-08.

    For ObjectStore to operate correctly on Solaris 8 (SunOS 5.8),
    you must install the kernel update patch 108528-14 or greater.

  -SGI IRIX:

    If you use the OS_BEGIN_TXN and OS_END_TXN lexical transaction
    macros, eXcelon recommends that you obtain Patch 3776: MIPSpro
    7.2.1 C++ front-end rollup #8 patch for the C++ compiler.
    Without this patch, you are likely to see errors such  
    as the following:

    "stest.cc": Error: A goto outside a region cannot jump to a label
    inside a region, t3_s at line 1150


Release 6.0 Service Pack 8 Highlights
=====================================

  This release of ObjectStore consists of the following:

    - Fixes to customer-reported problems

    - Minor performance improvements

    - Compile-line defines for enabling collections optimization

    - Support for JDK 1.4 on Windows, Solaris, and Linux (see "Support
      for JDK 1.4", below)

    - Support for the Solaris Forte 6.2 C++ compiler

  For more information about this release, see the ObjectStore Release
  Notes.

  Support for JDK 1.4
  -------------------

    JDK 1.4 is supported by the ObjectStore Java Interface (OSJI) and PSE
    Pro run times.  The post processor (osjcfp), however, has limited
    support for JDK 1.4.  It will not modify classes that have been
    compiled using the '-target 1.4' or '-source 1.4' options (both javac
    options).  More generally, osjcfp will not modify classes that have
    assertions.  The core Java classes that come with JDK 1.4 were
    compiled with the '-target 1.4' option and therefore cannot be
    modified with the post processor.

    Do not explicitly compile for JDK 1.4.  You must compile for JDK 1.2,
    which generates code that runs under JDK 1.2, 1.3, and 1.4.

  OSJI Demo Programs
  ------------------

    The following demo examples have been removed from the Release
    6.0 Service Pack 8 OSJI (<instal_dir>/com/odi/demo/)package:  

      OSDraw
      collections
      odmgcport
      cport
      props
      qport
      rmi
      rmimulti
      xml

  ObjectStore Documentation
  -------------------------

    The entire documentation set for OSCI and OSJI was revised with
    significant content improvements in Service Pack 6.  For a list of
    changes to the documentation since Service Pack 6, see the Release
    Notes.

    The ObjectStore documentation bookshelf gets installed in the
    following locations:
      
      Windows: %OS_ROOTDIR%\doc\topindex.htm
      UNIX:    $OS_ROOTDIR/doc/topindex.htm


Restrictions and Known Problems
===============================

-  If you are upgrading from ObjectStore Release 5.1 to ObjectStore
   Release 6.0 Service Pack 8, you must install ObjectStore Release 5.1
   Service Pack 5A.  Also, contact Technical Support (support@exln.com) for
   information about obtaining a patch for the dump/load facility for
   ObjectStore Release 5.1 Service Pack 5A.

-  eXcelon recommends that you not use the "least space" allocation
   strategy until contacting Support for a patch.  Note that the "least
   space" allocation strategy is not the default.  The default is the
   "least wait" allocation strategy, which you can continue to use.

-  Under certain conditions described under A) and B) that follow, using
   ObjectStore Release 6.0 Service Pack 5 or earlier can result in corrupted
   vector headers.

   A) In cases where a vector was created on HP-UX 11.0 (64-bit) or Solaris
   SPARC 2.8 (64-bit) without using the normal form of the
   ObjectStore overloaded operator "new", corruption can occur.  Normal form
   is the operator "new" followed by constructor syntax.  For example:

   void *p = new(db, foo::get_os_typespec(), N) foo[N];

   When this normal form is used, there is no problem.  Problems occur 
   with forms such as:

   void *p = ::operator new(sizeof(foo)*N, db, foo::get_os_typespec(), N);

   B) In cases where a vector was hetero-relocated from a different
   platform to HP-UX 11.0 (64-bit), Solaris SPARC 2.8 (64-bit),
   or Linux GPP, and the page containing the vector was
   committed, corruption can occur.

   This release includes several methods of detecting and
   correcting vector header problems. One method involves running
   a utility, osfixvh, that can detect and correct such vector
   header problems. See the ObjectStore Release 6.0 Service Pack 8  
   Release Notes for a discussion of this potential problem.

-  Do not copy debug libraries (in debug.zip) into the regular
   distribution area. Some debug libraries have the same name as
   the regular distribution libraries, so if you copy them into
   the regular distribution area, they will overwrite the few
   identically named libraries (lacking the d suffix). The result 
   will be libraries that do not work for normal operation.

-  In the CMTL module for Release 6.0 Service Pack 8 release, the
   CMTL cache pool attribute commit_if_idle value
   default is true for read-only caches (true is also the
   value for update caches). If the commit_if_idle attribute
   value is set to false, a shutdown timing problem in the CMTL 
   virtual transaction manager thread results. If you have
   explicitly set the commit_if_idle value to false in your cache
   pool configuration, you need to modify it to avoid this timing
   issue.

-  On Solaris 2.8, when using the SunPro C++ 4.2 compiler, the
   CMTL hello_xml example fails with an error such as the following:

   BEGIN TEST hello
   Unexpected JTCIllegalThreadStateException in ~JTCThreadGroup
   JTC failed initialization:
       pthread_setschedparam
           (
           1, // thrId_
           68208, // policy
           0xffbeea9c  // &param
           ) == 22 [Thread.cc:996]

   This is a known problem that will be corrected in a future release.

-  Use of JDK 1.3 on AIX: Address Space Allocation -- Depending on your 
   system configuration, you might need to adjust ObjectStore's default 
   persistent address space for ObjectStore to work properly on AIX 
   with JDK 1.3.  The default settings can be modified by setting the 
   OS_AS_START and OS_AS_SIZE environment variables.  For example, you 
   might need to change the address space start and size on AIX to the 
   following values:

      setenv OS_AS_START 0xb0000000
      setenv OS_AS_SIZE  0x20000000

   For more information about persistent address space, see the
   "Managing ObjectStore" book in the ObjectStore documentation set.
   If necessary, Technical Support can assist you with the configuration
   of address space on your system.

-  Use of JDK 1.3 and 1.4 on Solaris machines -- To ensure compatibility
   between ObjectStore and JDK 1.3 or JDK 1.4 on Solaris, you must set
   the LD_PRELOAD environment variable as follows:

	setenv LD_PRELOAD libosopdel.so

-  Use of JDK 1.3 on HP-UX 32-bit -- To ensure compatibility between 
   ObjectStore and JDK 1.3 on HP-UX 32-bit machines, you can set the
   LD_PRELOAD environment variable as follows:

	setenv LD_PRELOAD libos.sl:libosth.sl
  
-  Patches Required for HP-UX -- The patches PHNE_23456 and PHNE_23249 
   and all dependent patches must be installed for ObjectStore to 
   operate correctly. PHCO_23770 is a dependent patch that must be 
   installed to enable correct pthread operation. Patch number PHSS_23440 
   is required to allow the LD_PRELOAD environment variable to work with 
   JDK 1.3 and ObjectStore.

-  Address Space Allocation on HP-UX with JDK 1.3 -- Depending on your 
   system configuration, you might need to adjust ObjectStore's default 
   persistent address space for ObjectStore to work properly on HP-UX 
   with JDK 1.3.  The default settings can be modified by setting the 
   OS_AS_START and OS_AS_SIZE environment variables.  For example, 
   you might need to reduce the address space size on HP-UX from the default 
   value of 0xc000000:

      setenv OS_AS_SIZE 0x6000000    

   For more information about persistent address space, see the
   "Managing ObjectStore" book in the ObjectStore documentation set.  If
   necessary, Technical Support can assist you with the configuration of
   address space on your system.

-  HP-UX 64-bit 3.27 C++ Compiler Support machines -- In order to use the
   3.27 C++ compiler successfully with ObjectStore 6.0 Service Pack 6 or
   Service Pack 7, you must use the following flags:

     -Wc,-longdouble,old_alignment

   These flags specify using the old (3.15 compiler) long double 
   alignment.

-  Compaq Tru64 UNIX has some hetero restrictions and
   considerations that are described in the Release Notes.

-  On Linux 6.2, there is a hard-coded 256-megabyte address space
   restriction requiring workarounds to avoid the potential of
   running out of address space. Such a restriction does not exist
   on Linux 7.1 since it includes a kernel parameter that can be
   modified. Check the Release Notes for specific
   information about the workaround if you are using Linux 6.2,
   and for setting the parameter if you are using Linux 7.1.

- On Linux, ifstream is not opened by default for reading. The
  workaround is to explicitly pass an argument to the constructor
  telling it to open the stream for reading. For example:

          ifstream xml_file(config_info, ios::nocreate);

  This workaround should also open the stream for reading, but on
  Linux it does not. On Linux the following is necessary:

          ifstream xml_file(config_info, ios::nocreate | ios::in);

  The flag ios::in tells the constructor to open the stream for
  reading. Such a change is only required on Linux.

- Databases written by ObjectStore Release 6.0 (or later) Service
  Pack 6 on Solaris (64-bit) platforms are not supported for
  heterogeneous access from any other version of ObjectStore,
  including other 6.0.6 versions and earlier Release 6.0 (or later)
  versions.  Heterogeneous access to ObjectStore databases created
  on Solaris 64-bit platforms should be avoided; if tried, the
  access will appear to work correctly but in some cases can
  corrupt data. 

  The use of ObjectStore Release 6.0 Service Pack 6 (or later) on
  Solaris (64-bit) platforms to access databases written by any
  other version of ObjectStore is also not supported and risks
  data corruption.

  Such heterogeneous access will be supported in a future release
  of ObjectStore.

- On the HP-UX 32-bit version of ObjectStore, in order to link a
  shared library or executable with OSJI libraries, the library path

       <java-jre-libraries>/PA_RISC/classic

  needs to be added to the link line. Otherwise, the ld command
  will give the following error message:

     Can't open ../../lib/PA_RISC/classic/libjvm.sl

- To use the DDML C++ API, add the DDML executables to your
  environment.  To use the DDML Java API, add the DDML .zip or .jar
  file to your CLASSPATH.

  For example, on Solaris, if you place the ObjectStore distribution into
  /opt/ODI, add the following additional entry to use the C++ API:

    LD_LIBRARY_PATH=/opt/ODI/ddml/lib

  To use the Java API, add the following:

    CLASSPATH=/opt/ODI/ddml/osddml.zip

  On Windows, if you place the ObjectStore distribution into
  c:\odi\, you need this additional entry to use the C++ API:

    PATH=c:\odi\ddml\bin

  To use the Java API, add this entry:

    CLASSPATH=c:\odi\ddml\osddml.zip



