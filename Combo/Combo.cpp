
#include <iostream>

// There are 3 guys with who come together for dinner
// They decide to see who has the largest stomach
// Each say 2 phrases to describe the relationship of their stomach size with the others
// However, the amount of true phrases they say is based on their stomach size ranking, with the lowest stomach size corresponding to the most true phrases


// This is probably a very inefficient solution but it was my first thought process and I'm too lazy to think of more

struct Guy
{
	bool (*cond1)(int a, int b, int c);
	bool (*cond2)(int a, int b, int c);
	char symbol;
	int val;

	Guy(char symbol, bool (*cond1)(int a, int b, int c), bool (*cond2)(int a, int b, int c)) : symbol(symbol), cond1(cond1), cond2(cond2)
	{}

	char getSymbol() const
	{
		return symbol;
	}

	int getVal() const
	{
		return val;
	}

	void setVal(int val)
	{
		this->val = val;
	}

	int fetchVal(char symbol, Guy** arr)
	{
		for (int i = 0; i < 3; i++)
		{
			if (arr[i]->getSymbol() == symbol)
			{
				return arr[i]->getVal();
			}
		}
		std::cerr << "Symbol \"" << symbol << "\" not found!\n";
		return 0;
	}

	int verify(Guy** arr)
	{
		int a = fetchVal('A', arr);
		int b = fetchVal('B', arr);
		int c = fetchVal('C', arr);

		return (cond1(a, b, c) ? 1 : 0) + (cond2(a, b, c) ? 1 : 0);
	}
};

bool tryArrangement(Guy** arr)
{
	// I previously didn't consider the chance that two guys might eat the same but whatever

	Guy* sortedArr[] = { arr[0], arr[1], arr[2] };

	bool sorted = false;
	while (!sorted)
	{
		sorted = true;
		for (int i = 1; i < 3; i++)
		{
			int a = sortedArr[i - 1]->getVal();
			int b = sortedArr[i]->getVal();
			if (b < a)
			{
				Guy* temp = sortedArr[i];
				sortedArr[i] = sortedArr[i - 1];
				sortedArr[i - 1] = temp;
				sorted = false;
			}
		}
	}

	// Test if the combination fits the description
	for (int i = 0; i < 3; i++)
	{
		int truths = 2 - i;
		int trueCount = sortedArr[i]->verify(arr);
		if (trueCount != truths)
		{
			return false;
		}

	}
	return true;
}

Guy* fetchGuy(char symbol, Guy** arr)
{
	for (int i = 0; i < 3; i++)
	{
		if (arr[i]->getSymbol() == symbol)
		{
			return arr[i];
		}
	}
	return nullptr;
}

void setArrangement(int a, int b, int c, Guy** arr)
{
	Guy* guya = fetchGuy('A', arr);
	Guy* guyb = fetchGuy('B', arr);
	Guy* guyc = fetchGuy('C', arr);
	guya->setVal(a);
	guyb->setVal(b);
	guyc->setVal(c);
}

void printArrangement(Guy** arr)
{
	Guy* sortedArr[] = { arr[0], arr[1], arr[2] };

	bool sorted = false;
	while (!sorted)
	{
		sorted = true;
		for (int i = 1; i < 3; i++)
		{
			int a = sortedArr[i - 1]->getVal();
			int b = sortedArr[i]->getVal();
			if (b < a)
			{
				Guy* temp = sortedArr[i];
				sortedArr[i] = sortedArr[i - 1];
				sortedArr[i - 1] = temp;
				sorted = false;
			}
		}
	}

	for (int i = 0; i < 3; i++)
	{
		std::cout << sortedArr[i]->getSymbol() << ' ';
	}
	std::cout << '\n';
}

int main1()
{
	// A says:
	Guy* a = new Guy('A', [](int a, int b, int c) -> bool {
			return b > a; // B eats more than me
		}, [](int a, int b, int c) -> bool{
			return b == c; // C eats as much as me
		});
	// B says:
	Guy* b = new Guy('B', [](int a, int b, int c) -> bool {
			return a > b; // A eats more than me
		}, [](int a, int b, int c) -> bool{
			return a > c; // A eats more than C
		});
	// C says:
	Guy* c = new Guy('C', [](int a, int b, int c) -> bool {
			return b > c; // I eat more than B
		}, [](int a, int b, int c) -> bool{
			return b == c; // B eats more than A
		});

	Guy* arr[] = { a, b, c };

	for (int ai = 0; ai < 3; ai++)
	{
		for (int bi = 0; bi < 3; bi++)
		{
			for (int ci = 0; ci < 3; ci++)
			{
				setArrangement(ai, bi, ci, arr);
				if (tryArrangement(arr))
				{
					printArrangement(arr);
					return 0;
				}
			}
		}
	}

	std::cout << "No solution...\n";
}

// Odd, something must be wrong here