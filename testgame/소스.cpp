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

<<<<<<< HEAD
#define MAGIC_KEY 224	//상하좌우 화살표가 들어올때 먼저 들어오는 숫자
#define SPACE 32		//스페어 키 값
=======
#define MAGIC_KEY 224	//�긽�븯醫뚯슦 �솕�궡�몴媛� �뱾�뼱�삱�븣 癒쇱�� �뱾�뼱�삤�뒗 �닽�옄
#define SPACE 32		//�뒪�럹�뼱 �궎 媛�
>>>>>>> c478910ff3972ccf048f12ce2a19817a88d748fb
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

//肄섏넄 而ㅼ꽌 �씠�룞
void gotoxy(int x, int y)//肄섏넄 �궡遺��쓽 �듅�젙 �쐞移섎줈 而ㅼ꽌瑜� �씠�룞�떆�궎�뒗 �븿�닔 �엯�땲�떎.
{
	COORD Pos;//x,y瑜� 媛�吏�怨� �엳�뒗 援ъ“泥� 
	Pos.X = 2 * x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
//keyboard �엯�젰
int GetKeyDown()
{
	if (_kbhit() != 0)        //�궎蹂대뱶�뿉 萸붽�� �엯�젰�씠 �삤硫�
	{
		return _getch();    //�엯�젰�맂 �궎媛믪쓣 諛섑솚.
	}
	return 0;
}
//而ㅼ꽌 ���吏곸씠�뒗寃� 異쒕젰
void DrawUserCursor(int& y)
{
	if (y <= 0)			//而ㅼ꽌媛� �쐞濡� 洹몃쭔 �삱�씪媛�寃� �븯湲�
	{
		y = 0;
	}
	else if (y >= 2)	//而ㅼ꽌媛� 洹몃쭔 �븘�옒濡� �궡�젮媛�寃� �븯湲�
	{
		y = 2;
	}

	gotoxy(9, 8 + y);	//�쐞移� 議곗젙
	cout << ">";
}
//肄섏넄 �겕湲�,����씠���
void SetConsoleView()
{
	system("mode con:cols=50 lines=20");	//媛�濡� 50, �꽭濡� 20
	system("title Dance");				//����씠��� �젙�븯湲�
}

//-----------Draw-----------------
void DrawReadyGame()//寃뚯엫 泥� �솕硫� 洹몃━湲�
{
	system("cls");		//�솕硫대�� �겢由ъ뼱 �빐以�
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

//寃뚯엫 �떆�옉 �솕硫� 洹몃━湲�
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
	cout << "SPACE!瑜� �닃�윭�빞 �빀�땲�떎.";
	gotoxy(2, 18);
	cout << "*******************************************" << endl;

}
//�뻾留� 誘몃땲 寃뚯엫�솕硫� draw
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
	cout << "硫붿씤�솕硫� 'qq'" << endl;
}

