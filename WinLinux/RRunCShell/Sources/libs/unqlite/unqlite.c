#include "unqlite.h"

unqldb *unqldb_init(const char *path)
{
	unqldb *self = (unqldb *)malloc(sizeof(unqldb));
	if (self == NULL)
		return self;
	
	int rc;
	rc = unqlite_open(&self->db,path,UNQLITE_OPEN_CREATE);
	if( rc != UNQLITE_OK )
	{
		unqldb_deinit(self);
		return self;
	}

	self->add = unqldb_add;
	self->append = unqldb_append;
	self->get = unqldb_get;
	self->get_size = unqldb_get_size;
	self->del = unqldb_del;
	self->add_file = unqldb_add_file;
	self->backup = unqldb_backup;
	return self;
}

void unqldb_deinit(unqldb *self)
{
	unqlite_close(self->db);

	free(self);
	self = NULL;
}

int unqldb_add(unqldb *self, const char *key, const char *value)
{
	int rc;
	rc = unqlite_kv_store(self->db ,key,-1,value,strlen(value));
	if( rc != UNQLITE_OK )
		return 0;
	return 1;
}

int unqldb_append(unqldb *self, const char *key, const char *value)
{
	int rc;
	rc = unqlite_kv_append(self->db ,key,-1,value,strlen(value));
	if( rc != UNQLITE_OK )
		return 0;
	return 1;
}

char *unqldb_get(unqldb *self, const char *key)
{
	unqlite_int64 nBytes;
	char *zBuf = NULL;
	int rc;
	rc = unqlite_kv_fetch(self->db,key,-1,NULL,&nBytes);
	if( rc != UNQLITE_OK )
		return NULL;
	
	zBuf = (char *)malloc(nBytes * sizeof(char));
	if( zBuf == NULL )
		return NULL;

	//Copy record content in our buffer
	rc = unqlite_kv_fetch(self->db,key,-1,zBuf,&nBytes);
	if( rc != UNQLITE_OK )
	{
		free(zBuf);
		zBuf = NULL;
		return NULL;
	}
	zBuf[nBytes] = '\0';
	
	return zBuf;
}

char *unqldb_get_size(unqldb *self, const char *key, unqlite_int64 *size)
{
	char *zBuf = NULL;
	int rc;
	rc = unqlite_kv_fetch(self->db,key,-1,NULL,size);
	if( rc != UNQLITE_OK )
		return NULL;
	
	zBuf = (char *)malloc(*size * sizeof(char));
	if( zBuf == NULL )
		return NULL;

	//Copy record content in our buffer
	rc = unqlite_kv_fetch(self->db,key,-1,zBuf,size);
	if( rc != UNQLITE_OK )
	{
		free(zBuf);
		zBuf = NULL;
		return NULL;
	}
	zBuf[*size] = '\0';
	
	return zBuf;
}

int unqldb_del(unqldb *self, const char *key)
{
	int rc;
	rc = unqlite_kv_delete(self->db ,key,-1);
	if( rc != UNQLITE_OK )
		return 0;
	return 1;
}

int unqldb_add_file(unqldb *self, const char *key, const char *path)
{
	void *pMap;
	unqlite_int64 nBytes;
	int rc;
	rc = unqlite_util_load_mmaped_file(path,&pMap,&nBytes);
	if( rc != UNQLITE_OK )
		return 0;
	rc = unqlite_kv_store(self->db,key,-1,pMap,nBytes);
	if( rc != UNQLITE_OK )
		return 0;
	unqlite_util_release_mmaped_file(pMap,nBytes);
	return 1;
}

int unqldb_backup(unqldb *self, const char *path)
{
	char *db_path = getDirPathFromPath(path);
	char *tmpName = (char *)malloc((strlen(db_path) + 4) * sizeof(char));
	strcpy(tmpName, db_path);
	strcat(tmpName, "tmp");
	free(db_path);
	
	unqlite_kv_cursor *pCursor;
	char *kBuf = NULL;
	int kBytes;
	char *vBuf = NULL;
	unqlite_int64 vBytes;
	int rc;
	rc = unqlite_kv_cursor_init(self->db,&pCursor);
	if( rc != UNQLITE_OK )
	{
		free(tmpName);
		return 0;
	}
	rc = unqlite_kv_cursor_first_entry(pCursor);
	if( rc != UNQLITE_OK )
	{
		free(tmpName);
		return 0;
	}
	
	unqldb *udb = NULL;
	FILE* fp = NULL;
	
	while( unqlite_kv_cursor_valid_entry(pCursor) )
	{
		kBuf = NULL;
		kBytes = 0;
		vBuf = NULL;
		vBytes = 0;
		
		rc = unqlite_kv_cursor_key(pCursor,NULL,&kBytes);
		if( rc != UNQLITE_OK )
		{
			free(tmpName);
			return 0;
		}
		kBuf = (char *)malloc(kBytes * sizeof(char));
		if( kBuf == NULL )
		{
			free(tmpName);
			return 0;
		}
		//Copy record content in our buffer
		rc = unqlite_kv_cursor_key(pCursor,kBuf,&kBytes);
		if( rc != UNQLITE_OK )
		{
			free(tmpName);
			free(kBuf);
			kBuf = NULL;
			return 0;
		}
		kBuf[kBytes] = '\0';
		
		rc = unqlite_kv_cursor_data(pCursor,NULL,&vBytes);
		if( rc != UNQLITE_OK )
		{
			free(tmpName);
			free(kBuf);
			kBuf = NULL;
			return 0;
		}
		vBuf = (char *)malloc(vBytes * sizeof(char));
		if( vBuf == NULL )
		{
			free(tmpName);
			free(kBuf);
			kBuf = NULL;
			return 0;
		}
		//Copy record content in our buffer
		rc = unqlite_kv_cursor_data(pCursor,vBuf,&vBytes);
		if( rc != UNQLITE_OK )
		{
			free(tmpName);
			free(kBuf);
			kBuf = NULL;
			free(vBuf);
			vBuf = NULL;
			return 0;
		}
		vBuf[vBytes] = '\0';
		
		fp = fopen(tmpName,"wb");
		if(fp != NULL)
		{
			fwrite(vBuf, 1, (size_t)vBytes, fp);
		}
		fclose(fp);
		
		if (udb == NULL)
		{
			if( access( path, F_OK ) == 0 )
				remove(path);
			udb = unqldb_init(path);
		}
		udb->add_file(udb,kBuf,tmpName);
		
		remove(tmpName);
		
		free(kBuf);
		free(vBuf);
		
		unqlite_kv_cursor_next_entry(pCursor);
	}
	
	if (udb != NULL)
		unqldb_deinit(udb);

	unqlite_kv_cursor_release(self->db,pCursor);
	
	free(tmpName);
	
	return 1;
}