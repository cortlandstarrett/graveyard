/* $Id: puzzle.c,v 1.10 1995/07/24 17:53:18 scotth Exp $
 *
 * The following Sample Code is provided for your reference purposes in
 * connection with your use of the Galaxy Application Environment (TM) software
 * product which you have licensed from Visix Software, Inc. ("Visix").
 * The Sample code is provided to you without any warranty of any kind
 * whatsoever and you agree to be responsible for the use and/or incorporation
 * of the Sample Code into any software product you develop. You agree to fully
 * and completely indemnify and hold Visix harmless from any and all loss,
 * claim, liability or damages with respect to your use of the Sample Code.  
 *
 * Subject to the foregoing, you are permitted to copy, modify, and distribute
 * the Sample Code for any purpose and without fee, provided that (i) a
 * copyright notice in the in the form of "Copyright 1992 Visix Software Inc.,
 * 11440 Commerce Park Drive, Reston, VA  22091. All Rights Reserved" appears
 * in all copies, (ii) both the copyright notice and this permission notice
 * appear in supporting documentation and (iii) you are a valid licensee of
 * Galaxy Application Environment.
 */

/*
 * puzzle - game consisting of 4 x 4 grid of tiles (one of which is empty)
 *	    numbered from 1 to 15.  Object is to get tiles in increasing
 *	    order in rows.
 *
 *		Solved puzzle:
 *		 -- -- -- --
 *		| 1| 2| 3| 4|
 *		 -- -- -- --
 *		| 5| 6| 7| 8|
 *		 -- -- -- --
 *		| 9|10|11|12|
 *		 -- -- -- --
 *		|13|14|15|  |
 *		 -- -- -- --
 *
 * As an option, the tiles may be drawn as pieces of an image.  In this
 * case, the size of the puzzle is determined by the image size, and the
 * tile size is the same default size (unless overridden).  The image
 * used is an image in the resource file named "PuzzleImage".  Until the
 * image exporting routines become part of the standard Galaxy package,
 * you may use a different image in one of two ways: either replace the
 * default "Galaxy" image in puzzle.vr or create another resource
 * file containing an image called "PuzzleImage" (see "Options" below
 * for the exact command arguments).
 *
 * Options:
 *
 *	-rows : set number of rows of tiles (default = 4 for numbered tiles,
 *		and whatever is required for images)
 *	-cols : set number of columns of tiles (default = 4 for numbered tiles,
 *		and whatever is required for images)
 *	-image : use the Galaxy image for the tiles
 *	-res <resfile> : use an image named "PuzzleImage" from the specified
 *			 ".vr" resource file
 *	-tilesize : set the default tile height and width (ignored when
 *		    using an image)
 *
 * If you are trying to solve a puzzle with a complicated image, it may
 * be helpful to view the solved puzzle.  This can be accomplished by
 * selecting the "Show Solution" option from the popup menu of the puzzle
 * window.  Under X, mouse button 3 will get you the popup menu.
 *
 * The popup menu also contains an "Exit" option to exit gracefully.
 *
 * $Log: puzzle.c,v $
 * Revision 1.10  1995/07/24  17:53:18  scotth
 * Added 'static' to the definitions of show_notify() and exit_notify() 'cause
 * their prototypes are declared static and the HP compiler warns if the
 * definition doesn't match the prototype. Also changed all references to the
 * Mickey Mouse image to references to the new Galaxy image.
 *
 * Revision 1.9  1995/06/20  14:23:45  chad
 * stopped using RAND_MAX as it isn't correctly defined for sunos
 *
 * Revision 1.8  1994/08/07  20:47:37  chad
 * fixed randomness to be really random
 *
 */

#include <vport.h>		/* for v*HEADER */
#include vstdlibHEADER
#include vtimeHEADER
#include vapplicationHEADER
#include vstartupHEADER
#include vmemHEADER
#include vdialogHEADER
#include veventHEADER
#include vdomainHEADER
#include vdomainitemHEADER
#include vdomainviewHEADER
#include vnoticeHEADER
#include vnumHEADER
#include vimageHEADER
#include vprefHEADER

