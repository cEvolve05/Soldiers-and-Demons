#include <graphics.h>
#include <iostream>

#include "include.h"
#pragma execution_character_set("utf-8")

#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"

void data_callback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount)
{
	ma_decoder* pDecoder = (ma_decoder*)pDevice->pUserData;
	if (pDecoder == NULL) {
		return;
	}

	/* Reading PCM frames will loop based on what we specified when called ma_data_source_set_looping(). */
	ma_data_source_read_pcm_frames(pDecoder, pOutput, frameCount, NULL);

	(void)pInput;
}

int main()
{

	ma_result result;
	ma_decoder decoder;
	ma_device_config deviceConfig;
	ma_device device;

	result = ma_decoder_init_file("./Resource/Gaming-fix.mp3", NULL, &decoder);
	if (result != MA_SUCCESS) {
		return -2;
	}

	/*
	A decoder is a data source which means we just use ma_data_source_set_looping() to set the
	looping state. We will read data using ma_data_source_read_pcm_frames() in the data callback.
	*/
	ma_data_source_set_looping(&decoder, MA_TRUE);

	deviceConfig = ma_device_config_init(ma_device_type_playback);
	deviceConfig.playback.format = decoder.outputFormat;
	deviceConfig.playback.channels = decoder.outputChannels;
	deviceConfig.sampleRate = decoder.outputSampleRate;
	deviceConfig.dataCallback = data_callback;
	deviceConfig.pUserData = &decoder;

	if (ma_device_init(NULL, &deviceConfig, &device) != MA_SUCCESS) {
		printf("Failed to open playback device.\n");
		ma_decoder_uninit(&decoder);
		return -3;
	}

	if (ma_device_start(&device) != MA_SUCCESS) {
		printf("Failed to start playback device.\n");
		ma_device_uninit(&device);
		ma_decoder_uninit(&decoder);
		return -4;
	}

	srand((unsigned int)time(NULL));
	game SOD;
	SOD.entry();
	getchar();

	ma_device_uninit(&device);
	ma_decoder_uninit(&decoder);

	return 0;
}
/*
#include <graphics.h>
#include <iostream>
#include <winuser.h>

#include <wchar.h>//Debug

#include "resource.h"
#include "role_buried.h"
#include "board_buried.h"

//#define DEBUGG

using namespace std;

int main()
{
	const int windowX = 500;
	const int windowY = 500;
	const POINT windowPoint[] = { {0,0},{0,windowY},{windowX,windowY},{windowX,0} };
	//const wchar_t playerImagePath[] = L"player.png";
	ExMessage m;
	//IMAGE player;
	//POINT playerLocation = { windowX / 2, windowY / 2 };
	char userLastInput = 0;
	int InputRequireProcess = 0;

	initgraph(windowX, windowY, EX_SHOWCONSOLE);

	role testRole;
	board testBoard;


	//loadimage(&player, L"PNG", MAKEINTRESOURCE(testRoleImg));
	testRole.setRoleImg(L"PNG", MAKEINTRESOURCE(testRoleImg));
	testRole.setLocation({ windowX / 2, windowY / 2 });

	testBoard.setBoardLocation({ 0,0 });
	testBoard.setBoardSize({ 5,5 });
	testBoard.setGridSize({ 90,90 });

	//IMPORTANT: must flush draw after every draw
	BeginBatchDraw();

	//player need to be encapsulated
	//
	//putimage(playerLocation.x, playerLocation.y, &player);
	testBoard.render();
	testRole.render();

	LINESTYLE pstyle;
	getlinestyle(&pstyle);
	DWORD lineWidth = pstyle.thickness;
	cout << lineWidth;

	FlushBatchDraw();

	while (true)
	{
		//flushmessage(EX_MOUSE | EX_CHAR);
		//Input Process
		while (peekmessage(&m, EX_MOUSE | EX_KEY))
		{
			switch (m.message)
			{
			case WM_MOUSEMOVE:
				putpixel(m.x, m.y, RED);
				break;

			case WM_KEYDOWN:

#ifdef DEBUG
				cout << "KEY_DOWN" << m.vkcode << "   " << GetKeyState(userLastInput);
#endif // DEBUG

				//switch (m.vkcode)
				//{
				//case 'W':
				//	userLastInput = 'W';
				//	break;

				//case 'S':
				//	userLastInput = 'S';
				//	break;

				//case 'A':
				//	userLastInput = 'A';
				//	break;

				//case 'D':
				//	userLastInput = 'D';
				//	break;

				//case VK_ESCAPE:
				//	closegraph();
				//	return 0;

				//default:
				//	break;
				//}

				if (m.vkcode == VK_ESCAPE)
				{
					closegraph();
					return 0;
				}
				if (m.vkcode == 'W' || m.vkcode == 'S' || m.vkcode == 'A' || m.vkcode == 'D')
				{
					if (m.vkcode==userLastInput)
					{
						InputRequireProcess = 0;
					}
					userLastInput = m.vkcode;
				}
				

			case WM_KEYUP:

#ifdef DEBUG
				cout << "KEY_UP" << m.vkcode << "   " << GetKeyState(userLastInput);
#endif // DEBUG

				if (m.vkcode == userLastInput && ~(GetKeyState(userLastInput) >> 7))
					userLastInput = 0;
				break;

			default:
				break;
			}
#ifdef DEBUG
			cout << "               " << m.vkcode << " & " << userLastInput << endl;//Debug
#endif // DEBUG
		}

		//Object Update
		switch (userLastInput)
		{
		case 'W':
			testRole.shiftLocation({0,-5});
			InputProcessed = 1;
			break;

		case 'S':
			testRole.shiftLocation({ 0,5 });
			InputProcessed = 1;
			break;

		case 'A':
			testRole.shiftLocation({ -5,0 });
			InputProcessed = 1;
			break;

		case 'D':
			testRole.shiftLocation({ 5,0});
			InputProcessed = 1;
			break;

		default:
			break;
		}

#ifdef DEBUG
		cout << "                              " << playerLocation.x << " & " << playerLocation.y << endl;//Debug
#endif // DEBUG

		//Render
		clearpolygon(windowPoint, 4);
		//putimage(testRole.roleLocation.x, testRole.roleLocation.y, &player);
		testBoard.render(); 
		testRole.render();
		FlushBatchDraw();
		Sleep(17);
	}

	return 0;
}


*/