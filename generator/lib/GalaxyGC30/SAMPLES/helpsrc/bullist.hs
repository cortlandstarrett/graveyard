@subject(helpsamps Help Source Samples)

Here are some samples of the Visix Help Syntax language.  The Visix
Help Syntax language is a simple text markup language (like SGML,
Scribe, TeX or HTML) that you can use to author Galaxy help documents.


These samples are not complete documents but rather "snippets" that
illustrate a particular style or construct that you might find handy
when writing your own .hs (Help Syntax) files.


@link(bullist Bulleted list)

@link(enum Enumerated list)

@link(section1 Links)

@link(margins Relative margins)


@section(bullist Bulleted List)
@parent(helpsamps)

The following is a bulleted list.  Bulleted lists are useful for
conveying many kinds of information:


@relmargin(24 24)
@prefix(-18 *) lists of options or parameters


different methods for accomplishing the same task


lists of features, or any other information that lends itself to being
split up into discrete chunks, even if one or more of those chunks are
longer than one line

@end(prefix)
@end(relmargin)
