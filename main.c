

#include <stdio.h>
#include <curl/curl.h>

size_t 
write_cat_data (void *ptr, size_t size, size_t nmemb, FILE *stream) 
{
  return fwrite (ptr, size, nmemb, stream);
}
 
int 
main (void)
{
  FILE *fp;
  CURL *curl;
  CURLcode res;

  curl = curl_easy_init ();
  fp = fopen ("skepticalcat.jpg", "wb");
  if (!fp) {
    fprintf (stderr, "Error creating cat file.");
    return -1;
  }

  if (!curl) {
    fprintf (stderr, "Curl error");
    fclose (fp);
    return -1;
  }

  curl_easy_setopt (curl, CURLOPT_URL, "http://skepticalcat.com/skepticalcat.jpg");
  curl_easy_setopt (curl, CURLOPT_FOLLOWLOCATION, 1L);
  curl_easy_setopt (curl, CURLOPT_WRITEFUNCTION, write_cat_data);
  curl_easy_setopt (curl, CURLOPT_WRITEDATA, fp);
 
  res = curl_easy_perform (curl);
  if (res != CURLE_OK) {
    fprintf(stderr, "skeptical cat error: %s\n", curl_easy_strerror (res));
    fclose (fp);
    return -1;
  }
 
  curl_easy_cleanup(curl);

  return 0;
}