#define SHUFFLE		4096			/* to randomize board	*/
#define TILE_COLOR	(vcolorCOMPONENT_MAX / 3), (vcolorCOMPONENT_MAX / 3), \
(4 * vcolorCOMPONENT_MAX / 5)	/* blue tile	*/ 

#define	WON1_MSG "You solved the puzzle in "
#define WON2_MSG " moves!  Would you like to play again?"

/*
 * Macros to map a square to a row or column.
 */
#define square_to_row(SQUARE) (SQUARE / puzzle_cols)
#define square_to_col(SQUARE)  (SQUARE % puzzle_cols)

/*
 * Macro to check that a square is slideable.  This translates to
 * checking that the row or column of the square contains the empty square.
 */
#define LEGIT_SQUARE(SQ, ESQ) \
(SQ != ESQ && \
 (((square_to_row(SQ)) == (square_to_row(ESQ))) || \
 ((square_to_col(SQ)) == (square_to_col(ESQ)))))

/*
 * Initial dimension declarations for the actual board.
 */
#define PUZZLE_ROWS	4
#define PUZZLE_COLS	4
#define NUM_SQUARES	(PUZZLE_ROWS * PUZZLE_COLS)
#define TILE_GAP	2
#define GAME_BORDER	3
#define TILE_BEG_COL	GAME_BORDER
#define TILE_BEG_ROW	GAME_BORDER
#define INIT_TILE_H	48
#define INIT_TILE_W	48

/*
 * Each board on the tile is a domain object whose data pointer is set to
 * its tile number (1 to # tiles).  The empty square is tracked separately
 * for efficiency's sake, even though it may also be found by searching the
 * domainObject pointer array for a NULL.  A second board, which is
 * read-only may also be created if the user wishes to view the solved board.
 */
typedef struct {
	vdomainObject	**board;
	int		empty;
} brd_data;

static brd_data	puz_brd,
		solve_brd;

static vdialog	*puz_dialog,			/* puzzle dialog	*/
		*solve_dialog = NULL;		/* solved puzzle dialog	*/

static vcolor	*ts_color,			/* top shadow color	*/
		*bs_color,			/* bottom shadow color	*/
		*tile_color;			/* tile color		*/

static vcolorSpec				/* internal color format*/
		*tile_spec;

static vnotice	*confirm = NULL;		/* confirmation on quit	*/

/*
 * Variables to hold board dimensions.  If using an image, we need to
 * remember the original board width and height to facilitate scaling if
 * the user resizes the board.
 */
static int	tile_height = INIT_TILE_H,
		tile_width = INIT_TILE_W,
		puzzle_rows = PUZZLE_ROWS,
		puzzle_cols = PUZZLE_COLS,
		orig_height,
		orig_width,
		num_squares,
		image_height;

static unsigned	move_cnt = 0;			/* move counter		*/

static vbool	use_image = FALSE;		/* image or numbers?	*/

static vimage	*puz_image = NULL;		/* image to use		*/

static vresource	res;			/* resource pointer	*/

static vdomainitemClass	*puzzleItemClass;
					/* override vdialogSET_ITEM_RECT*/

/*
 * Forward declarations.
 */
static void puz_notify(vdialog *dialog, vevent *event);
static void draw_tile(vdomainview *domainView, vdomainObject *object);
static void draw_tileimage(vdomainview *domainView, vdomainObject *object);
static void select_tile(vdomainview *domainView, vdomainObject *object);
static void dummy_solve(vdomainview *domainView, vdomainObject *object);
static void init_board(vdomain *domain);
static void reset_board(vdomain *domain, int shuffle_cnt);
static void move_square(vdomain *domain, unsigned square, unsigned show);
static unsigned	game_won(vdomain *domain);
static void confirm_box(vdialog *dialog, vscribe *scribe,
			vnoticeHookProc yesProc, vnoticeHookProc noProc);
static int done_playing(vnotice *notice, vevent *event);
static int play_again(vnotice *notice, vevent *event);
static void exit_notify(vmenuItem *item, vevent *event);
static void show_notify(vmenuItem *item, vevent *event);
static void sclose_notify(vmenuItem *item, vevent *event);
static void puz_setitemrect(vdomainitem *item, const vrect *r);

