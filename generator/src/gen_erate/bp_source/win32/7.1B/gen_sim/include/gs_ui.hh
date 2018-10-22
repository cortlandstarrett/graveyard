/*========================================================================
 *
 * File:      $RCSfile: gs_ui.hh,v $
 * Version:   $Revision: 1.10 $
 * Modified:  $Date: 2013/01/10 23:41:18 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#ifndef GS_UI_HH
#define GS_UI_HH

#include <u_typdef.hh>

#include <u_string.hh>
#include <u_desc.hh>



enum t_ui_prompt_response
			    {
			    UI_RESPONSE__NO		= 0x0001,
			    UI_RESPONSE__YES		= 0x0002,
			    UI_RESPONSE__YES_TO_ALL	= 0x0004
			    };

enum t_ui_information_level
			    {
			    UI_INFORM__ERROR		= 0x0001,
			    UI_INFORM__WARNING		= 0x0002,

			    UI_INFORM__SYS		= 0x0010,

			    UI_INFORM__ACTN		= 0x0100,
			    UI_INFORM__STMT		= 0x0200,
			    UI_INFORM__COMP		= 0x0400
			    };




//  Define a macro which causes the level check to happen first
//    which allows all of the information string manipulation to
//    be skipped if information will not be printed anyway.
//

#define GS_UI_INFORM(p_information_level,p_information_str)		\
{									\
    extern t_ui_information_level GS_information_level;			\
    if (p_information_level <= GS_information_level)			\
    {									\
	GS_ui::inform (p_information_level, p_information_str);		\
    }									\
}

//  Define two macros which first do a level check to 
//    skip all processing if information will not be printed anyway.
//
#define GS_UI_INFORM_START(p_information_level)		\
{									\
    extern t_ui_information_level GS_information_level;			\
    if (p_information_level <= GS_information_level)			\
    {									

#define GS_UI_INFORM_END(p_information_level, p_information_str)		\
	GS_ui::inform (p_information_level, p_information_str);		\
    }									\
}






class GS_ui
{
public:
    static void		init (const GS_string& p_log_file_name_str,
			    t_ui_information_level p_ui_information_level
				= UI_INFORM__SYS);

    static void		inform (t_ui_information_level p_information_level,
			    const Description& p_information_str);

    static void		inform (t_ui_information_level p_information_level,
			    const GS_string& p_information_str);

    static t_ui_prompt_response
			prompt (int p_legal_responses,
			    const Description& p_question_str);

    static GS_string	get_name_str ()
			    { return s_name_str; }
			    
    static void		set_name_str (const GS_string& p_name_str);

    static void		reset_line_num (t_uint p_line_num = 0)
			    { s_line_num = p_line_num; }
    static void		increment_line_num ()
			    { s_line_num++; }
    static t_uint	get_line_num ()
			    { return s_line_num; }



private:
    static const char* file_name_ptr ( ) 
                {
    				return s_fileNamePtr;
                }
	
	static void setFileNamePtr() {
        s_fileNamePtr = s_name_str.char_ptr();
    	int len = s_name_str.length();
    	bool done = false;
    	for (int i = len-1; !done && i > 0; --i) {
    		if (s_fileNamePtr [i] == '/' || s_fileNamePtr [i] == '\\' || s_fileNamePtr [i] == ':') {
    			s_fileNamePtr = &s_fileNamePtr[i+1];
    			done = true;
    		}
    	}
	}
    
    static GS_string	s_name_str;
    static t_uint	s_line_num;
    static const char* s_fileNamePtr;
};




#endif