//�궗�쟾�쓣 �꽭�똿�븯�뒗 �븿�닔 �엯�땲�떎. �뙆�씪 �엯異쒕젰
void SetDictionary(vector<string>& strArr)
{
	static const int INIT_NUM = 4;
	static const string str[INIT_NUM] = { "apple", "banana", "code", "program" };    //�깦�뵆 �떒�뼱�뱾
	ifstream readFromFile("words.txt");        //words.txt �뙆�씪�쓣 �씫湲� �쟾�슜�쑝濡� �삤�뵂
	if (!readFromFile.is_open())            //is_open�씠 �릺吏� �븡�뒗�떎�뒗寃껋�� �뙆�씪�씠 議댁옱�븯吏� �븡�떎�뒗 �쑜.
	{
		ofstream writeToFile("words.txt");    //�벐湲� �쟾�슜�쑝濡� words.txt �뙆�씪�쓣 �삤�뵂 (�뙆�씪�씠 �뾾�쑝硫� �옄�룞 �깮�꽦�맖)
		for (int i = 0; i < INIT_NUM; ++i)    //�깦�뵆 �떒�뼱�뱾�쓣 format�뿉 留욊쾶 words.txt �뙆�씪�뿉 �엯�젰
		{
			string tmp = str[i];
			if (i != INIT_NUM - 1)
			{
				tmp += "\n";
			}
			writeToFile.write(tmp.c_str(), tmp.size());    //�뙆�씪�뿉 �벐�뒗 �븿�닔
			strArr.push_back(str[i]); //�떒�뼱�옣(strArr)�뿉 �떒�뼱瑜� 吏묒뼱�꽔�뒿�땲�떎.
		}
		writeToFile.close();    //�벐湲곗쟾�슜�뙆�씪 �떕湲�
		return;                    //�븿�닔�걹
	}

	//�뿬湲곕줈 �솕�떎�뒗寃껋�� �씫湲곗쟾�슜�쑝濡� �뙆�씪�삤�뵂 �릺�뿀�떎�뒗�쑜.
	while (!readFromFile.eof())    //�뙆�씪 �걹源뚯��
	{
		string tmp;
		getline(readFromFile, tmp);    //�븳以꾩뵫 �씫�뼱�꽌
		strArr.push_back(tmp);        //�떒�뼱�옣(strArr)�뿉 �떒�뼱 �꽔湲�
	}
	readFromFile.close();        //�씫湲곗쟾�슜�뙆�씪 �떕湲�
	return;
}
//寃뚯엫 �삤踰� 洹몃━湲�
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
MENU ReadyGame()//寃뚯엫 湲곕뒫
{
	int y = 0;				//而ㅼ꽌�쓽 y�쐞移�
	int input = 0;			//�궎蹂대뱶�뿉 �엯�젰諛쏆쓣 蹂��닔
	while (true)			//寃뚯엫 猷⑦봽
	{
		DrawReadyGame();	//寃뚯엫 泥� �솕硫� 洹몃━湲�
		DrawUserCursor(y);	//而ㅼ꽌 ���吏곸엫
		input = _getch();	//_getch():�궗�슜�옄媛� �엯�젰�븳 �궎�뿉 ����븳 媛믪쓣 �븘�뒪�궎肄붾뱶濡� 諛섑솚
		//�넂�넀�넁�넃			
		if (input == MAGIC_KEY)		//224瑜� 諛쏆쓬
		{
			switch (_getch())		//�긽�븯醫뚯슦瑜� 諛쏄린�쐞�빐 �븳踰� �뜑 諛쏆쓬
			{
			case UP:				//�쐞
				--y;
				break;
			case DOWN:				//�븘�옒
				++y;
				break;
			}
		}
		else if (input == SPACE)	//�궎蹂대뱶 �엯�젰�씠 space�씪 �븣
		{
			switch (y)				//y�쐞移섏뿉 �뵲�씪 �뙋�떒
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
//�뻾留④쾶�엫 �떆�옉�솕硫� 洹몃━湲�
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
	cout << "�떆�옉�븯�젮硫� 's'瑜� �닃�윭二쇱꽭�슂";
	gotoxy(6, 7);
	cout << "醫낅즺�븯�젮硫� 'q'瑜� �닃�윭二쇱꽭�슂";
	
}
//�뻾留� �떆�옉�솕硫� 湲곕뒫
bool MiniReadyGame()
{
	DrawReadyGame2();    //�떆�옉�솕硫� 洹몃━湲�
	while (true)
	{
		int key = GetKeyDown();                //�궎媛� �뱾�뼱�삤硫�
		if (key == 's' || key == 'S')        //s�뒗 �뒪����듃
		{
			return true;
		}
		else if (key == 'q' || key == 'Q')    //q�뒗 �걹
		{
			break;
		}
	}
	return false;
}
//臾몄젣 以�鍮�
void SetQuestion(vector<int>& questionVec, int level)
{
	if (level > MAX_LEVEL)
	{
		level = MAX_LEVEL;
	}

	int num = 0;
	srand((unsigned int)time(NULL));
	for (int i = 0; i < level; ++i)	//�솕�궡�몴�쓽 媛쒖닔 (臾몄젣 �궃�씠�룄)
	{
		num = rand() % KEY_NUM;	//�솕�궡�몴 醫낅쪟.
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
//�솕�궡�몴 �씤�떇
void VectorToString(const vector<int> v, string& str)
{
	for (int i = 0; i < static_cast<int>(v.size()); ++i)
	{
		switch (v[i])
		{
		case UP:
			str += "�넁 ";
			break;
		case DOWN:
			str += "�넃 ";
			break;
		case LEFT:
			str += "�넀 ";
			break;
		case RIGHT:
			str += "�넂 ";
			break;
		}
	}
}
//�떟�븞 �솗�씤
bool CheckAnswer(const vector<int> questionVec, const vector<int> answerVec)
{
	//�닽�옄�쓽 諛곗뿴�씠 媛숇떎.
	//湲몄씠 泥댄겕
	if (questionVec.size() != answerVec.size())
	{
		//湲몄씠 �떎瑜대꽕
		return false;
	}

	//�궡�슜臾� 泥댄겕
	for (int i = 0; i < static_cast<int>(questionVec.size()); ++i)
	{
		if (questionVec[i] != answerVec[i])
		{
			//�떎瑜멸쾶 �엳�꽕.
			return false;
		}
	}
	return true;
}
//寃뚯엫 �떆�옉 李�
void StartGame()
{
<<<<<<< HEAD
	//음악 재생
	PlaySound("Little Fist - Quincas Moreira.mp3", NULL, SND_NODEFAULT | SND_ASYNC | SND_LOOP);
=======
	//�쓬�븙 �옱�깮
	PlaySound("HYP-Hit.wav", NULL, SND_NODEFAULT | SND_ASYNC | SND_LOOP);
>>>>>>> c478910ff3972ccf048f12ce2a19817a88d748fb
	int life = LIFE;
	int score = 0;
	//�옱�깮�뻽�쓣�븣 �쁽�옱�떆媛�.
	clock_t startTime, endTime;
	startTime = clock();

	//�넂�넀�넁�넃, d a w s
	//臾몄젣
	vector<int> questionVec;
	string questionStr = "";
	//�떟�븞吏�
	vector<int> answerVec;
	string answerStr = "";

	int firstInput = 0;
	int secondInput = 0;
	while (true)
	{
		int level = (score / 30) + 1;

		//臾몄젣瑜� �꽭�똿
		SetQuestion(questionVec, level);
		//臾몄젣瑜� 蹂댁뿬二쇨린.
		VectorToString(questionVec, questionStr);
		while (true)
		{
			//1臾몄젣瑜� 媛�吏�怨� 臾몄젣瑜� �뫜�떎.
			DrawStartGame(life, score, questionStr, answerStr);

			if (life == 0)
			{
				//寃뚯엫 �삤踰꾩씪�븣 �쁽�옱�떆媛�
				endTime = clock();
				int playTime = static_cast<int>((endTime - startTime) / CLOCKS_PER_SEC);

				DrawGameOver(playTime);
				PlaySound(NULL, NULL, 0);
				return;
			}

			//�젙�떟 �븯�굹�뵫 �엯�젰.
			firstInput = _getch();
			if (firstInput == MAGIC_KEY)
			{
				secondInput = _getch();
				answerVec.push_back(secondInput);
				switch (secondInput)
				{
				case UP:
					answerStr += "�넁 ";
					break;
				case DOWN:
					answerStr += "�넃 ";
					break;
				case LEFT:
					answerStr += "�넀 ";
					break;
				case RIGHT:
					answerStr += "�넂 ";
					break;
				}
			}
			else if (firstInput == SPACE)
			{
				//�떟�븞 �젣異�
				//�떟�븞 �솗�씤
				if (CheckAnswer(questionVec, answerVec))
				{
					score += 10;
				}
				else
				{
					//����졇�떎.
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
//�뻾留� 寃뚯엫 �떆�옉 �븿�닔
void StartGame2()
{
	int score = 0;
	vector<string> pastWord;    //�엯�젰�븳 �쁺�떒�뼱 ����옣
	vector<string> strArr;        //留욎텧 �떒�뼱�옣
	SetDictionary(strArr);        //read from file

	while (true)    //�븯�굹�쓽 �깂�쓣 �몴�쁽�븯�뒗 猷⑦봽
	{
		//1 play
		int num = 0;
		srand((unsigned int)time(NULL));    //�옖�뜡�븿�닔 
		num = rand() % static_cast<int>(strArr.size());    //�떒�뼱�옣 �궡�뿉 �옖�뜡�븳 �떒�뼱 �꽑�깮

		string strQuestion;                        // _ _ _ _ _ 濡� �몴�쁽�븷 蹂��닔
		const string strOriginal = strArr[num];    //�떒�뼱媛� 留욌뒗吏� �젙�떟�솗�씤�슜�쑝濡� ����옣
		const int originLen = static_cast<int>(strOriginal.length());

		//init
		for (int i = 0; i < originLen; ++i)
		{
			strQuestion += "_";    //�젙�떟 湲몄씠留뚰겮 "_"
		}

		int life = originLen + 2;    //�깮紐낅젰��� �젙�떟 �떒�뼱 湲몄씠 + 2

		//1 question
		while (true)    //�븯�굹�쓽 �떒�뼱瑜� 留욎텛�뒗 猷⑦봽
		{
			DrawStartGame2(life, score, pastWord);    //�궗�슜�떒�뼱, �깮紐낅젰, �젏�닔�몴湲�

			//draw question
			gotoxy(5, 5);
			for (int i = 0; i < originLen; ++i)
			{
				cout << strQuestion[i] << " ";    // _ _ _ _ �몴湲�
			}
			cout << endl;

			//input
			gotoxy(9, 12);
			string strInput;
			cin >> strInput;    //�엯�젰 諛쏄린.
			if (strInput == "qq")
			{
				return;
			}
			pastWord.push_back(strInput);    //�븳踰� �엯�젰�븳 �떒�뼱�뒗 pastword�뿉�꽌 �몴湲�

			if (strInput.length() == 1)        //�엯�젰諛쏆�� �뒪�듃留곸쓽 湲몄씠媛� 1�씤寃쎌슦
			{
				//alphabet
				for (int i = 0; i < originLen; ++i)
				{
					if (strOriginal[i] == strInput[0])    //�삤由ъ���꼸 �떒�뼱�뿉 �엯�젰�븳 �븣�뙆踰녹씠 �엳�뒗寃쎌슦
					{
						strQuestion[i] = strInput[0];    // �빐�떦 �쐞移섏쓽 "_" 瑜� �븣�뙆踰녹쑝濡� 諛붽퓭以� 
					}
				}
			}
			else if (strInput.length() > 1)    //�엯�젰諛쏆�� �뒪�듃留곸쓽 湲몄씠媛� 1蹂대떎 �겙 寃쎌슦
			{
				//word
				if (strOriginal == strInput) //�삤由ъ���꼸 �떒�뼱�옉 �엯�젰 �떒�뼱媛� 媛숈쓣�븣 (�젙�떟)
				{
					//score up !!
					score += 5;
					pastWord.clear();
					break;    //�븯�굹�쓽 �떒�뼱瑜� 留욎텛�뒗 猷⑦봽瑜� �굹媛�寃뚮릺怨� �떎�쓬 �깂�쑝濡� �꽆�뼱媛�寃� �맗�땲�떎.
				}
			}

			//���由ш굅�굹, 留욊굅�굹 �뼱夷뗫뱺 �엯�젰�씠 �릺硫� �씪�씠�봽媛� 臾댁“嫄� 1媛쒖뵫 源롮엯�땲�떎.
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
	SetConsoleView();		//�봽濡쒓렇�옩 �떆�옉 �떆 肄섏넄 �겕湲�
	while (true)
	{
		switch (ReadyGame())//由ы꽩 諛쏆븘 �뙋�떒
		{
		case GAMESTART:
			StartGame();	//�떆�옉 寃뚯엫李�
			break;
		case INFO:
			StartGame2();		//寃뚯엫 �젙蹂댁갹
			break;
		case QUIT:			//�굹媛�湲�
			return 0;
		}
	}
	return 0;
}