#define TMP_BUF_SIZ 32
int main(int argc, char *argv[])
{
    register int	i;
	
    int		argCount;

    vresource	dialres,	/* resource for dialog w/board	*/
    imageres,			/* resource for dialog image	*/
    userres;			/* user's resource file w/image	*/
	
    vdomain		*puz_domain; /* puzzle domain		*/
	
    vdomainitem	*puz_item;	/* puzzle item - the background	*/
	
    vdomainview	*puz_view;	/* view of puzzle domain	*/
	
    vmenu		*puz_menu; /* popup menu from puzzle	*/
	
    vmenuItem	*show_item;	/* show item on menu		*/
	
    vmenuItem	*exit_item;	/* exit item on menu		*/
	
    const vchar	*res_file;	/* name of resource file	*/
	
    const vchar	**argList;	/* argument list		*/
	
    vchar		tmpBuf[TMP_BUF_SIZ];
    /* convert numbers from arg list*/
	
    /*
     * Initialize the toolkit
     */
    vstartup(argc, argv);
	
    /*
     * Reseed the number generator
     */
    srand((unsigned int)vtimestampGetSeconds(vtimestampGetNow()));
	
    /*
     * Process any comamnd-line arguments
     */
    res = vapplicationGetResources(vapplicationGetCurrent());
    res_file = NULL;
    vprefGetArgs(&argCount, &argList);
	
    while (--argCount) {
	argList++;
	tmpBuf[TMP_BUF_SIZ - 1] = 0;
	vcharCopyScribedBounded(vcharScribeLiteral("-image"), tmpBuf,
				TMP_BUF_SIZ - 1);
	if (vcharCompare(*argList, tmpBuf) == 0) {
	    use_image = TRUE;
	    continue;
	}
	vcharCopyScribedBounded(vcharScribeLiteral("-rows"), tmpBuf,
				TMP_BUF_SIZ - 1);
	if (vcharCompare(*argList, tmpBuf) == 0) {
	    --argCount;
	    (void) vcharCopyFromSystem(*++argList, tmpBuf);
	    if ((i = vnumParseInt(tmpBuf, NULL)) >= 2)
		puzzle_rows = i;
	    continue;
	}
	vcharCopyScribedBounded(vcharScribeLiteral("-cols"), tmpBuf,
				TMP_BUF_SIZ - 1);
	if (vcharCompare(*argList, tmpBuf) == 0) {
	    --argCount;
	    (void) vcharCopyFromSystem(*++argList, tmpBuf);
	    if ((i = vnumParseInt(tmpBuf, NULL)) >= 2)
		puzzle_cols = i;
	    continue;
	}
	vcharCopyScribedBounded(vcharScribeLiteral("-tilesize"), tmpBuf,
				TMP_BUF_SIZ - 1);
	if (vcharCompare(*argList, tmpBuf) == 0) {
	    --argCount;
	    (void) vcharCopyFromSystem(*++argList, tmpBuf);
	    tile_width = tile_height = vnumParseInt(tmpBuf, NULL);
	    continue;
	}
	vcharCopyScribedBounded(vcharScribeLiteral("-res"), tmpBuf,
				TMP_BUF_SIZ - 1);
	if (vcharCompare(*argList, tmpBuf) == 0) {
	    --argCount;
	    res_file = *++argList;
	    use_image = TRUE;
	    continue;
	}
    }
	
    /*
     * if the user specified a resource file with a different
     * "PuzzleImage" resource, get the image from there instead.
     */
    userres = vresourceNULL;
    if (res_file) {
	vfsPath	*tmp_path;

	tmp_path = vfsPathFromStrScribed(vcharScribe(res_file));
	userres = vresourceOpenFile(tmp_path, vfsOPEN_READ_ONLY);
	vfsDestroyPath(tmp_path);
    }
	
    /*
     * Override the set item rect method so we can reset tile sizes
     * on dialog resizes.
     */
    puzzleItemClass = vclassReproduce(vdomainitemGetDefaultClass());
    vclassSetName(puzzleItemClass, vnameInternGlobalLiteral("puzzleItem"));
    vclassSet(puzzleItemClass, vdialogSET_ITEM_RECT,
	      puz_setitemrect);
	
    /*
     * Locate and load the dialog containing the puzzle board.
     */
    dialres = vresourceGet(res, vnameInternGlobalLiteral("PuzzleDialog"));
    puz_dialog = vdialogLoad(dialres);
    vdialogSetNotify(puz_dialog, puz_notify);
	
	
    /*
     * If using an image, load it now.
     */
    if (use_image) {
	imageres = vresourceGet(userres ? userres : res,
				vnameInternGlobalLiteral("PuzzleImage"));
	puz_image = vimageLoad(imageres);
	image_height = vimageGetHeight(puz_image);
	tile_height = image_height / puzzle_rows;
	tile_width = vimageGetWidth(puz_image) / puzzle_cols;
	orig_width = tile_width;
	orig_height = tile_height;
    }
    num_squares = puzzle_rows * puzzle_cols;
	
    /*
     * Set the initial dialog size.
     */
    vdialogResize(puz_dialog,
		  (tile_width * puzzle_cols) + ((puzzle_cols - 1) * TILE_GAP) +
		  (2 * GAME_BORDER) + 4,
		  (tile_height * puzzle_rows) + ((puzzle_rows-1) * TILE_GAP) +
		  (2 * GAME_BORDER) + 4);
	
    /*
     * Get the domain item and set it up.  Hang a pointer to the board
     * structure off the domain.
     */
    puz_item = (vdomainitem *)
	vdialogFindItem(puz_dialog, vnameInternGlobalLiteral("PuzzleBoard"));
    puz_view = vdomainitemGetView(puz_item);
    puz_domain = vdomainitemGetDomain(puz_item);
    vdomainSetData(puz_domain, (void *) &puz_brd);
    puz_brd.board =
	(vdomainObject **) vmemAlloc(num_squares * sizeof(vdomainObject *));
    solve_brd.board = NULL;
    vdomainviewSetDrawObjectProc(puz_view,
				 use_image ? draw_tileimage : draw_tile);
    vdomainviewSetDrawSelectionProc(puz_view, select_tile);
    vdomainviewSetSingleSelection(puz_view, TRUE);
    vdomainviewSetDragProhibited(puz_view, TRUE);
    ts_color = vdialogDetermineItemColor(vdomainitemGetItem(puz_item),
					 vdrawCOLOR_SHADOW_TOP),
    bs_color = vdialogDetermineItemColor(vdomainitemGetItem(puz_item),
					 vdrawCOLOR_SHADOW_BOTTOM),
    tile_spec = vcolorCreateSpec();
    vcolorSetSpecRGB(tile_spec, TILE_COLOR);
    tile_color = vcolorInternSpec(tile_spec);
	
    /*
     * Set up the popup menu.
     */
    puz_menu = (vmenu *)
	vdialogGetItemMenu(vdomainitemGetItem(puz_item));
    show_item = vmenuFindItem(puz_menu, vnameInternGlobalLiteral("MenShow"));
    exit_item = vmenuFindItem(puz_menu, vnameInternGlobalLiteral("MenExit"));
    vmenuSetItemNotify(show_item, show_notify);
    vmenuSetItemNotify(exit_item, exit_notify);
	
    /*
     * Initialize the board for a new game.
     */
    init_board(puz_domain);
    reset_board(puz_domain, SHUFFLE);
	
    /*
     * Display the dialog.
     */
    vdialogOpen(puz_dialog);
	
    /*
     * Process events as they happen.
     */
    veventProcess();
    vdialogDestroy(puz_dialog);
    vmemFree(puz_brd.board);
    if (solve_dialog)
	vdialogDestroy(solve_dialog);
    if (solve_brd.board)
	vmemFree(solve_brd.board);
    vcolorDestroySpec(tile_spec);
    if (puz_image)
	vimageDestroy(puz_image);
    if (confirm)
	vnoticeDestroy(confirm);
	
    exit(EXIT_SUCCESS);
    return EXIT_FAILURE;
}

