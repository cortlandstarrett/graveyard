/*=========================================================================
 *
 * File:      main_gen_erate.cc
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corporation, and is not for external distribution 
 *========================================================================
 */
#include <mc_dbms/database.h>
#include <mc_dbms/persistence.h>
#include <u_typdef.hh>
#include <string>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <map>
#include <deque>
#include <ctime>
#include <iomanip>
#include <vstartup.h>
#include <vformat.h>
#include <tclap/CmdLine.h>
#include <u_string.hh>
#include <u_trace.hh>
#include <gs_ui.hh>
#include <u_mc_dbms.hh>
#include <u_keyword.hh>
#include <gs_arch.hh>
#include <i_idb.hh>
#include <gs_func.hh>
#include <gs_sub.hh>
extern "C" {
#include <pt_trans.h>
}
#ifdef WIN32
#include <windows.h>
/**
 * The values of BELOW_NORMAL and ABOVE_NORMAL are only valid on XP (and above).
 * They  will be ignored if used on NT, Win95, Win98, or WinMe
 */
#ifndef BELOW_NORMAL_PRIORITY_CLASS
#define BELOW_NORMAL_PRIORITY_CLASS 0x00004000
#endif

#ifndef ABOVE_NORMAL_PRIORITY_CLASS
#define ABOVE_NORMAL_PRIORITY_CLASS 0x00008000
#endif

#endif

using namespace TCLAP;
using namespace std;

int gen_import_main (const std::string&);
int gen_file_main (const std::string&);
void parseCommandLineOptions(int argc, char** argv);
void initGenerator(int argc, char** argv);
void generate();
void validateCommandLineOptions();
void reportTime(const std::string& msg);
string getAppName(const string& cmdLineName);
void buildInputFileList(MultiArg<string>& sqlFiles, MultiArg<string>& archFiles);
void validateDomainCode(int domain);
int getDomainCode(int filePosition, int numFilesProcessed);

/**
 * Global variables that hold command-line results
 */

const std::string CurrentVersionString("$Revision: 2.9 $");

mc_dbms_database*   GS_gen_sim_db_ptr = 0;
t_boolean           s_quit_on_error = FALSE;
t_int               s_number_of_errors = 0;
t_boolean           use_log_file = false;;
long                num_populations = 0;
GS_string           gen_file_name_str;
GS_string           log_volume_str;
GS_string           log_trace_on_full_blast_password_str;
String              default_feature;
GS_string           arc_file_name_str;
int                 GS_domain_code = -1;
t_boolean           is_simulator = false;
bool gen_import_only = false;
bool gen_file_only = false;
bool persistenceEnabled = true;
bool debug = false;
bool ThisIsGenImport = false;
bool sourceLicense3020Used = false;
bool binaryLicense3020Used = false;
bool sourceLicense2020Used = false;
bool binaryLicense2020Used = false;
bool sourceLicenseSystemCUsed = false;
bool sourceLicenseVHDLUsed = false;

time_t g_start,g_end;

/**
 *  Declare a global variable to hold a pointer to the process name so that
 *  a logfile of the appropriate name may be opened up for LOG_ERROR,
 *  LOG_REPORT, and LOG_TRACE.
 *
 */
char* process_name_char_ptr = "gen_erate";

enum Generator_InputFileType {
  SQL_FILE,
  Archetype_File,
};

class Generator_InputFile {
public:
  Generator_InputFile(std::string& fileName, Generator_InputFileType type) :
    m_fileName(fileName), m_type(type)
  { }

  virtual ~Generator_InputFile() { }

  std::string m_fileName;
  Generator_InputFileType m_type;
};

/**
 * The key for this map is the position on the command-line where the "-d"
 * option was seen, and the value specified holds the type and name of the file.
 */
typedef std::map<int, Generator_InputFile> InputFileMap;

/**
 * The key for this map is the position on the command-line where the "-d"
 * option was seen, and the value is that domain-code that was specified.
 */
typedef std::map<int, int> DomainCodeMap;
DomainCodeMap DomainCodes;

