static void _dumpdata(const char *funcname, int line, unsigned char *buf, int ret)
{
	   #define IS_PRINTF(c)    ((c)>=0x20 && (c)<=0x7E)
	    int i = 0;
	    printf("\n[%s][%d] num=%d\n", funcname, line, ret);
	    for(i = 0; i < ret; i++)
	    {
	        printf("%02x%s", (unsigned char)buf[i], (i+1)%16?" ":" | ");
	        if( ((i+1) % 16 == 0) )
	        {
	            int j = i - 15;
	            for(; j <= i; j++)
	                printf("%c",IS_PRINTF((unsigned char)buf[j])?(unsigned char)buf[j]:'.');
                printf("\n");
	        }
	    }
	    if( i%16 != 0 )
	    {
	        int j = 16 - (i+1)%16;
	        for(; j >= 0; j--)
	            printf("   ");
	        printf("| ");

	        j = i - (i+1)%16 + 1;
	        for(; j < i; j++)
                printf("%c",IS_PRINTF((unsigned char)buf[j])?(unsigned char)buf[j]:'.');

            printf("\n");
	    }
	    printf("\n[%s][%d] dump data over \n",funcname,line);
}
#if 0
#define DumpData(b,r)	_dumpdata(__FUNCTION__, __LINE__, (unsigned char *)(b), (int)(r))
#else
#define DumpData(b,r)
#endif