/*
 * Handle an event on the main window.
 */
static void puz_notify(vdialog *dialog, vevent *event)
{
    if (veventIsClose(event))
	veventStopProcessing();
    return;
}

/*
 * Override function for our subclass on vdialogSET_ITEM_RECT.  This
 * will get called if the dialog item changes size, due to the
 * dialog being resized.
 */
static void puz_setitemrect(vdomainitem *item, const vrect *r)
{
    /*
     * First call the default SET_ITEM_RECT procedure gor generic
     * domain items.
     */
    vclassSendSuper(puzzleItemClass, vdialogSET_ITEM_RECT, (item, r));

    /*
     * Recalculate the bounds on all the domain objects and force
     * them to be redrawn.
     */
    tile_width = (vdialogGetItemW(vdomainitemGetItem(item)) -
		  ((puzzle_cols - 1) * TILE_GAP) - (2 * GAME_BORDER) - 4) /
		      puzzle_cols;
    tile_height = (vdialogGetItemH(vdomainitemGetItem(item)) -
		   ((puzzle_rows - 1) * TILE_GAP) - (2 * GAME_BORDER) - 4) /
		       puzzle_rows;
    reset_board(vdomainitemGetDomain(item), 0);
    vdomainviewInval(vdomainitemGetView(item));
    if (vdialogDetermineItemDialog(vdomainitemGetItem(item)) == puz_dialog
	&& solve_dialog != NULL)
	vdialogResize(solve_dialog,
		      (tile_width * puzzle_cols)  +
		      ((puzzle_cols - 1) * TILE_GAP) + (2 * GAME_BORDER) + 4,
		      (tile_height * puzzle_rows) +
		      ((puzzle_rows - 1) * TILE_GAP) + (2 * GAME_BORDER) + 4);
    return;
}

