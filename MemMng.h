
/*****************************************\
*  文件：MemMng.h                         *
*  描述：内存管理                         *
*  制作：朱广锋                           *
*  时间：2017年12月6日                    *
*  修改：                                 *
*      2017-12-14                         *
*        修改CREATE_ARRAY宏               *
*        取消中间的GetMemery函数调用      *
\*****************************************/

#ifndef MEMMNG_H
#define MEMMNG_H
//#define MEMMNG_AUTO_SET_NULL
//设置自动清除指针内容

#include<stdlib.h>

//申请内存
template<class Type>
inline Type*&GetMemery(Type*&PData,unsigned int Len){
	return PData=(Type*)calloc(Len,sizeof(Type));
}
//重设内存
template<class Type>
inline Type*&ResizeMemery(Type*&PData,unsigned int newLen){
	return PData=(Type*)realloc(PData,newLen*sizeof(Type));
}
//释放内存
template<class Type>
inline void FreeMemery(Type*&PData){
	free(PData);
#ifndef MEMMNG_AUTO_SET_NULL
	PData=NULL;
#endif
}
#define CREATE_ARRAY(TYPE,X,LEN)     TYPE*X=(TYPE*)calloc(LEN,sizeof(TYPE));
#define CreateArray CREATE_ARRAY
#endif