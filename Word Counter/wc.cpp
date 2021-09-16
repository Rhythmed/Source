// wc.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <io.h>

#include <tchar.h>
#include <locale.h>
#include <ShlObj.h>
using namespace std;


//***************************************************//

void	file_exist(char *filename);											//	打开文件	预先判断文件是否存在
int		count_of_character(char *filename);									//	统计字符个数
int		count_of_word(char *filename);										//	统计单词个数
int		count_of_line(char *filename, bool print = true);					//	统计行数
void	count_of_more(char *filename, int *c, int *n, int *e);				//	统计更多数据
void	recursion_function(char *parameter, char *filename);				//	递归操作
void	file_dialog();														//	界面操作



char * wchar2char(const wchar_t* wchar){									//	宽字符转换
	char * m_char;
	int len = WideCharToMultiByte(CP_ACP, 0, wchar, wcslen(wchar), NULL, 0, NULL, NULL);
	m_char = new char[len + 1];
	WideCharToMultiByte(CP_ACP, 0, wchar, wcslen(wchar), m_char, len, NULL, NULL);
	m_char[len] = '\0';
	return m_char;
}






int main(int argc, char *argv[]){
	if (strcmp(argv[1], "-s") && strcmp(argv[1], "-x")){				//	parameter 非 "-s" "-x"
		file_exist(argv[2]);											//	预先判断文件是否存在 否则直接退出
	}


	int		count_char = 0;					//	字符数统计
	int		count_line = 0;					//	行数统计
	int		count_word = 0;					//	单词数统计
	int		count_code_line = 0;					//	代码行统计
	int		count_note_line = 0;					//	注释行统计
	int		count_empty_line = 0;					//	空白行统计

	if (!strcmp(argv[1], "-c"))
		count_char = count_of_character(argv[2]);				//	执行 字符统计操作

	else if (!strcmp(argv[1], "-l"))
		count_line = count_of_line(argv[2]);					//	执行 行数统计操作

	else if (!strcmp(argv[1], "-w"))
		count_word = count_of_word(argv[2]);					//	执行 单词统计操作

	else if (!strcmp(argv[1], "-a"))
		count_of_more(argv[2], &count_code_line, &count_note_line, &count_empty_line);			//	执行 更多复杂操作

	else if (!strcmp(argv[1], "-s"))
		recursion_function(argv[2], argv[3]);					//	执行 递归操作

	else if (!strcmp(argv[1], "-x"))
		file_dialog();											//	执行 打开目录界面操作

	return 0;
}





void	file_exist(char *filename){
	ifstream file(filename);
	if (!file.is_open()){
		cout << filename << " 文件不存在！" << endl;
		file.close();
		exit(0);
	}
}

int		count_of_character(char *filename){				//	统计字符个数
	ifstream file(filename);
	file.seekg(0, ios::end);							//	转到文件尾
	int count = (int)file.tellg();							//	返回文件字符数		字符'\n'算两个 因此需要 减去行数 加1
	int	line = count_of_line(filename, false);
	count = count - line + 1;
	cout << filename << " 文件的 字符数为 " << count << endl;
	file.close();
	return count;
}

int		count_of_line(char *filename, bool print){					//	统计文件行数
	ifstream	file(filename);
	int			line = 0;					//	统计行数
	char		buffer[1024];
	while (!file.eof())
	{
		file.getline(buffer, 1024);			//	逐行读取数据
		line++;								//	行数加一
	}
	if (print){
		cout << filename << " 文件的 行数为 " << line << endl;
	}
	file.close();
	return line;
}

int		count_of_word(char *filename){					//	统计文件单词数
	ifstream	file(filename);
	int			word = 0;
	string		buffer;
	while (file >> buffer){
		word++;
	}
	cout << filename << " 文件的 单词数为 " << word << endl;
	file.close();
	return word;
}

void	count_of_more(char *filename, int *c, int *n, int *e){
	int		empty_line = 0;					//	空白行
	int		code_line = 0;					//	代码行
	int		note_line = 0;					//	注释行
	char	buffer[1024];

	ifstream file(filename);
	while (!file.eof()){
		memset(buffer, 0, sizeof(buffer));			//	清零缓冲区
		file.getline(buffer, 1024);					//	读取一行数据

		if (buffer[0] == '\0')								//	读取的首字符 为 空
			empty_line++;
		else{												//	读取的首字符 非 空
			int empty = 0;										//	记录 空格 或 水平制表符
			int	note = 0;										//	记录 注释行
			int code = 0;										//	记录 代码行
			int i = 0;
			for (; buffer[i] != '\0'; i++){
				if (buffer[i] == ' ' || buffer[i] == '\t')		//	出现 空格 水平制表符 记录
					empty++;
				else if (buffer[i] == '/')						//	先出现 '/'
					note++;
				else if (buffer[i] != '/' && buffer[i] != '{' && buffer[i] != '}')		//	先出现 其他字符
					code++;
				if (note > code){
					note_line++;
					i = -1;
					break;
				}
				if (code > note){
					code_line++;
					i = -1;
					break;
				}
			}
			if (empty == i || empty == i - 1)
				empty_line++;
		}
	}
	file.close();
	cout << filename << " 文件的 代码行为 " << code_line << endl;
	cout << filename << " 文件的 注释行为 " << note_line << endl;
	cout << filename << " 文件的 空行为 " << empty_line << endl;
	*c = code_line;
	*n = note_line;
	*e = empty_line;
}

