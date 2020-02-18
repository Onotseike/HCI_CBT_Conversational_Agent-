//#define _CRT_SECURE_NO_WARNINGS
/* Authour: Paula Aliu
 * AINT512 MiniProject

 * Sheva -The Conversational Agent
 */

#pragma once
#pragma region IncludeFiles
#include <cstdlib>	/* exit() */
#include <cstring>
#include <app.h>
#include <nl.h>
#include <recresult.h>

#include <ctime>
#include <chrono>
#include <iostream>

#include <ctime>

#include "prompts.h"
#include <string>
#include <locale>
#include <filesystem>

#pragma endregion 

#pragma  region Variables
const char *daysWeek[7] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };
const char *month[12] = { "January", "February", "March", "April", "May", "June", "July", "August","September", "October", "November", "December" };

#pragma endregion 


using namespace std;
using namespace chrono;

//void(* DateTimeFxn)(AppStruct*);
void DateTime(App *app, int slot_value)
{
	if (slot_value == 3)
	{
		AppAppendTTSPrompt(app, "You asked: What day is it?");
		auto today = system_clock::to_time_t(system_clock::now());
		char result[100];
		strcpy(result, "Today is: ");
		strcat(result, ctime(&today));
		printf(result);
		printf("\n");
		AppAppendTTSPrompt(app, result);

	}
	else if (slot_value == 1)
	{
		AppAppendTTSPrompt(app, "You asked: What is the date");
		auto currentDate = system_clock::to_time_t(system_clock::now());

		auto _currentDay = localtime(&currentDate);
		char result[100];

		strcpy(result, "The Date is: ");
		strcat(result, daysWeek[_currentDay->tm_wday]);
		strcat(result, ", The  ");
		strcat(result, to_string(_currentDay->tm_mday).c_str());
		strcat(result, "th of ");
		strcat(result, month[_currentDay->tm_mon]);
		strcat(result, ", ");
		strcat(result, to_string(1900 + _currentDay->tm_year).c_str());

		printf(result);
		printf("\n");
		AppAppendTTSPrompt(app, result);
	}
	else if (slot_value == 2)
	{
		AppAppendTTSPrompt(app, "You asked: What time is it");
		auto currentTime = system_clock::to_time_t(system_clock::now());

		auto _currentTime = localtime(&currentTime);
		char result[100];

		strcpy(result, "The Time is: ");
		strcat(result, to_string(_currentTime->tm_hour).c_str());
		strcat(result, ": ");
		strcat(result, to_string(_currentTime->tm_min).c_str());

		printf(result);
		printf("\n");
		AppAppendTTSPrompt(app, result);
	}
}

void CoreFxn(App *app)
{
	AppSetBeginSpeechTimeout(app, float(35.0));
	AppSetEndSpeechTimeout(app, float(40.0));
	AppSetEndRecognitionTimeout(app, float(40.0));
	AppSetRejectionThreshold(app, 30);
	//AppSetEndPromptCallback(app, DateTimeFxn);
	AppSetBargeInAllowed(app, 1);
}

void CorePostRecFxn(App *app)
{
	UttStatus _status = AppGetUttStatus(app);
	switch (_status)
	{
	case UTT_NORMAL:
	case UTT_SESSION_ABORTED:
		break;
	case UTT_REJECT:
	case UTT_BEGIN_SPEECH_TIMEOUT:
	case UTT_END_SPEECH_TIMEOUT:
	case UTT_END_RECOGNITION_TIMEOUT:
		//AppAppendTTSPrompt(app, "Try again Please.");
		
		//AppGotoSelf(app);
		break;
	default:
		fprintf(stderr, "Unexpected utterance status\n");
		AppAppendTTSPrompt(app, "Try Again.");
		//AppAppendPrompt(app, "try_again.wav");
		AppGotoSelf(app);
		break;
	}
}



