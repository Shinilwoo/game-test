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
#define MAGIC_KEY 224	//�����¿� ȭ��ǥ�� ���ö� ���� ������ ����
#define SPACE 32		//����� Ű ��
=======
#define MAGIC_KEY 224	//상하좌우 화살표가 들어올때 먼저 들어오는 숫자
#define SPACE 32		//스페어 키 값
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

//콘솔 커서 이동
void gotoxy(int x, int y)//콘솔 내부의 특정 위치로 커서를 이동시키는 함수 입니다.
{
	COORD Pos;//x,y를 가지고 있는 구조체 
	Pos.X = 2 * x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
//keyboard 입력
int GetKeyDown()
{
	if (_kbhit() != 0)        //키보드에 뭔가 입력이 오면
	{
		return _getch();    //입력된 키값을 반환.
	}
	return 0;
}
//커서 움직이는것 출력
void DrawUserCursor(int& y)
{
	if (y <= 0)			//커서가 위로 그만 올라가게 하기
	{
		y = 0;
	}
	else if (y >= 2)	//커서가 그만 아래로 내려가게 하기
	{
		y = 2;
	}

	gotoxy(9, 8 + y);	//위치 조정
	cout << ">";
}
//콘솔 크기,타이틀
void SetConsoleView()
{
	system("mode con:cols=50 lines=20");	//가로 50, 세로 20
	system("title Dance");				//타이틀 정하기
}

//-----------Draw-----------------
void DrawReadyGame()//게임 첫 화면 그리기
{
	system("cls");		//화면를 클리어 해줌
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

//게임 시작 화면 그리기
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
	cout << "SPACE!를 눌러야 합니다.";
	gotoxy(2, 18);
	cout << "*******************************************" << endl;

}
//행맨 미니 게임화면 draw
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
	cout << "메인화면 'qq'" << endl;
}

