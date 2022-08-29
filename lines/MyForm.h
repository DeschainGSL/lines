#pragma once
#include <ctime>
#include<cstdlib>
#include<vector>


bool selected = false;  //выделена ячейка, или нет
bool deleted;           //было ли удаление шариков
int score;              //игровой счет
const int i = 10;       //размеры игрового поля
const int j = 10;
int field[i][j];        //массив игрового поля
int way_field[i][j];    //вспомогательный массив для поиска пути (0 - свободна, 1 - занята\проверена, 2 - цель)
int tmpN, tmpM;         //координаты выделенного шарика
int tmpColor;           //цвет выделенного шарика
std::vector<int> add;   //массив с индексами свободных элементов
std::vector<int> clr;   //массив с индексами элементов на удаление

void search_empty()     //процедура поиска и сохранения пустых ячеек
{
	add.clear();                 //очистка массива с пустыми ячейками

	for (int n = 0; n < 10; n++) //проход по всему полю, индексы пустых ячеек добавляются в массив add[]
	{
		for (int m = 0; m < 10; m++)
		{
			if (field[n][m] == 0)
			{
				add.push_back(n * 10 + m);   //заполнение массива с пустыми ячейками координатами пустых ячеек в формате XY
			}
		}
	}
}

void add_new(int count)      //процедура добавления count шариков на поле 
{
	for (int k = 0; k < count; k++) //выбор из списка пустых ячеек случайной, добавление стартовых шариков, удаление ячеек из списка пустых
	{
		int pos = 0;
		int n = 0;
		int m = 0;
		pos = (rand() % add.size());
		n = add[pos] / 10;
		m = add[pos] % 10;
		add.erase(add.begin() + pos);
		field[n][m] = 1 + rand() % 7; //7 цветов
	}
}

