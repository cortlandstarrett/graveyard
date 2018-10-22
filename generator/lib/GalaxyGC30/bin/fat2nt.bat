@echo off 

@echo "Expanding header file names to long names for NTFS system.       "

if not "%1" == "" goto INSTALL1

@echo "                                                                  "
@echo "ERROR: Invalid Syntax                                             "
@echo "                                                                  "
@echo "    To modify files in same directory:                            "
@echo "        fat2nt <include path>                                     "
@echo "    ex. fat2nt c:\galaxy\include                                "
@echo "                                                                  "
@echo "    To copy and modify header files to a new directory:           "
@echo "        fat2nt <full src path> <full dest path>                   "
@echo "    ex. fat2nt c:\galaxy\include d:\galaxy\include            "

goto END

:INSTALL1
if not "%2" == "" goto COPYINSTALL

cd %1

copy vhdrlong.h vhdrmode.h

if exist vabstrac.h if exist vabstract.h del vabstract.h
if exist vabstrac.h rename vabstrac.h vabstract.h
if exist vaccep_c.h if exist vaccept_c.h del vaccept_c.h
if exist vaccep_c.h rename vaccep_c.h vaccept_c.h
if exist vappfram.h if exist vappframe.h del vappframe.h
if exist vappfram.h rename vappfram.h vappframe.h
if exist vappfr_c.h if exist vappframe_c.h del vappframe_c.h
if exist vappfr_c.h rename vappfr_c.h vappframe_c.h
if exist vapplica.h if exist vapplication.h del vapplication.h
if exist vapplica.h rename vapplica.h vapplication.h
if exist vappli_c.h if exist vapplication_c.h del vapplication_c.h
if exist vappli_c.h rename vappli_c.h vapplication_c.h
if exist vargscra.h if exist vargscrap.h del vargscrap.h
if exist vargscra.h rename vargscra.h vargscrap.h
if exist varpaine.h if exist varpainet.h del varpainet.h
if exist varpaine.h rename varpaine.h varpainet.h
if exist vattribu.h if exist vattribute.h del vattribute.h
if exist vattribu.h rename vattribu.h vattribute.h
if exist vattri_c.h if exist vattribute_c.h del vattribute_c.h
if exist vattri_c.h rename vattri_c.h vattribute_c.h
if exist vboolite.h if exist vboolitem.h del vboolitem.h
if exist vboolite.h rename vboolite.h vboolitem.h
if exist vbooli_c.h if exist vboolitem_c.h del vboolitem_c.h
if exist vbooli_c.h rename vbooli_c.h vboolitem_c.h
if exist vbuffe_c.h if exist vbuffer_c.h del vbuffer_c.h
if exist vbuffe_c.h rename vbuffe_c.h vbuffer_c.h
if exist vbuildst.h if exist vbuildstrs.h del vbuildstrs.h
if exist vbuildst.h rename vbuildst.h vbuildstrs.h
if exist vbuildst.c if exist vbuildstrs.c del vbuildstrs.c
if exist vbuildst.c rename vbuildst.c vbuildstrs.c
if exist vbutto_c.h if exist vbutton_c.h del vbutton_c.h
if exist vbutto_c.h rename vbutto_c.h vbutton_c.h
if exist vcanva_c.h if exist vcanvas_c.h del vcanvas_c.h
if exist vcanva_c.h rename vcanva_c.h vcanvas_c.h
if exist vcharenc.h if exist vcharencoding.h del vcharencoding.h
if exist vcharenc.h rename vcharenc.h vcharencoding.h
if exist vchare_c.h if exist vcharencoding_c.h del vcharencoding_c.h
if exist vchare_c.h rename vchare_c.h vcharencoding_c.h
if exist vclassex.h if exist vclassextra.h del vclassextra.h
if exist vclassex.h rename vclassex.h vclassextra.h
if exist vclassin.h if exist vclassinfo.h del vclassinfo.h
if exist vclassin.h rename vclassin.h vclassinfo.h
if exist vclassre.h if exist vclassreg.h del vclassreg.h
if exist vclassre.h rename vclassre.h vclassreg.h
if exist vclien_c.h if exist vclient_c.h del vclient_c.h
if exist vclien_c.h rename vclien_c.h vclient_c.h
if exist vclipboa.h if exist vclipboard.h del vclipboard.h
if exist vclipboa.h rename vclipboa.h vclipboard.h
if exist vclipb_c.h if exist vclipboard_c.h del vclipboard_c.h
if exist vclipb_c.h rename vclipb_c.h vclipboard_c.h
if exist vcmdch_c.h if exist vcmdchsr_c.h del vcmdchsr_c.h
if exist vcmdch_c.h rename vcmdch_c.h vcmdchsr_c.h
if exist vcolorch.h if exist vcolorchsr.h del vcolorchsr.h
if exist vcolorch.h rename vcolorch.h vcolorchsr.h
if exist vcolch_c.h if exist vcolorchsr_c.h del vcolorchsr_c.h
if exist vcolch_c.h rename vcolch_c.h vcolorchsr_c.h
if exist vcolorsy.h if exist vcolorsys.h del vcolorsys.h
if exist vcolorsy.h rename vcolorsy.h vcolorsys.h
if exist vcombobo.h if exist vcombobox.h del vcombobox.h
if exist vcombobo.h rename vcombobo.h vcombobox.h
if exist vcombx_c.h if exist vcombobox_c.h del vcombobox_c.h
if exist vcombx_c.h rename vcombx_c.h vcombobox_c.h
if exist vcommc_c.h if exist vcommchn_c.h del vcommchn_c.h
if exist vcommc_c.h rename vcommc_c.h vcommchn_c.h
if exist vcomma_c.h if exist vcommand_c.h del vcommand_c.h
if exist vcomma_c.h rename vcomma_c.h vcommand_c.h
if exist vconditi.h if exist vcondition.h del vcondition.h
if exist vconditi.h rename vconditi.h vcondition.h
if exist vconfi_c.h if exist vconfirm_c.h del vconfirm_c.h
if exist vconfi_c.h rename vconfi_c.h vconfirm_c.h
if exist vctrgr_c.h if exist vctrgrid_c.h del vctrgrid_c.h
if exist vctrgr_c.h rename vctrgr_c.h vctrgrid_c.h
if exist vconta_c.h if exist vcontain_c.h del vcontain_c.h
if exist vconta_c.h rename vconta_c.h vcontain_c.h
if exist vcontr_c.h if exist vcontrol_c.h del vcontrol_c.h
if exist vcontr_c.h rename vcontr_c.h vcontrol_c.h
if exist vctlch_c.h if exist vctlchsr_c.h del vctlchsr_c.h
if exist vctlch_c.h rename vctlch_c.h vctlchsr_c.h
if exist vcurso_c.h if exist vcursor_c.h del vcursor_c.h
if exist vcurso_c.h rename vcurso_c.h vcursor_c.h
if exist vdasse_c.h if exist vdasserv_c.h del vdasserv_c.h
if exist vdasse_c.h rename vdasse_c.h vdasserv_c.h
if exist vdschs_c.h if exist vdschsr_c.h del vdschsr_c.h
if exist vdschs_c.h rename vdschs_c.h vdschsr_c.h
if exist vdsdat_c.h if exist vdsdata_c.h del vdsdata_c.h
if exist vdsdat_c.h rename vdsdat_c.h vdsdata_c.h
if exist vdsdbe_c.h if exist vdsdbeng_c.h del vdsdbeng_c.h
if exist vdsdbe_c.h rename vdsdbe_c.h vdsdbeng_c.h
if exist vdsfse_c.h if exist vdsfseng_c.h del vdsfseng_c.h
if exist vdsfse_c.h rename vdsfse_c.h vdsfseng_c.h
if exist vdatasou.h if exist vdatasource.h del vdatasource.h
if exist vdatasou.h rename vdatasou.h vdatasource.h
if exist vdsuie_c.h if exist vdsuieng_c.h del vdsuieng_c.h
if exist vdsuie_c.h rename vdsuie_c.h vdsuieng_c.h
if exist vdatas_c.h if exist vdatasource_c.h del vdatasource_c.h
if exist vdatas_c.h rename vdatas_c.h vdatasource_c.h
if exist vdatat_c.h if exist vdatatag_c.h del vdatatag_c.h
if exist vdatat_c.h rename vdatat_c.h vdatatag_c.h
if exist vdateite.h if exist vdateitem.h del vdateitem.h
if exist vdateite.h rename vdateite.h vdateitem.h
if exist vdatei_c.h if exist vdateitem_c.h del vdateitem_c.h
if exist vdatei_c.h rename vdatei_c.h vdateitem_c.h
if exist vdbchs_c.h if exist vdbchsr_c.h del vdbchsr_c.h
if exist vdbchs_c.h rename vdbchs_c.h vdbchsr_c.h
if exist vdbcombo.h if exist vdbcombobox.h del vdbcombobox.h
if exist vdbcombo.h rename vdbcombo.h vdbcombobox.h
if exist vdbspinn.h if exist vdbspinner.h del vdbspinner.h
if exist vdbspinn.h rename vdbspinn.h vdbspinner.h
if exist vdelegat.h if exist vdelegator.h del vdelegator.h
if exist vdelegat.h rename vdelegat.h vdelegator.h
if exist vdeleg_c.h if exist vdelegator_c.h del vdelegator_c.h
if exist vdeleg_c.h rename vdeleg_c.h vdelegator_c.h
if exist vdialo_c.h if exist vdialog_c.h del vdialog_c.h
if exist vdialo_c.h rename vdialo_c.h vdialog_c.h
if exist vdockcnt.h if exist vdockcont.h del vdockcont.h
if exist vdockcnt.h rename vdockcnt.h vdockcont.h
if exist vdockc_c.h if exist vdockcont_c.h del vdockcont_c.h
if exist vdockc_c.h rename vdockc_c.h vdockcont_c.h
if exist vdocke_c.h if exist vdocker_c.h del vdocker_c.h
if exist vdocke_c.h rename vdocke_c.h vdocker_c.h
if exist vdockitm.h if exist vdockitem.h del vdockitem.h
if exist vdockitm.h rename vdockitm.h vdockitem.h
if exist vdocki_c.h if exist vdockitem_c.h del vdockitem_c.h
if exist vdocki_c.h rename vdocki_c.h vdockitem_c.h
if exist vdomai_c.h if exist vdomain_c.h del vdomain_c.h
if exist vdomai_c.h rename vdomai_c.h vdomain_c.h
if exist vdomit_c.h if exist vdomitem_c.h del vdomitem_c.h
if exist vdomit_c.h rename vdomit_c.h vdomitem_c.h
if exist vdomvi_c.h if exist vdomview_c.h del vdomview_c.h
if exist vdomvi_c.h rename vdomvi_c.h vdomview_c.h
if exist vdblitem.h if exist vdoubleitem.h del vdoubleitem.h
if exist vdblitem.h rename vdblitem.h vdoubleitem.h
if exist vdblit_c.h if exist vdoubleitem_c.h del vdoubleitem_c.h
if exist vdblit_c.h rename vdblit_c.h vdoubleitem_c.h
if exist vdrawcon.h if exist vdrawcontext.h del vdrawcontext.h
if exist vdrawcon.h rename vdrawcon.h vdrawcontext.h
if exist vdrwco_c.h if exist vdrawcontext_c.h del vdrawcontext_c.h
if exist vdrwco_c.h rename vdrwco_c.h vdrawcontext_c.h
if exist vdrawpat.h if exist vdrawpath.h del vdrawpath.h
if exist vdrawpat.h rename vdrawpat.h vdrawpath.h
if exist vdrwpa_c.h if exist vdrawpath_c.h del vdrawpath_c.h
if exist vdrwpa_c.h rename vdrwpa_c.h vdrawpath_c.h
if exist vdrwpe_c.h if exist vdrawpen_c.h del vdrawpen_c.h
if exist vdrwpe_c.h rename vdrwpe_c.h vdrawpen_c.h
if exist vdrawrec.h if exist vdrawrectset.h del vdrawrectset.h
if exist vdrawrec.h rename vdrawrec.h vdrawrectset.h
if exist vdrwre_c.h if exist vdrawrectset_c.h del vdrawrectset_c.h
if exist vdrwre_c.h rename vdrwre_c.h vdrawrectset_c.h
if exist vdropsit.h if exist vdropsite.h del vdropsite.h
if exist vdropsit.h rename vdropsit.h vdropsite.h
if exist vdrops_c.h if exist vdropsite_c.h del vdropsite_c.h
if exist vdrops_c.h rename vdrops_c.h vdropsite_c.h
if exist vdropsit.h if exist vdropsite.h del vdropsite.h
if exist vdropsit.h rename vdropsit.h vdropsite.h
if exist vdrops_c.h if exist vdropsite_c.h del vdropsite_c.h
if exist vdrops_c.h rename vdrops_c.h vdropsite_c.h
if exist vdsdbe_c.h if exist vdsdbeng_c.h del vdsdbeng_c.h
if exist vdsdbe_c.h rename vdsdbe_c.h vdsdbeng_c.h
if exist vdsfse_c.h if exist vdsfseng_c.h del vdsfseng_c.h
if exist vdsfse_c.h rename vdsfse_c.h vdsfseng_c.h
if exist vdsuie_c.h if exist vdsuieng_c.h del vdsuieng_c.h
if exist vdsuie_c.h rename vdsuie_c.h vdsuieng_c.h
if exist veven2_c.h if exist vevent2_c.h del vevent2_c.h
if exist veven2_c.h rename veven2_c.h vevent2_c.h
if exist vevent2s.h if exist vevent2sys.h del vevent2sys.h
if exist vevent2s.h rename vevent2s.h vevent2sys.h
if exist vevn2s_c.h if exist vevent2sys_c.h del vevent2sys_c.h
if exist vevn2s_c.h rename vevn2s_c.h vevent2sys_c.h
if exist veventsy.h if exist veventsys.h del veventsys.h
if exist veventsy.h rename veventsy.h veventsys.h
if exist vevnsy_c.h if exist veventsys_c.h del veventsys_c.h
if exist vevnsy_c.h rename vevnsy_c.h veventsys_c.h
if exist vevnti_c.h if exist vevntitr_c.h del vevntitr_c.h
if exist vevnti_c.h rename vevnti_c.h vevntitr_c.h
if exist vfilechs.h if exist vfilechsr.h del vfilechsr.h
if exist vfilechs.h rename vfilechs.h vfilechsr.h
if exist vfilec_c.h if exist vfilechsr_c.h del vfilechsr_c.h
if exist vfilec_c.h rename vfilec_c.h vfilechsr_c.h
if exist vfontchs.h if exist vfontchsr.h del vfontchsr.h
if exist vfontchs.h rename vfontchs.h vfontchsr.h
if exist vfontc_c.h if exist vfontchsr_c.h del vfontchsr_c.h
if exist vfontc_c.h rename vfontc_c.h vfontchsr_c.h
if exist vfontspe.h if exist vfontspec.h del vfontspec.h
if exist vfontspe.h rename vfontspe.h vfontspec.h
if exist vfonts_c.h if exist vfontspec_c.h del vfontspec_c.h
if exist vfonts_c.h rename vfonts_c.h vfontspec_c.h
if exist vfrmctxt.h if exist vformctxt.h del vformctxt.h
if exist vfrmctxt.h rename vfrmctxt.h vformctxt.h
if exist vfrmct_c.h if exist vformctxt_c.h del vformctxt_c.h
if exist vfrmct_c.h rename vfrmct_c.h vformctxt_c.h
if exist vforma_c.h if exist vformat_c.h del vformat_c.h
if exist vforma_c.h rename vforma_c.h vformat_c.h
if exist vgridcon.h if exist vgridcont.h del vgridcont.h
if exist vgridcon.h rename vgridcon.h vgridcont.h
if exist vgridc_c.h if exist vgridcont_c.h del vgridcont_c.h
if exist vgridc_c.h rename vgridc_c.h vgridcont_c.h
if exist vgridmod.h if exist vgridmodel.h del vgridmodel.h
if exist vgridmod.h rename vgridmod.h vgridmodel.h
if exist vgridm_c.h if exist vgridmodel_c.h del vgridmodel_c.h
if exist vgridm_c.h rename vgridm_c.h vgridmodel_c.h
if exist vhelpdis.h if exist vhelpdisplay.h del vhelpdisplay.h
if exist vhelpdis.h rename vhelpdis.h vhelpdisplay.h
if exist vhpdis_c.h if exist vhelpdisplay_c.h del vhelpdisplay_c.h
if exist vhpdis_c.h rename vhpdis_c.h vhelpdisplay_c.h
if exist vhelpdef.h if exist vhelpdefault.h del vhelpdefault.h
if exist vhelpdef.h rename vhelpdef.h vhelpdefault.h
if exist vhpdef_c.h if exist vhelpdefault_c.h del vhelpdefault_c.h
if exist vhpdef_c.h rename vhpdef_c.h vhelpdefault_c.h
if exist vhelpexp.h if exist vhelpexplorer.h del vhelpexplorer.h
if exist vhelpexp.h rename vhelpexp.h vhelpexplorer.h
if exist vhpexp_c.h if exist vhelpexplorer_c.h del vhelpexplorer_c.h
if exist vhpexp_c.h rename vhpexp_c.h vhelpexplorer_c.h
if exist vhelpgal.h if exist vhelpgalaxy.h del vhelpgalaxy.h
if exist vhelpgal.h rename vhelpgal.h vhelpgalaxy.h
if exist vhpgal_c.h if exist vhelpgalaxy_c.h del vhelpgalaxy_c.h
if exist vhpgal_c.h rename vhpgal_c.h vhelpgalaxy_c.h
if exist vhelphtg.h if exist vhelphtmlgalaxy.h del vhelphtmlgalaxy.h
if exist vhelphtg.h rename vhelphtg.h vhelphtmlgalaxy.h
if exist vhphtg_c.h if exist vhelphtmlgalaxy_c.h del vhelphtmlgalaxy_c.h
if exist vhphtg_c.h rename vhphtg_c.h vhelphtmlgalaxy_c.h
if exist vhelphtl.h if exist vhelphtmllocator.h del vhelphtmllocator.h
if exist vhelphtl.h rename vhelphtl.h vhelphtmllocator.h
if exist vhphtl_c.h if exist vhelphtmllocator_c.h del vhelphtmllocator_c.h
if exist vhphtl_c.h rename vhphtl_c.h vhelphtmllocator_c.h
if exist vhelphyp.h if exist vhelphypertext.h del vhelphypertext.h
if exist vhelphyp.h rename vhelphyp.h vhelphypertext.h
if exist vhphyp_c.h if exist vhelphypertext_c.h del vhelphypertext_c.h
if exist vhphyp_c.h rename vhphyp_c.h vhelphypertext_c.h
if exist vhelplin.h if exist vhelplinker.h del vhelplinker.h
if exist vhelplin.h rename vhelplin.h vhelplinker.h
if exist vhelploc.h if exist vhelplocator.h del vhelplocator.h
if exist vhelploc.h rename vhelploc.h vhelplocator.h
if exist vhploc_c.h if exist vhelplocator_c.h del vhelplocator_c.h
if exist vhploc_c.h rename vhploc_c.h vhelplocator_c.h
if exist vhelpnet.h if exist vhelpnetscape.h del vhelpnetscape.h
if exist vhelpnet.h rename vhelpnet.h vhelpnetscape.h
if exist vhpnet_c.h if exist vhelpnetscape_c.h del vhelpnetscape_c.h
if exist vhpnet_c.h rename vhpnet_c.h vhelpnetscape_c.h
if exist vhelpobj.h if exist vhelpobject.h del vhelpobject.h
if exist vhelpobj.h rename vhelpobj.h vhelpobject.h
if exist vhpobj_c.h if exist vhelpobject_c.h del vhelpobject_c.h
if exist vhpobj_c.h rename vhpobj_c.h vhelpobject_c.h
if exist vhpref_c.h if exist vhelpref_c.h del vhelpref_c.h
if exist vhpref_c.h rename vhpref_c.h vhelpref_c.h
if exist vhelprfl.h if exist vhelpreflocator.h del vhelpreflocator.h
if exist vhelprfl.h rename vhelprfl.h vhelpreflocator.h
if exist vhprfl_c.h if exist vhelpreflocator_c.h del vhelpreflocator_c.h
if exist vhprfl_c.h rename vhprfl_c.h vhelpreflocator_c.h
if exist vhelpreg.h if exist vhelpregistry.h del vhelpregistry.h
if exist vhelpreg.h rename vhelpreg.h vhelpregistry.h
if exist vhpreg_c.h if exist vhelpregistry_c.h del vhelpregistry_c.h
if exist vhpreg_c.h rename vhpreg_c.h vhelpregistry_c.h
if exist vhelpreq.h if exist vhelprequest.h del vhelprequest.h
if exist vhelpreq.h rename vhelpreq.h vhelprequest.h
if exist vhpreq_c.h if exist vhelprequest_c.h del vhelprequest_c.h
if exist vhpreq_c.h rename vhpreq_c.h vhelprequest_c.h
if exist vhelpsta.h if exist vhelpstatus.h del vhelpstatus.h
if exist vhelpsta.h rename vhelpsta.h vhelpstatus.h
if exist vhpsta_c.h if exist vhelpstatus_c.h del vhelpstatus_c.h
if exist vhpsta_c.h rename vhpsta_c.h vhelpstatus_c.h
if exist vhelptex.h if exist vhelptext.h del vhelptext.h
if exist vhelptex.h rename vhelptex.h vhelptext.h
if exist vhptex_c.h if exist vhelptext_c.h del vhelptext_c.h
if exist vhptex_c.h rename vhptex_c.h vhelptext_c.h
if exist vhelptxl.h if exist vhelptextlocator.h del vhelptextlocator.h
if exist vhelptxl.h rename vhelptxl.h vhelptextlocator.h
if exist vhptxl_c.h if exist vhelptextlocator_c.h del vhelptextlocator_c.h
if exist vhptxl_c.h rename vhptxl_c.h vhelptextlocator_c.h
if exist vhelptip.h if exist vhelptooltip.h del vhelptooltip.h
if exist vhelptip.h rename vhelptip.h vhelptooltip.h
if exist vhptip_c.h if exist vhelptooltip_c.h del vhelptooltip_c.h
if exist vhptip_c.h rename vhptip_c.h vhelptooltip_c.h
if exist vhelptra.h if exist vhelptrans.h del vhelptrans.h
if exist vhelptra.h rename vhelptra.h vhelptrans.h
if exist vhelpwin.h if exist vhelpwinhelp.h del vhelpwinhelp.h
if exist vhelpwin.h rename vhelpwin.h vhelpwinhelp.h
if exist vhpwin_c.h if exist vhelpwinhelp_c.h del vhelpwinhelp_c.h
if exist vhpwin_c.h rename vhpwin_c.h vhelpwinhelp_c.h
if exist vhexch_c.h if exist vhexchsr_c.h del vhexchsr_c.h
if exist vhexch_c.h rename vhexch_c.h vhexchsr_c.h
if exist viconvie.h if exist viconview.h del viconview.h
if exist viconvie.h rename viconvie.h viconview.h
if exist viconv_c.h if exist viconview_c.h del viconview_c.h
if exist viconv_c.h rename viconv_c.h viconview_c.h
if exist vimagd_c.h if exist vimageed_c.h del vimageed_c.h
if exist vimagd_c.h rename vimagd_c.h vimageed_c.h
if exist vimgedut.h if exist vimgedutils.h del vimgedutils.h
if exist vimgedut.h rename vimgedut.h vimgedutils.h
if exist vimgutil.h if exist vimgutils.h del vimgutils.h
if exist vimgutil.h rename vimgutil.h vimgutils.h
if exist vinputsy.h if exist vinputsys.h del vinputsys.h
if exist vinputsy.h rename vinputsy.h vinputsys.h
if exist vinstl_c.h if exist vinstall_c.h del vinstall_c.h
if exist vinstl_c.h rename vinstl_c.h vinstall_c.h
if exist vinstanc.h if exist vinstance.h del vinstance.h
if exist vinstanc.h rename vinstanc.h vinstance.h
if exist vinsta_c.h if exist vinstance_c.h del vinstance_c.h
if exist vinsta_c.h rename vinsta_c.h vinstance_c.h
if exist vinterfa.h if exist vinterface.h del vinterface.h
if exist vinterfa.h rename vinterfa.h vinterface.h
if exist vinter_c.h if exist vinterface_c.h del vinterface_c.h
if exist vinter_c.h rename vinter_c.h vinterface_c.h
if exist viterato.h if exist viterator.h del viterator.h
if exist viterato.h rename viterato.h viterator.h
if exist vitera_c.h if exist viterator_c.h del viterator_c.h
if exist vitera_c.h rename vitera_c.h viterator_c.h
if exist vkeyit_c.h if exist vkeyitem_c.h del vkeyitem_c.h
if exist vkeyit_c.h rename vkeyit_c.h vkeyitem_c.h
if exist vlistedi.h if exist vlistedit.h del vlistedit.h
if exist vlistedi.h rename vlistedi.h vlistedit.h
if exist vlistite.h if exist vlistitem.h del vlistitem.h
if exist vlistite.h rename vlistite.h vlistitem.h
if exist vlisti_c.h if exist vlistitem_c.h del vlistitem_c.h
if exist vlisti_c.h rename vlisti_c.h vlistitem_c.h
if exist vlistn_c.h if exist vlistsel_c.h del vlistsel_c.h
if exist vlistn_c.h rename vlistn_c.h vlistsel_c.h
if exist vlistsiz.h if exist vlistsize.h del vlistsize.h
if exist vlistsiz.h rename vlistsiz.h vlistsize.h
if exist vlistz_c.h if exist vlistsize_c.h del vlistsize_c.h
if exist vlistz_c.h rename vlistz_c.h vlistsize_c.h
if exist vlists_c.h if exist vliststr_c.h del vliststr_c.h
if exist vlists_c.h rename vlists_c.h vliststr_c.h
if exist vlistvie.h if exist vlistview.h del vlistview.h
if exist vlistvie.h rename vlistvie.h vlistview.h
if exist vlistv_c.h if exist vlistview_c.h del vlistview_c.h
if exist vlistv_c.h rename vlistv_c.h vlistview_c.h
if exist vloadabl.h if exist vloadable.h del vloadable.h
if exist vloadabl.h rename vloadabl.h vloadable.h
if exist vloada_c.h if exist vloadable_c.h del vloadable_c.h
if exist vloada_c.h rename vloada_c.h vloadable_c.h
if exist vlongite.h if exist vlongitem.h del vlongitem.h
if exist vlongite.h rename vlongite.h vlongitem.h
if exist vlongi_c.h if exist vlongitem_c.h del vlongitem_c.h
if exist vlongi_c.h rename vlongi_c.h vlongitem_c.h
if exist vlonglon.h if exist vlonglong.h del vlonglong.h
if exist vlonglon.h rename vlonglon.h vlonglong.h
if exist vlongl_c.h if exist vlonglong_c.h del vlonglong_c.h
if exist vlongl_c.h rename vlongl_c.h vlonglong_c.h
if exist vmaccont.h if exist vmaccontrols.h del vmaccontrols.h
if exist vmaccont.h rename vmaccont.h vmaccontrols.h
if exist vmacdial.h if exist vmacdialogs.h del vmacdialogs.h
if exist vmacdial.h rename vmacdial.h vmacdialogs.h
if exist vmacerro.h if exist vmacerrors.h del vmacerrors.h
if exist vmacerro.h rename vmacerro.h vmacerrors.h
if exist vmaceven.h if exist vmacevents.h del vmacevents.h
if exist vmaceven.h rename vmaceven.h vmacevents.h
if exist vmacfile.h if exist vmacfiles.h del vmacfiles.h
if exist vmacfile.h rename vmacfile.h vmacfiles.h
if exist vmacfont.h if exist vmacfonts.h del vmacfonts.h
if exist vmacfont.h rename vmacfont.h vmacfonts.h
if exist vmacgest.h if exist vmacgestaltequ.h del vmacgestaltequ.h
if exist vmacgest.h rename vmacgest.h vmacgestaltequ.h
if exist vmachi_c.h if exist vmachine_c.h del vmachine_c.h
if exist vmachi_c.h rename vmachi_c.h vmachine_c.h
if exist vmacmemo.h if exist vmacmemory.h del vmacmemory.h
if exist vmacmemo.h rename vmacmemo.h vmacmemory.h
if exist vmacquic.h if exist vmacquickdraw.h del vmacquickdraw.h
if exist vmacquic.h rename vmacquic.h vmacquickdraw.h
if exist vmacreso.h if exist vmacresources.h del vmacresources.h
if exist vmacreso.h rename vmacreso.h vmacresources.h
if exist vmacscri.h if exist vmacscript.h del vmacscript.h
if exist vmacscri.h rename vmacscri.h vmacscript.h
if exist vmacstri.h if exist vmacstrings.h del vmacstrings.h
if exist vmacstri.h rename vmacstri.h vmacstrings.h
if exist vmacsyse.h if exist vmacsysequ.h del vmacsysequ.h
if exist vmacsyse.h rename vmacsyse.h vmacsysequ.h
if exist vmactype.h if exist vmactypes.h del vmactypes.h
if exist vmactype.h rename vmactype.h vmactypes.h
if exist vmacwind.h if exist vmacwindows.h del vmacwindows.h
if exist vmacwind.h rename vmacwind.h vmacwindows.h
if exist vmainv_c.h if exist vmainvie_c.h del vmainvie_c.h
if exist vmainv_c.h rename vmainv_c.h vmainvie_c.h
if exist vmappi_c.h if exist vmapping_c.h del vmapping_c.h
if exist vmappi_c.h rename vmappi_c.h vmapping_c.h
if exist vmaskite.h if exist vmaskitem.h del vmaskitem.h
if exist vmaskite.h rename vmaskite.h vmaskitem.h
if exist vmaski_c.h if exist vmaskitem_c.h del vmaskitem_c.h
if exist vmaski_c.h rename vmaski_c.h vmaskitem_c.h
if exist vmatri_c.h if exist vmatrix_c.h del vmatrix_c.h
if exist vmatri_c.h rename vmatri_c.h vmatrix_c.h
if exist vmenub_c.h if exist vmenubar_c.h del vmenubar_c.h
if exist vmenub_c.h rename vmenub_c.h vmenubar_c.h
if exist vmodul_c.h if exist vmodule_c.h del vmodule_c.h
if exist vmodul_c.h rename vmodul_c.h vmodule_c.h
if exist vmutexsy.h if exist vmutexsys.h del vmutexsys.h
if exist vmutexsy.h rename vmutexsy.h vmutexsys.h
if exist vnameo_c.h if exist vnameobj_c.h del vnameobj_c.h
if exist vnameo_c.h rename vnameo_c.h vnameobj_c.h
if exist vnetinet.h if exist vnetinetin.h del vnetinetin.h
if exist vnetinet.h rename vnetinet.h vnetinetin.h
if exist vnoteboo.h if exist vnotebook.h del vnotebook.h
if exist vnoteboo.h rename vnoteboo.h vnotebook.h
if exist vnoteb_c.h if exist vnotebook_c.h del vnotebook_c.h
if exist vnoteb_c.h rename vnoteb_c.h vnotebook_c.h
if exist vnotic_c.h if exist vnotice_c.h del vnotice_c.h
if exist vnotic_c.h rename vnotic_c.h vnotice_c.h
if exist vobjec_c.h if exist vobject_c.h del vobject_c.h
if exist vobjec_c.h rename vobjec_c.h vobject_c.h
if exist vobserva.h if exist vobservable.h del vobservable.h
if exist vobserva.h rename vobserva.h vobservable.h
if exist vobsab_c.h if exist vobservable_c.h del vobservable_c.h
if exist vobsab_c.h rename vobsab_c.h vobservable_c.h
if exist vobserve.h if exist vobserver.h del vobserver.h
if exist vobserve.h rename vobserve.h vobserver.h
if exist vobser_c.h if exist vobserver_c.h del vobserver_c.h
if exist vobser_c.h rename vobser_c.h vobserver_c.h
if exist voccurre.h if exist voccurrence.h del voccurrence.h
if exist voccurre.h rename voccurre.h voccurrence.h
if exist voccur_c.h if exist voccurrence_c.h del voccurrence_c.h
if exist voccur_c.h rename voccur_c.h voccurrence_c.h
if exist volect_c.h if exist volectrl_c.h del volectrl_c.h
if exist volect_c.h rename volect_c.h volectrl_c.h
if exist volesi_c.h if exist volesite_c.h del volesite_c.h
if exist volesi_c.h rename volesi_c.h volesite_c.h
if exist volevari.h if exist volevariant.h del volevariant.h
if exist volevari.h rename volevari.h volevariant.h
if exist voleva_c.h if exist volevariant_c.h del volevariant_c.h
if exist voleva_c.h rename voleva_c.h volevariant_c.h
if exist volege_c.h if exist volegen_c.h del volegen_c.h
if exist volege_c.h rename volege_c.h volegen_c.h
if exist vpalet_c.h if exist vpalette_c.h del vpalette_c.h
if exist vpalet_c.h rename vpalet_c.h vpalette_c.h
if exist vpanecon.h if exist vpanecont.h del vpanecont.h
if exist vpanecon.h rename vpanecon.h vpanecont.h
if exist vpanec_c.h if exist vpanecont_c.h del vpanecont_c.h
if exist vpanec_c.h rename vpanec_c.h vpanecont_c.h
if exist vpthsc_c.h if exist vpthscrp_c.h del vpthscrp_c.h
if exist vpthsc_c.h rename vpthsc_c.h vpthscrp_c.h
if exist vpersist.h if exist vpersistent.h del vpersistent.h
if exist vpersist.h rename vpersist.h vpersistent.h
if exist vpersi_c.h if exist vpersistent_c.h del vpersistent_c.h
if exist vpersi_c.h rename vpersi_c.h vpersistent_c.h
if exist vpixma_c.h if exist vpixmap_c.h del vpixmap_c.h
if exist vpixma_c.h rename vpixma_c.h vpixmap_c.h
if exist vprintsy.h if exist vprintsys.h del vprintsys.h
if exist vprintsy.h rename vprintsy.h vprintsys.h
if exist vproce_c.h if exist vprocess_c.h del vprocess_c.h
if exist vproce_c.h rename vproce_c.h vprocess_c.h
if exist vpsconte.h if exist vpscontext.h del vpscontext.h
if exist vpsconte.h rename vpsconte.h vpscontext.h
if exist vpsinter.h if exist vpsinterp.h del vpsinterp.h
if exist vpsinter.h rename vpsinter.h vpsinterp.h
if exist vpsobjec.h if exist vpsobject.h del vpsobject.h
if exist vpsobjec.h rename vpsobjec.h vpsobject.h
if exist vpwdit_c.h if exist vpwditem_c.h del vpwditem_c.h
if exist vpwdit_c.h rename vpwdit_c.h vpwditem_c.h
if exist vqueryva.h if exist vqueryvalue.h del vqueryvalue.h
if exist vqueryva.h rename vqueryva.h vqueryvalue.h
if exist vquerybu.h if exist vquerybuilder.h del vquerybuilder.h
if exist vquerybu.h rename vquerybu.h vquerybuilder.h
if exist vreedito.h if exist vreeditor.h del vreeditor.h
if exist vreedito.h rename vreedito.h vreeditor.h
if exist vregex_c.h if exist vregexp_c.h del vregexp_c.h
if exist vregex_c.h rename vregex_c.h vregexp_c.h
if exist vreplb_c.h if exist vreplabel_c.h del vreplabel_c.h
if exist vreplb_c.h rename vreplb_c.h vreplabel_c.h
if exist vrepla_c.h if exist vreplang_c.h del vreplang_c.h
if exist vrepla_c.h rename vrepla_c.h vreplang_c.h
if exist vreportc.h if exist vreportcomponent.h del vreportcomponent.h
if exist vreportc.h rename vreportc.h vreportcomponent.h
if exist vrptcm_c.h if exist vreportcomponent_c.h del vreportcomponent_c.h
if exist vrptcm_c.h rename vrptcm_c.h vreportcomponent_c.h
if exist vrdchs_c.h if exist vrdchsr_c.h del vrdchsr_c.h
if exist vrdchs_c.h rename vrdchs_c.h vrdchsr_c.h
if exist vrdevchs.h if exist vrdevchsr.h del vrdevchsr.h
if exist vrdevchs.h rename vrdevchs.h vrdevchsr.h
if exist vrdevc_c.h if exist vrdevchsr_c.h del vrdevchsr_c.h
if exist vrdevc_c.h rename vrdevc_c.h vrdevchsr_c.h
if exist vreportd.h if exist vreportdevice.h del vreportdevice.h
if exist vreportd.h rename vreportd.h vreportdevice.h
if exist vrptdv_c.h if exist vreportdevice_c.h del vreportdevice_c.h
if exist vrptdv_c.h rename vrptdv_c.h vreportdevice_c.h
if exist vreportf.h if exist vreportfiledev.h del vreportfiledev.h
if exist vreportf.h rename vreportf.h vreportfiledev.h
if exist vrptfd_c.h if exist vreportfiledev_c.h del vreportfiledev_c.h
if exist vrptfd_c.h rename vrptfd_c.h vreportfiledev_c.h
if exist vrepfm_c.h if exist vrepfmt_c.h del vrepfmt_c.h
if exist vrepfm_c.h rename vrepfm_c.h vrepfmt_c.h
if exist vreplabe.h if exist vreplabel.h del vreplabel.h
if exist vreplabe.h rename vreplabe.h vreplabel.h
if exist vreplb_c.h if exist vreplabel_c.h del vreplabel_c.h
if exist vreplb_c.h rename vreplb_c.h vreplabel_c.h
if exist vreportl.h if exist vreportlayout.h del vreportlayout.h
if exist vreportl.h rename vreportl.h vreportlayout.h
if exist vrptlo_c.h if exist vreportlayout_c.h del vreportlayout_c.h
if exist vrptlo_c.h rename vrptlo_c.h vreportlayout_c.h
if exist vrepli_c.h if exist vrepline_c.h del vrepline_c.h
if exist vrepli_c.h rename vrepli_c.h vrepline_c.h
if exist vreporto.h if exist vreportobject.h del vreportobject.h
if exist vreporto.h rename vreporto.h vreportobject.h
if exist vrptob_c.h if exist vreportobject_c.h del vreportobject_c.h
if exist vrptob_c.h rename vrptob_c.h vreportobject_c.h
if exist vreports.h if exist vreportscreen.h del vreportscreen.h
if exist vreports.h rename vreports.h vreportscreen.h
if exist vrptos_c.h if exist vreportscreen_c.h del vreportscreen_c.h
if exist vrptos_c.h rename vrptos_c.h vreportscreen_c.h
if exist vreportp.h if exist vreportppv.h del vreportppv.h
if exist vreportp.h rename vreportp.h vreportppv.h
if exist vrptpp_c.h if exist vreportppv_c.h del vreportppv_c.h
if exist vrptpp_c.h rename vrptpp_c.h vreportppv_c.h
if exist vreportt.h if exist vreporttree.h del vreporttree.h
if exist vreportt.h rename vreportt.h vreporttree.h
if exist vrpttr_c.h if exist vreporttree_c.h del vreporttree_c.h
if exist vrpttr_c.h rename vrpttr_c.h vreporttree_c.h
if exist vrepor_c.h if exist vreport_c.h del vreport_c.h
if exist vrepor_c.h rename vrepor_c.h vreport_c.h
if exist vrptdv_c.h if exist vreportdevice_c.h del vreportdevice_c.h
if exist vrptdv_c.h rename vrptdv_c.h vreportdevice_c.h
if exist vrptlo_c.h if exist vreportlayout_c.h del vreportlayout_c.h
if exist vrptlo_c.h rename vrptlo_c.h vreportlayout_c.h
if exist vrepva_c.h if exist vrepvar_c.h del vrepvar_c.h
if exist vrepva_c.h rename vrepva_c.h vrepvar_c.h
if exist vreput_c.h if exist vreputil_c.h del vreputil_c.h
if exist vreput_c.h rename vreput_c.h vreputil_c.h
if exist vresfi_c.h if exist vresfile_c.h del vresfile_c.h
if exist vresfi_c.h rename vresfi_c.h vresfile_c.h
if exist vresolve.h if exist vresolver.h del vresolver.h
if exist vresolve.h rename vresolve.h vresolver.h
if exist vresol_c.h if exist vresolver_c.h del vresolver_c.h
if exist vresol_c.h rename vresol_c.h vresolver_c.h
if exist vresourc.h if exist vresource.h del vresource.h
if exist vresourc.h rename vresourc.h vresource.h
if exist vresou_c.h if exist vresource_c.h del vresource_c.h
if exist vresou_c.h rename vresou_c.h vresource_c.h
if exist vscrib_c.h if exist vscribe_c.h del vscribe_c.h
if exist vscrib_c.h rename vscrib_c.h vscribe_c.h
if exist vsequenc.h if exist vsequence.h del vsequence.h
if exist vsequenc.h rename vsequenc.h vsequence.h
if exist vseque_c.h if exist vsequence_c.h del vsequence_c.h
if exist vseque_c.h rename vseque_c.h vsequence_c.h
if exist vservi_c.h if exist vservice_c.h del vservice_c.h
if exist vservi_c.h rename vservi_c.h vservice_c.h
if exist vsvcch_c.h if exist vsvcchsr_c.h del vsvcchsr_c.h
if exist vsvcch_c.h rename vsvcch_c.h vsvcchsr_c.h
if exist vsessi_c.h if exist vsession_c.h del vsession_c.h
if exist vsessi_c.h rename vsessi_c.h vsession_c.h
if exist vsiggr_c.h if exist vsiggrp_c.h del vsiggrp_c.h
if exist vsiggr_c.h rename vsiggr_c.h vsiggrp_c.h
if exist vsignatu.h if exist vsignature.h del vsignature.h
if exist vsignatu.h rename vsignatu.h vsignature.h
if exist vsigna_c.h if exist vsignature_c.h del vsignature_c.h
if exist vsigna_c.h rename vsigna_c.h vsignature_c.h
if exist vsizevie.h if exist vsizeview.h del vsizeview.h
if exist vsizevie.h rename vsizevie.h vsizeview.h
if exist vsizev_c.h if exist vsizeview_c.h del vsizeview_c.h
if exist vsizev_c.h rename vsizev_c.h vsizeview_c.h
if exist vslide_c.h if exist vslider_c.h del vslider_c.h
if exist vslide_c.h rename vslide_c.h vslider_c.h
if exist vspinn_c.h if exist vspinner_c.h del vspinner_c.h
if exist vspinn_c.h rename vspinn_c.h vspinner_c.h
if exist vsplitte.h if exist vsplitter.h del vsplitter.h
if exist vsplitte.h rename vsplitte.h vsplitter.h
if exist vsprin_c.h if exist vspring_c.h del vspring_c.h
if exist vsprin_c.h rename vsprin_c.h vspring_c.h
if exist vsprdo_c.h if exist vsprdom_c.h del vsprdom_c.h
if exist vsprdo_c.h rename vsprdo_c.h vsprdom_c.h
if exist vstart_c.h if exist vstartup_c.h del vstartup_c.h
if exist vstart_c.h rename vstart_c.h vstartup_c.h
if exist vstatusb.h if exist vstatusbar.h del vstatusbar.h
if exist vstatusb.h rename vstatusb.h vstatusbar.h
if exist vstatb_c.h if exist vstatusbar_c.h del vstatusbar_c.h
if exist vstatb_c.h rename vstatb_c.h vstatusbar_c.h
if exist vstdiosy.h if exist vstdiosys.h del vstdiosys.h
if exist vstdiosy.h rename vstdiosy.h vstdiosys.h
if exist vstrch_c.h if exist vstrchsr_c.h del vstrchsr_c.h
if exist vstrch_c.h rename vstrch_c.h vstrchsr_c.h
if exist vstrea_c.h if exist vstream_c.h del vstream_c.h
if exist vstrea_c.h rename vstrea_c.h vstream_c.h
if exist vstrit_c.h if exist vstritem_c.h del vstritem_c.h
if exist vstrit_c.h rename vstrit_c.h vstritem_c.h
if exist vstylech.h if exist vstylechsr.h del vstylechsr.h
if exist vstylech.h rename vstylech.h vstylechsr.h
if exist vstyle_c.h if exist vstylechsr_c.h del vstylechsr_c.h
if exist vstyle_c.h rename vstyle_c.h vstylechsr_c.h
if exist vsysioct.h if exist vsysioctl.h del vsysioctl.h
if exist vsysioct.h rename vsysioct.h vsysioctl.h
if exist vsysmnte.h if exist vsysmntent.h del vsysmntent.h
if exist vsysmnte.h rename vsysmnte.h vsysmntent.h
if exist vsyspara.h if exist vsysparam.h del vsysparam.h
if exist vsyspara.h rename vsyspara.h vsysparam.h
if exist vsysreso.h if exist vsysresource.h del vsysresource.h
if exist vsysreso.h rename vsysreso.h vsysresource.h
if exist vsyssele.h if exist vsysselect.h del vsysselect.h
if exist vsyssele.h rename vsyssele.h vsysselect.h
if exist vsyssock.h if exist vsyssocket.h del vsyssocket.h
if exist vsyssock.h rename vsyssock.h vsyssocket.h
if exist vsysinfo.h if exist vsyssysteminfo.h del vsyssysteminfo.h
if exist vsysinfo.h rename vsysinfo.h vsyssysteminfo.h
if exist vsystims.h if exist vsystimes.h del vsystimes.h
if exist vsystims.h rename vsystims.h vsystimes.h
if exist vsystype.h if exist vsystypes.h del vsystypes.h
if exist vsystype.h rename vsystype.h vsystypes.h
if exist vsysutsn.h if exist vsysutsname.h del vsysutsname.h
if exist vsysutsn.h rename vsysutsn.h vsysutsname.h
if exist vtablevi.h if exist vtableview.h del vtableview.h
if exist vtablevi.h rename vtablevi.h vtableview.h
if exist vtblv_c.h if exist vtableview_c.h del vtableview_c.h
if exist vtblv_c.h rename vtblv_c.h vtableview_c.h
if exist vtextite.h if exist vtextitem.h del vtextitem.h
if exist vtextite.h rename vtextite.h vtextitem.h
if exist vtexti_c.h if exist vtextitem_c.h del vtextitem_c.h
if exist vtexti_c.h rename vtexti_c.h vtextitem_c.h
if exist vtextmar.h if exist vtextmarker.h del vtextmarker.h
if exist vtextmar.h rename vtextmar.h vtextmarker.h
if exist vtextm_c.h if exist vtextmarker_c.h del vtextmarker_c.h
if exist vtextm_c.h rename vtextm_c.h vtextmarker_c.h
if exist vtextrul.h if exist vtextruler.h del vtextruler.h
if exist vtextrul.h rename vtextrul.h vtextruler.h
if exist vtextr_c.h if exist vtextruler_c.h del vtextruler_c.h
if exist vtextr_c.h rename vtextr_c.h vtextruler_c.h
if exist vtexts_c.h if exist vtextsel_c.h del vtextsel_c.h
if exist vtexts_c.h rename vtexts_c.h vtextsel_c.h
if exist vtextvie.h if exist vtextview.h del vtextview.h
if exist vtextvie.h rename vtextvie.h vtextview.h
if exist vtextv_c.h if exist vtextview_c.h del vtextview_c.h
if exist vtextv_c.h rename vtextv_c.h vtextview_c.h
if exist vthrea_c.h if exist vthread_c.h del vthread_c.h
if exist vthrea_c.h rename vthrea_c.h vthread_c.h
if exist vthreade.h if exist vthreader.h del vthreader.h
if exist vthreade.h rename vthreade.h vthreader.h
if exist vthreads.h if exist vthreadsys.h del vthreadsys.h
if exist vthreads.h rename vthreads.h vthreadsys.h
if exist vthrds_c.h if exist vthreadsys_c.h del vthreadsys_c.h
if exist vthrds_c.h rename vthrds_c.h vthreadsys_c.h
if exist vtimesta.h if exist vtimestamp.h del vtimestamp.h
if exist vtimesta.h rename vtimesta.h vtimestamp.h
if exist vtimes_c.h if exist vtimestamp_c.h del vtimestamp_c.h
if exist vtimes_c.h rename vtimes_c.h vtimestamp_c.h
if exist vtoolb_c.h if exist vtoolbar_c.h del vtoolbar_c.h
if exist vtoolb_c.h rename vtoolb_c.h vtoolbar_c.h
if exist vtbrearr.h if exist vtbrearranger.h del vtbrearranger.h
if exist vtbrearr.h rename vtbrearr.h vtbrearranger.h
if exist vtbrar_c.h if exist vtbrearranger_c.h del vtbrearranger_c.h
if exist vtbrar_c.h rename vtbrar_c.h vtbrearranger_c.h
if exist vtbsep_c.h if exist vtbsepar_c.h del vtbsepar_c.h
if exist vtbsep_c.h rename vtbsep_c.h vtbsepar_c.h
if exist vtolbt_c.h if exist vtoolbtn_c.h del vtoolbtn_c.h
if exist vtolbt_c.h rename vtolbt_c.h vtoolbtn_c.h
if exist vtolchgr.h if exist vtoolchanger.h del vtoolchanger.h
if exist vtolchgr.h rename vtolchgr.h vtoolchanger.h
if exist vtolch_c.h if exist vtoolchanger_c.h del vtoolchanger_c.h
if exist vtolch_c.h rename vtolch_c.h vtoolchanger_c.h
if exist vtoolt_c.h if exist vtooltip_c.h del vtooltip_c.h
if exist vtoolt_c.h rename vtoolt_c.h vtooltip_c.h
if exist vtransfo.h if exist vtransform.h del vtransform.h
if exist vtransfo.h rename vtransfo.h vtransform.h
if exist vtrans_c.h if exist vtransform_c.h del vtransform_c.h
if exist vtrans_c.h rename vtrans_c.h vtransform_c.h
if exist vtrnsl_c.h if exist vtrans_c.h del vtrans_c.h
if exist vtrnsl_c.h rename vtrnsl_c.h vtrans_c.h
if exist vtreecar.h if exist vtreecard.h del vtreecard.h
if exist vtreecar.h rename vtreecar.h vtreecard.h
if exist vtreec_c.h if exist vtreecard_c.h del vtreecard_c.h
if exist vtreec_c.h rename vtreec_c.h vtreecard_c.h
if exist vtreelis.h if exist vtreelist.h del vtreelist.h
if exist vtreelis.h rename vtreelis.h vtreelist.h
if exist vtreel_c.h if exist vtreelist_c.h del vtreelist_c.h
if exist vtreel_c.h rename vtreel_c.h vtreelist_c.h
if exist vtreevie.h if exist vtreeview.h del vtreeview.h
if exist vtreevie.h rename vtreevie.h vtreeview.h
if exist vtreev_c.h if exist vtreeview_c.h del vtreeview_c.h
if exist vtreev_c.h rename vtreev_c.h vtreeview_c.h
if exist vtypedit.h if exist vtypeditem.h del vtypeditem.h
if exist vtypedit.h rename vtypedit.h vtypeditem.h
if exist vtypdi_c.h if exist vtypeditem_c.h del vtypeditem_c.h
if exist vtypdi_c.h rename vtypdi_c.h vtypeditem_c.h
if exist vulongit.h if exist vulongitem.h del vulongitem.h
if exist vulongit.h rename vulongit.h vulongitem.h
if exist vulngi_c.h if exist vulongitem_c.h del vulongitem_c.h
if exist vulngi_c.h rename vulngi_c.h vulongitem_c.h
if exist vundocom.h if exist vundocompat.h del vundocompat.h
if exist vundocom.h rename vundocom.h vundocompat.h
if exist vvaxfloa.h if exist vvaxfloat.h del vvaxfloat.h
if exist vvaxfloa.h rename vvaxfloa.h vvaxfloat.h
if exist vvmstype.h if exist vvmstypes.h del vvmstypes.h
if exist vvmstype.h rename vvmstype.h vvmstypes.h
if exist vwebbrow.h if exist vwebbrowse.h del vwebbrowse.h
if exist vwebbrow.h rename vwebbrow.h vwebbrowse.h
if exist vwebbr_c.h if exist vwebbrowse_c.h del vwebbrowse_c.h
if exist vwebbr_c.h rename vwebbr_c.h vwebbrowse_c.h
if exist vwindo_c.h if exist vwindow_c.h del vwindow_c.h
if exist vwindo_c.h rename vwindo_c.h vwindow_c.h
if exist vwindows.h if exist vwindowsys.h del vwindowsys.h
if exist vwindows.h rename vwindows.h vwindowsys.h
if exist vx11curs.h if exist vx11cursorfont.h del vx11cursorfont.h
if exist vx11curs.h rename vx11curs.h vx11cursorfont.h
if exist vx11exte.h if exist vx11extensionsxshm.h del vx11extensionsxshm.h
if exist vx11exte.h rename vx11exte.h vx11extensionsxshm.h
if exist vx11keys.h if exist vx11keysym.h del vx11keysym.h
if exist vx11keys.h rename vx11keys.h vx11keysym.h
if exist vx11xato.h if exist vx11xatom.h del vx11xatom.h
if exist vx11xato.h rename vx11xato.h vx11xatom.h
if exist vx11xuti.h if exist vx11xutil.h del vx11xutil.h
if exist vx11xuti.h rename vx11xuti.h vx11xutil.h
if exist vxxloada.h if exist vxxloadable.h del vxxloadable.h
if exist vxxloada.h rename vxxloada.h vxxloadable.h