/*
 * Domain draw procedure if using numbered tiles.
 */
static void draw_tile(vdomainview *domainView, vdomainObject *object)
{
    /*
     * Draw a color 3-D rectangle and draw a number in the middle.
     */
    vdrawRectsHiliteFillInside(vdomainGetObjectBounds(
						      vdomainviewGetDomain(domainView), object), 1, tile_color,
			       ts_color, bs_color);
    vdrawScribedRectShowCenter(
			       vnumScribeInt((int) vdomainGetObjectData(vdomainviewGetDomain(
											     domainView), object)),
			       vdomainGetObjectBounds(
						      vdomainviewGetDomain(domainView), object));
    return;
}

/*
 * Domain draw procedure if using an image.  Basically this involves
 * copying the appropriate rectangle from the source image to the
 * bounds of the domain object.  Note the image y axis goes in an upward
 * direction!  Also note scaling happens automatically if the source
 * and destination rectangles differ in size.
 */
static void draw_tileimage(vdomainview *domainView, vdomainObject *object)
{
    register int	i;

    vrect		src_rect;

    i = (int) vdomainGetObjectData(
				   vdomainviewGetDomain(domainView), object) - 1;
    src_rect.w = orig_width;
    src_rect.h = orig_height;
    src_rect.x = (i % puzzle_cols) * orig_width;
    src_rect.y = image_height - ((i / puzzle_cols) + 1) * orig_height;
    vdrawRectImage(puz_image, &src_rect, 
		   vdomainGetObjectBounds(vdomainviewGetDomain(domainView), object));
    return;
}

/*
 * Domain object select procedure.  This could either be unselection
 * of the previously selected item (since we are using single slection)
 * or selection of the currently clicked on object.
 */
static void select_tile(vdomainview *domainView, vdomainObject *object)
{
    register int	i;

    vdialog		*dialog;

    brd_data	*bdata;

    vdomainObject	**brd_ptr;

    vstr		*msg;

    /*
     * If this is an unselect notify, just return.
     */
    if (!vdomainIsObjectSelected(vdomainviewGetDomain(domainView),
				 vdomainviewGetSelection(domainView), object))
	return;
    vdomainUnselectObjects(vdomainviewGetDomain(domainView),
			   vdomainviewGetSelection(domainView), vdomainObjectToSet(object));

    /*
     * Match the clicked-on domain object pointer to its slot in the
     * table.  If the square is illegal, beep.  Otherwise, make the
     * move and see if the game is over.  If so, put up a confirmation
     * box, and either exit or start a new game.
     */
    bdata = (brd_data *) vdomainGetData(vdomainviewGetDomain(domainView));
    brd_ptr = bdata -> board;
    for (i = 0; i < num_squares; i++, brd_ptr++) {
	if (*brd_ptr != object)
	    continue;
	if (LEGIT_SQUARE(i, bdata -> empty)) {
	    move_square(vdomainviewGetDomain(domainView), i, TRUE);
	    move_cnt++;
	    if (game_won(vdomainviewGetDomain(domainView))) {
		vwindowBeep();
		msg = vstrCopyMultiScribed(
					   vcharScribeLiteral(WON1_MSG),
					   vnumScribeInt(move_cnt),
					   vcharScribeLiteral(WON2_MSG),
					   NULL,
					   NULL);
		dialog = vdialogDetermineItemDialog(
						    vdomainviewGetItem(domainView));
		confirm_box(dialog, vstrScribe(msg),
			    play_again, done_playing);
	    }
	}
	else
	    vwindowBeep();
	break;
    }
    return;
}

