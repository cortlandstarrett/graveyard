

Welcome to combo samples directory.  The combo directory consists of
samples that show standard and popdown comboboxes along with various
dialog items that control the looks in these comboboxes.  In addition,
these comboboxes control the looks in "QUIT" button.  The samples
include

	sample
	sample1
	sample2
	sample3
	sample4
	sample5

All samples share the common code and resource, main.c and main.vr,
which creates the control dialog items, while each sample uses its own
privately held code, sample*.c, which creates sample-specialized
comboboxes.

The "various dialog items" that manipulate all these sample-specialized
comboboxes in similar behaviors, including

 *             combo's accept behavior
 *             accept combo to a randomly-chosen value
                    (if accept behavior is set to "NOTHING")
 *             combo's background color
 *             combo's border on/off
 *             combo's enable/disable look
 *             combo's font
 *             combo's foreground color
 *             mix values in combo
 *             control modifiable flag in combo
 *             combo's scroll behavior
 *             scroll combo to a randomly-chosen value
                    (if scroll behavior is set to "NOTHING")
 *             combo's select behavior
 *             select combo to a randomly-chosen value
                    (if select behavior is set to "NOTHING")
 *             show/hide combo
 *             sort values in combo
 *             use of copy
 *             use of copyInit
 *             use of load and store
 *             QUIT

The descriptions of each sample-specialized combobox are enclosed below.

        sample: Use of Galaxy's simple and default comboboxes.

        sample1: Use of subclassed comboboxes with overridden entrybox.
           Their entryboxes use label items (i.e. vdialogLabelItem),
           instead of Galaxy's default entrybox.

        sample2: Use of subclassed comboboxes with overridden choicebox.
           Their choiceboxes use vpalettes instead of Galaxy's default
           choicebox.

        sample3: Use of subclassed comboboxes with overridden values.
           Their values use vcolors instead of Galaxy's default
           string values.

        sample4: Use of subclassed comboboxes with all overrides combined
	   in sample1, sample2 and sample3.

        sample5: Use of subclassed comboboxes with overridden choicebox.
           Their choiceboxs consist of more than one-column options.