bool check_way(int n, int m)  //функция проверки наличия пути. n,m - координаты перемещаемого шарика
{
	way_field[n][m] = 1;      //текущая клетка - проверена

	if ((n != 0) && (n != 9) && (m != 0) && (m != 9))   //если текущая клетка находится не на краю поля
	{
		if (way_field[n + 1][m] == 2) return true;  //если цель достигнута
		if (way_field[n][m + 1] == 2) return true;
		if (way_field[n - 1][m] == 2) return true;
		if (way_field[n][m - 1] == 2) return true;

		if (way_field[n + 1][m] == 0)
		{
			if ((check_way(n + 1, m))) return true;
		}
		if (way_field[n][m + 1] == 0)
		{
			if ((check_way(n, m + 1))) return true;
		}
		if (way_field[n - 1][m] == 0)
		{
			if ((check_way(n - 1, m))) return true;
		}
		if (way_field[n][m - 1] == 0)
		{
			if ((check_way(n, m - 1))) return true;
		}
	}

	if ((n == 0) && (m == 0))   //если текущая клетка находится в левом верхнем углу (1)
	{
		if (way_field[n + 1][m] == 2) return true;  //если цель достигнута
		if (way_field[n][m + 1] == 2) return true;
		

		if (way_field[n + 1][m] == 0)
		{
			if ((check_way(n + 1, m))) return true;
		}
		if (way_field[n][m + 1] == 0)
		{
			if ((check_way(n, m + 1))) return true;
		}
	}

	if ((n == 0) && (m != 0) && (m != 9))   //если текущая клетка находится на верхнем краю (2)
	{
		if (way_field[n + 1][m] == 2) return true;  //если цель достигнута
		if (way_field[n][m + 1] == 2) return true;
		if (way_field[n][m - 1] == 2) return true;

		if (way_field[n + 1][m] == 0)
		{
			if ((check_way(n + 1, m))) return true;
		}
		if (way_field[n][m + 1] == 0)
		{
			if ((check_way(n, m + 1))) return true;
		}
		if (way_field[n][m - 1] == 0)
		{
			if ((check_way(n, m - 1))) return true;
		}
	}

	if ((n == 0) && (m == 9))   //если текущая клетка находится в правом верхнем углу (3)
	{
		if (way_field[n + 1][m] == 2) return true;  //если цель достигнута
		if (way_field[n][m - 1] == 2) return true;

		if (way_field[n + 1][m] == 0)
		{
			if ((check_way(n + 1, m))) return true;
		}
		if (way_field[n][m - 1] == 0)
		{
			if ((check_way(n, m - 1))) return true;
		}
	}

	if ((m == 0) && (n != 0) && (n != 9))   //если текущая клетка находится на левом краю (4)
	{
		if (way_field[n + 1][m] == 2) return true;  //если цель достигнута
		if (way_field[n - 1][m] == 2) return true;
		if (way_field[n][m + 1] == 2) return true;

		if (way_field[n + 1][m] == 0)
		{
			if ((check_way(n + 1, m))) return true;
		}
		if (way_field[n - 1][m] == 0)
		{
			if ((check_way(n - 1, m))) return true;
		}
		if (way_field[n][m + 1] == 0)
		{
			if ((check_way(n, m + 1))) return true;
		}
	}

	if ((m == 9) && (n != 0) && (n != 9))   //если текущая клетка находится на правом краю (5)
	{
		if (way_field[n + 1][m] == 2) return true;  //если цель достигнута
		if (way_field[n - 1][m] == 2) return true;
		if (way_field[n][m - 1] == 2) return true;

		if (way_field[n + 1][m] == 0)
		{
			if ((check_way(n + 1, m))) return true;
		}
		if (way_field[n - 1][m] == 0)
		{
			if ((check_way(n - 1, m))) return true;
		}
		if (way_field[n][m - 1] == 0)
		{
			if ((check_way(n, m - 1))) return true;
		}
	}

	if ((n == 9) && (m == 0))   //если текущая клетка находится в левом нижнем углу (6)
	{
		if (way_field[n][m + 1] == 2) return true;  //если цель достигнута
		if (way_field[n - 1][m] == 2) return true;

		if (way_field[n][m + 1] == 0)
		{
			if ((check_way(n, m + 1))) return true;
		}
		if (way_field[n - 1][m] == 0)
		{
			if ((check_way(n - 1, m))) return true;
		}
	}

	if ((n == 9) && (m != 0) && (m != 9))   //если текущая клетка находится на нижнем краю (7)
	{
		if (way_field[n][m + 1] == 2) return true;  //если цель достигнута
		if (way_field[n - 1][m] == 2) return true;
		if (way_field[n][m - 1] == 2) return true;

		if (way_field[n][m + 1] == 0)
		{
			if ((check_way(n, m + 1))) return true;
		}
		if (way_field[n - 1][m] == 0)
		{
			if ((check_way(n - 1, m))) return true;
		}
		if (way_field[n][m - 1] == 0)
		{
			if ((check_way(n, m - 1))) return true;
		}
	}
	
	if ((n == 9) && (m == 9))         //если текущая клетка находится в правом нижнем углу (8)
	{
		if (way_field[n - 1][m] == 2) return true;  // если цель достигнута
		if (way_field[n][m - 1] == 2) return true;

		if (way_field[n - 1][m] == 0)
		{
			if ((check_way(n - 1, m))) return true;
		}
		if (way_field[n][m - 1] == 0)
		{
			if ((check_way(n, m - 1))) return true;
		}
	}
}

