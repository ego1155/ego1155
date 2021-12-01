#include "unzip.h"

int unzip(const char *fname, const char *path)
{
#ifdef __unix__
	const char dir_separator = '/';
#elif _WIN32
	const char dir_separator = '\\';
#endif
	// Open the zip file
    unzFile *zipfile = unzOpen( fname );
    if ( zipfile == NULL )
    {
        //printf( "%s: not found\n" );
        return -1;
    }

    // Get info about the zip file
    unz_global_info global_info;
    if ( unzGetGlobalInfo( zipfile, &global_info ) != UNZ_OK )
    {
        //printf( "could not read file global info\n" );
        unzClose( zipfile );
        return -1;
    }

    // Buffer to hold data read from the zip file.
    char read_buffer[ READ_SIZE ];

    // Loop to extract all files
    uLong i;
    for ( i = 0; i < global_info.number_entry; ++i )
    {
        // Get info about current file.
        unz_file_info file_info;
        char filename[ MAX_FILENAME ];
        if ( unzGetCurrentFileInfo(
            zipfile,
            &file_info,
            filename,
            MAX_FILENAME,
            NULL, 0, NULL, 0 ) != UNZ_OK )
        {
            //printf( "could not read file info\n" );
            unzClose( zipfile );
            return -1;
        }
		
		char fname[ MAX_FILENAME * 2 ];
		if (path)
		{
			const size_t path_length = strlen( path );
			strcpy(fname,path);
			if ( path[ path_length-1 ] != dir_separator )
			{
				char cToStr[2];
				cToStr[0] = dir_separator;
				cToStr[1] = '\0';
				strcat(fname,cToStr);
			}
			strcat(fname,filename);
		}
		else
		{
			strcpy(fname,filename);
		}

        // Check if this entry is a directory or file.
        const size_t filename_length = strlen( fname );
        if ( fname[ filename_length-1 ] == dir_delimter )
        {
            // Entry is a directory, so create it.
            //printf( "dir:%s\n", filename );
            mkdir( fname );
        }
        else
        {
            // Entry is a file, so extract it.
            //printf( "file:%s\n", filename );
            if ( unzOpenCurrentFile( zipfile ) != UNZ_OK )
            {
                //printf( "could not open file\n" );
                unzClose( zipfile );
                return -1;
            }

            // Open a file to write out the data.
            FILE *out = fopen( fname, "wb" );
            if ( out == NULL )
            {
                //printf( "could not open destination file\n" );
                unzCloseCurrentFile( zipfile );
                unzClose( zipfile );
                return -1;
            }

            int error = UNZ_OK;
            do    
            {
                error = unzReadCurrentFile( zipfile, read_buffer, READ_SIZE );
                if ( error < 0 )
                {
                    //printf( "error %d\n", error );
                    unzCloseCurrentFile( zipfile );
                    unzClose( zipfile );
                    return -1;
                }

                // Write data to file.
                if ( error > 0 )
                {
                    fwrite( read_buffer, error, 1, out ); // You should check return of fwrite...
                }
            } while ( error > 0 );

            fclose( out );
        }

        unzCloseCurrentFile( zipfile );

        // Go the the next entry listed in the zip file.
        if ( ( i+1 ) < global_info.number_entry )
        {
            if ( unzGoToNextFile( zipfile ) != UNZ_OK )
            {
                //printf( "cound not read next file\n" );
                unzClose( zipfile );
                return -1;
            }
        }
    }

    unzClose( zipfile );
	
	return 1;
}