#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "nexus_types.h"
#include "nexus_platform.h"
#include "bstd.h"
#include "bkni.h"
#include "bkni_event_group.h"
#include "nexus_input_capture.h"
#include "nexus_input_capture_init.h"
#include "nexus_ir_input.h"

#include <unistd.h>
#include <signal.h>

/************************macros************************************/
#if 0
#define DEBUG   printf
#else
#define DEBUG
#endif

#if 0
#define DBG_LAKALA(fmt, arg...)  printf("LAKALA:[%s]:"fmt, __FUNCTION__, ## arg )
#else
#define DBG_LAKALA(fmt, arg...)
#endif

static NEXUS_InputCaptureHandle capHandle;

enum{IDLE, NEC_S=1, NEC_P=2, NEC_R=4, LAKALA=8};

/************************ symbol defines **************************/
typedef struct{
    #define BUF_SIZE 1024
	long time[BUF_SIZE];
	unsigned triger;
	int wpos, rpos;
	int count;
	bool overflow;
}symbol_t;

static symbol_t symbol = {{0},
                    0, /*triger 10, every 10 symbol,give the event*/
                    0, 0,
                    0,
                    false};



#define get_rpos(sym,offs)  ((sym.rpos+(offs))%BUF_SIZE)
#define put_rpos(sym,offs)  sym.rpos=(sym.rpos+(offs))%BUF_SIZE

/************************ lakala key defines **************************/
/* for lakala key*/
typedef struct {
    #define LAKALA_BUF_SIZE    1024
    unsigned char key[LAKALA_BUF_SIZE];
    int count;
    int rpos,wpos;
}lakala_key_t;
static lakala_key_t lakala={{0},0,0,0};

#define set_rpos(la,offs)   la.rpos = (la.rpos+offs)%LAKALA_BUF_SIZE
#define set_wpos(la,offs)   la.wpos = (la.wpos+offs)%LAKALA_BUF_SIZE
#if 1
static void put_key(lakala_key_t *la, unsigned char key)
{
    la->key[la->wpos] = key;
    la->count++;
    la->wpos++;
    la->wpos%=LAKALA_BUF_SIZE;
}

static unsigned char get_key(lakala_key_t *la, unsigned char *key)
{
    unsigned char tmp = la->key[la->rpos];
    la->rpos++;
    la->rpos %= LAKALA_BUF_SIZE;
    la->count--;

    if( key )
        *key = tmp;
    return tmp;
}
#else
#define get_key(la,offs)    (la.key[get_rpos(la,offs)])
/*donnot not why this not work*/
#define put_key(la,offs,key) (la.key[get_wpos(la,offs)]) = key
#endif


/* nec decode */
static int ir_decode_nec(symbol_t sym, unsigned char *key_code, int *key_num)
{
	int ret = -1;
	int pos, i = 0, _key_num;
	if( !key_code || !key_num )
		return ret;

	_key_num = 0;

	DEBUG("%s:rpos=%d wpos=%d\n", __FUNCTION__, sym.rpos, sym.wpos);
	for(;i<32;i++)
	{
	    pos = get_rpos(sym,i);
	/*  DEBUG("%ld %s\n",sym.time[pos+i], "us");*/
		/*
		2700 2250 1800, 1344 1120 896
		*/
		if ( (sym.time[pos] > 2700) || (sym.time[pos] < 896) )
		{
		    /*fixme. this should return from this functin,because it isnot nec symbol*/
		    ;
		}

		if(sym.time[pos] > 1650)
			/* bit 1 */
			key_code[_key_num] |= 1<<(i%8);

		if((i+1)%8 == 0)
		{
			DEBUG("%d  0x%02x\n", _key_num, key_code[_key_num]);
			_key_num++;
		}
	}

	*key_num = _key_num;
	DEBUG("key_num %d\n", *key_num);
	return 0;
}

