#include "TinyUtil.h"
#include <cctype>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <execinfo.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <stdarg.h>
#include <time.h>
#include <sys/time.h>

int octet_weight[256] = {
  0, 1, 1, 2, 1, 2, 2, 3,
  1, 2, 2, 3, 2, 3, 3, 4,
  1, 2, 2, 3, 2, 3, 3, 4,
  2, 3, 3, 4, 3, 4, 4, 5,
  1, 2, 2, 3, 2, 3, 3, 4,
  2, 3, 3, 4, 3, 4, 4, 5,
  2, 3, 3, 4, 3, 4, 4, 5,
  3, 4, 4, 5, 4, 5, 5, 6,
  1, 2, 2, 3, 2, 3, 3, 4,
  2, 3, 3, 4, 3, 4, 4, 5,
  2, 3, 3, 4, 3, 4, 4, 5,
  3, 4, 4, 5, 4, 5, 5, 6,
  2, 3, 3, 4, 3, 4, 4, 5,
  3, 4, 4, 5, 4, 5, 5, 6,
  3, 4, 4, 5, 4, 5, 5, 6,
  4, 5, 5, 6, 5, 6, 6, 7,
  1, 2, 2, 3, 2, 3, 3, 4,
  2, 3, 3, 4, 3, 4, 4, 5,
  2, 3, 3, 4, 3, 4, 4, 5,
  3, 4, 4, 5, 4, 5, 5, 6,
  2, 3, 3, 4, 3, 4, 4, 5,
  3, 4, 4, 5, 4, 5, 5, 6,
  3, 4, 4, 5, 4, 5, 5, 6,
  4, 5, 5, 6, 5, 6, 6, 7,
  2, 3, 3, 4, 3, 4, 4, 5,
  3, 4, 4, 5, 4, 5, 5, 6,
  3, 4, 4, 5, 4, 5, 5, 6,
  4, 5, 5, 6, 5, 6, 6, 7,
  3, 4, 4, 5, 4, 5, 5, 6,
  4, 5, 5, 6, 5, 6, 6, 7,
  4, 5, 5, 6, 5, 6, 6, 7,
  5, 6, 6, 7, 6, 7, 7, 8
};

char bit_string[MAX_PRINT_STRING_LEN];
char LOG_FILE[256] = "journey.log";

static FILE *fp ;
static int SESSION_TRACKER; //Keeps track of session
 


int octet_get_weight(uint8_t octet) {
  extern int octet_weight[256];

  return octet_weight[octet];
}  

