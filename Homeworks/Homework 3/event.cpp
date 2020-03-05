#include <iostream>
#include <string>

using namespace std;

class Event {
public:
	Event(string pname) {
		eName = pname;
	}
	
	string name() const {
		return eName;
	}
	virtual bool isSport() const = 0;
	virtual string need() const = 0;
	virtual ~Event() {
		
	}
private:
	string eName;
};

class BasketballGame : public Event {
public:

	BasketballGame(string pname) : Event(pname) {

	}
	virtual bool isSport() const {
		return true;
	}
	virtual string need() const {
		return "hoops";
	}
	virtual ~BasketballGame() {
		cout << "Destroying the " << name() << " basketball game" << endl;
	}

};

class Concert : public Event {
public:

	Concert(string band, string genre) : Event(band), m_genre(genre) {

	}
	virtual bool isSport() const{
		return false;
	}
	virtual string need() const {
		return "a stage";
	}
	virtual ~Concert() {
		cout << "Destroying the " << name() << " " << m_genre << " concert" << endl;
	}

private:
	string m_genre;
};

class HockeyGame : public Event {
public: 

	HockeyGame(string hTeams) : Event(hTeams) {

	}
	virtual bool isSport() const {
		return true;
	}
	virtual string need() const {
		return "ice";
	}
	virtual ~HockeyGame() {
		cout << "Destroying the " << name() << " hockey game" << endl;
	}
};

void display(const Event* e)
{
	cout << e->name() << ": ";
	if (e->isSport())
		cout << "(sport) ";
	cout << "needs " << e->need() << endl;
}

int main()
{
	Event* events[4];
	events[0] = new BasketballGame("Lakers vs. Suns");
	// Concerts have a name and a genre.
	events[1] = new Concert("Banda MS", "banda");
	events[2] = new Concert("KISS", "hard rock");
	events[3] = new HockeyGame("Kings vs. Flames");

	cout << "Here are the events." << endl;
	for (int k = 0; k < 4; k++)
		display(events[k]);

	// Clean up the events before exiting
	cout << "Cleaning up." << endl;
	for (int k = 0; k < 4; k++)
		delete events[k];
}