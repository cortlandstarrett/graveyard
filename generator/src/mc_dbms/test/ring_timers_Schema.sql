--========================================================================
--
--File:      $RCSfile: ring_timers_Schema.sql,v $
--Version:   $Revision: 1.9 $
--Modified:  $Date: 2013/01/10 23:41:41 $
--
--(c) Copyright 2005-2013 by Mentor Graphics Corp. All rights reserved.
--
--========================================================================
--This document contains information proprietary and confidential to
--Mentor Graphics Corp., and is not for external distribution.
--======================================================================== 
--
CREATE TABLE M (
	current_state	integer,
	dips	integer,
    tag     integer,
    circleCount integer);

CREATE TABLE W (
	current_state	integer,
	swings	integer,
    num     integer);

CREATE TABLE B (
	current_state	integer,
    berry_count	integer);