//사전을 세팅하는 함수 입니다. 파일 입출력
void SetDictionary(vector<string>& strArr)
{
	static const int INIT_NUM = 4;
	static const string str[INIT_NUM] = { "apple", "banana", "code", "program" };    //샘플 단어들
	ifstream readFromFile("words.txt");        //words.txt 파일을 읽기 전용으로 오픈
	if (!readFromFile.is_open())            //is_open이 되지 않는다는것은 파일이 존재하지 않다는 뜻.
	{
		ofstream writeToFile("words.txt");    //쓰기 전용으로 words.txt 파일을 오픈 (파일이 없으면 자동 생성됨)
		for (int i = 0; i < INIT_NUM; ++i)    //샘플 단어들을 format에 맞게 words.txt 파일에 입력
		{
			string tmp = str[i];
			if (i != INIT_NUM - 1)
			{
				tmp += "\n";
			}
			writeToFile.write(tmp.c_str(), tmp.size());    //파일에 쓰는 함수
			strArr.push_back(str[i]); //단어장(strArr)에 단어를 집어넣습니다.
		}
		writeToFile.close();    //쓰기전용파일 닫기
		return;                    //함수끝
	}

	//여기로 왔다는것은 읽기전용으로 파일오픈 되었다는뜻.
	while (!readFromFile.eof())    //파일 끝까지
	{
		string tmp;
		getline(readFromFile, tmp);    //한줄씩 읽어서
		strArr.push_back(tmp);        //단어장(strArr)에 단어 넣기
	}
	readFromFile.close();        //읽기전용파일 닫기
	return;
}
//게임 오버 그리기
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
MENU ReadyGame()//게임 기능
{
	int y = 0;				//커서의 y위치
	int input = 0;			//키보드에 입력받을 변수
	while (true)			//게임 루프
	{
		DrawReadyGame();	//게임 첫 화면 그리기
		DrawUserCursor(y);	//커서 움직임
		input = _getch();	//_getch():사용자가 입력한 키에 대한 값을 아스키코드로 반환
		//→←↑↓			
		if (input == MAGIC_KEY)		//224를 받음
		{
			switch (_getch())		//상하좌우를 받기위해 한번 더 받음
			{
			case UP:				//위
				--y;
				break;
			case DOWN:				//아래
				++y;
				break;
			}
		}
		else if (input == SPACE)	//키보드 입력이 space일 때
		{
			switch (y)				//y위치에 따라 판단
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
//행맨게임 시작화면 그리기
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
	cout << "시작하려면 's'를 눌러주세요";
	gotoxy(6, 7);
	cout << "종료하려면 'q'를 눌러주세요";
	
}
//행맨 시작화면 기능
bool MiniReadyGame()
{
	DrawReadyGame2();    //시작화면 그리기
	while (true)
	{
		int key = GetKeyDown();                //키가 들어오면
		if (key == 's' || key == 'S')        //s는 스타트
		{
			return true;
		}
		else if (key == 'q' || key == 'Q')    //q는 끝
		{
			break;
		}
	}
	return false;
}
//문제 준비
void SetQuestion(vector<int>& questionVec, int level)
{
	if (level > MAX_LEVEL)
	{
		level = MAX_LEVEL;
	}

	int num = 0;
	srand((unsigned int)time(NULL));
	for (int i = 0; i < level; ++i)	//화살표의 개수 (문제 난이도)
	{
		num = rand() % KEY_NUM;	//화살표 종류.
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
//화살표 인식
void VectorToString(const vector<int> v, string& str)
{
	for (int i = 0; i < static_cast<int>(v.size()); ++i)
	{
		switch (v[i])
		{
		case UP:
			str += "↑ ";
			break;
		case DOWN:
			str += "↓ ";
			break;
		case LEFT:
			str += "← ";
			break;
		case RIGHT:
			str += "→ ";
			break;
		}
	}
}
//답안 확인
bool CheckAnswer(const vector<int> questionVec, const vector<int> answerVec)
{
	//숫자의 배열이 같다.
	//길이 체크
	if (questionVec.size() != answerVec.size())
	{
		//길이 다르네
		return false;
	}

	//내용물 체크
	for (int i = 0; i < static_cast<int>(questionVec.size()); ++i)
	{
		if (questionVec[i] != answerVec[i])
		{
			//다른게 있네.
			return false;
		}
	}
	return true;
}
//게임 시작 창
void StartGame()
{
<<<<<<< HEAD
	//���� ���
	PlaySound("Little Fist - Quincas Moreira.mp3", NULL, SND_NODEFAULT | SND_ASYNC | SND_LOOP);
=======
	//음악 재생
	PlaySound("HYP-Hit.wav", NULL, SND_NODEFAULT | SND_ASYNC | SND_LOOP);
>>>>>>> c478910ff3972ccf048f12ce2a19817a88d748fb
	int life = LIFE;
	int score = 0;
	//재생했을때 현재시간.
	clock_t startTime, endTime;
	startTime = clock();

	//→←↑↓, d a w s
	//문제
	vector<int> questionVec;
	string questionStr = "";
	//답안지
	vector<int> answerVec;
	string answerStr = "";

	int firstInput = 0;
	int secondInput = 0;
	while (true)
	{
		int level = (score / 30) + 1;

		//문제를 세팅
		SetQuestion(questionVec, level);
		//문제를 보여주기.
		VectorToString(questionVec, questionStr);
		while (true)
		{
			//1문제를 가지고 문제를 푼다.
			DrawStartGame(life, score, questionStr, answerStr);

			if (life == 0)
			{
				//게임 오버일때 현재시간
				endTime = clock();
				int playTime = static_cast<int>((endTime - startTime) / CLOCKS_PER_SEC);

				DrawGameOver(playTime);
				PlaySound(NULL, NULL, 0);
				return;
			}

			//정답 하나씩 입력.
			firstInput = _getch();
			if (firstInput == MAGIC_KEY)
			{
				secondInput = _getch();
				answerVec.push_back(secondInput);
				switch (secondInput)
				{
				case UP:
					answerStr += "↑ ";
					break;
				case DOWN:
					answerStr += "↓ ";
					break;
				case LEFT:
					answerStr += "← ";
					break;
				case RIGHT:
					answerStr += "→ ";
					break;
				}
			}
			else if (firstInput == SPACE)
			{
				//답안 제출
				//답안 확인
				if (CheckAnswer(questionVec, answerVec))
				{
					score += 10;
				}
				else
				{
					//틀렸다.
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
//행맨 게임 시작 함수
void StartGame2()
{
	int score = 0;
	vector<string> pastWord;    //입력한 영단어 저장
	vector<string> strArr;        //맞출 단어장
	SetDictionary(strArr);        //read from file

	while (true)    //하나의 탄을 표현하는 루프
	{
		//1 play
		int num = 0;
		srand((unsigned int)time(NULL));    //랜덤함수 
		num = rand() % static_cast<int>(strArr.size());    //단어장 내에 랜덤한 단어 선택

		string strQuestion;                        // _ _ _ _ _ 로 표현할 변수
		const string strOriginal = strArr[num];    //단어가 맞는지 정답확인용으로 저장
		const int originLen = static_cast<int>(strOriginal.length());

		//init
		for (int i = 0; i < originLen; ++i)
		{
			strQuestion += "_";    //정답 길이만큼 "_"
		}

		int life = originLen + 2;    //생명력은 정답 단어 길이 + 2

		//1 question
		while (true)    //하나의 단어를 맞추는 루프
		{
			DrawStartGame2(life, score, pastWord);    //사용단어, 생명력, 점수표기

			//draw question
			gotoxy(5, 5);
			for (int i = 0; i < originLen; ++i)
			{
				cout << strQuestion[i] << " ";    // _ _ _ _ 표기
			}
			cout << endl;

			//input
			gotoxy(9, 12);
			string strInput;
			cin >> strInput;    //입력 받기.
			if (strInput == "qq")
			{
				return;
			}
			pastWord.push_back(strInput);    //한번 입력한 단어는 pastword에서 표기

			if (strInput.length() == 1)        //입력받은 스트링의 길이가 1인경우
			{
				//alphabet
				for (int i = 0; i < originLen; ++i)
				{
					if (strOriginal[i] == strInput[0])    //오리지널 단어에 입력한 알파벳이 있는경우
					{
						strQuestion[i] = strInput[0];    // 해당 위치의 "_" 를 알파벳으로 바꿔줌 
					}
				}
			}
			else if (strInput.length() > 1)    //입력받은 스트링의 길이가 1보다 큰 경우
			{
				//word
				if (strOriginal == strInput) //오리지널 단어랑 입력 단어가 같을때 (정답)
				{
					//score up !!
					score += 5;
					pastWord.clear();
					break;    //하나의 단어를 맞추는 루프를 나가게되고 다음 탄으로 넘어가게 됩니다.
				}
			}

			//틀리거나, 맞거나 어쨋든 입력이 되면 라이프가 무조건 1개씩 깎입니다.
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
	SetConsoleView();		//프로그램 시작 시 콘솔 크기
	while (true)
	{
		switch (ReadyGame())//리턴 받아 판단
		{
		case GAMESTART:
			StartGame();	//시작 게임창
			break;
		case INFO:
			StartGame2();		//게임 정보창
			break;
		case QUIT:			//나가기
			return 0;
		}
	}
	return 0;
}
