#include "MainFunctions.h"
#include<ctime>
#include<time.h>

int Event::num_events(0);
using namespace std;
int main() {

	bool exit_flag{ 0 };
	bool loaded{ 0 };
	// Create vectors of each type of event
	std::vector<std::shared_ptr<Event>> events;
	std::unordered_map<int, std::shared_ptr<Event>> event_map;
	std::string do_load;
	std::cout << std::endl << "Welcome to the Car owner calendar!" << std::endl;
	// Give user option to load from a text file
	while (do_load != "y" && do_load != "n"){
		std::cout << std::endl << "Do you want to load a previously saved calendar? (y/n): ";
		std::cin >> do_load;
		cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	std::string file_name;
	if (do_load == "y"){
		// Ask user for a file name
		do {
			std::cout << std::endl << "Enter the name of the load file: ";
			std::cin >> file_name;
			cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
		} while (cin.fail());
		// Check if file exists
		ifstream load_file(file_name.c_str());
		if (!load_file.good()){
			load_file.close();
			cout << "WARNING: The file " << file_name << " does not exist" << endl;
		}
		else{
			load_file.close();
			// Load in all events and fill vectors of each type of event -- use function
			std::vector<std::shared_ptr<Event>> events = mainfunc::loadEvents(file_name, events);
			loaded = 1;
		}
	}
	// Everything done within exit while loop
	while (!exit_flag){
		// Give user options of what to do next (have a help command to display all the options)
		std::string option;
		while (!noCaseCompare(option, "help") && 
		!noCaseCompare(option, "new") && 
		!noCaseCompare(option, "search") && 
		!noCaseCompare(option, "exit")){
			std::cout << std::endl << "What do you want to do? (Type help for options): ";
			std::cin >> option;
			cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		// Display help to user
		if (noCaseCompare(option, "help")){
			std::cout << std::endl << "The available options are:" << std::endl
				<< "help = Display available options" << std::endl
				<< "new = Create a new event" << std::endl
				<< "search = Search chosen events for any string, integer, float or date (can also search files)" << std::endl
				<< "exit = Exit the calendar" << std::endl;
		}
		// Create new events -- use function
		else if (noCaseCompare(option, "new")){
			// Ask user which type of event they want to create
			// Pass type and relevant vector to function
			event_map = mainfunc::createNewEvent(event_map);
		}
		// Edit existing events -- use function
		else if (noCaseCompare(option, "edit")){
			// Print all events with their ID type and name
			std::cout << std::endl << "Events: " << std::endl;
			for (auto evt : event_map){
				std::cout << "ID(" << evt.second->getId() << ") " << evt.second->getType()
					<< " (" << evt.second->getName() << ")" << std::endl;
			}
			// Ask user for the ID of the event they want to edit
			int edit_id;
			do {
				if (cin.fail()){
					cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
				}
				std::cout << std::endl << "Which event would you like to edit? (Give ID): "; std::cin >> edit_id;
			} while (cin.fail());
			// Pass ID and relevant vector to function
			if (event_map.find(edit_id) == event_map.end()){
				std::cout << "WARNING: ID not available" << std::endl;
			}
			else {
				// Ask user if they want to edit or delete the event
				std::string edit_or_delete;
				while (edit_or_delete != "e"&&edit_or_delete != "d"){
					std::cout << std::endl << "Do you want to edit (e) or delete (d) this event?: ";
					std::cin >> edit_or_delete;
					cin.clear();  cin.ignore(numeric_limits<streamsize>::max(), '\n');
				}

				if (edit_or_delete == "d"){
					event_map.erase(edit_id);
				}
			}
		}

		// Search the events -- use function
		else if (noCaseCompare(option, "search")){
			// Pass map to search function
			mainfunc::searchEvents(event_map);
		}

		// Exit the organiser
		else if (noCaseCompare(option, "exit")){
			std::string confirm;
			while (confirm != "y"&&confirm != "n"){
				std::cout << std::endl << "Are you sure you want to exit? (y/n): ";
				std::cin >> confirm;
				cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			if (confirm == "y") exit_flag = 1;
		}
		else { std::cout << "WARNING: Error in option choice" << std::endl; }
	}
	// When exit loop breaks, give option to save the system to a text file -- use function
	std::string save_state;
	while (save_state != "y"&&save_state != "n"){
		std::cout << std::endl << "Do you want to save any changes you have made? (y/n): ";
		std::cin >> save_state;
		cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	if (save_state == "y"){
		// If the current calendar was loaded overwrite the file with the new list of events
		if (loaded){
			mainfunc::saveState(file_name, event_map);
		}
		// If not create a new file to save to
		else mainfunc::saveState("none", event_map);
		std::cout << std::endl << "Goodbye!" << std::endl;
	}
	else std::cout << std::endl << "Goodbye!" << std::endl;

	return 0;
}