void IntroShevaFxn(App *app)
{
	//AppSetBargeInAllowed(app, 1);
	AppAppendTTSPrompt(app, hi_sheva);
	printf(hi_sheva);
	//AppPlayPrompts(app, 1);
	
	printf("\n");
	//AppCallCond(app, "date_time", 0, AppHasSessionEnded(app));
	
	//AppCall(app, "date_time", 0);

	//AppGotoCond(app,)
	AppGoto(app, "about_me");
}

void AboutMeFxn(App *app)
{
	AppSetRejectionThreshold(app, 30);
	//AppSetBargeInAllowed(app, 1);
	AppSetGrammar(app, ".MainGrammar");
	//AppPlayPrompts(app, 1);
	AppAppendTTSPrompt(app, about_me_question);
	printf(about_me_question);
	//AppPlayPrompts(app, 1);
	printf("\n");
	

	//Get a yes or no answer
	if (!AppRecognize(app))
	{
		AppAppendTTSPrompt(app, "Sorry I did not get that so I assume you said no.");
		printf("Sorry I did not get that so I assume you said no. \n");
		//return;
	}
	
	int yesNo;
	//Get the a yes or no reply	
	NLGetIntSlotValue(AppGetNLResult(app), yes_no_slot, &yesNo);
	if (yesNo == 0)
	{
		AppAppendTTSPrompt(app, cbt_define);
		printf(cbt_define);
		printf("\n");
	}
	else if(yesNo == 1)
	{
		AppAppendTTSPrompt(app, "Great!");
		printf("Great!");
		printf("\n");
		
	}
	else if(yesNo == 2)
	{
		int slot_value;
		NLGetIntSlotValue(AppGetNLResult(app), day_slot, &slot_value);
		DateTime(app, slot_value);
	}
	
	/*AppAppendTTSPrompt(app, corpus_guide);
	printf(corpus_guide);
	printf("\n");
*/
	AppAppendTTSPrompt(app, no_kid);
	printf(no_kid);
	printf("\n");

	AppGoto(app, "main_state");
}

