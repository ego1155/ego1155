#include "main.h"

assetsys_t* assetsys = NULL;
filewatch_t* filewatch = NULL;

bool isShutdown=false;
bool isRestart=false;

void watch_callback(filewatch_update_t change, const char* virtual_path, void* udata)
{
	const char* change_string = 0;
	switch (change)
	{
		case FILEWATCH_DIR_ADDED:
			change_string = "FILEWATCH_DIR_ADDED";
			break;
		case FILEWATCH_DIR_REMOVED:
			change_string = "FILEWATCH_DIR_REMOVED";
			break;
		case FILEWATCH_FILE_ADDED:
			change_string = "FILEWATCH_FILE_ADDED";
			break;
		case FILEWATCH_FILE_REMOVED:
			change_string = "FILEWATCH_FILE_REMOVED";
			break;
		case FILEWATCH_FILE_MODIFIED:
			change_string = "FILEWATCH_FILE_MODIFIED";
			break;
	}
	//printf("%s at %s.\n", change_string, virtual_path);
	char* fName = sc_str_create(virtual_path);
	sc_str_replace(&fName, "/", "\\");
	printf( "%s at %s\n", change_string, fName );
	sc_str_destroy(&fName);
	
	time_t t;
    time(&t);
	
	char* path = (char*)malloc(1000 * sizeof(char));
	sprintf(path, "log_dataprotection_%s", ctime(&t));
	char* path2 = (char*)malloc(1000 * sizeof(char));
	sprintf(path2, "log_dataprotection_latest_%s", ctime(&t));
	sc_log_init();
	sc_log_set_file(path, path2);
	sc_log_info("Virus attack occured...at $s\n", ctime(&t));
	sc_log_term();
	free(path);
	free(path2);
	if (isShutdown)
		system("c:\\windows\\system32\\shutdown /s /t 0");
	if (isRestart)
		system("c:\\windows\\system32\\shutdown /r /t 0");
}

int main(int argc, char *argv[])
{
	if( argc == 2 )
	{
		if (strcmp("--config",argv[1]) == 0)
		{
			if( access( "Config.ini", F_OK ) != -1)
			{
				printf("Config.ini exits.\n");
				exit(EXIT_SUCCESS);
			}
		
			ini_t* ini = ini_create(NULL);
			int section_config = ini_section_add( ini, "Config", 6 );
			ini_property_add( ini, section_config, "Folder", 6, "", 0 );
			
			int section_system = ini_section_add( ini, "System", 6 );
			ini_property_add( ini, section_system, "Shutdown", 8, "False", 5 );
			ini_property_add( ini, section_system, "Restart", 7, "False", 5 );

			int size = ini_save( ini, NULL, 0 ); // Find the size needed
			char* data = (char*) malloc( size );
			size = ini_save( ini, data, size ); // Actually save the file
			ini_destroy( ini );

			FILE* fp = fopen( "Config.ini", "w" );
			fwrite( data, 1, size, fp );
			fclose( fp );
			free( data );
			
			printf("Config.ini created.\n");
		}
		else if (strcmp("--watcher",argv[1]) == 0)
		{
			if( access( "Config.ini", F_OK ) != -1)
			{
				FILE* fp = fopen( "Config.ini", "r" );
				fseek( fp, 0, SEEK_END );
				int size = ftell( fp );
				fseek( fp, 0, SEEK_SET );
				char* data = (char*) malloc( size + 1 );
				fread( data, 1, size, fp );
				data[ size ] = '\0';
				fclose( fp );
				ini_t* ini = ini_load( data, NULL );
				free( data );
				
				int section, count, i, idx;
				
				section = ini_find_section( ini, "System", 6 );
				if (section == INI_NOT_FOUND)
					exit(EXIT_FAILURE);
				idx = ini_find_property( ini, section, "Shutdown", 8 );
				if (idx == INI_NOT_FOUND)
					exit(EXIT_FAILURE);
				char const* shdn = ini_property_value( ini, section, idx );
				idx = ini_find_property( ini, section, "Restart", 7 );
				if (idx == INI_NOT_FOUND)
					exit(EXIT_FAILURE);
				char const* rst = ini_property_value( ini, section, idx );
				
				if (strcmp(shdn, "True")==0)
					isShutdown=true;
				if (strcmp(rst, "True")==0)
					isRestart=true;
				
				section = ini_find_section( ini, "Config", 6 );
				if (section == INI_NOT_FOUND)
					exit(EXIT_FAILURE);
				count = ini_property_count( ini, section );
				if (count <= 0)
					exit(EXIT_FAILURE);
				if (!assetsys && !filewatch)
				{
					assetsys = assetsys_create(0);
					filewatch = filewatch_create(assetsys, 0);
					
					for(i=0; i<count; i++)
					{
						char const* field = ini_property_value( ini, section, i );
						char* fdName = sc_str_create(field);
						strip_trailing_slashes(fdName);
						printf( "%s=%s\n", "Folder", fdName );
						filewatch_mount(filewatch, fdName, fdName);
						filewatch_start_watching(filewatch, fdName, watch_callback, 0);
						sc_str_destroy(&fdName);
					}
					ini_destroy( ini );
					while (!GetAsyncKeyState(VK_ESCAPE))
					{
						filewatch_update(filewatch);
						filewatch_notify(filewatch);
						Sleep(100);
					}
					filewatch_stop_watching(filewatch, "/data");
					filewatch_free(filewatch);
					assetsys_destroy(assetsys);
				}
				ini_destroy( ini );
			}
		}
	}
	return EXIT_SUCCESS;
}
