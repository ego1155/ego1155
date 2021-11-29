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