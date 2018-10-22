@section(enum Enumerated List)
@parent(helpsamps)
@bold(Enumerated List Sample)


The following is an example of a numerical list, such as might be used
to explain a step-by-step process. To create an enumerated list like
this one, follow these steps:

@relmargin(40 0)
@prefix(-10 1.) 

Outline the steps of the procedure or otherwise segment the
information you wish to present.

@end(prefix)

This information can have multiple paragraphs per number.


Once you have outlined your list, you can proceed to step two.

@prefix(-10 2.)

Set the left margin with the \@relmargin command.

@end(prefix)
@prefix(-10 3.)

Precede each item in the list with a \@prefix(x n.) command. x
should be a negative number representing the offset (in points) of the
prefix from the relative margin.  n is the prefix (usually a number in
an enumerated list). 

@end(prefix)

You can also include other paragraph formats @bold(inside) one
of the items of your enumerated list. These include:

@relmargin(20 0)
@prefix(-10 *)

bulleted lists, such as this one

another enumerated list

an indented paragraph

@end(prefix)
@end(relmargin)
@relmargin(40 0)

Note that the preceding bulleted list reset the margins with an
\@relmargin command. The \@end(relmargin) command ending the bulleted
list ends all relative margins. To continue with the previous
enumerated list format, set the margins again with a new \@relmargin
command.

@prefix(-10 4.)

End your enumerated list by ending the existing relmargin environment.

@end(prefix)
@end(relmargin)
