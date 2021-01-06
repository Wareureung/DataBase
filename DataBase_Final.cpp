// DataBase_Final.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "pch.h"
#include "framework.h"
#include "DataBase_Final.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 유일한 애플리케이션 개체입니다.

CWinApp theApp;

using namespace std;

CDatabase db;

bool login_menu_state;
int choise_boos;

void MyDataBase();
void BossMenu();
void BoosMenuOne();
void BoosMenuTwo();
void NormalMenu();
void NormalMenuOne();
void NormalMenuTwo();

void PrintfIndex(const CString sql, int index_num);

int main()
{
    int nRetCode = 0;

    HMODULE hModule = ::GetModuleHandle(nullptr);

    if (hModule != nullptr)
    {
        // MFC를 초기화합니다. 초기화하지 못한 경우 오류를 인쇄합니다.
        if (!AfxWinInit(hModule, nullptr, ::GetCommandLine(), 0))
        {
            // TODO: 여기에 애플리케이션 동작을 코딩합니다.
			_tprintf_s(L"심각한 오류: MFC 초기화 실패\n");
            nRetCode = 1;
        }
        else
        {
            // TODO: 여기에 애플리케이션 동작을 코딩합니다.
			MyDataBase();			
        }
    }
    else
    {
        // TODO: 오류 코드를 필요에 따라 수정합니다.
		_tprintf_s(L"심각한 오류: GetModuleHandle 실패\n");
        nRetCode = 1;
    }

    return nRetCode;
}

void gotoxy(int x, int y)
{
	COORD curpos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), curpos);
}

void MyDataBase()
{
	_tsetlocale(LC_ALL, _T(""));
	
	db.OpenEx(_T("DSN=db_final"), 0);

	bool roof_base = true;
	char choice_next;
		
	int myid;
	int mypassword;
	int myrank;

	while (roof_base)
	{
		bool check_id_same = false;
		bool check_password_same = false;

		_tprintf_s(_T("\n\n====================== 메 인 화 면 ======================\n\n"));
		_tprintf_s(_T("\t1 - 로그인\t\t2 - 종료\n\n"));
		choice_next = _getch();

		switch (choice_next - '0')
		{
		case 1:			
		{
			//로그인
			system("cls");
			gotoxy(0, 0);

			_tprintf_s(_T("\n\n====================== 로그인 화면 ======================\n\n"));

			_tprintf_s(_T("\t\tID 입력(8자리) : "));			
			_tscanf_s(_T("%d"), &myid);

			_tprintf_s(_T("\n\t\tPASSWORD 입력(4자리) : "));
			_tscanf_s(_T("%d"), &mypassword);

			CRecordset rs(&db);
			rs.Open(CRecordset::dynaset, _T("select m_id from employee"));

			CRecordset rr(&db);
			rr.Open(CRecordset::dynaset, _T("select m_rank from employee"));
						
			while (!rs.IsEOF())
			{
				CString db_myid;
				rs.GetFieldValue(short(0), db_myid);				
				int get_db_id = _ttoi(db_myid);

				CString db_rank;
				rr.GetFieldValue(short(0), db_rank);
				int get_db_rank = _ttoi(db_rank);

				rs.MoveNext();
				rr.MoveNext();

				if (get_db_id == myid)
				{
					check_id_same = true;
					myrank = get_db_rank;
				}
			}


			CRecordset rp(&db);
			rp.Open(CRecordset::dynaset, _T("select m_password from employee"));

			while (!rp.IsEOF())
			{
				CString db_mypassword;
				rp.GetFieldValue(short(0), db_mypassword);
				int get_db_password = _ttoi(db_mypassword);

				rp.MoveNext();

				if (get_db_password == mypassword)
					check_password_same = true;
			}

			if (check_id_same && check_password_same)
			{				
				system("cls");
				gotoxy(0, 0);

				login_menu_state = true;

				while (login_menu_state)
				{
					if (myrank == 0)
					{
						BossMenu();
					}
					else
					{
						NormalMenu();
					}
				}
				
			}
			else if (!check_id_same && check_password_same)
			{
				system("cls");
				gotoxy(0, 0);
				_tprintf_s(_T("====================== 존재하지 않는 아이디입니다.====================== \n"));
			}
			else if (check_id_same && !check_password_same)
			{
				system("cls");
				gotoxy(0, 0);
				_tprintf_s(_T("====================== 비밀번호가 틀렸습니다.====================== \n"));
			}
			else
			{
				system("cls");
				gotoxy(0, 0);
				_tprintf_s(_T("================== 아이디 비밀번호를 확인해주십시요.================== \n"));
			}
			break;
		}
		case 2:
			roof_base = false;
			break;

		default:
			system("cls");
			gotoxy(0, 0);
			break;
		}
		
	}
}

