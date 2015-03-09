/*
 * sd_tests.c
 *
 * Created: 04/12/2014
 *  Author: Rafael B. Januzi
 */ 

#include <sd_tests.h>

bool sd_exec_test( int testNumber )
{
	int i, aux, paramsSize = 1; /* Nao tem parametro, mas quando o paramsSize eh 0 esta ocorrendo um erro. (Atividade futura corrigir) */
	cmd_frame_t cmdFrame, ansFrame;
	bool result;
	
	cmdFrame = newEmptyTestCmdFrame(testNumber, paramsSize);
	
	//Notifica o CC sobre a execucao do teste 01 e envia os dados auxiliares.
	sendTestCmdFrame(cmdFrame);
	
	print_dbg("\n\nTest command sent: ");
	printfCmd(cmdFrame);
	
	ansFrame = rcvTestCmdAnswer();
	if(ansFrame.magicCode != 0)
	{
		if( ansFrame.data[0] == PARAM_TEST_FAIL )
		{
			result = false;
			print_dbg( "\n\nFAIL" );
		}
		else
		{
			result = true;
			print_dbg( "\n\nPASS" );
		}
		
		print_dbg("\n\nTest answer received: ");
		printfCmd(ansFrame);
		freeCmdFrame(ansFrame);
	}
	else
	{
		print_dbg( "\n\nFAIL" );
		result = false;
	}
	
	return result;
}

void sd_test_all()
{
	sd_test_01();
	sd_test_02();
	sd_test_03();
}

bool sd_test_01()
{	
	print_dbg("\n\n==============================\nExecutando sd teste 01...\n==============================\n");
	
	return sd_exec_test( 1+SD_TEST_NUMBER_OFFSET );
}

bool sd_test_02()
{
	print_dbg("\n\n==============================\nExecutando sd teste 02...\n==============================\n");
	
	return sd_exec_test( 2+SD_TEST_NUMBER_OFFSET );
}

bool sd_test_03()
{
	print_dbg("\n\n==============================\nExecutando sd teste 03...\n==============================\n");
	
	return sd_exec_test( 3+SD_TEST_NUMBER_OFFSET );
}

bool sd_test_04()
{
	print_dbg("\n\n==============================\nExecutando sd teste 04...\n==============================\n");
	
	return sd_exec_test( 4+SD_TEST_NUMBER_OFFSET );
}