uint8_t nibble_to_hex_char(uint8_t nibble) {
  char buf[16] = {'0', '1', '2', '3', '4', '5', '6', '7',
		  '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };
  return buf[nibble & 0xF];
}

char * octet_string_hex_string(const void *s, int length) {
  const uint8_t *str = (const uint8_t *)s;
  int i;
  
  /* double length, since one octet takes two hex characters */
  length *= 2;

  /* truncate string if it would be too long */
  if (length > MAX_PRINT_STRING_LEN)
    length = MAX_PRINT_STRING_LEN-1;
  
  for (i=0; i < length; i+=2) {
    bit_string[i]   = nibble_to_hex_char(*str >> 4);
    bit_string[i+1] = nibble_to_hex_char(*str++ & 0xF);
  }
  bit_string[i] = 0; /* null terminate string */
  return bit_string;
}

static inline int hex_char_to_nibble(uint8_t c) {
  switch(c) {
  case ('0'): return 0x0;
  case ('1'): return 0x1;
  case ('2'): return 0x2;
  case ('3'): return 0x3;
  case ('4'): return 0x4;
  case ('5'): return 0x5;
  case ('6'): return 0x6;
  case ('7'): return 0x7;
  case ('8'): return 0x8;
  case ('9'): return 0x9;
  case ('a'): return 0xa;
  case ('A'): return 0xa;
  case ('b'): return 0xb;
  case ('B'): return 0xb;
  case ('c'): return 0xc;
  case ('C'): return 0xc;
  case ('d'): return 0xd;
  case ('D'): return 0xd;
  case ('e'): return 0xe;
  case ('E'): return 0xe;
  case ('f'): return 0xf;
  case ('F'): return 0xf;
  default: return -1;   /* this flags an error */
  }
  /* NOTREACHED */
  return -1;  /* this keeps compilers from complaining */
}

int is_hex_string(char *s) {
  while(*s != 0)
    if (hex_char_to_nibble(*s++) == -1)
      return 0;
  return 1;
}

/*
 * hex_string_to_octet_string converts a hexadecimal string
 * of length 2 * len to a raw octet string of length len
 */

int hex_string_to_octet_string(char *raw, char *hex, int len) {
  uint8_t x;
  int tmp;
  int hex_len;

  hex_len = 0;
  while (hex_len < len) {
    tmp = hex_char_to_nibble(hex[0]);
    if (tmp == -1)
      return hex_len;
    x = (tmp << 4);
    hex_len++;
    tmp = hex_char_to_nibble(hex[1]);
    if (tmp == -1)
      return hex_len;
    x |= (tmp & 0xff);
    hex_len++;
    *raw++ = x;
    hex += 2;
  }
  return hex_len;
}

int octet_string_is_eq(uint8_t *a, uint8_t *b, int len) {
  uint8_t *end = b + len;
  while (b < end)
    if (*a++ != *b++)
      return 1;
  return 0;
}

void octet_string_set_to_zero(uint8_t *s, int len) {
  uint8_t *end = s + len;

  do {
    *s = 0;
  } while (++s < end);
  
}


namespace wfan {

std::string trim(const std::string& str, const std::string& whitespace )
{
    string::size_type strBegin = str.find_first_not_of(whitespace);
    if (strBegin == std::string::npos)
        return ""; // no content

    string::size_type strEnd = str.find_last_not_of(whitespace);
    string::size_type strRange = strEnd - strBegin + 1;

    return str.substr(strBegin, strRange);
}

std::string ltrim(const std::string& str, const std::string& whitespace )
{
    string::size_type strBegin = str.find_first_not_of(whitespace);
    if (strBegin == std::string::npos)
        return ""; // no content


    string::size_type strRange = str.size() - strBegin + 1;
    return str.substr(strBegin, strRange);
}

std::string rtrim(const std::string& str, const std::string& whitespace )
{
    string::size_type strEnd = str.find_last_not_of(whitespace);
    if (strEnd == std::string::npos)
        return ""; // no content

    string::size_type strRange = strEnd + 1;

    return str.substr(0, strRange);
}

string ReplaceValueAsKey(const string& str, const char* key,
		const char* mask, const char* sep)
{

	string::size_type nBegin = str.find(key);
	if(string::npos == nBegin) return str;

	string::size_type nEnd = str.find(sep, nBegin);

	if(string::npos == nEnd) {
		return str.substr(0, nBegin) + key + mask;
	}
	return str.substr(0, nBegin) + key + mask + str.substr(nEnd);
}

int file2msg(const char* filename,string& msg)
{
    ifstream ifile(filename);
    if(!ifile)
    {
        cout<<"Unable to read "<<filename<<endl;
        return RET_ERR;
    }
    ostringstream buf;
    char ch;
    while ( buf && ifile.get( ch ))
        buf.put( ch );
    ifile.close();
    msg=buf.str();
    return RET_OK;
}

int file2msg(const char* filename,char *msg)
{
    ifstream ifile(filename);
    if(!ifile)
    {
        cout<<"Unable to read "<<filename<<endl;
        return -1;
    }
    ostringstream buf;
    char ch;
    while ( buf && ifile.get( ch ))
    buf.put( ch );
    strcpy(msg, buf.str().c_str());
    return 0;
}

int RetrieveFiles(const char* szFolder, vector<string>& files)
{
  struct dirent* direntp;
  DIR* dirp = opendir(szFolder);

  if(NULL == dirp) {
    return -1;
  }

  while( NULL != (direntp = readdir(dirp))) {
    string file = direntp->d_name;
    if(".." == file || "." == file)
        continue;
    files.push_back(file);
  }

  while((-1 == closedir(dirp)) && (errno == EINTR));

  return files.size();
}

string UpperCase( const string& p_string )
{
    string str = p_string;

    for( size_t i = 0; i < str.size(); i++ )
    {
        str[i] = toupper( str[i] );
    }
    return str;
}

string LowerCase( const string& p_string )
{
    string str = p_string;

    for( size_t i = 0; i < str.size(); i++ )
    {
        str[i] = tolower( str[i] );
    }
    return str;
}

void WriteLog(char* filename, int line, char *fmt,...)
{
    va_list         args;
    int n = 0;
    char log_msg[1024] = {'\0'}; 

    if(SESSION_TRACKER > 0)
      fp = fopen (LOG_FILE,"a+");
    else
      fp = fopen (LOG_FILE,"w");

    struct timeval tim;  
    gettimeofday(&tim, NULL);  
     
    va_start( args, fmt );
    n = vsnprintf(log_msg, 1024, fmt, args);
    va_end( args );
    
    //fprintf(fp,"%ld ",time(NULL));
    fprintf(fp,"[%ld.%3d, %s, %d] %s", tim.tv_sec, tim.tv_usec/1000, filename,line, log_msg);
    #ifdef __WF_DEBUG__
    fprintf(stdout,"[%ld.%3d, %s, %d] %s", tim.tv_sec, tim.tv_usec/1000, filename,line, log_msg);
    #endif
    
    
    SESSION_TRACKER++;
    fclose(fp);
}

void DumpCallStack(std::ostream &os)
{
	void* trace[ 64 ];
	char** messages = NULL;
	int trace_size = 0;

	os << "Begin Stack Frame Dump" << std::endl;
	os << "(if useful symbols are not found, try recompiling "
		<< "with -rdynamic during link, and -g without -O#)"
		<< std::endl;
	trace_size = backtrace( trace, 64 );
	messages = backtrace_symbols( trace, trace_size );
	for( int i = 0; i < trace_size; ++i )
	{
		os << "Traced: " << messages[i] << std::endl;
	}

	os << "End Stack Frame Dump" << std::endl;

    free (messages);
}

}//--end of namespace wfan
