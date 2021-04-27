/******************************************************************************
* Description: Example interation with our API. How to use libcurl taken from
*   source directly. Not to be called from the main program!
* Programmers: Gabriel Frey freyg@purdue.edu
* Source:      https://curl.se/libcurl/c/http-post.html
* Required Op: -lcurl
******************************************************************************/

/* to complie use:
* gcc api-test.c -lcurl -o api-test
*/

// Includes
#include <stdio.h>
#include <curl/curl.h>

void addScore();
void getScores();

int main(void){
  addScore();
  getScores();

  return 0;
}

/******************************************************************************
* Function:    addScore
* Description: Example of curl calls to add player score
* Parameters:
* Return:      void
******************************************************************************/
void addScore(){
  CURL *curl;
  CURLcode res;

  /* In windows, this will init the winsock stuff */
  curl_global_init(CURL_GLOBAL_ALL);

  /* get a curl handle */
  curl = curl_easy_init();
  if (curl){
    /* First set the URL that is about to receive our POST. This URL can
       just as well be a https:// URL if that is what should receive the
       data. */
    curl_easy_setopt(curl, CURLOPT_URL, "http://frey.network/CNIT315/api.php");
    /* Now specify the POST data */
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "player_name=daniel&score=1000&seed=1&version=0.01");

    /* Perform the request, res will get the return code */
    res = curl_easy_perform(curl);
    /* Check for errors */
    if (res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));

    /* always cleanup */
    curl_easy_cleanup(curl);
  }
  curl_global_cleanup();
}

/******************************************************************************
* Function:    getScores
* Description: Example of how to get scores from API
* Parameters:
* Return:      void
******************************************************************************/
void getScores(){
  CURL *curl;
  CURLcode res;

  /* In windows, this will init the winsock stuff */
  curl_global_init(CURL_GLOBAL_ALL);

  /* get a curl handle */
  curl = curl_easy_init();
  if (curl){
    /* First set the URL that is about to receive our POST. This URL can
       just as well be a https:// URL if that is what should receive the
       data. */
    curl_easy_setopt(curl, CURLOPT_URL, "http://frey.network/CNIT315/api.php");
    /* Now specify the POST data */
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "seed=1&version=0.01");

    /* Perform the request, res will get the return code */
    res = curl_easy_perform(curl);
    /* Check for errors */
    if (res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));

    /* always cleanup */
    curl_easy_cleanup(curl);
  }
  curl_global_cleanup();
}