/* lakala decode */
static int ir_decode_lakala(symbol_t sym)
{
    int pos, i=0, n,bits=0,start_pos=0, end_pos=9,has_start=0;
    unsigned char data = 0;
    n = sym.wpos - sym.rpos;
    n += (n<0?BUF_SIZE-1:0);
    for(i=0,start_pos=0;i<n;i++)
    {
        pos = get_rpos(sym,i);
        DBG_LAKALA("pos=%d time=%ld has_start=%d \n", \
                pos, sym.time[pos], has_start);

        if( sym.time[pos] > 45000 && sym.time[pos] < 65000 )
        {
            /* protocol : every protocol package, the idle time is 50ms */
            DBG_LAKALA("catch a 50MS inter-gap\n");
            continue;
        }
        if( sym.time[pos] > 10000 && sym.time[pos] < 30000)
        {
            /* protocol : every 16bytes,delay 20ms,then continue to transmit */
            DBG_LAKALA("catch a 20MS inter-gap\n");
            continue;
        }

        /* !fixme: if in the lakala mode ,the data has more dismatch with the protocol */
        #if 0
        /* maybe this is the right condition, but for exception */
        if( sym.time[pos] > 3000 || sym.time[pos] < 400)/*50%*/
        #else
        if( sym.time[pos] > 9000 || sym.time[pos] < 400)/*more then 100%*/
        #endif
            return 0-i;/*goto IDLE*/

        if( !has_start )
        {
            /* this should be start */
            if( sym.time[pos] < 1100 )/*30%*/
            {
                if( n-i < 10 )
                    return i;

                has_start = 1;
                start_pos = i;
                end_pos = i+9;
            }else if(sym.time[pos] < 1600){/*1428*/
                DBG_LAKALA("catch one inter-gap!\n");
                if( n-i < 10 )
                    return i;
            }
            continue;
        }

        if( sym.time[pos] < 1200 )/*1100*/
        {
            bits++;
        }
        else if(sym.time[pos] > 1428)
        {
            /* check if is end_pos */
            if( i == end_pos )
            {
                if( (sym.time[pos]>1428)  )
                {
                    DBG_LAKALA("catch one data: 0x%02x\n", data);
                    put_key(&lakala, data);
                    data = 0;
                    bits = 0;
                    has_start = 0;
                }
            }else{
                data |= 1<<bits;
                bits++;
            }
        }
        else{
             DBG_LAKALA("error should not come here. this\"gap\" shoudle be 0 or 1\n");
        }
    }

    return i;/*success, not need goto IDLE */
}

/* get us for two timepsec struct, it just use in InputCapture Callback */
static long ts_delta_us (struct timespec now,
			     struct timespec last)
{
    /* return the data in us */
	if (now.tv_nsec < last.tv_nsec) {
		return (now.tv_sec - last.tv_sec) * 1000 * 1000 -
			(last.tv_nsec - now.tv_nsec) / 1000;
	}else{
	    int _s = now.tv_sec - last.tv_sec;

	    return _s>=1000?-1:(_s*1000*1000 + (now.tv_nsec - last.tv_nsec)/1000);
	}
	return -1;
}

/* this is just for debug the lakala key receive */
static void timeoutHandler(int signo)
{
   if(signo == SIGALRM)
    {
        unsigned char key = 0;
        int i=0;
        printf("LAKALA code count=%d\n", lakala.count);
        while(lakala.count)
        {
            key = get_key(&lakala,0);
            printf("\t%d %02x\n", ++i, key);
        }
   }
}

/* get the time for each symbol */
void capture_callback(void *context, int param)
{
    static struct timespec last;
    struct timespec now;
    int tmp;
    long tval;
	NEXUS_InputCaptureStatus status;
	NEXUS_InputCapture_GetStatus(capHandle, &status);

    BSTD_UNUSED(param);

    clock_gettime(CLOCK_MONOTONIC, &now);
    tval = ts_delta_us(now, last);
    last = now;

    /*put the time to symbol */
    symbol.time[symbol.wpos] = tval;

	/* get the symbol */
	symbol.wpos++;
	symbol.wpos %= BUF_SIZE;
	symbol.count++;
	if(symbol.wpos < symbol.rpos)
	{
		NEXUS_InputCapture_Reset(capHandle);
		symbol.overflow = true;
	}

    #if 0
	if( symbol.overflow || (symbol.wpos - symbol.rpos)>=symbol.triger)
    #else
    tmp = symbol.wpos-symbol.rpos + symbol.overflow*BUF_SIZE;
  	if(tmp>=symbol.triger)
    #endif
	{
		BKNI_SetEvent((BKNI_EventHandle)context);
	}
}

/* this fo IrInput callback , this time just set for nec */
void ir_callback(void *context, int param)
{
    BSTD_UNUSED(param);
	BKNI_SetEvent((BKNI_EventHandle)context);
}