void BossMenu()
{
	_tprintf_s(_T("\n\n========================== B O S S 화 면 ==========================\n\n"));
	_tprintf_s(_T("       1 - 인사\t\t     2 - 보기\t\t3 - 돌아가기\n\n"));	
	choise_boos = _getch();
	switch (choise_boos - '0')
	{
	case 1:
	{
		BoosMenuOne();
		break;
	}
	case 2:
	{
		BoosMenuTwo();
		break;
	}
	case 3:
	{
		system("cls");
		gotoxy(0, 0);
		login_menu_state = false;
		break;
	}
	}
}


void NormalMenu()
{
	_tprintf_s(_T("\n\n========================== 메 뉴 화 면 ==========================\n\n"));
	_tprintf_s(_T("  1 - 게임 정보 조회\t\t2 - 보기\t\t3 - 돌아가기\n\n"));
	int choise_boos;
	choise_boos = _getch();
	switch (choise_boos - '0')
	{
	case 1:
	{
		NormalMenuOne();
		break;
	}
	case 2:
	{
		NormalMenuTwo();
		break;
	}	
	case 3:
		system("cls");
		gotoxy(0, 0);
		login_menu_state = false;
		break;
	}
}

void BoosMenuOne()
{
	//직원 부서 이동
	system("cls");
	gotoxy(0, 0);

	bool check_dep_name = false;
	bool check_inname = false;
	bool check_same = false;
	char emname[10];
	char emdepart[10];

	_tprintf_s(_T("\n\n========================== 팀 조 정 ==========================\n\n"));

	_tprintf_s(_T("\n직원 이름 입력 : "));
	scanf_s("%s", emname, sizeof(emname));

	_tprintf_s(_T("\n\n팀 이름 입력 : "));
	scanf_s("%s", emdepart, sizeof(emdepart));

	CRecordset rs(&db);
	rs.Open(CRecordset::dynaset, _T("select m_name from employee"));
	CRecordset rd(&db);
	rd.Open(CRecordset::dynaset, _T("select m_nowin from employee"));

	while (!rs.IsEOF())
	{
		CString get_name;
		rs.GetFieldValue(short(0), get_name);

		CString get_depart;
		rd.GetFieldValue(short(0), get_depart);

		rs.MoveNext();
		rd.MoveNext();

		get_name.Replace(_T(" "), NULL);
		get_depart.Replace(_T(" "), NULL);

		if (get_name.Compare((CString)emname) == 0)
		{
			check_inname = true;
			if (get_depart.Compare((CString)emdepart) == 0)
				check_same = true;
		}
	}

	if (!check_same)
	{

		CString game_name00("라자니");
		game_name00.Replace(_T(" "), NULL);
		CString game_name01("무도사");
		game_name01.Replace(_T(" "), NULL);
		CString game_name02("새우런");
		game_name02.Replace(_T(" "), NULL);

		if (game_name00.Compare((CString)emdepart) == 0 || game_name01.Compare((CString)emdepart) == 0 || game_name02.Compare((CString)emdepart) == 0)
			check_dep_name = true;



		if (check_inname && check_dep_name)
		{
			CString change_dep = _T("EXEC pro_move_dep ");
			change_dep = change_dep + _T("'") + (CString)emname + _T("'") + _T(", ") + _T("'") + (CString)emdepart + _T("'");
			db.ExecuteSQL(change_dep);
			system("cls");
			gotoxy(0, 0);
			_tprintf_s(_T("================== 직원 '%s'님의 팀이 '%s'(으)로 옮겨 졌습니다. ==================\n"), (CString)emname, (CString)emdepart);
		}
		else if (check_inname && !check_dep_name)
		{
			system("cls");
			gotoxy(0, 0);
			_tprintf_s(_T("======================= 존재하지 않는 부서입니다. =======================\n"));
		}
		else if (!check_inname && check_dep_name)
		{
			system("cls");
			gotoxy(0, 0);
			_tprintf_s(_T("======================= 존재하지 않는 사원입니다. =======================\n"));
		}
		else
		{
			system("cls");
			gotoxy(0, 0);
			_tprintf_s(_T("======================= 정확하지 않은 정보 입니다. =======================\n"));
		}
	}
	else
	{
		system("cls");
		gotoxy(0, 0);
		_tprintf_s(_T("======================= 이미 해당 팀입니다. =======================\n"));
	}
}

