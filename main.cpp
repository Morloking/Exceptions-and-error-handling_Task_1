#include <iostream>
#include <string>
#include <exception>

#include <Windows.h>

class BadLength : //для соответствия код стилю решил переназвать, суть не меняет
	public std::exception {
public:
	explicit BadLength(const std::string& error) : message(error) {}
	const char* what() const noexcept override { return message.c_str(); }
private:
	std::string message{ "" };
};

int function(std::string str, int forbiddenLength) {
	if (str.size() == forbiddenLength) { throw BadLength("Вы ввели слово запретной длины! До свидания\n"); }
	else { return static_cast<int>(str.length()); }
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int forbiddenLength{ 0 }, currLength{ 0 };
	std::string word{ "" };
	std::cout << "Введите запретную длину: ";
	std::cin >> forbiddenLength;

	try {
		while (true) {
			std::cout << "Введите слово: ";
			std::cin >> word;
			currLength = function(word, forbiddenLength);
			std::cout << "Длина слова \"" << word << "\" равна " << currLength << "\n";
		}
	}
	catch (BadLength& ex) {
		std::cout << ex.what();
	}
	return 0;
}
