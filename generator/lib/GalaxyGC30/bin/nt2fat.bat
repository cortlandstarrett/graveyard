@echo off 

@echo "Shrinking include file names to 8.3 format for FAT system.        "

if not "%1" == "" goto INSTALL1

@echo "                                                                 "
@echo "ERROR: Invalid Syntax                                            " 
@echo "                                                                 " 
@echo "    To modify files in same directory:                           " 
@echo "        nt2fat <include path>                                    "
@echo "    ex. nt2fat c:\galaxy\include                               "
@echo "                                                                 "
@echo "    To copy and modify header files to a new directory:          "
@echo "        nt2fat <full src path> <full dest path>                  "
@echo "    ex. nt2fat c:\galaxy\include d:\galaxy\include           "
goto END

:INSTALL1
if not "%2" == "" goto COPYINSTALL

cd %1

copy vhdr83.h vhdrmode.h

if exist vabstract.h if exist vabstrac.h del vabstrac.h
if exist vabstract.h rename vabstract.h vabstrac.h
if exist vaccept_c.h if exist vaccep_c.h del vaccep_c.h
if exist vaccept_c.h rename vaccept_c.h vaccep_c.h
if exist vappframe.h if exist vappfram.h del vappfram.h
if exist vappframe.h rename vappframe.h vappfram.h
if exist vappframe_c.h if exist vappfr_c.h del vappfr_c.h
if exist vappframe_c.h rename vappframe_c.h vappfr_c.h
if exist vapplication.h if exist vapplica.h del vapplica.h
if exist vapplication.h rename vapplication.h vapplica.h
if exist vapplication_c.h if exist vappli_c.h del vappli_c.h
if exist vapplication_c.h rename vapplication_c.h vappli_c.h
if exist vargscrap.h if exist vargscra.h del vargscra.h
if exist vargscrap.h rename vargscrap.h vargscra.h
if exist varpainet.h if exist varpaine.h del varpaine.h
if exist varpainet.h rename varpainet.h varpaine.h
if exist vattribute.h if exist vattribu.h del vattribu.h
if exist vattribute.h rename vattribute.h vattribu.h
if exist vattribute_c.h if exist vattri_c.h del vattri_c.h
if exist vattribute_c.h rename vattribute_c.h vattri_c.h
if exist vboolitem.h if exist vboolite.h del vboolite.h
if exist vboolitem.h rename vboolitem.h vboolite.h
if exist vboolitem_c.h if exist vbooli_c.h del vbooli_c.h
if exist vboolitem_c.h rename vboolitem_c.h vbooli_c.h
if exist vbuffer_c.h if exist vbuffe_c.h del vbuffe_c.h
if exist vbuffer_c.h rename vbuffer_c.h vbuffe_c.h
if exist vbuildstrs.h if exist vbuildst.h del vbuildst.h
if exist vbuildstrs.h rename vbuildstrs.h vbuildst.h
if exist vbuildstrs.c if exist vbuildst.c del vbuildst.c
if exist vbuildstrs.c rename vbuildstrs.c vbuildst.c
if exist vbutton_c.h if exist vbutto_c.h del vbutto_c.h
if exist vbutton_c.h rename vbutton_c.h vbutto_c.h
if exist vcanvas_c.h if exist vcanva_c.h del vcanva_c.h
if exist vcanvas_c.h rename vcanvas_c.h vcanva_c.h
if exist vcharencoding.h if exist vcharenc.h del vcharenc.h
if exist vcharencoding.h rename vcharencoding.h vcharenc.h
if exist vcharencoding_c.h if exist vchare_c.h del vchare_c.h
if exist vcharencoding_c.h rename vcharencoding_c.h vchare_c.h
if exist vclassextra.h if exist vclassex.h del vclassex.h
if exist vclassextra.h rename vclassextra.h vclassex.h
if exist vclassinfo.h if exist vclassin.h del vclassin.h
if exist vclassinfo.h rename vclassinfo.h vclassin.h
if exist vclassreg.h if exist vclassre.h del vclassre.h
if exist vclassreg.h rename vclassreg.h vclassre.h
if exist vclient_c.h if exist vclien_c.h del vclien_c.h
if exist vclient_c.h rename vclient_c.h vclien_c.h
if exist vclipboard.h if exist vclipboa.h del vclipboa.h
if exist vclipboard.h rename vclipboard.h vclipboa.h
if exist vclipboard_c.h if exist vclipb_c.h del vclipb_c.h
if exist vclipboard_c.h rename vclipboard_c.h vclipb_c.h
if exist vcmdchsr_c.h if exist vcmdch_c.h del vcmdch_c.h
if exist vcmdchsr_c.h rename vcmdchsr_c.h vcmdch_c.h
if exist vcolorchsr.h if exist vcolorch.h del vcolorch.h
if exist vcolorchsr.h rename vcolorchsr.h vcolorch.h
if exist vcolorchsr_c.h if exist vcolch_c.h del vcolch_c.h
if exist vcolorchsr_c.h rename vcolorchsr_c.h vcolch_c.h
if exist vcolorsys.h if exist vcolorsy.h del vcolorsy.h
if exist vcolorsys.h rename vcolorsys.h vcolorsy.h
if exist vcombobox.h if exist vcombobo.h del vcombobo.h
if exist vcombobox.h rename vcombobox.h vcombobo.h
if exist vcombobox_c.h if exist vcombx_c.h del vcombx_c.h
if exist vcombobox_c.h rename vcombobox_c.h vcombx_c.h
if exist vcommchn_c.h if exist vcommc_c.h del vcommc_c.h
if exist vcommchn_c.h rename vcommchn_c.h vcommc_c.h
if exist vcommand_c.h if exist vcomma_c.h del vcomma_c.h
if exist vcommand_c.h rename vcommand_c.h vcomma_c.h
if exist vcondition.h if exist vconditi.h del vconditi.h
if exist vcondition.h rename vcondition.h vconditi.h
if exist vconfirm_c.h if exist vconfi_c.h del vconfi_c.h
if exist vconfirm_c.h rename vconfirm_c.h vconfi_c.h
if exist vctrgrid_c.h if exist vctrgr_c.h del vctrgr_c.h
if exist vctrgrid_c.h rename vctrgrid_c.h vctrgr_c.h
if exist vcontain_c.h if exist vconta_c.h del vconta_c.h
if exist vcontain_c.h rename vcontain_c.h vconta_c.h
if exist vcontrol_c.h if exist vcontr_c.h del vcontr_c.h
if exist vcontrol_c.h rename vcontrol_c.h vcontr_c.h
if exist vctlchsr_c.h if exist vctlch_c.h del vctlch_c.h
if exist vctlchsr_c.h rename vctlchsr_c.h vctlch_c.h
if exist vcursor_c.h if exist vcurso_c.h del vcurso_c.h
if exist vcursor_c.h rename vcursor_c.h vcurso_c.h
if exist vdasserv_c.h if exist vdasse_c.h del vdasse_c.h
if exist vdasserv_c.h rename vdasserv_c.h vdasse_c.h
if exist vdschsr_c.h if exist vdschs_c.h del vdschs_c.h
if exist vdschsr_c.h rename vdschsr_c.h vdschs_c.h
if exist vdsdata_c.h if exist vdsdat_c.h del vdsdat_c.h
if exist vdsdata_c.h rename vdsdata_c.h vdsdat_c.h
if exist vdsdbeng_c.h if exist vdsdbe_c.h del vdsdbe_c.h
if exist vdsdbeng_c.h rename vdsdbeng_c.h vdsdbe_c.h
if exist vdsfseng_c.h if exist vdsfse_c.h del vdsfse_c.h
if exist vdsfseng_c.h rename vdsfseng_c.h vdsfse_c.h
if exist vdatasource.h if exist vdatasou.h del vdatasou.h
if exist vdatasource.h rename vdatasource.h vdatasou.h
if exist vdsuieng_c.h if exist vdsuie_c.h del vdsuie_c.h
if exist vdsuieng_c.h rename vdsuieng_c.h vdsuie_c.h
if exist vdatasource_c.h if exist vdatas_c.h del vdatas_c.h
if exist vdatasource_c.h rename vdatasource_c.h vdatas_c.h
if exist vdatatag_c.h if exist vdatat_c.h del vdatat_c.h
if exist vdatatag_c.h rename vdatatag_c.h vdatat_c.h
if exist vdateitem.h if exist vdateite.h del vdateite.h
if exist vdateitem.h rename vdateitem.h vdateite.h
if exist vdateitem_c.h if exist vdatei_c.h del vdatei_c.h
if exist vdateitem_c.h rename vdateitem_c.h vdatei_c.h
if exist vdbchsr_c.h if exist vdbchs_c.h del vdbchs_c.h
if exist vdbchsr_c.h rename vdbchsr_c.h vdbchs_c.h
if exist vdbcombobox.h if exist vdbcombo.h del vdbcombo.h
if exist vdbcombobox.h rename vdbcombobox.h vdbcombo.h
if exist vdbspinner.h if exist vdbspinn.h del vdbspinn.h
if exist vdbspinner.h rename vdbspinner.h vdbspinn.h
if exist vdelegator.h if exist vdelegat.h del vdelegat.h
if exist vdelegator.h rename vdelegator.h vdelegat.h
if exist vdelegator_c.h if exist vdeleg_c.h del vdeleg_c.h
if exist vdelegator_c.h rename vdelegator_c.h vdeleg_c.h
if exist vdialog_c.h if exist vdialo_c.h del vdialo_c.h
if exist vdialog_c.h rename vdialog_c.h vdialo_c.h
if exist vdockcont.h if exist vdockcnt.h del vdockcnt.h
if exist vdockcont.h rename vdockcont.h vdockcnt.h
if exist vdockcont_c.h if exist vdockc_c.h del vdockc_c.h
if exist vdockcont_c.h rename vdockcont_c.h vdockc_c.h
if exist vdocker_c.h if exist vdocke_c.h del vdocke_c.h
if exist vdocker_c.h rename vdocker_c.h vdocke_c.h
if exist vdockitem.h if exist vdockitm.h del vdockitm.h
if exist vdockitem.h rename vdockitem.h vdockitm.h
if exist vdockitem_c.h if exist vdocki_c.h del vdocki_c.h
if exist vdockitem_c.h rename vdockitem_c.h vdocki_c.h
if exist vdomain_c.h if exist vdomai_c.h del vdomai_c.h
if exist vdomain_c.h rename vdomain_c.h vdomai_c.h
if exist vdomitem_c.h if exist vdomit_c.h del vdomit_c.h
if exist vdomitem_c.h rename vdomitem_c.h vdomit_c.h
if exist vdomview_c.h if exist vdomvi_c.h del vdomvi_c.h
if exist vdomview_c.h rename vdomview_c.h vdomvi_c.h
if exist vdoubleitem.h if exist vdblitem.h del vdblitem.h
if exist vdoubleitem.h rename vdoubleitem.h vdblitem.h
if exist vdoubleitem_c.h if exist vdblit_c.h del vdblit_c.h
if exist vdoubleitem_c.h rename vdoubleitem_c.h vdblit_c.h
if exist vdrawcontext.h if exist vdrawcon.h del vdrawcon.h
if exist vdrawcontext.h rename vdrawcontext.h vdrawcon.h
if exist vdrawcontext_c.h if exist vdrwco_c.h del vdrwco_c.h
if exist vdrawcontext_c.h rename vdrawcontext_c.h vdrwco_c.h
if exist vdrawpath.h if exist vdrawpat.h del vdrawpat.h
if exist vdrawpath.h rename vdrawpath.h vdrawpat.h
if exist vdrawpath_c.h if exist vdrwpa_c.h del vdrwpa_c.h
if exist vdrawpath_c.h rename vdrawpath_c.h vdrwpa_c.h
if exist vdrawpen_c.h if exist vdrwpe_c.h del vdrwpe_c.h
if exist vdrawpen_c.h rename vdrawpen_c.h vdrwpe_c.h
if exist vdrawrectset.h if exist vdrawrec.h del vdrawrec.h
if exist vdrawrectset.h rename vdrawrectset.h vdrawrec.h
if exist vdrawrectset_c.h if exist vdrwre_c.h del vdrwre_c.h
if exist vdrawrectset_c.h rename vdrawrectset_c.h vdrwre_c.h
if exist vdropsite.h if exist vdropsit.h del vdropsit.h
if exist vdropsite.h rename vdropsite.h vdropsit.h
if exist vdropsite_c.h if exist vdrops_c.h del vdrops_c.h
if exist vdropsite_c.h rename vdropsite_c.h vdrops_c.h
if exist vdropsite.h if exist vdropsit.h del vdropsit.h
if exist vdropsite.h rename vdropsite.h vdropsit.h
if exist vdropsite_c.h if exist vdrops_c.h del vdrops_c.h
if exist vdropsite_c.h rename vdropsite_c.h vdrops_c.h
if exist vdsdbeng_c.h if exist vdsdbe_c.h del vdsdbe_c.h
if exist vdsdbeng_c.h rename vdsdbeng_c.h vdsdbe_c.h
if exist vdsfseng_c.h if exist vdsfse_c.h del vdsfse_c.h
if exist vdsfseng_c.h rename vdsfseng_c.h vdsfse_c.h
if exist vdsuieng_c.h if exist vdsuie_c.h del vdsuie_c.h
if exist vdsuieng_c.h rename vdsuieng_c.h vdsuie_c.h
if exist vevent2_c.h if exist veven2_c.h del veven2_c.h
if exist vevent2_c.h rename vevent2_c.h veven2_c.h
if exist vevent2sys.h if exist vevent2s.h del vevent2s.h
if exist vevent2sys.h rename vevent2sys.h vevent2s.h
if exist vevent2sys_c.h if exist vevn2s_c.h del vevn2s_c.h
if exist vevent2sys_c.h rename vevent2sys_c.h vevn2s_c.h
if exist veventsys.h if exist veventsy.h del veventsy.h
if exist veventsys.h rename veventsys.h veventsy.h
if exist veventsys_c.h if exist vevnsy_c.h del vevnsy_c.h
if exist veventsys_c.h rename veventsys_c.h vevnsy_c.h
if exist vevntitr_c.h if exist vevnti_c.h del vevnti_c.h
if exist vevntitr_c.h rename vevntitr_c.h vevnti_c.h
if exist vfilechsr.h if exist vfilechs.h del vfilechs.h
if exist vfilechsr.h rename vfilechsr.h vfilechs.h
if exist vfilechsr_c.h if exist vfilec_c.h del vfilec_c.h
if exist vfilechsr_c.h rename vfilechsr_c.h vfilec_c.h
if exist vfontchsr.h if exist vfontchs.h del vfontchs.h
if exist vfontchsr.h rename vfontchsr.h vfontchs.h
if exist vfontchsr_c.h if exist vfontc_c.h del vfontc_c.h
if exist vfontchsr_c.h rename vfontchsr_c.h vfontc_c.h
if exist vfontspec.h if exist vfontspe.h del vfontspe.h
if exist vfontspec.h rename vfontspec.h vfontspe.h
if exist vfontspec_c.h if exist vfonts_c.h del vfonts_c.h
if exist vfontspec_c.h rename vfontspec_c.h vfonts_c.h
if exist vformctxt.h if exist vfrmctxt.h del vfrmctxt.h
if exist vformctxt.h rename vformctxt.h vfrmctxt.h
if exist vformctxt_c.h if exist vfrmct_c.h del vfrmct_c.h
if exist vformctxt_c.h rename vformctxt_c.h vfrmct_c.h
if exist vformat_c.h if exist vforma_c.h del vforma_c.h
if exist vformat_c.h rename vformat_c.h vforma_c.h
if exist vgridcont.h if exist vgridcon.h del vgridcon.h
if exist vgridcont.h rename vgridcont.h vgridcon.h
if exist vgridcont_c.h if exist vgridc_c.h del vgridc_c.h
if exist vgridcont_c.h rename vgridcont_c.h vgridc_c.h
if exist vgridmodel.h if exist vgridmod.h del vgridmod.h
if exist vgridmodel.h rename vgridmodel.h vgridmod.h
if exist vgridmodel_c.h if exist vgridm_c.h del vgridm_c.h
if exist vgridmodel_c.h rename vgridmodel_c.h vgridm_c.h
if exist vhelpdisplay.h if exist vhelpdis.h del vhelpdis.h
if exist vhelpdisplay.h rename vhelpdisplay.h vhelpdis.h
if exist vhelpdisplay_c.h if exist vhpdis_c.h del vhpdis_c.h
if exist vhelpdisplay_c.h rename vhelpdisplay_c.h vhpdis_c.h
if exist vhelpdefault.h if exist vhelpdef.h del vhelpdef.h
if exist vhelpdefault.h rename vhelpdefault.h vhelpdef.h
if exist vhelpdefault_c.h if exist vhpdef_c.h del vhpdef_c.h
if exist vhelpdefault_c.h rename vhelpdefault_c.h vhpdef_c.h
if exist vhelpexplorer.h if exist vhelpexp.h del vhelpexp.h
if exist vhelpexplorer.h rename vhelpexplorer.h vhelpexp.h
if exist vhelpexplorer_c.h if exist vhpexp_c.h del vhpexp_c.h
if exist vhelpexplorer_c.h rename vhelpexplorer_c.h vhpexp_c.h
if exist vhelpgalaxy.h if exist vhelpgal.h del vhelpgal.h
if exist vhelpgalaxy.h rename vhelpgalaxy.h vhelpgal.h
if exist vhelpgalaxy_c.h if exist vhpgal_c.h del vhpgal_c.h
if exist vhelpgalaxy_c.h rename vhelpgalaxy_c.h vhpgal_c.h
if exist vhelphtmlgalaxy.h if exist vhelphtg.h del vhelphtg.h
if exist vhelphtmlgalaxy.h rename vhelphtmlgalaxy.h vhelphtg.h
if exist vhelphtmlgalaxy_c.h if exist vhphtg_c.h del vhphtg_c.h
if exist vhelphtmlgalaxy_c.h rename vhelphtmlgalaxy_c.h vhphtg_c.h
if exist vhelphtmllocator.h if exist vhelphtl.h del vhelphtl.h
if exist vhelphtmllocator.h rename vhelphtmllocator.h vhelphtl.h
if exist vhelphtmllocator_c.h if exist vhphtl_c.h del vhphtl_c.h
if exist vhelphtmllocator_c.h rename vhelphtmllocator_c.h vhphtl_c.h
if exist vhelphypertext.h if exist vhelphyp.h del vhelphyp.h
if exist vhelphypertext.h rename vhelphypertext.h vhelphyp.h
if exist vhelphypertext_c.h if exist vhphyp_c.h del vhphyp_c.h
if exist vhelphypertext_c.h rename vhelphypertext_c.h vhphyp_c.h
if exist vhelplinker.h if exist vhelplin.h del vhelplin.h
if exist vhelplinker.h rename vhelplinker.h vhelplin.h
if exist vhelplocator.h if exist vhelploc.h del vhelploc.h
if exist vhelplocator.h rename vhelplocator.h vhelploc.h
if exist vhelplocator_c.h if exist vhploc_c.h del vhploc_c.h
if exist vhelplocator_c.h rename vhelplocator_c.h vhploc_c.h
if exist vhelpnetscape.h if exist vhelpnet.h del vhelpnet.h
if exist vhelpnetscape.h rename vhelpnetscape.h vhelpnet.h
if exist vhelpnetscape_c.h if exist vhpnet_c.h del vhpnet_c.h
if exist vhelpnetscape_c.h rename vhelpnetscape_c.h vhpnet_c.h
if exist vhelpobject.h if exist vhelpobj.h del vhelpobj.h
if exist vhelpobject.h rename vhelpobject.h vhelpobj.h
if exist vhelpobject_c.h if exist vhpobj_c.h del vhpobj_c.h
if exist vhelpobject_c.h rename vhelpobject_c.h vhpobj_c.h
if exist vhelpref_c.h if exist vhpref_c.h del vhpref_c.h
if exist vhelpref_c.h rename vhelpref_c.h vhpref_c.h
if exist vhelpreflocator.h if exist vhelprfl.h del vhelprfl.h
if exist vhelpreflocator.h rename vhelpreflocator.h vhelprfl.h
if exist vhelpreflocator_c.h if exist vhprfl_c.h del vhprfl_c.h
if exist vhelpreflocator_c.h rename vhelpreflocator_c.h vhprfl_c.h
if exist vhelpregistry.h if exist vhelpreg.h del vhelpreg.h
if exist vhelpregistry.h rename vhelpregistry.h vhelpreg.h
if exist vhelpregistry_c.h if exist vhpreg_c.h del vhpreg_c.h
if exist vhelpregistry_c.h rename vhelpregistry_c.h vhpreg_c.h
if exist vhelprequest.h if exist vhelpreq.h del vhelpreq.h
if exist vhelprequest.h rename vhelprequest.h vhelpreq.h
if exist vhelprequest_c.h if exist vhpreq_c.h del vhpreq_c.h
if exist vhelprequest_c.h rename vhelprequest_c.h vhpreq_c.h
if exist vhelpstatus.h if exist vhelpsta.h del vhelpsta.h
if exist vhelpstatus.h rename vhelpstatus.h vhelpsta.h
if exist vhelpstatus_c.h if exist vhpsta_c.h del vhpsta_c.h
if exist vhelpstatus_c.h rename vhelpstatus_c.h vhpsta_c.h
if exist vhelptext.h if exist vhelptex.h del vhelptex.h
if exist vhelptext.h rename vhelptext.h vhelptex.h
if exist vhelptext_c.h if exist vhptex_c.h del vhptex_c.h
if exist vhelptext_c.h rename vhelptext_c.h vhptex_c.h
if exist vhelptextlocator.h if exist vhelptxl.h del vhelptxl.h
if exist vhelptextlocator.h rename vhelptextlocator.h vhelptxl.h
if exist vhelptextlocator_c.h if exist vhptxl_c.h del vhptxl_c.h
if exist vhelptextlocator_c.h rename vhelptextlocator_c.h vhptxl_c.h
if exist vhelptooltip.h if exist vhelptip.h del vhelptip.h
if exist vhelptooltip.h rename vhelptooltip.h vhelptip.h
if exist vhelptooltip_c.h if exist vhptip_c.h del vhptip_c.h
if exist vhelptooltip_c.h rename vhelptooltip_c.h vhptip_c.h
if exist vhelptrans.h if exist vhelptra.h del vhelptra.h
if exist vhelptrans.h rename vhelptrans.h vhelptra.h
if exist vhelpwinhelp.h if exist vhelpwin.h del vhelpwin.h
if exist vhelpwinhelp.h rename vhelpwinhelp.h vhelpwin.h
if exist vhelpwinhelp_c.h if exist vhpwin_c.h del vhpwin_c.h
if exist vhelpwinhelp_c.h rename vhelpwinhelp_c.h vhpwin_c.h
if exist vhexchsr_c.h if exist vhexch_c.h del vhexch_c.h
if exist vhexchsr_c.h rename vhexchsr_c.h vhexch_c.h
if exist viconview.h if exist viconvie.h del viconvie.h
if exist viconview.h rename viconview.h viconvie.h
if exist viconview_c.h if exist viconv_c.h del viconv_c.h
if exist viconview_c.h rename viconview_c.h viconv_c.h
if exist vimageed_c.h if exist vimagd_c.h del vimagd_c.h
if exist vimageed_c.h rename vimageed_c.h vimagd_c.h
if exist vimgedutils.h if exist vimgedut.h del vimgedut.h
if exist vimgedutils.h rename vimgedutils.h vimgedut.h
if exist vimgutils.h if exist vimgutil.h del vimgutil.h
if exist vimgutils.h rename vimgutils.h vimgutil.h
if exist vinputsys.h if exist vinputsy.h del vinputsy.h
if exist vinputsys.h rename vinputsys.h vinputsy.h
if exist vinstall_c.h if exist vinstl_c.h del vinstl_c.h
if exist vinstall_c.h rename vinstall_c.h vinstl_c.h
if exist vinstance.h if exist vinstanc.h del vinstanc.h
if exist vinstance.h rename vinstance.h vinstanc.h
if exist vinstance_c.h if exist vinsta_c.h del vinsta_c.h
if exist vinstance_c.h rename vinstance_c.h vinsta_c.h
if exist vinterface.h if exist vinterfa.h del vinterfa.h
if exist vinterface.h rename vinterface.h vinterfa.h
if exist vinterface_c.h if exist vinter_c.h del vinter_c.h
if exist vinterface_c.h rename vinterface_c.h vinter_c.h
if exist viterator.h if exist viterato.h del viterato.h
if exist viterator.h rename viterator.h viterato.h
if exist viterator_c.h if exist vitera_c.h del vitera_c.h
if exist viterator_c.h rename viterator_c.h vitera_c.h
if exist vkeyitem_c.h if exist vkeyit_c.h del vkeyit_c.h
if exist vkeyitem_c.h rename vkeyitem_c.h vkeyit_c.h
if exist vlistedit.h if exist vlistedi.h del vlistedi.h
if exist vlistedit.h rename vlistedit.h vlistedi.h
if exist vlistitem.h if exist vlistite.h del vlistite.h
if exist vlistitem.h rename vlistitem.h vlistite.h
if exist vlistitem_c.h if exist vlisti_c.h del vlisti_c.h
if exist vlistitem_c.h rename vlistitem_c.h vlisti_c.h
if exist vlistsel_c.h if exist vlistn_c.h del vlistn_c.h
if exist vlistsel_c.h rename vlistsel_c.h vlistn_c.h
if exist vlistsize.h if exist vlistsiz.h del vlistsiz.h
if exist vlistsize.h rename vlistsize.h vlistsiz.h
if exist vlistsize_c.h if exist vlistz_c.h del vlistz_c.h
if exist vlistsize_c.h rename vlistsize_c.h vlistz_c.h
if exist vliststr_c.h if exist vlists_c.h del vlists_c.h
if exist vliststr_c.h rename vliststr_c.h vlists_c.h
if exist vlistview.h if exist vlistvie.h del vlistvie.h
if exist vlistview.h rename vlistview.h vlistvie.h
if exist vlistview_c.h if exist vlistv_c.h del vlistv_c.h
if exist vlistview_c.h rename vlistview_c.h vlistv_c.h
if exist vloadable.h if exist vloadabl.h del vloadabl.h
if exist vloadable.h rename vloadable.h vloadabl.h
if exist vloadable_c.h if exist vloada_c.h del vloada_c.h
if exist vloadable_c.h rename vloadable_c.h vloada_c.h
if exist vlongitem.h if exist vlongite.h del vlongite.h
if exist vlongitem.h rename vlongitem.h vlongite.h
if exist vlongitem_c.h if exist vlongi_c.h del vlongi_c.h
if exist vlongitem_c.h rename vlongitem_c.h vlongi_c.h
if exist vlonglong.h if exist vlonglon.h del vlonglon.h
if exist vlonglong.h rename vlonglong.h vlonglon.h
if exist vlonglong_c.h if exist vlongl_c.h del vlongl_c.h
if exist vlonglong_c.h rename vlonglong_c.h vlongl_c.h
if exist vmaccontrols.h if exist vmaccont.h del vmaccont.h
if exist vmaccontrols.h rename vmaccontrols.h vmaccont.h
if exist vmacdialogs.h if exist vmacdial.h del vmacdial.h
if exist vmacdialogs.h rename vmacdialogs.h vmacdial.h
if exist vmacerrors.h if exist vmacerro.h del vmacerro.h
if exist vmacerrors.h rename vmacerrors.h vmacerro.h
if exist vmacevents.h if exist vmaceven.h del vmaceven.h
if exist vmacevents.h rename vmacevents.h vmaceven.h
if exist vmacfiles.h if exist vmacfile.h del vmacfile.h
if exist vmacfiles.h rename vmacfiles.h vmacfile.h
if exist vmacfonts.h if exist vmacfont.h del vmacfont.h
if exist vmacfonts.h rename vmacfonts.h vmacfont.h
if exist vmacgestaltequ.h if exist vmacgest.h del vmacgest.h
if exist vmacgestaltequ.h rename vmacgestaltequ.h vmacgest.h
if exist vmachine_c.h if exist vmachi_c.h del vmachi_c.h
if exist vmachine_c.h rename vmachine_c.h vmachi_c.h
if exist vmacmemory.h if exist vmacmemo.h del vmacmemo.h
if exist vmacmemory.h rename vmacmemory.h vmacmemo.h
if exist vmacquickdraw.h if exist vmacquic.h del vmacquic.h
if exist vmacquickdraw.h rename vmacquickdraw.h vmacquic.h
if exist vmacresources.h if exist vmacreso.h del vmacreso.h
if exist vmacresources.h rename vmacresources.h vmacreso.h
if exist vmacscript.h if exist vmacscri.h del vmacscri.h
if exist vmacscript.h rename vmacscript.h vmacscri.h
if exist vmacstrings.h if exist vmacstri.h del vmacstri.h
if exist vmacstrings.h rename vmacstrings.h vmacstri.h
if exist vmacsysequ.h if exist vmacsyse.h del vmacsyse.h
if exist vmacsysequ.h rename vmacsysequ.h vmacsyse.h
if exist vmactypes.h if exist vmactype.h del vmactype.h
if exist vmactypes.h rename vmactypes.h vmactype.h
if exist vmacwindows.h if exist vmacwind.h del vmacwind.h
if exist vmacwindows.h rename vmacwindows.h vmacwind.h
if exist vmainvie_c.h if exist vmainv_c.h del vmainv_c.h
if exist vmainvie_c.h rename vmainvie_c.h vmainv_c.h
if exist vmapping_c.h if exist vmappi_c.h del vmappi_c.h
if exist vmapping_c.h rename vmapping_c.h vmappi_c.h
if exist vmaskitem.h if exist vmaskite.h del vmaskite.h
if exist vmaskitem.h rename vmaskitem.h vmaskite.h
if exist vmaskitem_c.h if exist vmaski_c.h del vmaski_c.h
if exist vmaskitem_c.h rename vmaskitem_c.h vmaski_c.h
if exist vmatrix_c.h if exist vmatri_c.h del vmatri_c.h
if exist vmatrix_c.h rename vmatrix_c.h vmatri_c.h
if exist vmenubar_c.h if exist vmenub_c.h del vmenub_c.h
if exist vmenubar_c.h rename vmenubar_c.h vmenub_c.h
if exist vmodule_c.h if exist vmodul_c.h del vmodul_c.h
if exist vmodule_c.h rename vmodule_c.h vmodul_c.h
if exist vmutexsys.h if exist vmutexsy.h del vmutexsy.h
if exist vmutexsys.h rename vmutexsys.h vmutexsy.h
if exist vnameobj_c.h if exist vnameo_c.h del vnameo_c.h
if exist vnameobj_c.h rename vnameobj_c.h vnameo_c.h
if exist vnetinetin.h if exist vnetinet.h del vnetinet.h
if exist vnetinetin.h rename vnetinetin.h vnetinet.h
if exist vnotebook.h if exist vnoteboo.h del vnoteboo.h
if exist vnotebook.h rename vnotebook.h vnoteboo.h
if exist vnotebook_c.h if exist vnoteb_c.h del vnoteb_c.h
if exist vnotebook_c.h rename vnotebook_c.h vnoteb_c.h
if exist vnotice_c.h if exist vnotic_c.h del vnotic_c.h
if exist vnotice_c.h rename vnotice_c.h vnotic_c.h
if exist vobject_c.h if exist vobjec_c.h del vobjec_c.h
if exist vobject_c.h rename vobject_c.h vobjec_c.h
if exist vobservable.h if exist vobserva.h del vobserva.h
if exist vobservable.h rename vobservable.h vobserva.h
if exist vobservable_c.h if exist vobsab_c.h del vobsab_c.h
if exist vobservable_c.h rename vobservable_c.h vobsab_c.h
if exist vobserver.h if exist vobserve.h del vobserve.h
if exist vobserver.h rename vobserver.h vobserve.h
if exist vobserver_c.h if exist vobser_c.h del vobser_c.h
if exist vobserver_c.h rename vobserver_c.h vobser_c.h
if exist voccurrence.h if exist voccurre.h del voccurre.h
if exist voccurrence.h rename voccurrence.h voccurre.h
if exist voccurrence_c.h if exist voccur_c.h del voccur_c.h
if exist voccurrence_c.h rename voccurrence_c.h voccur_c.h
if exist volectrl_c.h if exist volect_c.h del volect_c.h
if exist volectrl_c.h rename volectrl_c.h volect_c.h
if exist volesite_c.h if exist volesi_c.h del volesi_c.h
if exist volesite_c.h rename volesite_c.h volesi_c.h
if exist volevariant.h if exist volevari.h del volevari.h
if exist volevariant.h rename volevariant.h volevari.h
if exist volevariant_c.h if exist voleva_c.h del voleva_c.h
if exist volevariant_c.h rename volevariant_c.h voleva_c.h
if exist volegen_c.h if exist volege_c.h del volege_c.h
if exist volegen_c.h rename volegen_c.h volege_c.h
if exist vpalette_c.h if exist vpalet_c.h del vpalet_c.h
if exist vpalette_c.h rename vpalette_c.h vpalet_c.h
if exist vpanecont.h if exist vpanecon.h del vpanecon.h
if exist vpanecont.h rename vpanecont.h vpanecon.h
if exist vpanecont_c.h if exist vpanec_c.h del vpanec_c.h
if exist vpanecont_c.h rename vpanecont_c.h vpanec_c.h
if exist vpthscrp_c.h if exist vpthsc_c.h del vpthsc_c.h
if exist vpthscrp_c.h rename vpthscrp_c.h vpthsc_c.h
if exist vpersistent.h if exist vpersist.h del vpersist.h
if exist vpersistent.h rename vpersistent.h vpersist.h
if exist vpersistent_c.h if exist vpersi_c.h del vpersi_c.h
if exist vpersistent_c.h rename vpersistent_c.h vpersi_c.h
if exist vpixmap_c.h if exist vpixma_c.h del vpixma_c.h
if exist vpixmap_c.h rename vpixmap_c.h vpixma_c.h
if exist vprintsys.h if exist vprintsy.h del vprintsy.h
if exist vprintsys.h rename vprintsys.h vprintsy.h
if exist vprocess_c.h if exist vproce_c.h del vproce_c.h
if exist vprocess_c.h rename vprocess_c.h vproce_c.h
if exist vpscontext.h if exist vpsconte.h del vpsconte.h
if exist vpscontext.h rename vpscontext.h vpsconte.h
if exist vpsinterp.h if exist vpsinter.h del vpsinter.h
if exist vpsinterp.h rename vpsinterp.h vpsinter.h
if exist vpsobject.h if exist vpsobjec.h del vpsobjec.h
if exist vpsobject.h rename vpsobject.h vpsobjec.h
if exist vpwditem_c.h if exist vpwdit_c.h del vpwdit_c.h
if exist vpwditem_c.h rename vpwditem_c.h vpwdit_c.h
if exist vqueryvalue.h if exist vqueryva.h del vqueryva.h
if exist vqueryvalue.h rename vqueryvalue.h vqueryva.h
if exist vquerybuilder.h if exist vquerybu.h del vquerybu.h
if exist vquerybuilder.h rename vquerybuilder.h vquerybu.h
if exist vreeditor.h if exist vreedito.h del vreedito.h
if exist vreeditor.h rename vreeditor.h vreedito.h
if exist vregexp_c.h if exist vregex_c.h del vregex_c.h
if exist vregexp_c.h rename vregexp_c.h vregex_c.h
if exist vreplabel_c.h if exist vreplb_c.h del vreplb_c.h
if exist vreplabel_c.h rename vreplabel_c.h vreplb_c.h
if exist vreplang_c.h if exist vrepla_c.h del vrepla_c.h
if exist vreplang_c.h rename vreplang_c.h vrepla_c.h
if exist vreportcomponent.h if exist vreportc.h del vreportc.h
if exist vreportcomponent.h rename vreportcomponent.h vreportc.h
if exist vreportcomponent_c.h if exist vrptcm_c.h del vrptcm_c.h
if exist vreportcomponent_c.h rename vreportcomponent_c.h vrptcm_c.h
if exist vrdchsr_c.h if exist vrdchs_c.h del vrdchs_c.h
if exist vrdchsr_c.h rename vrdchsr_c.h vrdchs_c.h
if exist vrdevchsr.h if exist vrdevchs.h del vrdevchs.h
if exist vrdevchsr.h rename vrdevchsr.h vrdevchs.h
if exist vrdevchsr_c.h if exist vrdevc_c.h del vrdevc_c.h
if exist vrdevchsr_c.h rename vrdevchsr_c.h vrdevc_c.h
if exist vreportdevice.h if exist vreportd.h del vreportd.h
if exist vreportdevice.h rename vreportdevice.h vreportd.h
if exist vreportdevice_c.h if exist vrptdv_c.h del vrptdv_c.h
if exist vreportdevice_c.h rename vreportdevice_c.h vrptdv_c.h
if exist vreportfiledev.h if exist vreportf.h del vreportf.h
if exist vreportfiledev.h rename vreportfiledev.h vreportf.h
if exist vreportfiledev_c.h if exist vrptfd_c.h del vrptfd_c.h
if exist vreportfiledev_c.h rename vreportfiledev_c.h vrptfd_c.h
if exist vrepfmt_c.h if exist vrepfm_c.h del vrepfm_c.h
if exist vrepfmt_c.h rename vrepfmt_c.h vrepfm_c.h
if exist vreplabel.h if exist vreplabe.h del vreplabe.h
if exist vreplabel.h rename vreplabel.h vreplabe.h
if exist vreplabel_c.h if exist vreplb_c.h del vreplb_c.h
if exist vreplabel_c.h rename vreplabel_c.h vreplb_c.h
if exist vreportlayout.h if exist vreportl.h del vreportl.h
if exist vreportlayout.h rename vreportlayout.h vreportl.h
if exist vreportlayout_c.h if exist vrptlo_c.h del vrptlo_c.h
if exist vreportlayout_c.h rename vreportlayout_c.h vrptlo_c.h
if exist vrepline_c.h if exist vrepli_c.h del vrepli_c.h
if exist vrepline_c.h rename vrepline_c.h vrepli_c.h
if exist vreportobject.h if exist vreporto.h del vreporto.h
if exist vreportobject.h rename vreportobject.h vreporto.h
if exist vreportobject_c.h if exist vrptob_c.h del vrptob_c.h
if exist vreportobject_c.h rename vreportobject_c.h vrptob_c.h
if exist vreportscreen.h if exist vreports.h del vreports.h
if exist vreportscreen.h rename vreportscreen.h vreports.h
if exist vreportscreen_c.h if exist vrptos_c.h del vrptos_c.h
if exist vreportscreen_c.h rename vreportscreen_c.h vrptos_c.h
if exist vreportppv.h if exist vreportp.h del vreportp.h
if exist vreportppv.h rename vreportppv.h vreportp.h
if exist vreportppv_c.h if exist vrptpp_c.h del vrptpp_c.h
if exist vreportppv_c.h rename vreportppv_c.h vrptpp_c.h
if exist vreporttree.h if exist vreportt.h del vreportt.h
if exist vreporttree.h rename vreporttree.h vreportt.h
if exist vreporttree_c.h if exist vrpttr_c.h del vrpttr_c.h
if exist vreporttree_c.h rename vreporttree_c.h vrpttr_c.h
if exist vreport_c.h if exist vrepor_c.h del vrepor_c.h
if exist vreport_c.h rename vreport_c.h vrepor_c.h
if exist vreportdevice_c.h if exist vrptdv_c.h del vrptdv_c.h
if exist vreportdevice_c.h rename vreportdevice_c.h vrptdv_c.h
if exist vreportlayout_c.h if exist vrptlo_c.h del vrptlo_c.h
if exist vreportlayout_c.h rename vreportlayout_c.h vrptlo_c.h
if exist vrepvar_c.h if exist vrepva_c.h del vrepva_c.h
if exist vrepvar_c.h rename vrepvar_c.h vrepva_c.h
if exist vreputil_c.h if exist vreput_c.h del vreput_c.h
if exist vreputil_c.h rename vreputil_c.h vreput_c.h
if exist vresfile_c.h if exist vresfi_c.h del vresfi_c.h
if exist vresfile_c.h rename vresfile_c.h vresfi_c.h
if exist vresolver.h if exist vresolve.h del vresolve.h
if exist vresolver.h rename vresolver.h vresolve.h
if exist vresolver_c.h if exist vresol_c.h del vresol_c.h
if exist vresolver_c.h rename vresolver_c.h vresol_c.h
if exist vresource.h if exist vresourc.h del vresourc.h
if exist vresource.h rename vresource.h vresourc.h
if exist vresource_c.h if exist vresou_c.h del vresou_c.h
if exist vresource_c.h rename vresource_c.h vresou_c.h
if exist vscribe_c.h if exist vscrib_c.h del vscrib_c.h
if exist vscribe_c.h rename vscribe_c.h vscrib_c.h
if exist vsequence.h if exist vsequenc.h del vsequenc.h
if exist vsequence.h rename vsequence.h vsequenc.h
if exist vsequence_c.h if exist vseque_c.h del vseque_c.h
if exist vsequence_c.h rename vsequence_c.h vseque_c.h
if exist vservice_c.h if exist vservi_c.h del vservi_c.h
if exist vservice_c.h rename vservice_c.h vservi_c.h
if exist vsvcchsr_c.h if exist vsvcch_c.h del vsvcch_c.h
if exist vsvcchsr_c.h rename vsvcchsr_c.h vsvcch_c.h
if exist vsession_c.h if exist vsessi_c.h del vsessi_c.h
if exist vsession_c.h rename vsession_c.h vsessi_c.h
if exist vsiggrp_c.h if exist vsiggr_c.h del vsiggr_c.h
if exist vsiggrp_c.h rename vsiggrp_c.h vsiggr_c.h
if exist vsignature.h if exist vsignatu.h del vsignatu.h
if exist vsignature.h rename vsignature.h vsignatu.h
if exist vsignature_c.h if exist vsigna_c.h del vsigna_c.h
if exist vsignature_c.h rename vsignature_c.h vsigna_c.h
if exist vsizeview.h if exist vsizevie.h del vsizevie.h
if exist vsizeview.h rename vsizeview.h vsizevie.h
if exist vsizeview_c.h if exist vsizev_c.h del vsizev_c.h
if exist vsizeview_c.h rename vsizeview_c.h vsizev_c.h
if exist vslider_c.h if exist vslide_c.h del vslide_c.h
if exist vslider_c.h rename vslider_c.h vslide_c.h
if exist vspinner_c.h if exist vspinn_c.h del vspinn_c.h
if exist vspinner_c.h rename vspinner_c.h vspinn_c.h
if exist vsplitter.h if exist vsplitte.h del vsplitte.h
if exist vsplitter.h rename vsplitter.h vsplitte.h
if exist vspring_c.h if exist vsprin_c.h del vsprin_c.h
if exist vspring_c.h rename vspring_c.h vsprin_c.h
if exist vsprdom_c.h if exist vsprdo_c.h del vsprdo_c.h
if exist vsprdom_c.h rename vsprdom_c.h vsprdo_c.h
if exist vstartup_c.h if exist vstart_c.h del vstart_c.h
if exist vstartup_c.h rename vstartup_c.h vstart_c.h
if exist vstatusbar.h if exist vstatusb.h del vstatusb.h
if exist vstatusbar.h rename vstatusbar.h vstatusb.h
if exist vstatusbar_c.h if exist vstatb_c.h del vstatb_c.h
if exist vstatusbar_c.h rename vstatusbar_c.h vstatb_c.h
if exist vstdiosys.h if exist vstdiosy.h del vstdiosy.h
if exist vstdiosys.h rename vstdiosys.h vstdiosy.h
if exist vstrchsr_c.h if exist vstrch_c.h del vstrch_c.h
if exist vstrchsr_c.h rename vstrchsr_c.h vstrch_c.h
if exist vstream_c.h if exist vstrea_c.h del vstrea_c.h
if exist vstream_c.h rename vstream_c.h vstrea_c.h
if exist vstritem_c.h if exist vstrit_c.h del vstrit_c.h
if exist vstritem_c.h rename vstritem_c.h vstrit_c.h
if exist vstylechsr.h if exist vstylech.h del vstylech.h
if exist vstylechsr.h rename vstylechsr.h vstylech.h
if exist vstylechsr_c.h if exist vstyle_c.h del vstyle_c.h
if exist vstylechsr_c.h rename vstylechsr_c.h vstyle_c.h
if exist vsysioctl.h if exist vsysioct.h del vsysioct.h
if exist vsysioctl.h rename vsysioctl.h vsysioct.h
if exist vsysmntent.h if exist vsysmnte.h del vsysmnte.h
if exist vsysmntent.h rename vsysmntent.h vsysmnte.h
if exist vsysparam.h if exist vsyspara.h del vsyspara.h
if exist vsysparam.h rename vsysparam.h vsyspara.h
if exist vsysresource.h if exist vsysreso.h del vsysreso.h
if exist vsysresource.h rename vsysresource.h vsysreso.h
if exist vsysselect.h if exist vsyssele.h del vsyssele.h
if exist vsysselect.h rename vsysselect.h vsyssele.h
if exist vsyssocket.h if exist vsyssock.h del vsyssock.h
if exist vsyssocket.h rename vsyssocket.h vsyssock.h
if exist vsyssysteminfo.h if exist vsysinfo.h del vsysinfo.h
if exist vsyssysteminfo.h rename vsyssysteminfo.h vsysinfo.h
if exist vsystimes.h if exist vsystims.h del vsystims.h
if exist vsystimes.h rename vsystimes.h vsystims.h
if exist vsystypes.h if exist vsystype.h del vsystype.h
if exist vsystypes.h rename vsystypes.h vsystype.h
if exist vsysutsname.h if exist vsysutsn.h del vsysutsn.h
if exist vsysutsname.h rename vsysutsname.h vsysutsn.h
if exist vtableview.h if exist vtablevi.h del vtablevi.h
if exist vtableview.h rename vtableview.h vtablevi.h
if exist vtableview_c.h if exist vtblv_c.h del vtblv_c.h
if exist vtableview_c.h rename vtableview_c.h vtblv_c.h
if exist vtextitem.h if exist vtextite.h del vtextite.h
if exist vtextitem.h rename vtextitem.h vtextite.h
if exist vtextitem_c.h if exist vtexti_c.h del vtexti_c.h
if exist vtextitem_c.h rename vtextitem_c.h vtexti_c.h
if exist vtextmarker.h if exist vtextmar.h del vtextmar.h
if exist vtextmarker.h rename vtextmarker.h vtextmar.h
if exist vtextmarker_c.h if exist vtextm_c.h del vtextm_c.h
if exist vtextmarker_c.h rename vtextmarker_c.h vtextm_c.h
if exist vtextruler.h if exist vtextrul.h del vtextrul.h
if exist vtextruler.h rename vtextruler.h vtextrul.h
if exist vtextruler_c.h if exist vtextr_c.h del vtextr_c.h
if exist vtextruler_c.h rename vtextruler_c.h vtextr_c.h
if exist vtextsel_c.h if exist vtexts_c.h del vtexts_c.h
if exist vtextsel_c.h rename vtextsel_c.h vtexts_c.h
if exist vtextview.h if exist vtextvie.h del vtextvie.h
if exist vtextview.h rename vtextview.h vtextvie.h
if exist vtextview_c.h if exist vtextv_c.h del vtextv_c.h
if exist vtextview_c.h rename vtextview_c.h vtextv_c.h
if exist vthread_c.h if exist vthrea_c.h del vthrea_c.h
if exist vthread_c.h rename vthread_c.h vthrea_c.h
if exist vthreader.h if exist vthreade.h del vthreade.h
if exist vthreader.h rename vthreader.h vthreade.h
if exist vthreadsys.h if exist vthreads.h del vthreads.h
if exist vthreadsys.h rename vthreadsys.h vthreads.h
if exist vthreadsys_c.h if exist vthrds_c.h del vthrds_c.h
if exist vthreadsys_c.h rename vthreadsys_c.h vthrds_c.h
if exist vtimestamp.h if exist vtimesta.h del vtimesta.h
if exist vtimestamp.h rename vtimestamp.h vtimesta.h
if exist vtimestamp_c.h if exist vtimes_c.h del vtimes_c.h
if exist vtimestamp_c.h rename vtimestamp_c.h vtimes_c.h
if exist vtoolbar_c.h if exist vtoolb_c.h del vtoolb_c.h
if exist vtoolbar_c.h rename vtoolbar_c.h vtoolb_c.h
if exist vtbrearranger.h if exist vtbrearr.h del vtbrearr.h
if exist vtbrearranger.h rename vtbrearranger.h vtbrearr.h
if exist vtbrearranger_c.h if exist vtbrar_c.h del vtbrar_c.h
if exist vtbrearranger_c.h rename vtbrearranger_c.h vtbrar_c.h
if exist vtbsepar_c.h if exist vtbsep_c.h del vtbsep_c.h
if exist vtbsepar_c.h rename vtbsepar_c.h vtbsep_c.h
if exist vtoolbtn_c.h if exist vtolbt_c.h del vtolbt_c.h
if exist vtoolbtn_c.h rename vtoolbtn_c.h vtolbt_c.h
if exist vtoolchanger.h if exist vtolchgr.h del vtolchgr.h
if exist vtoolchanger.h rename vtoolchanger.h vtolchgr.h
if exist vtoolchanger_c.h if exist vtolch_c.h del vtolch_c.h
if exist vtoolchanger_c.h rename vtoolchanger_c.h vtolch_c.h
if exist vtooltip_c.h if exist vtoolt_c.h del vtoolt_c.h
if exist vtooltip_c.h rename vtooltip_c.h vtoolt_c.h
if exist vtransform.h if exist vtransfo.h del vtransfo.h
if exist vtransform.h rename vtransform.h vtransfo.h
if exist vtransform_c.h if exist vtrans_c.h del vtrans_c.h
if exist vtransform_c.h rename vtransform_c.h vtrans_c.h
if exist vtrans_c.h if exist vtrnsl_c.h del vtrnsl_c.h
if exist vtrans_c.h rename vtrans_c.h vtrnsl_c.h
if exist vtreecard.h if exist vtreecar.h del vtreecar.h
if exist vtreecard.h rename vtreecard.h vtreecar.h
if exist vtreecard_c.h if exist vtreec_c.h del vtreec_c.h
if exist vtreecard_c.h rename vtreecard_c.h vtreec_c.h
if exist vtreelist.h if exist vtreelis.h del vtreelis.h
if exist vtreelist.h rename vtreelist.h vtreelis.h
if exist vtreelist_c.h if exist vtreel_c.h del vtreel_c.h
if exist vtreelist_c.h rename vtreelist_c.h vtreel_c.h
if exist vtreeview.h if exist vtreevie.h del vtreevie.h
if exist vtreeview.h rename vtreeview.h vtreevie.h
if exist vtreeview_c.h if exist vtreev_c.h del vtreev_c.h
if exist vtreeview_c.h rename vtreeview_c.h vtreev_c.h
if exist vtypeditem.h if exist vtypedit.h del vtypedit.h
if exist vtypeditem.h rename vtypeditem.h vtypedit.h
if exist vtypeditem_c.h if exist vtypdi_c.h del vtypdi_c.h
if exist vtypeditem_c.h rename vtypeditem_c.h vtypdi_c.h
if exist vulongitem.h if exist vulongit.h del vulongit.h
if exist vulongitem.h rename vulongitem.h vulongit.h
if exist vulongitem_c.h if exist vulngi_c.h del vulngi_c.h
if exist vulongitem_c.h rename vulongitem_c.h vulngi_c.h
if exist vundocompat.h if exist vundocom.h del vundocom.h
if exist vundocompat.h rename vundocompat.h vundocom.h
if exist vvaxfloat.h if exist vvaxfloa.h del vvaxfloa.h
if exist vvaxfloat.h rename vvaxfloat.h vvaxfloa.h
if exist vvmstypes.h if exist vvmstype.h del vvmstype.h
if exist vvmstypes.h rename vvmstypes.h vvmstype.h
if exist vwebbrowse.h if exist vwebbrow.h del vwebbrow.h
if exist vwebbrowse.h rename vwebbrowse.h vwebbrow.h
if exist vwebbrowse_c.h if exist vwebbr_c.h del vwebbr_c.h
if exist vwebbrowse_c.h rename vwebbrowse_c.h vwebbr_c.h
if exist vwindow_c.h if exist vwindo_c.h del vwindo_c.h
if exist vwindow_c.h rename vwindow_c.h vwindo_c.h
if exist vwindowsys.h if exist vwindows.h del vwindows.h
if exist vwindowsys.h rename vwindowsys.h vwindows.h
if exist vx11cursorfont.h if exist vx11curs.h del vx11curs.h
if exist vx11cursorfont.h rename vx11cursorfont.h vx11curs.h
if exist vx11extensionsxshm.h if exist vx11exte.h del vx11exte.h
if exist vx11extensionsxshm.h rename vx11extensionsxshm.h vx11exte.h
if exist vx11keysym.h if exist vx11keys.h del vx11keys.h
if exist vx11keysym.h rename vx11keysym.h vx11keys.h
if exist vx11xatom.h if exist vx11xato.h del vx11xato.h
if exist vx11xatom.h rename vx11xatom.h vx11xato.h
if exist vx11xutil.h if exist vx11xuti.h del vx11xuti.h
if exist vx11xutil.h rename vx11xutil.h vx11xuti.h
if exist vxxloadable.h if exist vxxloada.h del vxxloada.h
if exist vxxloadable.h rename vxxloadable.h vxxloada.h
goto END

