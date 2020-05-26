#define _STRINGIZE(x) #x
#define STRINGIZE(x) _STRINGIZE(x)

#include <string>
#include <speech-dispatcher/libspeechd.h>

using namespace std;

string message;
SPDConnection *conn;

int main(int argc, char **argv)
{
   for(int i=1; i<argc; i++){
       message += " ";
       message += argv[i];
   }

   /* Open Speech Dispatcher connection in SINGLE MODE mode. */
   conn = spd_open("say","conn", NULL, SPD_MODE_SINGLE);   

#ifdef LANG
   /* Set Language */
   spd_set_language(conn, STRINGIZE(LANG) );
#endif

    /* Say message. */
   spd_say(conn, SPD_MESSAGE, (char*) message.c_str());

    /* Close connection */   
   spd_close(conn);

   return 0;
}