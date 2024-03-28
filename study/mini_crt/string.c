int strcmp(const char* src, const char* dst)
{
	int ret = 0;
	unsigned char* p1 = (unsigned char*)src;
	unsigned char* p2 = (unsigned char*)dst;
	while(!(ret = *p1 - *p2) && *p2) ++p1,++p2;
	if(ret < 0) ret = -1;
	else if(ret > 0) ret = 1;
	return ret;
}

int strlen(const char* s)
{
	int cnt = 0;
	while(s[cnt++]);
	return cnt - 1;
}

void strcpy(char* dst, const char* src)
{
	while(*(dst++) = *(src++));
}