/*
 * Dummy select routine for dialog which shows solved puzzle.
 */
static void dummy_solve(vdomainview *domainView, vdomainObject *object)
{
    return;
}

/*
 * init_board() - Allocate the domain items for the board.
 */
static void init_board(vdomain *domain)
{

    register int	i,
    j;

    brd_data	*bdata;

    vdomainObject	*object,
    **brd_ptr; 

    /*
     * Add the puzzle tiles to the domain.  Set each item's data
     * pointer to contain its number to be drawn.
     */
    bdata = (brd_data *) vdomainGetData(domain);
    brd_ptr = bdata -> board;
    for (i = puzzle_rows - 1; i >= 0; --i) {
	for (j = 0; j < puzzle_cols; j++) {
	    if (j == puzzle_cols - 1 && i == 0)
		continue;
	    object = vdomainAddObject(domain);
	    vdomainSetObjectData(domain,
				 vdomainObjectToSet(object),
				 (void *) (((puzzle_rows - 1 - i) * puzzle_cols) +
					   j + 1));
	    brd_ptr[((puzzle_rows - 1 - i) * puzzle_cols) + j] =
		object;
	}
    }
    bdata -> empty = num_squares - 1;
    brd_ptr[num_squares - 1] = NULL;
    return;
}

/*
 * reset_board() - Randomize the board by starting with the solved
 *		  puzzle and "unsolving" it by shuffle_cnt attempted
 *		  moves, of which only the legal ones are done.
 */
static void	reset_board(vdomain *domain, int shuffle_cnt)
{
    register unsigned
	square;			/* random square	*/

    register int	i;

    int		j;

    vdomainObject	*object,
    **brd_ptr;

    vdomainObjectSet
	*objectSet;

    brd_data	*bdata;

    vrect		tile_rect;

    move_cnt = 0;

    /*
     * Do the moves.
     */
    bdata = (brd_data *) vdomainGetData(domain);
    brd_ptr = bdata -> board;
    for (i = 0; i < shuffle_cnt; i++)
    {
	do {
	    square = rand() % num_squares;
	    vdebugMInform(("%d %d %d %d\n",
			   square, num_squares, i, shuffle_cnt));
	} while (!LEGIT_SQUARE(square, bdata -> empty));
	move_square(domain, square, FALSE);
    }

    /*
     * Set the domain items bounds based on their new positions.
     */
    objectSet = vdomainCreateObjectSet(NULL);
    vrectSet(0, 0, tile_width, tile_height, &tile_rect);
    for (i = puzzle_rows - 1; i >= 0; --i) {
	for (j = 0; j < puzzle_cols; j++) {
	    object = *brd_ptr++;
	    if (!object)
		continue;
	    tile_rect.x = GAME_BORDER +
		j * (tile_width + TILE_GAP);
	    tile_rect.y = GAME_BORDER +
		i * (tile_height + TILE_GAP);
	    vdomainSetObjectBounds(domain,
				   vdomainObjectToSet(object), &tile_rect);
	    vdomainAddToObjectSet(&objectSet, object);
	}
    }
    vdomainShowObjects(domain, objectSet);
    vdomainDestroyObjectSet(objectSet);
    return;
}

