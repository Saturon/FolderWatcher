#include <iostream>
#include <string>
#include <Poco/Delegate.h>
#include <Poco/DirectoryWatcher.h>
#include <Poco/LocalDateTime.h>
#include <csignal>

Poco::LocalDateTime* timevar;
Poco::DirectoryWatcher* watcher;

void onItemAddedF(const Poco::DirectoryWatcher::DirectoryEvent& event)
{
	timevar = new Poco::LocalDateTime();
	std::cout << "[" << timevar->day() << ":" << timevar->month() << ":" << timevar->year() << " " << timevar->hour() << ":" << timevar->minute() << ":" << timevar->second() << "]"
		<< " Added: " + event.item.path() << std::endl;
}

void onItemModifiedF(const Poco::DirectoryWatcher::DirectoryEvent& event)
{
	timevar = new Poco::LocalDateTime();
	std::cout << "[" << timevar->day() << ":" << timevar->month() << ":" << timevar->year() << " " << timevar->hour() << ":" << timevar->minute() << ":" << timevar->second() << "]"
		<< " Modified: " + event.item.path() << std::endl;
}

void onItemMovedFromF(const Poco::DirectoryWatcher::DirectoryEvent& event)
{
	timevar = new Poco::LocalDateTime();
	std::cout << "[" << timevar->day() << ":" << timevar->month() << ":" << timevar->year() << " " << timevar->hour() << ":" << timevar->minute() << ":" << timevar->second() << "]"
		<< " MovedFrom: " + event.item.path() << std::endl;
}

void onItemMovedToF(const Poco::DirectoryWatcher::DirectoryEvent& event)
{
	timevar = new Poco::LocalDateTime();
	std::cout << "[" << timevar->day() << ":" << timevar->month() << ":" << timevar->year() << " " << timevar->hour() << ":" << timevar->minute() << ":" << timevar->second() << "]"
		<< " Movetimevaro: " + event.item.path() << std::endl;
}

void onItemRemovedF(const Poco::DirectoryWatcher::DirectoryEvent& event)
{
	timevar = new Poco::LocalDateTime();
	std::cout << "[" << timevar->day() << ":" << timevar->month() << ":" << timevar->year() << " " << timevar->hour() << ":" << timevar->minute() << ":" << timevar->second() << "]"
		<< " Removed: " + event.item.path() << std::endl;
}

void watch(std::string path, int eventMask /*= Poco::DirectoryWatcher::DW_FILTER_ENABLE_ALL*/, int scanInterval /*= Poco::DirectoryWatcher::DW_DEFAULT_SCAN_INTERVAL*/)
{
	//std::unique_ptr<Poco::DirectoryWatcher> watcher = std::unique_ptr<Poco::DirectoryWatcher>(new Poco::DirectoryWatcher(path, eventMask, scanInterval));
	watcher = new Poco::DirectoryWatcher(path, eventMask, scanInterval);
	watcher->itemAdded += Poco::delegate(&onItemAddedF);
	watcher->itemModified += Poco::delegate(&onItemModifiedF);
	watcher->itemMovedFrom += Poco::delegate(&onItemMovedFromF);
	watcher->itemMovedTo += Poco::delegate(&onItemMovedToF);
	watcher->itemRemoved += Poco::delegate(&onItemRemovedF);
}

void signalHandler(int signum) {
	std::cout << "Interrupt signal (" << signum << ") received.\n";

	if (signum == 6) or (signum == 2) {
		delete watcher;
	}

	exit(signum);
}

int main(int argc, char* argv[])
{
	std::cout << "Folder Watcher\n";
	signal(SIGINT, signalHandler);
	
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
	/*
	watch("D:/Games", Poco::DirectoryWatcher::DW_FILTER_ENABLE_ALL, Poco::DirectoryWatcher::DW_DEFAULT_SCAN_INTERVAL);
	while (true)
	{
		std::cout << "Waiting for event...\n";
		Sleep(10000);
	}*/

	return 0;

}