/**
 * This collections hold the names of the input files to process sorted by
 * their position on the command-line.
 */
InputFileMap InputFiles;

/**
 * This routine proceses every command-line option that may be seen by gen_erate.  This
 * includes options that are needed by both gen_import and gen_file.  It uses TCLAP
 * to manage the command-line options.
 *
 */
int main(int argc, char** argv)
{
  int result = 0;
  time (&g_start);

  try {
    parseCommandLineOptions(argc, argv);

    initGenerator(argc, argv);

    validateCommandLineOptions();

    // Process the command-line
    generate();

  } catch(ArgException& argErr) {
    std::cerr   << "Error: "
          << argErr.error()
          << " for arg "
          << argErr.argId()
          << endl;
    result = 1;
  } catch(std::exception& error) {
    std::cerr   << std::endl
          << error.what()
          << std::endl;
    result = 2;
  }

  return result;
}

/**
 * This routine calls gen_import_main and/or gen_file_main as specified by the
 * command-line.
 */
void generate()
{
  if ( debug ) {
    __asm int 3;
  }

    GS_gen_sim_db_ptr = mc_dbms_database::get_persistent_database();

  mc_dbms_database::setSerializationFlag(persistenceEnabled);
  if (persistenceEnabled) {
    Persistence::restore(gen_file_name_str.char_ptr(), true);

    std::string timMsg("Time to restore: ");
    timMsg += gen_file_name_str.char_ptr();
      reportTime(timMsg);
  }

  int numSQLFilesProcessed = 0;
  int numArchFilesProcessed = 0;
   InputFileMap::iterator fileIter = InputFiles.begin();
   for (; fileIter != InputFiles.end(); ++fileIter) {
     std::string timMsg;
     switch (fileIter->second.m_type) {
     case SQL_FILE:
       GS_domain_code = getDomainCode(fileIter->first, numSQLFilesProcessed);
       gen_import_main(fileIter->second.m_fileName);
       timMsg = "Time to complete gen_import_main of ";
      numSQLFilesProcessed++;
       break;

     case Archetype_File:
       if ( numArchFilesProcessed == 0 ) {
          GS_substitution::translate_parm = pt_TranslateInit();
       }

       gen_file_main(fileIter->second.m_fileName);
       timMsg = "Time to complete gen_file_main of ";
       numArchFilesProcessed++;
       break;

     default:
       throw std::runtime_error("Invalid input file type.");
     }

    timMsg += fileIter->second.m_fileName;
      reportTime(timMsg);
   }

   if (numArchFilesProcessed > 0) {
      pt_TranslateCleanup( GS_substitution::translate_parm );
   }

  if (persistenceEnabled) {
    Persistence::persist(gen_file_name_str.char_ptr());

    std::string timMsg("Time to persist: ");
    timMsg += gen_file_name_str.char_ptr();
      reportTime(timMsg);
  }

  L_log::close_log_files ();
}

/**
 * Determine the domain code that should be given the number of files processed
 * so far, and the position of the current file on the command-line.
 *
 * @param filePosition The location on the command-line where the file that is
 *                     about to be processed was found.
 * @param numFilesProcessed The number of files of type SQL_FILE that were
 *                          processed before this one.
 */
int getDomainCode(int filePosition, int numFilesProcessed)
{
  // The value of -1 tells gen_import to use the next available domain
  // code.
  int domainCode = -1;

  if (ThisIsGenImport) {
    // If we are running as gen_import than there is only one domain-code
    // and we set it right after parsing the command-line arguments.
    domainCode = GS_domain_code;
  } else {
    // We subtract 2 instead of 1 because the value stored is the position
    // of the command-line option, so we need to skip past the value.
    int domainCodePosition = filePosition - 2;
    DomainCodeMap::iterator iter = DomainCodes.find(domainCodePosition);
    if (iter != DomainCodes.end()) {
      domainCode = iter->second;
    }
  }

  return domainCode;
}

