#define _STRINGIZE(x) #x
#define STRINGIZE(x) _STRINGIZE(x)

#include <string>
#include <iostream>

#if _WIN32 || _WIN64
#include <windows.h>
#include <sapi.h>

int say(std::string message)
{
   ISpVoice *pVoice = NULL;

   if (FAILED(::CoInitialize(NULL)))
      return 1;

   HRESULT hr = CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void **)&pVoice);
   if (SUCCEEDED(hr))
   {
      std::wstring wmessage = std::wstring(message.begin(), message.end());
      LPCWSTR lmessage = wmessage.c_str();
      hr = pVoice->Speak(lmessage, 0, NULL);
      pVoice->Release();
      pVoice = NULL;
   }

   ::CoUninitialize();

   return 0;
}

#else

#include <speech-dispatcher/libspeechd.h>

int say(std::string message)
{

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

   return 0;
}

#endif

int main(int argc, char **argv)
{
   std::string message;

   for (int i = 1; i < argc; i++)
   {
      message += " ";
      message += argv[i];
   }

   say(message);

   return 0;
}
