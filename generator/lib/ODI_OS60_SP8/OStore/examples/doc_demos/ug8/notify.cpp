// notify.cpp: Illustrates sending and receiving ObjectStore
// notifications.  This example is intended to be run in two
// processes. Start the sender process by running the notify
// executable with no command-line arguments.  Start the receiver
// by running the same executable with any command-line argument.
// Run the receiver first, then the sender.
 
#include <ostore/ostore.hh>
#include <iostream.h>
#include <assert.h>

#include <sys/timeb.h>
 
class timer {
public:
	static double now() {
		struct _timeb timeStruct;
		_ftime(&timeStruct);
		double result = (double)1000000 * timeStruct.time +
			(timeStruct.millitm * 1000);
		return result;
	}
};
 

 
int main(int argc, char** argv)
{
	const char* db_name = "notif.db";
	const char* root_name = "Test Object";
 
	OS_ESTABLISH_FAULT_HANDLER {
		// can see client name with "ossvrstat -clients <host>"
		objectstore::set_client_name(argv[0]);
 
		objectstore::initialize();
 
		cout << "Opening database " << db_name << endl;
		os_database* db = os_database::open(db_name,0,0644);
 
		os_soft_pointer<void> location1 = 0;
		os_soft_pointer<void> location2 = 0;
 
		OS_BEGIN_TXN(t1,0,os_transaction::update) {
			os_database_root* root = db->find_root(root_name);
			if (!root) {
				cout << "Creating a couple of ints" << endl;
				root = db->create_root(root_name);
				root->set_value(new (db, os_typespec::get_int(), 2) int[2]);
			}
 
			location1 = root->get_value(); // &int[0]
			location2 = &((int*)location1.resolve())[1]; // &int[1]
		} OS_END_TXN(t1)
 
		os_notification* note;
		int iterations = 0;
 
		OS_BEGIN_TXN(t2,0,os_transaction::read_only) {
			// the sender process takes no command-line args
			if ( argc == 1) {
				cout << "Sender Starting notifications..." << endl;
				os_notification::subscribe(location2); // subscribe to location2;
				double begin = timer::now();
 
				while (iterations < 50) {
					iterations++;
 
					// send immediate notification on location1 with
					// iterations as kind
					os_notification::notify_immediate(location1,iterations);
 
					// now get response in note
					os_notification::receive(note);
 
					// make sure note response is on location2
					os_soft_pointer<void> location = note->get_location();
					assert(location == location2);
 
					// make sure correct iterations comes back
					int kind = note->get_kind();
					assert(kind == iterations);
 
					delete note; // avoid memory leak
				}
 
				double end = timer::now();
 
				// Tell receiver to exit by sending notification on location1
				// with kind=0
				os_notification::notify_immediate(location1,0);
 
				cout << "We performed " << 2*iterations
					<< " notifications in " << (end-begin)/1000000
					<< " seconds.\n";
 
				// sender done
			}
			else { // receiver process takes any args on command line
				cout << "Receiver Waiting for Notifications" << endl;
 
				os_notification::subscribe(location1); // subscribe to location1
 
				while(1) {
					// receive notification for location1 into note
					os_notification::receive(note);
 
					int kind = note->get_kind(); // see what kind it is
 
					if (kind == 0) // if kind is 0, exit
						break; // receiver done
 
					// make sure notification is about location1
					os_soft_pointer<void> location = note->get_location();
					assert(location == location1);
					delete note; // avoid memory leak
 
					// send notification on location2 with kind
					os_notification::notify_immediate(location2,kind);
				}
			}
		} OS_END_TXN(t2)
		objectstore::shutdown();
 
	} OS_END_FAULT_HANDLER
	return 0;
}
 