void BoosMenuTwo()
{
	system("cls");
	gotoxy(0, 0);

	int b_infor_choise = 0;
	bool b_state = true;

	while (b_state)
	{
		_tprintf_s(_T("\n\n================================== 정 보 선 택 화 면 =================================\n\n"));
		_tprintf_s(_T(" 1 - 개인 정보 열람\t\t2 - 모든 정보 열람\t\t3 - 게임 정보 열람\t\t4 - 돌아가기\n\n"));
		b_infor_choise = _getch();

		system("cls");
		gotoxy(0, 0);

		switch (b_infor_choise - '0')
		{
		case 1:
		{
			char b_alone_name[10];
			_tprintf_s(_T("\n\n================================== 직원 조회 =================================\n\n"));

			_tprintf_s(_T("\n직원 이름 입력 : "));
			scanf_s("%s", b_alone_name, sizeof(b_alone_name));

			_tprintf_s(_T("\n================================================================================ 사원 정보 =====================================================================\n\n"));
			_tprintf_s(_T("\n=== ID ============ 이름 ================== 직급 =================== 월급 ============ 전화번호 ============= 입사일 ========= 직무 ============== 소속 팀 =====\n\n"));

			CString find_one;
			find_one.Format(_T("select m_id,m_name, m_position, m_salary, m_phone, m_enter, m_job, m_nowin from employee where m_name = '%s'"), (CString)b_alone_name);
			PrintfIndex(find_one, 8);

			_tprintf_s(_T("================================================================= 돌아가기 - 아무버튼이나 누르세요 ==============================================================="));
			_getch();
			system("cls");
			gotoxy(0, 0);
			break;
		}
		case 2:
		{
			_tprintf_s(_T("\n================================================================================ 사원 정보 =====================================================================\n\n"));
			_tprintf_s(_T("\n=== ID ============ 이름 ================== 직급 =================== 월급 ============ 전화번호 ============= 입사일 ========= 직무 ============== 소속 팀 =====\n\n"));

			CString str = _T("select* from view_b_all_employee");
			PrintfIndex(str, 8);

			_tprintf_s(_T("================================================================= 돌아가기 - 아무버튼이나 누르세요 ==============================================================="));
			choise_boos = _getch();
			system("cls");
			gotoxy(0, 0);
			break;
		}
		case 3:
		{
			char game_name[10];
			int gi = 0;

			CString game_name00("라자니");
			game_name00.Replace(_T(" "), NULL);
			CString game_name01("무도사");
			game_name01.Replace(_T(" "), NULL);
			CString game_name02("새우런");
			game_name02.Replace(_T(" "), NULL);

			_tprintf_s(_T("\n\n================================== 게임 조회 =================================\n\n"));

			_tprintf_s(_T("\n게임 이름 입력 : "));
			scanf_s("%s", game_name, sizeof(game_name));

			if (game_name00.Compare((CString)game_name) == 0 || game_name01.Compare((CString)game_name) == 0 || game_name02.Compare((CString)game_name) == 0)
			{
				_tprintf_s(_T("\n================================================================== 게임 정보 ==========================================================================================\n\n"));
				_tprintf_s(_T("\n=== 직급 ================== 이름 ===================== 직무 =============== 게임이름 ============== 장르 ========== 개발시작일 === 개발종료일 === 서비스 상태 ========\n\n"));

				CString ab_game = _T("EXEC About_Game");
				ab_game = ab_game + _T("'") + (CString)game_name + _T("'");

				db.ExecuteSQL(ab_game);
				
				CString game_info;
				game_info.Format(_T("select m_position, m_name, m_job, m_nowin, g_genre, g_startdate, g_enddate, g_state from employee INNER JOIN game ON employee.m_nowin = game.g_name where m_nowin = '%s'"), (CString)game_name);

				PrintfIndex(game_info, 8);

				_tprintf_s(_T("===================================================== 돌아가기 - 아무버튼이나 누르세요 ================================================================================"));
				choise_boos = _getch();
				system("cls");
				gotoxy(0, 0);
			}
			else
			{
				system("cls");
				gotoxy(0, 0);
				_tprintf_s(_T("======================= 존재하는 게임이 아닙니다. =======================\n"));
			}			
			break;
		}
		case 4:
			b_state = false;
			b_infor_choise = false;
			break;
		}
	}
}

