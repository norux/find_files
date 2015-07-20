#include "dir.h"

/* 마지막 / 체크 */
static void check_last_char (char * dirpath)
{
	int len = strlen (dirpath);
	
	if (dirpath[len - 1] != '/')
	{
		dirpath[len++] = '/';
		dirpath[len] = '\0';
	}
}

/* 일반 디렉토리의 경우 슬래시(/)뒤에 그대로 붙여준다. */
static int put_dir (char * in_dir, char * ret_dir)
{
	char * token = NULL;
	char tmp[PATH_MAX] = {0,};
	int len = 0;
	int ret = 0;

	token = strchr (in_dir, '/');

	if (token != NULL)
	{
		int len = token - in_dir;
		strncpy (tmp, in_dir, len); 
	}
	else
	{
		strcpy (tmp, in_dir);
	}

	strcat (ret_dir, "/");
	strcat (ret_dir, tmp);

	ret = strlen (tmp);

	return ret;
}

/* ~를 home 경로로 변환한다. */
static int get_home_path (const char * in_dir, char * ret_dir)
{
	char username[128] = {0,};

	if (getlogin_r (username, sizeof(username)))
	{
		printf ("getlogin_r error.\n");
		return -1;
	}

	sprintf (ret_dir, "/home/%s/", username);

	if (in_dir[1] == '/')
	{
		strcat (ret_dir, in_dir + 2);
	}

	return 0;
}

bool is_dir (const char * filepath)
{
	struct stat file_stat = {0,};

	if (stat (filepath, &file_stat) == -1)
	{
		return false;
	}

	if (S_ISDIR(file_stat.st_mode))
	{
		return true;
	}
	else
	{
		return false;
	}
}

/* 인자로 넘어온 경로를 루트부터의 절대경로로 변환해준다. */
int get_base_dir (char * in_dir, char * ret_dir)
{
	char dir[PATH_MAX] = {0,};
	char * pdir = in_dir;

	/* 절대경로 처리 */
	if (in_dir[0] == '/' || in_dir[0] == '~')
	{
		if (in_dir[0] == '~')
		{
			get_home_path (in_dir, dir);
		}
		else if (in_dir[0] == '/')
		{
			strcpy (dir, in_dir);
		}

		check_last_char (dir);

		strncpy (ret_dir, dir, strlen(dir));

		return 0;
	}


	/* 상대경로 처리*/
	if (getcwd(dir, PATH_MAX) == NULL)
	{
		printf("getcwd error.\n");
		return -1;
	}

	assert (pdir != NULL);
	while (*pdir != '\0')
	{
		if (*pdir == '.' && *(pdir + 1) == '.')
		{
			char * last_dir = NULL;

			last_dir = strrchr (dir, '/');
			*(last_dir) = '\0';
			
			pdir+=2;
		}
		else if (*pdir == '.' || *pdir == '/')
		{
			pdir++;
		}
		else
		{
			int len = 0;
			len = put_dir (pdir, dir); 
		
			pdir += len;
		}
	}

	check_last_char (dir);

	/* root를 가리키고 있을 때 */
	if (strlen(dir) == 0)
	{
		dir[0] = '/';
	}

	strncpy (ret_dir, dir, strlen(dir));

	return 0;
}



