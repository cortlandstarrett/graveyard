// def_exc.cpp:  Illustrates how to use the DEFINE_EXCEPTION
// macro to define your own TIX exceptions. This program defines
// TIX exceptions to handle command-line argument errors. The
// program signals err_too_few_args if there are no arguments
// present, err_too_many_args if there are more than one,
// and err_bad_arg if the word "bad" is used as an argument.
// Only err_too_few_args is handled.
#include <ostore/ostore.hh>
#include <string.h>
#include <fstream.h>

DEFINE_EXCEPTION(err_too_few_args, "Too few arguments", 0);
DEFINE_EXCEPTION(err_too_many_args, "Too many arguments", 0);
DEFINE_EXCEPTION(err_bad_arg, "Illegal argument: ", 0);

void validate_args(int argc, char **argv);

int
main(int argc, char **argv)
{
	OS_ESTABLISH_FAULT_HANDLER {
		objectstore::initialize();
		TIX_HANDLE (err_too_few_args) {
			validate_args(argc, argv);
		} TIX_EXCEPTION {
			tix_exception *exception = tix_handler::get_exception();
			if (exception == &err_too_few_args)
				cout << "Missing command-line arguments.\n"; 
			else
				cout << "Unknown exception occurred.\n";	
		} TIX_END_HANDLE
		objectstore::shutdown();
	} OS_END_FAULT_HANDLER

        return 0;
}

void validate_args(int argc, char **argv)
{
	if (argc == 1)  // no arguments
		// No message is specified because the default message 
		// specified in the DEFINE_EXCEPTION macro is sufficient. 
		err_too_few_args.signal("");
	else if (argc > 2) // more than one argument
		// No message is specified, so only the default message
		// specified with the DEFINE_EXCEPTION macro will
		// be displayed.
		err_too_many_args.signal("");
	else if (argc == 2 && !strcmp(argv[1], "bad"))
		// This call to signal includes a message,
		// which will therefore be displayed along with the
		// default message specified with the DEFINE_EXCEPTION
		// macro.
		err_bad_arg.signal(argv[1]);
}