void delete_ball()   //процедура удаления шаров
{
	for (int n = 0; n < 10; n++)  //удаление шара в строках
	{
		clr.clear();   //очистка массива с индексами стоящих рядом шаров
		for (int m = 0; m < 10; m++)
		{
			clr.push_back(n * 10 + m);   //добавление в массив исходного шара
			if ((field[n][m] == field[n][m + 1]) && (field[n][m] !=0))   //если следующий шар такой же, как текущий
			{
				continue;
			}
			else   //если цепь одинаковых шаров закончилась
			{
				if (clr.size() > 4)   //если шаров в массиве больше 4
				{
					score += clr.size()*clr.size();
					for (int k = 0; k < clr.size(); k++)
					{
						field[clr[k] / 10][clr[k] % 10] = 0;   //очистка соответствующих ячеек поля
					}
					deleted = true;
				}
				clr.clear();
			}
		}
	}

	for (int m = 0; m < 10; m++)  //удаление шара в столбцах
	{
		clr.clear();   //очистка массива с индексами стоящих рядом шаров
		for (int n = 0; n < 10; n++)
		{
			clr.push_back(n * 10 + m);
			if ((field[n][m] == field[n + 1][m]) && (field[n][m] != 0))   //если следующий шар такой же, как текущий
			{
				continue;
			}
			else   //если цепь одинаковых шаров закончилась
			{
				if (clr.size() > 4)
				{
					score += clr.size()*clr.size();
					for (int k = 0; k < clr.size(); k++)
					{
						field[clr[k] / 10][clr[k] % 10] = 0;   //очистка соответствующих ячеек поля
					}
					deleted = true;
				}
				clr.clear();
			}
		}
	}

	for (int n = 0;  n < 10; n++)  //главная диагональ, движение - вправо
	{
		clr.clear();
		for (int m = 0; m < 10; m++)
		{
			clr.push_back(m * 10 + (m+n));
			if ((field[m][m+n] == field[m+1][m+n+1]) && (field[m][m+n] != 0))
			{
				continue;
			}
			else
			{
				if (clr.size() > 4)
				{
					score += clr.size()*clr.size();
					for (int k = 0; k < clr.size(); k++)
					{
						field[clr[k] / 10][clr[k] % 10] = 0;
					}
					deleted = true;
				}
				clr.clear();
			}
		}
	}

	for (int n = 0; n < 10; n++)  //главная диагональ, движение - влево
	{
		clr.clear();
		for (int m = 0; m < 10; m++)
		{
			//clr.push_back(m * 10 + (m + n));
			clr.push_back((n + m) * 10 + m);
			if ((field[n + m][m] == field[n + m + 1][m + 1]) && (field[n + m][m] != 0))
			{
				continue;
			}
			else
			{
				if (clr.size() > 4)
				{
					score += clr.size()*clr.size();
					for (int k = 0; k < clr.size(); k++)
					{
						field[clr[k] / 10][clr[k] % 10] = 0;
					}
					deleted = true;
				}
				clr.clear();
			}
		}
	}

	for (int n = 9; n < 19; n++)  //побочная диагональ, движение - вправо
	{
		clr.clear();
		for (int m = 0; m < 10; m++)
		{
			clr.push_back(m * 10 + (n - m));
			if ((field[m][n - m] == field[m + 1][n - m - 1]) && (field[m][n - m] != 0))
			{
				continue;
			}
			else
			{
				if (clr.size() > 4)
				{
					score += clr.size()*clr.size();
					for (int k = 0; k < clr.size(); k++)
					{
						field[clr[k] / 10][clr[k] % 10] = 0;
					}
					deleted = true;
				}
				clr.clear();
			}
		}
	}

	for (int n = 9; n >= 0; n--)  //побочная диагональ, движение - влево
	{
		clr.clear();
		for (int m = 0; m < 10; m++)
		{
			clr.push_back(m * 10 + (n - m));
			if ((field[m][n - m] == field[m + 1][n - m - 1]) && (field[m][n - m] != 0))
			{
				continue;
			}
			else
			{
				if (clr.size() > 4)
				{
					score += clr.size()*clr.size();
					for (int k = 0; k < clr.size(); k++)
					{
						field[clr[k] / 10][clr[k] % 10] = 0;
					}
					deleted = true;
				}
				clr.clear();
			}
		}
	}
}

namespace lines {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	public: System::Windows::Forms::Button^  button1;
	private:

	private: System::Windows::Forms::Label^  label1;
	public: System::Windows::Forms::Label^  label2;
	public: System::Windows::Forms::Label^  label3;
	private:

	private:

	protected:

	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// pictureBox1
			// 
			this->pictureBox1->BackColor = System::Drawing::SystemColors::InactiveBorder;
			this->pictureBox1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->pictureBox1->Location = System::Drawing::Point(0, 0);
			this->pictureBox1->MinimumSize = System::Drawing::Size(600, 600);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(600, 600);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::AutoSize;
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::pictureBox1_MouseClick);
			// 
			// button1
			// 
			this->button1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button1->Location = System::Drawing::Point(626, 12);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(151, 68);
			this->button1->TabIndex = 1;
			this->button1->Text = L"Старт";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// label1
			// 
			this->label1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Calibri", 16, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label1->Location = System::Drawing::Point(637, 192);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(86, 39);
			this->label1->TabIndex = 2;
			this->label1->Text = L"Счет:";
			// 
			// label2
			// 
			this->label2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label2->Location = System::Drawing::Point(638, 250);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(0, 32);
			this->label2->TabIndex = 3;
			// 
			// label3
			// 
			this->label3->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label3->Location = System::Drawing::Point(606, 322);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(0, 30);
			this->label3->TabIndex = 4;
			// 
			// MyForm
			// 
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Inherit;
			this->BackColor = System::Drawing::SystemColors::InactiveBorder;
			this->ClientSize = System::Drawing::Size(823, 616);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->pictureBox1);
			this->MinimumSize = System::Drawing::Size(845, 672);
			this->Name = L"MyForm";
			this->Text = L"Lines Game";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

		Graphics ^Gr;   //создание графики
	private: System::Void MyForm_Load(System::Object^  sender, System::EventArgs^  e) {
		Gr = pictureBox1->CreateGraphics();
	}

//========================================== обработка событий кнопки старт - рестарт ========================================

	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
		srand(time(0));
		selected = false;
		for (int n = 0; n < 10; n++)  //заполнение массива поля нулями (пустая клетка)
		{
			for (int m = 0; m < 10; m++)
			{
				field[n][m] = 0;
			}
		}
		search_empty();
		
		add_new(5);
		score = 0;
		label2->Text = (System::Convert::ToString(score));
		button1->Text = "Рестарт";
		label3->Text = "";

		Gr->Clear(Color::White);     //очистка поля после нажатия на кнопку

		for (int i = 0; i < 600; i = i + 60)   //разметка поля
		{
			Gr->DrawLine(Pens::Black, i, 0, i, 600);
		}
		for (int i = 0; i < 600; i = i + 60)
		{
			Gr->DrawLine(Pens::Black, 0, i, 600, i);
		}


        for (int n = 0; n < 10; n++)   //начальная отрисовка шариков
		{
			for (int m = 0; m < 10; m++)
			{
				if (field[n][m] == 1) Gr->FillEllipse(Brushes::Red, n * 60 + 5, m * 60 + 5, 50, 50);
				if (field[n][m] == 2) Gr->FillEllipse(Brushes::GreenYellow, n * 60 + 5, m * 60 + 5, 50, 50);
				if (field[n][m] == 3) Gr->FillEllipse(Brushes::Blue, n * 60 + 5, m * 60 + 5, 50, 50);
				if (field[n][m] == 4) Gr->FillEllipse(Brushes::Green, n * 60 + 5, m * 60 + 5, 50, 50);
				if (field[n][m] == 5) Gr->FillEllipse(Brushes::Violet, n * 60 + 5, m * 60 + 5, 50, 50);
				if (field[n][m] == 6) Gr->FillEllipse(Brushes::Brown, n * 60 + 5, m * 60 + 5, 50, 50);
				if (field[n][m] == 7) Gr->FillEllipse(Brushes::Orange, n * 60 + 5, m * 60 + 5, 50, 50);

			}
		}
	}

