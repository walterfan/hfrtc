#include <stdio.h>
#include <string.h>
#include <curl/curl.h>
 
const int URL_MAX_LEN = 2048;

int main(int argc, char* argv[])
{
  
  char url[URL_MAX_LEN] = "http://www.google.com";
  if(argc > 1) {
    int len = strlen(argv[1]);
    if(len >= URL_MAX_LEN)
	 len = URL_MAX_LEN - 1;
    strncpy(url, argv[1], len);	
  }
  CURL *curl;
  CURLcode res;
 
  curl = curl_easy_init();
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, url);
    /* example.com is redirected, so we tell libcurl to follow redirection */ 
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
 
    /* Perform the request, res will get the return code */ 
    res = curl_easy_perform(curl);
    /* Check for errors */ 
    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
 
    /* always cleanup */ 
    curl_easy_cleanup(curl);
  }
  return 0;
}

