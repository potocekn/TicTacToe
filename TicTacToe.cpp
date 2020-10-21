#include <iostream>
#include <vector>
using namespace std;


enum class Field{ EMPTY, PLAYER1, PLAYER2};

class Matrix
{
	int width = 0;
	int height = 0;
public:
	vector<vector<Field>> matrix;

	void set(int x, int y, Field value)
	{
		this->matrix.at(x).at(y) = value;
	}

	Field get(int x, int y) const
	{
		return this->matrix.at(x).at(y);
	}

	void print() const
	{
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				if (this->matrix.at(i).at(j) == Field::EMPTY)
				{
					cout << ". ";
				}
				else if (this->matrix.at(i).at(j) == Field::PLAYER1)
				{
					cout << "X ";
				}
				else
				{
					cout << "O ";
				}


			}
			cout << endl;
		}
	}

	void set_width(int width)
	{
		if ((this->width < width) && (this->width != 0))
				{
					for (int i = 0; i < this->height; i++)
					{

						for (int j = 0; j < (width - this->width); j++)
						{
							this->matrix.at(i).push_back(Field::EMPTY);
						}

					}
					this->width = width;
				}
				else
				{
					this->width = width;
				}

	}

	int get_width() const
	{
		return this->width;
	}

	void set_height(int height)
	{
		if (this->height < height)
		{
			for (int i = 0; i < (height - this->height); i++)
			{
				vector<Field> new_row;
				for (int i = 0; i < this->width; i++)
				{
					new_row.push_back(Field::EMPTY);
				}
				this->matrix.push_back(new_row);
			}

		}

		this->height = height;

	}

	int get_height() const
	{
		return this->height;
	}

	void fill_with_value(Field value)
	{
		vector<vector<Field>> temp_matrix;
		for (int i = 0; i < height; i++)
		{
			vector<Field> row;
			for (int j = 0; j < width; j++)
			{
				row.push_back(value);
			}
			temp_matrix.push_back(row);
		}
		this->matrix = temp_matrix;
	}

	void clear()
	{
		fill_with_value(Field::EMPTY);
	}


	vector<Field> get_row(int x) const
	{
		vector<Field> row = this->matrix.at(x);
		if (row.size() == this->width)
		{
			return row;
		}
		else if (row.size() >= this->width)
		{
			vector<Field> new_row;
			for (int i = 0; i < this->width; i++)
			{
				new_row.push_back(row.at(i));
			}
			return new_row;
		}
		else
		{
			for (int i = 0; i < (this->width - row.size()); i++)
			{
				row.push_back(Field::EMPTY);
			}
			return row;
		}

	}

	vector<vector<Field>> get_transpose() const
	{
		vector<vector<Field>> transposed_matrix(this->width,vector<Field>(this->height));

		for (size_t i = 0; i < this->height; i++)
		{
			for (size_t j = 0; j < this->width; j++)
			{
				transposed_matrix.at(j).at(i) = matrix.at(i).at(j);
			}
		}

		return transposed_matrix;
	}


	vector<Field> get_column(int x) const
	{

		vector<Field> row = this->get_transpose().at(x);
			if (row.size() == this->width)
			{
				return row;
			}
			else if (row.size() >= this->width)
			{
				vector<Field> new_row;
				for (int i = 0; i < this->width; i++)
				{
					new_row.push_back(row.at(i));
				}
				return new_row;
			}
			else
			{
				for (int i = 0; i < (this->width - row.size()); i++)
				{
					row.push_back(Field::EMPTY);
				}
				return row;
			}
	}

	vector<vector<Field>> get_rows()
	{
		return this->matrix;
	}

	vector<vector<Field>> get_columns()
	{
		return get_transpose();
	}
};

