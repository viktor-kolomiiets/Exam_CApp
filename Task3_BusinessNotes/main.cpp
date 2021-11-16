/*Создайте приложение «Список дел». Приложение должно позволять:
1. Добавление дел. У дела есть:
  - название;
  - приоритет;
  - описание;
  - дата, время исполнения.
2. Удаление дел.
3. Редактирование дел.
4. Поиск дел по:
  - названию;
  - приоритету;
  - описанию;
  - дате и времени исполнения.
5. Отображение списка дел:
  - на день;
  - на неделю;
  - на месяц.
6. При отображении должна быть возможность сортировки:
  - по приоритету;
  - по дате и времени исполнения*/

#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include "subfunctions.h"
using namespace std;

const int SIZE = 100;
int lastNoteID = 0;

struct Date
{
	int minutes = 0;
	int hour = 0;
	int day = 0;
	int month = 0;
	int year = 0;

	void setDate()
	{
		cout << "\tDay      : ";
		day = inputNumRange(1, 31);
		cout << "\tMonth    : ";
		month = inputNumRange(1, 12);
		cout << "\tYear     : ";
		year = inputNumRange(1, 9999);
	}

	void setTime()
	{
		cout << "\tHour     : ";
		hour = inputNumRange(0, 24);
		cout << "\tMinutes  : ";
		minutes = inputNumRange(0, 59);
	}

	int getWeek()
	{
		return weekNo(year, month, day);
	}

	//convert date & time to union value
	long toValue()
	{
		long _value = year * 100000000 + month * 1000000 + day * 10000 + hour * 100 + minutes;
		return _value;
	}

	void removeDate()
	{
		minutes = 0;
		hour = 0;
		day = 0;
		month = 0;
		year = 0;
	}

	void print()
	{
		printf("%d.%d.%d, %d:%d", day, month, year, hour, minutes);
	}
};

struct Note
{
	string name = "";
	int priority = 0;
	string description = "";
	Date dateExec;

	void addNote()
	{
		system("cls");
		cout << "Enter note\'s name        : ";
		name = inputString();

		cout << "Enter note\'s priority    : ";
		priority = inputNum();

		cout << "Enter description        : ";
		description = inputString();

		cout << "Enter data&time execution:\n";
		dateExec.setDate();
		dateExec.setTime();
	}

	void removeNote()
	{
		name = "";
		priority = 0;
		description = "";
		dateExec.removeDate();
	}
};

bool compareDates(Date date1, Date date2)
{
	if (date1.year == date2.year)
		if (date1.month == date2.month)
			if (date1.day == date2.day)
				if (date1.hour == date2.hour)
					if (date1.minutes == date2.minutes)
						return true;
					else
						return false;
				else
					return false;
			else
				return false;
		else
			return false;
	else
		return false;
}

void setMinNotePrior(Note notes[], int start, int end)
{
	Note min = notes[start];

	for (int i = 1; i <= end; i++)
	{
		if (notes[i].priority < min.priority)
			min = notes[i];
	}

	notes[start] = min;
}

void sortByPriority(Note notes[], long size)
{
	Note note;
	long i, j;

	Note oldFirstNote = notes[0];

	setMinNotePrior(notes, 0, size - 1);

	for (i = 1; i < size; i++) {
		note = notes[i];
		for (j = i - 1; notes[j].priority > note.priority; j--)
			notes[j + 1] = notes[j];
		notes[j + 1] = note;
	}

	for (j = 1; j < size && notes[j].priority < oldFirstNote.priority; j++)
		notes[j - 1] = notes[j];

	notes[j - 1] = oldFirstNote;
}

void setMinNoteDate(Note notes[], int start, int end)
{
	Note min = notes[start];

	for (int i = 1; i <= end; i++)
	{
		if (notes[i].dateExec.toValue() < min.dateExec.toValue())
			min = notes[i];
	}

	notes[start] = min;
}