//=================================================== обработка событий нажатия мыши по picturebox =============================

	private: System::Void pictureBox1_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		int n, m;   //координаты ячейки, по которой был произведен щелчок
		n = ((e->X) / 60);  //60 х 60 - количество пикселей в одной ячейке
		m = ((e->Y) / 60);
			if (selected == false)  //если какая-либо ячейка не выделена
			{
				if (field[n][m] != 0)  //если в ячейке есть шарик
				{
					Gr->FillRectangle(Brushes::LightSkyBlue, n * 60 + 5, m * 60 + 5, 50, 50);  //обозначение выделения
					selected = true;
					tmpN = n;          //сохранение координат
					tmpM = m;
					tmpColor = field[n][m];  //сохранение цвета
				}
			}
			else                        //если какая-либо ячейка выделена
			{
				if (field[n][m] == 0)   //если в ячейке, по которой щелкнули, нет шарика
				{
					for (int n = 0; n < 10; n++)   //заполнение массива для поиска пути
					{
						for (int m = 0; m < 10; m++)
						{
							way_field[n][m] = 0; //обнуление массива поиска пути
							if (field[n][m] != 0) way_field[n][m] = 1; //заполнение массива поиска пути
						}
					}
					way_field[(e->X)/60][(e->Y)/60] = 2;  //обозначение кликнутой ячейки, как целевой
					if (check_way(tmpN, tmpM) == true)    //еслт путь к целевой ячейке есть
					{
						field[tmpN][tmpM] = 0;  //ранее выделенная ячейка становится пустой
						Gr->FillRectangle(Brushes::White, tmpN * 60 + 5, tmpM * 60 + 5, 50, 50); //снятие выделения с ячейки
						field[(e->X) / 60][(e->Y) / 60] = tmpColor;  //перенос шарика из ранее выделенной ячейки в ту, по которой был произведен щелчок
						search_empty();         //пересчет таблицы с пустыми ячейками 

						deleted = false;
						delete_ball();
						search_empty();
						if (deleted == false)   //если на предыдущем ходу не были удалены шарики
						{
							if (add.size() >= 3)  //добавление новых шариков
							{
								add_new(3);
							}
							if (add.size() == 2)
							{
								add_new(2);
							}
							if (add.size() == 1)
							{
								add_new(1);
							}
							delete_ball();
							search_empty();   //пересчет таблицы с пустыми ячейками 
						}
						selected = false;       //снятие выделения
						label2->Text = (System::Convert::ToString(score));
					}
				}
				else
				{
					Gr->FillRectangle(Brushes::White, tmpN * 60 + 5, tmpM * 60 + 5, 50, 50);  //иначе - снятие выделения
					selected = false;
				}
			
			}

			if (add.size() == 0)   //если пустых ячеек не осталось
			{
				label3->Text = "Игра окончена";
				button1->Text = "Новая игра";
			}

		for (int a = 0; a < 10; a++)  //отрисовка таблицы после каждого клика по picturebox
		{
			for (int b = 0; b < 10; b++)
			{
				if (field[a][b] == 0) Gr->FillEllipse(Brushes::White, a * 60 + 5, b * 60 + 5, 50, 50);
				if (field[a][b] == 1) Gr->FillEllipse(Brushes::Red, a * 60 + 5, b * 60 + 5, 50, 50);
				if (field[a][b] == 2) Gr->FillEllipse(Brushes::GreenYellow, a * 60 + 5, b * 60 + 5, 50, 50);
				if (field[a][b] == 3) Gr->FillEllipse(Brushes::Blue, a * 60 + 5, b * 60 + 5, 50, 50);
				if (field[a][b] == 4) Gr->FillEllipse(Brushes::Green, a * 60 + 5, b * 60 + 5, 50, 50);
				if (field[a][b] == 5) Gr->FillEllipse(Brushes::Violet, a * 60 + 5, b * 60 + 5, 50, 50);
				if (field[a][b] == 6) Gr->FillEllipse(Brushes::Brown, a * 60 + 5, b * 60 + 5, 50, 50);
				if (field[a][b] == 7) Gr->FillEllipse(Brushes::Orange, a * 60 + 5, b * 60 + 5, 50, 50);
			}
		}	
	}
};
}
