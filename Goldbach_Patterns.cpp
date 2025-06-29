// A C++ program which can be used to compute
// data supporting the conjecture in this paper.
// Each option generates a user-specified output file
// or options to send the output to the concole.
//
// Input Options and output formats
//   Start = srarting value of e
//   End   = ending value of e
//
//   Output f = output file on desktop
//     or   c for console output
//
//   Code:  
//       'a' all solutions
//       'f' first sequential solution
//	     'g' all Goldbach partitions
//	     'l' last sequential solution
//	     's' allequential solutions
//	     't' total number of solutions
//	     'x' exceptions only
// 
// Output file option
//		Formatted solutions depending on code
//		a, f, g, l, s, t, x 
//
#include <io.h>
#include <conio.h>
#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <fstream>
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
	cout << "   One or more:" << endl;
	cout << "		'a' all solutions" << endl;
	cout << "		'f' first sequential solution" << endl;
	cout << "		'g' all Goldbach partitions" << endl;
	cout << "		'l' last sequential solution" << endl;
	cout << "		's' all sequential solutions" << endl;
	cout << "		't' total number of solutions" << endl;
	cout << "		'x' exceptions only" << endl;
	cout << "   Output file option:" << endl;
	cout << "		Formatted solutions depending on code" << endl;
	cout << "	        a, f, g, l, s, t, x " << endl;
}