void sortByDate(Note notes[], long size)
{
	Note note;
	long i, j;

	Note oldFirstNote = notes[0];

	setMinNotePrior(notes, 0, size - 1);

	for (i = 1; i < size; i++) {
		note = notes[i];
		for (j = i - 1; notes[j].dateExec.toValue() > note.dateExec.toValue(); j--)
			notes[j + 1] = notes[j];
		notes[j + 1] = note;
	}

	for (j = 1; j < size && notes[j].dateExec.toValue() < oldFirstNote.dateExec.toValue(); j++)
		notes[j - 1] = notes[j];

	notes[j - 1] = oldFirstNote;
}

void printLine(Note note, int id)
{
	cout.width(4);
	cout << id << " \t| ";
	cout << note.name;
	if (note.name.size() < 6)
		cout << "\t";
	cout << "\t| " << note.priority << "\t|  ";
	note.dateExec.print();
	cout << "\t| ";
	cout << note.description << "\n";
}

void printTable(Note notes[], int size)
{
	system("cls");
	cout << string(105, '-') << "\n";
	cout.width(4);
	cout << "   No\t| " << "Name\t\t| " << "Prior.|  " << "Date & Time Exec.\t| " << "Description" << endl;
	cout << string(105, '-') << "\n";

	for (int i = 0; i < size; i++)
		printLine(notes[i], i + 1);

	cout << string(105, '-') << "\n";
}

void addBusiness(Note notes[])
{
	system("cls");
	if (lastNoteID + 1 < 100)
	{
		notes[lastNoteID].addNote();
		lastNoteID += 1;
	}
	else
		cout << "Out of memory\n";
}

void removeBusiness(Note notes[])
{
	printTable(notes, lastNoteID);
	if (lastNoteID > 0)
	{
		int id = 0;
		for (;;)
		{
			cout << "Enter business No: ";
			id = inputNum() - 1;
			if (id >= 0 && id < lastNoteID)
				break;
			else
			{
				cout << "Out of range\n";
				continue;
			}
		}

		system("cls");
		for (int i = id; i < lastNoteID; i++)
		{
			notes[i] = notes[i + 1];
		}
		notes[lastNoteID].removeNote();
		::lastNoteID--;
	}
	else
		for (;;)
		{
			cout << "0. Back\n>> ";
			string s = inputString();
			if (s.size() >= 0)
				break;
		}
}

void editBusiness(Note notes[])
{
	printTable(notes, lastNoteID);
	if (lastNoteID > 0)
	{
		int id = 0;

		for (;;)
		{
			cout << "Enter business No: ";
			id = inputNum() - 1;
			if (id >= 0 && id < lastNoteID)
				break;
			else
			{
				cout << "Out of range\n";
				continue;
			}
		}

		system("cls");
		cout << "Enter new data:\n";
		notes[id].addNote();
	}
	else
		for (;;)
		{
			cout << "0. Back\n>> ";
			string s = inputString();
			if (s.size() >= 0)
				break;
		}
}

