// EgyptRuler.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <string>
#include <random>


// Константы

constexpr int kYears = 10;

constexpr int kPopulation = 100;
constexpr int kLand = 1000;
constexpr int kFood = 2800;

constexpr int kPopulationFoodConsumption = 20;
constexpr int kLandPerPerson = 10;
constexpr float kFoodToGrow = 0.5f;

constexpr int kMinLandPrice = 17;
constexpr int kMaxLandPrice = 26;
constexpr int kMinFoodGet = 1;
constexpr int kMaxFoodGet = 6;

constexpr int kPlaugeChancePercent = 15;
constexpr float kMaxRatDestruction = 0.07f;

constexpr float kPeopleDiedToLose = 0.45f;

constexpr char kSaveFileName[] = "save.dat";


// Переменные

int year;

int population;
int food;
int land;

int landPrice;
int foodGet;

int diedLastRound;
int arrivedLastRound;
bool plagueWasLastRound;
int foodCollectedLastRound;
int landPriceLastRound;
int foodGetLastRound;

int foodDestroyedByRats;

int foodToEat;
int landToGrow;

int diedOverall;



// Список функций

void new_game();

void get_input();
int get_input_int();

void turn(std::default_random_engine rndEngine_);

void display_info();
void display_score();

void save_game();
void load_game();
bool save_exists();



// Функции

void new_game()
{
	std::cout << "\n                                      Начало новой игры!                                     \n\n\n";

	year = 0;

	population = kPopulation;
	food = kFood;
	land = kLand;

	//landPrice;
	//foodGet;

	diedLastRound = 0;
	arrivedLastRound = 0;
	plagueWasLastRound = false;
	foodCollectedLastRound = 0;
	landPriceLastRound = 0;

	foodDestroyedByRats = 0;

	foodToEat = 0;
	landToGrow = 0;

	diedOverall = 0;

	std::cout << "Мой повелитель, соизволь поведать тебе о состоянии дел на начало твоего высочайшего правления" << std::endl;
	std::cout << "\tНаселение города сейчас составляет " << population << " человек;" << std::endl <<
		"\tСейчас у нас " << food << " бушелей пшеницы в амбарах;" << std::endl <<
		"\tГород сейчас занимает " << land << " акров;" << std::endl <<
		"\t1 акр земли стоит сейчас " << landPrice << " бушелей." << std::endl;
}

int get_input_int()
{
	std::string input = "";
	int output = INT32_MIN;
	do
	{
		std::cin >> input;
		try
		{
			output = std::stoi(input);
		}
		catch (std::invalid_argument const& ex)
		{
			std::cout << "Введите число." << std::endl;
		}
		catch (std::out_of_range const& ex)
		{
			std::cout << "Введите число из корректного диапазона." << std::endl;
		}
		if (output < 0)
			std::cout << "Введите неотрицательное число." << std::endl;
	} while (output < 0);
	return output;
}

void get_input()
{
	std::cout << "\nЧто пожелаешь, повелитель?" << std::endl;
	int buyInput = 0;
	int sellInput = 0;
	int eatInput = 0;
	int growInput = 0;

	while (true)
	{
		std::cout << "Сколько акров земли повелеваешь купить? ";
		buyInput = get_input_int();
		std::cout << "Сколько акров земли повелеваешь продать? ";
		sellInput = get_input_int();
		std::cout << "Сколько бушелей пшеницы повелеваешь съесть? ";
		eatInput = get_input_int();
		std::cout << "Сколько акров земли повелеваешь засеять? ";
		growInput = get_input_int();


		if (food - (buyInput - sellInput) * landPrice - eatInput - ceil(growInput * kFoodToGrow) > 0 && growInput <= kLandPerPerson * population && land >= growInput && (land + buyInput - sellInput) > 0)
			break;
		std::cout << "О повелитель, пощади нас! У нас лишь " << population << " человек, " << food << " бушелей пшеницы и " << land << " акров земли!" << std::endl;
	}

	land += buyInput - sellInput;
	food -= (buyInput - sellInput) * landPrice + ceil(growInput * kFoodToGrow);
	landToGrow = growInput;
	foodToEat = eatInput;
	std::cout << "\n";
}