int main()
{
	string data = GetCurrentDirectory().c_str();
	string outdata = "C:\\Users\\" + username() + "\\Desktop\\";
	string base = "C:\\Users\\" + username() + "\\Desktop\\Goldbach_mini\\";
	string filename, first, dir, cmd;
	string code, r1 = "";
	string diff = "";
	int start, end, e, k, count, totals, twins, ndx, exception_count;
	bool debug = false;
	bool fileopen = false;
	bool goldbach = false;
	bool sequential = false;
	bool total = false;
	bool verify = false;
	bool exception = false;
	bool first_step = false;
	bool last_step = false;
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
		sequential = false;
		goldbach = false;
		verify = false;
		total = false;
		fileopen = false;
		exception = false;
		first_step = false;
		last_step = false;

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

		if (end > pow(10.0,9))
		{
			std::cout << "\nEnd > 10^9" << endl;
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

		if (100000000 <= end)
		{
			filename = data + "10-9.txt";
		}

		k = (end - 6) / 2 + 1;
	
		cout << filename << endl;

		infile.open(filename);
		r1 = getFileContent(filename);
		r1.erase(remove(r1.begin(), r1.end(), ' '), r1.end());
		r1.erase(remove(r1.begin(), r1.end(), '\n'), r1.end());
		std::cout << r1.size() << " bytes read from " << filename << endl;

		if (2 * k > r1.size())
		{
			std::cout << 2 * k << " > " << r1.size() << endl;
			exit(1);
		}

		for (int i = 1; i <= 2 * k + 2; i += 2)
			v1.push_back(r1[i] - 48);

		infile.close();

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
		std::cout << "\t'a' all solutions" << endl;
		std::cout << "\t'f' first sequential solution" << endl;
		std::cout << "\t'g' all Goldbach partitions" << endl;
		std::cout << "\t'l' last sequential solution" << endl;
		std::cout << "\t's  all sequential solutions" << endl;
		std::cout << "\t't' total number of solutions" << endl;
		std::cout << "\t'x' exceptions only" << endl;
		std::cin >> code;

		std::transform(code.begin(), code.end(), code.begin(), ::toupper);

		if (code.find('A') != std::string::npos)
		{
			std::cout << "  All solutions" << endl;
			goldbach = true;
			sequential = true;
		}

		if (code.find('G') != std::string::npos)
		{
			std::cout << "  All Goldbach partitions" << endl;
			goldbach = true;
		}

		if (code.find('L') != std::string::npos)
		{
			std::cout << "  Last sequential solution" << endl;
			last_step = true;
		}

		if (code.find('S') != std::string::npos)
		{
			std::cout << "  All sequential solutions" << endl;
			sequential = true;
		}

		if (code.find('T') != std::string::npos && (goldbach || sequential))
		{
			std::cout << "  Total number of solutions" << endl;
			total = true;
		}

		if (code.find('F') != std::string::npos)
		{
			std::cout << "  First sequential solution" << endl;
			first_step = true;
		}

		if (code.find('X') != std::string::npos)
		{
			std::cout << "  Exceptions only" << endl;
			exception = true;
		}

		cout << endl;


		if (code != "")
		{
			int exception_count = 0;

			for (e = start; e <= end; e += 2)
			{
				long p1 = 0;
				long p2 = 0;
				count = 0;
				totals = 0;
				twins = 0;
				string flag = "";

				if (e <= 4) break;

				k = (e - 6) / 2 + 1;
				int l = (e - 4) / 2 + 1;

				clock_t start = clock(); // Start the clock
				for (int ii = 0; ii < k; ii++)
				{
					int i = ii;
					if (last_step)
					{
						i = k  - 1 - ii;
					}

					if (total && ii > 10000 && ii % 10000 == 0)
						std::cout << " " << e << ": " << ii/10000 <<  "\r";


					if (debug)
						cout << "i: " << i << " - " << k - i - 1 << endl;

					if (v1[i] * v1[k - i - 1])
					{
						p1 = 2 * i + 3;

						if (goldbach && !total && p1 <= e/2)
						{
							if (fileopen)
								outfile << to_string(e) + " (mod 6) = " + to_string(e % 6) + " : " + to_string(p1) << " : " << to_string(e - p1) << endl;
							std::cout << to_string(e) + " (mod 6) = " + to_string(e % 6) + " : " + to_string(p1) << " : " << to_string(e - p1) << endl;
						}

						totals = totals + 1;
						
						int jj = i - 1;
						if (jj < 0)
							jj = 0;

						for (int j = jj  ; j <= i + 1; j += 1)
						{

							if (debug)
								cout << "j: " << j << " - " << l - j - 1 << endl;

								if (v1[j] * v1[l - j - 1])
								{
									p2 = 2 * j + 3;

									if (debug)
										cout << i << " : " << p1 << " / " << j << " : " << p2 << endl;

									if (p2 < e && is_prime(e - p1) && is_prime(e + 2 - p2) )
									{
										count = count + 1;
										twins = twins + 1;
										if (count >= 1)
										{
											flag = "";
											int diff = (e + 2 - 2 * p2) - (e - 2 * p1);

											if (debug)
												cout << "diff: " << diff << endl;

											if (e % 6 == 2 && diff != 6)
											{
												flag = "*";
												twins--;
											}
											if ((e % 6 == 0 || e % 6 == 4) && diff != -2)
											{
												flag = "*";
												twins--;
											}

											if (!exception)
											{
												if ((sequential || first_step || last_step) && !total && flag != "*")
												{
													if (fileopen)
													{
														outfile << to_string(e) + " (mod 6) = " + to_string(e % 6) + " : " + to_string(p1) + " / " + to_string(e - p1) << " : " << to_string(p2) << " (" << e - 2 * p1 << ") ";
														outfile << flag << " ( " << e + 2 - 2 * p2 - (e - 2 * p1) << " ) " << to_string(p2) << " : " << to_string(e + 2 - p2) << endl;
													}
													cout << to_string(e) + " (mod 6) = " + to_string(e % 6) + " : " + to_string(p1) + " / " + to_string(e-p1) << " : " << to_string(p2) << " (" << e - 2 * p1 << ") ";
													cout << flag << " ( " << e + 2 - 2 * p2 - (e - 2 * p1) << " ) " << to_string(p2) << " : " << to_string(e + 2 - p2) << endl;
												}
											}
											else
											{
												if (!exception && flag == "*")
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

											if (total || sequential || goldbach)
												continue;
											if (twins > 0)
											{
												ii = k;
												break;
											}
										}
									}
							}
						}
					}
				}
				if (goldbach && total && !exception)
				{
					totals = floor((totals + 1) / 2);
					cout << "Total number of Goldbach partitions for " << e << ": " << totals << endl;
					if (fileopen)
						outfile << "Total number of Goldbach partitions for " << e << ": " << totals << endl;
				}
				if (sequential && total &&  !exception)
				{
					cout << "Total number of twin prime solutions for " << e << ": " << twins << endl;
					if (fileopen)
						outfile << "Total number of twin prime solutions for " << e << ": " << twins << endl;
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
			if (exception)
				std::cout << endl << "Number of exceptions = " << exception_count << endl;

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
