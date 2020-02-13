
/*****************************************\
*  �ļ���MemMng.h                         *
*  �������ڴ����                         *
*  ����������                           *
*  ʱ�䣺2017��12��6��                    *
*  �޸ģ�                                 *
*      2017-12-14                         *
*        �޸�CREATE_ARRAY��               *
*        ȡ���м��GetMemery��������      *
\*****************************************/

#ifndef MEMMNG_H
#define MEMMNG_H
//#define MEMMNG_AUTO_SET_NULL
//�����Զ����ָ������

#include<stdlib.h>

//�����ڴ�
template<class Type>
inline Type*&GetMemery(Type*&PData,unsigned int Len){
	return PData=(Type*)calloc(Len,sizeof(Type));
}
//�����ڴ�
template<class Type>
inline Type*&ResizeMemery(Type*&PData,unsigned int newLen){
	return PData=(Type*)realloc(PData,newLen*sizeof(Type));
}
//�ͷ��ڴ�
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