int main(int argc, char **argv)
{
    NEXUS_PlatformSettings platformSettings;
	NEXUS_Error rc;

	/* event group */
	BKNI_EventGroupHandle eventGroup;
	BKNI_EventHandle  retEvent[2];
	unsigned retEventNum;

	/*  ir input */
	NEXUS_IrInputHandle irHandle;
	NEXUS_IrInputSettings irSettings;
	BKNI_EventHandle ir_event;

	/*  capture  */
    NEXUS_InputCaptureSettings capSettings;
/*  	NEXUS_InputCaptureHandle capHandle;*/
	BKNI_EventHandle cap_event;

    BSTD_UNUSED(argc);
    BSTD_UNUSED(argv);

    NEXUS_Platform_GetDefaultSettings(&platformSettings);
    platformSettings.openFrontend = false;
    NEXUS_Platform_Init(&platformSettings);

	/*  open IR for NEC protocol */
	BKNI_CreateEvent(&ir_event);
	NEXUS_IrInput_GetDefaultSettings(&irSettings);
#if 1
	/*  for NEC  */
	irSettings.mode = NEXUS_IrInputMode_eCirNec;
#else
	irSettings.mode = NEXUS_IrInputMode_eRemoteA;
#endif
	irSettings.dataReady.callback = ir_callback;
	irSettings.dataReady.context = ir_event;
    irHandle = NEXUS_IrInput_Open(0, &irSettings);

	/*  open capture for another remouter */
	BKNI_CreateEvent(&cap_event);
    NEXUS_InputCapture_GetDefaultSettings(&capSettings);
	capSettings.rejectCount = 15;
	capSettings.edgeConfig = NEXUS_InputCaptureEdgeConfig_eNegative;/*NEXUS_InputCaptureEdgeConfig_eBoth;*/
	capSettings.trigger.callback = capture_callback;
	capSettings.trigger.context = cap_event;
    capHandle = NEXUS_InputCapture_Open(3, &capSettings);
	if (capHandle==NULL)
	{
		printf("error from NEXUS_InputCapture_Open\n");
		return 1;
	}


	/*  creat event group */
	BKNI_CreateEventGroup(&eventGroup);
	BKNI_AddEventGroup(eventGroup, ir_event);
	BKNI_AddEventGroup(eventGroup, cap_event);

    signal(SIGALRM, &timeoutHandler);
    printf("\nWaiting for key...\n");
	while(1)
	{
#if 0
		BKNI_WaitForEvent(cap_event, 0xFFFFFFFF);
#else
		rc = BKNI_WaitForGroup(eventGroup, 0xFFFFFFFF, retEvent, sizeof(retEvent)/sizeof(retEvent[0]), &retEventNum );
#endif

		if( retEventNum == 0 )
			continue;

		if( retEventNum == 2 || retEvent[0] == ir_event )
		{
			/*  process ir */
			NEXUS_IrInputEvent irEvent;
			size_t numEvents;
			bool overflow;
			rc = NEXUS_IrInput_GetEvents(irHandle,&irEvent,1,&numEvents,&overflow);
			if (numEvents)
				printf("irInput:\n\tcode: %08x\n\trepeat: %s\n"
						"\tcodeHigh: %u\n\tinterval: %u\n"
						"\toverflow: %s\n",
						irEvent.code, irEvent.repeat ? "true" : "false",
						irEvent.codeHigh, irEvent.interval,
						overflow ? "true":"false");
		}

		if( retEventNum == 2 || retEvent[0] == cap_event)
		{
			/*  process capture */
			/*  in the callback get symbol, here just process the symbols */
            int n, rpos, i;
			static unsigned char key_code[10];
			static int key_num;
			static int stateM = 0;

			n = symbol.wpos - symbol.rpos;
            n += (n<0?(BUF_SIZE-1):0);
            DEBUG("symbol:rpos=%d wpos=%d triger=%d %s |*| avail num:%d \n",
                    symbol.rpos, symbol.wpos, symbol.triger,
					symbol.overflow?"|*| overflow":"", n);
#if 0
			/*  for debug */
			{
				for(i=0; i<n; i++)
				{
				    rpos = get_rpos(symbol, i);
					DEBUG("bit:time=%ld\n",  symbol.time[rpos]);
				}
			}
#endif

			if( stateM == IDLE)
			{
			        /* check nec_s or LAKALA */
					/* check for nec start */
					for(i=0; i<n; i++)
					{
					    rpos = get_rpos(symbol,i);
						DEBUG("IDLE:readpos:%d time=%ld\n", rpos, symbol.time[rpos]);
#if 0
						if( (symbol.time[rpos] == -1) || (symbol.time[rpos] > 12))								)
							break;
#endif

						if( (symbol.time[rpos] > 12*1000) &&\
								(symbol.time[rpos] < 15*1000) )
						{
						    DEBUG("IDLE:find NEC leader n=%d rpos=%d wpos=%d i=%d triger=%d\n",
						        n, symbol.rpos, symbol.wpos,i, symbol.triger);
						    stateM = NEC_S;

                            /* set tirger */
                            if( n < 30 )
    						    symbol.triger = 30;
    					    else
    						    symbol.triger = 0;

                            i++;
							break;
						}


					   /* try to use lakala protocal */
						if( symbol.time[rpos] < 1100 && symbol.time[rpos] > 580 )/* 840 +- 30% */
						{
						    stateM = LAKALA;

						    if( n < 30 )
						        symbol.triger = 10;

                            DEBUG("IDLE:try to LAKALA n=%d rpos=%d wpos=%d i=%d triger=%d\n",
						        n, symbol.rpos, symbol.wpos,i, symbol.triger);
						    break;
						}
					}
					 n -= i;
				     put_rpos(symbol, i);
			}

			if(stateM & NEC_S)
			{
			    /* decode nec 32bits */
				DEBUG("NEC_S:n=%d rpos=%d wpos=%d triger=%d\n", n, symbol.rpos, symbol.wpos, symbol.triger);
				if( n >= 32 )
				{
					DEBUG("NEC_S:try to decode symbol...\n");
					ir_decode_nec(symbol, key_code, &key_num);
					printf("\nInputCapture:%d\n", key_num);
					for(i=0;i<key_num;i++)
						printf("\t%d  0x%02x\n", i, key_code[i]);
					memset(key_code, 0, key_num+1);

					n -= 32;
					put_rpos(symbol,32);
					stateM = NEC_P;

					symbol.triger = 0;
				}
			}

			if(stateM&NEC_P)
			{
   			    /* decode nec Repeat */
        		DEBUG("NEC_P:n=%d rpos=%d wpos=%d triger=%d\n", n, symbol.rpos, symbol.wpos, symbol.triger);
				rpos = symbol.rpos;

				if(n>=2)
				{
				    i = 0;
					while(i<n)
					{
					    rpos = get_rpos(symbol, 0);
						DEBUG("bit:time=%ld n=%d rpos=%d wpos=%d\n",
						    symbol.time[rpos], n, symbol.rpos, symbol.wpos);
						/*  check if invalue symbol */
						if( symbol.time[rpos]==-1 )
						{
							/* next to IDLE, then check the event */
							DEBUG("NEC_P:goto IDLE\n");
							stateM = IDLE;
							put_rpos(symbol, i+1);
							if(n<30)
								symbol.triger = 10;
							else
								symbol.triger = 0;

							break;
						}else

						/*  check if repeat code */
						if( 	(symbol.time[rpos]>20*1000 && symbol.time[rpos]<130*1000) &&
								(symbol.time[rpos+1]<135*100 &&	symbol.time[rpos+1]>9*1000)
						   )
						{
							printf("InputCapture: repeated\n");
							put_rpos(symbol,2);
							i+=2;
						}else{
							DEBUG("NEC_P:not match NEC_Repeat , Goto IDLE\n");
							stateM = IDLE;
							break;
						}
					}

				}
			}

			if( stateM&LAKALA )
			{
  				DBG_LAKALA("n=%d rpos=%d wpos=%d triger=%d\n",
  				         n, symbol.rpos, symbol.wpos, symbol.triger);
  				if( n >= 10 )
  				{
  				    int ret = ir_decode_lakala(symbol);
  				    DBG_LAKALA("decode ret=%d\n",ret);
  				    if( ret <= 0 )
  				    {
  				        put_rpos(symbol,0-ret);
  				        stateM = IDLE;
  				    }else
  				        put_rpos(symbol, ret);

                    /* use alarm to repleace it*/
                    #if 0
                    if( lakala.count )
                    {
                        static int _count = 0;
                        printf("LAKALA code count=%d\n", lakala.count);
      				    while( lakala.count )
      				    {
      				        ret = get_key(&lakala,0);
      				        printf("\t%02x  %d\n", ret, _count++);
      				    }
  				    }
  				    #else
  				    /* after 2s then printf the data */
  				        alarm(2);
  				    #endif
  				}
			}

            if(symbol.overflow)
                symbol.overflow = false;
		}
    }

	NEXUS_InputCapture_Close(capHandle);
	NEXUS_IrInput_Close(irHandle);
    NEXUS_Platform_Uninit();
    return 0;
}