goto END

:COPYINSTALL
echo on

copy %1\vport.h %2\vport.h
copy %1\vdllvar.h %2\vdllvar.h
copy %1\vhdrdefs.h %2\vhdrdefs.h
copy %1\vhdrlong.h %2\vhdrlong.h
copy %1\vhdr83.h %2\vhdr83.h
copy %1\vhdrlong.h %2\vhdrmode.h

copy %1\vgalaxy.h %2\vgalaxy.h
if exist vabstrac.h copy %1\vabstrac.h %2\vabstract.h
if exist vaccept.h copy %1\vaccept.h %2\vaccept.h
if exist vaccep_c.h copy %1\vaccep_c.h %2\vaccept_c.h
if exist vappfram.h copy %1\vappfram.h %2\vappframe.h
if exist vappfr_c.h copy %1\vappfr_c.h %2\vappframe_c.h
if exist vapplica.h copy %1\vapplica.h %2\vapplication.h
if exist vappli_c.h copy %1\vappli_c.h %2\vapplication_c.h
if exist vargscra.h copy %1\vargscra.h %2\vargscrap.h
if exist varpaine.h copy %1\varpaine.h %2\varpainet.h
if exist varray.h copy %1\varray.h %2\varray.h
if exist vassert.h copy %1\vassert.h %2\vassert.h
if exist vat.h copy %1\vat.h %2\vat.h
if exist vattribu.h copy %1\vattribu.h %2\vattribute.h
if exist vattri_c.h copy %1\vattri_c.h %2\vattribute_c.h
if exist vblock.h copy %1\vblock.h %2\vblock.h
if exist vboolite.h copy %1\vboolite.h %2\vboolitem.h
if exist vbooli_c.h copy %1\vbooli_c.h %2\vboolitem_c.h
if exist vbtree.h copy %1\vbtree.h %2\vbtree.h
if exist vbtree_c.h copy %1\vbtree_c.h %2\vbtree_c.h
if exist vbuffer.h copy %1\vbuffer.h %2\vbuffer.h
if exist vbuffe_c.h copy %1\vbuffe_c.h %2\vbuffer_c.h
if exist vbldnum.h copy %1\vbldnum.h %2\vbldnum.h
if exist vbuildst.h copy %1\vbuildst.h %2\vbuildstrs.h
if exist vbuildst.c copy %1\vbuildst.c %2\vbuildstrs.c
if exist vbutton.h copy %1\vbutton.h %2\vbutton.h
if exist vbutto_c.h copy %1\vbutto_c.h %2\vbutton_c.h
if exist vcanvas.h copy %1\vcanvas.h %2\vcanvas.h
if exist vcanva_c.h copy %1\vcanva_c.h %2\vcanvas_c.h
if exist vchar.h copy %1\vchar.h %2\vchar.h
if exist vchar_c.h copy %1\vchar_c.h %2\vchar_c.h
if exist vcharenc.h copy %1\vcharenc.h %2\vcharencoding.h
if exist vchare_c.h copy %1\vchare_c.h %2\vcharencoding_c.h
if exist vchunk.h copy %1\vchunk.h %2\vchunk.h
if exist vclass.h copy %1\vclass.h %2\vclass.h
if exist vclass_c.h copy %1\vclass_c.h %2\vclass_c.h
if exist vclassex.h copy %1\vclassex.h %2\vclassextra.h
if exist vclassin.h copy %1\vclassin.h %2\vclassinfo.h
if exist vclassre.h copy %1\vclassre.h %2\vclassreg.h
if exist vclex.h copy %1\vclex.h %2\vclex.h
if exist vclient.h copy %1\vclient.h %2\vclient.h
if exist vclien_c.h copy %1\vclien_c.h %2\vclient_c.h
if exist vclipboa.h copy %1\vclipboa.h %2\vclipboard.h
if exist vclipb_c.h copy %1\vclipb_c.h %2\vclipboard_c.h
if exist vcmdchsr.h copy %1\vcmdchsr.h %2\vcmdchsr.h
if exist vcmdch_c.h copy %1\vcmdch_c.h %2\vcmdchsr_c.h
if exist vcolor.h copy %1\vcolor.h %2\vcolor.h
if exist vcolor_c.h copy %1\vcolor_c.h %2\vcolor_c.h
if exist vcolorch.h copy %1\vcolorch.h %2\vcolorchsr.h
if exist vcolch_c.h copy %1\vcolch_c.h %2\vcolorchsr_c.h
if exist vcolorsy.h copy %1\vcolorsy.h %2\vcolorsys.h
if exist vcombo.h copy %1\vcombo.h %2\vcombo.h
if exist vcombo_c.h copy %1\vcombo_c.h %2\vcombo_c.h
if exist vcombobo.h copy %1\vcombobo.h %2\vcombobox.h
if exist vcombx_c.h copy %1\vcombx_c.h %2\vcombobox_c.h
if exist vcommchn.h copy %1\vcommchn.h %2\vcommchn.h
if exist vcommc_c.h copy %1\vcommc_c.h %2\vcommchn_c.h
if exist vcomm.h copy %1\vcomm.h %2\vcomm.h
if exist vcomm_c.h copy %1\vcomm_c.h %2\vcomm_c.h
if exist vcommand.h copy %1\vcommand.h %2\vcommand.h
if exist vcomma_c.h copy %1\vcomma_c.h %2\vcommand_c.h
if exist vcommdll.h copy %1\vcommdll.h %2\vcommdll.h
if exist vcommfix.h copy %1\vcommfix.h %2\vcommfix.h
if exist vconditi.h copy %1\vconditi.h %2\vcondition.h
if exist vconfirm.h copy %1\vconfirm.h %2\vconfirm.h
if exist vconfi_c.h copy %1\vconfi_c.h %2\vconfirm_c.h
if exist vctrgrid.h copy %1\vctrgrid.h %2\vctrgrid.h
if exist vctrgr_c.h copy %1\vctrgr_c.h %2\vctrgrid_c.h
if exist vcontain.h copy %1\vcontain.h %2\vcontain.h
if exist vconta_c.h copy %1\vconta_c.h %2\vcontain_c.h
if exist vcontrol.h copy %1\vcontrol.h %2\vcontrol.h
if exist vcontr_c.h copy %1\vcontr_c.h %2\vcontrol_c.h
if exist vctlchsr.h copy %1\vctlchsr.h %2\vctlchsr.h
if exist vctlch_c.h copy %1\vctlch_c.h %2\vctlchsr_c.h
if exist vctype.h copy %1\vctype.h %2\vctype.h
if exist vcursor.h copy %1\vcursor.h %2\vcursor.h
if exist vcurso_c.h copy %1\vcurso_c.h %2\vcursor_c.h
if exist vdasdict.h copy %1\vdasdict.h %2\vdasdict.h
if exist vdasserv.h copy %1\vdasserv.h %2\vdasserv.h
if exist vdasse_c.h copy %1\vdasse_c.h %2\vdasserv_c.h
if exist vdschsr.h copy %1\vdschsr.h %2\vdschsr.h
if exist vdschs_c.h copy %1\vdschs_c.h %2\vdschsr_c.h
if exist vdsdata.h copy %1\vdsdata.h %2\vdsdata.h
if exist vdsdat_c.h copy %1\vdsdat_c.h %2\vdsdata_c.h
if exist vdsdbeng.h copy %1\vdsdbeng.h %2\vdsdbeng.h
if exist vdsdbe_c.h copy %1\vdsdbe_c.h %2\vdsdbeng_c.h
if exist vdsfseng.h copy %1\vdsfseng.h %2\vdsfseng.h
if exist vdsfse_c.h copy %1\vdsfse_c.h %2\vdsfseng_c.h
if exist vdatasou.h copy %1\vdatasou.h %2\vdatasource.h
if exist vdsuieng.h copy %1\vdsuieng.h %2\vdsuieng.h
if exist vdsuie_c.h copy %1\vdsuie_c.h %2\vdsuieng_c.h
if exist vdatas_c.h copy %1\vdatas_c.h %2\vdatasource_c.h
if exist vdatatag.h copy %1\vdatatag.h %2\vdatatag.h
if exist vdatat_c.h copy %1\vdatat_c.h %2\vdatatag_c.h
if exist vdate.h copy %1\vdate.h %2\vdate.h
if exist vdate_c.h copy %1\vdate_c.h %2\vdate_c.h
if exist vdateite.h copy %1\vdateite.h %2\vdateitem.h
if exist vdatei_c.h copy %1\vdatei_c.h %2\vdateitem_c.h
if exist vdb.h copy %1\vdb.h %2\vdb.h
if exist vdbserv.h copy %1\vdbserv.h %2\vdbserv.h
if exist vdb_c.h copy %1\vdb_c.h %2\vdb_c.h
if exist vdbchsr.h copy %1\vdbchsr.h %2\vdbchsr.h
if exist vdbchs_c.h copy %1\vdbchs_c.h %2\vdbchsr_c.h
if exist vdbcombo.h copy %1\vdbcombo.h %2\vdbcombobox.h
if exist vdbform.h copy %1\vdbform.h %2\vdbform.h
if exist vdblist.h copy %1\vdblist.h %2\vdblist.h
if exist vdbmenu.h copy %1\vdbmenu.h %2\vdbmenu.h
if exist vdbpriv.h copy %1\vdbpriv.h %2\vdbpriv.h
if exist vdbquery.h copy %1\vdbquery.h %2\vdbquery.h
if exist vdbqb.h copy %1\vdbqb.h %2\vdbqb.h
if exist vdbspec.h copy %1\vdbspec.h %2\vdbspec.h
if exist vdbspinn.h copy %1\vdbspinn.h %2\vdbspinner.h
if exist vdebug.h copy %1\vdebug.h %2\vdebug.h
if exist vdebug_c.h copy %1\vdebug_c.h %2\vdebug_c.h
if exist vdebugut.h copy %1\vdebugut.h %2\vdebugut.h
if exist vdelegat.h copy %1\vdelegat.h %2\vdelegator.h
if exist vdeleg_c.h copy %1\vdeleg_c.h %2\vdelegator_c.h
if exist vdialog.h copy %1\vdialog.h %2\vdialog.h
if exist vdialog.h copy %1\vdialog.h %2\vdialog.h
if exist vdialo_c.h copy %1\vdialo_c.h %2\vdialog_c.h
if exist vdialsys.h copy %1\vdialsys.h %2\vdialsys.h
if exist vdict.h copy %1\vdict.h %2\vdict.h
if exist vdict_c.h copy %1\vdict_c.h %2\vdict_c.h
if exist vdirent.h copy %1\vdirent.h %2\vdirent.h
if exist vdock.h copy %1\vdock.h %2\vdock.h
if exist vdock_c.h copy %1\vdock_c.h %2\vdock_c.h
if exist vdockcnt.h copy %1\vdockcnt.h %2\vdockcont.h
if exist vdockc_c.h copy %1\vdockc_c.h %2\vdockcont_c.h
if exist vdocker.h copy %1\vdocker.h %2\vdocker.h
if exist vdocke_c.h copy %1\vdocke_c.h %2\vdocker_c.h
if exist vdockitm.h copy %1\vdockitm.h %2\vdockitem.h
if exist vdocki_c.h copy %1\vdocki_c.h %2\vdockitem_c.h
if exist vdomain.h copy %1\vdomain.h %2\vdomain.h
if exist vdomai_c.h copy %1\vdomai_c.h %2\vdomain_c.h
if exist vdomitem.h copy %1\vdomitem.h %2\vdomitem.h
if exist vdomit_c.h copy %1\vdomit_c.h %2\vdomitem_c.h
if exist vdomview.h copy %1\vdomview.h %2\vdomview.h
if exist vdomvi_c.h copy %1\vdomvi_c.h %2\vdomview_c.h
if exist vdouble.h copy %1\vdouble.h %2\vdouble.h
if exist vdblitem.h copy %1\vdblitem.h %2\vdoubleitem.h
if exist vdblit_c.h copy %1\vdblit_c.h %2\vdoubleitem_c.h
if exist vdrag.h copy %1\vdrag.h %2\vdrag.h
if exist vdrag_c.h copy %1\vdrag_c.h %2\vdrag_c.h
if exist vdraw.h copy %1\vdraw.h %2\vdraw.h
if exist vdraw_c.h copy %1\vdraw_c.h %2\vdraw_c.h
if exist vdrawcon.h copy %1\vdrawcon.h %2\vdrawcontext.h
if exist vdrwco_c.h copy %1\vdrwco_c.h %2\vdrawcontext_c.h
if exist vdrawpat.h copy %1\vdrawpat.h %2\vdrawpath.h
if exist vdrwpa_c.h copy %1\vdrwpa_c.h %2\vdrawpath_c.h
if exist vdrawpen.h copy %1\vdrawpen.h %2\vdrawpen.h
if exist vdrwpe_c.h copy %1\vdrwpe_c.h %2\vdrawpen_c.h
if exist vdrawrec.h copy %1\vdrawrec.h %2\vdrawrectset.h
if exist vdrwre_c.h copy %1\vdrwre_c.h %2\vdrawrectset_c.h
if exist vdrawsys.h copy %1\vdrawsys.h %2\vdrawsys.h
if exist vdropsit.h copy %1\vdropsit.h %2\vdropsite.h
if exist vdrops_c.h copy %1\vdrops_c.h %2\vdropsite_c.h
if exist vdropsit.h copy %1\vdropsit.h %2\vdropsite.h
if exist vdrops_c.h copy %1\vdrops_c.h %2\vdropsite_c.h
if exist vdsdbe_c.h copy %1\vdsdbe_c.h %2\vdsdbeng_c.h
if exist vdsfse_c.h copy %1\vdsfse_c.h %2\vdsfseng_c.h
if exist vdsuie_c.h copy %1\vdsuie_c.h %2\vdsuieng_c.h
if exist verrno.h copy %1\verrno.h %2\verrno.h
if exist vevent2.h copy %1\vevent2.h %2\vevent2.h
if exist veven2_c.h copy %1\veven2_c.h %2\vevent2_c.h
if exist vevent2s.h copy %1\vevent2s.h %2\vevent2sys.h
if exist vevn2s_c.h copy %1\vevn2s_c.h %2\vevent2sys_c.h
if exist vevent.h copy %1\vevent.h %2\vevent.h
if exist vevent_c.h copy %1\vevent_c.h %2\vevent_c.h
if exist veventsy.h copy %1\veventsy.h %2\veventsys.h
if exist vevnsy_c.h copy %1\vevnsy_c.h %2\veventsys_c.h
if exist vevntitr.h copy %1\vevntitr.h %2\vevntitr.h
if exist vevnti_c.h copy %1\vevnti_c.h %2\vevntitr_c.h
if exist vex.h copy %1\vex.h %2\vex.h
if exist vex_c.h copy %1\vex_c.h %2\vex_c.h
if exist vexport.h copy %1\vexport.h %2\vexport.h
if exist vexsys.h copy %1\vexsys.h %2\vexsys.h
if exist vfcntl.h copy %1\vfcntl.h %2\vfcntl.h
if exist vfield.h copy %1\vfield.h %2\vfield.h
if exist vfield_c.h copy %1\vfield_c.h %2\vfield_c.h
if exist vfile.h copy %1\vfile.h %2\vfile.h
if exist vfile_c.h copy %1\vfile_c.h %2\vfile_c.h
if exist vfilechs.h copy %1\vfilechs.h %2\vfilechsr.h
if exist vfilec_c.h copy %1\vfilec_c.h %2\vfilechsr_c.h
if exist vfixed.h copy %1\vfixed.h %2\vfixed.h
if exist vfixed_c.h copy %1\vfixed_c.h %2\vfixed_c.h
if exist vfloat.h copy %1\vfloat.h %2\vfloat.h
if exist vfont.h copy %1\vfont.h %2\vfont.h
if exist vfont_c.h copy %1\vfont_c.h %2\vfont_c.h
if exist vfontchs.h copy %1\vfontchs.h %2\vfontchsr.h
if exist vfontc_c.h copy %1\vfontc_c.h %2\vfontchsr_c.h
if exist vfontspe.h copy %1\vfontspe.h %2\vfontspec.h
if exist vfonts_c.h copy %1\vfonts_c.h %2\vfontspec_c.h
if exist vfontsys.h copy %1\vfontsys.h %2\vfontsys.h
if exist vfrmctxt.h copy %1\vfrmctxt.h %2\vformctxt.h
if exist vfrmct_c.h copy %1\vfrmct_c.h %2\vformctxt_c.h
if exist vform.h copy %1\vform.h %2\vform.h
if exist vform_c.h copy %1\vform_c.h %2\vform_c.h
if exist vformat.h copy %1\vformat.h %2\vformat.h
if exist vforma_c.h copy %1\vforma_c.h %2\vformat_c.h
if exist vfs.h copy %1\vfs.h %2\vfs.h
if exist vfs_c.h copy %1\vfs_c.h %2\vfs_c.h
if exist vgalbnum.h copy %1\vgalbnum.h %2\vgalbnum.h
if exist vglitem.h copy %1\vglitem.h %2\vglitem.h
if exist vglwin.h copy %1\vglwin.h %2\vglwin.h
if exist vgraph.h copy %1\vgraph.h %2\vgraph.h
if exist vgridcon.h copy %1\vgridcon.h %2\vgridcont.h
if exist vgridc_c.h copy %1\vgridc_c.h %2\vgridcont_c.h
if exist vgridmod.h copy %1\vgridmod.h %2\vgridmodel.h
if exist vgridm_c.h copy %1\vgridm_c.h %2\vgridmodel_c.h
if exist vgrp.h copy %1\vgrp.h %2\vgrp.h
if exist vhelp.h copy %1\vhelp.h %2\vhelp.h
if exist vhelprun.h copy %1\vhelprun.h %2\vhelprun.h
if exist vhelp_c.h copy %1\vhelp_c.h %2\vhelp_c.h
if exist vhelpdas.h copy %1\vhelpdas.h %2\vhelpdas.h
if exist vhelpdis.h copy %1\vhelpdis.h %2\vhelpdisplay.h
if exist vhpdis_c.h copy %1\vhpdis_c.h %2\vhelpdisplay_c.h
if exist vhelpdoc.h copy %1\vhelpdoc.h %2\vhelpdoc.h
if exist vhelpdef.h copy %1\vhelpdef.h %2\vhelpdefault.h
if exist vhpdef_c.h copy %1\vhpdef_c.h %2\vhelpdefault_c.h
if exist vhelpexp.h copy %1\vhelpexp.h %2\vhelpexplorer.h
if exist vhpexp_c.h copy %1\vhpexp_c.h %2\vhelpexplorer_c.h
if exist vhelpgal.h copy %1\vhelpgal.h %2\vhelpgalaxy.h
if exist vhpgal_c.h copy %1\vhpgal_c.h %2\vhelpgalaxy_c.h
if exist vhelphtg.h copy %1\vhelphtg.h %2\vhelphtmlgalaxy.h
if exist vhphtg_c.h copy %1\vhphtg_c.h %2\vhelphtmlgalaxy_c.h
if exist vhelphtl.h copy %1\vhelphtl.h %2\vhelphtmllocator.h
if exist vhphtl_c.h copy %1\vhphtl_c.h %2\vhelphtmllocator_c.h
if exist vhelphyp.h copy %1\vhelphyp.h %2\vhelphypertext.h
if exist vhphyp_c.h copy %1\vhphyp_c.h %2\vhelphypertext_c.h
if exist vhelplin.h copy %1\vhelplin.h %2\vhelplinker.h
if exist vhelploc.h copy %1\vhelploc.h %2\vhelplocator.h
if exist vhploc_c.h copy %1\vhploc_c.h %2\vhelplocator_c.h
if exist vhelpnet.h copy %1\vhelpnet.h %2\vhelpnetscape.h
if exist vhpnet_c.h copy %1\vhpnet_c.h %2\vhelpnetscape_c.h
if exist vhelpobj.h copy %1\vhelpobj.h %2\vhelpobject.h
if exist vhpobj_c.h copy %1\vhpobj_c.h %2\vhelpobject_c.h
if exist vhelpref.h copy %1\vhelpref.h %2\vhelpref.h
if exist vhpref_c.h copy %1\vhpref_c.h %2\vhelpref_c.h
if exist vhelprfl.h copy %1\vhelprfl.h %2\vhelpreflocator.h
if exist vhprfl_c.h copy %1\vhprfl_c.h %2\vhelpreflocator_c.h
if exist vhelpreg.h copy %1\vhelpreg.h %2\vhelpregistry.h
if exist vhpreg_c.h copy %1\vhpreg_c.h %2\vhelpregistry_c.h
if exist vhelpreq.h copy %1\vhelpreq.h %2\vhelprequest.h
if exist vhpreq_c.h copy %1\vhpreq_c.h %2\vhelprequest_c.h
if exist vhelpsta.h copy %1\vhelpsta.h %2\vhelpstatus.h
if exist vhpsta_c.h copy %1\vhpsta_c.h %2\vhelpstatus_c.h
if exist vhelptex.h copy %1\vhelptex.h %2\vhelptext.h
if exist vhptex_c.h copy %1\vhptex_c.h %2\vhelptext_c.h
if exist vhelptxl.h copy %1\vhelptxl.h %2\vhelptextlocator.h
if exist vhptxl_c.h copy %1\vhptxl_c.h %2\vhelptextlocator_c.h
if exist vhelptip.h copy %1\vhelptip.h %2\vhelptooltip.h
if exist vhptip_c.h copy %1\vhptip_c.h %2\vhelptooltip_c.h
if exist vhelptra.h copy %1\vhelptra.h %2\vhelptrans.h
if exist vhelpwin.h copy %1\vhelpwin.h %2\vhelpwinhelp.h
if exist vhpwin_c.h copy %1\vhpwin_c.h %2\vhelpwinhelp_c.h
if exist vhex.h copy %1\vhex.h %2\vhex.h
if exist vhex_c.h copy %1\vhex_c.h %2\vhex_c.h
if exist vhexchsr.h copy %1\vhexchsr.h %2\vhexchsr.h
if exist vhexch_c.h copy %1\vhexch_c.h %2\vhexchsr_c.h
if exist vhtml.h copy %1\vhtml.h %2\vhtml.h
if exist vhtmled.h copy %1\vhtmled.h %2\vhtmled.h
if exist vi18n.h copy %1\vi18n.h %2\vi18n.h
if exist viconvie.h copy %1\viconvie.h %2\viconview.h
if exist viconv_c.h copy %1\viconv_c.h %2\viconview_c.h
if exist vimage.h copy %1\vimage.h %2\vimage.h
if exist vimage_c.h copy %1\vimage_c.h %2\vimage_c.h
if exist vimageed.h copy %1\vimageed.h %2\vimageed.h
if exist vimagd_c.h copy %1\vimagd_c.h %2\vimageed_c.h
if exist vimged.h copy %1\vimged.h %2\vimged.h
if exist vimgedut.h copy %1\vimgedut.h %2\vimgedutils.h
if exist vimgutil.h copy %1\vimgutil.h %2\vimgutils.h
if exist vimport.h copy %1\vimport.h %2\vimport.h
if exist vinput.h copy %1\vinput.h %2\vinput.h
if exist vinput_c.h copy %1\vinput_c.h %2\vinput_c.h
if exist vinputsy.h copy %1\vinputsy.h %2\vinputsys.h
if exist vinst.h copy %1\vinst.h %2\vinst.h
if exist vinst_c.h copy %1\vinst_c.h %2\vinst_c.h
if exist vinstall.h copy %1\vinstall.h %2\vinstall.h
if exist vinstl_c.h copy %1\vinstl_c.h %2\vinstall_c.h
if exist vinstanc.h copy %1\vinstanc.h %2\vinstance.h
if exist vinsta_c.h copy %1\vinsta_c.h %2\vinstance_c.h
if exist vinterfa.h copy %1\vinterfa.h %2\vinterface.h
if exist vinter_c.h copy %1\vinter_c.h %2\vinterface_c.h
if exist vio.h copy %1\vio.h %2\vio.h
if exist viterato.h copy %1\viterato.h %2\viterator.h
if exist vitera_c.h copy %1\vitera_c.h %2\viterator_c.h
if exist vkey.h copy %1\vkey.h %2\vkey.h
if exist vkey_c.h copy %1\vkey_c.h %2\vkey_c.h
if exist vkeyitem.h copy %1\vkeyitem.h %2\vkeyitem.h
if exist vkeyit_c.h copy %1\vkeyit_c.h %2\vkeyitem_c.h
if exist vkeysys.h copy %1\vkeysys.h %2\vkeysys.h
if exist vkind.h copy %1\vkind.h %2\vkind.h
if exist vlaf.h copy %1\vlaf.h %2\vlaf.h
if exist vlaf_c.h copy %1\vlaf_c.h %2\vlaf_c.h
if exist vlibc.h copy %1\vlibc.h %2\vlibc.h
if exist vlimits.h copy %1\vlimits.h %2\vlimits.h
if exist vlist.h copy %1\vlist.h %2\vlist.h
if exist vlist_c.h copy %1\vlist_c.h %2\vlist_c.h
if exist vlistedi.h copy %1\vlistedi.h %2\vlistedit.h
if exist vlistite.h copy %1\vlistite.h %2\vlistitem.h
if exist vlisti_c.h copy %1\vlisti_c.h %2\vlistitem_c.h
if exist vlistsel.h copy %1\vlistsel.h %2\vlistsel.h
if exist vlistn_c.h copy %1\vlistn_c.h %2\vlistsel_c.h
if exist vlistsiz.h copy %1\vlistsiz.h %2\vlistsize.h
if exist vlistz_c.h copy %1\vlistz_c.h %2\vlistsize_c.h
if exist vliststr.h copy %1\vliststr.h %2\vliststr.h
if exist vlists_c.h copy %1\vlists_c.h %2\vliststr_c.h
if exist vlistvie.h copy %1\vlistvie.h %2\vlistview.h
if exist vlistv_c.h copy %1\vlistv_c.h %2\vlistview_c.h
if exist vloadabl.h copy %1\vloadabl.h %2\vloadable.h
if exist vloada_c.h copy %1\vloada_c.h %2\vloadable_c.h
if exist vlocale.h copy %1\vlocale.h %2\vlocale.h
if exist vlock.h copy %1\vlock.h %2\vlock.h
if exist vlongite.h copy %1\vlongite.h %2\vlongitem.h
if exist vlongi_c.h copy %1\vlongi_c.h %2\vlongitem_c.h
if exist vlonglon.h copy %1\vlonglon.h %2\vlonglong.h
if exist vlongl_c.h copy %1\vlongl_c.h %2\vlonglong_c.h
if exist vmaccont.h copy %1\vmaccont.h %2\vmaccontrols.h
if exist vmacdial.h copy %1\vmacdial.h %2\vmacdialogs.h
if exist vmacerro.h copy %1\vmacerro.h %2\vmacerrors.h
if exist vmaceven.h copy %1\vmaceven.h %2\vmacevents.h
if exist vmacfile.h copy %1\vmacfile.h %2\vmacfiles.h
if exist vmacfont.h copy %1\vmacfont.h %2\vmacfonts.h
if exist vmacgest.h copy %1\vmacgest.h %2\vmacgestaltequ.h
if exist vmachine.h copy %1\vmachine.h %2\vmachine.h
if exist vmachi_c.h copy %1\vmachi_c.h %2\vmachine_c.h
if exist vmacmemo.h copy %1\vmacmemo.h %2\vmacmemory.h
if exist vmacquic.h copy %1\vmacquic.h %2\vmacquickdraw.h
if exist vmacreso.h copy %1\vmacreso.h %2\vmacresources.h
if exist vmacscri.h copy %1\vmacscri.h %2\vmacscript.h
if exist vmacstri.h copy %1\vmacstri.h %2\vmacstrings.h
if exist vmacsyse.h copy %1\vmacsyse.h %2\vmacsysequ.h
if exist vmactype.h copy %1\vmactype.h %2\vmactypes.h
if exist vmacwind.h copy %1\vmacwind.h %2\vmacwindows.h
if exist vmaindia.h copy %1\vmaindia.h %2\vmaindia.h
if exist vmainvie.h copy %1\vmainvie.h %2\vmainvie.h
if exist vmainv_c.h copy %1\vmainv_c.h %2\vmainvie_c.h
if exist vmapping.h copy %1\vmapping.h %2\vmapping.h
if exist vmappi_c.h copy %1\vmappi_c.h %2\vmapping_c.h
if exist vmaskite.h copy %1\vmaskite.h %2\vmaskitem.h
if exist vmaski_c.h copy %1\vmaski_c.h %2\vmaskitem_c.h
if exist vmath.h copy %1\vmath.h %2\vmath.h
if exist vmatrix.h copy %1\vmatrix.h %2\vmatrix.h
if exist vmatri_c.h copy %1\vmatri_c.h %2\vmatrix_c.h
if exist vmem.h copy %1\vmem.h %2\vmem.h
if exist vmem_c.h copy %1\vmem_c.h %2\vmem_c.h
if exist vmemsys.h copy %1\vmemsys.h %2\vmemsys.h
if exist vmenu.h copy %1\vmenu.h %2\vmenu.h
if exist vmenu_c.h copy %1\vmenu_c.h %2\vmenu_c.h
if exist vmenubar.h copy %1\vmenubar.h %2\vmenubar.h
if exist vmenub_c.h copy %1\vmenub_c.h %2\vmenubar_c.h
if exist vmessage.h copy %1\vmessage.h %2\vmessage.h
if exist vmodule.h copy %1\vmodule.h %2\vmodule.h
if exist vmodul_c.h copy %1\vmodul_c.h %2\vmodule_c.h
if exist vmswhdrs.h copy %1\vmswhdrs.h %2\vmswhdrs.h
if exist vmutex.h copy %1\vmutex.h %2\vmutex.h
if exist vmutexsy.h copy %1\vmutexsy.h %2\vmutexsys.h
if exist vname.h copy %1\vname.h %2\vname.h
if exist vname_c.h copy %1\vname_c.h %2\vname_c.h
if exist vnameobj.h copy %1\vnameobj.h %2\vnameobj.h
if exist vnameo_c.h copy %1\vnameo_c.h %2\vnameobj_c.h
if exist vndx.h copy %1\vndx.h %2\vndx.h
if exist vnetdb.h copy %1\vnetdb.h %2\vnetdb.h
if exist vnetinet.h copy %1\vnetinet.h %2\vnetinetin.h
if exist vnoteboo.h copy %1\vnoteboo.h %2\vnotebook.h
if exist vnoteb_c.h copy %1\vnoteb_c.h %2\vnotebook_c.h
if exist vnotice.h copy %1\vnotice.h %2\vnotice.h
if exist vnotic_c.h copy %1\vnotic_c.h %2\vnotice_c.h
if exist vnum.h copy %1\vnum.h %2\vnum.h
if exist vnum_c.h copy %1\vnum_c.h %2\vnum_c.h
if exist vobject.h copy %1\vobject.h %2\vobject.h
if exist vobjec_c.h copy %1\vobjec_c.h %2\vobject_c.h
if exist vobserva.h copy %1\vobserva.h %2\vobservable.h
if exist vobsab_c.h copy %1\vobsab_c.h %2\vobservable_c.h
if exist vobserve.h copy %1\vobserve.h %2\vobserver.h
if exist vobser_c.h copy %1\vobser_c.h %2\vobserver_c.h
if exist voccurre.h copy %1\voccurre.h %2\voccurrence.h
if exist voccur_c.h copy %1\voccur_c.h %2\voccurrence_c.h
if exist vodbc.h copy %1\vodbc.h %2\vodbc.h
if exist vole.h copy %1\vole.h %2\vole.h
if exist vole_c.h copy %1\vole_c.h %2\vole_c.h
if exist volectrl.h copy %1\volectrl.h %2\volectrl.h
if exist volect_c.h copy %1\volect_c.h %2\volectrl_c.h
if exist volesite.h copy %1\volesite.h %2\volesite.h
if exist volesi_c.h copy %1\volesi_c.h %2\volesite_c.h
if exist volevari.h copy %1\volevari.h %2\volevariant.h
if exist voleva_c.h copy %1\voleva_c.h %2\volevariant_c.h
if exist volegen.h copy %1\volegen.h %2\volegen.h
if exist volege_c.h copy %1\volege_c.h %2\volegen_c.h
if exist vos2.h copy %1\vos2.h %2\vos2.h
if exist vpaled.h copy %1\vpaled.h %2\vpaled.h
if exist vpalette.h copy %1\vpalette.h %2\vpalette.h
if exist vpalet_c.h copy %1\vpalet_c.h %2\vpalette_c.h
if exist vpanecon.h copy %1\vpanecon.h %2\vpanecont.h
if exist vpanec_c.h copy %1\vpanec_c.h %2\vpanecont_c.h
if exist vpthscrp.h copy %1\vpthscrp.h %2\vpthscrp.h
if exist vpthsc_c.h copy %1\vpthsc_c.h %2\vpthscrp_c.h
if exist vpersist.h copy %1\vpersist.h %2\vpersistent.h
if exist vpersi_c.h copy %1\vpersi_c.h %2\vpersistent_c.h
if exist vpixmap.h copy %1\vpixmap.h %2\vpixmap.h
if exist vpixma_c.h copy %1\vpixma_c.h %2\vpixmap_c.h
if exist vpoint.h copy %1\vpoint.h %2\vpoint.h
if exist vpoint_c.h copy %1\vpoint_c.h %2\vpoint_c.h
if exist vpool.h copy %1\vpool.h %2\vpool.h
if exist vpool_c.h copy %1\vpool_c.h %2\vpool_c.h
if exist vportenv.h copy %1\vportenv.h %2\vportenv.h
if exist vportmac.h copy %1\vportmac.h %2\vportmac.h
if exist vpq.h copy %1\vpq.h %2\vpq.h
if exist vpq_c.h copy %1\vpq_c.h %2\vpq_c.h
if exist vpref.h copy %1\vpref.h %2\vpref.h
if exist vpref_c.h copy %1\vpref_c.h %2\vpref_c.h
if exist vprint.h copy %1\vprint.h %2\vprint.h
if exist vprint_c.h copy %1\vprint_c.h %2\vprint_c.h
if exist vprintsy.h copy %1\vprintsy.h %2\vprintsys.h
if exist vprocess.h copy %1\vprocess.h %2\vprocess.h
if exist vproce_c.h copy %1\vproce_c.h %2\vprocess_c.h
if exist vpsconte.h copy %1\vpsconte.h %2\vpscontext.h
if exist vpsdict.h copy %1\vpsdict.h %2\vpsdict.h
if exist vpserror.h copy %1\vpserror.h %2\vpserror.h
if exist vpsfile.h copy %1\vpsfile.h %2\vpsfile.h
if exist vpsinter.h copy %1\vpsinter.h %2\vpsinterp.h
if exist vpsobjec.h copy %1\vpsobjec.h %2\vpsobject.h
if exist vpsop.h copy %1\vpsop.h %2\vpsop.h
if exist vpsscan.h copy %1\vpsscan.h %2\vpsscan.h
if exist vpsstack.h copy %1\vpsstack.h %2\vpsstack.h
if exist vpsvm.h copy %1\vpsvm.h %2\vpsvm.h
if exist vpwd.h copy %1\vpwd.h %2\vpwd.h
if exist vpwditem.h copy %1\vpwditem.h %2\vpwditem.h
if exist vpwdit_c.h copy %1\vpwdit_c.h %2\vpwditem_c.h
if exist vquery.h copy %1\vquery.h %2\vquery.h
if exist vqueryva.h copy %1\vqueryva.h %2\vqueryvalue.h
if exist vquerybu.h copy %1\vquerybu.h %2\vquerybuilder.h
if exist vre.h copy %1\vre.h %2\vre.h
if exist vreader.h copy %1\vreader.h %2\vreader.h
if exist vrect.h copy %1\vrect.h %2\vrect.h
if exist vrect_c.h copy %1\vrect_c.h %2\vrect_c.h
if exist vredecl.h copy %1\vredecl.h %2\vredecl.h
if exist vreedito.h copy %1\vreedito.h %2\vreeditor.h
if exist vrefile.h copy %1\vrefile.h %2\vrefile.h
if exist vregexp.h copy %1\vregexp.h %2\vregexp.h
if exist vregex_c.h copy %1\vregex_c.h %2\vregexp_c.h
if exist vreinit.h copy %1\vreinit.h %2\vreinit.h
if exist vrepanel.h copy %1\vrepanel.h %2\vrepanel.h
if exist vreplb_c.h copy %1\vreplb_c.h %2\vreplabel_c.h
if exist vreplang.h copy %1\vreplang.h %2\vreplang.h
if exist vrepla_c.h copy %1\vrepla_c.h %2\vreplang_c.h
if exist vreportc.h copy %1\vreportc.h %2\vreportcomponent.h
if exist vrptcm_c.h copy %1\vrptcm_c.h %2\vreportcomponent_c.h
if exist vrdchsr.h copy %1\vrdchsr.h %2\vrdchsr.h
if exist vrdchs_c.h copy %1\vrdchs_c.h %2\vrdchsr_c.h
if exist vrdevchs.h copy %1\vrdevchs.h %2\vrdevchsr.h
if exist vrdevc_c.h copy %1\vrdevc_c.h %2\vrdevchsr_c.h
if exist vreportd.h copy %1\vreportd.h %2\vreportdevice.h
if exist vrptdv_c.h copy %1\vrptdv_c.h %2\vreportdevice_c.h
if exist vreportf.h copy %1\vreportf.h %2\vreportfiledev.h
if exist vrptfd_c.h copy %1\vrptfd_c.h %2\vreportfiledev_c.h
if exist vrepfmt.h copy %1\vrepfmt.h %2\vrepfmt.h
if exist vrepfm_c.h copy %1\vrepfm_c.h %2\vrepfmt_c.h
if exist vreport.h copy %1\vreport.h %2\vreport.h
if exist vreplabe.h copy %1\vreplabe.h %2\vreplabel.h
if exist vreplb_c.h copy %1\vreplb_c.h %2\vreplabel_c.h
if exist vreportl.h copy %1\vreportl.h %2\vreportlayout.h
if exist vrptlo_c.h copy %1\vrptlo_c.h %2\vreportlayout_c.h
if exist vrepline.h copy %1\vrepline.h %2\vrepline.h
if exist vrepli_c.h copy %1\vrepli_c.h %2\vrepline_c.h
if exist vreporto.h copy %1\vreporto.h %2\vreportobject.h
if exist vrptob_c.h copy %1\vrptob_c.h %2\vreportobject_c.h
if exist vreports.h copy %1\vreports.h %2\vreportscreen.h
if exist vrptos_c.h copy %1\vrptos_c.h %2\vreportscreen_c.h
if exist vreportp.h copy %1\vreportp.h %2\vreportppv.h
if exist vrptpp_c.h copy %1\vrptpp_c.h %2\vreportppv_c.h
if exist vreportt.h copy %1\vreportt.h %2\vreporttree.h
if exist vrpttr_c.h copy %1\vrpttr_c.h %2\vreporttree_c.h
if exist vrepor_c.h copy %1\vrepor_c.h %2\vreport_c.h
if exist vrptdv_c.h copy %1\vrptdv_c.h %2\vreportdevice_c.h
if exist vrptlo_c.h copy %1\vrptlo_c.h %2\vreportlayout_c.h
if exist vrepvar.h copy %1\vrepvar.h %2\vrepvar.h
if exist vrepva_c.h copy %1\vrepva_c.h %2\vrepvar_c.h
if exist vreputil.h copy %1\vreputil.h %2\vreputil.h
if exist vreput_c.h copy %1\vreput_c.h %2\vreputil_c.h
if exist vrereg.h copy %1\vrereg.h %2\vrereg.h
if exist vres.h copy %1\vres.h %2\vres.h
if exist vresfile.h copy %1\vresfile.h %2\vresfile.h
if exist vresfi_c.h copy %1\vresfi_c.h %2\vresfile_c.h
if exist vresolve.h copy %1\vresolve.h %2\vresolver.h
if exist vresol_c.h copy %1\vresol_c.h %2\vresolver_c.h
if exist vresourc.h copy %1\vresourc.h %2\vresource.h
if exist vresou_c.h copy %1\vresou_c.h %2\vresource_c.h
if exist vrestext.h copy %1\vrestext.h %2\vrestext.h
if exist vreutils.h copy %1\vreutils.h %2\vreutils.h
if exist vrl.h copy %1\vrl.h %2\vrl.h
if exist vrl_c.h copy %1\vrl_c.h %2\vrl_c.h
if exist vrtf.h copy %1\vrtf.h %2\vrtf.h
if exist vruler.h copy %1\vruler.h %2\vruler.h
if exist vruler_c.h copy %1\vruler_c.h %2\vruler_c.h
if exist vscrap.h copy %1\vscrap.h %2\vscrap.h
if exist vscrap_c.h copy %1\vscrap_c.h %2\vscrap_c.h
if exist vscribe.h copy %1\vscribe.h %2\vscribe.h
if exist vscrib_c.h copy %1\vscrib_c.h %2\vscribe_c.h
if exist vsepar.h copy %1\vsepar.h %2\vsepar.h
if exist vsepar_c.h copy %1\vsepar_c.h %2\vsepar_c.h
if exist vsequenc.h copy %1\vsequenc.h %2\vsequence.h
if exist vseque_c.h copy %1\vseque_c.h %2\vsequence_c.h
if exist vservice.h copy %1\vservice.h %2\vservice.h
if exist vservi_c.h copy %1\vservi_c.h %2\vservice_c.h
if exist vsvcchsr.h copy %1\vsvcchsr.h %2\vsvcchsr.h
if exist vsvcch_c.h copy %1\vsvcch_c.h %2\vsvcchsr_c.h
if exist vsession.h copy %1\vsession.h %2\vsession.h
if exist vsessi_c.h copy %1\vsessi_c.h %2\vsession_c.h
if exist vsetjmp.h copy %1\vsetjmp.h %2\vsetjmp.h
if exist vsignal.h copy %1\vsignal.h %2\vsignal.h
if exist vsiggrp.h copy %1\vsiggrp.h %2\vsiggrp.h
if exist vsiggr_c.h copy %1\vsiggr_c.h %2\vsiggrp_c.h
if exist vsignatu.h copy %1\vsignatu.h %2\vsignature.h
if exist vsigna_c.h copy %1\vsigna_c.h %2\vsignature_c.h
if exist vsingle.h copy %1\vsingle.h %2\vsingle.h
if exist vsizevie.h copy %1\vsizevie.h %2\vsizeview.h
if exist vsizev_c.h copy %1\vsizev_c.h %2\vsizeview_c.h
if exist vslider.h copy %1\vslider.h %2\vslider.h
if exist vslide_c.h copy %1\vslide_c.h %2\vslider_c.h
if exist vsock.h copy %1\vsock.h %2\vsock.h
if exist vsocksys.h copy %1\vsocksys.h %2\vsocksys.h
if exist vsockmac.h copy %1\vsockmac.h %2\vsockmac.h
if exist vsockos2.h copy %1\vsockos2.h %2\vsockos2.h
if exist vsocktcp.h copy %1\vsocktcp.h %2\vsocktcp.h
if exist vsockudp.h copy %1\vsockudp.h %2\vsockudp.h
if exist vsockunx.h copy %1\vsockunx.h %2\vsockunx.h
if exist vsockwin.h copy %1\vsockwin.h %2\vsockwin.h
if exist vspinner.h copy %1\vspinner.h %2\vspinner.h
if exist vspinn_c.h copy %1\vspinn_c.h %2\vspinner_c.h
if exist vsplit.h copy %1\vsplit.h %2\vsplit.h
if exist vsplit_c.h copy %1\vsplit_c.h %2\vsplit_c.h
if exist vsplitte.h copy %1\vsplitte.h %2\vsplitter.h
if exist vspring.h copy %1\vspring.h %2\vspring.h
if exist vsprin_c.h copy %1\vsprin_c.h %2\vspring_c.h
if exist vsprdom.h copy %1\vsprdom.h %2\vsprdom.h
if exist vsprdo_c.h copy %1\vsprdo_c.h %2\vsprdom_c.h
if exist vsprview.h copy %1\vsprview.h %2\vsprview.h
if exist vstartup.h copy %1\vstartup.h %2\vstartup.h
if exist vstart_c.h copy %1\vstart_c.h %2\vstartup_c.h
if exist vstatus.h copy %1\vstatus.h %2\vstatus.h
if exist vstatusb.h copy %1\vstatusb.h %2\vstatusbar.h
if exist vstatb_c.h copy %1\vstatb_c.h %2\vstatusbar_c.h
if exist vstd.h copy %1\vstd.h %2\vstd.h
if exist vstdarg.h copy %1\vstdarg.h %2\vstdarg.h
if exist vstddef.h copy %1\vstddef.h %2\vstddef.h
if exist vstdio.h copy %1\vstdio.h %2\vstdio.h
if exist vstdiosy.h copy %1\vstdiosy.h %2\vstdiosys.h
if exist vstdlib.h copy %1\vstdlib.h %2\vstdlib.h
if exist vstr.h copy %1\vstr.h %2\vstr.h
if exist vstr_c.h copy %1\vstr_c.h %2\vstr_c.h
if exist vstrchsr.h copy %1\vstrchsr.h %2\vstrchsr.h
if exist vstrch_c.h copy %1\vstrch_c.h %2\vstrchsr_c.h
if exist vstream.h copy %1\vstream.h %2\vstream.h
if exist vstrea_c.h copy %1\vstrea_c.h %2\vstream_c.h
if exist vstring.h copy %1\vstring.h %2\vstring.h
if exist vstritem.h copy %1\vstritem.h %2\vstritem.h
if exist vstrit_c.h copy %1\vstrit_c.h %2\vstritem_c.h
if exist vstylech.h copy %1\vstylech.h %2\vstylechsr.h
if exist vstyle_c.h copy %1\vstyle_c.h %2\vstylechsr_c.h
if exist vsys.h copy %1\vsys.h %2\vsys.h
if exist vsysdir.h copy %1\vsysdir.h %2\vsysdir.h
if exist vsysfile.h copy %1\vsysfile.h %2\vsysfile.h
if exist vsysioct.h copy %1\vsysioct.h %2\vsysioctl.h
if exist vsysipc.h copy %1\vsysipc.h %2\vsysipc.h
if exist vsysmnte.h copy %1\vsysmnte.h %2\vsysmntent.h
if exist vsyspara.h copy %1\vsyspara.h %2\vsysparam.h
if exist vsysreso.h copy %1\vsysreso.h %2\vsysresource.h
if exist vsyssele.h copy %1\vsyssele.h %2\vsysselect.h
if exist vsysshm.h copy %1\vsysshm.h %2\vsysshm.h
if exist vsyssock.h copy %1\vsyssock.h %2\vsyssocket.h
if exist vsysstat.h copy %1\vsysstat.h %2\vsysstat.h
if exist vsysinfo.h copy %1\vsysinfo.h %2\vsyssysteminfo.h
if exist vsystime.h copy %1\vsystime.h %2\vsystime.h
if exist vsystims.h copy %1\vsystims.h %2\vsystimes.h
if exist vsystype.h copy %1\vsystype.h %2\vsystypes.h
if exist vsysuio.h copy %1\vsysuio.h %2\vsysuio.h
if exist vsysun.h copy %1\vsysun.h %2\vsysun.h
if exist vsysutsn.h copy %1\vsysutsn.h %2\vsysutsname.h
if exist vsyswait.h copy %1\vsyswait.h %2\vsyswait.h
if exist vtablevi.h copy %1\vtablevi.h %2\vtableview.h
if exist vtblv_c.h copy %1\vtblv_c.h %2\vtableview_c.h
if exist vterm.h copy %1\vterm.h %2\vterm.h
if exist vtest.h copy %1\vtest.h %2\vtest.h
if exist vtest_c.h copy %1\vtest_c.h %2\vtest_c.h
if exist vtext.h copy %1\vtext.h %2\vtext.h
if exist vtext_c.h copy %1\vtext_c.h %2\vtext_c.h
if exist vtextite.h copy %1\vtextite.h %2\vtextitem.h
if exist vtexti_c.h copy %1\vtexti_c.h %2\vtextitem_c.h
if exist vtextmar.h copy %1\vtextmar.h %2\vtextmarker.h
if exist vtextm_c.h copy %1\vtextm_c.h %2\vtextmarker_c.h
if exist vtextrul.h copy %1\vtextrul.h %2\vtextruler.h
if exist vtextr_c.h copy %1\vtextr_c.h %2\vtextruler_c.h
if exist vtextsel.h copy %1\vtextsel.h %2\vtextsel.h
if exist vtexts_c.h copy %1\vtexts_c.h %2\vtextsel_c.h
if exist vtextvie.h copy %1\vtextvie.h %2\vtextview.h
if exist vtextv_c.h copy %1\vtextv_c.h %2\vtextview_c.h
if exist vthread.h copy %1\vthread.h %2\vthread.h
if exist vthrea_c.h copy %1\vthrea_c.h %2\vthread_c.h
if exist vthreade.h copy %1\vthreade.h %2\vthreader.h
if exist vthrdrss.h copy %1\vthrdrss.h %2\vthrdrss.h
if exist vthreads.h copy %1\vthreads.h %2\vthreadsys.h
if exist vthrds_c.h copy %1\vthrds_c.h %2\vthreadsys_c.h
if exist vtime.h copy %1\vtime.h %2\vtime.h
if exist vtimer.h copy %1\vtimer.h %2\vtimer.h
if exist vtimer_c.h copy %1\vtimer_c.h %2\vtimer_c.h
if exist vtimesta.h copy %1\vtimesta.h %2\vtimestamp.h
if exist vtimes_c.h copy %1\vtimes_c.h %2\vtimestamp_c.h
if exist vstmpsys.h copy %1\vstmpsys.h %2\vstmpsys.h
if exist vtoolbar.h copy %1\vtoolbar.h %2\vtoolbar.h
if exist vtoolb_c.h copy %1\vtoolb_c.h %2\vtoolbar_c.h
if exist vtbrearr.h copy %1\vtbrearr.h %2\vtbrearranger.h
if exist vtbrar_c.h copy %1\vtbrar_c.h %2\vtbrearranger_c.h
if exist vtbsepar.h copy %1\vtbsepar.h %2\vtbsepar.h
if exist vtbsep_c.h copy %1\vtbsep_c.h %2\vtbsepar_c.h
if exist vtoolbtn.h copy %1\vtoolbtn.h %2\vtoolbtn.h
if exist vtolbt_c.h copy %1\vtolbt_c.h %2\vtoolbtn_c.h
if exist vtolchgr.h copy %1\vtolchgr.h %2\vtoolchanger.h
if exist vtolch_c.h copy %1\vtolch_c.h %2\vtoolchanger_c.h
if exist vtooltip.h copy %1\vtooltip.h %2\vtooltip.h
if exist vtoolt_c.h copy %1\vtoolt_c.h %2\vtooltip_c.h
if exist vtransfo.h copy %1\vtransfo.h %2\vtransform.h
if exist vtrans_c.h copy %1\vtrans_c.h %2\vtransform_c.h
if exist vtrans.h copy %1\vtrans.h %2\vtrans.h
if exist vtrnsl_c.h copy %1\vtrnsl_c.h %2\vtrans_c.h
if exist vtree.h copy %1\vtree.h %2\vtree.h
if exist vtree_c.h copy %1\vtree_c.h %2\vtree_c.h
if exist vtreecar.h copy %1\vtreecar.h %2\vtreecard.h
if exist vtreec_c.h copy %1\vtreec_c.h %2\vtreecard_c.h
if exist vtreelis.h copy %1\vtreelis.h %2\vtreelist.h
if exist vtreel_c.h copy %1\vtreel_c.h %2\vtreelist_c.h
if exist vtreevie.h copy %1\vtreevie.h %2\vtreeview.h
if exist vtreev_c.h copy %1\vtreev_c.h %2\vtreeview_c.h
if exist vtypedit.h copy %1\vtypedit.h %2\vtypeditem.h
if exist vtypdi_c.h copy %1\vtypdi_c.h %2\vtypeditem_c.h
if exist vulimit.h copy %1\vulimit.h %2\vulimit.h
if exist vulongit.h copy %1\vulongit.h %2\vulongitem.h
if exist vulngi_c.h copy %1\vulngi_c.h %2\vulongitem_c.h
if exist vundo.h copy %1\vundo.h %2\vundo.h
if exist vundo_c.h copy %1\vundo_c.h %2\vundo_c.h
if exist vundocom.h copy %1\vundocom.h %2\vundocompat.h
if exist vunistd.h copy %1\vunistd.h %2\vunistd.h
if exist vurl.h copy %1\vurl.h %2\vurl.h
if exist vurl_c.h copy %1\vurl_c.h %2\vurl_c.h
if exist vut.h copy %1\vut.h %2\vut.h
if exist vutime.h copy %1\vutime.h %2\vutime.h
if exist vvalues.h copy %1\vvalues.h %2\vvalues.h
if exist vvarray.h copy %1\vvarray.h %2\vvarray.h
if exist vvaxfloa.h copy %1\vvaxfloa.h %2\vvaxfloat.h
if exist vvint.h copy %1\vvint.h %2\vvint.h
if exist vvmstype.h copy %1\vvmstype.h %2\vvmstypes.h
if exist vwaitos2.h copy %1\vwaitos2.h %2\vwaitos2.h
if exist vwaitunx.h copy %1\vwaitunx.h %2\vwaitunx.h
if exist vwebbrow.h copy %1\vwebbrow.h %2\vwebbrowse.h
if exist vwebbr_c.h copy %1\vwebbr_c.h %2\vwebbrowse_c.h
if exist vwindow.h copy %1\vwindow.h %2\vwindow.h
if exist vwindo_c.h copy %1\vwindo_c.h %2\vwindow_c.h
if exist vwindows.h copy %1\vwindows.h %2\vwindowsys.h
if exist vx11.h copy %1\vx11.h %2\vx11.h
if exist vx11curs.h copy %1\vx11curs.h %2\vx11cursorfont.h
if exist vx11exte.h copy %1\vx11exte.h %2\vx11extensionsxshm.h
if exist vx11keys.h copy %1\vx11keys.h %2\vx11keysym.h
if exist vx11xato.h copy %1\vx11xato.h %2\vx11xatom.h
if exist vx11xlib.h copy %1\vx11xlib.h %2\vx11xlib.h
if exist vx11xuti.h copy %1\vx11xuti.h %2\vx11xutil.h
if exist vxxloada.h copy %1\vxxloada.h %2\vxxloadable.h

:END

