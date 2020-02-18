///* Authour: Paula Aliu
// * AINT512 MiniProject

// * Sheva -The Conversational Agent
// */
/////#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS
//
//#define __STDC_WANT_LIB_EXT1__ 1
//
//#pragma region IncludeFiles
//#include <stdlib.h>	/* exit() */
//#include <string.h>
//#include <app.h>
//#include <nl.h>
//#include <recresult.h>
//
//
//#include <time.h>
//#pragma endregion 
//
//#pragma region Variables&Constants
//const char *date_time_slot = "current_dateTime"; 
//const char *day_slot = "current_day)";
//const char *date_slot = "current_date";
//const char *time_slot = "current_time";
//
//#pragma endregion
//
//#pragma region CoreFunctions
//
//void CoreEntryFxn(App *app)
//{
//    AppSetBeginSpeechTimeout(app, (float)30.0);
//	AppSetEndSpeechTimeout(app, (float)30.0);
//	AppSetEndRecognitionTimeout(app, (float)30.0);
//	AppSetRejectionThreshold(app, 35);
//}
//
//void CorePostRecFxn(App *app)
//{
//	UttStatus _status = AppGetUttStatus(app);
//	switch (_status)
//	{
//		case UTT_NORMAL:
//		case UTT_SESSION_ABORTED:
//			break;
//		case UTT_REJECT:
//		case UTT_BEGIN_SPEECH_TIMEOUT:
//		case UTT_END_SPEECH_TIMEOUT:
//		case UTT_END_RECOGNITION_TIMEOUT:
//			AppAppendPrompt(app, "try_again.wav");
//			AppGotoSelf(app);
//			break;
//		default:
//			fprintf(stderr, "Unexpected utterance status\n");
//			AppAppendTTSPrompt(app, "Try Again");
//			//AppAppendPrompt(app, "try_again.wav");
//			AppGotoSelf(app);
//			break;
//	}
//}
//
//void DateTimeEntryFn(App *app)
//{
//	char _buffer[100];
//
//	//Set The Grammar File
//	AppSetGrammar(app, ".DateTime");
//
//	AppAppendTTSPrompt(app,"hi! I am Sheva");
//
//	if (!AppRecognize(app))
//	{
//		printf("Sorry I did not catch that");
//		return;
//	}
//
//	//Get the current date and/or Time
//	NLGetStringSlotValue(AppGetNLResult(app), date_time_slot, _buffer,100);
//
//	if (!strcmp(_buffer, day_slot))
//	{
//		AppAppendTTSPrompt(app,"You said: What day is it");
//		time_t currentDay = time(NULL);
//		printf("Today is: %s", asctime(localtime(&currentDay)));
//
//	}
//	/*else if(!strcmp(_buffer, date_slot))
//	{
//		AppAppendTTSPrompt(app,"You said: What is the date is it");
//		time_t currentDay;
//		printf("today is  %A, the %d day of %B in the year %Y");
//	}
//	else if(!strcmp(_buffer,time_slot))
//	{
//		AppAppendTTSPrompt(app,"You said: What time is it");
//		time_t currentDay;
//		printf("The time is   %s", "%H:%M:%S");
//	}*/
//
//
//	#ifdef __STDC_LIB_EXT1__
//    struct tm buf;
//    char str[26];
//    asctime_s(str,sizeof str,gmtime_s(&t, &buf));
//    printf("UTC:   %s", str);
//    asctime_s(str,sizeof str,localtime_s(&t, &buf));
//    printf("local: %s", str);
//#endif
//
//
//}
//
//void DateTimePostRecFn(App *app)
//{
//
//}
//
//
//
//
//int main(int argc, char *argv[])
//{
//    App *app;
//	app = AppNew(&argc,argv);
//	
//	if (app == NULL)
//	{
//		exit(-1);
//	}
//
//
//	//App Creating Classes
//	AppCreateStateClass(app, "root", NULL, CoreEntryFxn, CorePostRecFxn);
//	AppCreateState(app, "date_time", "root", DateTimeEntryFn);
//	AppGo(app, "date_time");
//	return 0;
//}
//#pragma endregion 