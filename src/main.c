#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char** argv) {
	char pkgname[128];
	char command[128];
	char path[64];
	bool gitSuffix = true;

	if (argc == 1) {
		printf("aur-install\nmy tool for installing things from AUR\n");
		return 0;
	}

	
	for (size_t i = 1; i<(size_t)argc; ++i) {
		if (argv[i][0] == '-') {
			if (strcmp(argv[i], "-gs") == 0) { // toggle git suffix
				gitSuffix = !gitSuffix;
			}
		}
		else {
			printf("installing %s\n\n", argv[i]);
			if (gitSuffix) sprintf(pkgname, "https://aur.archlinux.org/%s-git.git", argv[i]);
			else sprintf(pkgname, "https://aur.archlinux.org/%s.git", argv[i]);
			sprintf(command, "git clone %s", pkgname);
			system(command);
			if (gitSuffix) sprintf(path, "%s-git", argv[i]);
			else strcpy(path, argv[i]);
			chdir(path);
			system("makepkg -si");
			chdir("..");
			if (gitSuffix) sprintf(command, "rm -rdf %s-git", argv[i]);
			else sprintf(command, "rm -rdf %s", argv[i]);
			system(command);
		}
	}
}
