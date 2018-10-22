/*========================================================================
 *
 * File:      $RCSfile: u_dumper.cc,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:58 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
// Test case
#include <mc_dbms/mc_dbms.hh>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/param.h>
#include <sys/types.h>


#include "d_invoct.hh"
#include "d_domain.hh"
#include "d_dd_sam.hh"
#include "m_dd.hh"
#include "m_ce/m_rect.hh"
#include "m_ce/m_pntwin.hh"
#include "m_ce/m_lincon.hh"
#include "ce_glue/ce_psglu.hh"
#include "u_dumper.hh"

void dump_special1()
{
	special_dumper();
}

void special_dumper()
{
  Domain *domain_ptr;
  Domain_id domain_id = Invocation::get_current_domain_id();
  mc_dbms_database *dbase_ptr = domain_id->get_db_ptr();
  mc_dbms_database_root *root_ptr = dbase_ptr->find_root( Domain::DOMAIN_ROOT );
  domain_ptr = ( Domain * ) root_ptr->get_value();
  printf("domain_ptr = %#xx\n", domain_ptr);
  dump_core(domain_ptr, sizeof(Domain), "Domain");

  D_dd_srm_scm_sam *dd_ptr = 0;
  float n;
  FOR_ALL_ELEMENTS( dd_ptr,
                    D_dd_srm_scm_sam,
                    domain_ptr->get_dd_coll_ptr(),
                    cursor )
    {
      n = dd_ptr->version_tag().get_version_num();
      printf("  dd_ptr = %#xx, version_num = %.2f\n", dd_ptr, n);
      dump_core(dd_ptr, sizeof(D_dd_srm_scm_sam), "D_dd_srm_scm_sam");

      M_dd *m_dd_ptr = dd_ptr->get_dd_ptr();
      printf("    m_dd_ptr = %#xx\n", m_dd_ptr);
      dump_core(m_dd_ptr, sizeof(M_dd), "M_dd");

      M_model *m_model_ptr = (M_model *)m_dd_ptr;       // supertype of M_dd
      printf("      m_model_ptr = %#xx\n", m_model_ptr);
      dump_core(m_model_ptr, sizeof(M_model), "M_model");

      CE_persistent_glue*	persistent_glue_ptr =
        m_dd_ptr->get_persistent_glue_ptr();
      printf("        persistent_glue_ptr = %#xx\n", persistent_glue_ptr);
      dump_core(persistent_glue_ptr, sizeof(CE_persistent_glue), "CE_persistent_glue");

      M_Paint_Window *m_pw_ptr =
        persistent_glue_ptr->Get_M_pw_ptr();
      printf("          m_pw_ptr = %#xx\n", m_pw_ptr);
      dump_core(m_pw_ptr, sizeof(M_Paint_Window), "M_Paint_Window");

      M_Graphical_Element *persis_ge = m_pw_ptr->Get_head( 0 );
      printf("            persis_ge = %#xx\n", persis_ge);
      dump_core(persis_ge, sizeof(M_Graphical_Element), "M_Graphical_Element");

      while (persis_ge != 0) {
          Graphical_Element::GE_Type ge_type =
            persis_ge->get_type();
          printf ("            after persis_ge->get_type()\n");

          char *type = "UNKNOWN TYPE";
          M_Connector      *m_conn_ptr = 0;
          M_Line_con       *m_lncn_ptr = 0;
          M_Shape          *m_shap_ptr = 0;
          M_Ellipse        *m_elli_ptr = 0;
          M_Flattened_Oval *m_oval_ptr = 0;
          M_Rectangle      *m_rect_ptr = 0;

          // Break out type for tracing only
          switch (ge_type)
            {
            case Graphical_Element::SHAPE:
              type = "SHAPE";
              break;
            case Graphical_Element::CONNECTOR:
              type = "CONNECTOR";
              break;
            case Graphical_Element::BOUNDING_BOX:
              type = "BOUNDING_BOX";
              break;
            }
          printf("              ge_type = %s\n", type);

          char *shape_type_str = "UNKNOWN";
          Shape	*ge;
          switch (ge_type)
            {
            case Graphical_Element::SHAPE:
              {
                M_Shape	*p_shape = (M_Shape *) persis_ge;
                printf("              p_shape = %#xx\n", p_shape);
                dump_core(p_shape, sizeof(M_Shape), "M_Shape");

                Shape::Shape_type shape_type = p_shape->Get_shape_type();	 
                printf("              after p_shape->Get_shape_type()\n");

                // Break out type for tracing only
                switch ( shape_type )
                  {
                  case Shape::CE_RECTANGLE:
                    shape_type_str = "RECTANGLE";
                    break;
                  case Shape::CE_ELLIPSE:
                    shape_type_str = "ELLIPSE";
                    break;
                  case Shape::CE_FLATTENED_OVAL:
                    shape_type_str = "OVAL";
                    break;
                  }
                printf("              shape_type = %s\n", shape_type_str);

                switch ( shape_type )
                  {
                  case Shape::CE_RECTANGLE:
                    {
                      m_rect_ptr = (M_Rectangle *) persis_ge;
                      dump_core(m_rect_ptr, sizeof(M_Rectangle), "M_Rectangle");

                      M_Line_con *m_lc_ptr = m_rect_ptr->Gethostconn();
                      printf("                m_lc_ptr = %#xx\n", m_lc_ptr);
                      dump_core(m_lc_ptr, sizeof(M_Line_con), "M_Line_con");
                    } 
                    break;
                  case Shape::CE_ELLIPSE:
                    m_elli_ptr = (M_Ellipse *) persis_ge;
                    break;
                  case Shape::CE_FLATTENED_OVAL:
                    m_oval_ptr = (M_Flattened_Oval *) persis_ge;
                    break;
                  }
              }
              break;
            case Graphical_Element::CONNECTOR:
              m_conn_ptr = persis_ge->get_M_Connector_ptr();
              break;
            case Graphical_Element::BOUNDING_BOX:
              m_rect_ptr = persis_ge->get_M_Rectangle_ptr();
              break;
            }

          // M_Line_con       *m_lncn_ptr = persis_ge->get_M_Line_con_ptr();
          // M_Ellipse        *m_elli_ptr = persis_ge->get_M_Ellipse_ptr();
          // M_Flattened_Oval *m_oval_ptr = persis_ge->get_M_Flattened_Oval_ptr();

          printf("              m_conn_ptr = %#xx\n", m_conn_ptr);
          printf("              m_lncn_ptr = %#xx\n", m_lncn_ptr);
          printf("              m_shap_ptr = %#xx\n", m_shap_ptr);
          printf("              m_elli_ptr = %#xx\n", m_elli_ptr);
          printf("              m_oval_ptr = %#xx\n", m_oval_ptr);
          printf("              m_rect_ptr = %#xx\n", m_rect_ptr);

          persis_ge = persis_ge->get_next(M_Graphical_Element::P_NORMAL);
          printf("            persis_ge = %#xx\n", persis_ge);
        }
    }
}

void dump_core(void *mem, int size, const char *tag, const char *indent)
{
  if (!tag)
    tag="";
  if (!indent)
    indent = "  ";
  printf("%s:\n", tag);
  if (!mem)
    {
      printf("  zero pointer\n");
      fflush(stdout);
      return;
    }
  unsigned int value;
  int m1 = 4;
  int c1 = m1;
  char *s1 = " ";
  int m2 = 4;
  int c2 = m2;
  char *s2 = "  ";
  int m3 = 1;
  int c3 = m3;
  char *s3 = "\n";

  unsigned char *mem_char = (unsigned char *)mem;
  int printed = 0;

  for(int i=0; i<size; i++)
    {
      printed = 1;
      if ( (c1 == m1 ) && (c2 == m2) && (c3 == m3))
        {
          printf("%s%.8X  ", indent, mem);
          fflush(stdout);
        }
      value = (int)(*mem_char++);
      printf("%.2X", value);
      fflush(stdout);
      if (!--c1)
        {
          printf("%s", s1);
          fflush(stdout);
          c1 = m1;
          if (!--c2)
            {
              printf("%s", s2);
              fflush(stdout);
              c2 = m2;
              if (!--c3)
                {
                  printf("%s", s3);
                  fflush(stdout);
                  c3 = m3;
                }
            }
        }
    }
  if (printed)
    {
      printf("\n");
      fflush(stdout);
    }
}

          
