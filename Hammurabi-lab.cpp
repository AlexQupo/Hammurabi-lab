#include <iostream>
#include <cstdlib>
#include <ctime>
#include "windows.h"
#include <iomanip>
#include <string>
#include <fstream>
//#include <math.h>


class City {
private:
	int population_ = 100;
	int bushelOfWheat_ = 2800;
	int acresOfLand_ = 1000;
	/*
	 *Начальные значения:
	    В городе проживает 100 человек
	    В закромах города 2800 бушелей пшеницы
	    Город занимает 1000 акров земли
	*/
public:
	int getPopulation() const {
		return population_;
	}

	int getBushelOfWheat() const {
		return bushelOfWheat_;
	}

	int getAcresOfLand() const {
		return acresOfLand_;
	}

	void setPopulation(int value) {
		if (value < 0) {
			value = 0;
		}
		population_ = value;
	}

	void setBushelOfWheat(int value) {
		if (value < 0) {
			value = 0;
		}
		bushelOfWheat_ = value;
	}

	void setAcresOfLand(int value) {
		if (value < 0) {
			value = 0;
		}
		acresOfLand_ = value;
	}
};

class Round {
private:
	// Видимые данные для игрока
	int numOfRound_ = 0;//Номер раунда
	int amountOfDeadPeople_ = 0;//Умерло +
	int amountOfNewPeople_ = 0;//Приезжих +
	bool isPlague_ = false;//Чума +
	int currentPopulation_ = 0;//Текущее население +
	int amountOfWheatHarvested_ = 0;//Собрано пшеницы +
	int avgAmountOfWheatPerAcre_ = 0;//Получено за Акр
	int amountOfWheatDestroyByRats_ = 0;//Съедино крысами +
	int currentCitySize_ = 0;//Площадь города + 
	int pricePerAcreOfLandInRound_ = 0;//Цена акра земли в текущем году +
	//Скрытые данные от игрока
	City city_ = City();
	int currentbushelOfWheat = 0;
	std::string score_;
	int acresOfLandPurchased_ = 0;// Земли куплено
	int acresOfLandSold_ = 0;// Земли продано
	int wheatForFood_ = 0;// Количество пшеницы на еду
	int landForSowing_ = 0;// Количество пшеницы на посадку
	float coefficientOfDead_ = 0;//Коэф умерших за год
	bool isNewGame_ = false;
	float avgDeadPeople_ = 0;

	void UpdatePrice() {
		int minValue = 17;
		int widthValue = 26 - 17 + 1;
		pricePerAcreOfLandInRound_ = minValue + std::rand() % widthValue;
	}
	int SetRandomValueInRange(int minValue, int widthValue) {
		return minValue + std::rand() % widthValue;
	}
	int InputOfQuantity(std::string text, int min = 0, int max = INT_MAX) {
		int cost;
		for (;;) {
			std::cout << text << " Максимально значение: "<< max << "\n" << std::flush;
			if ((std::cin >> cost).good() && (min <= cost) && (cost <= max)) return cost;
			if (std::cin.fail()) {
				std::cin.clear();
				std::cout << "Введите количество в целочисленном эквиваленте.\n";
			}
			else {
				std::cout << "Вы ввели отрицательное число или больше, чем имеете.\n";
			}
			std::cin.ignore(100, '\n');
		}
	}