:COPYINSTALL
echo on

copy %1\vport.h %2\vport.h
copy %1\vgalaxy.h %2\vgalaxy.h
copy %1\vdllvar.h %2\vdllvar.h
copy %1\vhdrdefs.h %2\vhdrdefs.h
copy %1\vhdrlong.h %2\vhdrlong.h
copy %1\vhdr83.h %2\vhdr83.h
copy %1\vhdr83.h %2\vhdrmode.h

if exist vabstract.h copy %1\vabstract.h %2\vabstrac.h
if exist vaccept.h copy %1\vaccept.h %2\vaccept.h
if exist vaccept_c.h copy %1\vaccept_c.h %2\vaccep_c.h
if exist vappframe.h copy %1\vappframe.h %2\vappfram.h
if exist vappframe_c.h copy %1\vappframe_c.h %2\vappfr_c.h
if exist vapplication.h copy %1\vapplication.h %2\vapplica.h
if exist vapplication_c.h copy %1\vapplication_c.h %2\vappli_c.h
if exist vargscrap.h copy %1\vargscrap.h %2\vargscra.h
if exist varpainet.h copy %1\varpainet.h %2\varpaine.h
if exist varray.h copy %1\varray.h %2\varray.h
if exist vassert.h copy %1\vassert.h %2\vassert.h
if exist vat.h copy %1\vat.h %2\vat.h
if exist vattribute.h copy %1\vattribute.h %2\vattribu.h
if exist vattribute_c.h copy %1\vattribute_c.h %2\vattri_c.h
if exist vblock.h copy %1\vblock.h %2\vblock.h
if exist vboolitem.h copy %1\vboolitem.h %2\vboolite.h
if exist vboolitem_c.h copy %1\vboolitem_c.h %2\vbooli_c.h
if exist vbtree.h copy %1\vbtree.h %2\vbtree.h
if exist vbtree_c.h copy %1\vbtree_c.h %2\vbtree_c.h
if exist vbuffer.h copy %1\vbuffer.h %2\vbuffer.h
if exist vbuffer_c.h copy %1\vbuffer_c.h %2\vbuffe_c.h
if exist vbldnum.h copy %1\vbldnum.h %2\vbldnum.h
if exist vbuildstrs.h copy %1\vbuildstrs.h %2\vbuildst.h
if exist vbuildstrs.c copy %1\vbuildstrs.c %2\vbuildst.c
if exist vbutton.h copy %1\vbutton.h %2\vbutton.h
if exist vbutton_c.h copy %1\vbutton_c.h %2\vbutto_c.h
if exist vcanvas.h copy %1\vcanvas.h %2\vcanvas.h
if exist vcanvas_c.h copy %1\vcanvas_c.h %2\vcanva_c.h
if exist vchar.h copy %1\vchar.h %2\vchar.h
if exist vchar_c.h copy %1\vchar_c.h %2\vchar_c.h
if exist vcharencoding.h copy %1\vcharencoding.h %2\vcharenc.h
if exist vcharencoding_c.h copy %1\vcharencoding_c.h %2\vchare_c.h
if exist vchunk.h copy %1\vchunk.h %2\vchunk.h
if exist vclass.h copy %1\vclass.h %2\vclass.h
if exist vclass_c.h copy %1\vclass_c.h %2\vclass_c.h
if exist vclassextra.h copy %1\vclassextra.h %2\vclassex.h
if exist vclassinfo.h copy %1\vclassinfo.h %2\vclassin.h
if exist vclassreg.h copy %1\vclassreg.h %2\vclassre.h
if exist vclex.h copy %1\vclex.h %2\vclex.h
if exist vclient.h copy %1\vclient.h %2\vclient.h
if exist vclient_c.h copy %1\vclient_c.h %2\vclien_c.h
if exist vclipboard.h copy %1\vclipboard.h %2\vclipboa.h
if exist vclipboard_c.h copy %1\vclipboard_c.h %2\vclipb_c.h
if exist vcmdchsr.h copy %1\vcmdchsr.h %2\vcmdchsr.h
if exist vcmdchsr_c.h copy %1\vcmdchsr_c.h %2\vcmdch_c.h
if exist vcolor.h copy %1\vcolor.h %2\vcolor.h
if exist vcolor_c.h copy %1\vcolor_c.h %2\vcolor_c.h
if exist vcolorchsr.h copy %1\vcolorchsr.h %2\vcolorch.h
if exist vcolorchsr_c.h copy %1\vcolorchsr_c.h %2\vcolch_c.h
if exist vcolorsys.h copy %1\vcolorsys.h %2\vcolorsy.h
if exist vcombo.h copy %1\vcombo.h %2\vcombo.h
if exist vcombo_c.h copy %1\vcombo_c.h %2\vcombo_c.h
if exist vcombobox.h copy %1\vcombobox.h %2\vcombobo.h
if exist vcombobox_c.h copy %1\vcombobox_c.h %2\vcombx_c.h
if exist vcommchn.h copy %1\vcommchn.h %2\vcommchn.h
if exist vcommchn_c.h copy %1\vcommchn_c.h %2\vcommc_c.h
if exist vcomm.h copy %1\vcomm.h %2\vcomm.h
if exist vcomm_c.h copy %1\vcomm_c.h %2\vcomm_c.h
if exist vcommand.h copy %1\vcommand.h %2\vcommand.h
if exist vcommand_c.h copy %1\vcommand_c.h %2\vcomma_c.h
if exist vcommdll.h copy %1\vcommdll.h %2\vcommdll.h
if exist vcommfix.h copy %1\vcommfix.h %2\vcommfix.h
if exist vcondition.h copy %1\vcondition.h %2\vconditi.h
if exist vconfirm.h copy %1\vconfirm.h %2\vconfirm.h
if exist vconfirm_c.h copy %1\vconfirm_c.h %2\vconfi_c.h
if exist vctrgrid.h copy %1\vctrgrid.h %2\vctrgrid.h
if exist vctrgrid_c.h copy %1\vctrgrid_c.h %2\vctrgr_c.h
if exist vcontain.h copy %1\vcontain.h %2\vcontain.h
if exist vcontain_c.h copy %1\vcontain_c.h %2\vconta_c.h
if exist vcontrol.h copy %1\vcontrol.h %2\vcontrol.h
if exist vcontrol_c.h copy %1\vcontrol_c.h %2\vcontr_c.h
if exist vctlchsr.h copy %1\vctlchsr.h %2\vctlchsr.h
if exist vctlchsr_c.h copy %1\vctlchsr_c.h %2\vctlch_c.h
if exist vctype.h copy %1\vctype.h %2\vctype.h
if exist vcursor.h copy %1\vcursor.h %2\vcursor.h
if exist vcursor_c.h copy %1\vcursor_c.h %2\vcurso_c.h
if exist vdasdict.h copy %1\vdasdict.h %2\vdasdict.h
if exist vdasserv.h copy %1\vdasserv.h %2\vdasserv.h
if exist vdasserv_c.h copy %1\vdasserv_c.h %2\vdasse_c.h
if exist vdschsr.h copy %1\vdschsr.h %2\vdschsr.h
if exist vdschsr_c.h copy %1\vdschsr_c.h %2\vdschs_c.h
if exist vdsdata.h copy %1\vdsdata.h %2\vdsdata.h
if exist vdsdata_c.h copy %1\vdsdata_c.h %2\vdsdat_c.h
if exist vdsdbeng.h copy %1\vdsdbeng.h %2\vdsdbeng.h
if exist vdsdbeng_c.h copy %1\vdsdbeng_c.h %2\vdsdbe_c.h
if exist vdsfseng.h copy %1\vdsfseng.h %2\vdsfseng.h
if exist vdsfseng_c.h copy %1\vdsfseng_c.h %2\vdsfse_c.h
if exist vdatasource.h copy %1\vdatasource.h %2\vdatasou.h
if exist vdsuieng.h copy %1\vdsuieng.h %2\vdsuieng.h
if exist vdsuieng_c.h copy %1\vdsuieng_c.h %2\vdsuie_c.h
if exist vdatasource_c.h copy %1\vdatasource_c.h %2\vdatas_c.h
if exist vdatatag.h copy %1\vdatatag.h %2\vdatatag.h
if exist vdatatag_c.h copy %1\vdatatag_c.h %2\vdatat_c.h
if exist vdate.h copy %1\vdate.h %2\vdate.h
if exist vdate_c.h copy %1\vdate_c.h %2\vdate_c.h
if exist vdateitem.h copy %1\vdateitem.h %2\vdateite.h
if exist vdateitem_c.h copy %1\vdateitem_c.h %2\vdatei_c.h
if exist vdb.h copy %1\vdb.h %2\vdb.h
if exist vdbserv.h copy %1\vdbserv.h %2\vdbserv.h
if exist vdb_c.h copy %1\vdb_c.h %2\vdb_c.h
if exist vdbchsr.h copy %1\vdbchsr.h %2\vdbchsr.h
if exist vdbchsr_c.h copy %1\vdbchsr_c.h %2\vdbchs_c.h
if exist vdbcombobox.h copy %1\vdbcombobox.h %2\vdbcombo.h
if exist vdbform.h copy %1\vdbform.h %2\vdbform.h
if exist vdblist.h copy %1\vdblist.h %2\vdblist.h
if exist vdbmenu.h copy %1\vdbmenu.h %2\vdbmenu.h
if exist vdbpriv.h copy %1\vdbpriv.h %2\vdbpriv.h
if exist vdbquery.h copy %1\vdbquery.h %2\vdbquery.h
if exist vdbqb.h copy %1\vdbqb.h %2\vdbqb.h
if exist vdbspec.h copy %1\vdbspec.h %2\vdbspec.h
if exist vdbspinner.h copy %1\vdbspinner.h %2\vdbspinn.h
if exist vdebug.h copy %1\vdebug.h %2\vdebug.h
if exist vdebug_c.h copy %1\vdebug_c.h %2\vdebug_c.h
if exist vdebugut.h copy %1\vdebugut.h %2\vdebugut.h
if exist vdelegator.h copy %1\vdelegator.h %2\vdelegat.h
if exist vdelegator_c.h copy %1\vdelegator_c.h %2\vdeleg_c.h
if exist vdialog.h copy %1\vdialog.h %2\vdialog.h
if exist vdialog.h copy %1\vdialog.h %2\vdialog.h
if exist vdialog_c.h copy %1\vdialog_c.h %2\vdialo_c.h
if exist vdialsys.h copy %1\vdialsys.h %2\vdialsys.h
if exist vdict.h copy %1\vdict.h %2\vdict.h
if exist vdict_c.h copy %1\vdict_c.h %2\vdict_c.h
if exist vdirent.h copy %1\vdirent.h %2\vdirent.h
if exist vdock.h copy %1\vdock.h %2\vdock.h
if exist vdock_c.h copy %1\vdock_c.h %2\vdock_c.h
if exist vdockcont.h copy %1\vdockcont.h %2\vdockcnt.h
if exist vdockcont_c.h copy %1\vdockcont_c.h %2\vdockc_c.h
if exist vdocker.h copy %1\vdocker.h %2\vdocker.h
if exist vdocker_c.h copy %1\vdocker_c.h %2\vdocke_c.h
if exist vdockitem.h copy %1\vdockitem.h %2\vdockitm.h
if exist vdockitem_c.h copy %1\vdockitem_c.h %2\vdocki_c.h
if exist vdomain.h copy %1\vdomain.h %2\vdomain.h
if exist vdomain_c.h copy %1\vdomain_c.h %2\vdomai_c.h
if exist vdomitem.h copy %1\vdomitem.h %2\vdomitem.h
if exist vdomitem_c.h copy %1\vdomitem_c.h %2\vdomit_c.h
if exist vdomview.h copy %1\vdomview.h %2\vdomview.h
if exist vdomview_c.h copy %1\vdomview_c.h %2\vdomvi_c.h
if exist vdouble.h copy %1\vdouble.h %2\vdouble.h
if exist vdoubleitem.h copy %1\vdoubleitem.h %2\vdblitem.h
if exist vdoubleitem_c.h copy %1\vdoubleitem_c.h %2\vdblit_c.h
if exist vdrag.h copy %1\vdrag.h %2\vdrag.h
if exist vdrag_c.h copy %1\vdrag_c.h %2\vdrag_c.h
if exist vdraw.h copy %1\vdraw.h %2\vdraw.h
if exist vdraw_c.h copy %1\vdraw_c.h %2\vdraw_c.h
if exist vdrawcontext.h copy %1\vdrawcontext.h %2\vdrawcon.h
if exist vdrawcontext_c.h copy %1\vdrawcontext_c.h %2\vdrwco_c.h
if exist vdrawpath.h copy %1\vdrawpath.h %2\vdrawpat.h
if exist vdrawpath_c.h copy %1\vdrawpath_c.h %2\vdrwpa_c.h
if exist vdrawpen.h copy %1\vdrawpen.h %2\vdrawpen.h
if exist vdrawpen_c.h copy %1\vdrawpen_c.h %2\vdrwpe_c.h
if exist vdrawrectset.h copy %1\vdrawrectset.h %2\vdrawrec.h
if exist vdrawrectset_c.h copy %1\vdrawrectset_c.h %2\vdrwre_c.h
if exist vdrawsys.h copy %1\vdrawsys.h %2\vdrawsys.h
if exist vdropsite.h copy %1\vdropsite.h %2\vdropsit.h
if exist vdropsite_c.h copy %1\vdropsite_c.h %2\vdrops_c.h
if exist vdropsite.h copy %1\vdropsite.h %2\vdropsit.h
if exist vdropsite_c.h copy %1\vdropsite_c.h %2\vdrops_c.h
if exist vdsdbeng_c.h copy %1\vdsdbeng_c.h %2\vdsdbe_c.h
if exist vdsfseng_c.h copy %1\vdsfseng_c.h %2\vdsfse_c.h
if exist vdsuieng_c.h copy %1\vdsuieng_c.h %2\vdsuie_c.h
if exist verrno.h copy %1\verrno.h %2\verrno.h
if exist vevent2.h copy %1\vevent2.h %2\vevent2.h
if exist vevent2_c.h copy %1\vevent2_c.h %2\veven2_c.h
if exist vevent2sys.h copy %1\vevent2sys.h %2\vevent2s.h
if exist vevent2sys_c.h copy %1\vevent2sys_c.h %2\vevn2s_c.h
if exist vevent.h copy %1\vevent.h %2\vevent.h
if exist vevent_c.h copy %1\vevent_c.h %2\vevent_c.h
if exist veventsys.h copy %1\veventsys.h %2\veventsy.h
if exist veventsys_c.h copy %1\veventsys_c.h %2\vevnsy_c.h
if exist vevntitr.h copy %1\vevntitr.h %2\vevntitr.h
if exist vevntitr_c.h copy %1\vevntitr_c.h %2\vevnti_c.h
if exist vex.h copy %1\vex.h %2\vex.h
if exist vex_c.h copy %1\vex_c.h %2\vex_c.h
if exist vexport.h copy %1\vexport.h %2\vexport.h
if exist vexsys.h copy %1\vexsys.h %2\vexsys.h
if exist vfcntl.h copy %1\vfcntl.h %2\vfcntl.h
if exist vfield.h copy %1\vfield.h %2\vfield.h
if exist vfield_c.h copy %1\vfield_c.h %2\vfield_c.h
if exist vfile.h copy %1\vfile.h %2\vfile.h
if exist vfile_c.h copy %1\vfile_c.h %2\vfile_c.h
if exist vfilechsr.h copy %1\vfilechsr.h %2\vfilechs.h
if exist vfilechsr_c.h copy %1\vfilechsr_c.h %2\vfilec_c.h
if exist vfixed.h copy %1\vfixed.h %2\vfixed.h
if exist vfixed_c.h copy %1\vfixed_c.h %2\vfixed_c.h
if exist vfloat.h copy %1\vfloat.h %2\vfloat.h
if exist vfont.h copy %1\vfont.h %2\vfont.h
if exist vfont_c.h copy %1\vfont_c.h %2\vfont_c.h
if exist vfontchsr.h copy %1\vfontchsr.h %2\vfontchs.h
if exist vfontchsr_c.h copy %1\vfontchsr_c.h %2\vfontc_c.h
if exist vfontspec.h copy %1\vfontspec.h %2\vfontspe.h
if exist vfontspec_c.h copy %1\vfontspec_c.h %2\vfonts_c.h
if exist vfontsys.h copy %1\vfontsys.h %2\vfontsys.h
if exist vformctxt.h copy %1\vformctxt.h %2\vfrmctxt.h
if exist vformctxt_c.h copy %1\vformctxt_c.h %2\vfrmct_c.h
if exist vform.h copy %1\vform.h %2\vform.h
if exist vform_c.h copy %1\vform_c.h %2\vform_c.h
if exist vformat.h copy %1\vformat.h %2\vformat.h
if exist vformat_c.h copy %1\vformat_c.h %2\vforma_c.h
if exist vfs.h copy %1\vfs.h %2\vfs.h
if exist vfs_c.h copy %1\vfs_c.h %2\vfs_c.h
if exist vgalbnum.h copy %1\vgalbnum.h %2\vgalbnum.h
if exist vglitem.h copy %1\vglitem.h %2\vglitem.h
if exist vglwin.h copy %1\vglwin.h %2\vglwin.h
if exist vgraph.h copy %1\vgraph.h %2\vgraph.h
if exist vgridcont.h copy %1\vgridcont.h %2\vgridcon.h
if exist vgridcont_c.h copy %1\vgridcont_c.h %2\vgridc_c.h
if exist vgridmodel.h copy %1\vgridmodel.h %2\vgridmod.h
if exist vgridmodel_c.h copy %1\vgridmodel_c.h %2\vgridm_c.h
if exist vgrp.h copy %1\vgrp.h %2\vgrp.h
if exist vhelp.h copy %1\vhelp.h %2\vhelp.h
if exist vhelprun.h copy %1\vhelprun.h %2\vhelprun.h
if exist vhelp_c.h copy %1\vhelp_c.h %2\vhelp_c.h
if exist vhelpdas.h copy %1\vhelpdas.h %2\vhelpdas.h
if exist vhelpdisplay.h copy %1\vhelpdisplay.h %2\vhelpdis.h
if exist vhelpdisplay_c.h copy %1\vhelpdisplay_c.h %2\vhpdis_c.h
if exist vhelpdoc.h copy %1\vhelpdoc.h %2\vhelpdoc.h
if exist vhelpdefault.h copy %1\vhelpdefault.h %2\vhelpdef.h
if exist vhelpdefault_c.h copy %1\vhelpdefault_c.h %2\vhpdef_c.h
if exist vhelpexplorer.h copy %1\vhelpexplorer.h %2\vhelpexp.h
if exist vhelpexplorer_c.h copy %1\vhelpexplorer_c.h %2\vhpexp_c.h
if exist vhelpgalaxy.h copy %1\vhelpgalaxy.h %2\vhelpgal.h
if exist vhelpgalaxy_c.h copy %1\vhelpgalaxy_c.h %2\vhpgal_c.h
if exist vhelphtmlgalaxy.h copy %1\vhelphtmlgalaxy.h %2\vhelphtg.h
if exist vhelphtmlgalaxy_c.h copy %1\vhelphtmlgalaxy_c.h %2\vhphtg_c.h
if exist vhelphtmllocator.h copy %1\vhelphtmllocator.h %2\vhelphtl.h
if exist vhelphtmllocator_c.h copy %1\vhelphtmllocator_c.h %2\vhphtl_c.h
if exist vhelphypertext.h copy %1\vhelphypertext.h %2\vhelphyp.h
if exist vhelphypertext_c.h copy %1\vhelphypertext_c.h %2\vhphyp_c.h
if exist vhelplinker.h copy %1\vhelplinker.h %2\vhelplin.h
if exist vhelplocator.h copy %1\vhelplocator.h %2\vhelploc.h
if exist vhelplocator_c.h copy %1\vhelplocator_c.h %2\vhploc_c.h
if exist vhelpnetscape.h copy %1\vhelpnetscape.h %2\vhelpnet.h
if exist vhelpnetscape_c.h copy %1\vhelpnetscape_c.h %2\vhpnet_c.h
if exist vhelpobject.h copy %1\vhelpobject.h %2\vhelpobj.h
if exist vhelpobject_c.h copy %1\vhelpobject_c.h %2\vhpobj_c.h
if exist vhelpref.h copy %1\vhelpref.h %2\vhelpref.h
if exist vhelpref_c.h copy %1\vhelpref_c.h %2\vhpref_c.h
if exist vhelpreflocator.h copy %1\vhelpreflocator.h %2\vhelprfl.h
if exist vhelpreflocator_c.h copy %1\vhelpreflocator_c.h %2\vhprfl_c.h
if exist vhelpregistry.h copy %1\vhelpregistry.h %2\vhelpreg.h
if exist vhelpregistry_c.h copy %1\vhelpregistry_c.h %2\vhpreg_c.h
if exist vhelprequest.h copy %1\vhelprequest.h %2\vhelpreq.h
if exist vhelprequest_c.h copy %1\vhelprequest_c.h %2\vhpreq_c.h
if exist vhelpstatus.h copy %1\vhelpstatus.h %2\vhelpsta.h
if exist vhelpstatus_c.h copy %1\vhelpstatus_c.h %2\vhpsta_c.h
if exist vhelptext.h copy %1\vhelptext.h %2\vhelptex.h
if exist vhelptext_c.h copy %1\vhelptext_c.h %2\vhptex_c.h
if exist vhelptextlocator.h copy %1\vhelptextlocator.h %2\vhelptxl.h
if exist vhelptextlocator_c.h copy %1\vhelptextlocator_c.h %2\vhptxl_c.h
if exist vhelptooltip.h copy %1\vhelptooltip.h %2\vhelptip.h
if exist vhelptooltip_c.h copy %1\vhelptooltip_c.h %2\vhptip_c.h
if exist vhelptrans.h copy %1\vhelptrans.h %2\vhelptra.h
if exist vhelpwinhelp.h copy %1\vhelpwinhelp.h %2\vhelpwin.h
if exist vhelpwinhelp_c.h copy %1\vhelpwinhelp_c.h %2\vhpwin_c.h
if exist vhex.h copy %1\vhex.h %2\vhex.h
if exist vhex_c.h copy %1\vhex_c.h %2\vhex_c.h
if exist vhexchsr.h copy %1\vhexchsr.h %2\vhexchsr.h
if exist vhexchsr_c.h copy %1\vhexchsr_c.h %2\vhexch_c.h
if exist vhtml.h copy %1\vhtml.h %2\vhtml.h
if exist vhtmled.h copy %1\vhtmled.h %2\vhtmled.h
if exist vi18n.h copy %1\vi18n.h %2\vi18n.h
if exist viconview.h copy %1\viconview.h %2\viconvie.h
if exist viconview_c.h copy %1\viconview_c.h %2\viconv_c.h
if exist vimage.h copy %1\vimage.h %2\vimage.h
if exist vimage_c.h copy %1\vimage_c.h %2\vimage_c.h
if exist vimageed.h copy %1\vimageed.h %2\vimageed.h
if exist vimageed_c.h copy %1\vimageed_c.h %2\vimagd_c.h
if exist vimged.h copy %1\vimged.h %2\vimged.h
if exist vimgedutils.h copy %1\vimgedutils.h %2\vimgedut.h
if exist vimgutils.h copy %1\vimgutils.h %2\vimgutil.h
if exist vimport.h copy %1\vimport.h %2\vimport.h
if exist vinput.h copy %1\vinput.h %2\vinput.h
if exist vinput_c.h copy %1\vinput_c.h %2\vinput_c.h
if exist vinputsys.h copy %1\vinputsys.h %2\vinputsy.h
if exist vinst.h copy %1\vinst.h %2\vinst.h
if exist vinst_c.h copy %1\vinst_c.h %2\vinst_c.h
if exist vinstall.h copy %1\vinstall.h %2\vinstall.h
if exist vinstall_c.h copy %1\vinstall_c.h %2\vinstl_c.h
if exist vinstance.h copy %1\vinstance.h %2\vinstanc.h
if exist vinstance_c.h copy %1\vinstance_c.h %2\vinsta_c.h
if exist vinterface.h copy %1\vinterface.h %2\vinterfa.h
if exist vinterface_c.h copy %1\vinterface_c.h %2\vinter_c.h
if exist vio.h copy %1\vio.h %2\vio.h
if exist viterator.h copy %1\viterator.h %2\viterato.h
if exist viterator_c.h copy %1\viterator_c.h %2\vitera_c.h
if exist vkey.h copy %1\vkey.h %2\vkey.h
if exist vkey_c.h copy %1\vkey_c.h %2\vkey_c.h
if exist vkeyitem.h copy %1\vkeyitem.h %2\vkeyitem.h
if exist vkeyitem_c.h copy %1\vkeyitem_c.h %2\vkeyit_c.h
if exist vkeysys.h copy %1\vkeysys.h %2\vkeysys.h
if exist vkind.h copy %1\vkind.h %2\vkind.h
if exist vlaf.h copy %1\vlaf.h %2\vlaf.h
if exist vlaf_c.h copy %1\vlaf_c.h %2\vlaf_c.h
if exist vlibc.h copy %1\vlibc.h %2\vlibc.h
if exist vlimits.h copy %1\vlimits.h %2\vlimits.h
if exist vlist.h copy %1\vlist.h %2\vlist.h
if exist vlist_c.h copy %1\vlist_c.h %2\vlist_c.h
if exist vlistedit.h copy %1\vlistedit.h %2\vlistedi.h
if exist vlistitem.h copy %1\vlistitem.h %2\vlistite.h
if exist vlistitem_c.h copy %1\vlistitem_c.h %2\vlisti_c.h
if exist vlistsel.h copy %1\vlistsel.h %2\vlistsel.h
if exist vlistsel_c.h copy %1\vlistsel_c.h %2\vlistn_c.h
if exist vlistsize.h copy %1\vlistsize.h %2\vlistsiz.h
if exist vlistsize_c.h copy %1\vlistsize_c.h %2\vlistz_c.h
if exist vliststr.h copy %1\vliststr.h %2\vliststr.h
if exist vliststr_c.h copy %1\vliststr_c.h %2\vlists_c.h
if exist vlistview.h copy %1\vlistview.h %2\vlistvie.h
if exist vlistview_c.h copy %1\vlistview_c.h %2\vlistv_c.h
if exist vloadable.h copy %1\vloadable.h %2\vloadabl.h
if exist vloadable_c.h copy %1\vloadable_c.h %2\vloada_c.h
if exist vlocale.h copy %1\vlocale.h %2\vlocale.h
if exist vlock.h copy %1\vlock.h %2\vlock.h
if exist vlongitem.h copy %1\vlongitem.h %2\vlongite.h
if exist vlongitem_c.h copy %1\vlongitem_c.h %2\vlongi_c.h
if exist vlonglong.h copy %1\vlonglong.h %2\vlonglon.h
if exist vlonglong_c.h copy %1\vlonglong_c.h %2\vlongl_c.h
if exist vmaccontrols.h copy %1\vmaccontrols.h %2\vmaccont.h
if exist vmacdialogs.h copy %1\vmacdialogs.h %2\vmacdial.h
if exist vmacerrors.h copy %1\vmacerrors.h %2\vmacerro.h
if exist vmacevents.h copy %1\vmacevents.h %2\vmaceven.h
if exist vmacfiles.h copy %1\vmacfiles.h %2\vmacfile.h
if exist vmacfonts.h copy %1\vmacfonts.h %2\vmacfont.h
if exist vmacgestaltequ.h copy %1\vmacgestaltequ.h %2\vmacgest.h
if exist vmachine.h copy %1\vmachine.h %2\vmachine.h
if exist vmachine_c.h copy %1\vmachine_c.h %2\vmachi_c.h
if exist vmacmemory.h copy %1\vmacmemory.h %2\vmacmemo.h
if exist vmacquickdraw.h copy %1\vmacquickdraw.h %2\vmacquic.h
if exist vmacresources.h copy %1\vmacresources.h %2\vmacreso.h
if exist vmacscript.h copy %1\vmacscript.h %2\vmacscri.h
if exist vmacstrings.h copy %1\vmacstrings.h %2\vmacstri.h
if exist vmacsysequ.h copy %1\vmacsysequ.h %2\vmacsyse.h
if exist vmactypes.h copy %1\vmactypes.h %2\vmactype.h
if exist vmacwindows.h copy %1\vmacwindows.h %2\vmacwind.h
if exist vmaindia.h copy %1\vmaindia.h %2\vmaindia.h
if exist vmainvie.h copy %1\vmainvie.h %2\vmainvie.h
if exist vmainvie_c.h copy %1\vmainvie_c.h %2\vmainv_c.h
if exist vmapping.h copy %1\vmapping.h %2\vmapping.h
if exist vmapping_c.h copy %1\vmapping_c.h %2\vmappi_c.h
if exist vmaskitem.h copy %1\vmaskitem.h %2\vmaskite.h
if exist vmaskitem_c.h copy %1\vmaskitem_c.h %2\vmaski_c.h
if exist vmath.h copy %1\vmath.h %2\vmath.h
if exist vmatrix.h copy %1\vmatrix.h %2\vmatrix.h
if exist vmatrix_c.h copy %1\vmatrix_c.h %2\vmatri_c.h
if exist vmem.h copy %1\vmem.h %2\vmem.h
if exist vmem_c.h copy %1\vmem_c.h %2\vmem_c.h
if exist vmemsys.h copy %1\vmemsys.h %2\vmemsys.h
if exist vmenu.h copy %1\vmenu.h %2\vmenu.h
if exist vmenu_c.h copy %1\vmenu_c.h %2\vmenu_c.h
if exist vmenubar.h copy %1\vmenubar.h %2\vmenubar.h
if exist vmenubar_c.h copy %1\vmenubar_c.h %2\vmenub_c.h
if exist vmessage.h copy %1\vmessage.h %2\vmessage.h
if exist vmodule.h copy %1\vmodule.h %2\vmodule.h
if exist vmodule_c.h copy %1\vmodule_c.h %2\vmodul_c.h
if exist vmswhdrs.h copy %1\vmswhdrs.h %2\vmswhdrs.h
if exist vmutex.h copy %1\vmutex.h %2\vmutex.h
if exist vmutexsys.h copy %1\vmutexsys.h %2\vmutexsy.h
if exist vname.h copy %1\vname.h %2\vname.h
if exist vname_c.h copy %1\vname_c.h %2\vname_c.h
if exist vnameobj.h copy %1\vnameobj.h %2\vnameobj.h
if exist vnameobj_c.h copy %1\vnameobj_c.h %2\vnameo_c.h
if exist vndx.h copy %1\vndx.h %2\vndx.h
if exist vnetdb.h copy %1\vnetdb.h %2\vnetdb.h
if exist vnetinetin.h copy %1\vnetinetin.h %2\vnetinet.h
if exist vnotebook.h copy %1\vnotebook.h %2\vnoteboo.h
if exist vnotebook_c.h copy %1\vnotebook_c.h %2\vnoteb_c.h
if exist vnotice.h copy %1\vnotice.h %2\vnotice.h
if exist vnotice_c.h copy %1\vnotice_c.h %2\vnotic_c.h
if exist vnum.h copy %1\vnum.h %2\vnum.h
if exist vnum_c.h copy %1\vnum_c.h %2\vnum_c.h
if exist vobject.h copy %1\vobject.h %2\vobject.h
if exist vobject_c.h copy %1\vobject_c.h %2\vobjec_c.h
if exist vobservable.h copy %1\vobservable.h %2\vobserva.h
if exist vobservable_c.h copy %1\vobservable_c.h %2\vobsab_c.h
if exist vobserver.h copy %1\vobserver.h %2\vobserve.h
if exist vobserver_c.h copy %1\vobserver_c.h %2\vobser_c.h
if exist voccurrence.h copy %1\voccurrence.h %2\voccurre.h
if exist voccurrence_c.h copy %1\voccurrence_c.h %2\voccur_c.h
if exist vodbc.h copy %1\vodbc.h %2\vodbc.h
if exist vole.h copy %1\vole.h %2\vole.h
if exist vole_c.h copy %1\vole_c.h %2\vole_c.h
if exist volectrl.h copy %1\volectrl.h %2\volectrl.h
if exist volectrl_c.h copy %1\volectrl_c.h %2\volect_c.h
if exist volesite.h copy %1\volesite.h %2\volesite.h
if exist volesite_c.h copy %1\volesite_c.h %2\volesi_c.h
if exist volevariant.h copy %1\volevariant.h %2\volevari.h
if exist volevariant_c.h copy %1\volevariant_c.h %2\voleva_c.h
if exist volegen.h copy %1\volegen.h %2\volegen.h
if exist volegen_c.h copy %1\volegen_c.h %2\volege_c.h
if exist vos2.h copy %1\vos2.h %2\vos2.h
if exist vpaled.h copy %1\vpaled.h %2\vpaled.h
if exist vpalette.h copy %1\vpalette.h %2\vpalette.h
if exist vpalette_c.h copy %1\vpalette_c.h %2\vpalet_c.h
if exist vpanecont.h copy %1\vpanecont.h %2\vpanecon.h
if exist vpanecont_c.h copy %1\vpanecont_c.h %2\vpanec_c.h
if exist vpthscrp.h copy %1\vpthscrp.h %2\vpthscrp.h
if exist vpthscrp_c.h copy %1\vpthscrp_c.h %2\vpthsc_c.h
if exist vpersistent.h copy %1\vpersistent.h %2\vpersist.h
if exist vpersistent_c.h copy %1\vpersistent_c.h %2\vpersi_c.h
if exist vpixmap.h copy %1\vpixmap.h %2\vpixmap.h
if exist vpixmap_c.h copy %1\vpixmap_c.h %2\vpixma_c.h
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
if exist vprintsys.h copy %1\vprintsys.h %2\vprintsy.h
if exist vprocess.h copy %1\vprocess.h %2\vprocess.h
if exist vprocess_c.h copy %1\vprocess_c.h %2\vproce_c.h
if exist vpscontext.h copy %1\vpscontext.h %2\vpsconte.h
if exist vpsdict.h copy %1\vpsdict.h %2\vpsdict.h
if exist vpserror.h copy %1\vpserror.h %2\vpserror.h
if exist vpsfile.h copy %1\vpsfile.h %2\vpsfile.h
if exist vpsinterp.h copy %1\vpsinterp.h %2\vpsinter.h
if exist vpsobject.h copy %1\vpsobject.h %2\vpsobjec.h
if exist vpsop.h copy %1\vpsop.h %2\vpsop.h
if exist vpsscan.h copy %1\vpsscan.h %2\vpsscan.h
if exist vpsstack.h copy %1\vpsstack.h %2\vpsstack.h
if exist vpsvm.h copy %1\vpsvm.h %2\vpsvm.h
if exist vpwd.h copy %1\vpwd.h %2\vpwd.h
if exist vpwditem.h copy %1\vpwditem.h %2\vpwditem.h
if exist vpwditem_c.h copy %1\vpwditem_c.h %2\vpwdit_c.h
if exist vquery.h copy %1\vquery.h %2\vquery.h
if exist vqueryvalue.h copy %1\vqueryvalue.h %2\vqueryva.h
if exist vquerybuilder.h copy %1\vquerybuilder.h %2\vquerybu.h
if exist vre.h copy %1\vre.h %2\vre.h
if exist vreader.h copy %1\vreader.h %2\vreader.h
if exist vrect.h copy %1\vrect.h %2\vrect.h
if exist vrect_c.h copy %1\vrect_c.h %2\vrect_c.h
if exist vredecl.h copy %1\vredecl.h %2\vredecl.h
if exist vreeditor.h copy %1\vreeditor.h %2\vreedito.h
if exist vrefile.h copy %1\vrefile.h %2\vrefile.h
if exist vregexp.h copy %1\vregexp.h %2\vregexp.h
if exist vregexp_c.h copy %1\vregexp_c.h %2\vregex_c.h
if exist vreinit.h copy %1\vreinit.h %2\vreinit.h
if exist vrepanel.h copy %1\vrepanel.h %2\vrepanel.h
if exist vreplabel_c.h copy %1\vreplabel_c.h %2\vreplb_c.h
if exist vreplang.h copy %1\vreplang.h %2\vreplang.h
if exist vreplang_c.h copy %1\vreplang_c.h %2\vrepla_c.h
if exist vreportcomponent.h copy %1\vreportcomponent.h %2\vreportc.h
if exist vreportcomponent_c.h copy %1\vreportcomponent_c.h %2\vrptcm_c.h
if exist vrdchsr.h copy %1\vrdchsr.h %2\vrdchsr.h
if exist vrdchsr_c.h copy %1\vrdchsr_c.h %2\vrdchs_c.h
if exist vrdevchsr.h copy %1\vrdevchsr.h %2\vrdevchs.h
if exist vrdevchsr_c.h copy %1\vrdevchsr_c.h %2\vrdevc_c.h
if exist vreportdevice.h copy %1\vreportdevice.h %2\vreportd.h
if exist vreportdevice_c.h copy %1\vreportdevice_c.h %2\vrptdv_c.h
if exist vreportfiledev.h copy %1\vreportfiledev.h %2\vreportf.h
if exist vreportfiledev_c.h copy %1\vreportfiledev_c.h %2\vrptfd_c.h
if exist vrepfmt.h copy %1\vrepfmt.h %2\vrepfmt.h
if exist vrepfmt_c.h copy %1\vrepfmt_c.h %2\vrepfm_c.h
if exist vreport.h copy %1\vreport.h %2\vreport.h
if exist vreplabel.h copy %1\vreplabel.h %2\vreplabe.h
if exist vreplabel_c.h copy %1\vreplabel_c.h %2\vreplb_c.h
if exist vreportlayout.h copy %1\vreportlayout.h %2\vreportl.h
if exist vreportlayout_c.h copy %1\vreportlayout_c.h %2\vrptlo_c.h
if exist vrepline.h copy %1\vrepline.h %2\vrepline.h
if exist vrepline_c.h copy %1\vrepline_c.h %2\vrepli_c.h
if exist vreportobject.h copy %1\vreportobject.h %2\vreporto.h
if exist vreportobject_c.h copy %1\vreportobject_c.h %2\vrptob_c.h
if exist vreportscreen.h copy %1\vreportscreen.h %2\vreports.h
if exist vreportscreen_c.h copy %1\vreportscreen_c.h %2\vrptos_c.h
if exist vreportppv.h copy %1\vreportppv.h %2\vreportp.h
if exist vreportppv_c.h copy %1\vreportppv_c.h %2\vrptpp_c.h
if exist vreporttree.h copy %1\vreporttree.h %2\vreportt.h
if exist vreporttree_c.h copy %1\vreporttree_c.h %2\vrpttr_c.h
if exist vreport_c.h copy %1\vreport_c.h %2\vrepor_c.h
if exist vreportdevice_c.h copy %1\vreportdevice_c.h %2\vrptdv_c.h
if exist vreportlayout_c.h copy %1\vreportlayout_c.h %2\vrptlo_c.h
if exist vrepvar.h copy %1\vrepvar.h %2\vrepvar.h
if exist vrepvar_c.h copy %1\vrepvar_c.h %2\vrepva_c.h
if exist vreputil.h copy %1\vreputil.h %2\vreputil.h
if exist vreputil_c.h copy %1\vreputil_c.h %2\vreput_c.h
if exist vrereg.h copy %1\vrereg.h %2\vrereg.h
if exist vres.h copy %1\vres.h %2\vres.h
if exist vresfile.h copy %1\vresfile.h %2\vresfile.h
if exist vresfile_c.h copy %1\vresfile_c.h %2\vresfi_c.h
if exist vresolver.h copy %1\vresolver.h %2\vresolve.h
if exist vresolver_c.h copy %1\vresolver_c.h %2\vresol_c.h
if exist vresource.h copy %1\vresource.h %2\vresourc.h
if exist vresource_c.h copy %1\vresource_c.h %2\vresou_c.h
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
if exist vscribe_c.h copy %1\vscribe_c.h %2\vscrib_c.h
if exist vsepar.h copy %1\vsepar.h %2\vsepar.h
if exist vsepar_c.h copy %1\vsepar_c.h %2\vsepar_c.h
if exist vsequence.h copy %1\vsequence.h %2\vsequenc.h
if exist vsequence_c.h copy %1\vsequence_c.h %2\vseque_c.h
if exist vservice.h copy %1\vservice.h %2\vservice.h
if exist vservice_c.h copy %1\vservice_c.h %2\vservi_c.h
if exist vsvcchsr.h copy %1\vsvcchsr.h %2\vsvcchsr.h
if exist vsvcchsr_c.h copy %1\vsvcchsr_c.h %2\vsvcch_c.h
if exist vsession.h copy %1\vsession.h %2\vsession.h
if exist vsession_c.h copy %1\vsession_c.h %2\vsessi_c.h
if exist vsetjmp.h copy %1\vsetjmp.h %2\vsetjmp.h
if exist vsignal.h copy %1\vsignal.h %2\vsignal.h
if exist vsiggrp.h copy %1\vsiggrp.h %2\vsiggrp.h
if exist vsiggrp_c.h copy %1\vsiggrp_c.h %2\vsiggr_c.h
if exist vsignature.h copy %1\vsignature.h %2\vsignatu.h
if exist vsignature_c.h copy %1\vsignature_c.h %2\vsigna_c.h
if exist vsingle.h copy %1\vsingle.h %2\vsingle.h
if exist vsizeview.h copy %1\vsizeview.h %2\vsizevie.h
if exist vsizeview_c.h copy %1\vsizeview_c.h %2\vsizev_c.h
if exist vslider.h copy %1\vslider.h %2\vslider.h
if exist vslider_c.h copy %1\vslider_c.h %2\vslide_c.h
if exist vsock.h copy %1\vsock.h %2\vsock.h
if exist vsocksys.h copy %1\vsocksys.h %2\vsocksys.h
if exist vsockmac.h copy %1\vsockmac.h %2\vsockmac.h
if exist vsockos2.h copy %1\vsockos2.h %2\vsockos2.h
if exist vsocktcp.h copy %1\vsocktcp.h %2\vsocktcp.h
if exist vsockudp.h copy %1\vsockudp.h %2\vsockudp.h
if exist vsockunx.h copy %1\vsockunx.h %2\vsockunx.h
if exist vsockwin.h copy %1\vsockwin.h %2\vsockwin.h
if exist vspinner.h copy %1\vspinner.h %2\vspinner.h
if exist vspinner_c.h copy %1\vspinner_c.h %2\vspinn_c.h
if exist vsplit.h copy %1\vsplit.h %2\vsplit.h
if exist vsplit_c.h copy %1\vsplit_c.h %2\vsplit_c.h
if exist vsplitter.h copy %1\vsplitter.h %2\vsplitte.h
if exist vspring.h copy %1\vspring.h %2\vspring.h
if exist vspring_c.h copy %1\vspring_c.h %2\vsprin_c.h
if exist vsprdom.h copy %1\vsprdom.h %2\vsprdom.h
if exist vsprdom_c.h copy %1\vsprdom_c.h %2\vsprdo_c.h
if exist vsprview.h copy %1\vsprview.h %2\vsprview.h
if exist vstartup.h copy %1\vstartup.h %2\vstartup.h
if exist vstartup_c.h copy %1\vstartup_c.h %2\vstart_c.h
if exist vstatus.h copy %1\vstatus.h %2\vstatus.h
if exist vstatusbar.h copy %1\vstatusbar.h %2\vstatusb.h
if exist vstatusbar_c.h copy %1\vstatusbar_c.h %2\vstatb_c.h
if exist vstd.h copy %1\vstd.h %2\vstd.h
if exist vstdarg.h copy %1\vstdarg.h %2\vstdarg.h
if exist vstddef.h copy %1\vstddef.h %2\vstddef.h
if exist vstdio.h copy %1\vstdio.h %2\vstdio.h
if exist vstdiosys.h copy %1\vstdiosys.h %2\vstdiosy.h
if exist vstdlib.h copy %1\vstdlib.h %2\vstdlib.h
if exist vstr.h copy %1\vstr.h %2\vstr.h
if exist vstr_c.h copy %1\vstr_c.h %2\vstr_c.h
if exist vstrchsr.h copy %1\vstrchsr.h %2\vstrchsr.h
if exist vstrchsr_c.h copy %1\vstrchsr_c.h %2\vstrch_c.h
if exist vstream.h copy %1\vstream.h %2\vstream.h
if exist vstream_c.h copy %1\vstream_c.h %2\vstrea_c.h
if exist vstring.h copy %1\vstring.h %2\vstring.h
if exist vstritem.h copy %1\vstritem.h %2\vstritem.h
if exist vstritem_c.h copy %1\vstritem_c.h %2\vstrit_c.h
if exist vstylechsr.h copy %1\vstylechsr.h %2\vstylech.h
if exist vstylechsr_c.h copy %1\vstylechsr_c.h %2\vstyle_c.h
if exist vsys.h copy %1\vsys.h %2\vsys.h
if exist vsysdir.h copy %1\vsysdir.h %2\vsysdir.h
if exist vsysfile.h copy %1\vsysfile.h %2\vsysfile.h
if exist vsysioctl.h copy %1\vsysioctl.h %2\vsysioct.h
if exist vsysipc.h copy %1\vsysipc.h %2\vsysipc.h
if exist vsysmntent.h copy %1\vsysmntent.h %2\vsysmnte.h
if exist vsysparam.h copy %1\vsysparam.h %2\vsyspara.h
if exist vsysresource.h copy %1\vsysresource.h %2\vsysreso.h
if exist vsysselect.h copy %1\vsysselect.h %2\vsyssele.h
if exist vsysshm.h copy %1\vsysshm.h %2\vsysshm.h
if exist vsyssocket.h copy %1\vsyssocket.h %2\vsyssock.h
if exist vsysstat.h copy %1\vsysstat.h %2\vsysstat.h
if exist vsyssysteminfo.h copy %1\vsyssysteminfo.h %2\vsysinfo.h
if exist vsystime.h copy %1\vsystime.h %2\vsystime.h
if exist vsystimes.h copy %1\vsystimes.h %2\vsystims.h
if exist vsystypes.h copy %1\vsystypes.h %2\vsystype.h
if exist vsysuio.h copy %1\vsysuio.h %2\vsysuio.h
if exist vsysun.h copy %1\vsysun.h %2\vsysun.h
if exist vsysutsname.h copy %1\vsysutsname.h %2\vsysutsn.h
if exist vsyswait.h copy %1\vsyswait.h %2\vsyswait.h
if exist vtableview.h copy %1\vtableview.h %2\vtablevi.h
if exist vtableview_c.h copy %1\vtableview_c.h %2\vtblv_c.h
if exist vterm.h copy %1\vterm.h %2\vterm.h
if exist vtest.h copy %1\vtest.h %2\vtest.h
if exist vtest_c.h copy %1\vtest_c.h %2\vtest_c.h
if exist vtext.h copy %1\vtext.h %2\vtext.h
if exist vtext_c.h copy %1\vtext_c.h %2\vtext_c.h
if exist vtextitem.h copy %1\vtextitem.h %2\vtextite.h
if exist vtextitem_c.h copy %1\vtextitem_c.h %2\vtexti_c.h
if exist vtextmarker.h copy %1\vtextmarker.h %2\vtextmar.h
if exist vtextmarker_c.h copy %1\vtextmarker_c.h %2\vtextm_c.h
if exist vtextruler.h copy %1\vtextruler.h %2\vtextrul.h
if exist vtextruler_c.h copy %1\vtextruler_c.h %2\vtextr_c.h
if exist vtextsel.h copy %1\vtextsel.h %2\vtextsel.h
if exist vtextsel_c.h copy %1\vtextsel_c.h %2\vtexts_c.h
if exist vtextview.h copy %1\vtextview.h %2\vtextvie.h
if exist vtextview_c.h copy %1\vtextview_c.h %2\vtextv_c.h
if exist vthread.h copy %1\vthread.h %2\vthread.h
if exist vthread_c.h copy %1\vthread_c.h %2\vthrea_c.h
if exist vthreader.h copy %1\vthreader.h %2\vthreade.h
if exist vthrdrss.h copy %1\vthrdrss.h %2\vthrdrss.h
if exist vthreadsys.h copy %1\vthreadsys.h %2\vthreads.h
if exist vthreadsys_c.h copy %1\vthreadsys_c.h %2\vthrds_c.h
if exist vtime.h copy %1\vtime.h %2\vtime.h
if exist vtimer.h copy %1\vtimer.h %2\vtimer.h
if exist vtimer_c.h copy %1\vtimer_c.h %2\vtimer_c.h
if exist vtimestamp.h copy %1\vtimestamp.h %2\vtimesta.h
if exist vtimestamp_c.h copy %1\vtimestamp_c.h %2\vtimes_c.h
if exist vstmpsys.h copy %1\vstmpsys.h %2\vstmpsys.h
if exist vtoolbar.h copy %1\vtoolbar.h %2\vtoolbar.h
if exist vtoolbar_c.h copy %1\vtoolbar_c.h %2\vtoolb_c.h
if exist vtbrearranger.h copy %1\vtbrearranger.h %2\vtbrearr.h
if exist vtbrearranger_c.h copy %1\vtbrearranger_c.h %2\vtbrar_c.h
if exist vtbsepar.h copy %1\vtbsepar.h %2\vtbsepar.h
if exist vtbsepar_c.h copy %1\vtbsepar_c.h %2\vtbsep_c.h
if exist vtoolbtn.h copy %1\vtoolbtn.h %2\vtoolbtn.h
if exist vtoolbtn_c.h copy %1\vtoolbtn_c.h %2\vtolbt_c.h
if exist vtoolchanger.h copy %1\vtoolchanger.h %2\vtolchgr.h
if exist vtoolchanger_c.h copy %1\vtoolchanger_c.h %2\vtolch_c.h
if exist vtooltip.h copy %1\vtooltip.h %2\vtooltip.h
if exist vtooltip_c.h copy %1\vtooltip_c.h %2\vtoolt_c.h
if exist vtransform.h copy %1\vtransform.h %2\vtransfo.h
if exist vtransform_c.h copy %1\vtransform_c.h %2\vtrans_c.h
if exist vtrans.h copy %1\vtrans.h %2\vtrans.h
if exist vtrans_c.h copy %1\vtrans_c.h %2\vtrnsl_c.h
if exist vtree.h copy %1\vtree.h %2\vtree.h
if exist vtree_c.h copy %1\vtree_c.h %2\vtree_c.h
if exist vtreecard.h copy %1\vtreecard.h %2\vtreecar.h
if exist vtreecard_c.h copy %1\vtreecard_c.h %2\vtreec_c.h
if exist vtreelist.h copy %1\vtreelist.h %2\vtreelis.h
if exist vtreelist_c.h copy %1\vtreelist_c.h %2\vtreel_c.h
if exist vtreeview.h copy %1\vtreeview.h %2\vtreevie.h
if exist vtreeview_c.h copy %1\vtreeview_c.h %2\vtreev_c.h
if exist vtypeditem.h copy %1\vtypeditem.h %2\vtypedit.h
if exist vtypeditem_c.h copy %1\vtypeditem_c.h %2\vtypdi_c.h
if exist vulimit.h copy %1\vulimit.h %2\vulimit.h
if exist vulongitem.h copy %1\vulongitem.h %2\vulongit.h
if exist vulongitem_c.h copy %1\vulongitem_c.h %2\vulngi_c.h
if exist vundo.h copy %1\vundo.h %2\vundo.h
if exist vundo_c.h copy %1\vundo_c.h %2\vundo_c.h
if exist vundocompat.h copy %1\vundocompat.h %2\vundocom.h
if exist vunistd.h copy %1\vunistd.h %2\vunistd.h
if exist vurl.h copy %1\vurl.h %2\vurl.h
if exist vurl_c.h copy %1\vurl_c.h %2\vurl_c.h
if exist vut.h copy %1\vut.h %2\vut.h
if exist vutime.h copy %1\vutime.h %2\vutime.h
if exist vvalues.h copy %1\vvalues.h %2\vvalues.h
if exist vvarray.h copy %1\vvarray.h %2\vvarray.h
if exist vvaxfloat.h copy %1\vvaxfloat.h %2\vvaxfloa.h
if exist vvint.h copy %1\vvint.h %2\vvint.h
if exist vvmstypes.h copy %1\vvmstypes.h %2\vvmstype.h
if exist vwaitos2.h copy %1\vwaitos2.h %2\vwaitos2.h
if exist vwaitunx.h copy %1\vwaitunx.h %2\vwaitunx.h
if exist vwebbrowse.h copy %1\vwebbrowse.h %2\vwebbrow.h
if exist vwebbrowse_c.h copy %1\vwebbrowse_c.h %2\vwebbr_c.h
if exist vwindow.h copy %1\vwindow.h %2\vwindow.h
if exist vwindow_c.h copy %1\vwindow_c.h %2\vwindo_c.h
if exist vwindowsys.h copy %1\vwindowsys.h %2\vwindows.h
if exist vx11.h copy %1\vx11.h %2\vx11.h
if exist vx11cursorfont.h copy %1\vx11cursorfont.h %2\vx11curs.h
if exist vx11extensionsxshm.h copy %1\vx11extensionsxshm.h %2\vx11exte.h
if exist vx11keysym.h copy %1\vx11keysym.h %2\vx11keys.h
if exist vx11xatom.h copy %1\vx11xatom.h %2\vx11xato.h
if exist vx11xlib.h copy %1\vx11xlib.h %2\vx11xlib.h
if exist vx11xutil.h copy %1\vx11xutil.h %2\vx11xuti.h
if exist vxxloadable.h copy %1\vxxloadable.h %2\vxxloada.h
:END
