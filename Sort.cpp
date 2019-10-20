#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <sstream>
#include <time.h>
#include <iomanip>
using namespace std;

class times
{
public:
	double ReadTime_used() const  {
		return time_used;
	}
	vector<int> ReadFromAfter() const {
		return after;
	}
	vector<int> ReadFromBefore() const {
		return before;
	}
	void WriteToBefore(const vector<int>& buf) {
		before = buf;
	}
	void WriteToAfter(const vector<int>& buf) {
		after = buf;
	}
	void WriteTime_used(const double& buf) {
		time_used = buf;
	}
	void WriteToFile() {
		size_t size;
		if (before.size() > 20) {
			size = 20;
		}
		else size = before.size();
		ofstream out(out_file, ios::app);
		out << setw(50) << endl 
			<< sort_type + ": " << endl;
		out << setw(49) << endl
			<< "Actual size: " << after.size() << endl;

		out << endl << endl << "Before:" << endl;
		for (size_t i = 0; i < size; ++i) {
			out << before[i] << " ";
		}
		out << endl << endl <<	"After:" << endl;
		for (size_t i = 0; i < size; ++i) {
			out << after[i] << " ";
		}
		out << endl << endl << "Time used: " << time_used << " Sec."<< endl;
	}
	void WriteWhereToWriteFile(const string& name) {
		out_file = name;
	}
	void WriteSortType(const string& name) {
		sort_type = name;
	}
private:
	string sort_type;
	string out_file;
	vector<int> before;
	vector<int> after;
	double time_used;
};
class Algorithms {

public:
	times SortPuz(vector<int>& number,const string& to_file) {
		times t;

		t.WriteToBefore(number);
		clock_t time;
		time = clock();

		for (size_t i = 0; i < number.size(); ++i) {
			for (size_t j = 0; j < number.size() - i - 1; ++j) {
				if (number[j] > number[j + 1]) {
					swap(number[j], number[j + 1]);
				}
			}
		}

		time = clock() - time;
		t.WriteTime_used(time / CLOCKS_PER_SEC);
		t.WriteToAfter(number);
		t.WriteWhereToWriteFile(to_file);
		return t;
	}
	times SortSl(vector<int>& number, const string& to_file) {
		times z;
		z.WriteToBefore(number);
		clock_t time;
		time = clock();
		sort(number, 0, number.size());
		time = clock() - time;
		z.WriteTime_used( time / CLOCKS_PER_SEC);
		z.WriteToAfter(number);
		z.WriteWhereToWriteFile(to_file);
		return z;
	}
	times SortInsert(vector<int>& number, const string& to_file) {
		times z;
		z.WriteToBefore(number);
		clock_t time;
		time = clock();

		for (int i = 1; i < number.size(); i++)
		{
			int key = number[i];
			int j = i - 1;
			while (j >= 0 && number[j] > key)
			{
				number[j + 1] = number[j];
				j = j - 1;
			}
			number[j + 1] = key;
		}

		time = clock() - time;
		z.WriteTime_used(time / CLOCKS_PER_SEC);
		z.WriteToAfter(number);
		z.WriteWhereToWriteFile(to_file);
		return z;
	}
	times SortShell(vector<int>& number, const string& to_file) {
		size_t j;
		times z;
		z.WriteToBefore(number);
		clock_t time;
		time = clock();

		for (size_t step = number.size() / 2; step > 0; step /= 2) {

			for (size_t i = step; i < number.size(); ++i) {
				int buf = number[i];
				for (j = i; j >= step; j -= step) {
					if (buf < number[j - step]) {
						number[j] = number[j - step];
					}
					else {
						break;
					}
				}
				number[j] = buf;
			}
		}

		time = clock() - time;
		z.WriteTime_used(time / CLOCKS_PER_SEC);
		z.WriteToAfter(number);
		z.WriteWhereToWriteFile(to_file);
		return z;
	}
	times SortSelection(vector<int>& number, const string& to_file) {
		times z;
		z.WriteToBefore(number);
		clock_t time;
		time = clock();
	
		for (size_t i = 0; i < number.size() - 1; i++)
		{
			int count = number[i]; 
			int key = i;
			for (size_t j = i + 1; j < number.size(); j++)
				if (number[j] < number[key]) key = j;
			if (key != i)
			{
				number[i] = number[key];
				number[key] = count;
			}
		}

		time = clock() - time;
		z.WriteTime_used(time / CLOCKS_PER_SEC);
		z.WriteToAfter(number);
		z.WriteWhereToWriteFile(to_file);
		return z;
	}
	times SortHeap(vector<int>& number, const string& to_file) {
		times z;
		z.WriteToBefore(number);
		clock_t time;
		time = clock();

		for (int i = (number.size() / 2) - 1; i >= 0; i--)
			siftDown(number, i, number.size() - 1);
		for (int i = number.size() - 1; i >= 1; i--)
		{
			int temp = number[0];
			number[0] = number[i];
			number[i] = temp;
			siftDown(number,0, i - 1);
		}

		time = clock() - time;
		z.WriteTime_used(time / CLOCKS_PER_SEC);
		z.WriteToAfter(number);
		z.WriteWhereToWriteFile(to_file);
		return z;
	}
	times SortQuick(vector<int>& number, const string& to_file) {
		times z;
		z.WriteToBefore(number);
		clock_t time;
		time = clock();

		Quick(number, number.size());

		time = clock() - time;
		z.WriteTime_used(time / CLOCKS_PER_SEC);
		z.WriteToAfter(number);
		z.WriteWhereToWriteFile(to_file);
		return z;
	}
	times SortPatience(vector<int>& number, const string& to_file) {
		times z;
		z.WriteToBefore(number);
		clock_t time;
		time = clock();

		vector<vector<int>> piles;

		for (int insertPos = 0; insertPos < number.size(); insertPos++)
		{
			int middle, left = 0, right = piles.size() - 1;
			while (left <= right)
			{
				middle = (left + right) / 2;
				number.at(insertPos) > piles.at(middle).back() ? left = middle + 1 : right = middle - 1;
			}
			if (left >= piles.size())
				piles.resize(piles.size() + 1);
			piles.at(left).push_back(number.at(insertPos));
		}

		for (int insertPos = 0; insertPos < number.size(); insertPos++)
		{
			number.at(insertPos) = piles.front().back();
			piles.front().pop_back();

			if (piles.front().empty())
			{
				swap(piles.front(), piles.back());
				piles.resize(piles.size() - 1);
			}

			int root = 0, minChild = 0;

			while (root < piles.size())
			{
				int child1 = root * 2 + 1, child2 = root * 2 + 2;

				if (child1 < piles.size() && piles.at(child1).back() < piles.at(minChild).back())
					minChild = child1;
				if (child2 < piles.size() && piles.at(child2).back() < piles.at(minChild).back())
					minChild = child2;
				if (minChild != root)
				{
					swap(piles.at(minChild), piles.at(root));
					root = minChild;
				}
				else break;
			}
		}

		time = clock() - time;
		z.WriteTime_used(time / CLOCKS_PER_SEC);
		z.WriteToAfter(number);
		z.WriteWhereToWriteFile(to_file);
		return z;
	}
private:
		void sort(vector<int>& number, size_t start, size_t end) {
			if (end - start < 2) {
				return;
			}
			if (end - start == 2) {
				if (number[start] > number[start + 1]) {
					swap(number[start], number[start + 1]);
					return;
				}
			}

			sort(number, start, start + (end - start) / 2);
			sort(number, start + (end - start) / 2, end);
			vector<int> b;
			size_t b1 = start;
			size_t e1 = start + (end - start) / 2;
			size_t b2 = e1;
			while (b.size() < end - start) {

				if (b1 >= e1 || (b2 < end) && (number[b2] <= number[b1])) {
					b.push_back(number[b2]);
					++b2;
				}
				else {
					b.push_back(number[b1]);
					++b1;
				}
			}
			for (size_t i = start; i < end; ++i) {
				number[i] = b[i - start];
			}
		}
		void siftDown(vector<int>& number, int root, const int& bottom)
		{
			int maxChild;
			int done = 0;
			while ((root * 2 <= bottom) && (!done))
			{
				if (root * 2 == bottom)
					maxChild = root * 2;
				else if (number[root * 2] > number[root * 2 + 1])
					maxChild = root * 2;
				else
					maxChild = root * 2 + 1;
				if (number[root] < number[maxChild])
				{
					int temp = number[root];
					number[root] = number[maxChild];
					number[maxChild] = temp;
					root = maxChild;
				}
				else
					done = 1;
			}
		}
		void Quick(vector<int>& number,	int n) {
			int i = 0;
			int j = n - 1;
			int mid = number[n / 2];
			do {
				while (number[i] < mid) {
					i++;
				}
				while (number[j] > mid) {
					j--;
				}
				if (i <= j) {
					int tmp = number[i];
					number[i] = number[j];
					number[j] = tmp;

					i++;
					j--;
				}
			} while (i <= j);
			if (j > 0) {
				Quick(number, j + 1);
			}
			if (i < n) {
				Quick(number, n - i);
			}
		
		}
};



