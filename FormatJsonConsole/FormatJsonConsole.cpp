// FormatJsonConsole.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

#include <iostream>
#include <fstream>
#include <cstring>

std::ifstream in;
std::ofstream out;

int _tmain(int argc, _TCHAR* argv[])
{
	bool fe = false;
	char ch ;
	char prev_ch='\n' ;
	int indent = -1;
	bool quoted = false;
	bool escaped = false;
	int index = 0;
	int i = 0 ;
	std::string buf = "";

	std::cout << "exe file.profile file.json";

	in.open(argv[1]);
	out.open(argv[2]);

	std::cout << "Read file..... ";

    while((ch = in.get()) != EOF) {
	  if (char(ch)=='\n') continue ;
	  if (char(ch)=='\t') continue ;

	  switch (ch)
	  {
	    case '{':
	    case '[':
	  	  out<< ch;
	  	  if (!quoted)
	  	  {
	  		  out<< std::endl;
	  		  ++indent;
	  		  for(i=0;i<=indent;i++) out<< '\t' ;
	  	  }
    	break;
	    case '}':
	    case ']':
	  	  if (!quoted)
	  	  {
	  		  out<< std::endl;
	  		  --indent;
	  		  for(i=0;i<=indent;i++) out<< '\t' ;
	  	  }
	  	  out<< ch;
        break;
	    case '"':
	  	  out<< ch;
	  	  escaped = false;
	  	  //while (index > 0 && str[--index] == '\\')  escaped = !escaped;
	  	  if (prev_ch=='\\') escaped = !escaped;
	  	  if (!escaped) quoted = !quoted;
 	    break;
	    case ',':
	  	  out<< ch;
	  	  if (!quoted)
	  	  {
	  		  out<< std::endl;
	  		  for(i=0;i<=indent;i++) out<< '\t' ;
	  	  }
	    break;
	    case ':':
	  	  out<< ch;
	  	  //if (!quoted) out<< " " << std::endl;
	    break;
	    default:
	  	    out<< ch;
    		break;
	  }
	  prev_ch=ch;

	  fe=in.eof();
      if (fe) break;
	  if (in.fail()) in.clear();

    }

	out.flush();
	out.close();
	in.close();

	return 0;
}