	void Input() {
		std::cout << "Что пожелаешь, повелитель?\n";

		int maxAvailableNumberOfAcresForPurchase = city_.getBushelOfWheat() / pricePerAcreOfLandInRound_; // доступной земли на покупку
		acresOfLandPurchased_ = InputOfQuantity("Сколько акров земли вы хотите купить?", 0, maxAvailableNumberOfAcresForPurchase);

		city_.setAcresOfLand(city_.getAcresOfLand() + acresOfLandPurchased_);
		city_.setBushelOfWheat(city_.getBushelOfWheat() - (acresOfLandPurchased_ * pricePerAcreOfLandInRound_));

		int maxAvailableNumberOfAcresForSell = city_.getAcresOfLand(); // доступной земли на продажу
		acresOfLandSold_ = InputOfQuantity("Сколько акров земли вы хотите продать?", 0, maxAvailableNumberOfAcresForSell);

		city_.setAcresOfLand(city_.getAcresOfLand() - acresOfLandSold_);
		city_.setBushelOfWheat(city_.getBushelOfWheat() + (acresOfLandSold_ * pricePerAcreOfLandInRound_));

		int maxAvailableNumberOfBushelOfWheat = city_.getBushelOfWheat(); // доступные бушелей пшеницы
		wheatForFood_ = InputOfQuantity("Сколько бушелей пшеницы вы хотите использовать в качестве еды?", 0, maxAvailableNumberOfBushelOfWheat);

		city_.setBushelOfWheat(city_.getBushelOfWheat() - wheatForFood_);

		float maxAvailableNumberOfSowAcresOfLand = static_cast<float>(city_.getPopulation()) * 10; // максимальное количество посадки акров по числу жителей
		int maxAvailableNumberOfWheatSeeds = static_cast<int>(maxAvailableNumberOfSowAcresOfLand * .5f); // максимальное число пшеницы для посадки максимального количества посадки акров по числу жителей
		if (maxAvailableNumberOfWheatSeeds >= city_.getBushelOfWheat()) {//Если требуемое число выше доступного, то берется доступное
			maxAvailableNumberOfWheatSeeds = city_.getBushelOfWheat();
		}
		landForSowing_ = InputOfQuantity("Сколько акров земли необходимо засеять пшеницей?", 0, maxAvailableNumberOfWheatSeeds);
		city_.setBushelOfWheat(city_.getBushelOfWheat() - landForSowing_);
		std::cout << std::endl << std::endl;
	}

	void BeginningAfterSave() {
		std::cout << "С возвращением в игру, повелитель!" << std::endl;
		std::cout << "Позвольте напомнить Вам о состоянии Ваших владений:" << std::endl;
		std::cout << "Население: " << city_.getPopulation() << std::endl;
		std::cout << "Бушелей пшеницы: " << city_.getBushelOfWheat() << std::endl;
		std::cout << "Акров земли: " << city_.getAcresOfLand() << std::endl;
		std::cout << "Цена за один акр земли: " << pricePerAcreOfLandInRound_ << std::endl;
		std::cout << std::endl;

		Input();
		End();
	}

	void Beginning() {// Новости, ввод пользователя, подсчет итогов
		numOfRound_++;
		UpdatePrice();
		Save();
		if (isNewGame_) {
			std::cout << "Повелитель, это твой первый год правления. Поздравляю вас. \nТекущая цена за один АКР земли равна - " << pricePerAcreOfLandInRound_ << std::endl;
		}
		else {
			std::cout << "Мой повелитель, соизволь поведать тебе\n";
			std::cout << "\t" << "в году " << numOfRound_ << " твоего высочайшего правления\n";
			std::cout << "\t\t" << amountOfDeadPeople_ << " человек умерли с голоду, и " << amountOfNewPeople_ << " прибыли в наш великий город;\n";
			if (isPlague_) {
				std::cout << "\t\t" << "Чума уничтожила половину населения;\n";
			}
			std::cout << "\t\t" << "Население города сейчас составляет " << city_.getPopulation() << " человек;\n";
			std::cout << "\t\t" << "Мы собрали " << amountOfWheatHarvested_ << " пшеницы, по " << avgAmountOfWheatPerAcre_ << " бушеля с акра;\n";
			std::cout << "\t\t" << "Крысы истребили " << amountOfWheatDestroyByRats_ << " бушелей пшеницы, оставив " << city_.getBushelOfWheat() << " бушеля в амбарах;\n";
			std::cout << "\t\t" << "Город сейчас занимает " << city_.getAcresOfLand() << " акров;\n";
			std::cout << "\t\t" << "1 акр земли стоит сейчас " << pricePerAcreOfLandInRound_ << " бушель.\n";
		}

		Input();
		End();
	}