void parseCommandLineOptions(int argc, char** argv)
{
  std::string appName = getAppName(argv[0]);

  bool thisIsGenFile = (appName == "gen_file");
  ThisIsGenImport = (appName == "gen_import");
  std::string descrip = "Unused";
  if (ThisIsGenImport) {
    descrip = "SQL input file";
  } else if (thisIsGenFile) {
    descrip = "Archetype file";
  }

  CmdLine cmd(appName, ' ', CurrentVersionString);

  // Define all the possible options, but we'll only use the ones that we have to
  // based on how we are being called.
  ValueArg<long>        arg_numFilesToGen(      "", "#", "Number of files to generate", false, 0, "integer");
  ValueArg<string>  arg_genFileName(        "", "f", "Generated file name (database)", false, "", "string");
  SwitchArg             arg_useLogFile(         "", "l", "Use log file", false);
  SwitchArg             arg_quitOnError(        "", "q", "Quit on error", false);
  ValueArg<string>  arg_verboseMode(        "", "v", "Verbose mode (STMT, COMP, or SYS)", false, "", "string");
  ValueArg<string>  arg_fullBlastLogging(   "", "t", "Full-blast logging", false, "", "string");
  ValueArg<string>  arg_featureToEnable(    "", "e", "Enable specified feature", false, "", "string");
  SwitchArg             arg_noPersistence(      "", "nopersist", "Disable persistence", false);
  MultiArg<string>  arg_sqlFileList(        "", "import", "Data file name(s)", false, "string");
  MultiArg<string>  arg_archFileList(       "", "arch", "Archetype file name(s)", false, "string");
  MultiArg<int>         arg_multiDomainCode(    "", "d", "The domain code.  This argument must immediately precede the \"-import\" argument that it applies to.", false, "integer");
  ValueArg<int>         arg_singleDomainCode(   "", "d", "The domain code.", false, -1, "integer");
  SwitchArg                 arg_3020SourceLicense( "", "l3s", "Use MC-3020 source license", false);
  SwitchArg                 arg_3020BinaryLicense( "", "l3b", "Use MC-3020 binary license", false);
  SwitchArg                 arg_2020SourceLicense( "", "l2s", "Use MC-2020 source license", false);
  SwitchArg                 arg_2020BinaryLicense( "", "l2b", "Use MC-2020 binary license", false);
  SwitchArg                 arg_SystemCSourceLicense( "", "lSCs", "Use SystemC source license", false);
  SwitchArg                 arg_VHDLSourceLicense( "", "lVHs", "Use VHDL source license", false);
#ifdef _DEBUG
  SwitchArg             arg_debug(              "", "debug", "Debug the application (int 3 breakpoint)", false);
#endif
#ifdef WIN32
  std::string priority_descrip;
  priority_descrip = "Set process priority.  Acceptable values are:\n";
  priority_descrip += "\t\tNORMAL_PRIORITY_CLASS = 32\n";
  priority_descrip += "\t\tIDLE_PRIORITY_CLASS = 64\n";
  priority_descrip += "\t\tHIGH_PRIORITY_CLASS = 128\n";
  priority_descrip += "\t\tREALTIME_PRIORITY_CLASS = 256\n";
  priority_descrip += "\t\tBELOW_NORMAL_PRIORITY_CLASS = 16384 (default)\n";
  priority_descrip += "\t\tABOVE_NORMAL_PRIORITY_CLASS = 32768\n";

  ValueArg<long>        arg_priority(       "", "priority", priority_descrip, false, (DWORD)BELOW_NORMAL_PRIORITY_CLASS, "integer");
#endif

  // This is only used in backward-compatibily mode
  UnlabeledValueArg<string>  arg_gen_db( "gen_db", "Name of the gen database", "", "string"  );
  // This is only used in backward-compatibily mode
  UnlabeledValueArg<string>  arg_input_file( "input_file", descrip, "", "string"  );

  // First we'll add-in the common command-line options
  cmd.add( arg_numFilesToGen );
  cmd.add( arg_genFileName );
  cmd.add( arg_useLogFile );
  cmd.add( arg_quitOnError );
  cmd.add( arg_verboseMode );
  cmd.add( arg_fullBlastLogging );
  cmd.add( arg_featureToEnable );
  cmd.add( arg_noPersistence );
  cmd.add( arg_3020SourceLicense );
  cmd.add( arg_3020BinaryLicense );
  cmd.add( arg_2020SourceLicense );
  cmd.add( arg_2020BinaryLicense );
  cmd.add( arg_SystemCSourceLicense );
  cmd.add( arg_VHDLSourceLicense );
#ifdef _DEBUG
  cmd.add( arg_debug );
#endif
#ifdef WIN32
  cmd.add( arg_priority );
#endif

  // Add command-line options specific to this run.
  if ( thisIsGenFile ) {
    cmd.add( arg_gen_db );
    cmd.add( arg_input_file );
  } else if (ThisIsGenImport) {
    cmd.add( arg_singleDomainCode );
    cmd.add( arg_gen_db );
    cmd.add( arg_input_file );
  } else  {
    cmd.add( arg_multiDomainCode );
    cmd.add( arg_sqlFileList );
    cmd.add( arg_archFileList );
  }

    // Parse
  cmd.parse( argc, argv );

    // Retrieve the common values
  num_populations = arg_numFilesToGen.getValue();
    use_log_file = arg_useLogFile.getValue();
  s_quit_on_error = arg_quitOnError.getValue();
  log_volume_str = arg_verboseMode.getValue().c_str();
  log_trace_on_full_blast_password_str = arg_fullBlastLogging.getValue().c_str();
  default_feature = arg_featureToEnable.getValue().c_str();
  persistenceEnabled = !arg_noPersistence.getValue();
  sourceLicense3020Used = arg_3020SourceLicense.getValue();
  binaryLicense3020Used = arg_3020BinaryLicense.getValue();
  sourceLicense2020Used = arg_2020SourceLicense.getValue();
  binaryLicense2020Used = arg_2020BinaryLicense.getValue();
  sourceLicenseSystemCUsed = arg_SystemCSourceLicense.getValue();
  sourceLicenseVHDLUsed = arg_VHDLSourceLicense.getValue();
#ifdef _DEBUG
  debug = arg_debug.getValue();
#endif
#ifdef WIN32
  DWORD priorityClass = arg_priority.getValue();
  // If it's not one of the valid priorities set it to below normal
  if (priorityClass != NORMAL_PRIORITY_CLASS &&
    priorityClass != IDLE_PRIORITY_CLASS &&
    priorityClass != HIGH_PRIORITY_CLASS &&
    priorityClass != REALTIME_PRIORITY_CLASS &&
    priorityClass != BELOW_NORMAL_PRIORITY_CLASS &&
    priorityClass != ABOVE_NORMAL_PRIORITY_CLASS
    )
  {
    priorityClass = (DWORD)BELOW_NORMAL_PRIORITY_CLASS;
  }

  HANDLE procHandle = GetCurrentProcess();
  SetPriorityClass(procHandle, priorityClass);
#endif

  // Retrieve the values specific to this run.
  if (thisIsGenFile) {
    gen_file_only = true;
    std::string genDBName  = arg_gen_db.getValue();
    std::string archFile  = arg_input_file.getValue();
    Generator_InputFile inputFile(archFile, Archetype_File);
    InputFiles.insert( std::make_pair(0, inputFile) );
    if (arg_genFileName.getValue().empty()) {
      gen_file_name_str = arg_gen_db.getValue().c_str();
    } else {
      gen_file_name_str = arg_genFileName.getValue().c_str();
    }
  } else if (ThisIsGenImport) {
    gen_import_only = true;
    GS_domain_code = arg_singleDomainCode.getValue();
    validateDomainCode(GS_domain_code);
    std::string genDBName  = arg_gen_db.getValue();
    std::string sqlFile  = arg_input_file.getValue();
    Generator_InputFile inputFile(sqlFile, SQL_FILE);
    InputFiles.insert( std::make_pair(0, inputFile) );
    if (arg_genFileName.getValue().empty()) {
      gen_file_name_str = arg_gen_db.getValue().c_str();
    } else {
      gen_file_name_str = arg_genFileName.getValue().c_str();
    }
  } else {
    gen_file_name_str = arg_genFileName.getValue().c_str();

    // Find all the domain codes that were specified and store them by the
    // position on the command-line where they were found.
    const int numDomains = arg_multiDomainCode.getValue().size();
    for (int i = 0; i < numDomains; ++i) {
      int domain = arg_multiDomainCode.getValue()[i];
      validateDomainCode(domain);
      int cmdLinePosition = arg_multiDomainCode.getPosition()[i];
      DomainCodes.insert( std::make_pair(cmdLinePosition, domain) );
    }

    // Populate the InputFiles map
    buildInputFileList(arg_sqlFileList, arg_archFileList);

  }

  if (persistenceEnabled && gen_file_name_str == "") {
    gen_file_name_str = "mcdbms.gen";
  }
}

