#ifndef __CONFIG_H_
#define __CONFIG_H_


//#undef DEBUG //������

/*************************************���Ժ�*****************************************/

#ifdef DEBUG
#define debug(format, ...)   fprintf(stderr,"[debug][%s:%s:%d] "format"",\
               __FILE__,__FUNCTION__,__LINE__,##__VA_ARGS__)
#else


#define debug(...)
#endif

/*************************************��������*****************************************/







#endif
























