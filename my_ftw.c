#include "dir.h"
#include "my_ftw.h"

/* File Tree Walk와 같은 작업을 수행하는 실제 함수  */
int my_ftw (char * dirpath)
{
	int ret = 0;

	do
	{
		DIR *dp = NULL;
		struct dirent * dirp = NULL;
		int file_cnt = 0;

		if ((dp = opendir(dirpath)) == NULL)
		{
			//printf("openddir error: %s\n", dirpath);
			ret = -1;
			break;
		}

		assert (dp != NULL);
		/* 디렉토리의 모든 파일 또는 디렉토리 탐색 */
		while((dirp = readdir(dp)) != NULL)
		{
			char filepath[PATH_MAX] = {0,};
			struct stat file_stat = {0,};

			assert (dirp != NULL);
			if (strcmp (dirp->d_name, ".") == 0 ||
				strcmp (dirp->d_name, "..") == 0)
			{
				continue;
			}

			file_cnt++;

			strncpy(filepath, dirpath, strlen(dirpath));
			strcat(filepath, dirp->d_name);

			if (is_dir (filepath))
			{
				char *ptr = NULL;

				ptr = dirpath + strlen(dirpath);

				strcat (dirpath, dirp->d_name);
				strcat (dirpath, "/");
				ret = my_ftw (dirpath);	/* 재귀호출 */

				/* 하위 디렉토리 탐색이 완료되면 / 이하를 삭제한다. */
				assert (ptr != NULL);
				*ptr = '\0';
			}
			else 
			{
				assert (filepath != NULL);
				printf ("%s\n", filepath);
			}
		}

		/* 디렉토리가 비어있다면, 디렉토리의 이름을 출력 */
		if (file_cnt == 0)
		{
			assert (dirpath != NULL);
			printf("%s\n", dirpath);
		}
	
		if (closedir(dp) == -1)
		{
			printf ("closedir error.\n");
			ret = -1;
		}

	} while (0);

	return ret;
}