void NormalMenuOne()
{
	system("cls");
	gotoxy(0, 0);

	char game_name[10];
	int gi = 0;

	CString game_name00("라자니");
	game_name00.Replace(_T(" "), NULL);
	CString game_name01("무도사");
	game_name01.Replace(_T(" "), NULL);
	CString game_name02("새우런");
	game_name02.Replace(_T(" "), NULL);

	_tprintf_s(_T("\n\n================================== 게임 조회 =================================\n\n"));

	_tprintf_s(_T("\n게임 이름 입력 : "));
	scanf_s("%s", game_name, sizeof(game_name));

	if (game_name00.Compare((CString)game_name) == 0 || game_name01.Compare((CString)game_name) == 0 || game_name02.Compare((CString)game_name) == 0)
	{
		_tprintf_s(_T("\n================================================================== 게임 정보 ==========================================================================================\n\n"));
		_tprintf_s(_T("\n=== 직급 ================== 이름 ===================== 직무 =============== 게임이름 ============== 장르 ========== 개발시작일 === 개발종료일 === 서비스 상태 ========\n\n"));

		CString ab_game = _T("EXEC About_Game");
		ab_game = ab_game + _T("'") + (CString)game_name + _T("'");

		db.ExecuteSQL(ab_game);

		CString game_info;
		game_info.Format(_T("select m_position, m_name, m_job, m_nowin, g_genre, g_startdate, g_enddate, g_state from employee INNER JOIN game ON employee.m_nowin = game.g_name where m_nowin = '%s'"), (CString)game_name);

		PrintfIndex(game_info, 8);

		_tprintf_s(_T("===================================================== 돌아가기 - 아무버튼이나 누르세요 ================================================================================"));
		choise_boos = _getch();
		system("cls");
		gotoxy(0, 0);
	}
	else
	{
		system("cls");
		gotoxy(0, 0);
		_tprintf_s(_T("======================= 존재하는 게임이 아닙니다. =======================\n"));
	}
}

void NormalMenuTwo()
{
	system("cls");
	gotoxy(0, 0);

	int e_infor_choise = 0;
	bool e_state = true;

	while (e_state)
	{
		_tprintf_s(_T("\n\n================================== 정 보 선 택 화 면 =================================\n\n"));
		_tprintf_s(_T(" 1 - 개인 정보 열람\t\t2 - 모든 정보 열람\t\t3 - 종료\n\n"));
		e_infor_choise = _getch();

		system("cls");
		gotoxy(0, 0);

		switch (e_infor_choise - '0')
		{
		case 1:
		{
			char e_alone_name[10];
			_tprintf_s(_T("\n\n================================== 직원 조회 =================================\n\n"));

			_tprintf_s(_T("\n직원 이름 입력 : "));
			scanf_s("%s", e_alone_name, sizeof(e_alone_name));

			_tprintf_s(_T("\n==================================================== 사원 정보 =====================================================\n\n"));
			_tprintf_s(_T("\n=== 이름 ================== 직급 ==================== 전화번호 =============== 직무 =============== 소속 팀 ========\n\n"));

			CString find_one;
			find_one.Format(_T("select m_name, m_position, m_phone, m_job, m_nowin from employee where m_name = '%s'"), (CString)e_alone_name);
			PrintfIndex(find_one, 5);

			_tprintf_s(_T("========================================== 돌아가기 - 아무버튼이나 누르세요 =========================================="));
			_getch();
			system("cls");
			gotoxy(0, 0);
			break;
		}

		case 2:
		{
			CString str = _T("select* from view_e_all_employee");

			_tprintf_s(_T("\n==================================================== 사원 정보 =====================================================\n\n"));
			_tprintf_s(_T("\n=== 이름 ================== 직급 ==================== 전화번호 =============== 직무 =============== 소속 팀 ========\n\n"));

			PrintfIndex(str, 5);

			_tprintf_s(_T("========================================== 돌아가기 - 아무버튼이나 누르세요 =========================================="));
			_getch();
			system("cls");
			gotoxy(0, 0);
			break;
		}

		case 3:
			e_state = false;
			e_infor_choise = false;
			break;
		}
	}
}

void PrintfIndex(const CString sql, int index_num)
{
	CRecordset rs(&db);
	rs.Open(CRecordset::dynaset, sql);

	CString str;
	int i = 0;

	while (!rs.IsEOF())
	{
		rs.GetFieldValue(short(i), str);
		if (str.GetLength() > 0)
			_tprintf_s(_T("    %s\t"), (LPCTSTR)str);

		i++;

		if (i / index_num == 1)
		{
			rs.MoveNext();
			_tprintf_s(_T("\n\n"));
			i = 0;
		}
	}
}