void	recursion_function(char *parameter, char *filename){							//	递归操作
	intptr_t		file;
	_finddata_t		fileData;

	file = _findfirst(filename, &fileData);			// 查找与输入匹配的第一个文件
	if (file == -1)
	{
		cout << "当前目录下无与" << filename << "匹配的文件" << endl;
		return;
	}

	do
	{
		char *_filename = fileData.name;	//	获取文件名称
		int		count_char = 0;				//	字符数统计
		int		count_line = 0;				//	行数统计
		int		count_word = 0;				//	单词数统计
		int		count_code_line = 0;
		int		count_note_line = 0;
		int		count_empty_line = 0;

		if (!strcmp(parameter, "-c")){
			count_char = count_of_character(_filename);				//	执行 字符统计操作
			cout << _filename << " 文件的 字符数为 " << count_char << endl;
		}
		else if (!strcmp(parameter, "-l")){
			count_line = count_of_line(_filename);					//	执行 行数统计操作
			cout << _filename << " 文件的 行数为 " << count_line << endl;
		}
		else if (!strcmp(parameter, "-w")){
			count_word = count_of_word(_filename);					//	执行 单词统计操作
			cout << _filename << " 文件的 单词数为 " << count_word << endl;
		}
		else if (!strcmp(parameter, "-a")){
			count_of_more(_filename, &count_code_line, &count_note_line, &count_empty_line);			//	执行 更多复杂操作
		}

	} while (!_findnext(file, &fileData));		// 查找目录中的下一个文件
}

void	file_dialog(){


	int		count_char = 0;				//	字符数统计
	int		count_line = 0;				//	行数统计
	int		count_word = 0;				//	单词数统计
	int		count_code_line = 0;
	int		count_note_line = 0;
	int		count_empty_line = 0;
	wchar_t buffer[1024];

	_tsetlocale(LC_CTYPE, L"");
	TCHAR			szPathName[MAX_PATH];
	OPENFILENAME	ofn = { OPENFILENAME_SIZE_VERSION_400 };


	ofn.lpstrFilter = L"文本文件(*.txt;*.cpp;*.c;*.h)";

	lstrcpy(szPathName, L"");
	ofn.lpstrFile = szPathName;
	ofn.nMaxFile = sizeof(szPathName);				//	存放用户选择文件的 路径及文件名 缓冲区
	ofn.lpstrTitle = L"选择文件";						//	选择文件对话框标题
	TCHAR szCurDir[MAX_PATH];
	GetCurrentDirectory(sizeof(szCurDir), szCurDir);
	ofn.lpstrInitialDir = szCurDir;						//	设置对话框显示的初始目录
	ofn.Flags = OFN_EXPLORER | OFN_ALLOWMULTISELECT | OFN_FILEMUSTEXIST;		//	如果需要选择多个文件 则必须带有  OFN_ALLOWMULTISELECT标志
	_tprintf(TEXT("Please select file"));

there:
	BOOL bOk = GetOpenFileName(&ofn);					//	调用对话框打开文件
	if (bOk)
	{
		count_char = count_of_character(wchar2char(szPathName));			//	统计字符个数
		count_line = count_of_line(wchar2char(szPathName));					//	统计行数
		count_word = count_of_word(wchar2char(szPathName));					//	统计单词个数
		count_of_more(wchar2char(szPathName), &count_code_line, &count_note_line, &count_empty_line);		//	统计更多数据
		swprintf_s(buffer, 1024, L"文件的 字符数 为 %d\n文件的 行数 为 %d\n文件的 单词数 为 %d\n文件的 代码行 为 %d\n文件的 注释行 为 %d\n文件的 空白行 为 %d"
			, count_char, count_line, count_word, count_code_line, count_note_line, count_empty_line);
		MessageBox(NULL, buffer, L"统计", MB_OK);
		if (IDYES == MessageBox(NULL, L"是否继续查看其他文件信息?", L"统计", MB_YESNO)){
			goto there;
		}
	}
}