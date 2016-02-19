#include <stdio.h>

typedef struct que{
	int no;
	char name[64];

	int (*get_no)(struct que *this);
	void (*set_no)(struct que *this, int);
}que_s;

int que_get_no(que_s *this);
void que_set_no(que_s *this, int);

int main(int argc ,char **argv)
{
	que_s s1;

	s1.get_no = que_get_no;
	s1.set_no = que_set_no;

	s1.set_no(&s1, 100);

	printf("s1.no %d  s1.no(get_no) %d\n", s1.no, s1.get_no(&s1));

	return 0;
}


int que_get_no(que_s *this)
{
	if(this)
		return this->no;
	else
		return -1;
}

void que_set_no(que_s *this, int no)
{
	if(this)
		this->no = no;
}