void MainStateFxn(App *app)
{
	//AppSetBargeInAllowed(app, 1);
	AppSetGrammar(app, ".MainGrammar");
	AppSetRejectionThreshold(app, 30);
	
	AppAppendTTSPrompt(app, current_state);
	printf(current_state);
	printf("\n");

	
	//Get a happy, sad, or meh answer
utterance:
	if (!AppRecognize(app))
	{
		AppAppendTTSPrompt(app, "Sorry, is that a sad, happy  or meh?");
		printf("Sorry, is that a sad, happy or meh? \n");
		//AppRecognize(app);
		//goto utterance;
	}
	int userState;
	//Get a sad happy or meh response
	NLGetIntSlotValue(AppGetNLResult(app), user_state_slot, &userState);
	

	if (userState == 3)
	{
		//Sad
		AppAppendTTSPrompt(app, current_emotions);
		printf(current_emotions);
		printf("\n");

		AppAppendTTSPrompt(app, negative_emotions);
		printf(negative_emotions);
		printf("\n");

		//AppCall(app, "date_time", 0);

	utterance_one:
		if (!AppRecognize(app))
		{
			AppAppendTTSPrompt(app, "Sorry, could you describe your current emotions?");
			printf("Sorry, could you describe your current emotions? \n");

			AppAppendTTSPrompt(app, negative_emotions);
			printf(negative_emotions);
			printf("\n");

			//AppRecognize(app);
			goto utterance_one;
		}

		int userEmotion;
		//Get emotional state
		NLGetIntSlotValue(AppGetNLResult(app), user_emotion_slot, &userEmotion);
		if (userEmotion == 3)
		{
			//Hopeless
			int yesNo;

			AppAppendTTSPrompt(app, hopeless);
			printf(hopeless);
			printf("\n");

			AppRecognize(app);

			NLGetIntSlotValue(AppGetNLResult(app), yes_no_slot, &yesNo);

			if (yesNo == 1)
			{
				int _yesNo;
				//Yes
				AppAppendTTSPrompt(app, hopeless_one);
				printf(hopeless_one);
				printf("\n");

				AppRecognize(app);
				NLGetIntSlotValue(AppGetNLResult(app), yes_no_slot, &_yesNo);

				if (_yesNo == 1)
				{
					//Yes
					AppAppendTTSPrompt(app, hopeless_answer);
					printf(hopeless_answer);
					printf("\n");
				}
				else
				{
					//No
				}

				AppAppendTTSPrompt(app, hopeless_answer_question);
				printf(hopeless_answer_question);
				printf("\n");

				AppRecognize(app);
				int __yesNo;
				NLGetIntSlotValue(AppGetNLResult(app), yes_no_slot, &__yesNo);

				if (__yesNo == 1)
				{
					//Yes
					
					AppAppendTTSPrompt(app, hopeless_answer_one);
					printf(hopeless_answer_one);
					printf("\n");
				}
				else
				{
					//No
				}
				//hopeless_answer_question_one
				AppAppendTTSPrompt(app, hopeless_answer_question_one);
				printf(hopeless_answer_question_one);
				printf("\n");

				AppRecognize(app);

				//hopeless_answer_two
				int ___yesNo;
				NLGetIntSlotValue(AppGetNLResult(app), yes_no_slot, &___yesNo);

				if (___yesNo == 1)
				{
					//Yes
					AppAppendTTSPrompt(app, hopeless_answer_two);
					printf(hopeless_answer_two);
					printf("\n");

					//self_blame
					AppAppendTTSPrompt(app, self_blame);
					printf(self_blame);
					printf("\n");
					printf("Here's a link: ");
					printf(link_self_blame);
					printf("\n");

					//
				}

			}
			else
			{
				//No
			}
			AppAppendTTSPrompt(app, self_blame_worksheet);
			printf(self_blame_worksheet);
			printf("\n");

		}
		else if (userEmotion == 1)
		{
			//Depressed

			int yesNo;

			AppAppendTTSPrompt(app, depressed);
			printf(depressed);
			printf("\n");

			AppRecognize(app);
			NLGetIntSlotValue(AppGetNLResult(app), yes_no_slot, &yesNo);

			if (yesNo == 1)
			{
				//Yes
				//depressed_one

				int _yesNo;

				AppAppendTTSPrompt(app, depressed_one);
				printf(depressed_one);
				printf("\n");
				AppRecognize(app);
				NLGetIntSlotValue(AppGetNLResult(app), yes_no_slot, &_yesNo);

				if (_yesNo)
				{
					//Yes
					int __yesNo;

					AppAppendTTSPrompt(app, depressed_two);
					printf(depressed_two);
					printf("\n");
					AppRecognize(app);
					NLGetIntSlotValue(AppGetNLResult(app), yes_no_slot, &__yesNo);
					if (__yesNo)
					{
						//Yes	
						AppAppendTTSPrompt(app, depressed_two_answer);
						printf(depressed_two_answer);
						printf("\n");
					}
					else
					{
						//No Severe  depressed_three_answer
						AppAppendTTSPrompt(app, depressed_three);
						printf(depressed_three);
						printf("\n");
						AppRecognize(app);
						int ___yesNo;
						NLGetIntSlotValue(AppGetNLResult(app), yes_no_slot, &___yesNo);
						if (___yesNo == 1)
						{
							//Yes
							AppAppendTTSPrompt(app, depressed_three_answer);
							printf(depressed_three_answer);
							printf("\n");
						}
						else
						{
							//No
						}
					}
				}
				else
				{
					//No
					
				}
			}
			else
			{
				//No
				//Jokes
				//depressed_two_answer_one
				int replyAnswers;

				AppAppendTTSPrompt(app, depressed_two_answer_one);
				printf(depressed_two_answer_one);
				printf("\n");

				//Riddles from 11
				int riddleReply;

				//Riddle 11
				AppAppendTTSPrompt(app, carnation);
				printf(carnation);
				printf("\n");


				if (!AppRecognize(app))
				{
					AppAppendTTSPrompt(app, "Sorry, I did not get an answer?");
					printf("Sorry, I did not get an answer? \n");

					AppAppendTTSPrompt(app, "The answer is CAR NATION, get it. Ha");
					printf("The answer is CAR NATION, get it. Ha \n");
				}

				int riddleReply6;
				NLGetIntSlotValue(AppGetNLResult(app), reply_slot, &riddleReply);
				if (riddleReply == 11)
				{
					AppAppendTTSPrompt(app, "Correct!");
					printf("Correct! \n");
				}
				else
				{
					AppAppendTTSPrompt(app, "The answer is CAR NATION, get it. Ha");
					printf("The answer is CAR NATION, get it. Ha \n");
				}



				//Riddle 12
				AppAppendTTSPrompt(app, star_warts);
				printf(star_warts);
				printf("\n");


				if (!AppRecognize(app))
				{
					AppAppendTTSPrompt(app, "Sorry, I did not get an answer?");
					printf("Sorry, I did not get an answer? \n");

					AppAppendTTSPrompt(app, "The answer is STAR WARTS, get it. Ha");
					printf("The answer is STAR WARTS. Ha \n");
				}

				int riddleReply7;
				NLGetIntSlotValue(AppGetNLResult(app), reply_slot, &riddleReply);
				if (riddleReply == 12)
				{
					AppAppendTTSPrompt(app, "Correct!");
					printf("Correct! \n");
				}
				else
				{
					AppAppendTTSPrompt(app, "The answer is STAR WARTS, Ha");

					printf("The answer is STAR WARTS, Ha \n");
				}



				//Riddle 13
				AppAppendTTSPrompt(app, cow_bell);
				printf(cow_bell);
				printf("\n");


				if (!AppRecognize(app))
				{
					AppAppendTTSPrompt(app, "Sorry, I did not get an answer?");
					printf("Sorry, I did not get an answer? \n");

					AppAppendTTSPrompt(app, "The answer is COW BELL, get it. Ha");
					printf("The answer is COW BELL, get it. Ha \n");
				}

				int riddleReply8;
				NLGetIntSlotValue(AppGetNLResult(app), reply_slot, &riddleReply);
				if (riddleReply == 13)
				{
					AppAppendTTSPrompt(app, "Correct!");
					printf("Correct! \n");
				}
				else
				{
					AppAppendTTSPrompt(app, "The answer is COW BELL, get it. Ha");
					printf("The answer is COW BELL, get it. Ha \n");
				}



				//Riddle 14
				AppAppendTTSPrompt(app, cat_purr);
				printf(cat_purr);
				printf("\n");


				if (!AppRecognize(app))
				{
					AppAppendTTSPrompt(app, "Sorry, I did not get an answer?");
					printf("Sorry, I did not get an answer? \n");

					AppAppendTTSPrompt(app, "The answer is CAT. PURR! get it. Ha");
					printf("The answer is CAT. PURR! get it. Ha \n");
				}

				int riddleReply9;
				NLGetIntSlotValue(AppGetNLResult(app), reply_slot, &riddleReply);
				if (riddleReply == 14)
				{
					AppAppendTTSPrompt(app, "Correct!");
					printf("Correct! \n");
				}
				else
				{
					AppAppendTTSPrompt(app, "The answer is CAT. PURR! get it. Ha");
					printf("The answer is CAT. PURR! get it. Ha \n");
				}



				//Riddle 15
				AppAppendTTSPrompt(app, sour_puss);
				printf(sour_puss);
				printf("\n");


				if (!AppRecognize(app))
				{
					AppAppendTTSPrompt(app, "Sorry, I did not get an answer?");
					printf("Sorry, I did not get an answer? \n");

					AppAppendTTSPrompt(app, "The answer is SOUR PUSS, get it. Ha Ha");
					printf("The answer is SOUR PUSS, get it. Ha Ha \n");
				}

				int riddleReply10;
				NLGetIntSlotValue(AppGetNLResult(app), reply_slot, &riddleReply);
				if (riddleReply == 15)
				{
					AppAppendTTSPrompt(app, "Correct!");
					printf("Correct! \n");
				}
				else
				{
					AppAppendTTSPrompt(app, "The answer is SOUR PUSS, get it. Ha Ha");
					printf("The answer is SOUR PUSS, get it. Ha Ha \n");
				}



				//Hope I was able to make you happier
				AppAppendTTSPrompt(app, self_depreciation);
				printf(self_depreciation);
				printf("\n");

				AppAppendTTSPrompt(app, "I hope I was able to make you laugh.");
				printf("I hope I was able to make you laugh. \n");

				AppAppendTTSPrompt(app, exit_Sheva);
				printf(exit_Sheva);
				printf("\n"); printf("\n");
				AppEndSession(app);
			}
			//Jokes
		}
		else
		{
			//Suicidal
			AppAppendTTSPrompt(app, depressed_four);
			printf(depressed_four);
			printf("\n");

			printf("Here's a link : ");
			printf(emergency_services);
			printf("\n");
		}

	}
	else if (userState == 1)
	{
		//Happy
		AppAppendTTSPrompt(app, "Great! so let's try and maintain this state!");
		printf("Great! so let's try and maintain this state!");
		printf("\n");

		AppAppendTTSPrompt(app, riddle);
		printf(riddle);
		printf("\n");

	utterance_two:
		if (!AppRecognize(app))
		{
			AppAppendTTSPrompt(app, "Sorry, is that a yes or no?");
			printf("Sorry, is that a yes or no \n");
			//AppRecognize(app);
			goto utterance_two;
		}

		int yesNo;
		//Get a yes no reply
		NLGetIntSlotValue(AppGetNLResult(app), yes_no_slot, &yesNo);
		if (yesNo == 0)
		{
			//No Bye
			AppAppendTTSPrompt(app, exit_Sheva);
			printf(exit_Sheva);
			printf("\n");
			AppEndSession(app);
			//return;
		}
		else
		{
			//Yes
			//Five riddles From 6
			int riddleReply;

			//Riddle 6
			AppAppendTTSPrompt(app, cereal_killer);
			printf(cereal_killer);
			printf("\n");


			if (!AppRecognize(app))
			{
				AppAppendTTSPrompt(app, "Sorry, I did not get an answer?");
				printf("Sorry, I did not get an answer? \n");

				AppAppendTTSPrompt(app, "The answer is CEREAL KILLER, get it. Ha");
				printf("The answer is CEREAL KILLER, get it. Ha \n");
			}

			int riddleReply6;
			NLGetIntSlotValue(AppGetNLResult(app), reply_slot, &riddleReply);
			if (riddleReply == 6)
			{
				AppAppendTTSPrompt(app, "Correct!");
				printf("Correct! \n");
			}
			else
			{
				AppAppendTTSPrompt(app, "The answer is CEREAL KILLER AIDE, get it. Ha");
				printf("The answer is CEREAL KILLER, get it. Ha \n");
			}



			//Riddle 7
			AppAppendTTSPrompt(app, canned_carrot);
			printf(canned_carrot);
			printf("\n");


			if (!AppRecognize(app))
			{
				AppAppendTTSPrompt(app, "Sorry, I did not get an answer?");
				printf("Sorry, I did not get an answer? \n");

				AppAppendTTSPrompt(app, "The answer is CANNED CARROT, get it. Ha");
				printf("The answer is CANNED CARROT. Ha \n");
			}

			int riddleReply7;
			NLGetIntSlotValue(AppGetNLResult(app), reply_slot, &riddleReply);
			if (riddleReply == 7)
			{
				AppAppendTTSPrompt(app, "Correct!");
				printf("Correct! \n");
			}
			else
			{
				AppAppendTTSPrompt(app, "The answer is CANNED CARROT, Ha");

				printf("The answer is CANNED CARROT, Ha \n");
			}



			//Riddle 8
			AppAppendTTSPrompt(app, serial_killer);
			printf(serial_killer);
			printf("\n");


			if (!AppRecognize(app))
			{
				AppAppendTTSPrompt(app, "Sorry, I did not get an answer?");
				printf("Sorry, I did not get an answer? \n");

				AppAppendTTSPrompt(app, "The answer is SERIAL KILLER, get it. Ha");
				printf("The answer is SERIAL KILLER, get it. Ha \n");
			}

			int riddleReply8;
			NLGetIntSlotValue(AppGetNLResult(app), reply_slot, &riddleReply);
			if (riddleReply == 8)
			{
				AppAppendTTSPrompt(app, "Correct!");
				printf("Correct! \n");
			}
			else
			{
				AppAppendTTSPrompt(app, "The answer is SERIAL KILLER, get it. Ha");
				printf("The answer is SERIAL KILLER, get it. Ha \n");
			}



			//Riddle 9
			AppAppendTTSPrompt(app, dog_ruff);
			printf(dog_ruff);
			printf("\n");


			if (!AppRecognize(app))
			{
				AppAppendTTSPrompt(app, "Sorry, I did not get an answer?");
				printf("Sorry, I did not get an answer? \n");

				AppAppendTTSPrompt(app, "The answer is DOG. RUFF! get it. Ha");
				printf("The answer is DOG. RUFF! get it. Ha \n");
			}

			int riddleReply9;
			NLGetIntSlotValue(AppGetNLResult(app), reply_slot, &riddleReply);
			if (riddleReply == 9)
			{
				AppAppendTTSPrompt(app, "Correct!");
				printf("Correct! \n");
			}
			else
			{
				AppAppendTTSPrompt(app, "The answer is DOG. RUFF! get it. Ha");
				printf("The answer is DOG. RUFF! get it. Ha \n");
			}



			//Riddle 10
			AppAppendTTSPrompt(app, sour_milk);
			printf(sour_milk);
			printf("\n");


			if (!AppRecognize(app))
			{
				AppAppendTTSPrompt(app, "Sorry, I did not get an answer?");
				printf("Sorry, I did not get an answer? \n");

				AppAppendTTSPrompt(app, "The answer is SOUR MILK, get it. Ha Ha");
				printf("The answer is SOUR MILK, get it. Ha Ha \n");
			}

			int riddleReply10;
			NLGetIntSlotValue(AppGetNLResult(app), reply_slot, &riddleReply);
			if (riddleReply == 10)
			{
				AppAppendTTSPrompt(app, "Correct!");
				printf("Correct! \n");
			}
			else
			{
				AppAppendTTSPrompt(app, "The answer is SOUR MILK, get it. Ha Ha");
				printf("The answer is SOUR MILK, get it. Ha Ha \n");
			}



			//Hope I was able to make you happier
			AppAppendTTSPrompt(app, self_depreciation);
			printf(self_depreciation);
			printf("\n");

			AppAppendTTSPrompt(app, "I hope I was able to make you laugh.");
			printf("I hope I was able to make you laugh. \n");

			AppAppendTTSPrompt(app, exit_Sheva);
			printf(exit_Sheva);

			return;

		}
	}
	else
	{
		//Meh
		AppAppendTTSPrompt(app, "OK! so let's try and get you from a meh to Happy!");
		printf("OK! so let's try and get you from a meh to Happy!");
		printf("\n");

		AppAppendTTSPrompt(app, riddle);
		printf(riddle);
		printf("\n");

	utterance_three:
		if (!AppRecognize(app))
		{
			AppAppendTTSPrompt(app, "Sorry, is that a yes or no?");
			printf("Sorry, is that a yes or no \n");
			//AppRecognize(app);
			goto utterance_three;
		}

		int yesNo;
		//Get a yes no reply
		NLGetIntSlotValue(AppGetNLResult(app), yes_no_slot, &yesNo);
		if (yesNo == 0)
		{
			//No Bye
			AppAppendTTSPrompt(app, exit_Sheva);
			printf(exit_Sheva);
			printf("\n");
			AppPlayPrompts(app, 1);
			AppEndSession(app);
		}
		else
		{
			//Yes
			//Five riddles

			//Riddle 1
			AppAppendTTSPrompt(app, bandaide);
			printf(bandaide);
			printf("\n");


			if (!AppRecognize(app))
			{
				AppAppendTTSPrompt(app, "Sorry, I did not get an answer?");
				printf("Sorry, I did not get an answer? \n");

				AppAppendTTSPrompt(app, "The answer is BAND AIDE, get it. Ha Ha");
				printf("The answer is BAND AIDE, get it. Ha Ha \n");
			}

			int riddleReply1;
			NLGetIntSlotValue(AppGetNLResult(app), reply_slot, &riddleReply1);
			if (riddleReply1 == 1)
			{
				AppAppendTTSPrompt(app, "Correct!");
				printf("Correct! \n");
			}
			else
			{
				AppAppendTTSPrompt(app, "The answer is BAND AIDE, get it. Ha Ha");
				printf("The answer is BAND AIDE, get it. Ha Ha \n");
			}



			//Riddle 2
			AppAppendTTSPrompt(app, cartune);
			printf(cartune);
			printf("\n");


			if (!AppRecognize(app))
			{
				AppAppendTTSPrompt(app, "Sorry, I did not get an answer?");
				printf("Sorry, I did not get an answer? \n");

				AppAppendTTSPrompt(app, "The answer is CAR TUNE, get it. Ha");
				printf("The answer is CAR TUNE. Ha \n");
			}

			int riddleReply2;
			NLGetIntSlotValue(AppGetNLResult(app), reply_slot, &riddleReply2);
			if (riddleReply2 == 2)
			{
				AppAppendTTSPrompt(app, "Correct!");
				printf("Correct! \n");
			}
			else
			{
				AppAppendTTSPrompt(app, "The answer is CAR TUNE, Ha");

				printf("The answer is CAR TUNE, Ha \n");
			}



			//Riddle 3
			AppAppendTTSPrompt(app, flower_power);
			printf(flower_power);
			printf("\n");


			if (!AppRecognize(app))
			{
				AppAppendTTSPrompt(app, "Sorry, I did not get an answer?");
				printf("Sorry, I did not get an answer? \n");

				AppAppendTTSPrompt(app, "The answer is FLOWER POWER, get it. Ha Ha");
				printf("The answer is FLOWER POWER, get it. Ha Ha \n");
			}

			int riddleReply3;
			NLGetIntSlotValue(AppGetNLResult(app), reply_slot, &riddleReply3);
			if (riddleReply3 == 3)
			{
				AppAppendTTSPrompt(app, "Correct!");
				printf("Correct! \n");
			}
			else
			{
				AppAppendTTSPrompt(app, "The answer is FLOWER POWER, get it. Ha Ha");
				printf("The answer is FLOWER POWER, get it. Ha Ha \n");
			}



			//Riddle 4
			AppAppendTTSPrompt(app, pork_chops);
			printf(pork_chops);
			printf("\n");


			if (!AppRecognize(app))
			{
				AppAppendTTSPrompt(app, "Sorry, I did not get an answer?");
				printf("Sorry, I did not get an answer? \n");

				AppAppendTTSPrompt(app, "The answer is PORK CHOPS, get it. Ha Ha");
				printf("The answer is PORK CHOPS, get it. Ha Ha \n");
			}

			int riddleReply4;
			NLGetIntSlotValue(AppGetNLResult(app), reply_slot, &riddleReply4);
			if (riddleReply4 == 4)
			{
				AppAppendTTSPrompt(app, "Correct!");
				printf("Correct! \n");
			}
			else
			{
				AppAppendTTSPrompt(app, "The answer is PORK CHOPS, get it. Ha Ha");
				printf("The answer is PORK CHOPS, get it. Ha Ha \n");
			}



			//Riddle 5
			AppAppendTTSPrompt(app, fast_food);
			printf(fast_food);
			printf("\n");


			if (!AppRecognize(app))
			{
				AppAppendTTSPrompt(app, "Sorry, I did not get an answer?");
				printf("Sorry, I did not get an answer? \n");

				AppAppendTTSPrompt(app, "The answer is FAST FOOD, get it. Ha Ha");
				printf("The answer is FAST FOOD, get it. Ha Ha \n");
			}

			int riddleReply5;
			NLGetIntSlotValue(AppGetNLResult(app), reply_slot, &riddleReply5);
			if (riddleReply5 == 5)
			{
				AppAppendTTSPrompt(app, "Correct!");
				printf("Correct! \n");
			}
			else
			{
				AppAppendTTSPrompt(app, "The answer is FAST FOOD, get it. Ha Ha");
				printf("The answer is FAST FOOD, get it. Ha Ha \n");
			}



			//Hope I was able to make you happier
			AppAppendTTSPrompt(app, "I hope I was able to make you laugh.");
			printf("I hope I was able to make you laugh. \n");

			AppAppendTTSPrompt(app, exit_Sheva);
			printf(exit_Sheva);
			//AppEndSession(app);
			return;

		}
	}

}

