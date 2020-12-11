#include <stdio.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <unistd.h>
#include <grp.h>


int main(int ac, char *av[]){
	struct passwd* p;
	struct group* g;
	int n;
	int am = 10;
	gid_t list[10];
	if (ac == 1){
		uid_t uid;
		gid_t gid;
		uid = getuid();
		p = getpwuid(uid);
		gid = getgid();
        	g = getgrgid(gid);
		n = getgroups(100, list);
		printf("uid=%d(%s) gid=%d(%s) groups=%d(%s)",p->pw_uid, p->pw_name, g->gr_gid, g->gr_name, g->gr_gid, g->gr_name);
        	for (int i = 0; i < n - 1; i++){
                	if (list[i] != g->gr_gid)
                        	printf(",%d(%s)", list[i], getgrgid(list[i])->gr_name);
		}
	}else{
		p = getpwnam(av[1]);
		g = getgrnam(av[1]);
		getgrouplist(av[1], g->gr_gid, list, &am);
		printf("uid=%d(%s) gid=%d(%s) groups=%d(%s)",p->pw_uid, p->pw_name, g->gr_gid, g->gr_name, g->gr_gid, g->gr_name);
		for (int i = 0; i < am; i++){
                       if (list[i] != g->gr_gid)
                               printf(",%d(%s)", list[i], getgrgid(list[i])->gr_name);
                             		}
	}
	return 0;
}
