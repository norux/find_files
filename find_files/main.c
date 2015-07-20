#include "common.h"
#include "dir.h"
#include "my_ftw.h"


void error_exit (const char * error_msg)
{
	printf ("%s\n", error_msg);
	exit (-1);
}

int main (int argc, char * argv[])
{
	char base_dir[PATH_MAX] = {0,};
	struct stat argv_stat = {0,};

	if (argc != 2)
	{
		printf("USAGE: %s [DIRECTORY] \n", argv[0]);
		exit (-1);
	}

	if (!is_dir(argv[1]))
	{
		error_exit (strerror(ENOTDIR));
	}

	if (get_base_dir (argv[1], base_dir) == -1)
	{
		error_exit ("get_base_dir error.\n");
	}

	/* base_dir의 값이 채워져 있어야 한다. */
	assert (strlen(base_dir) > 0);
	if (strlen(base_dir) == 0)
	{
		error_exit ("base_dir issn't filled.\n");
	}

	printf("base(root) directory: %s\n", base_dir);
	printf("\n");

	/* 파일트리탐색을 시작한다. */
	if (my_ftw (base_dir) == -1)
	{
		error_exit ("my_ftw error.\n");
	}

	return 0;
}
