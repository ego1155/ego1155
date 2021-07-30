#include "main.h"

static int count = 0;
void CronFunc1(void)
{
	sc_log_info("CronFunc1 is running...\n");
	count++;
}
void CronFunc2(void)
{
	sc_log_info("CronFunc2 is running...\n");
	count++;
}

int main()
{
	sc_log_init();
	sc_log_set_file("log.0.txt", "log-latest.txt");
	sc_log_info("Hello world!\n");
	sc_log_info("to stdout and file!\n");
    sc_log_info("to all!\n");
	sc_log_error("helo error...\n");
	sc_log_debug("helo debug...\n");
	sc_log_warn("helo warn...\n");
	
	if( access( "PfxApp.ini", F_OK ) != -1)
	{
		printf("PfxApp.ini exits\n");
		
		FILE* fp = fopen( "PfxApp.ini", "r" );
        fseek( fp, 0, SEEK_END );
        int size = ftell( fp );
        fseek( fp, 0, SEEK_SET );
        char* data = (char*) malloc( size + 1 );
        fread( data, 1, size, fp );
        data[ size ] = '\0';
        fclose( fp );
        ini_t* ini = ini_load( data, NULL );
        free( data );
		
		int section, idx;
		section = ini_find_section( ini, "PfxApp", 6 );
		if (section == INI_NOT_FOUND)
			exit(EXIT_FAILURE);
        idx = ini_find_property( ini, section, "WebPort", 7 );
		if (idx == INI_NOT_FOUND)
			exit(EXIT_FAILURE);
        char const* webPort = ini_property_value( ini, section, idx );
        printf( "%s=%s\n", "WebPort", webPort );
        idx = ini_find_property( ini, section, "WebOpenAuto", 11 );
		if (idx == INI_NOT_FOUND)
			exit(EXIT_FAILURE);
        char const* webOpenAuto = ini_property_value( ini, section, idx );
        printf( "%s=%s\n", "WebOpenAuto", webOpenAuto );
		
        ini_destroy( ini );
	}
	else
	{
		printf("PfxApp.ini does not exits\n");
		
		ini_t* ini = ini_create(NULL);
		int section_pfxapp = ini_section_add( ini, "PfxApp", 6 );
		ini_property_add( ini, section_pfxapp, "WebPort", 7, "9876", 4 );
		ini_property_add( ini, section_pfxapp, "WebOpenAuto", 11, "True", 4 );

		int size = ini_save( ini, NULL, 0 ); // Find the size needed
		char* data = (char*) malloc( size );
		size = ini_save( ini, data, size ); // Actually save the file
		ini_destroy( ini );

		FILE* fp = fopen( "PfxApp.ini", "w" );
		fwrite( data, 1, size, fp );
		fclose( fp );
		free( data );
	}
	
	cron_expr expr;
	const char* err = NULL;
	memset(&expr, 0, sizeof(expr));
	cron_parse_expr("0 */2 * * * *", &expr, &err);
	//if (err) ... /* invalid expression */
	time_t cur = time(NULL);
	time_t next = cron_next(&expr, cur);
	printf("cur :: %s", ctime(&cur));
	printf("next :: %s", ctime(&next));
	//while(cur < next)
	//{
		//cur = time(NULL);
		//if (cur >= next)
		//{
			//printf("next :: %s", ctime(&next));
		//}
	//}
	
	cronjob* cj = cronjob_init();
	for(int i=1; i<10; i++)
	{
	//cj->add_task(cj, 1, "*/30 * * * * *", CronFunc1);
	//cj->add_task(cj, 2, "0 */1 * * * *", CronFunc2);
		cj->add_task(cj, i, "*/30 * * * * *", CronFunc1);
	}
	while (count<10) {
		cj->process_task(cj);
		usleep(500000);//500 millisecond
	}
	cronjob_deinit(cj);
	
	printf("main.c\n");
	one();
	two();
	
	LIBSSH2_SESSION *session;
	LIBSSH2_LISTENER *listener = NULL;
	LIBSSH2_CHANNEL *channel = NULL;
	int rc = libssh2_init(0);
	if(rc != 0) {
        	fprintf(stderr, "libssh2 initialization failed (%d)\n", rc);
        	return 1;
	}
	session = libssh2_session_init();
#ifdef _WIN64
	printf("\nSecureTcp Win64\n\n");
#elif __APPLE__
	printf("\nSecureTcp MacOsX\n\n");
#elif __linux
	printf("\nSecureTcp Linux\n\n");
#elif __unix
	printf("\nSecureTcp Unix\n\n");
#elif __posix
	printf("\nSecureTcp Posix\n\n");
#endif
	printf("\nSecureTcp\n\n");
	libssh2_session_free(session);
	libssh2_exit();
	
	sc_log_term();
	return EXIT_SUCCESS;
}