/*
 * move_square() - Recalculate the board based on the selected square.
 *		   Only show the result if requested to do so (when
 *		   initializing the board, this routine could get called
 *		   several thousand times, so we don't want to show
 *		   all of this movement).
 */
static void	move_square(vdomain *domain, register unsigned square,
			    unsigned show)
{
    register int	i,
    empty_square;

    register 	vdomainObject **brd_ptr;

    brd_data	*bdata;

    vdomainObjectSet
	*objectSet;

    bdata = (brd_data *) vdomainGetData(domain);
    brd_ptr = bdata -> board;
    empty_square = bdata -> empty;
    if (show)
	objectSet = vdomainCreateObjectSet(NULL);

    /*
     * The direction of the move is obvious from the location
     * of the empty square relative to the target square.
     */
    if ((square_to_col(square)) == (square_to_col(empty_square))) {
	/*
	 * Squares are in same column
	 */
	if (square < empty_square) {
	    /*
	     * Slide tile(s) down
	     */
	    for (i = empty_square; i > square; i -= puzzle_cols) {
		if (show)
		    vdomainAddToObjectSet(&objectSet,
					  brd_ptr[i - puzzle_cols]);
		brd_ptr[i] = brd_ptr[i - puzzle_cols];
	    }
	    if (show)
		vdomainMoveObjects(domain, objectSet, 0,
				   -(tile_height + TILE_GAP), vdomainRELATIVE);
	} else {
	    /*
	     * Slide tile(s) up
	     */
	    for (i = empty_square; i < square; i += puzzle_cols) {
		if (show)
		    vdomainAddToObjectSet(&objectSet,
					  brd_ptr[i + puzzle_cols]);
		brd_ptr[i] = brd_ptr[i + puzzle_cols];
	    }
	    if (show)
		vdomainMoveObjects(domain, objectSet, 0,
				   tile_height + TILE_GAP, vdomainRELATIVE);
	}
    } else {
	/*
	 * Squares are in same row
	 */
	if (square < empty_square) {
	    /*
	     * Slide tiles right
	     */
	    for (i = empty_square; i > square; --i) {
		if (show) {
		    vdomainAddToObjectSet(&objectSet,
					  brd_ptr[i - 1]);
		}
		brd_ptr[i] = brd_ptr[i - 1];
	    }
	    if (show)
		vdomainMoveObjects(domain, objectSet,
				   tile_width + TILE_GAP, 0,
				   vdomainRELATIVE);
	} else {
	    /*
	     * Slide tiles left
	     */
	    for (i = empty_square; i < square; i++) {
		if (show) {
		    vdomainAddToObjectSet(&objectSet,
					  brd_ptr[i + 1]);
		}
		brd_ptr[i] = brd_ptr[i + 1];
	    }
	    if (show)
		vdomainMoveObjects(domain, objectSet,
				   -(tile_width + TILE_GAP), 0,
				   vdomainRELATIVE);
	}
    }

    /*
     * Update the empty square.
     */
    bdata->empty = square;
    brd_ptr[square] = NULL;
    if (show)
	vdomainDestroyObjectSet(objectSet);
    return;
}

/*
 * game_won() - Check if the board is in the solved configuration.
 */
static unsigned	game_won(vdomain *domain)
{
    register vdomainObject	**brd_ptr; /* ptr to a tile	*/

    register int		i;

    brd_data		*bdata;


    bdata = (brd_data *) vdomainGetData(domain);
    brd_ptr = bdata -> board;
    if (brd_ptr[num_squares - 1])
	return FALSE;
    for (i = 1; i < num_squares; i++)
	if ((int) vdomainGetObjectData(domain, *brd_ptr++) != i)
	    return FALSE;
    return TRUE;
}

/*
 * The puzzle has been solved.  See if the user wants to play again.
 */
