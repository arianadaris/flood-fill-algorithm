/*
	Author: Ariana Rajewski
	Date: 4/2/2021
	Description: Allows the user to create a grid and populate it with impassible items. User can then enter a valid
		coordinate and fill character of their choice, and the grid will be filled using a 4-way flood fill algorithm.
	Usage: C++
*/
#include <iostream>

using std::cout;
using std::cin;
using std::endl;

void add_impassible(char**&, int, int, int);
void print(char**, int, int);
void flood(char**&, char, int, int, int, int);

int main()
{
	int width, height, percent;
	char** grid = NULL;
	char input = ' '; // set to ' ' temporarily

	while (input != 'N') // If input == N, continue with program. Otherwise, continue prmopting user.
	{
		// Prompt user for width and height
		cout << "Enter width. " << endl;
		cin >> width;

		cout << "Enter height. " << endl;
		cin >> height;

		// Create dynamic 2D char array
		grid = new char* [width];
		for (int i = 0; i < width; i++)
		{
			grid[i] = new char[height];
		}

		// Prompt user for "Percent of Impassible"
		cout << "Enter Percent of Impassible (without %). " << endl;
		cin >> percent; // percent as in 30, 40, 50 percent

		// Check if Percent of Impassible > 40
		if (percent > 40)
		{
			// Prompt user with warning, check decision
			cout << "Percent of Impassible is greater than 40% and may cause poor results. Would you like to continue? Y/N " << endl;
			cin >> input;

			// Delete array if user does not want to continue
			if (input == 'Y')
			{
				for (int i = 0; i < width; i++)
				{
					delete[] grid[i];
				}
				delete[] grid;
			}
		}
		else // If Percent of Impassible is <= 40, continue without warning
			break;
	}
	// Fill grid array with spaces
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			grid[i][j] = ' ';
		}
	}

	// Populate grid array with Percent of Impassible
	int area = width * height;
	double percentage = (double) percent / 100; // actual percentage, ex. 3%, 15%
	int impassible = (int)(area * percentage);
	add_impassible(grid, impassible, width, height); // Add the impassible items to the grid

	// Print grid array
	print(grid, width, height);

	// Prompt user for x, y cordinates and fill character of choice
	int x, y;

	while (1) // Run prompt 
	{
		// Prompt user for x, y coordinate
		cout << "Enter X coordinate. " << endl;
		cin >> x;

		cout << "Enter Y coordinate. " << endl;
		cin >> y;

		if (x > width || y > height || grid[x][y] == '#') // check if coordinate is valid
		{
			cout << "Please check that the coordinates are valid." << endl;
		}
		else // if coordinates are valid, continue 
			break;
	}

	// Prompt user for fill char
	char fill_char;
	cout << "Enter fill character. " << endl;
	cin >> fill_char;

	// Perform 4 way flood fill
	flood(grid, fill_char, width, height, x, y);

}


void add_impassible(char**& grid, int impassible, int width, int height)
{
	srand(time(NULL)); // set seed for random

	// Fill 2D grid array with Impassible Items in random locations until no items are left
	while (impassible > 0)
	{
		// Select a random coordinate on the grid
		int x = rand() % width;
		int y = rand() % height;

		// Check that the value at the coordinate in the grid is empty (not already an impassible char)
		if (grid[x][y] == ' ')
		{
			grid[x][y] = '#'; // set the value of the coordinate to #, the impassible char
			impassible--; // decrement the number of impassible items to be added
		}
	}
	return;
}


void print(char** grid, int width, int height)
{
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			cout << grid[i][j];
		}
		cout << endl;
	}
	cout << endl;
	return;
}


void flood(char**& grid, char fill_char, int width, int height, int x, int y)
{
	if (x > width - 1 || y > height - 1 || x < 0 || y < 0) // check if x or y is within area of grid
		return;
	if (grid[x][y] == '#') // check if an impassible char is at that coordinate
		return;
	if (grid[x][y] == fill_char) // check if the coordinate has already been filled
		return;

	// If previous conditions have not been met, fill the coordinate with fill char
	grid[x][y] = fill_char;
	print(grid, width, height);
	cout << "------------------" << endl;

	// Check the coordinates around the original coordinate
	flood(grid, fill_char, width, height, (x + 1), y);
	flood(grid, fill_char, width, height, x, (y - 1));
	flood(grid, fill_char, width, height, (x - 1), y);
	flood(grid, fill_char, width, height, x, (y + 1));
}