class Alg {
public:
	Alg(const int& number_of_elements, const string& file2) {
		push_file = file2;
		elements.resize(number_of_elements);
		srand(time(NULL));
		for (auto& item : elements) {
			item = rand();
		}
	}
	Alg(const string& file, const string& file2) {
		push_file = file2;
		ifstream inp(file);
		if (!inp.is_open()) {
			throw exception("File wasn't open");
		}
		stringstream input;
		string c, b;
		getline(inp, c);
		getline(inp, b);
		input << c + " " << b;
		int number_of_elements;
		input >> number_of_elements;
		elements.resize(number_of_elements);
		for (int i = 0; i < number_of_elements; ++i) {
			input >> elements[i];
		}
	}
	times timer() {
		Algorithms bubble;
		times buf;
		cout << endl 
			<< "1.Bubble" << endl 
			<< "2.Merger" << endl 
			<< "3.Insertion sort" << endl 
			<< "4.Shell" << endl
			<< "5.Selection sort" << endl
			<< "6.Heap sort" << endl
			<< "7.Quick sort" << endl
			<< "8.Patience sort" << endl;
		int numbe;
		cin >> numbe;
		switch (numbe)
		{
		case 1:
			buf = bubble.SortPuz(elements, push_file);
			buf.WriteSortType("Bubble");
			return buf;
			break;
		case 2:
			buf = bubble.SortSl(elements, push_file);
			buf.WriteSortType("Merger");
			return buf;
			break;
		case 3:
			buf = bubble.SortInsert(elements, push_file);
			buf.WriteSortType("Insertion");
			return buf;
		case 4:
			buf = bubble.SortShell(elements, push_file);
			buf.WriteSortType("Shell");
			return buf;
		case 5:
			buf = bubble.SortSelection(elements, push_file);
			buf.WriteSortType("Selection");
			return buf;
		case 6:
			buf = bubble.SortHeap(elements, push_file);
			buf.WriteSortType("Heap");
			return buf;
		case 7:
			buf = bubble.SortQuick(elements, push_file);
			buf.WriteSortType("Quick");
			return buf;
		case 8:
			buf = bubble.SortPatience(elements, push_file);
			buf.WriteSortType("Patience");
			return buf;
		default: throw exception("Wrong sort");
			break;
		}
	}
private:
	string push_file;
	vector<int> elements;
};
int main() {
	vector<times> str;
	try {
		//////////////// Add some items \\\\\\\\\\\\\\\\\\\\\\\\\\\\

		
		Alg j("C://Users//Ko1l//Desktop//1.txt", "C://Users//Ko1l//Desktop//2.txt"); //From file 1.txt to 2.txt
		Alg al(500, "C://Users//Ko1l//Desktop//2.txt"); //Random 500 numbers 
	

		try {
			str.push_back(al.timer());
			str.push_back(j.timer());
		}
		catch (exception& c) {
			cout << c.what();
		}
	}
	catch (exception& c) {
		cout << c.what();
	}

	for (auto& item : str) {
	
		item.WriteToFile();
		 
	}
	cout << "Completed";
	return 0;
}