/**
 * This is a helper function used to populate the list of files we are going to
 * process.  These input files are stored in a collection that is sorted
 * by the position of the argument on the command-line.  This allows us to assure
 * that these input files are processed in the order specified.
 *
 * @param sqlFiles This is a reference to an object that holds all the  sql import
 *                 files that were specified on the command line.
 * @param archFiles This is a reference to an object that holds all the  archetype
 *                  files that were specified on the command line.
 */
void buildInputFileList(MultiArg<string>& sqlFiles, MultiArg<string>& archFiles)
{
  const int numSqlFiles = sqlFiles.getValue().size();
  for (int i = 0; i < numSqlFiles; ++i) {
    std::string fileName = sqlFiles.getValue()[i];
    int cmdLinePosition = sqlFiles.getPosition()[i];
    Generator_InputFile inputFile(fileName, SQL_FILE);
    InputFiles.insert( std::make_pair(cmdLinePosition, inputFile) );
  }

  const int numArchFiles = archFiles.getValue().size();
  for (int j = 0; j < numArchFiles; ++j) {
    std::string fileName = archFiles.getValue()[j];
    int cmdLinePosition = archFiles.getPosition()[j];
    Generator_InputFile inputFile(fileName, Archetype_File);
    InputFiles.insert( std::make_pair(cmdLinePosition, inputFile) );
  }
}