void turn(std::default_random_engine rndEngine_)
{
	foodCollectedLastRound = foodGetLastRound * landToGrow;
	food += foodCollectedLastRound;
	food -= foodToEat;

	std::uniform_int_distribution<int> ratDist(0, round(kMaxRatDestruction * food));
	foodDestroyedByRats = ratDist(rndEngine_);

	if (foodDestroyedByRats > food)
		foodDestroyedByRats = food;

	food -= foodDestroyedByRats;


	if (foodToEat >= population * kPopulationFoodConsumption)
		diedLastRound = 0;
	else
		diedLastRound = population - foodToEat / kPopulationFoodConsumption;

	population -= diedLastRound;

	arrivedLastRound = diedLastRound / 2 + (5 - foodGetLastRound) * food / 600 + 1;


	if (arrivedLastRound < 0)
		arrivedLastRound = 0;

	if (arrivedLastRound > 50)
		arrivedLastRound = 50;

	population += arrivedLastRound;


	if (plagueWasLastRound)
		population = population / 2;
}

void display_info()
{
	std::cout << "Мой повелитель, соизволь поведать тебе" << std::endl <<
		"\tв году " << year << " твоего высочайшего правления" << std::endl;

	if (diedLastRound > 0)
	{
		std::cout << "\t" << diedLastRound << " человек умерли с голоду";
		if (arrivedLastRound > 0)
			std::cout << ", и " << arrivedLastRound << " человек прибыли в наш великий город";
	}
	else if (arrivedLastRound > 0)
		std::cout << "\t" << arrivedLastRound << " человек прибыли в наш великий город";

	if (diedLastRound > 0 || arrivedLastRound > 0)
		std::cout << ";" << std::endl;

	if (plagueWasLastRound)
		std::cout << "\tЧума уничтожила половину населения;" << std::endl;

	std::cout << "\tНаселение города сейчас составляет " << population << " человек;" << std::endl <<
		"\tМы собрали " << foodCollectedLastRound << " бушелей пшеницы, по " << foodGetLastRound << " бушелей с акра;" << std::endl <<
		"\tКрысы истребили " << foodDestroyedByRats << " бушелей пшеницы, оставив " << food << " бушелей в амбарах;" << std::endl <<
		"\tГород сейчас занимает " << land << " акров;" << std::endl <<
		"\t1 акр земли стоит сейчас " << landPrice << " бушелей.\n" << std::endl;
}

void display_score()
{
	float p = 1.0f * diedOverall / kYears;
	int l = land / population;

	std::cout << "Итак, 10 лет твоего высочайшего правления подошли к концу. Результат:" << std::endl;

	std::cout << "\nЧасть населения, умершая от голода: " << p << "\n" << "Акров земли на одного жителя: " << l << "\n\n";

	if (p > 0.33f && l < 7)
		std::cout << "Из-за вашей некомпетентности в управлении народ устроил бунт, и изгнал вас их города. Теперь вы вынуждены влачить жалкое существование в изгнании." << std::endl;
	else if ((p > 0.10f && l < 9) || l < 7 || p > 0.33f)
		std::cout << "Вы правили железной рукой, подобно Нерону и Ивану Грозному. Народ вздохнул с облегчением, и никто больше не желает видеть вас правителем." << std::endl;
	else if ((p > 0.03f && l < 10) || l < 9 || p > 0.10f)
		std::cout << "Вы справились вполне неплохо. У вас, конечно, есть недоброжелатели, но многие хотели бы увидеть вас во главе города снова." << std::endl;
	else
		std::cout << "Фантастика! Карл Великий, Дизраэли и Джефферсон вместе не справились бы лучше!" << std::endl;

}

void save_game()
{
	std::string s = "";
	s.append(std::to_string(year));
	s.append("\n");

	s.append(std::to_string(population));
	s.append("\n");
	s.append(std::to_string(food));
	s.append("\n");
	s.append(std::to_string(land));
	s.append("\n");

	s.append(std::to_string(landPrice));
	s.append("\n");

	s.append(std::to_string(diedLastRound));
	s.append("\n");
	s.append(std::to_string(arrivedLastRound));
	s.append("\n");
	s.append(std::to_string(plagueWasLastRound));
	s.append("\n");
	s.append(std::to_string(foodCollectedLastRound));
	s.append("\n");
	s.append(std::to_string(landPriceLastRound));
	s.append("\n");
	s.append(std::to_string(foodGetLastRound));
	s.append("\n");

	s.append(std::to_string(foodDestroyedByRats));
	s.append("\n");

	s.append(std::to_string(landToGrow));
	s.append("\n");

	s.append(std::to_string(foodToEat));
	s.append("\n");

	s.append(std::to_string(diedOverall));
	s.append("\n");

	std::fstream f;
	f.open(kSaveFileName, std::fstream::out);
	f.write(s.c_str(), s.size());
	f.close();
}