void showBisinesses(Note notes[])
{
	string subMenu = "";
	void(*sortF[2])(Note*, long) { sortByPriority, sortByDate };

	for (;;)
	{
		system("cls");
		cout << "Display to-do list for:\n";
		cout << "1. Day\n2. Week\n3. Month\n4. All list\n0. Back\n>> ";
		subMenu = inputString();

		if (subMenu == "0")
			break;
		else if (subMenu == "1")
		{
			Date date;
			int sub = 0;
			
			system("cls");
			for (;;)
			{
				int outputSize = 0;
				Note* output;
				
				cout << "Enter day date:\n";
				date.setDate();

				for (int i = 0; i < lastNoteID; i++)
					if (notes[i].dateExec.day == date.day && notes[i].dateExec.month == date.month && notes[i].dateExec.year == date.year)
						outputSize++;

				if (outputSize == 0)
					cout << "There is no entry for this day\n";
				else
				{
					output = new Note[outputSize];
					int j = 0;
					for (int i = 0; i < lastNoteID; i++)
						if (notes[i].dateExec.day == date.day && notes[i].dateExec.month == date.month && notes[i].dateExec.year == date.year)
						{
							output[j] = notes[i];
							j++;
						}

					cout << "Sort by:\n1. Priority\n2. Date & Time Exec.\n>> ";
					int sort = inputNumRange(1, 2);
					sortF[sort - 1](output, outputSize);
					printTable(output, outputSize);

					if (output)
					{
						delete[] output;
						output = nullptr;
					}
				}

				cout << "0. Back\n>> ";
				sub = inputNum() + 1;
				if (sub)
					break;
			}
		}
		else if (subMenu == "2")
		{
			int sub = 0, year = 0;

			system("cls");
			for (;;)
			{
				int week = 0;
				int outputSize = 0;
				Note* output;

				cout << "Enter year: ";
				year = inputNumRange(1, 9999);
				cout << "Enter week No (1 - 55): ";
				week = inputNumRange(1, 55);

				for (int i = 0; i < lastNoteID; i++)
					if (notes[i].dateExec.year == year && notes[i].dateExec.getWeek() == week)
						outputSize++;

				if (outputSize == 0)
					cout << "There is no entry for this week\n";
				else
				{
					output = new Note[outputSize];
					int j = 0;
					for (int i = 0; i < lastNoteID; i++)
						if (notes[i].dateExec.year == year && notes[i].dateExec.getWeek() == week)
						{
							output[j] = notes[i];
							j++;
						}

					cout << "Sort by:\n1. Priority\n2. Date & Time Exec.\n>> ";
					int sort = inputNumRange(1, 2);
					sortF[sort - 1](output, outputSize);
					printTable(output, outputSize);

					if (output)
					{
						delete[] output;
						output = nullptr;
					}
				}

				cout << "0. Back\n>> ";
				sub = inputNum() + 1;
				if (sub)
					break;
			}
		}
		else if (subMenu == "3")
		{
			int sub = 0, month = 0, year = 0;

			system("cls");
			for (;;)
			{
				int outputSize = 0;
				Note* output;

				cout << "Enter month: ";
				month = inputNumRange(1, 12);
				cout << "Enter year: ";
				year = inputNumRange(1, 9999);

				for (int i = 0; i < lastNoteID; i++)
					if (notes[i].dateExec.month == month && notes[i].dateExec.year == year)
						outputSize++;

				if (outputSize == 0)
					cout << "There is no entry for this month\n";
				else
				{
					output = new Note[outputSize];
					int j = 0;
					for (int i = 0; i < lastNoteID; i++)
						if (notes[i].dateExec.month == month && notes[i].dateExec.year == year)
						{
							output[j] = notes[i];
							j++;
						}
					
					cout << "Sort by:\n1. Priority\n2. Date & Time Exec.\n>> ";
					int sort = inputNumRange(1, 2);
					sortF[sort - 1](output, outputSize);
					printTable(output, outputSize);

					if (output)
					{
						delete[] output;
						output = nullptr;
					}
				}

				cout << "0. Back\n>> ";
				sub = inputNum() + 1;
				if (sub)
					break;
			}
		}
		else if (subMenu == "4")
		{
			cout << "Sort by:\n1. Priority\n2. Date & Time Exec.\n>> ";
			int sort = inputNumRange(1, 2);
			sortF[sort - 1](notes, lastNoteID);

			for (;;)
			{
				printTable(notes, lastNoteID);
				cout << "0. Back\n>> ";
				string s = inputString();
				if (s == "0")
					break;
			}
		}
		else
			continue;
	}
}

