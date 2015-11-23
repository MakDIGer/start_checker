/*
 * start_checker.cpp
 * 
 * Copyright 2015 Nikolay <Nikolay@REX>
 * 
 * 
 * Version 1.2.2
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */


#include <stdio.h>
#include <iostream>
#include <string.h>
#include "windows.h"
#include <ctime> 

using namespace std;

string files[128], buffer_line;

void extrDIR(string indir)
{
	char dir1[128];
	
	buffer_line = indir+"*";
	strncpy(dir1, buffer_line.c_str(), buffer_line.length()+1);
	
	int count = 0;
	WIN32_FIND_DATA FindFileData;
	HANDLE hf;
	hf=FindFirstFile(dir1, &FindFileData);
	if (hf!=INVALID_HANDLE_VALUE)
	{
		do
		{
			files[count] = FindFileData.cFileName; count++;
		}
		while (FindNextFile(hf,&FindFileData)!=0);
		FindClose(hf);
	}
}

int check_file(string dir1, string file1)
{
	extrDIR(dir1);
	for (int i=2;i<128;i++)
	{
		if (files[i]=="")
		{
			i=128;
		} else 
		{
			if (files[i] == file1)
			{
				return 1;
			}
		}
	}
	return 0;
}

void run_cmd(string buffer_line)
{
	char command[256];
	
	strncpy(command, buffer_line.c_str(), buffer_line.length()+1);
	system(command);
}

string time_now()
{
	time_t rawtime;
	struct tm * timeinfo;
	time ( &rawtime );
	timeinfo = localtime ( &rawtime );
	return asctime (timeinfo);
}

int main()
{
	char start_file[] = "D:\\Garant.SRV\\start.txt";
	
	cout << ".............:::Start checker utulity:::.............." << endl;
	cout << "..................... Version 1.2.2 .................." << endl;
	cout << "...................... REX Edition ..................." << endl;
	
	remove(start_file);
	
	checking:
	if (check_file("D:\\Garant.SRV\\","start.txt"))
	{
		cout << endl;
		cout << time_now() << "::There is Etalon" << endl;
		cout << endl;
		cout << "C:\\MTurtle\\combin.exe" << endl;
		run_cmd("C:\\MTurtle\\combin.exe");
	} else 
	{
		cout << endl;
		cout << time_now() << "::There isn't etalon" << endl;
		Sleep(600000);
		goto checking;
	}
	run_cmd("pause");
	return 0;
}

