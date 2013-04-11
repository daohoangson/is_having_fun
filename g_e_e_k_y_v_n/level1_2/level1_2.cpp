#include <iostream>
#include <vector>
#include <string>

class Mapping
{
public:
	char from;
	char to;
};

void add_string_to_list(std::string &temp_str, char temp_char, std::vector<std::string> &list)
{
	if (temp_char < 'a' || temp_char > 'z')
	{
		list.push_back(temp_str);
		temp_str = "";
	}
	else
	{
		temp_str += temp_char;
	}
}

void read_line_of_strings_to_list(std::vector<std::string> &list)
{
	std::string temp_str = "";
	char temp_char;

	do
	{
		temp_char = getchar();
		add_string_to_list(temp_str, temp_char, list);
	} while (temp_char != '\n' && temp_char != EOF);
}

void read_mapping(std::vector<Mapping> &mappings)
{
	char c1, c2, c3;

	while (true)
	{
		c1 = getchar();
		if (c1 < 'a' || c1 > 'z') break;
		c3 = getchar();
		if (c3 != ' ') break;

		do
		{
			c2 = getchar();
			c3 = getchar();
			
			Mapping m;
			m.from = c1;
			m.to = c2;
			mappings.push_back(m);
		} while (c3 != '\n' && c3 != EOF);
	}
}

bool is_mapping_found(const std::vector<Mapping> &mappings,
	const char from, const char to)
{
	for (int kk = 0, lkk = mappings.size(); kk < lkk; kk++)
	{
		Mapping m = mappings.at(kk);
		if (m.from == from)
		{
			return m.to == to;
		}
	}

	return true;
}

bool is_mapping_match(const std::string &input,
	const std::string &word,
	const std::vector<Mapping> &mappings)
{
	if (input.length() != word.length()) return false;

	for (int k = 0, lk = input.length(); k < lk; k++)
	{
		if (!is_mapping_found(mappings, input[k], word[k]))
		{
			return false;
		}
	}

	return true;
}

std::string decode(const std::string &input,
	const std::vector<std::string> &dictionary,
	const std::vector<Mapping> &mappings)
{
	for (int j = 0, lj = dictionary.size(); j < lj; j++)
	{
		if (is_mapping_match(input, dictionary.at(j), mappings))
		{
			return dictionary.at(j);
		}
	}

	return input;
}

void decode(const std::vector<std::string> &inputs,
	const std::vector<std::string> &dictionary,
	const std::vector<Mapping> &mappings)
{
	for (int i = 0, l = inputs.size(); i < l; i++)
	{
		if (i > 0) std::cout << ' ';
		std::cout << decode(inputs.at(i), dictionary, mappings);
	}
}

void filter_incorrect_mappings(const std::vector<std::string> &inputs,
	const std::vector<std::string> &dictionary,
	std::vector<Mapping> &mappings)
{
	bool* incorrect = new bool[mappings.size()];
	for (int kk = 0, lkk = mappings.size(); kk < lkk; kk++) incorrect[kk] = false;

	for (int kk = 0, lkk = mappings.size(); kk < lkk; kk++)
	{
		int same_from_count = 0;
		Mapping m = mappings.at(kk);

		// look for mapping with the same `from`
		for (int kk2 = 0; kk2 < lkk; kk2++)
		{
			if (kk2 == kk) continue; // same mapping index, ignore

			if (mappings.at(kk2).from == m.from)
			{
				same_from_count++;
			}
		}

		if (same_from_count > 0)
		{
			// this mapping may be incorrect, start checking
			std::vector<Mapping> mappings_without_same_from;
			mappings_without_same_from.push_back(m);
			for (int kk2 = 0; kk2 < lkk; kk2++)
			{
				if (mappings.at(kk2).from != m.from)
				{
					mappings_without_same_from.push_back(mappings.at(kk2));
				}
			}

			for (int i = 0, l = inputs.size(); i < l; i++)
			{
				std::string decoded = decode(inputs.at(i), dictionary, mappings_without_same_from);
				if (decoded.compare(inputs.at(i)) == 0)
				{
					// unable to decode the input
					// this mapping must be incorrect
					incorrect[kk] = true;
					break; // for (i;...;...)
				}
			}
		}
	}

	for (int kk = mappings.size() - 1; kk >= 0; kk--)
	{
		if (incorrect[kk])
		{
			mappings.erase(mappings.begin() + kk);
		}
	}

	delete[] incorrect;
}

int main()
{
	std::vector<std::string> inputs;
	std::vector<std::string> dictionary;
	std::vector<Mapping> mappings;
	
	read_line_of_strings_to_list(inputs);
	read_line_of_strings_to_list(dictionary);
	read_mapping(mappings);
	filter_incorrect_mappings(inputs, dictionary, mappings);

	decode(inputs, dictionary, mappings);
}