/**
 * This is a helper function used to "munge" (invalidate) the paths to
 * archetype files that are passed to the generator when running in binary
 * mode.
 */
void mungeInputArchFilePaths()
{
  InputFileMap::iterator fileIter = InputFiles.begin();
  for ( ; fileIter != InputFiles.end(); ++fileIter ) {
    if ( Archetype_File == fileIter->second.m_type ) {
      std::string name_no_path = fileIter->second.m_fileName;
      std::string::size_type index = name_no_path.find_last_of( "\\/" );
      if ( (index != std::string::npos) && (index + 1 != std::string::npos) ) {
        name_no_path = name_no_path.substr( index + 1 );
      }
      fileIter->second.m_fileName = ":binarc/" + name_no_path;
    }
  }
  // Look for the file in the encrypted archetypes map.  If found
  // use that, otherwise, read from the file system
}

/**
 * Make sure the given domain code is with the specified range.  If it is not
 * within the specified range then throw an exception.
 */
void validateDomainCode(int domainCode)
{
  // Validate the domain code (Note that -1 is a default that means; use next
  // available domain code.
  if ((GS_domain_code < -1) || (GS_domain_code > 15) )
  {
        std::string msg("\nERROR:  Domain code is not between 0-15 inclusive.\n\n");
    throw std::runtime_error( msg );
  }
}

/**
 * Verify that the command-line options are valid.  This routine will throw
 * an exception if it encounters an error.
 */