bool is_valid(int x, int y, Matrix m)
{
	if ((x >= 0 && x < m.get_width()) && (y >=0 && y < m.get_height()))
	{
		if (m.get(x,y) == Field::EMPTY)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	return false;
}


bool is_winner(Field player, Matrix m)
{

	for (int i = 0; i < m.get_height()/2 + 1; i++)
	{
		for (int j = 0; j < m.get_width(); j++)
		{
			if (m.get(i, j) == player && m.get(i+1, j) == player && m.get(i+2,j) == player && m.get(i+3,j) == player && m.get(i+4,j) == player)
			{
				return true;
			}
		}
	}

	for (int i = 0; i < m.get_height(); i++)
	{
		for (int j = 0; j < m.get_width()/2 + 1; j++)
		{
			if (m.get(i, j) == player && m.get(i, j+1) == player && m.get(i,j+2) == player && m.get(i,j+3) == player && m.get(i,j+4) == player)
			{
				return true;
			}
		}
	}

	for (int i = 0; i < m.get_height()/2; i++)
	{
		for (int j = 0; j < m.get_width()/2; j++)
		{

			if (m.get(i, j) == player && m.get(i+1, j+1) == player && m.get(i+2,j+2) == player && m.get(i+3,j+3) == player && m.get(i+4,j+4) == player)
			{
				return true;
			}
		}
	}

	for (int i = m.get_height() -1; i > m.get_height()/2; i--)
	{
		for (int j = 0; j < m.get_width()/2; j++)
		{

			if (m.get(i, j) == player && m.get(i-1, j+1) == player && m.get(i-2,j+2) == player && m.get(i-3,j+3) == player && m.get(i-4,j+4) == player)
			{
				return true;
			}
		}
	}

	for (int i = m.get_height()-1; i > m.get_height()/2; i--)
	{
		for (int j = m.get_width(); j > m.get_width()/2; j--)
		{

			if (m.get(i, j) == player && m.get(i-1, j-1) == player && m.get(i-2,j-2) == player && m.get(i-3,j-3) == player && m.get(i-4,j-4) == player)
			{
				return true;
			}
		}
	}

	for (int i = 0; i < m.get_height()/2; i++)
	{
		for (int j = m.get_width() -1; j > m.get_width()/2; j--)
		{

			if (m.get(i, j) == player && m.get(i+1, j-1) == player && m.get(i+2,j-2) == player && m.get(i+3,j-3) == player && m.get(i+4,j-4) == player)
			{
				return true;
			}
		}
	}


	return false;
}

int main() {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!

	Matrix matrix;
	matrix.set_height(10);
	matrix.set_width(10);
	matrix.clear();
	matrix.print();

	bool playing = true;
	bool player1 = true;
	bool is_valid_move = false;

	while (playing)
	{
		if (player1)
		{
			is_valid_move = false;
			int x;
			int y;

			do
			{

				cout << "Player 1 please enter your move x: ";
				cin >> x;
				cout << "Player 1 please enter your move y: ";
				cin >> y;

				if (is_valid(x,y,matrix))
				{
					is_valid_move = true;
				}
				else
				{
					cout << "Invalid move.\n";
				}

			} while(!is_valid_move);

			cout << "Loaded values!\n";

			matrix.set(x, y, Field::PLAYER1);

			cout << "Set value in matrix!\n";
			matrix.print();

			if (is_winner(Field::PLAYER1, matrix))
			{
				cout << "CONGRATULATIONS PLAYER 1 WON!";
				playing = false;
			}
			else
			{
				player1 = false;
			}
		}
		else
		{
			is_valid_move = false;
			int x;
			int y;
			do
			{
				cout << "Player 2 please enter your move x: ";
				cin >> x;
				cout << "Player 2 please enter your move y: ";
				cin >> y;

				if (is_valid(x,y,matrix))
				{
					is_valid_move = true;
				}
				else
				{
					cout << "Invalid move.\n";
				}

			} while(!is_valid_move);

			matrix.set(x, y, Field::PLAYER2);
			matrix.print();
			if (is_winner(Field::PLAYER2, matrix))
			{
				cout << "CONGRATULATIONS PLAYER 2 WON!";
				playing = false;
			}
			else
			{
				player1 = true;
			}
		}
	}

	return 0;
}
