/*========================================================================
 *
 * File:      $RCSfile: r_lang.hh,v $
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
#ifndef		R_LANG_HH
#define		R_LANG_HH


#include <d_typdef.hh>
#include <u_typdef.hh>

#include <vchar.h>
#include <vfont.h>

typedef struct {
    short x, y;
} RL_Point;


class RL_Gal;
class RL_PostScript;
class String;


class RL_Render_Language

{
public:
  enum Stroke_Fill_Option
  {
    NO_STROKE_OR_FILL = 0,
    FILL_ONLY = 1,
    STROKE_ONLY = 2,
    STROKE_FILL = 3
  };
  enum Line_Style_Option
  {
    LINESOLID,
    LINEDASHED,
    LINEDOTTED,
    INVISIBLE,
    UNINITIALIZED
  };
  enum Font_Style_Option
  {
    UNASSIGNED,
    NORMAL,
    BOLD,
    ITALIC
  };
  enum t_paper_orientation
  {
    LANDSCAPE,
    PORTRAIT
  };
  enum t_render_language
  {
    GALAXY,
    POSTSCRIPT,
    HPGL
  };
  enum t_render_mode
  {
    NONE,
    COPY,
    XOR
  };
	
  virtual RL_Gal*	get_RL_Gal_ptr () { return 0; }
  virtual RL_PostScript*
    get_RL_PostScript_ptr () { return 0; }


  RL_Render_Language () 
    {
      zoomlevel = 1.0;
      font = 0;
    }
  virtual		~RL_Render_Language () {}
		

  //  IMPORTANT:  When and how prepare_to_render () and done_rendering ()
  //    is critical.  prepare_to_render( ) must be called AFTER the
  //    constructor but BEFORE any specific render function.  The
  //    "p_title" argument is the model title that will label the model.
  //    done_rendering () must be called AFTER all individual render
  //    functions have been called and we are ready to output the
  //    resultant graphic.
  //
  virtual t_boolean prepare_to_render
    (const vchar*, t_render_mode, String &p_error_msg) { return TRUE; }
  virtual void	done_rendering (t_render_mode = NONE) {}
		
  virtual void	RL_Rectangle (int x, int y, int w, int h, t_class_type type,
                              Stroke_Fill_Option = STROKE_FILL) = 0;
  virtual void	RL_Rounded_Rectangle (int x, int y, int w, int h, int radius, t_class_type type,
                                      Stroke_Fill_Option = STROKE_FILL) = 0;
  
  virtual void	RL_String (int x, int y, const vchar* string,
                           t_boolean p_connector, t_uint p_type, t_boolean underline = FALSE) = 0;
  virtual void	RL_Line (int x1, int y1, int x2, int y2, 
                         t_boolean p_stroke = TRUE) = 0; 
  virtual void	RL_Polygon (RL_Point* points, int num_points,
                            t_class_type p_type = (t_class_type)0,
			    Stroke_Fill_Option = NO_STROKE_OR_FILL) = 0;
  virtual void	RL_Arc (int x, int y, int w, int h, int radius,
                        int angle1, int angle2,
                        Stroke_Fill_Option = NO_STROKE_OR_FILL, 
                        t_boolean stroke = TRUE) = 0;

  virtual void	RL_Set_Dashes (int, char*, int) {}
  virtual void	RL_Set_GC (int, Line_Style_Option = LINESOLID) {}
  void	RL_Set_Font (Font_Style_Option, int, t_boolean = TRUE);
  vfont*  RL_Get_Current_Font ();
  
  virtual void	RL_Set_Clip_Rectangle (int, int, int, int) {}
  virtual void	RL_Clear_Clip_Rectangle () {}
  virtual void	RL_Clear_Container (int, int, int, int) {}
	
  double		Zoomlevel () { return zoomlevel; }
  void		Set_zoomlevel (double zz) { zoomlevel = zz; }

protected:

private:
  double zoomlevel;
  vfont* font;
};




#endif
