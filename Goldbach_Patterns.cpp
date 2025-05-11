// A C++ program which can be used to compute
// data supporting the conjecture in this paper.
// Each option generates a user-specified output file
// or options to send the output to the concole.
//
// Input Options and output formats
//   Start = srarting value of e
//   End   = ending value of e
//   Output f = output file on desktop
//     or   c for console output
//   Code:  'f' first induction step
//			'l' last induction step
//			'x' exceptions only
//			'5' include 5 in sequential solution
//			't' total number of solutions
//			'a' all sequential solutions
// 
// Output file option
//			Formatted solutions depending on code
//				f, l, x, 5, t, a 
//
#include <io.h>
#include <conio.h>
#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <cmath>
#include <string>
#include <cstring>
#include <iterator>
#include <vector>
#include <random>
#include <numeric>
#include <memory>
#include <ctime>
#include <windows.h>
#include <Lmcons.h>
#include <sys/types.h>
#include <boost/tuple/tuple.hpp>
#include <wchar.h>
#include <locale.h>

using namespace std;

ofstream fout;
ifstream fin;
vector<string> files;

std::vector<double> v1;
std::vector<double> v;

bool is_prime(long n)
{
	long i;
	bool is_prime = true;

	// loop to check if n is prime
	for (i = 2; i <= n / 2; ++i)
	{
		if (n % i == 0)
		{
			is_prime = false;
			break;
		}
	}
	return is_prime;
}

string username()
{
	char buffer[UNLEN + 1]{};
	DWORD len = UNLEN + 1;
	if (GetUserNameA(buffer, &len)) return buffer;
	else return "";
}

std::string getFileContent(const std::string& path)
{
	std::ifstream file(path);
	std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	return content;
}

string GetCurrentDirectory()
{
	string s;
	char buffer[MAX_PATH];
	const char* str;
	GetModuleFileNameA(NULL, buffer, MAX_PATH);
	std::string::size_type pos = std::string(buffer).find_last_of("\\/");
	s = std::string(buffer).substr(0, pos);
	return s + "\\";
}

void findAndReplaceAll(std::string& data, std::string toSearch, std::string replaceStr)
{
	// Get the first occurrence
	size_t pos = data.find(toSearch);
	// Repeat till end is reached
	while (pos != std::string::npos)
	{
		// Replace this occurrence of Sub String
		data.replace(pos, toSearch.size(), replaceStr);
		// Get the next occurrence from the current position
		pos = data.find(toSearch, pos + replaceStr.size());
	}
}

void help1()
{
	cout << " Input Options and output formats" << endl;
	cout << "   Start = srarting value of e" << endl;
	cout << "   End   = ending value of e" << endl;
	cout << "   Output f = output file on desktop" << endl;
	cout << "     or   c for console output" << endl;
	cout << "   Code:	'f' first induction step" << endl;
	cout << "		'l' last induction step" << endl;
	cout << "		'x' exceptions only" << endl;
	cout << "		'5' include 5 in sequential solution" << endl;
	cout << "		't' total number of solutions" << endl;
	cout << "		'a' all sequential solutions" << endl;
	cout << "   Output file option:" << endl;
	cout << "		Formatted solutions depending on code" << endl;
	cout << "	        f, l, 5, x, t, a " << endl;
}

bool file_exists(const std::string& filename)
{
	std::ifstream file(filename);
	return file.good();
}

bool create_file(long final)
{ 
	string code, r1 = "";
	long k = (final - 6) / 2 + 1;

	std::cout << "\nDo you really want to compute this vector [N]?" << endl;
	std::cout << "This could take several hours or even days." << endl;
	std::cin >> code;

	if (toupper(code[0]) != 'Y')
		return false;

	clock_t start = clock(); // Start the clock

	for (int i = 1; i <= k; i++)
	{
		if (is_prime(2 * i + 1))
			v1.push_back(1);
		else
			v1.push_back(0);
		if (i % 100000 == 0)
			std::cout << "                   " << '\r' << 2 * i;
	}

	clock_t end = clock(); // Stop the clock

	double elapsed_mins = double(end - start) / (60 * CLOCKS_PER_SEC);
	if (elapsed_mins > 1)
		std::cout << "\n Elapsed time constructing vector: " << elapsed_mins << " minutes" << std::endl;
}

