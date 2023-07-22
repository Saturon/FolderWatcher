#include <iostream>
#include <string>
#include <Poco/Delegate.h>
#include <Poco/DirectoryWatcher.h>
#include <Poco/DateTime.h>
#include <csignal>

Poco::DateTime* timevar;
Poco::DirectoryWatcher* watcher;

void onItemAdded(const Poco::DirectoryWatcher::DirectoryEvent& event)
{
	timevar = new Poco::DateTime();
	std::cout << "[" << timevar->year() << timevar->month() << timevar->day() << " " << timevar->hour() << ":" << timevar->minute() << ":" << timevar->second() << "]"
		<< " Added: " + event.item.path() << std::endl;
}

void onItemModified(const Poco::DirectoryWatcher::DirectoryEvent& event)
{
	timevar = new Poco::DateTime();
	std::cout << "[" << timevar->year() << timevar->month() << timevar->day() << " " << timevar->hour() << ":" << timevar->minute() << ":" << timevar->second() << "]"
		<< " Modified: " + event.item.path() << std::endl;
}

void onItemMovedFrom(const Poco::DirectoryWatcher::DirectoryEvent& event)
{
	timevar = new Poco::DateTime();
	std::cout << "[" << timevar->year() << timevar->month() << timevar->day() << " " << timevar->hour() << ":" << timevar->minute() << ":" << timevar->second() << "]"
		<< " MovedFrom: " + event.item.path() << std::endl;
}

void onItemMovetimevaro(const Poco::DirectoryWatcher::DirectoryEvent& event)
{
	timevar = new Poco::DateTime();
	std::cout << "[" << timevar->year() << timevar->month() << timevar->day() << " " << timevar->hour() << ":" << timevar->minute() << ":" << timevar->second() << "]"
		<< " Movetimevaro: " + event.item.path() << std::endl;
}

void onItemRemoved(const Poco::DirectoryWatcher::DirectoryEvent& event)
{
	timevar = new Poco::DateTime();
	std::cout << "[" << timevar->year() << timevar->month() << timevar->day() << " " << timevar->hour() << ":" << timevar->minute() << ":" << timevar->second() << "]"
		<< " Removed: " + event.item.path() << std::endl;
}

void watch(std::string path, int eventMask /*= Poco::DirectoryWatcher::DW_FILTER_ENABLE_ALL*/, int scanInterval /*= Poco::DirectoryWatcher::DW_DEFAULT_SCAN_INTERVAL*/)
{
	//std::unique_ptr<Poco::DirectoryWatcher> watcher = std::unique_ptr<Poco::DirectoryWatcher>(new Poco::DirectoryWatcher(path, eventMask, scanInterval));
	watcher = new Poco::DirectoryWatcher(path, eventMask, scanInterval);
	watcher->itemAdded += Poco::delegate(&onItemAdded);
	watcher->itemModified += Poco::delegate(&onItemModified);
	watcher->itemMovedFrom += Poco::delegate(&onItemMovedFrom);
	watcher->itemMovedTo += Poco::delegate(&onItemMovetimevaro);
	watcher->itemRemoved += Poco::delegate(&onItemRemoved);
}

void signalHandler(int signum) {
	std::cout << "Interrupt signal (" << signum << ") received.\n";

	if (signum == 6) {
		delete watcher;
	}

	exit(signum);
}

int main(int argc, char* argv[])
{
	std::cout << "Folder Watcher\n";
	
	if (argc < 2) {
		std::cout << "Please add a directory as a command line parameter\n";
		return 0;
	}

	if (argc > 2) {
		std::cout << "Too many command line parameters\n";
		return 0;
	}
	
	if (argc == 2) {
		std::string str(argv[1]);
		std::cout << "Watching directory: " << str << std::endl;
		watch(str, Poco::DirectoryWatcher::DW_FILTER_ENABLE_ALL, Poco::DirectoryWatcher::DW_DEFAULT_SCAN_INTERVAL);

		while (true)
		{
			std::cout << "Waiting for event...\n";
			Sleep(50000);

		}
	}
	/*watch("D:/Games", Poco::DirectoryWatcher::DW_FILTER_ENABLE_ALL, Poco::DirectoryWatcher::DW_DEFAULT_SCAN_INTERVAL);
	while (true)
	{
		std::cout << "Waiting for event...\n";
		Sleep(10000);
	}*/

	return 0;

}
