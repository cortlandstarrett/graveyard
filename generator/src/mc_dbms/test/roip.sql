--========================================================================
--
--File:      $RCSfile: roip.sql,v $
--Version:   $Revision: 1.9 $
--Modified:  $Date: 2013/01/10 23:41:40 $
--
--(c) Copyright 2005-2013 by Mentor Graphics Corp. All rights reserved.
--
--========================================================================
--This document contains information proprietary and confidential to
--Mentor Graphics Corp., and is not for external distribution.
--======================================================================== 
--
CREATE TABLE O_OBJ (
	Obj_ID	UNIQUE_ID );

CREATE TABLE O_ATTR (
	Obj_ID	UNIQUE_ID );

CREATE ROP REF_ID R102	FROM MC O_ATTR	(Obj_ID)
			  TO 1  O_OBJ	(Obj_ID);

INSERT INTO O_OBJ
	VALUES (1048578);
    
INSERT INTO O_ATTR
	VALUES (1048578);