void searchBusiness(Note notes[])
{
	int subMenu = 0;
	for (;;)
	{
		system("cls");
		cout << "Search to-do note by:\n1. Name\n2. Priority\n3. Description\n4. Date & Time execution\n0. Back\n>> ";
		subMenu = inputNum();

		if (subMenu == 0)
			break;
		else if (subMenu == 1)
		{
			system("cls");
			cout << "Enter searching name: ";
			string key = inputString();

			Note* output;
			int outputSize = 0;
			for (int i = 0; i < lastNoteID; i++)
				if (notes[i].name == key)
					outputSize++;
			if (outputSize > 0)
			{
				int j = 0;
				output = new Note[outputSize];
				for (int i = 0; i < lastNoteID; i++)
					if (notes[i].name == key)
					{
						output[j] = notes[i];
						j++;
					}
				for (;;)
				{
					printTable(output, outputSize);
					cout << "0. Back\n>> ";
					string s = inputString();
					if (s == "0")
						break;
				}
			}
			else
				noSearches();
		}
		else if (subMenu == 2)
		{
			system("cls");
			cout << "Enter business priority: ";
			int key = inputNum();

			Note* output;
			int outputSize = 0;
			for (int i = 0; i < lastNoteID; i++)
				if (notes[i].priority == key)
					outputSize++;
			if (outputSize > 0)
			{
				int j = 0;
				output = new Note[outputSize];
				for (int i = 0; i < lastNoteID; i++)
					if (notes[i].priority == key)
					{
						output[j] = notes[i];
						j++;
					}
				for (;;)
				{
					printTable(output, outputSize);
					cout << "0. Back\n>> ";
					string s = inputString();
					if (s == "0")
						break;
				}
			}
			else
				noSearches();
		}
		else if (subMenu == 3)
		{
			system("cls");
			cout << "Enter key word: ";
			string key = inputString();

			Note* output;
			int outputSize = 0;
			for (int i = 0; i < lastNoteID; i++)
				if (notes[i].description.find(key) != string::npos)
					outputSize++;
			if (outputSize > 0)
			{
				int j = 0;
				output = new Note[outputSize];
				for (int i = 0; i < lastNoteID; i++)
					if (notes[i].description.find(key) != string::npos)
					{
						output[j] = notes[i];
						j++;
					}
				for (;;)
				{
					printTable(output, outputSize);
					cout << "0. Back\n>> ";
					string s = inputString();
					if (s == "0")
						break;
				}
			}
			else
				noSearches();
		}
		else if (subMenu == 4)
		{
			int sub = 0;
			for (;;)
			{
				system("cls");
				Date date;
				cout << "Enter date & time:\n";
				date.setDate();
				date.setTime();

				Note* output;
				int outputSize = 0;
				for (int i = 0; i < lastNoteID; i++)
					if (compareDates(notes[i].dateExec, date))
						outputSize++;
				if (outputSize > 0)
				{
					int j = 0;
					output = new Note[outputSize];
					for (int i = 0; i < lastNoteID; i++)
						if (compareDates(notes[i].dateExec, date))
						{
							output[j] = notes[i];
							j++;
						}
					for (;;)
					{
						printTable(output, outputSize);
						cout << "0. Back\n>> ";
						string s = inputString();
						if (s == "0")
							break;
					}
				}
				else
					noSearches();
			}
		}
		else
			continue;
	}
}

int main()
{
	Note notes[SIZE]{};
	int menuNum = 0;

	for (;;)
	{
		system("cls");
		cout << "1. Add to-do note\n2. Remove to-do note\n3. Edit to-do note\n";
		cout << "4. Search to-do note\n5. Print to-do list\n0. Exit\n>> ";
		menuNum = inputNumRange(0, 5);

		void (*menu[5])(Note notes[])
		{ 
			addBusiness,
			removeBusiness,
			editBusiness,
			searchBusiness,
			showBisinesses
		};

		if (menuNum == 0)
			break;
		else if (menuNum >= 1 && menuNum <= 5)
			menu[menuNum - 1](notes);
		else
			continue;
	}

	return 0;
}
