#pragma once 

//Ԥ�����
#ifdef DEBUG
#define GL_CALL(func)  func;checkError();
#else
#define GL_CALL(func) 
#endif 


void checkError();