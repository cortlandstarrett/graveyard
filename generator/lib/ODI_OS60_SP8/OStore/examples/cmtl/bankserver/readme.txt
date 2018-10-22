BankServer COM+ example application

This is a sample middle tier application that works in a COM+ server.  The 
example is setup as a Visual Studio Workspace.  The workspace is called 
BankServer and consists of the following Visual Studio projects:

  BankUtils - BankUtils.dll, Some usefull utility code.  Contains the code
              to initialize and shutdown CMTL.  This DLL is used by
              other projects.

  Account - Account.dll, An inprocess COM server.  Contains the CMTL code 
            which uses virtual transactions to read and update the bank 
            account databases.  Account.dll is used by InitializeData
            and BankServer.

  BankMsgLog - BankMsgLog.dll, an inprocess COM server. This is a message 
               logging mechanism which can relay text messages between two 
               processes.  It is used by the BankServer and 
               BankServerConsole.

  BankServer - BankServer.dll, an inprocess COM server. 
               This is the Middle Tier COM+ server.  It is added to 
               the Component Services as a Server Application.

  BankClients - BankClients.exe, client of BankServer.  This application 
                simulates a group of bank customers who are using their 
                checking and savings accounts.
 
  BankServerConsole - BankServerConsole.exe, client of BankServer.  This 
                      application is used to start, stop, and monitor the 
                      BankServer.

  InitializeData - InitializeData.exe.  Single process application which is 
                   used to create the initial databases which are used by 
                   the BankServer.

The source code of this example is contained in the BankServer.zip file.
You can unzip the contents of this ZIP file into a directory that you
choose.  See the file instructions.txt for information about how to build 
and run the BankServer application.