	void End() { // Основная логика перед началом следующего раунда

		//Сбор урожая
		avgAmountOfWheatPerAcre_ = SetRandomValueInRange(1, 6);
		amountOfWheatHarvested_ = landForSowing_ * avgAmountOfWheatPerAcre_;
		city_.setBushelOfWheat(city_.getBushelOfWheat() + amountOfWheatHarvested_);

		//Поело крысами
		float endNumberForRandom = 0.07f * static_cast<float>(city_.getBushelOfWheat());
		endNumberForRandom = std::round(endNumberForRandom);
		if (endNumberForRandom != 0) {
			amountOfWheatDestroyByRats_ = SetRandomValueInRange(0, static_cast<int>(endNumberForRandom));
		}
		else {
			amountOfWheatDestroyByRats_ = 0;
		}
		city_.setBushelOfWheat(city_.getBushelOfWheat() - amountOfWheatDestroyByRats_);

		//Потребили жители, умерло 
		int tempPopulation = city_.getPopulation();
		//city_.setBushelOfWheat(city_.getBushelOfWheat() - wheatForFood_);
		int providesResidents = wheatForFood_ / 20;
		if (providesResidents < city_.getPopulation()) {
			amountOfDeadPeople_ = city_.getPopulation() - providesResidents;
		}
		else {
			amountOfDeadPeople_ = 0;
		}
		city_.setPopulation(city_.getPopulation() - amountOfDeadPeople_);

		//Подсчет населения
		coefficientOfDead_ = static_cast<float>(amountOfDeadPeople_) / static_cast<float>(tempPopulation);
		if (coefficientOfDead_ >= 0.45f) {
			Defeat();
			return;
		}
		avgDeadPeople_ += coefficientOfDead_;

		//Приезжих
		amountOfNewPeople_ = amountOfDeadPeople_ / 2 + (5 - avgAmountOfWheatPerAcre_) * city_.getBushelOfWheat() / 600 + 1;
		if (amountOfNewPeople_ < 0) {
			amountOfNewPeople_ = 0;
		}
		else if (amountOfNewPeople_ > 50) {
			amountOfNewPeople_ = 50;
		}
		city_.setPopulation(city_.getPopulation() + amountOfNewPeople_);

		//Чума 15% = 15/100
		int dice = SetRandomValueInRange(1, 100);
		if (dice <= 15) {
			isPlague_ = true;
			city_.setPopulation(city_.getPopulation() / 2);
		}
		else {
			isPlague_ = false;
		}
		Save();
		Next();
	}

	void Next() {
		isNewGame_ = false;
		if (numOfRound_ == 10) {
			Result();
		}
		else {
			Beginning();
		}
	}

	void Result() {
		avgDeadPeople_ = avgDeadPeople_ / numOfRound_;
		float amountAcresOfLandOnPerson = static_cast<float>(city_.getAcresOfLand()) / static_cast<float>(city_.getPopulation());

		if (avgDeadPeople_ > 0.33f && amountAcresOfLandOnPerson < 7) {
			score_ = "Плохо";
			std::cout << "Из-за вашей некомпетентности в управлении, народ устроил бунт, и изгнал вас их города.Теперь вы вынуждены влачить жалкое существование в изгнании";
		}

		else if (avgDeadPeople_ > 0.10f && amountAcresOfLandOnPerson < 9) {
			score_ = "Удовлетворительно";
			std::cout << "Вы правили железной рукой, подобно Нерону и Ивану Грозному.Народ вздохнул с облегчением, и никто больше не желает видеть вас правителем";
		}

		else if (avgDeadPeople_ > 0.3f && amountAcresOfLandOnPerson < 10) {
			score_ = "Хорошо";
			std::cout << "Вы справились вполне неплохо, у вас, конечно, есть недоброжелатели, но многие хотели бы увидеть вас во главе города снова";
		}

		else {
			score_ = "Отлично";
			std::cout << "Фантастика! Карл Великий, Дизраэли и Джефферсон вместе не справились бы лучше";
		}
		std::cout << std::endl;
		std::cout << "Ваша оценка: " << score_ << std::endl;
	}

	void Defeat() {
		std::cout << "Вы проиграли!" << std::endl;
	}

