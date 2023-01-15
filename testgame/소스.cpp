#include<iostream>
#include<Windows.h>
#include<conio.h>
#include<vector>
#include<string>
#include<ctime>
#pragma comment(lib, "winmm.lib")
using namespace std;

//리듬게임 By. BlockDMask.
//[PART1] make screen, change screen, input.
//[PART2] input&output, question, life.
//[PART3] setting level, play music, play time

#define MAGIC_KEY 224	//상하좌우 화살표가 들어올때 먼저 들어오는 숫자
#define SPACE 32		//스페어 키 값
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
void gotoxy(int x, int y)//커서를 특정 위치로 이동
{
	COORD Pos;//x,y를 가지고 있는 구조체 
	Pos.X = 2 * x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
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
	cout << "*        Dance Dance         *";
	gotoxy(5, 4);
	cout << "******************************";
	gotoxy(10, 8);
	cout << "GameStart";
//	gotoxy(10, 9);
//	cout << "GameInfo";
	gotoxy(10, 10);
	cout << "Quit" << endl;
}
//정보 화면
/*
void DrawInfoGame()
{
	system("cls");
	gotoxy(1, 3);
	cout << "*******************************************";
	gotoxy(1, 4);
	cout << "|Developer - BlockDMask";
	gotoxy(1, 5);
	cout << "|Blog - https://blockdmask.tistory.com/";
	gotoxy(1, 8);
	cout << "|Thank you.";
	gotoxy(1, 9);
	cout << "*******************************************";
	gotoxy(1, 10);
	cout << "|Music - https://www.youtube.com/HYPMUSIC";
}*/
//시작 화면 그리기
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
//게임 정보창
void InfoGame()
{
	//DrawInfoGame();
	system("pause>null");
}

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
	//음악 재생
	PlaySound("HYP-Hit.wav", NULL, SND_NODEFAULT | SND_ASYNC | SND_LOOP);
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
			//InfoGame();		//게임 정보창
			break;
		case QUIT:			//나가기
			return 0;
		}
	}
	return 0;
}