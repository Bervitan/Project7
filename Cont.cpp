#include<iostream>
#include<exception>
using namespace std;
class bad_lenght : public exception
{
public:
	virtual const char* what() const noexcept override
	{
		return "Lenght not can be 0!";
	}
};

 class bad_range : public exception
{
public:
	virtual const char* what() const noexcept override
	{
		return "Exit out of array!";
	}
};

class IntArray
{ private:
	int m_lenght{};
	int* m_data{};

public:
	IntArray() = default;
	IntArray(int lenght) : m_lenght(lenght)
	{
		if (lenght <= 0)
		{
			throw bad_lenght();
		}
		if (lenght > 0)
		{
			m_data = new int[lenght]{};
		}
	}

	

	~IntArray()
	{
		delete[] m_data;
		cout << "Cont distructed" << endl;             // Для проверки работы исключений из конструктора.
	}

	void erase()
	{
		delete[] m_data;
		m_data = nullptr;
		m_lenght = 0;

	}

	int& operator[](int index)
	{

		return  m_data[index];
	}

	

	void reallocate(int newLenght)
	{
		erase();
		if (newLenght <= 0)
			return;
		m_data = new int[newLenght];
		m_lenght = newLenght;
	}

	void resize(int newLenght)
	{
		if (newLenght == m_lenght)
			return;

		if (newLenght <= 0)
		{
			erase();
			return;
		}

		int* data{ new int[newLenght] };
		if (m_lenght > 0)
		{
			int elementsToCopy{ (newLenght > m_lenght) ? m_lenght : newLenght };
			for (int index{ 0 }; index < elementsToCopy; ++index)
				data[index] = m_data[index];
		}

		delete[] m_data;

		m_data = data;
		m_lenght = newLenght;
	}

	void insertBefore(int value, int index)
	{
		if (index < 0 || index > m_lenght)
		{
			throw bad_range();
		}

		int* data{ new int[m_lenght + 1] };

		for (int before{ 0 }; before < index; ++before)
			data[before] = m_data[before];

		data[index] = value;

		for (int after{ index }; after < m_lenght; ++after)
			data[after + 1] = m_data[after];

		delete[] m_data;
		m_data = data;
		++m_lenght;

	}

	void remove(int index)
	{
		if (index < 0 || index > m_lenght)
		{
			throw "BadIndexRemove";
		}

		if (m_lenght == 1)
		{
			erase();
			return;
		}

		int* data{ new int[m_lenght - 1] };

		for (int before{ 0 }; before < index; ++before)
			data[before] = m_data[before];

		for (int after{ index + 1 }; after < m_lenght; ++after)
			data[after - 1] = m_data[after];

		delete[] m_data;
		m_data = data;
		--m_lenght;
	}

	int getLenght() const { return m_lenght; }

	void insertAtBeginning(int value) { insertBefore(value, 0); }
	void insertAtEnd(int value) { insertBefore(value, m_lenght); }
	
	
};

int main()
{
	try
	{
		IntArray array(10);               // Массив из десяти целых чисел.
		for (int i{ 0 }; i < 10; ++i)
			array[i] = i + 1;
		array.resize(6);                // Изменение размера.
		array.insertBefore(20, 5);      // Вставка елемента.
		array.remove(2);                // Изъятие.
		array.insertAtEnd(30);          // Добавление в конец массива.
		array.insertAtBeginning(40);    // Добавление в начало.


		for (int i{ 0 }; i < array.getLenght(); ++i)
			cout << array[i] << ' ';
		cout << '\n';
		cout << array.getLenght() << endl;
	}
	catch (exception& e)
	{
		cout << e.what();
	}

	catch (const char* ex)
	{
		cout << "Exception:" << ex << endl;   // Для примера.
	}


	

	return 0;
}