void DateTimeFxn(App *app)
{
	AppSetRejectionThreshold(app, 30);
	AppSetGrammar(app, ".MainGrammar");
	AppRecognize(app);
	
	//Set The Grammar File
	//AppSetGrammar(app, ".DateTime");


	if (!AppRecognize(app))
	{
		AppAppendTTSPrompt(app, "Sorry I did not catch that");
		printf("Sorry I did not catch that... \n");
		//AppGo(app, "main_state");
		//AppCall(app, "date_time",0);
		
		//AppReturn(app, 0);
		//goto  returnline;
	}

	//Get the current date and/or Time
	int enumCode;
	NLGetIntSlotValue(AppGetNLResult(app), day_slot, &enumCode);
	if (enumCode == 3)
	{
		AppAppendTTSPrompt(app, "You asked: What day is it?");
		auto today = system_clock::to_time_t(system_clock::now());
		char result[100];
		strcpy(result, "Today is: ");
		strcat(result, ctime(&today));
		printf(result);
		printf("\n");
		AppAppendTTSPrompt(app, result);

	}
	else if (enumCode == 1)
	{
		AppAppendTTSPrompt(app, "You asked: What is the date");
		auto currentDate = system_clock::to_time_t(system_clock::now());

		auto _currentDay = localtime(&currentDate);
		char result[100];

		strcpy(result, "The Date is: ");
		strcat(result, daysWeek[_currentDay->tm_wday]);
		strcat(result, ", The  ");
		strcat(result, to_string(_currentDay->tm_mday).c_str());
		strcat(result, "th of ");
		strcat(result, month[_currentDay->tm_mon]);
		strcat(result, ", ");
		strcat(result, to_string(1900 + _currentDay->tm_year).c_str());

		printf(result);
		printf("\n");
		AppAppendTTSPrompt(app, result);
	}
	else if (enumCode == 2)
	{
		AppAppendTTSPrompt(app, "You asked: What time is it");
		auto currentTime = system_clock::to_time_t(system_clock::now());

		auto _currentTime = localtime(&currentTime);
		char result[100];

		strcpy(result, "The Time is: ");
		strcat(result, to_string(_currentTime->tm_hour).c_str());
		strcat(result, ": ");
		strcat(result, to_string(_currentTime->tm_min).c_str());

		printf(result);
		printf("\n");
		AppAppendTTSPrompt(app, result);
	}

	//AppGotoSelf(app);
	//AppReturn(app, 0);
	AppGoto(app, "main_state");
	//goto returnline;
}



int main(int argc, char* argv[])
{
	App *app = AppNew(&argc, argv);


	if (app == NULL)
	{
		exit(-1);
	}


	//App Creating Classes
	AppCreateStateClass(app, "root", nullptr, CoreFxn, CorePostRecFxn);
//	AppCreateState(app, "user_intro", "root", UserIntroTxn);
	AppCreateState(app, "intro_sheva", "root", IntroShevaFxn);
	AppCreateState(app, "about_me", "root", AboutMeFxn);
	AppCreateState(app, "main_state", "root", MainStateFxn);
	//AppCreateState(app, "date_time", "root", DateTimeFxn);
	//AppSetEndPromptCallback(app, DateTimeFxn);
	AppGo(app, "intro_sheva");
	
	return 0;
}
