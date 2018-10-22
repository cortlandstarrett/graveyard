$Id: readme,v 1.2 1995/06/15 18:26:03 vince Exp $

Here are some samples of the Visix Help Syntax language.  The Visix
Help Syntax language is a simple text markup language (like SGML,
Scribe, TeX or HTML) that you can use to author Galaxy help documents.

These samples are not complete documents but rather "snippets" that
illustrate a particular style or construct that you might find handy
when writing your own .hs (Help Syntax) files. To view these samples
in on-line help you need to compile them with the Galaxy Help
Compiler.

Do the following in the Galaxy Help Compiler to compile these .hs
source files into a help document set (.vhs file).

1. In the help compiler, use the Add File... command from the Source
menu to add the source files to a new help project.

2. Save the help project and then update it using the Update Project
command from the Project. Updating the help project generates the help
document set.

Preview the help document set with the Galaxy Help Server using the
following command line. (This command line is for the UNIX platform.
Use the appropriate syntax for your platform.)

  % vhelpsrv -noserver helpsrc.vhs

"helpsrc" is the name for the help project specified in the Galaxy
Help Compiler. Specify any name you like when saving the help project.



