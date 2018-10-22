/*========================================================================
 *
 * File:      $RCSfile: r_galp.hh,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:11 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#ifndef		R_GALAXY_PRINT_HH
#define		R_GALAXY_PRINT_HH


#include <d_typdef.hh>

#include <r_lang.hh>
#include <v_subcls.hh>
#include <u_desc.hh>

#include <vdraw.h>
#include <vapplication.h>
#include <vdialog.h>
#include <vcontain.h>
#include <vfont.h>
#include <vpoint.h>


#define MAX_CLIP_DEPTH 3

class String;

class RL_GalaxyPrint : public RL_Render_Language

{
public:
  virtual RL_GalaxyPrint*	get_RL_GalaxyPrint_ptr () { return this; }


  enum { POINTS_PER_INCH = 72 };


	RL_GalaxyPrint (vprint* printer,
                  int p_poster_rows = 1, int p_poster_columns = 1,
                  t_boolean p_scale_to_poster_edges = TRUE,
                  float p_left_margin_inches = 1.0,
                  float p_right_margin_inches = 1.0,
                  float p_top_margin_inches = 1.0,
                  float p_bottom_margin_inches = 1.0);

  virtual		~RL_GalaxyPrint ();
    
  double ComputeRowCol ( int zoom_font_size, int& num_rows, int& num_cols );

  static void		init ();

  static t_boolean openDocument(vprint* printer, String &error_msg);
	static void closeDocument(vprint* printer);

  static void  print_text(vprint* volatile, const char *);
	    
  virtual t_boolean prepare_to_render (const vchar*,
                                       t_render_mode,
                                       String &p_error_msg);

  void start_page ( int row_num, int col_num, double scale );

  t_boolean cleanup_on_exception(String &error_msg);

  virtual void	done_rendering
    (t_render_mode = RL_Render_Language::NONE);
			

  virtual void RL_Rectangle (int, int, int, int, t_class_type,
                             Stroke_Fill_Option = STROKE_FILL);
  virtual void RL_Rounded_Rectangle (int x, int y, int w, int h,
                                     int radius, t_class_type type,
                                     Stroke_Fill_Option = STROKE_FILL);

  virtual void	RL_String (int, int, const vchar*,
                           t_boolean p_connector,
                           t_uint p_type,
                           t_boolean underline = FALSE);
  virtual void	RL_Line (int, int, int, int, t_boolean = TRUE);
  virtual void	RL_Polygon (RL_Point*, int, t_class_type,
                            Stroke_Fill_Option = NO_STROKE_OR_FILL);
  virtual void	RL_Arc (int, int, int, int, int, int, int radius, 
                        Stroke_Fill_Option = NO_STROKE_OR_FILL,
                        t_boolean = TRUE);

  virtual void  RL_Set_Dashes (int offset, char* dash_list, int n);
    
  virtual void	RL_Set_GC (int, Line_Style_Option);

  virtual void	RL_Set_Clip_Rectangle (int, int, int, int);
  virtual void	RL_Clear_Clip_Rectangle ();
    
  virtual void	RL_Set_BGColor (vcolor *color)
    { BGColor = color; }
  virtual void	RL_Set_FGColor (vcolor *color)
    { FGColor = color; }
  

private:

  // helper functions
	void output_title (const vchar* p_title);

  // transformation determination functions

  void determine_transform(int row_num, int col_num, double p_scale);
  t_boolean need_to_scale();
  t_boolean poster_print();
  void landscape_center_and_no_scale(double);
  void landscape_center_and_scale(double);
  void portrait_center_and_no_scale(double);
  void portrait_center_and_scale(double);

  void		preDraw (void);
    
  vprint*     printer;

  const vdialogItem*	item;
  int             	lineWidth;
  vcolor*		FGColor;
  vcolor*		BGColor;
  vrect*		crect;
  int			draw_function;

  vrect*		clip_rect[MAX_CLIP_DEPTH];
	int			clip_depth;

  Line_Style_Option	current_style;

  float		dash_pat[10];
  double		dash_offset;
  int			dash_size;

  t_boolean scaling_pass;
	t_paper_orientation orientation;

  Description page_title;

	float left_margin;
	float right_margin;
	float top_margin;
	float bottom_margin;

	float paper_width;
	float paper_height;

	float total_paper_width;
	float total_paper_height;

	float canvas_width;
	float canvas_height;

  float indent_from_left_margin;
  float indent_from_right_margin;
  float indent_from_top_margin;
  float indent_from_bottom_margin;

  float scord_min_x;
  float scord_max_x;
  float scord_width;

  float scord_min_y;
  float scord_max_y;
  float scord_height;

  float excess_width;
  float excess_height;

  float scale_factor;

  int poster_rows;
  int poster_columns;

  t_boolean scale_to_poster_edges;

};




#endif


//
// Formatting information for emacs
//
// Local Variables:
// tab-width:2
// End:
//