void load_game()
{
	std::fstream f;
	f.open(kSaveFileName, std::fstream::in);

	std::string s;
	std::getline(f, s);
	year = std::stoi(s);

	std::getline(f, s);
	population = std::stoi(s);

	std::getline(f, s);
	food = std::stoi(s);

	std::getline(f, s);
	land = std::stoi(s);


	std::getline(f, s);
	landPrice = std::stoi(s);


	std::getline(f, s);
	diedLastRound = std::stoi(s);

	std::getline(f, s);
	arrivedLastRound = std::stoi(s);

	std::getline(f, s);
	plagueWasLastRound = std::stoi(s);

	std::getline(f, s);
	foodCollectedLastRound = std::stoi(s);

	std::getline(f, s);
	landPriceLastRound = std::stoi(s);

	std::getline(f, s);
	foodGetLastRound = std::stoi(s);

	
	std::getline(f, s);
	foodDestroyedByRats = std::stoi(s);


	std::getline(f, s);
	landToGrow = std::stoi(s);

	std::getline(f, s);
	foodToEat = std::stoi(s);


	std::getline(f, s);
	diedOverall = std::stoi(s);


	f.close();
}

bool save_exists()
{
	std::ifstream sFile(kSaveFileName);
	return sFile.good();
}



// Игра

int main()
{
	setlocale(LC_ALL, "Russian");

	std::random_device rndDevice;
	std::default_random_engine rndEngine(rndDevice());
	std::uniform_int_distribution<int> landPriceDist(kMinLandPrice, kMaxLandPrice);
	std::uniform_int_distribution<int> foodGetDist(kMinFoodGet, kMaxFoodGet);
	std::uniform_int_distribution<int> plaugeDist(1, 100);


	// Запуск игры

	std::cout << "\n==============================  П Р А В И Т Е Л Ь   Е Г И П Т А  ==============================\n";
	std::cout << "\n                                   Добро пожаловать в игру!                                    \n\n";

	// Загрузка игры при наличии сохранения

	if (save_exists())
	{
		std::cout << "У вас есть сохраненная игра. Продолжить её? (y/n) ";
		if (std::cin.get() == 'y')
		{
			std::cout << "\n";
			load_game();
			display_info();
			get_input();
		}
		else
		{
			std::cout << "\n";
			landPrice = landPriceDist(rndEngine);
			new_game();
			get_input();
		}
	}
	else
	{
		std::cout << "\n";
		landPrice = landPriceDist(rndEngine);
		new_game();
		get_input();
	}


	// Флаги

	bool successFlag = true;
	bool exitFlag = false;


	// Игровой цикл

	while (year < kYears)
	{
		year++;
		foodGetLastRound = foodGetDist(rndEngine);
		plagueWasLastRound = (plaugeDist(rndEngine) > kPlaugeChancePercent ? false : true);

		int populationBackup = population;

		turn(rndEngine);


		if (1.0f * diedLastRound / populationBackup > kPeopleDiedToLose || population <= 0)
		{
			successFlag = false;
			break;
		}

		landPrice = landPriceDist(rndEngine);

		display_info();
		save_game();

		std::cout << "Игра сохранена. Хотите продолжть? (y/n) ";
		std::cin.clear();

		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		if (std::cin.get() == 'n')
		{
			exitFlag = true;
			break;
		}
		get_input();
	}


	// Конец игры

	if (!exitFlag)
	{
		if (successFlag)
		{
			display_score();
		}
		else
		{

			std::cout << "В результате ваших решений значительная часть населения умерла от голода.\n";
			std::cout << "\nИгра окончена. Из-за вашей некомпетентности в управлении народ устроил бунт, и изгнал вас их города. Теперь вы вынуждены влачить жалкое существование в изгнании.\n";
		}

		std::cout << "\n\n**************************************************************************************************\n\n";
		std::system("pause");
	}

	return 0;
}