static void confirm_box(vdialog *dialog, vscribe *scribe,
			vnoticeHookProc yesProc, vnoticeHookProc noProc)
{
    if (confirm == NULL) {
	confirm = vnoticeCreate();
	vnoticeSetCaution(confirm, TRUE);
	vnoticeSetYesHook(confirm, yesProc);
	vnoticeSetNoHook(confirm, noProc);
	if (dialog != NULL)
	    vnoticeSetData(confirm,
			   vdialogFindItem(dialog,
					   vnameInternGlobalLiteral("PuzzleBoard")));
    }
    vnoticeSetTextScribed(confirm, scribe);

    if (dialog != NULL) {
	vnoticePlace(confirm, dialog,
		     vrectPLACE_RIGHT  | vrectPLACE_NEAR,
		     vrectPLACE_CENTER | vrectPLACE_NEAR);
	vwindowSetLeader(vnoticeGetWindow(confirm),
			 vdialogGetWindow(dialog));
    }
    vnoticeOpen(confirm);
    return;
}

/*
 * Confirmation handler if user does not want to play again.
 */
static int done_playing(vnotice *notice, vevent *event)
{
    veventStopProcessing();
    return TRUE;
}

/*
 * Confirmation handler if user wants to play again.
 */
static int play_again(vnotice *notice, vevent *event)
{
    vdomainitem	*domItem;

    vdomain		*domain;

    domItem = (vdomainitem *) vnoticeGetData(notice);
    domain = vdomainitemGetDomain(domItem);
    if (domain)
	reset_board(domain, SHUFFLE);
    return TRUE;
}

/*
 * If the exit menu item is chosen, shut down.
 */
static void exit_notify(vmenuItem *item, vevent *event)
{
    veventStopProcessing();
    return;
}

/*
 * Close the shown solution dialog.
 */
static void sclose_notify(vmenuItem *item, vevent *event)
{
    vdialogClose((vdialog *) vmenuGetItemData(item));
    return;
}

/*
 * Show the solved puzzle.  We rig up a new domain and show an unshuffled
 * puzzle.
 */
static void show_notify(vmenuItem *item, vevent *event)
{
    vdomain			*solve_domain;

    vdomainitem		*solve_item;

    vdomainview		*solve_view;

    vwindow			*solve_win;

    vmenu			*solve_menu;

    vmenuItem		*close_item;

    vresource		solve_res;

    if (!solve_dialog) {
	solve_res = vresourceGet(res, vnameInternGlobalLiteral("SolveDialog"));
	solve_dialog = vdialogLoad(solve_res);
	vdialogResize(solve_dialog,
		      (tile_width * puzzle_cols)  +
		      ((puzzle_cols - 1) * TILE_GAP) + (2 * GAME_BORDER) + 4,
		      (tile_height * puzzle_rows) +
		      ((puzzle_rows - 1) * TILE_GAP) + (2 * GAME_BORDER) + 4);
	solve_item = (vdomainitem *)
	    vdialogFindItem(solve_dialog,
			    vnameInternGlobalLiteral("SolveBoard"));

	/*
	 * Set up the popup menu.
	 */
	solve_menu = (vmenu *)
	    vdialogGetItemMenu(vdomainitemGetItem(solve_item));
	close_item = vmenuFindItem(solve_menu, 
				   vnameInternGlobalLiteral("SolveClose"));
	vmenuSetItemNotify(close_item, sclose_notify);
	vmenuSetItemData(close_item, (void *) solve_dialog);

	solve_view = vdomainitemGetView(solve_item);
	solve_domain = vdomainitemGetDomain(solve_item);
	vdomainviewSetDrawObjectProc(solve_view,
				     use_image ? draw_tileimage : draw_tile);
	vdomainviewSetDrawSelectionProc(solve_view, dummy_solve);
	vdomainviewSetSingleSelection(solve_view, TRUE);
	vdomainviewSetDragProhibited(solve_view, TRUE);
	vdomainSetData(solve_domain, (void *) &solve_brd);
	solve_brd.board =
	    (vdomainObject **)
		vmemAlloc(num_squares * sizeof(vdomainObject *));
	init_board(solve_domain);
	reset_board(solve_domain, 0);
    }
    if (vdialogIsOpen(solve_dialog)) {
	solve_win = vdialogGetWindow(solve_dialog);
	vwindowUniconify(solve_win);
	vwindowRaise(solve_win);
    } else {
	vdialogPlace(solve_dialog, puz_dialog, 
		     vrectPLACE_RIGHT  | vrectPLACE_NEAR, vrectPLACE_CENTER);
	vdialogOpen(solve_dialog);
    }
    return;
}
