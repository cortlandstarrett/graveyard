@section(section1 Links)
@parent(helpsamps)
@bold(Section 1)
@context(linking)


This is section one of help source code which explains links. To learn
more about links, see @link(section2 Section 2).  To learn about popup
links, see @popup(section3 Section 3).


@section(section2 The Link Command)
@parent(section1)
@bold(Section 2)


The first parameter to a \@link command should be the context you wish
to link to. In the case of the link in Section 1, this is the label
@bold(section2) which is defined by the \@section command directly
above this paragraph. You can also make a link to a @link(linking
context) defined using the \@context command, as was done in Section 1.


Any other parameters to the link command will be included in the text
and will appear as underlined.


@section(section3 The Popup Command)
@parent(section1)
@bold(Section 3)


A popup link works like a link, except that the information linked to
appears in a separate popup box, not in the main help browser window.
This can be useful for definitions, examples, or other information
which is ancillary to the main text.  As with a link, the first
parameter to the \@popup command should be the context you wish to
link to.  Any other parameters to the \@popup command will appear in
the text as underlined.