int main()
{
	string data = GetCurrentDirectory().c_str();
	string outdata = "C:\\Users\\" + username() + "\\Desktop\\";
	string base = "C:\\Users\\" + username() + "\\Desktop\\Goldbach_mini\\";
	string filename, first, dir, cmd;
	string code, r1 = "";
	string diff = "";
	int start, end, e, k, cycle, count, totals, index, pos, fold, ndx, match, matched;
	bool fileopen = false;
	bool all = false;
	bool total = false;
	bool solutions = false;
	bool verify = false;
	bool induction_step = false;
	bool exception = false;
	bool reverse_step = false;
	bool use_five = false;
	double ratio, min, max;
	std::vector<double> v1;
	std::vector<double> v;
	char buffer[MAX_PATH];
	ifstream infile;
	ofstream outfile;

	v1.resize(10 ^ 10);
	v.resize(10 ^ 10);

	while (true)
	{
		code = "";
		all = false;
		verify = false;
		total = false;
		fileopen = false;
		induction_step = true;
		exception = false;
		reverse_step = false;
		use_five = false;
		fold = 1;
		match = -1;
		matched = 0;
		cycle = 0;

		v1.clear();
		v.clear();

		std::cout << "\nEnter ? or exit or starting value of e: ";
		std::cin >> cmd;
		std::transform(cmd.begin(), cmd.end(), cmd.begin(), ::tolower);

		if (cmd == "exit") return 0;

		if (cmd == "help" || cmd == "?")
		{
			system("CLS");
			help1();
			int ch = _getch();
			continue;
		}

		start = stoi(cmd);
		if (start < 6)
		{
			std::cout << "\Start < 6" << endl;
			std::cin.get();
			return 0;
		}

		std::cout << "\nEnter ending value of e: ";
		std::cin >> cmd;
		end = stoi(cmd);

		k = (end - 6) / 2 + 1;

		if (end > pow(10.0,10))
		{
			std::cout << "\nEnd > 10^10" << endl;
			std::cin.get();
			return 0;
		}

		if (start > end)
		{
			std::cout << "\nStart > End" << endl;
			std::cin.get();
			return 0;
		}

		if (end < pow(10.0, 6))
		{
			filename = data + "10-6.txt";
		}

		if (1000000 <= end && end < 10000000)
		{
			filename = data + "10-7.txt";
		}

		if (10000000 <= end && end < 100000000)
		{
			filename = data + "10-8.txt";
		}

		if (100000000 <= end && end < 1000000000)
		{
			filename = data + "10-9.txt";
			if (!file_exists(filename))
				if (!create_file(end))
					return 0;
		}

		if (1000000000 <= end)
		{
			filename = data + "10-10.txt";
			if (!create_file(end))
				return 0;
		}

		if (file_exists(filename))
		{ 
			cout << filename << endl;
			infile.open(filename);
			r1 = getFileContent(filename);
			r1.erase(remove(r1.begin(), r1.end(), ' '), r1.end());
			r1.erase(remove(r1.begin(), r1.end(), '\n'), r1.end());
			std::cout << r1.size() << " bytes read from " << filename << endl;

			for (int i = 1; i <= 2 * k; i += 2)
				v1.push_back(r1[i] - 48);
		}
		else
		{
			if (2 * k > r1.size())
			{
				std::cout << 2 * k << " > " << r1.size() << endl;
				exit(1);
			}

			infile.close();
		}

		std::cout << "\nEnter an 'f' for output file or 'c' for console" << endl;
		std::cin >> code;
		std::cout << endl;

		if (toupper(code[0]) == 'F')
		{
			filename = outdata + "G-" + std::to_string(start) + "-" + std::to_string(end) + ".dat";
			cout << "Output filename: " << filename << endl << endl;
			outfile.open(filename);
			fileopen = true;
		}

		std::cout << "Enter one or more of the following:" << endl;
		std::cout << "\t'f' first induction step" << endl;
		std::cout << "\t'l' last induction step" << endl;
		std::cout << "\t'x' exceptions only" << endl;
		std::cout << "\t'5' include 5 in sequential solutions" << endl;
		std::cout << "\t't' total number of solutions" << endl;
		std::cout << "\t'a' all sequential solutions" << endl;
		std::cin >> code;

		std::transform(code.begin(), code.end(), code.begin(), ::toupper);

		if (code.find('5') != std::string::npos)
		{
			std::cout << "  Include 5 in sequential solutions" << endl << endl;
			use_five = true;
		}

		if (code.find('L') != std::string::npos)
		{
			std::cout << "  Last sequential solution" << endl << endl;
			reverse_step = true;
		}

		if (code.find('A') != std::string::npos)
		{
			std::cout << "  All sequential solutions" << endl << endl;
			all = true;
		}

		if (code.find('T') != std::string::npos)
		{
			std::cout << "  Total number of solutions" << endl << endl;
			all = true;
			total = true;
		}

		if (code.find('F') != std::string::npos)
		{
			std::cout << "  First sequential solution" << endl << endl;
		}

		if (code.find('X') != std::string::npos)
		{
			std::cout << "  Induction step exceptions only" << endl << endl;
			exception = true;
		}

		if (induction_step)
		{
			int start_count = -1;
			int exception_count = 0;

			for (e = start; e <= end; e += 2)
			{
				long p1 = 0;
				long p2 = 0;
				count = 0;
				totals = 0;
				string flag = "";

				if (e <= 4) break;

				k = (e - 6) / 2 + 1;
				int l = (e - 4) / 2 + 1;

				clock_t start = clock(); // Start the clock
				for (int ii = 0; ii < floor((k + 1) / 2); ii++)
				{
					int i = ii;
					if (reverse_step)
					{
						i = floor((k + 1) / 2) - 1 - ii;
					}
					if (e % 100000 == 0)
					{
						std::cout << "              " << "\r";
						std::cout << " " << e << "\r";
					}

					if (v1[i] * v1[k - i - 1])
					{
						totals = totals + 1;
						if (is_prime(2 * i + 3))
						{
							p1 = 2 * i + 3;
							if (!use_five && p1 == 5)
								continue;
						}
						for (int j = i - 1; j >= 0 && j <= i + 1; j += 2)
						{
							if (v1[j] * v1[l - j - 1])
							{
								if (is_prime(2 * j + 3))
									p2 = 2 * j + 3;
								//								if ( (is_prime(p2 - 2) && p1 == p2 - 2))
								if ((is_prime(p2 + 2) && p1 == p2 + 2) || (is_prime(p2 - 2) && p1 == p2 - 2))
								{
									if (is_prime(e - p1) && is_prime(e + 2 - p2))
									{
										count = count + 1;
										if (!total && count >= 1)
										{
											flag = "";
											int diff = (e + 2 - 2 * p2) - (e - 2 * p1);
											if (e % 6 == 2 && diff != 6)
											{
												flag = "*";
												exception_count++;
											}
											if ((e % 6 == 0 || e % 6 == 4) && diff != -2)
											{
												flag = "*";
												exception_count++;
											}
											if (!exception)
											{
												if (fileopen)
												{
													outfile << to_string(e) + " (mod 6) = " + to_string(e % 6) + " : " + to_string(p1) << " : " << to_string(e - p1) << " (" << e - 2 * p1 << ") ";
													outfile << flag << " ( " << e + 2 - 2 * p2 - (e - 2 * p1) << " ) " << to_string(p2) << " : " << to_string(e + 2 - p2) << endl;
												}
												else
												{
													std::cout << to_string(e) + " (mod 6) = " + to_string(e % 6) + " : " + to_string(p1) << " : " << to_string(e - p1) << " (" << e - 2 * p1 << ") ";
													std::cout << flag << " ( " << e + 2 - 2 * p2 - (e - 2 * p1) << " ) " << to_string(p2) << " : " << to_string(e + 2 - p2) << endl;
												}
											}
											else
											{
												if (flag == "*")
												{
													if (fileopen)
													{
														outfile << to_string(e) + ": " + to_string(p1) << " : " << to_string(e - p1) << " (" << e - 2 * p1 << ") ";
														outfile << flag << " ( " << e + 2 - 2 * p2 - (e - 2 * p1) << " ) " << to_string(p2) << " : " << to_string(e + 2 - p2) << endl;
													}
													std::cout << to_string(e) + ": " + to_string(p1) << " : " << to_string(e - p1) << " (" << e - 2 * p1 << ") ";
													std::cout << flag << " ( " << e + 2 - 2 * p2 - (e - 2 * p1) << " ) " << to_string(p2) << " : " << to_string(e + 2 - p2) << endl;
												}
											}
											if (all)
												continue;
											ii = floor((k + 1) / 2);
											break;
										}
									}
								}
							}
						}

					}
				}
				if (total)
				{
					cout << "Total number of solutions for " << e << ": " << totals << endl;
					if (fileopen)
						outfile << "Total number of solutions for " << e << ": " << totals << endl;
				}
				if (count > 1)
				{
					cout << "Total number of twin prime solutions for " << e << ": " << count << endl;
					if (fileopen)
						outfile << "Total number of twin prime solutions for " << e << ": " << count << endl;
				}
				clock_t end = clock(); // Stop the clock

				double elapsed_mins = double(end - start) / (60 * CLOCKS_PER_SEC);
				if (elapsed_mins > 1)
					std::cout << "\t Elapsed time: " << elapsed_mins << " minutes" << std::endl;

				if (count == 0)
				{
					exception_count++;
					if (fileopen)
						outfile << to_string(e) + " has no sequential solution. " << endl;
					std::cout << to_string(e) + " has no sequential solution. " << endl;
				}
			}
			std::cout << endl << "\nNumber of exceptions = " << exception_count << endl;

			if (fileopen)
			{
				outfile << endl << "Range: " << start << " - " << end << endl;
				outfile << "Number of exceptions = " << exception_count << endl;
				std::cout << "<" << filename << "> created." << endl;
				outfile.close();
			}
			continue;
		}
	}
}