void validateCommandLineOptions()
{
  // validate full-blast logging password
    if (log_trace_on_full_blast_password_str != "")
    {
    long password;
    sscanf (log_trace_on_full_blast_password_str.char_ptr (),
        "%x", &password);
    vdate* curr_date_ptr = vdateCreate ();
    vdateSetCurrent (curr_date_ptr);
    vdateConvertToLocal (curr_date_ptr);
    long computed_password
        = (vdateGetDay (curr_date_ptr)
        * (vdateGetMonth (curr_date_ptr) + vdateGetYear (curr_date_ptr)))
        / (vdateGetDayOfWeek (curr_date_ptr) + 17)
        * ((vdateGetDayOfYear (curr_date_ptr) + 13) / 7)
        & 0xffff;
    vdateDestroy (curr_date_ptr);
    if (password != computed_password)
    {
        std::string  msg("Invalid support properties password entered!\n");
        throw std::runtime_error(msg);
    }
    L_log_trace::set_all_flags_full_blast ();
    fprintf (stderr, "Valid support properties password entered.\n");
    fprintf (stderr, "Trace set to Full Blast.\n");
    }

    if (num_populations < 0)
    {
    std::string msg("\nERROR:  Negative number not allowed for -# option.\n\n");
    throw std::runtime_error(msg);
    }

#ifdef WIN32
  for ( unsigned int i = 0; i < gen_file_name_str.length(); ++i )
  {
    if ( gen_file_name_str[i] == '/' )
    {
      gen_file_name_str[i] = '\\';
    }
  }
#endif

    // i3193, i3196 deleted
    GS_string log_file_name_str;
    if (use_log_file)
    {
    GS_string db_base_name_str = gen_file_name_str;
    db_base_name_str [db_base_name_str.length () - 4] = '\0';
    db_base_name_str.recalc_length ();
    log_file_name_str = db_base_name_str + ".gen_log";
    }

    if (log_volume_str == "STMT") {
    GS_ui::init (log_file_name_str, UI_INFORM__STMT);
    } else if (log_volume_str == "COMP") {
    GS_ui::init (log_file_name_str, UI_INFORM__COMP);
    } else {
    GS_ui::init (log_file_name_str, UI_INFORM__SYS);
    }
}

/**
 * Perform generator initialization.  Note that that paramters passed to this
 * routine are only required because of Galaxy initialization.
 */
void initGenerator(int argc, char** argv)
{
    //  Call the clock command for the first time to get it running - subsequent
    //    calls to clock () will return the amount of CPU time used since the
    //    first call to clock (which is assumed to be this call to clock ()).
    //
    (void) clock ();

    //  Initialize Galaxy...
    //
    vstartupMinimal (argc, argv);
    vformatStartup();

    Description running = " running ...";
    L_log::log_common (process_name_char_ptr, running.char_ptr());

  MCDBMSInit::start_initialization(process_name_char_ptr);

  keyword_init();

    //  Initialize the trace by clearing all trace flags.
    //
    L_log_trace::clear_all_flags ();
}

/**
 * Report the amount of time that has elapsed since the last time this function
 * was called.  The timer is initially started at the beginning of main().
 */
void reportTime(const std::string& msg)
{
#ifdef _DEBUG
  time(&g_end);
  double diff = difftime(g_end, g_start);
  long minutes = diff / 60;
  long seconds = (long)diff % 60;
  std::cerr     << "TIMER: " << msg << " "
        << minutes << " minutes  "
        << seconds << " seconds." << std::endl;
  time(&g_start);
#endif
}

/**
 * Given the name of the application as specified on the command-line strip-out
 * any leading path and trailing suffix and return the result in lowercase.
 */
string getAppName(const string& cmdLineName)
{
  int begin = 0;
  int endOfPath1 = cmdLineName.find_last_of("\\");
  int endOfPath2 = cmdLineName.find_last_of("/");
  if (endOfPath1 != endOfPath2) {
    begin = (endOfPath1 > endOfPath2) ? endOfPath1 : endOfPath2;
    begin++; // skip the slash
  }

  string result = cmdLineName.substr(begin);
  for (int i = 0; i < result.size(); ++i) {
    result[i] = tolower(result[i]);
  }

  // If ".exe" if present strip-it
  result = result.substr(0, result.rfind(".exe"));

  return result;
}