	std::string GetData() const {

		return std::to_string(numOfRound_) + '\n'
			+ std::to_string(city_.getPopulation()) + '\n'
			+ std::to_string(city_.getBushelOfWheat()) + '\n'
			+ std::to_string(city_.getAcresOfLand()) + '\n'
			+ std::to_string(pricePerAcreOfLandInRound_) + '\n'
			+ std::to_string(avgDeadPeople_);
	}

	void SetData(int numOfRound, int population, int bushelOfWheat, int acresOfLand, int price, float coefOfDead) {

		numOfRound_ = numOfRound;
		city_.setPopulation(population);
		city_.setBushelOfWheat(bushelOfWheat);
		city_.setAcresOfLand(acresOfLand);
		pricePerAcreOfLandInRound_ = price;
		coefficientOfDead_ = coefOfDead;
	}

	std::string GetNumOfRound() const {
		return std::to_string(numOfRound_);
	}

	void Save() {
		std::ofstream saveFile;
		saveFile.open("save.txt");
		if (!saveFile.is_open()) {
			std::cout << "Не удалось открыть файл!" << std::endl;
		}
		else {
			saveFile << GetData();
		}
		saveFile.close();
	}

public:
	void New() {
		city_ = City();
		numOfRound_ = 0;

		std::cout << "Добро пожаловать в игру Хаммурапи!" << std::endl;
		std::cout << "Вы начинаете игру с:" << std::endl;
		std::cout << "Население: " << city_.getPopulation() << std::endl;
		std::cout << "Бушелей пшеницы: " << city_.getBushelOfWheat() << std::endl;
		std::cout << "Акров земли: " << city_.getAcresOfLand() << std::endl;
		std::cout << std::endl;

		Sleep(1500);

		std::cout << "Да начнется игра!" << std::endl;
		std::cout << std::endl;
		isNewGame_ = true;

		Sleep(750);
		Beginning();
	}

	void Resume() {
		std::ifstream openFile;
		openFile.open("save.txt");
		if (!openFile.is_open()) {
			std::cout << "Не удалось открыть файл!" << std::endl;
		}
		else {
			std::string str;
			std::string line;

			while (!openFile.eof()) {
				openFile >> line;
				str.append(line);
				str.append("\n");
			}

			int n = 0;
			int num = 0;
			int popul = 0;
			int bush = 0;
			int acr = 0;
			int price = 0;
			float coef = 0;
			std::string endl = "\n";

			n = static_cast<int>(str.find_first_of(endl));
			n++;
			num = std::stoi(str.substr(0, n));
			str.erase(0, n);
			n = static_cast<int>(str.find_first_of(endl));
			popul = std::stoi(str.substr(0, n));
			n++;
			str.erase(0, n);
			n = static_cast<int>(str.find_first_of(endl));
			bush = std::stoi(str.substr(0, n));
			n++;
			str.erase(0, n);
			n = static_cast<int>(str.find_first_of(endl));
			acr = std::stoi(str.substr(0, n));
			n++;
			str.erase(0, n);
			n = static_cast<int>(str.find_first_of(endl));
			price = std::stoi(str.substr(0, n));
			n++;
			str.erase(0, n);
			coef = std::stof(str);
			str = "";

			SetData(num, popul, bush, acr, price, coef);
			BeginningAfterSave();
		}
		openFile.close();
	}


};

class Game {
private:
	Round rnd = Round();

public:
	void New() {
		rnd = Round();
		rnd.New();
	}

	void Start() {
		std::ifstream openFile;
		openFile.open("save.txt");
		if (!openFile.is_open()) {
			New();
		}
		else {
			std::cout << "Был обнаружен сейв. \n1. Продолжить с текущего года правления \n2. Начать заново" << std::endl;
			std::string answer;
			std::cin >> answer;
			if (answer == "1") {
				system("cls");
				rnd.Resume();
			}
			else if (answer == "2") {
				system("cls");
				rnd.New();
			}
		}
	}
};

int main() {
	setlocale(LC_ALL, "Russian");
	std::srand(time(0));

	Game session = Game();
	session.Start();
}