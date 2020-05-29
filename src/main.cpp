#define _STRINGIZE(x) #x
#define STRINGIZE(x) _STRINGIZE(x)

#include <string>
#include <iostream>

#if _WIN32 || _WIN64
//WINDOWS INCLUDES
#include <windows.h>
#include <sapi.h>

#else
//LINUX INCLUDES
#include <speech-dispatcher/libspeechd.h>
#endif

using namespace std;

int say(string message)
{

#if _WIN32 || _WIN64
   //WINDOWS CODE

   ISpVoice *pVoice = NULL;

   if (FAILED(::CoInitialize(NULL)))
      return 1;

   HRESULT hr = CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void **)&pVoice);
   if (SUCCEEDED(hr))
   {
      LPCWSTR lmessage = wstring(message.begin(),message.end()).c_str();
      wcout << lmessage; // this string truncates at 8 chars on 32 bit windows
      hr = pVoice->Speak(lmessage, 0, NULL);
      pVoice->Release();
      pVoice = NULL;
   }

   ::CoUninitialize();

#else
   //LINUX CODE

   SPDConnection *conn;

   /* Open Speech Dispatcher connection in SINGLE MODE mode. */
   conn = spd_open("say", "conn", NULL, SPD_MODE_SINGLE);

#ifdef LANG
   /* Set Language */
   spd_set_language(conn, STRINGIZE(LANG));
#endif

   /* Say message. */
   spd_say(conn, SPD_MESSAGE, (char *)message.c_str());

   /* Close connection */
   spd_close(conn);

#endif

   return 0;
}

int main(int argc, char **argv)
{
   string message;

   for (int i = 1; i < argc; i++)
   {
      message += " ";
      message += argv[i];
   }

   say(message);

   return 0;
}
