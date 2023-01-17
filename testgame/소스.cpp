#include<iostream>
#include<Windows.h>
#include<conio.h>
#include<vector>
#include<string>
#include<ctime>
#include<cstdlib>
#include<fstream> 
#pragma comment(lib, "winmm.lib")
using namespace std;

//������� By. BlockDMask.
//[PART1] make screen, change screen, input.
//[PART2] input&output, question, life.
//[PART3] setting level, play music, play time

#define MAGIC_KEY 224	//�����¿� ȭ��ǥ�� ���ö� ���� ������ ����
#define SPACE 32		//����� Ű ��
#define KEY_NUM 4
#define LIFE 3
#define MAX_LEVEL 11

enum MENU
{
	GAMESTART = 0,
	INFO,
	QUIT
};

enum KEYBOARD
{
	UP = 72,
	LEFT = 75,
	RIGHT = 77,
	DOWN = 80
};

//�ܼ� Ŀ�� �̵�
void gotoxy(int x, int y)//�ܼ� ������ Ư�� ��ġ�� Ŀ���� �̵���Ű�� �Լ� �Դϴ�.
{
	COORD Pos;//x,y�� ������ �ִ� ����ü 
	Pos.X = 2 * x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
//keyboard �Է�
int GetKeyDown()
{
	if (_kbhit() != 0)        //Ű���忡 ���� �Է��� ����
	{
		return _getch();    //�Էµ� Ű���� ��ȯ.
	}
	return 0;
}
//Ŀ�� �����̴°� ���
void DrawUserCursor(int& y)
{
	if (y <= 0)			//Ŀ���� ���� �׸� �ö󰡰� �ϱ�
	{
		y = 0;
	}
	else if (y >= 2)	//Ŀ���� �׸� �Ʒ��� �������� �ϱ�
	{
		y = 2;
	}

	gotoxy(9, 8 + y);	//��ġ ����
	cout << ">";
}
//�ܼ� ũ��,Ÿ��Ʋ
void SetConsoleView()
{
	system("mode con:cols=50 lines=20");	//���� 50, ���� 20
	system("title Dance");				//Ÿ��Ʋ ���ϱ�
}

//-----------Draw-----------------
void DrawReadyGame()//���� ù ȭ�� �׸���
{
	system("cls");		//ȭ�鸦 Ŭ���� ����
	gotoxy(5, 2);
	cout << "******************************";
	gotoxy(5, 3);
	cout << "*        Mini Game         *";
	gotoxy(5, 4);
	cout << "******************************";
	gotoxy(10, 8);
	cout << "DanceGame";
	gotoxy(10, 9);
	cout << "HangmanGame";
	gotoxy(10, 10);
	cout << "Quit" << endl;
}

//���� ���� ȭ�� �׸���
void DrawStartGame(const int life, const int score, const string questionStr, const string answerStr)
{
	system("cls");
	gotoxy(2, 1);
	cout << "*******************************************";
	gotoxy(4, 3);
	cout << "Life : " << life << " / " << LIFE;
	gotoxy(4, 4);
	cout << "Score : " << score;
	gotoxy(4, 8);
	cout << "Q : " << questionStr;
	gotoxy(4, 10);
	cout << "A : " << answerStr;
	gotoxy(4, 12);
	cout << "SPACE!�� ������ �մϴ�.";
	gotoxy(2, 18);
	cout << "*******************************************" << endl;

}
//��� �̴� ����ȭ�� draw
void DrawStartGame2(int life, int score, vector<string>& pastWord)
{
	system("cls");
	gotoxy(5, 1);
	cout << "life = " << life;
	gotoxy(5, 2);
	cout << "score = " << score;
	gotoxy(5, 8);
	cout << "past = ";
	for (int i = 0; i < static_cast<int>(pastWord.size()); ++i)
	{
		cout << pastWord[i] << " ";
	}

	gotoxy(5, 12);
	cout << "input = ";
	gotoxy(13, 14);
	cout << "����ȭ�� 'qq'" << endl;
}

//������ �����ϴ� �Լ� �Դϴ�. ���� �����
void SetDictionary(vector<string>& strArr)
{
	static const int INIT_NUM = 4;
	static const string str[INIT_NUM] = { "apple", "banana", "code", "program" };    //���� �ܾ��
	ifstream readFromFile("words.txt");        //words.txt ������ �б� �������� ����
	if (!readFromFile.is_open())            //is_open�� ���� �ʴ´ٴ°��� ������ �������� �ʴٴ� ��.
	{
		ofstream writeToFile("words.txt");    //���� �������� words.txt ������ ���� (������ ������ �ڵ� ������)
		for (int i = 0; i < INIT_NUM; ++i)    //���� �ܾ���� format�� �°� words.txt ���Ͽ� �Է�
		{
			string tmp = str[i];
			if (i != INIT_NUM - 1)
			{
				tmp += "\n";
			}
			writeToFile.write(tmp.c_str(), tmp.size());    //���Ͽ� ���� �Լ�
			strArr.push_back(str[i]); //�ܾ���(strArr)�� �ܾ ����ֽ��ϴ�.
		}
		writeToFile.close();    //������������ �ݱ�
		return;                    //�Լ���
	}

	//����� �Դٴ°��� �б��������� ���Ͽ��� �Ǿ��ٴ¶�.
	while (!readFromFile.eof())    //���� ������
	{
		string tmp;
		getline(readFromFile, tmp);    //���پ� �о
		strArr.push_back(tmp);        //�ܾ���(strArr)�� �ܾ� �ֱ�
	}
	readFromFile.close();        //�б��������� �ݱ�
	return;
}
//���� ���� �׸���
void DrawGameOver(const int playTime)
{
	gotoxy(8, 8);
	cout << "-------------------";
	gotoxy(8, 9);
	cout << "| G A M E O V E R |";
	gotoxy(8, 10);
	cout << " " << playTime << " sec";
	gotoxy(8, 11);
	cout << "-------------------";
	system("pause>null");
}

//-----------Func-----------------
MENU ReadyGame()//���� ���
{
	int y = 0;				//Ŀ���� y��ġ
	int input = 0;			//Ű���忡 �Է¹��� ����
	while (true)			//���� ����
	{
		DrawReadyGame();	//���� ù ȭ�� �׸���
		DrawUserCursor(y);	//Ŀ�� ������
		input = _getch();	//_getch():����ڰ� �Է��� Ű�� ���� ���� �ƽ�Ű�ڵ�� ��ȯ
		//�����			
		if (input == MAGIC_KEY)		//224�� ����
		{
			switch (_getch())		//�����¿츦 �ޱ����� �ѹ� �� ����
			{
			case UP:				//��
				--y;
				break;
			case DOWN:				//�Ʒ�
				++y;
				break;
			}
		}
		else if (input == SPACE)	//Ű���� �Է��� space�� ��
		{
			switch (y)				//y��ġ�� ���� �Ǵ�
			{
			case 0:
				return GAMESTART;
			case 1:
				return INFO;
			case 2:
				return QUIT;
			}
		}
	}
}
//��ǰ��� ����ȭ�� �׸���
void DrawReadyGame2()
{
	system("cls");
	gotoxy(5, 2);
	cout << "==============================";
	gotoxy(5, 3);
	cout << "======= HANG MAN GAME ========";
	gotoxy(5, 4);
	cout << "==============================";
	gotoxy(6, 6);
	cout << "�����Ϸ��� 's'�� �����ּ���";
	gotoxy(6, 7);
	cout << "�����Ϸ��� 'q'�� �����ּ���";
	
}
//��� ����ȭ�� ���
bool MiniReadyGame()
{
	DrawReadyGame2();    //����ȭ�� �׸���
	while (true)
	{
		int key = GetKeyDown();                //Ű�� ������
		if (key == 's' || key == 'S')        //s�� ��ŸƮ
		{
			return true;
		}
		else if (key == 'q' || key == 'Q')    //q�� ��
		{
			break;
		}
	}
	return false;
}
//���� �غ�
void SetQuestion(vector<int>& questionVec, int level)
{
	if (level > MAX_LEVEL)
	{
		level = MAX_LEVEL;
	}

	int num = 0;
	srand((unsigned int)time(NULL));
	for (int i = 0; i < level; ++i)	//ȭ��ǥ�� ���� (���� ���̵�)
	{
		num = rand() % KEY_NUM;	//ȭ��ǥ ����.
		switch (num)
		{
		case 0:
			questionVec.push_back(UP);
			break;
		case 1:
			questionVec.push_back(RIGHT);
			break;
		case 2:
			questionVec.push_back(LEFT);
			break;
		case 3:
			questionVec.push_back(DOWN);
			break;
		}
	}
}
//ȭ��ǥ �ν�
void VectorToString(const vector<int> v, string& str)
{
	for (int i = 0; i < static_cast<int>(v.size()); ++i)
	{
		switch (v[i])
		{
		case UP:
			str += "�� ";
			break;
		case DOWN:
			str += "�� ";
			break;
		case LEFT:
			str += "�� ";
			break;
		case RIGHT:
			str += "�� ";
			break;
		}
	}
}
//��� Ȯ��
bool CheckAnswer(const vector<int> questionVec, const vector<int> answerVec)
{
	//������ �迭�� ����.
	//���� üũ
	if (questionVec.size() != answerVec.size())
	{
		//���� �ٸ���
		return false;
	}

	//���빰 üũ
	for (int i = 0; i < static_cast<int>(questionVec.size()); ++i)
	{
		if (questionVec[i] != answerVec[i])
		{
			//�ٸ��� �ֳ�.
			return false;
		}
	}
	return true;
}
//���� ���� â
void StartGame()
{
	//���� ���
	PlaySound("HYP-Hit.wav", NULL, SND_NODEFAULT | SND_ASYNC | SND_LOOP);
	int life = LIFE;
	int score = 0;
	//��������� ����ð�.
	clock_t startTime, endTime;
	startTime = clock();

	//�����, d a w s
	//����
	vector<int> questionVec;
	string questionStr = "";
	//�����
	vector<int> answerVec;
	string answerStr = "";

	int firstInput = 0;
	int secondInput = 0;
	while (true)
	{
		int level = (score / 30) + 1;

		//������ ����
		SetQuestion(questionVec, level);
		//������ �����ֱ�.
		VectorToString(questionVec, questionStr);
		while (true)
		{
			//1������ ������ ������ Ǭ��.
			DrawStartGame(life, score, questionStr, answerStr);

			if (life == 0)
			{
				//���� �����϶� ����ð�
				endTime = clock();
				int playTime = static_cast<int>((endTime - startTime) / CLOCKS_PER_SEC);

				DrawGameOver(playTime);
				PlaySound(NULL, NULL, 0);
				return;
			}

			//���� �ϳ��� �Է�.
			firstInput = _getch();
			if (firstInput == MAGIC_KEY)
			{
				secondInput = _getch();
				answerVec.push_back(secondInput);
				switch (secondInput)
				{
				case UP:
					answerStr += "�� ";
					break;
				case DOWN:
					answerStr += "�� ";
					break;
				case LEFT:
					answerStr += "�� ";
					break;
				case RIGHT:
					answerStr += "�� ";
					break;
				}
			}
			else if (firstInput == SPACE)
			{
				//��� ����
				//��� Ȯ��
				if (CheckAnswer(questionVec, answerVec))
				{
					score += 10;
				}
				else
				{
					//Ʋ�ȴ�.
					--life;
					score -= 5;
					if (score < 0)
					{
						score = 0;
					}
				}

				questionVec.clear();
				questionStr = "";
				answerVec.clear();
				answerStr = "";
				break;
			}
		}
	}
}
//��� ���� ���� �Լ�
void StartGame2()
{
	int score = 0;
	vector<string> pastWord;    //�Է��� ���ܾ� ����
	vector<string> strArr;        //���� �ܾ���
	SetDictionary(strArr);        //read from file

	while (true)    //�ϳ��� ź�� ǥ���ϴ� ����
	{
		//1 play
		int num = 0;
		srand((unsigned int)time(NULL));    //�����Լ� 
		num = rand() % static_cast<int>(strArr.size());    //�ܾ��� ���� ������ �ܾ� ����

		string strQuestion;                        // _ _ _ _ _ �� ǥ���� ����
		const string strOriginal = strArr[num];    //�ܾ �´��� ����Ȯ�ο����� ����
		const int originLen = static_cast<int>(strOriginal.length());

		//init
		for (int i = 0; i < originLen; ++i)
		{
			strQuestion += "_";    //���� ���̸�ŭ "_"
		}

		int life = originLen + 2;    //������� ���� �ܾ� ���� + 2

		//1 question
		while (true)    //�ϳ��� �ܾ ���ߴ� ����
		{
			DrawStartGame2(life, score, pastWord);    //���ܾ�, �����, ����ǥ��

			//draw question
			gotoxy(5, 5);
			for (int i = 0; i < originLen; ++i)
			{
				cout << strQuestion[i] << " ";    // _ _ _ _ ǥ��
			}
			cout << endl;

			//input
			gotoxy(9, 12);
			string strInput;
			cin >> strInput;    //�Է� �ޱ�.
			if (strInput == "qq")
			{
				return;
			}
			pastWord.push_back(strInput);    //�ѹ� �Է��� �ܾ�� pastword���� ǥ��

			if (strInput.length() == 1)        //�Է¹��� ��Ʈ���� ���̰� 1�ΰ��
			{
				//alphabet
				for (int i = 0; i < originLen; ++i)
				{
					if (strOriginal[i] == strInput[0])    //�������� �ܾ �Է��� ���ĺ��� �ִ°��
					{
						strQuestion[i] = strInput[0];    // �ش� ��ġ�� "_" �� ���ĺ����� �ٲ��� 
					}
				}
			}
			else if (strInput.length() > 1)    //�Է¹��� ��Ʈ���� ���̰� 1���� ū ���
			{
				//word
				if (strOriginal == strInput) //�������� �ܾ�� �Է� �ܾ ������ (����)
				{
					//score up !!
					score += 5;
					pastWord.clear();
					break;    //�ϳ��� �ܾ ���ߴ� ������ �����Եǰ� ���� ź���� �Ѿ�� �˴ϴ�.
				}
			}

			//Ʋ���ų�, �°ų� ��¶�� �Է��� �Ǹ� �������� ������ 1���� ���Դϴ�.
			life -= 1;
			if (life < 0)
			{
				score -= 5;
				if (score < 0)
				{
					score = 0;
				}
				pastWord.clear();
				break;
			}
		}
	}
}
int main(void)
{
	SetConsoleView();		//���α׷� ���� �� �ܼ� ũ��
	while (true)
	{
		switch (ReadyGame())//���� �޾� �Ǵ�
		{
		case GAMESTART:
			StartGame();	//���� ����â
			break;
		case INFO:
			StartGame2();		//���� ����â
			break;
		case QUIT:			//������
			return 0;
		}
	}
	return 0;
}